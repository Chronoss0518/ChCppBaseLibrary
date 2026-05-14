#include"ChPanelCollider.h"

#include"../Box/ChBoxCollider.h"
#include"../ChHitTestRay.h"
#include"../Sphere/ChSphereCollider.h"

using namespace ChCpp;

bool PanelCollider::IsHit(HitTestBox* _target)
{
	return false;
}

bool PanelCollider::IsHit(HitTestSphere* _target)
{
	auto square = GetSquarePositions();

	ChVec3 pos = _target->GetPos();;

	ChVec3 nearVec = ChVec3(_target->GetSize());
	ChVec3 nearNormal = ChVec3(0.0f, 1.0f, 0.0f);
	
	ChVec3 tmpVec = ChVec3();
	ChVec3 normal = ChVec3();

	if (GetTriNearPoint(tmpVec, normal, pos, square.pos[0], square.pos[1], square.pos[2], _target->GetSize()))
	{
		nearVec = tmpVec;
		nearNormal = normal;
	}

	if (GetTriNearPoint(tmpVec, normal, pos, square.pos[0], square.pos[2], square.pos[3], _target->GetSize()))
	{
		if (nearVec.GetLen() > tmpVec.GetLen())
		{
			nearVec = tmpVec;
			nearNormal = normal;
		}
	}

	if (nearVec.GetLen() < _target->GetSize())
	{
		float len = nearVec.GetLen();
		if (len > 0.0f)
		{
			len = _target->GetSize() - len;
			nearVec.Normalize();

			_target->SetHitVector(nearVec * len);
			SetHitVector(nearVec * -len);
		}
		else
		{
			_target->SetHitVector(nearNormal * -_target->GetSize());
			SetHitVector(nearNormal * _target->GetSize());
		}

		return true;
	}


	return false;
}

bool PanelCollider::IsHit(HitTestRay* _target)
{
	auto square = GetSquarePositions();

	float maxLen = _target->GetMaxLen();

	unsigned long numbers[4]{ 0,1,2,3 };

	if (handType == UseHandType::RightHand)
	{
		numbers[0] = 3;
		numbers[1] = 2;
		numbers[2] = 1;
		numbers[3] = 0;
	}

	ChVec3 pos = _target->GetPos();;
	ChVec3 ray = _target->GetRayDir();

	ChVec3 tmpVec;

	float tmpLen = 0.0f;
	bool hitFlg = HitTestTri(tmpLen,tmpVec, pos ,ray, square.pos[numbers[0]], square.pos[numbers[1]], square.pos[numbers[2]]);

	if (handType != UseHandType::None && tmpLen < 0.0f)hitFlg = false;

	if (tmpVec.GetLen() > maxLen)hitFlg = false;

	if (!hitFlg)hitFlg = HitTestTri(tmpLen, tmpVec, pos, ray, square.pos[numbers[0]], square.pos[numbers[2]], square.pos[numbers[3]]);

	if (handType != UseHandType::None && tmpLen < 0.0f)hitFlg = false;

	if (tmpVec.GetLen() > maxLen)hitFlg = false;

	if (hitFlg)
	{
		SetHitVector(tmpVec);
		_target->SetHitVector(tmpVec * -1.0f);
	}

	return hitFlg;
}

bool PanelCollider::IsInnerHit(HitTestBox* _target)
{
	return false;
}

bool PanelCollider::IsInnerHit(HitTestSphere* _target)
{
	return false;
}

PanelCollider::Square PanelCollider::GetSquarePositions()
{
	Square out;

	ChVec3 tmpPos[4] = {
		ChVec3(-size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,size.y / 2.0f,0.0f),
		ChVec3(size.x / 2.0f,-size.y / 2.0f,0.0f),
		ChVec3(-size.x / 2.0f,-size.y / 2.0f,0.0f) };

	{
		
		auto tmpMat = GetMat();

		for (unsigned char i = 0; i < 4; i++)
		{
			out.pos[i] = tmpMat.Transform(tmpPos[i]);
		}
	}

	return out;
}