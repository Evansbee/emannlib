#include "Assert.hpp"


#include <string>
#include <sstream>
#include <iostream>

namespace emannlib
{
	void defaultOutput(const std::string& output);


	std::function<void(const std::string&)> Assert::ms_AssertionOutputFunction = defaultOutput;

	

	void Assert::Assertion(bool predicate, const std::string& predicate_string, const std::string& filename, int linenumber)
	{
		if (predicate)
		{
			return;
		}

		
		std::stringstream outputString;
		//do work
		outputString << "AssertionFail: " << predicate_string << " @ " << filename << "(" << linenumber << ")";
		ms_AssertionOutputFunction(outputString.str());
		exit(-1);
	}

	void defaultOutput(const std::string& output)
	{
		std::cerr << output;
	}
}