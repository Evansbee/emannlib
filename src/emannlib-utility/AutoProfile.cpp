//
//  AutoProfile.cpp
//  goldenduckLib
//
//  Created by Evan Ackmann on 5/10/14.
//
//

#include "AutoProfile.hpp"
#include "Time.hpp"


#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>


namespace goldenduck
{
#ifdef _DEBUG
	ProfileNode * AutoProfile::ms_RootProfileNode = new ProfileNode("Application", true);
	ProfileNode * AutoProfile::ms_CurrentProfileNode = ms_RootProfileNode;
#endif

	
	ProfileNode::ProfileNode(){}

	ProfileNode::ProfileNode(const std::string& name, bool forceStart) :
		m_Name(name),
		m_ChildNodes(),
		m_ParentNode(NULL),
		m_TotalNodeTime(0),
		m_MaxNodeTime(0),
		m_NumberOfSamples(0),
		m_NodeDepth(0)
	{
		if (forceStart)
		{
			m_CurrentlyActive = true;
			m_CurrentStartTime = Time::GetCurrentTime();
		}
	}


	ProfileNode::ProfileNode(const std::string& name, ProfileNode * parent) :
		m_Name(name),
		m_ChildNodes(),
		m_ParentNode(parent),
		m_TotalNodeTime(0),
		m_MaxNodeTime(0),
		m_NumberOfSamples(0),
		m_NodeDepth(parent->GetNodeDepth() + 1)
	{

	}

	void ProfileNode::SortChildren()
	{
		std::sort(m_ChildNodes.begin(), m_ChildNodes.end(), [](ProfileNode *a, ProfileNode *b){return a->GetAverageRunTime() > b->GetAverageRunTime(); });
	}

	uint32_t ProfileNode::GetNodeDepth() const
	{
		return m_NodeDepth;
	}

	void ProfileNode::SetNodeDepth(uint32_t depth)
	{
		m_NodeDepth = depth;
	}
	void ProfileNode::AddTime(double newTime)
	{
		m_TotalNodeTime += newTime;
		if (newTime > m_MaxNodeTime)
		{
			m_MaxNodeTime = newTime;
		}
		m_NumberOfSamples++;
	}

	const std::string& ProfileNode::GetName() const { return m_Name; }
	double ProfileNode::GetTotalTime() const {
		if (m_NumberOfSamples > 0)
		{
			return m_TotalNodeTime;;
		}
		else
		{
			return Time::GetCurrentTime() - m_CurrentStartTime;
		}
	}
	double ProfileNode::GetMaxTime() const {
		if (m_NumberOfSamples > 0)
		{
			return m_MaxNodeTime;
		}
		else
		{
			return Time::GetCurrentTime() - m_CurrentStartTime;
		}

	}
	uint64_t ProfileNode::GetNumberOfSamples() const
	{
		return m_NumberOfSamples;
	}

	double ProfileNode::GetAverageRunTime() const
	{
		if (m_NumberOfSamples > 0)
		{
			return m_TotalNodeTime / (double) m_NumberOfSamples;
		}
		else
		{
			return Time::GetCurrentTime() - m_CurrentStartTime;
		}
	}

	bool ProfileNode::HasChild(const std::string& name) const
	{
		for (auto it : m_ChildNodes)
		{
			if ((*it).m_Name == name)
			{
				return true;
			}
		}
		return false;
	}

	uint32_t ProfileNode::GetNumberOfChildren() const
	{
		return m_ChildNodes.size();
	}

	ProfileNode * ProfileNode::GetChildNode(uint32_t childNumber) const
	{
		return m_ChildNodes[childNumber];
	}

	ProfileNode * ProfileNode::GetChildByName(const std::string& name) const
	{
		for (auto it : m_ChildNodes)
		{
			if ((*it).m_Name == name)
			{
				return it;
			}
		}
		return NULL;
	}

	ProfileNode * ProfileNode::CreateAndAddChildNode(const std::string& name)
	{
		ProfileNode * newChild = new ProfileNode(name, this);
		m_ChildNodes.push_back(newChild);
		return newChild;
	}

	ProfileNode * ProfileNode::GetParent() const
	{
		return m_ParentNode;
	}

	void ProfileNode::SetCurrentStartTime(double startTime)
	{
		m_CurrentStartTime = startTime;
	}

	void ProfileNode::SetCurrentlyActive() { m_CurrentlyActive = true; }
	void ProfileNode::ClearCurrentlyActive() { m_CurrentlyActive = false; }


