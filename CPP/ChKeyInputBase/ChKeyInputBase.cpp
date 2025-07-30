#include"ChKeyInputBase.h"

void  ChCpp::KeyInputBase::SetKeyFlg(const unsigned char _key, bool _flg)
{
	keyInputBitbool.SetBitFlg(_key, _flg);
}

void  ChCpp::KeyInputBase::SetAllFlgDown()
{
	keyInputBitbool.SetAllDownFlg();
}

bool ChCpp::KeyInputBase::IsPushKey(const unsigned char _key)
{
	if (keyInputBitbool.GetBitFlg(_key))
	{
		nowInputBitbool.SetBitTrue(_key);
		return true;
	}
	nowInputBitbool.SetBitFalse(_key);
	return false;
}

bool ChCpp::KeyInputBase::IsPushKeyNoHold(const unsigned char _key)
{
	if (keyInputBitbool.GetBitFlg(_key))
	{
		if (!nowInputBitbool.GetBitFlg(_key))
		{
			nowInputBitbool.SetBitTrue(_key);
			return true;
		}
		return false;
	}
	nowInputBitbool.SetBitFalse(_key);
	return false;

}
