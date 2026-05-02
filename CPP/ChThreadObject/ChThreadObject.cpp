#include"../../BaseIncluder/ChBase.h"

#include"ChThreadObject.h"
#include"ChThreadObjectManager.h"

using namespace ChCpp;


void ThreadObject::Destroy()
{
	destroyFlg = true;
}

bool ThreadObject::IsDestroy()
{
	return destroyFlg;
}

void ThreadObjectList::Init()
{
	Release();

	endFlg = false;
	thread.Init([&]() {

		while (!endFlg)
		{
			for (size_t i = 0; i < addObjects.size(); i++)
			{
				addObjects[i]->Init();
				objects.push_back(addObjects[i]);
			}

			addObjects.clear();

			for (size_t i = 0; i < objects.size(); i)
			{
				for (size_t j = 0; j < removeObjects.size(); j++)
				{
					if (objects[i].get() == removeObjects[j].get())
						objects[i]->Destroy();
				}

				if (objects[i]->IsDestroy())
				{
					objects[i]->Release();
					objects.erase(objects.begin() + i);
					continue;
				}
				objects[i]->Update();
				i++;
			}
			removeObjects.clear();
		}

	});
}

void ThreadObjectList::Release()
{
	endFlg = true;
	thread.Release();

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Release();
	}
	objects.clear();
}
