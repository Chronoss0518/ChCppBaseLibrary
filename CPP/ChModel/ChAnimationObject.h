
#ifndef Ch_CPP_AnimationObject_h
#define Ch_CPP_AnimationObject_h

#include<string>
#include<map>
#include<vector>

#include"../../BaseIncluder/ChBase.h"


namespace ChCpp
{
	template<typename CharaType>
	class FrameObject;

	template<typename CharaType>
	class AnimationObject : public ChCp::Initializer
	{
	public:

		struct AnimationParameter
		{
			ChVec3 pos;
			ChQua rot;
			ChVec3 scl;
		};

		struct AnimationFrameObject
		{
			ChPtr::Shared<FrameObject<CharaType>>targetObject = nullptr;
			std::vector<ChPtr::Shared<AnimationParameter>> animationParameterList;
		};

	public:

		void AddModel(const ChPtr::Shared<FrameObject<CharaType>>& _frameObject);

	private:

		typedef std::basic_string<CharaType> FrameNamePath;


		std::map<FrameNamePath, AnimationFrameObject>animations;

		float animationMoveParFrame = 0.1f;
	};
}

#endif