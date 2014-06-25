#include <string>
#include <vector>

#include "FileSystemAccess.hpp"
#include "Path.hpp"
#include "../emannlib-utility/AutoProfile.hpp"

namespace goldenduck
{
	
		void split(std::vector<std::string> &tokens, const std::string& startstring, const std::string& delimiter)
		{
			AUTO_PROFILE("DirectorySplit");
            size_t  start = 0, end = 0;

			while (end != std::string::npos)
			{
				end = startstring.find_first_of(delimiter, start);

				// If at end, use length=maxLength.  Else use length=end-start.
				if (end != start)
				{
					tokens.push_back(startstring.substr(start,
						(end == std::string::npos) ? std::string::npos : end - start));
				}
				// If at end, use start=maxSize.  Else use start=end+delimiter.
				start = ((end > (std::string::npos - 1))
						 ? std::string::npos : end + 1);
                
                
			}

		}

		Path::Path(const std::string& basePath)
		{
             AUTO_PROFILE("PathConstructor");
#ifdef WIN32
			split(m_PathComponents, basePath, "\\:");
#else
			split(m_PathComponents, basePath, "/");
#endif
		}


		std::ostream& operator<<(std::ostream& os, const Path& dt)
		{
             AUTO_PROFILE("PathOperator<<");
			if (dt.m_PathComponents.size() > 0)
			{
				auto it = dt.m_PathComponents.begin();
#ifdef WIN32
				os <<dt.m_PathComponents[0] << ":\\";
				it++;
#else
				os<< std::string("/");
#endif
				for (; it != dt.m_PathComponents.end(); ++it)
				{
					os << *it;
#ifdef WIN32
					os << "\\";
#else
					os << std::string("/");
#endif
				}
			}
			else
			{
				os << std::string("<empty path>");
			}
			return os;
		}
	
}