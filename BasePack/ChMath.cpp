#include"ChMath.h"

#include <float.h>
#include <cmath>

#ifndef CH_MATH_FUNCTION
#define CH_MATH_FUNCTION(_Type,_FunctionName,_UseFunctionName)\
 _Type ChMath::_FunctionName (_Type _val) { return std::_UseFunctionName (_val); }
#endif

#ifndef CH_FMOD_USE_ARGUMENT
#define CH_FMOD_USE_ARGUMENT  _valx, _valy 
#endif

#ifndef CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION
#define CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(_AxisOrder,_ZeroTestAxis,_ZeroTestAxisFunction,_Axiz1,_ZeroAxiz1Function,_NotZeroAxiz1Function,_Axiz2,_ZeroAxiz2Function,_NotZeroAxiz2Function)\
template<typename T> ChMath::ChEular##_AxisOrder<T> ChMath::QuaternionBase<T>::GetEulerRotation##_AxisOrder(const unsigned long _digit)const\
{\
	ChEular##_AxisOrder<T> res;\
	res._ZeroTestAxis = ChMath::GetASin _ZeroTestAxisFunction;\
	T ww = w * w * static_cast<T>(2.0f);\
	if (CH_FLOAT_TEST(ChMath::GetCos(res._ZeroTestAxis), Ch_FLOAT_TEST_VALUE)){\
		res._Axiz1 = _ZeroAxiz1Function;\
		res._Axiz2 =_ZeroAxiz2Function;\
	}else{\
		res._Axiz1 = _NotZeroAxiz1Function;\
		res._Axiz2 = _NotZeroAxiz2Function;\
	}\
	return res;\
}
#endif

#ifndef CH_FLOATING_TYPE_EXPLICIT_DECLARATION
#define CH_FLOATING_TYPE_EXPLICIT_DECLARATION(_Class)\
template class _Class<float>;\
template class _Class<double>;\
template class _Class<long double>;
#endif

float ChMath::Round(const float& _val, const unsigned long _digit)
{
	return static_cast<float>(Round(static_cast<double>(_val), _digit));
}

double ChMath::SqrtEx(const double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	double out = _base;

	unsigned long maxCount = _digit > 307 ? 307 : _digit;

	out = static_cast<double>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}

float ChMath::SqrtEx(const float& _base, const unsigned long _digit)
{
	if (_base == 0.0f)return 0.0f;

	float out = _base;

	unsigned long maxCount = _digit > 37 ? 37 : _digit;

	out = static_cast<float>(SqrtEx(static_cast<long double>(out), maxCount));

	return out;
}

double ChMath::Round(const double& _val, const unsigned long _digit)
{
	if (_val == 0.0)return 0.0;

	double out = _val * std::pow(10, static_cast<double>(_digit - 1));
	out = std::round(out);
	out = out * std::pow(0.1, static_cast<double>(_digit - 1));

	return out;
}

long double ChMath::SqrtEx(const long double& _base, const unsigned long _digit)
{
	if (_base == 0.0)return 0.0;

	long double out = std::sqrt(_base);
	//微分積分自分で使えるようになってから再度考える//
	return out;

	unsigned long maxCount = _digit > 4931 ? 4931 : _digit;

	//以下を参照//
	//https://qiita.com/rytaryu/items/e5d760a80f9ce5db860f
	//

	for (unsigned long i = 0; i < maxCount; i++)
	{
		out = ((out * out) + _base) / (2 * out);
	}

	return out;
}

CH_MATH_FUNCTION(float, GetSin, sin);
CH_MATH_FUNCTION(double, GetSin,  sin);
CH_MATH_FUNCTION(long double, GetSin,  sin);

CH_MATH_FUNCTION(float, GetASin, asin);
CH_MATH_FUNCTION(double, GetASin, asin);
CH_MATH_FUNCTION(long double, GetASin, asin);

CH_MATH_FUNCTION(float, GetCos, cos);
CH_MATH_FUNCTION(double, GetCos, cos);
CH_MATH_FUNCTION(long double, GetCos, cos);

CH_MATH_FUNCTION(float, GetACos, acos);
CH_MATH_FUNCTION(double, GetACos, acos);
CH_MATH_FUNCTION(long double, GetACos, acos);

