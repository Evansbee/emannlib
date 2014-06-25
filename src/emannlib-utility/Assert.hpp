#ifndef __assert_h__
#define __assert_h__

#include <functional>
#include <string>

namespace goldenduck
{
	class Assert
	{
	public:
		static void SetAssertionOutput();
		static void Assertion(bool predicate, const std::string& predicate_string, const std::string& filename, int linenumber);
	private:

		static std::function<void(const std::string&)> ms_AssertionOutputFunction;
		Assert(){};
	};
}

#define GD_ASSERT(x) goldenduck::Assert::Assertion(x, #x, __FILE__, __LINE__)

#endif