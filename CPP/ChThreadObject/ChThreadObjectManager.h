#ifndef Ch_CPP_MThreadObject_h
#define Ch_CPP_MThreadObject_h

#include"ChThreadObject.h"

namespace ChCpp
{
	class ThreadObjectManager final
	{
	private:

		~ThreadObjectManager() { mgr.Release(); }

	public:

		inline void Init() { mgr.Init(); }

		inline void Release() { mgr.Release(); }

	public:

		inline void AddObject(ChPtr::Shared<ThreadObject> _object) { mgr.AddObject(_object); }

		inline void RemoveObject(ChPtr::Shared<ThreadObject> _object) { mgr.RemoveObject(_object); }

	private:

		ThreadObjectList mgr;

	public:

		static ThreadObjectManager& GetIns()
		{
			static ThreadObjectManager ins;
			return ins;
		}
	};

	inline ThreadObjectManager& ThreadObjectMgr() { return ThreadObjectManager::GetIns(); }

}

#endif