#ifndef Ch_CPP_HTO_h
#define Ch_CPP_HTO_h

#include"../../BasePack/ChMath3D.h"

namespace ChCpp
{
	class HitTestPositionClass
	{
	protected:

		HitTestPositionClass() {}

	public:

		inline void SetPosition(const ChVec3& _pos) { position = _pos; }

	public:

		inline ChVec3 GetPos() { return position; }

	private:

		ChVec3 position;
	};

	class HitTestMatrixClass
	{
	protected:

		HitTestMatrixClass(){}

	public:

		inline void SetPosition(const ChVec3& _pos) { mat.SetPosition(_pos); }
		
		inline void SetRotation(const ChQua& _rot) { mat.SetRotation(_rot); }
		
		inline void SetScalling(const ChVec3& _scl) { mat.SetScalling(_scl); }

		inline void SetMatrix(const ChLMat& _mat) { mat = _mat; }

	public:

		inline ChVec3 GetPos() { return mat.GetPosition(); }
		
		inline ChQua GetRot() { return mat.GetRotation(); }

		inline ChVec3 GetScl() { return mat.GetScalling(); }

		inline ChLMat GetMat() { return mat; }

	private:

		ChLMat mat;
	};

	//当たり判定を行う手法//
	class HitTestObject
	{

	public://Set Functions//

		inline void SetHitVector(const ChVec3& _vec) { hitVector = _vec; }

	public://Get Functions//

		//衝突していた場合に中心から見てどの位置までめり込んでいたかの数値//
		inline ChVec3 GetHitVector() { return hitVector; }

	private:

		//この数値文移動させれば衝突から免れる移動数値//
		ChVec3 hitVector = 0.0f;

	};

}

#endif