#pragma once
class SaveManager
{
public:
	static void StaticInit();
	static std::unique_ptr<SaveManager> sInstance;

	void SaveData(string id, string data);

	string LoadData(string id, string fallback_value = "");

	~SaveManager();
private:
	void ReadDataFromFile();
	void WriteDataToFile();

	SaveManager();

	std::map<string, string> m_data_map;
};

