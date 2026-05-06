#ifndef Ch_CPP_Collider_h
#define Ch_CPP_Collider_h

#include<vector>

#include"ChHitTestObject.h"

namespace ChCpp
{
	class HitTestRay;
	class BoxCollider;
	class SphereCollider;

	using HitTestSphere = SphereCollider;
	using HitTestBox = BoxCollider;

	//対象のHitTestObjectから衝突したかを判断するクラス//
	class Collider :public HitTestObject
	{
	public://Is Functions//

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestBox* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestSphere* _target) = 0;

		//対象のオブジェクトの外から衝突しているかの判定//
		virtual bool IsHit(HitTestRay* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestBox* _target) = 0;

		//対象のオブジェクト内から衝突しているかの判定//
		virtual bool IsInnerHit(HitTestSphere* _target) = 0;

	public:

		bool GetTriNearPoint(ChVec3& _hitVector, ChVec3& _normal, const ChVec3& _point, const ChVec3& _pos1, const ChVec3& _pos2, const ChVec3& _pos3);

		bool HitTestTri(float& _len, ChVec3& _thisHitVectol, const ChVec3& _pos, const ChVec3& _dir, const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

	private:

		float CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3);

		ChVec3 GetLineNearPoint(const ChVec3& _point, const ChVec3& _pos1, const ChVec3& _pos2);

	};
}


#endif