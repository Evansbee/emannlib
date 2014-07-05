#ifndef __singleton_h__
#define __singleton_h__

#include "Assert.hpp"



namespace emannlib
{
	template <typename T>
	class Singleton
	{
	private:
		static T* ms_Singleton;

	public:
		Singleton()
		{
			GD_ASSERT(ms_Singleton == NULL);
			long int offset = (long int) (T*) 1 - (long int) (Singleton <T>*)(T*) 1;
			ms_Singleton = (T*) ((long int)this + offset);
		}
		~Singleton()
		{
			GD_ASSERT(ms_Singleton != NULL);
			ms_Singleton = 0;
		}

		static T& GetSingleton()
		{
			GD_ASSERT(ms_Singleton != NULL);
			return *ms_Singleton;
		}

		static T* GetSingletonPtr()
		{
			GD_ASSERT(ms_Singleton != NULL);
			return ms_Singleton;
		}
	};
	template <typename T> T* Singleton<T>::ms_Singleton = NULL;
}

#endif