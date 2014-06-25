#ifndef __FILE_SYSTEM_ACCESS_HPP__
#define __FILE_SYSTEM_ACCESS_HPP__

#include <string>
#include <vector>
#include <fstream>

namespace goldenduck
{
	
		bool IsDirectory(const std::string& filename);
		bool IsRegularFile(const std::string& filename);
		
		
		bool CreateDirectory(const std::string& directory);
		bool CreateFile(const std::string& filename);

		std::vector<std::string> GetFilesInDirectory(const std::string& directory);
		std::vector<std::string> GetDirectoriesInDirectory(const std::string& directory);

		bool ChangeFileName(const std::string& oldFileName, const std::string& newFileName);
		bool ChangeDirectoryName(const std::string& oldDirectoryName, const std::string& newDirectoryName);


		std::string GetWorkingDirectory();

		template <typename T>
		void ReadFromFile(std::ifstream& file, T& var)
		{
			file.read(reinterpret_cast<char *>(&var), sizeof(T));
		}
		template <typename T>
		void WriteToFile(std::ofstream& file, T& var)
		{
			file.write(reinterpret_cast<char *>(&var), sizeof(T));
		}


		//class File
		//{
		//public:
		//	static const uint32_t READ = 1;
		//	static const uint32_t WRITE = READ << 1;
		//	static const uint32_t READWRITE = READ | WRITE;

		//	static const bool PRELOAD = true;
		//	static const bool NO_PRELOAD = false;


		//public:
		//	bool Rename(const std::string& newName){ return false; }
		//	bool Delete(){ return false; };
		//	bool Create(){
		//		return false;
		//	}
		//	char *GetData(){ return NULL; };

		//private:
		//	char* m_Data;
		//	std::fstream m_File;
		//	std::string m_Name;


		//};

}


#endif