	AutoProfile::AutoProfile(const std::string& name)
	{
#ifdef _DEBUG
		ProfileNode *currentNode = ms_CurrentProfileNode;
		if ((currentNode = ms_CurrentProfileNode->GetChildByName(name)) == NULL)
		{
			ms_CurrentProfileNode = ms_CurrentProfileNode->CreateAndAddChildNode(name);
		}
		else
		{
			ms_CurrentProfileNode = currentNode;
		}

		m_StartTime = Time::GetCurrentTime();

		ms_CurrentProfileNode->SetCurrentStartTime(m_StartTime);
		ms_CurrentProfileNode->SetCurrentlyActive();
#endif
	}

	AutoProfile::~AutoProfile()
	{
#ifdef _DEBUG
		ms_CurrentProfileNode->AddTime(Time::GetCurrentTime() - m_StartTime);
		ms_CurrentProfileNode->ClearCurrentlyActive();
		ms_CurrentProfileNode = ms_CurrentProfileNode->GetParent();
#endif
	}

	std::string AutoProfile::Report(uint32_t maxNameSectionWidth)
	{
#ifdef _DEBUG
		std::stringstream responseString;

		const int indentAmount = 3;
		uint32_t maxStringWidth = 0;


		ProfileNode * current = ms_RootProfileNode;
		std::stack<ProfileNode *> parseStack;

		std::map<ProfileNode *, uint32_t> currentChildNumber;

		do
		{

			if (currentChildNumber.count(current) == 0)
			{
				currentChildNumber[current] = 0;

				uint32_t thisWidth = current->GetName().length() + current->GetNodeDepth() * indentAmount;
				if (thisWidth > maxStringWidth)
				{
					maxStringWidth = thisWidth;
				}
				current->SortChildren();
				parseStack.push(current);
			}

			if (currentChildNumber[current] < current->GetNumberOfChildren())
			{
				auto cn = currentChildNumber[current];
				currentChildNumber[current]++;
				current = current->GetChildNode(cn);
			}
			else // there are no children, pop it
			{
				parseStack.pop();
				if (parseStack.size() > 0)
				{
					current = parseStack.top();
				}
			}
		} while (parseStack.size() > 0);


		currentChildNumber.clear();

		int nameSectionWidth = int(maxStringWidth + 1);

		const int MAX_NAME_WIDTH = maxNameSectionWidth;

		if (nameSectionWidth > MAX_NAME_WIDTH)
		{
			nameSectionWidth = MAX_NAME_WIDTH;
		}

		//std::cout << "AUTO PROFILE INFORMATION" << std::endl;
		for (auto i = 0; i <= nameSectionWidth + 9 + 9 + 4; ++i)
		{
			std::cout << "=";
		}
		responseString << std::endl;
		responseString << std::setw(nameSectionWidth) << std::left << "Name" << std::setw(9) << "Avg(s)" << std::setw(9) << "Max(s)" << "%" << std::endl;

		for (auto i = 0; i <= nameSectionWidth + 9 + 9 + 4; ++i)
		{
			responseString << "-";
		}

		responseString << std::endl;
		do
		{
			if (currentChildNumber.count(current) == 0)
			{
				currentChildNumber[current] = 0;

				responseString << std::fixed << std::setprecision(5);
				responseString << std::setw(nameSectionWidth);

				std::string indentedName = "";
				for (uint32_t i = 0; i < current->GetNodeDepth(); ++i)
				{
					indentedName += "|--";

				}
				indentedName += current->GetName();

				double averageRunTime = current->GetAverageRunTime();
				double maxRunTime = current->GetMaxTime();
				double percentageOfParent = (current->GetParent() == NULL || current->GetParent()->GetTotalTime() == 0.0) ? (1.0) : (current->GetTotalTime() / current->GetParent()->GetTotalTime());

				responseString << std::left << indentedName.substr(0, MAX_NAME_WIDTH - 1) <<
					std::setw(9) << averageRunTime <<
					std::setw(9) << maxRunTime <<
					std::setprecision(2) << 100.0*percentageOfParent << std::endl;

				parseStack.push(current);
				
			}


			if (currentChildNumber[current] < current->GetNumberOfChildren())
			{
				auto cn = currentChildNumber[current];
				currentChildNumber[current]++;
				current = current->GetChildNode(cn);

			}
			else // there are no children, pop it
			{
				
				parseStack.pop();
				if (parseStack.size() > 0)
				{
					current = parseStack.top();
				}
			}
		} while (parseStack.size() > 0);

		return responseString.str();
#endif
	}

}