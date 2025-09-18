

//#include"../ChTexture/ChBaseTexture.h"

#include"../ChBaseObject/ChBaseObject.h"
#include"ChModelObject.h"
#include"ChAnimationObject.h"

using namespace ChCpp;

template<typename CharaType>
void AnimationObject<CharaType>::AddModel(const ChPtr::Shared<FrameObject<CharaType>>& _frameObject)
{
	if (_frameObject == nullptr)return;
	auto&& animationPalam = animations.find(_frameObject->GetMyNamePath());
	if (animationPalam == animations.end())return;
	animationPalam.second->targetObject = _frameObject;
	auto&& childlen = _frameObject->GetChildlen<FrameObject<CharaType>>();

	for (auto&& child : childlen)
	{
		AddModel(child);
	}
}

