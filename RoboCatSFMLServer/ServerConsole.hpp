#pragma once

class ServerConsole
{
public:
    static void StaticInit();
    void Stop();

    static std::unique_ptr<ServerConsole> sInstance;

    ~ServerConsole() = default;

	int GetPort() const { return m_port.load(); }
	int GetLatency() const { return m_latency.load(); }
	float GetDropChance() const { return m_drop_chance.load(); }

private:

    ServerConsole();
    void RunConsole();

    std::atomic<bool> m_waiting_thread_end;
    std::unique_ptr<std::thread> m_console_thread;
    std::promise<void> m_start_promise;
    std::future<void> m_start_future;

    std::atomic<int> m_port;
    std::atomic<float> m_latency;
    std::atomic<float> m_drop_chance;
};