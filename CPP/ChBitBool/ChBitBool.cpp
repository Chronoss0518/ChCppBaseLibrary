#include"ChBitBool.h"

using namespace ChCpp;

#define GET_ARGS(arg) arg / 8
#define GET_MASK(arg) (1 << (arg % 8))
#define MAX_UCHAR (unsigned char)0xff

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

ChCpp::BitBool::BitBool()
{
	flgs.resize(1);
}

ChCpp::BitBool::BitBool(const unsigned char _size)
{
	flgs.resize(_size);
}

void ChCpp::BitBool::SetAllDownFlg()
{
	for (size_t i = 0; i < flgs.size(); i++)
	{
		flgs[i] = 0;
	}
}

void ChCpp::BitBool::SetSize(const unsigned char _byteCount)
{
	if (_byteCount <= 0)return;
	flgs.resize(_byteCount);
}

void BitBool::SetBitFlg(const unsigned long _argsNum, const bool _flg)
{
	_flg ?
		SetBitTrue(_argsNum) :
		SetBitFalse(_argsNum);
}

void BitBool::SetBitTrue(const unsigned long _argsNum)
{
	if (_argsNum >= GetSize())return;

	flgs[GET_ARGS(_argsNum)] = flgs[GET_ARGS(_argsNum)] | GET_MASK(_argsNum);
}

void BitBool::SetBitFalse(const unsigned long _argsNum)
{
	if (_argsNum >= GetSize())return;

	flgs[GET_ARGS(_argsNum)] = flgs[GET_ARGS(_argsNum)] & (MAX_UCHAR - GET_MASK(_argsNum));
}

void BitBool::SetValue(const unsigned char _value, const unsigned char _byteCount)
{
	if (_byteCount >= GetSize())return;

	flgs[_byteCount] = _value;
}

unsigned long  ChCpp::BitBool::GetSize()const
{
	return static_cast<unsigned long>(flgs.size() * 8);
}

bool BitBool::GetBitFlg(const unsigned long _argsNum)const
{
	if (_argsNum >= GetSize())return false;

	return flgs[GET_ARGS(_argsNum)] & GET_MASK(_argsNum);
}

unsigned char ChCpp::BitBool::GetValue(const unsigned char _byteCount)const
{
	if (flgs.size() < _byteCount)return 0;
	return flgs[_byteCount];
}
