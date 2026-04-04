#ifndef Ch_CPP_ThreadObject_h
#define Ch_CPP_ThreadObject_h

#include<vector>

#include"../ChMultiThread/ChMultiThread.h"

namespace ChCpp
{
	class ThreadObject
	{
	public:

		virtual void Init(){}

		virtual void Update() = 0;

		virtual void Release() {};

	public:

		void Destroy();

		bool IsDestroy();

	private:

		bool destroyFlg = false;

	};

	class ThreadObjectList final
	{
	public:

		~ThreadObjectList() { Release(); }

	public:

		void Init();

		void Release();

	public:

		void AddObject(ChPtr::Shared<ThreadObject> _object);

		void RemoveObject(ChPtr::Shared<ThreadObject> _object);

	private:

		MultiThread thread;
		bool endFlg = false;
		std::vector<ChPtr::Shared<ThreadObject>> objects;
		std::vector<ChPtr::Shared<ThreadObject>> addObjects;
		std::vector<ChPtr::Shared<ThreadObject>> removeObjects;
	};
}

#endif