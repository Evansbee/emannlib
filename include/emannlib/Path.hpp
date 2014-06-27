#ifndef __PATH_HPP__
#define __PATH_HPP__

#include <string>
#include <vector>
namespace emannlib
{
	
		class Path 
		{
		public:
			Path(const std::string& basePath);

		private:
			
			std::vector<std::string> m_PathComponents;

			friend std::ostream& operator<<(std::ostream& os, const Path& dt);
		};

		std::ostream& operator<<(std::ostream& os, const Path& dt);
	
}

#endif