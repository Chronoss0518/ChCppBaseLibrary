#ifndef Ch_CPP_HTPBase_h
#define Ch_CPP_HTPBase_h

#include"ChCollider.h"

namespace ChCpp
{
	//Šî–{“I‚É–Ê‚ÍãŒü‚«//
	class PanelColliderBase :public Collider
	{
	public:

		enum class UseHandType
		{
			None,
			LeftHand,
			RightHand,
		};

	public:

		inline void SetHandType(UseHandType _type) { handType = _type; }

		inline void SetRightHandType() { handType = UseHandType::RightHand; }

		inline void SetLeftHandType() { handType = UseHandType::LeftHand; }

		inline void SetNoneHandType() { handType = UseHandType::None; }

	protected:

		UseHandType handType = UseHandType::None;
	};
}

#endif