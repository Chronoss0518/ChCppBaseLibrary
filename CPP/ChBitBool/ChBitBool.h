#ifndef Ch_CPP_BiBo_h
#define Ch_CPP_BiBo_h

#include<vector>

namespace ChCpp
{
	class BitBool final
	{
	public://Constructor Destructor//

		BitBool();

		BitBool(const unsigned char _size);

	public://Set Functions//

		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFlg(const unsigned long _argsNum, const bool _flg);

		//引数で選択された位置のビットをtrueをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitTrue(const unsigned long _argsNum);

		//引数で選択された位置のビットをfalseをセットする//
		//第一引数はアドレス内の一番小さいビットから数えた数値を入力//
		//例)アドレス位置が1000番,選択箇所1001番の場合は1を選択//
		void SetBitFalse(const unsigned long _argsNum);

		//引数で選択された位置のByteをセットする//
		//第一引数はセットする値//
		//第二引数はアドレス内の一番小さいビットから数えた数値を入力//
		void SetValue(const unsigned char _value, const unsigned char _byteCount = 0);

		void SetAllDownFlg();

		//1バイトごとでフラグ数を変更する//
		//(1以下にはならない)//
		void SetSize(const unsigned char _byteCount);

	public://Get Functions//

		//引数で選択された数値のビットの値によって//
		//ChStd::TrueかChStd::Falseを返す//
		bool GetBitFlg(const unsigned long _argsNum)const;

		//使用可能バイト数//
		unsigned long GetByteSize()const;

		//使用可能サイズ//
		unsigned long  GetBitSize()const
;
		unsigned char GetValue(const unsigned char _byteCount = 0)const;

		//フラグ数の指定でのTrueの個数取得//
		unsigned long GetTrueCnt(const unsigned long& _cnt)const;

		inline unsigned long GetTrueCnt()const
		{
			return GetTrueCnt(GetBitSize());
		}

	private:

		std::vector<unsigned char> flgs;
	};

}
#endif