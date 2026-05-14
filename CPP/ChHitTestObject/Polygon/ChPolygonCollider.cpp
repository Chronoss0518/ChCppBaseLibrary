
#include"../../ChBaseObject/ChBaseObject.h"
#include"../../ChModel/ChModelObject.h"

#include"../ChHitTestRay.h"
#include"ChPolygonCollider.h"
#include"../Sphere/ChSphereCollider.h"
#include"../Box/ChBoxCollider.h"

#define SET_INIT_MAX_VALUE(_value) _value = -ChMath::GetMaxFloat()
#define SET_INIT_MIN_VALUE(_value) _value = ChMath::GetMaxFloat()

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitRayToMesh(TransformObject<CharaType>& _object, float& _outLen, const ChVec3& _rayPos, const ChVec3& _rayDir)
{
	bool hitFlg = IsHitTestRay(_outLen, _object, _rayPos, _rayDir);

	for (auto&& child : _object.GetChildlen<TransformObject<CharaType>>())
	{
		hitFlg = IsHitRayToMesh(*child.lock(), _outLen, _rayPos, _rayDir) || hitFlg;
	}

	return hitFlg;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitTestRay(float& _outLen, TransformObject<CharaType>& _object, const ChVec3& _rayPos, const ChVec3& _rayDir)
{
	_object.UpdateDrawTransform();

	ChPtr::Shared<FrameComponent<CharaType>>&& frameCom = GetFrameComponent(_object);

	if (frameCom == nullptr)return false;

	if (frameCom->vertexList.size() < 3)return false;

	ChLMat tmpMat = _object.GetDrawLHandMatrix() * GetMat();

	bool hitFlg = false;

	std::vector<ChPtr::Shared<ChVec3>>posList;

	for (unsigned long i = 0; i < frameCom->vertexList.size(); i++)
		posList.push_back(ChPtr::Make_S<ChVec3>(tmpMat.Transform(frameCom->vertexList[i]->pos)));

	float tmpLen = 0.0f;
	ChVec3 poss[3];
	ChVec3 tmpVec;
	for (ChPtr::Shared<Ch3D::Primitive>& primitive : frameCom->primitives)
	{
		if (primitive->vertexData.size() <= 2)continue;

		poss[0] = *posList[primitive->vertexData[0]->vertexNo];
		for (size_t i = 1; i < primitive->vertexData.size() - 1; i++)
		{
			for (unsigned char j = 1; j < 3; j++)
			{
				poss[j] = *posList[primitive->vertexData[handType == UseHandType::RightHand ? primitive->vertexData.size() - j - i : i + j - 1]->vertexNo];
			}

			if (!HitTestTri(
				tmpLen,
				tmpVec,
				_rayPos,
				_rayDir,
				poss[0],
				poss[1],
				poss[2]))continue;

			if (handType != UseHandType::None && tmpLen < 0.0f)continue;
			tmpLen = std::abs(tmpLen);
			if (tmpLen > _outLen)continue;
			hitFlg = true;
			if (_outLen < tmpLen)continue;
			_outLen = tmpLen;
			hitMaterialName = frameCom->materialList[primitive->mateNo]->mateName;
			SetHitVector(tmpVec);
		}
	}
	return hitFlg;

}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitSphereToMesh(TransformObject<CharaType>& _object, ChVec3& _nearNormal, const ChVec3& _spherePos, float _sphereSize)
{
	bool res = IsHitTestSphere(_object, _nearNormal, _spherePos, _sphereSize);

	for (auto&& child : _object.GetChildlen<ChCpp::TransformObject<CharaType>>())
	{
		if (child.expired())continue;
		auto childObject = child.lock();
		res = IsHitSphereToMesh(*childObject, _nearNormal, _spherePos, _sphereSize) || res;
	}

	return res;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHitTestSphere(TransformObject<CharaType>& _object, ChVec3& _nearNormal, const ChVec3& spherePos, float _sphereSize)
{
	_object.UpdateDrawTransform();

	ChPtr::Shared<FrameComponent<CharaType>>&& frameCom = GetFrameComponent(_object);
	if (frameCom == nullptr)return false;

	if (frameCom->vertexList.size() < 3)return false;

	ChLMat tmpMat = _object.GetDrawLHandMatrix() * GetMat();

	bool hitFlg = false;

	std::vector<ChPtr::Shared<ChVec3>>posList;

	for (size_t i = 0; i < frameCom->vertexList.size(); i++)
		posList.push_back(ChPtr::Make_S<ChVec3>(tmpMat.Transform(frameCom->vertexList[i]->pos)));
	
	ChVec3 testPoint[3];

	float nearVectorLen = GetHitVector().GetLen();
	float testLen = 0.0f;
	ChVec3 testVector = ChVec3();
	ChVec3 normal = ChVec3(0.0f, 1.0f, 0.0f);

	for (ChPtr::Shared<Ch3D::Primitive>& primitive : frameCom->primitives)
	{
		if (primitive->vertexData.size() <= 2)continue;
		testPoint[0] = *posList[primitive->vertexData[0]->vertexNo];
		
		for (size_t i = 0; i < primitive->vertexData.size() - 2; i++)
		{
			for (unsigned char j = 1; j < 3; j++)
			{
				testPoint[j] = *posList[primitive->vertexData[j + i]->vertexNo];
			}

			if(!GetTriNearPoint(testVector, normal, spherePos, testPoint[0], testPoint[1], testPoint[2], _sphereSize))continue;

			max.x = max.x > testVector.x ? max.x : testVector.x;
			max.y = max.y > testVector.y ? max.y : testVector.y;
			max.z = max.z > testVector.z ? max.z : testVector.z;

			min.x = min.x < testVector.x ? min.x : testVector.x;
			min.y = min.y < testVector.y ? min.y : testVector.y;
			min.z = min.z < testVector.z ? min.z : testVector.z;
			
			testLen = testVector.GetLen();

			if (nearVectorLen < testLen)continue;

			hitFlg = true;
			nearVectorLen = testLen;
			SetHitVector(testVector * -1.0f);
			_nearNormal = normal;
			hitMaterialName = frameCom->materialList[primitive->mateNo]->mateName;
		}

	}


	return hitFlg;
}

template<typename CharaType>
void ChCpp::PolygonCollider<CharaType>::SetModel(FrameObject<CharaType>& _model)
{
	model = &_model;
}

template<typename CharaType>
ChCpp::FrameObject<CharaType>* ChCpp::PolygonCollider<CharaType>::GetModel()const
{
	return model;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestBox* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestBox* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestSphere* _target)
{
	if (_target == nullptr)return false;
	if (ChPtr::NullCheck(model))return false;

	SetHitVector(ChVec3(_target->GetSize()));

	//_target->GetPos();

	SET_INIT_MAX_VALUE(max.x);
	SET_INIT_MAX_VALUE(max.y);
	SET_INIT_MAX_VALUE(max.z);

	SET_INIT_MIN_VALUE(min.x);
	SET_INIT_MIN_VALUE(min.y);
	SET_INIT_MIN_VALUE(min.z);

	ChVec3 normal;

	bool res = IsHitSphereToMesh(*model, normal, _target->GetPos(), _target->GetSize());

	if (res)
	{
		ChVec3 tmp = GetHitVector();

		float tmpLen = tmp.GetLen();

		if (tmpLen <= 0.0f)
		{
			normal.Normalize();
			tmp = normal * _target->GetSize();
			SetHitVector(tmp);
		}
		else
		{
			tmpLen = _target->GetSize() - tmpLen;

			tmp.Normalize();
			tmp *= tmpLen;
			SetHitVector(tmp);
		}

		_target->SetHitVector(tmp * -1.0f);
	}

	return res;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

template<typename CharaType>
bool ChCpp::PolygonCollider<CharaType>::IsHit(HitTestRay* _target)
{
	if (ChPtr::NullCheck(_target))return false;
	if (ChPtr::NullCheck(model))return false;

	float maxLen = _target->GetMaxLen();
	ChVec3 pos = _target->GetPos();
	ChVec3 ray = _target->GetRayDir();

	bool hitFlg = IsHitRayToMesh(*model, maxLen, pos, ray);

	if (hitFlg)
		_target->SetHitVector(GetHitVector() * -1.0f);

	return hitFlg;
}

CH_STRING_TYPE_USE_FILE_EXPLICIT_DECLARATION(ChCpp::PolygonCollider);
