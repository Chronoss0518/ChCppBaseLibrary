#ifndef Ch_CPP_HTM_h
#define Ch_CPP_HTM_h

#include<string>
#include<vector>

#include"../ChPanelColliderBase.h"

#include"../../../BasePack/ChStd.h"

#include"../../ChModel/ChModelObject.h"

namespace ChCpp
{
	template<typename CharaType>
	class FrameObject;

	template<typename CharaType>
	class PolygonCollider :public PanelColliderBase
	{
	public://SetFunction//

		void SetModel(FrameObject<CharaType>& _model);

	public://GetFunction//

		FrameObject<CharaType>* GetModel()const;

		std::basic_string<CharaType> GetHitMaterialName() { return hitMaterialName; }

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

		bool IsHitRayToMesh(TransformObject<CharaType>& _object, const ChVec3& _rayPos,const ChVec3& _rayDir,const float _rayLen,const bool _nowHitFlg = false);

		bool IsHitTest(float& _outLen, TransformObject<CharaType>& _object, const ChVec3& _rayPos, const ChVec3& _rayDir, const bool _nowHitFlg = false);

		ChPtr::Shared<FrameComponent<CharaType>> GetFrameComponent(TransformObject<CharaType>& _object)
		{
			auto&& frameCom = _object.GetComponent<FrameComponent<CharaType>>();
			return frameCom;
		}

	private:

		bool cullHitFlg = true;
		bool lHandWorldFlg = true;
		float minLen = 0.0f;

		std::basic_string<CharaType> hitMaterialName = ChStd::GetZeroChara<CharaType>();
		FrameObject<CharaType>* model = nullptr;
	};
}


#endif