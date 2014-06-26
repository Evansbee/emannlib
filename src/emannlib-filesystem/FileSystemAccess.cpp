#include <string>

#include "FileSystemAccess.hpp"
#include "Path.hpp"
#include "../emannlib-utility/AutoProfile.hpp"

#include <cstdlib>

#ifdef WIN32
	#include <windows.h>
	#include <direct.h>
#else
	#include <sys/stat.h>
	#include <unistd.h>
#endif

namespace emannlib
{
	
		bool IsDirectory(const std::string& filename)
		{
             AUTO_PROFILE("IsDirectory");
#ifdef WIN32
            DWORD attribs = GetFileAttributesA(filename.c_str());
			if (attribs == INVALID_FILE_ATTRIBUTES) {
				return false;
			}
			return ((attribs & FILE_ATTRIBUTE_DIRECTORY) > 0);
#else
            struct stat st;
            return (stat(filename.c_str(), &st) == 0 && S_ISDIR(st.st_mode));
#endif
		}
		
        
        
		bool IsRegularFile(const std::string& filename)
		{
            AUTO_PROFILE("IsRegularFile");
            #ifdef WIN32
			DWORD attribs = GetFileAttributesA(filename.c_str());
			if (attribs == INVALID_FILE_ATTRIBUTES) {
				return false;
			}
			return ( (attribs & FILE_ATTRIBUTE_NORMAL) >0 );
#endif
            return false;
		}

        
        
		bool CreateDirectory(const std::string& directory)
		{
            AUTO_PROFILE("CreateDirectory");
            #ifdef WIN32
			if (IsDirectory(directory))
			{
				return true;
			}
			return (::CreateDirectory(directory.c_str(), NULL)  > 0);
#endif
            return false;
		}

		
        
        std::vector<std::string> GetFilesInDirectory(const std::string& directory)
		{
            AUTO_PROFILE("GetFilesInDirectory");
			std::vector<std::string> list;
			return list;
		}


		std::string GetWorkingDirectory()
		{
            AUTO_PROFILE("GetWorkingDirectory");
#ifdef WIN32
			char* cwd = _getcwd(NULL, 0);
#else
            const int CWD_BUFFER_TRY =1024;
            char buffer[CWD_BUFFER_TRY];
            if(getcwd(buffer, CWD_BUFFER_TRY))
            {
                return buffer;
            }
            size_t size = CWD_BUFFER_TRY * 2;
            char* cwd = (char*)malloc(size);
            while (!getcwd(cwd, size)) {
                size *= 2;
                cwd = (char*)realloc(cwd, size);
            }
#endif
			std::string ret(cwd);
			free(cwd);
			return ret;
       
		}
	
}