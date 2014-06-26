#ifndef __RESOURCE_MANAGER_HPP__
#define __RESOURCE_MANAGER_HPP__

#include "../emannlib-utility/Singleton.hpp"

#include <string>
#include <fstream>
#include <memory>
#include <map>
#include <inttypes.h>


namespace emannlib
{
	class Resource;

	class ResourceManager : public Singleton < ResourceManager >
	{
	public:
		ResourceManager(const std::string& basePath) : 
			m_BasePathLocation(basePath),
			m_NumFilesLoaded(0),
			m_ResourceMap()
			{}

		//std::ifstream LoadFile(const std::string& file);
		void LoadFile(const std::string& file);
		size_t GetFileSize(const std::string& file);
		char * GetFileData(const std::string& file);

	private:
		std::string m_BasePathLocation;

		std::map<std::string, Resource *> m_ResourceMap;
		
		uint32_t m_NumFilesLoaded;

		friend class Resource;

	};


	class Resource
	{
		friend class ResourceManager;

		Resource(const std::string & file) : m_FileName(file), m_FileData(NULL), m_FileSize(-1)
		{
			m_FileHandle.open(m_FileName, std::ios::binary);
			if (m_FileHandle.is_open())
			{
				m_FileHandle.seekg(0, std::ios::end);
				m_FileSize = m_FileHandle.tellg();
				m_FileData = new char[m_FileSize];
				m_FileHandle.seekg(0, std::ios::beg);
				m_FileHandle.read(m_FileData, m_FileSize);
			}
		}

		~Resource()
		{
			m_FileHandle.close();
			delete [] m_FileData;
		}


	private:
		std::string m_FileName;
		std::ifstream m_FileHandle;
		char * m_FileData;
		size_t m_FileSize;
	};

}


#endif