CH_MATH_FUNCTION(float, GetATan, atan);
CH_MATH_FUNCTION(double, GetATan, atan);
CH_MATH_FUNCTION(long double, GetATan, atan);

float ChMath::GetATan2(float _val1, float _val2) { return std::atan2(_val1,_val2); }
double ChMath::GetATan2(double _val1, double _val2) { return std::atan2(_val1,_val2); }
long double ChMath::GetATan2(long double _val1, long double _val2) { return std::atan2(_val1,_val2); }

float ChMath::GetFMod(float _val1, float _val2) { return std::fmod(_val1, _val2); }
double ChMath::GetFMod(double _val1, double _val2) { return std::fmod(_val1, _val2); }
long double ChMath::GetFMod(long double _val1, long double _val2) { return std::fmod(_val1, _val2); }

float ChMath::GetMaxFloat()
{
	return FLT_MAX;
}

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	XYZ,
	y,
	(2.0f * x * z + 2.0f * y * w),
	x,
	ChMath::GetATan2((2.0f * y * z + 2.0f * x * w), (ww + 2.0f * y * y - 1.0f)),
	ChMath::GetATan2(-(2.0f * y * z - 2.0f * x * w), (ww + 2.0f * z * z - 1.0f)),
	z,
	0.0f,
	ChMath::GetATan2(-(2.0f * x * y - 2.0f * z * w), (ww + 2.0f * x * x - 1.0f)));

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	XZY,
	z,
	(-(2.0f * x * y - 2.0f * z * w)),
	x,
	ChMath::GetATan2(-(2.0f * y * z - 2.0f * x * w), (ww + 2.0f * z * z - 1.0f)),
	ChMath::GetATan2((2.0f * y * z + 2.0f * x * w), (ww + 2.0f * y * y - 1.0f)),
	y,
	0.0f,
	ChMath::GetATan2((2.0f * x * z + 2.0f * y * w), (ww + 2.0f * x * x - 1.0f))
);

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	YXZ,
	x,
	(-(2.0f * y * z - 2.0f * x * w)),
	y,
	ChMath::GetATan2(-(2.0f * x * z - 2.0f * y * w), (ww + 2.0f * x * x - 1.0f)),
	ChMath::GetATan2((2.0f * x * z + 2.0f * y * w), (ww + 2.0f * z * z - 1.0f)),
	z,
	0.0f,
	ChMath::GetATan2((2.0f * x * y + 2.0f * z * w), (ww + 2.0f * y * y - 1.0f))
);

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	YZX,
	z,
	(2.0f * x * y + 2.0f * z * w),
	x,
	0.0f,
	ChMath::GetATan2(-(2.0f * y * z - 2.0f * x * w), (ww + 2.0f * y * y - 1.0f)),
	y,
	ChMath::GetATan2((2.0f * x * z + 2.0f * y * w), (ww + 2.0f * z * z - 1.0f)),
	ChMath::GetATan2(-(2.0f * x * z - 2.0f * y * w), (ww + 2.0f * x * x - 1.0f))
);

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	ZXY,
	x,
	((2.0f * y * z + 2.0f * x * w)),
	y,
	0.0f,
	ChMath::GetATan2(-(2.0f * x * y - 2.0f * z * w), (ww + 2.0f * y * y - 1.0f)),
	z,
	ChMath::GetATan2((2.0f * x * z + 2.0f * y * w), (ww + 2.0f * x * x - 1.0f)),
	ChMath::GetATan2(-(2.0f * x * z - 2.0f * y * w), (ww + 2.0f * z * z - 1.0f))
);

CH_MATH_METHOD_QUATERNION_GET_EULER_ROTATION(
	ZYX,
	y,
	(-(2.0f * x * z - 2.0f * y * w)),
	x,
	0.0f,
	ChMath::GetATan2((2.0f * y * z + 2.0f * x * w), (ww + 2.0f * z * z - 1.0f)),
	z,
	ChMath::GetATan2(-(2.0f * x * y - 2.0f * z * w), (ww + 2.0f * y * y - 1.0f)),
	ChMath::GetATan2((2.0f * x * y + 2.0f * z * w), (ww + 2.0f * x * x - 1.0f))
);

CH_FLOATING_TYPE_EXPLICIT_DECLARATION(ChMath::QuaternionBase);

