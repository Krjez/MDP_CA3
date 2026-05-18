#include "RoboCatServerPCH.hpp"
#include "ServerConsole.hpp"

#include "sstream"

std::unique_ptr<ServerConsole> ServerConsole::sInstance;

namespace
{
	BOOL WINAPI ConsoleCtrlHandler(DWORD event) {
		switch (event) {
		case CTRL_CLOSE_EVENT:
		case CTRL_LOGOFF_EVENT:
		case CTRL_SHUTDOWN_EVENT:
			// do your cleanup here
			ServerConsole::sInstance->Stop();
			return TRUE;  // signal we handled it
		}
		return FALSE;
	}

	void CreateDebugConsole() {
		AllocConsole();

		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
		freopen_s(&f, "CONOUT$", "w", stderr);
		freopen_s(&f, "CONIN$", "r", stdin);

		// Sync cout/cin/cerr with the new FILE* streams
		std::ios::sync_with_stdio(true);
		std::cout.clear();
		std::cerr.clear();
		std::cin.clear();

		SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
	}

	std::string GetLocalIP() {
		// Create a UDP socket
		SOCKET sock = socket(PF_INET, SOCK_DGRAM, 0);
		if (sock == INVALID_SOCKET) {
			LOG("Failed to retrieve local address (invalid socket)", 0);
			return "";
		}

		// Connect to a public IP (1.1.1.1) on any port
		// UDP won't actually send anything — just sets up routing
		sockaddr_in address = {};
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = htonl(0x01010101); // 1.1.1.1
		address.sin_port = htons(9);

		if (connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(address)) == SOCKET_ERROR) {
			closesocket(sock);
			LOG("Failed to retrieve local address (socket connection failure)", 0);
			return "";
		}

		// Read back the local address the OS chose
		int size = sizeof(address);
		if (getsockname(sock, reinterpret_cast<sockaddr*>(&address), &size) == SOCKET_ERROR) {
			closesocket(sock);
			LOG("Failed to retrieve local address (socket local address retrieval failure)", 0);
			return "";
		}

		closesocket(sock);

		// Convert to string
		char ipStr[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &address.sin_addr, ipStr, sizeof(ipStr));
		return ipStr;
	}
}

ServerConsole::ServerConsole() : m_waiting_thread_end(false), m_port(50000), m_latency(0), m_drop_chance(0.f)
{
}

void ServerConsole::StaticInit()
{
	sInstance.reset(new ServerConsole());
	sInstance->m_start_future = sInstance->m_start_promise.get_future();
	sInstance->m_console_thread = std::make_unique<std::thread>(&ServerConsole::RunConsole, sInstance.get());
	sInstance->m_start_future.wait();
}

