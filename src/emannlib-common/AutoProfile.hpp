//
//  AutoProfile.hpp
//  emannlibLib
//
//  Created by Evan Ackmann on 5/9/14.
//
//

#ifndef emannlibLib_AutoProfile_hpp
#define emannlibLib_AutoProfile_hpp

#include <vector>
#include <string>
#include <inttypes.h>

namespace emannlib {



	class ProfileNode
	{
#ifdef _DEBUG
	public:

		ProfileNode();

		ProfileNode(const std::string& name, bool forceStart = true);


		ProfileNode(const std::string& name, ProfileNode * parent);

		void SortChildren();

		uint32_t GetNodeDepth() const;

		void SetNodeDepth(uint32_t depth);
		void AddTime(double newTime);

		const std::string& GetName() const;
		double GetTotalTime() const;
		double GetMaxTime() const;
		uint64_t GetNumberOfSamples() const;
		
		double GetAverageRunTime() const;

		bool HasChild(const std::string& name) const;

		uint32_t GetNumberOfChildren() const;

		ProfileNode * GetChildNode(uint32_t childNumber) const;

		ProfileNode * GetChildByName(const std::string& name) const;

		ProfileNode * CreateAndAddChildNode(const std::string& name);

		ProfileNode * GetParent() const;

		void SetCurrentStartTime(double startTime);

		void SetCurrentlyActive();
		void ClearCurrentlyActive();
	private:
		std::vector<ProfileNode *> m_ChildNodes;
		ProfileNode * m_ParentNode;
		std::string m_Name;
		double m_TotalNodeTime;
		double m_MaxNodeTime;
		uint64_t m_NumberOfSamples;

		uint32_t m_NodeDepth;

		double m_CurrentStartTime;
		bool m_CurrentlyActive;
#endif
	};


	class AutoProfile
	{
	public:
		AutoProfile(const std::string& name);

		~AutoProfile();

		static std::string Report(uint32_t nameSectionWidth);
		

	private:
#ifdef _DEBUG
		double m_StartTime;

		static ProfileNode * ms_RootProfileNode;
		static ProfileNode * ms_CurrentProfileNode;
#endif
	};
}

#ifdef _DEBUG
#define AUTO_PROFILE(x) emannlib::AutoProfile autoprofilehelper( x )
#else
#define AUTO_PROFILE(x) 
#endif

#endif
