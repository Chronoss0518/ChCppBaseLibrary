#include"ChBitBool.h"

using namespace ChCpp;

#define GET_ARGS(arg) arg / 8
#define GET_MASK(arg) (1 << (arg % 8))
#define MAX_UCHAR (unsigned char)0xff

///////////////////////////////////////////////////////////////////////////////////////
//ChBitBoolƒƒ\ƒbƒh
///////////////////////////////////////////////////////////////////////////////////////

BitBool::BitBool()
{
	flgs.resize(1);
}

BitBool::BitBool(const unsigned char _size)
{
	flgs.resize(1);
	SetSize(_size);
}

BitBool::BitBool(const BitBool& _bitBool)
{
	SetBitBool(_bitBool);
}

void BitBool::SetAllDownFlg()
{
	for (size_t i = 0; i < flgs.size(); i++)
	{
		flgs[i] = 0;
	}
}

void BitBool::SetSize(const unsigned char _byteCount)
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
	if (_argsNum >= GetBitSize())return;

	flgs[GET_ARGS(_argsNum)] = flgs[GET_ARGS(_argsNum)] | GET_MASK(_argsNum);
}

void BitBool::SetBitFalse(const unsigned long _argsNum)
{
	if (_argsNum >= GetBitSize())return;

	flgs[GET_ARGS(_argsNum)] = flgs[GET_ARGS(_argsNum)] & (MAX_UCHAR - GET_MASK(_argsNum));
}

void BitBool::SetValue(const unsigned char _value, const unsigned char _byteCount)
{
	if (_byteCount >= GetByteSize())return;

	flgs[_byteCount] = _value;
}

void BitBool::SetBitBool(const BitBool& _bitBool)
{
	if (GetByteSize() != _bitBool.GetByteSize())
		SetSize(_bitBool.GetByteSize());

	for (unsigned long i = 0; i < _bitBool.GetByteSize(); i++)
	{
		SetValue(_bitBool.GetValue(i), i);
	}
}

unsigned long BitBool::GetByteSize()const
{
	return static_cast<unsigned long>(flgs.size());
}

unsigned long BitBool::GetBitSize()const
{
	return static_cast<unsigned long>(flgs.size() * 8);
}

bool BitBool::GetBitFlg(const unsigned long _argsNum)const
{
	if (_argsNum >= GetBitSize())return false;

	return flgs[GET_ARGS(_argsNum)] & GET_MASK(_argsNum);
}

unsigned char BitBool::GetValue(const unsigned char _byteCount)const
{
	if (GetByteSize() <= _byteCount)return 0;
	return flgs[_byteCount];
}

unsigned long BitBool::GetTrueCnt(const unsigned long& _cnt)const
{
	unsigned long cnt = 0;

	for (unsigned long i = 0; i < _cnt; i++)
	{
		if (!GetBitFlg(i))continue;
		cnt++;
	}

	return cnt;
}