void ServerConsole::RunConsole()
{
	CreateDebugConsole();

	std::cout << "Welcome to UltraRace Server Interface!" << std::endl;

	std::string localIP = GetLocalIP();
	if (localIP != "")
	{
		std::cout << "Your Local IP Address: " << localIP << std::endl;
	}
	else
	{
		std::cout << "Failed to retrieve local IP address." << std::endl;
	}
	std::cout << "Start the server using 'start'" << std::endl;
	std::cout << "Type 'help' for a list of commands" << std::endl;

	while (!m_waiting_thread_end)
	{
		std::cout << "> ";
		string command;
		std::getline(std::cin, command);
		
		std::vector<std::string> result;
		std::istringstream stream(command);
		std::string token;
		stream >> token;

		if(token == "quit")
		{
			Stop();
			continue;
		}

		if(token == "start")
		{
			std::cout << "Starting server..." << std::endl;
			m_start_promise.set_value();
			std::cout << "Server started on port " << m_port.load() << "." << std::endl;
			continue;
		}

		if(token == "help")
		{
			std::cout << "Available commands:\n";
			std::cout << "  start           - Start the server\n";
			std::cout << "  help            - Show this help message\n";
			std::cout << "  quit            - Stop the server and exit\n";
			std::cout << "  showip          - Display the server's local IP address\n";
			std::cout << "  port <number>   - Set the server's listening port\n";
			std::cout << "  dropchance <%>  - Set packet drop chance as a percentage (0-100)\n";
			std::cout << "  latency <ms>    - Set simulated latency in milliseconds\n";
			continue;
		}

		if (token == "showip")
		{
			std::string localIP = GetLocalIP();
			if (localIP != "")
			{
				std::cout << "Your Local IP Address: " << localIP << std::endl;
			}
			else
			{
				std::cout << "Failed to retrieve local IP address." << std::endl;
			}
			continue;
		}

		if (token == "port")
		{
			if(NetworkManagerServer::sInstance != nullptr)
			{
				std::cout << "Cannot change port while server is running." << std::endl;
				continue;
			}

			string amount;
			stream >> amount;
			if (amount.empty())
			{
				std::cout << "Usage: port <number>\n";
				continue;
			}

			try
			{
				int port = std::stoi(amount);
				port = std::max(1, std::min(65535, port));
				m_port = port;
				std::cout << "Setting port to " << port << std::endl;
			}
			catch (const std::invalid_argument&)
			{
				std::cout << "Invalid port value: '" << amount << "' is not a number\n";
			}
			catch (const std::out_of_range&)
			{
				std::cout << "Invalid port value: '" << amount << "' is out of range\n";
			}
			continue;
		}

		if (token == "dropchance")
		{
			string amount;
			stream >> amount;
			if (amount.empty())
			{
				std::cout << "Usage: dropchance <%>\n";
				continue;
			}

			try
			{
				int drop = std::stoi(amount);
				drop = std::max(0, std::min(100, drop));
				m_drop_chance = drop / 100.f;
				std::cout << "Setting drop chance to " << drop << "%\n";

				if (NetworkManagerServer::sInstance != nullptr)
				{
					NetworkManagerServer::sInstance->SetDropPacketChance(m_drop_chance.load());
				}

			}
			catch (const std::invalid_argument&)
			{
				std::cout << "Invalid drop chance value: '" << amount << "' is not a number\n";
			}
			catch (const std::out_of_range&)
			{
				std::cout << "Invalid drop chance value: '" << amount << "' is out of range\n";
			}
			continue;
		}

		if (token == "latency")
		{
			string amount;
			stream >> amount;
			if (amount.empty())
			{
				std::cout << "Usage: latency <ms>\n";
				continue;
			}

			try
			{;
				int latency = std::stoi(amount);
				latency = std::max(0, latency);
				m_latency = latency / 1000.f;
				std::cout << "Setting latency to " << latency << " ms\n";

				if (NetworkManagerServer::sInstance != nullptr)
				{
					NetworkManagerServer::sInstance->SetSimulatedLatency(m_latency.load());
				}
			}
			catch (const std::invalid_argument&)
			{
				std::cout << "Invalid latency value: '" << amount << "' is not a number\n";
			}
			catch (const std::out_of_range&)
			{
				std::cout << "Invalid latency value: '" << amount << "' is out of range\n";
			}
			continue;
		}

		std::cout << "Error: Unknown command '" << token << "'. Type 'help' to see available commands." << std::endl;

	}
}

void ServerConsole::Stop()
{
	std::cout << std::endl << "Closing server..." << std::endl;
	m_waiting_thread_end = true;

	// Unblock getline by injecting a fake enter key
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	ir.EventType = KEY_EVENT;
	ir.Event.KeyEvent.bKeyDown = TRUE;
	ir.Event.KeyEvent.wRepeatCount = 1;
	ir.Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
	ir.Event.KeyEvent.uChar.AsciiChar = '\r';
	DWORD written;
	WriteConsoleInput(hStdin, &ir, 1, &written);

	if (m_console_thread)
	{
		if (m_console_thread->get_id() != std::this_thread::get_id())
		{
			if (m_console_thread->joinable())
			{
				m_console_thread->join();
			}
		}
		else
		{
			if (m_console_thread->joinable())
			{
				m_console_thread->detach();
			}
		}
		m_console_thread.reset();
	}
	FreeConsole();
	if (Server::s_instance)
	{
		Server::s_instance->SetShouldKeepRunning(false);
	}
}
