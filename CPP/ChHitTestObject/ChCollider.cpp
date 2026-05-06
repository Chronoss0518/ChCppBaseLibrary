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
	//ÉNÉâÉÅÉãÇÃåˆéÆ//

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

bool ChCpp::Collider::GetTriNearPoint(ChVec3& _hitVector, ChVec3& _normal, const ChVec3& _point, const ChVec3& _pos1, const ChVec3& _pos2, const ChVec3& _pos3)
{
	//https://shikousakugo.wordpress.com/2012/06/27/ray-intersection-2/
	//ÉNÉâÉÅÉãÇÃåˆéÆ//

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

	_hitVector = 0.0f;

	float u = 0.0f, v = 0.0f;
	float len = 0.0f;

	ChVec3 uEdge = _pos2 - _pos1, vEdge = _pos3 - _pos1, v2sp = _point - _pos1;

	auto dir = ChVec3::GetCross(uEdge, vEdge);
	_normal = dir;

	float divDat = 0.0f;

	divDat = CreateDat(uEdge, vEdge, dir);

	if (divDat <= 0.0f)return false;

	u = CreateDat(v2sp, vEdge, dir);
	u = u / divDat;

	v = CreateDat(uEdge, v2sp, dir);
	v = v / divDat;

	if ((u >= 0.0f && u <= 1.0f) && (v >= 0.0f && v < 1.0f) && u + v <= 1.0f)
	{
		len = CreateDat(uEdge, vEdge, v2sp);
		len = len / divDat;

		_hitVector = dir * len;

		return true;
	}

	ChVec3 centerPos = _pos1 + _pos2 + _pos3;
	centerPos /= 3.0f;

	if (u <= 0.0f && v >= 1.0f)
	{
		_hitVector = _point - _pos3;
		_normal = _pos3 - centerPos;
		_normal.Normalize();

		return true;
	}

	if (u >= 1.0f && v <= 0.0f)
	{
		_hitVector = _point - _pos2;
		_normal = _pos2 - centerPos;
		_normal.Normalize();

		return true;
	}

	if (u <= 0.0f && v <= 0.0f)
	{
		_hitVector = _point - _pos1;
		_normal = _pos1 - centerPos;
		_normal.Normalize();

		return true;
	}

	if (v < 0.0f && u >= 0.0f && u <= 1.0f)
	{
		_hitVector = GetLineNearPoint(_point, _pos1, _pos2);

		_normal = ChVec3::GetCross(centerPos - _pos1, _pos2 - _pos1);
		_normal = ChVec3::GetCross(_normal, _pos2 - _pos1);
		_normal.Normalize();

		return true;
	}

	if (u < 0.0f && v >= 0.0f && v <= 1.0f)
	{
		_hitVector = GetLineNearPoint(_point, _pos1, _pos3);

		_normal = ChVec3::GetCross(centerPos - _pos1, _pos3 - _pos1);
		_normal = ChVec3::GetCross(_normal, _pos3 - _pos1);
		_normal.Normalize();

		return true;
	}

	_hitVector = GetLineNearPoint(_point, _pos2, _pos3);

	_normal = ChVec3::GetCross(centerPos - _pos2, _pos3 - _pos2);
	_normal = ChVec3::GetCross(_normal, _pos3 - _pos2);
	_normal.Normalize();

	return true;
}

ChVec3 ChCpp::Collider::GetLineNearPoint(const ChVec3& _point, const ChVec3& _pos1, const ChVec3& _pos2)
{
	ChVec3 line = _pos2 - _pos1;
	ChVec3 posToPoint = _point - _pos1;

	float dot = ChVec3::GetDot(line, posToPoint);

	float size = line.GetLen();

	float t = dot / (size * size);

	ChVec3 onPos = _pos1 + line * t;

	return _point - onPos;
}