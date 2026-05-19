/*
*  Written by:
*  Petr Sulc - GD4b - D00261476
*  Jakub Polacek - GD4b - D00260171
*/

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

