#include"ChCollider.h"

using namespace ChCpp;

///////////////////////////////////////////////////////////////////////////////////////
//HitTestObject Method
///////////////////////////////////////////////////////////////////////////////////////

float ChCpp::Collider::CreateDat(const ChVec3& _vec1, const ChVec3& _vec2, const ChVec3& _vec3)
{
	ChMath::BaseMatrix3x3<float> mat;

	ChVec3 tmp[3] = { _vec1,_vec2,_vec3 };

	for (unsigned char i = 0; i < mat.m.GetColumn(); i++)
	{
		for (unsigned char j = 0; j < mat.m.GetRow(); j++)
		{
			mat.m[i][j] = tmp[j].val[i];
		}
	}
	return mat.m.GetDeterminant();
}

bool ChCpp::Collider::HitTestTri(
	float& _len,
	ChVec3& _thisHitVectol,
	const ChVec3& _pos,
	const ChVec3& _dir,
	const ChVec3& _vec1,
	const ChVec3& _vec2,
	const ChVec3& _vec3)
{
	//https://shikousakugo.wordpress.com/2012/06/27/ray-intersection-2/
	//ƒNƒ‰ƒƒ‹‚ÌŒöŽ®//

	//eg1 = (v1 - v0), eg2 = (v2 - v0);
	//hitPos = spos + (dir * len)
	//hitPos = (eg1 * u) + (eg2 * v) + v0
	//spos + (dir * len) = (eg1 * u) + (eg2 * v) + v0
	//spos - v0 = (eg1 * u) + (eg2 * v) - (dir * len)

	//spos1 - v01 = eg11 * u + eg21 * v - dir1 * len
	//spos2 - v02 = eg12 * u + eg22 * v - dir2 * len
	//spos3 - v03 = eg13 * u + eg23 * v - dir3 * len
	//spos - v0 = v2sp

	//u = dat(v2sp,eg2,-dir)/dat(eg1.eg2.-dir)
	//v = dat(eg1,v2sp,-dir)/dat(eg1.eg2.-dir)
	//len = dat(eg1,eg2,v2sp)/dat(eg1.eg2.-dir)

	_thisHitVectol = 0.0f;

	float u = 0.0f, v = 0.0f;
	_len = 0.0f;

	ChVec3 eg1 = _vec2 - _vec1, eg2 = _vec3 - _vec1, v2sp = _pos - _vec1;

	ChVec3 mdir = _dir * -1;
	float divDat = 0.0f;

	divDat = CreateDat(eg1, eg2, mdir);

	if (divDat <= 0.0f)return false;

	u = CreateDat(v2sp, eg2, mdir);

	u = u / divDat;

	if (u < 0.0f || u > 1.0f)return false;

	v = CreateDat(eg1, v2sp, mdir);
	v = v / divDat;

	if (v < 0.0f || v > 1.0f)return false;

	float tmpVal = u + v;

	if (tmpVal < 0.0f || tmpVal > 1.0f)return false;

	_len = CreateDat(eg1, eg2, v2sp);
	_len = _len / divDat;

	_thisHitVectol = _dir * std::abs(_len);

	return true;
}

bool ChCpp::Collider::GetTriNearPoint(ChVec3& _hitVector, ChVec3& _normal, const ChVec3& _point, const ChVec3& _pos1, const ChVec3& _pos2, const ChVec3& _pos3, float _maxLen)
{
	_hitVector = 0.0f;

	ChVec3 centerPos = _pos1 + _pos2 + _pos3;
	centerPos /= 3.0f;
	ChVec3 testVec = 0.0f;

	ChVec3 uEdge = _pos2 - _pos1, vEdge = _pos3 - _pos1, v2sp = _point - _pos1;

	//Pos1 Near Test//
	float d1 = 0.0f, d2 = 0.0f;

	d1 = ChVec3::GetDot(uEdge, v2sp);//uEdge//
	d2 = ChVec3::GetDot(vEdge, v2sp);//vEdge//

	if (d1 <= 0.0f && d2 <= 0.0f)
	{
		testVec = v2sp;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = _pos1 - centerPos;
		_normal.Normalize();

		return true;
	}

	//Pos2 Near Test//
	float d3 = 0.0f, d4 = 0.0f;

	d3 = ChVec3::GetDot(uEdge, _point - _pos2);
	d4 = ChVec3::GetDot(vEdge, _point - _pos2);

	if (d3 >= 0.0f && d4 <= d3)
	{
		testVec = _point - _pos2;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = _pos1 - centerPos;
		_normal.Normalize();

		return true;
	}
	
	//Pos3 Near Test//
	float d5 = 0.0f, d6 = 0.0f;
	d5 = ChVec3::GetDot(uEdge, _point - _pos3);
	d6 = ChVec3::GetDot(vEdge, _point - _pos3);

	if (d6 >= 0.0f && d5 <= d6)
	{
		testVec = _point - _pos3;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = _pos1 - centerPos;
		_normal.Normalize();

		return true;
	}

	//Line1To2 Near Test//
	float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float w = d1 / (d1 - d3);
		testVec = _pos1 + uEdge * w;
		testVec = _point - testVec;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = ChVec3::GetCross(centerPos - _pos1, uEdge);
		_normal = ChVec3::GetCross(_normal, uEdge);
		_normal.Normalize();

		return true;
	}

	//Line1To3 Near Test//
	float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		testVec = _pos1 + vEdge * w;
		testVec = _point - testVec;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = ChVec3::GetCross(centerPos - _pos1, vEdge);
		_normal = ChVec3::GetCross(_normal, vEdge);
		_normal.Normalize();

		return true;
	}

	//Line2To3 Near Test//
	float va = d3 * d6 - d5 * d4;
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		testVec = _pos2 + (_pos3 - _pos2) * w;
		testVec = _point - testVec;
		if (testVec.GetLen() > _maxLen)return false;

		_hitVector = testVec;
		_normal = ChVec3::GetCross(centerPos - _pos1, _pos3 - _pos2);
		_normal = ChVec3::GetCross(_normal, _pos3 - _pos2);
		_normal.Normalize();

		return true;
	}


	float denom = 1.0f / (va + vb + vc);
	float v = vb * denom, w = vc * denom;
	testVec = _pos1 + uEdge * v + vEdge * w;
	testVec = _point - testVec;
	if (testVec.GetLen() > _maxLen)return false;
	_hitVector = testVec;
	_normal = ChVec3::GetCross(uEdge, vEdge);
	_normal.Normalize();

	return true;
}