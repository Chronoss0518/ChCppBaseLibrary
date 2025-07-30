#ifndef Ch_CPP_KeyInputBase
#define Ch_CPP_KeyInputBase

#include"../ChBitBool/ChBitBool.h"

namespace ChCpp
{
	class KeyInputBase
	{
	public:

		KeyInputBase()
		{
			keyInputBitbool.SetSize(BITBOOL_ARRAY_SIZE);
			nowInputBitbool.SetSize(BITBOOL_ARRAY_SIZE);
		}

	protected:

		void SetKeyFlg(const unsigned char _key, bool _flg);

		void SetAllFlgDown();

	public:

		//�L�[���������ۂ̃`�F�b�N���s���֐�//
		bool IsPushKey(const unsigned char _key);

		//�L�[���������ۂɒ��������܂񂾂̃`�F�b�N���s���֐�//
		bool IsPushKeyNoHold(const unsigned char _key);

	public:

		virtual void Update() = 0;

	private:

		static constexpr unsigned char BITBOOL_ARRAY_SIZE = 256 / 8;

		BitBool keyInputBitbool;
		BitBool nowInputBitbool;

	};
}

#endif