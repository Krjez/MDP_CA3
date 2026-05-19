#include "RoboCatPCH.hpp"
#include "SaveManager.hpp"

std::unique_ptr<SaveManager> SaveManager::sInstance;

void SaveManager::StaticInit()
{
    sInstance.reset(new SaveManager());
}

SaveManager::SaveManager() : m_data_map()
{
	ReadDataFromFile();
}

SaveManager::~SaveManager()
{
	WriteDataToFile();
}


void SaveManager::SaveData(string id, string name)
{
	m_data_map[id] = name;
}

string SaveManager::LoadData(string id, string fallback_value)
{
	if(m_data_map.find(id) == m_data_map.end())
	{
		return fallback_value;
	}
	return m_data_map[id];
}

void SaveManager::ReadDataFromFile()
{
	std::ifstream file("player_data.txt");
	if (file.is_open())
	{
		std::string entry = "init";
		while (entry != "")
		{
			getline(file, entry, ';');
			auto pos = entry.find('=');
			if (pos == std::string::npos)
			{
				continue;
			}
			string id = entry.substr(0, pos);
			string data = entry.substr(pos + 1);
			m_data_map[id] = data;
		}
		file.close();
	}
}

void SaveManager::WriteDataToFile()
{
	std::ofstream file("player_data.txt", std::ofstream::trunc);

	for (auto& pair : m_data_map)
	{
		file << pair.first << "=" << pair.second << ";";
	}
	file.close();
}


