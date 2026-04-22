#ifndef Ch_CPP_HTP_h
#define Ch_CPP_HTP_h

#include"../ChPanelColliderBase.h"

namespace ChCpp
{
	//基本的に面は上向き//
	class PanelCollider :public PanelColliderBase
	{
	public:

		struct Square
		{
			ChVec3 pos[4];
		};

	public://Set Functions//

		inline void SetSize(const ChVec2& _size)
		{
			size = _size;
		}

	public://GetFunction//

		inline ChVec2 GetSize() { return size; }

		Square GetSquarePositions();
	
	public://IsFunction//

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestSphere* _target)override;

		//対象のオブジェクトがオブジェクト外から衝突しているかの判定//
		bool IsHit(HitTestRay* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestBox* _target)override;

		//対象のオブジェクトがオブジェクト内から衝突しているかの判定//
		bool IsInnerHit(HitTestSphere* _target)override;

	private:

		ChVec2 size;
	};

}

#endif