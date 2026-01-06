
#ifndef Ch_CPP_StringObject_h
#define Ch_CPP_StringObject_h

#include"../../BasePack/ChStd.h"
#include<string>

namespace ChCpp
{
	class StringObjectBase
	{
	public:

		virtual ~StringObjectBase(){}

	public:

		static void Set(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static void Set(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static void Set(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static void Set(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static void Set(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

	public:

		static void Get(StringObjectBase* _obj, std::basic_string<char>& _str);
		static void Get(StringObjectBase* _obj, std::basic_string<wchar_t>& _str);
		static void Get(StringObjectBase* _obj, std::basic_string<char16_t>& _str);
		static void Get(StringObjectBase* _obj, std::basic_string<char32_t>& _str);

#ifdef CPP20
		static void Get(StringObjectBase* _obj, std::basic_string<char8_t>& _str);
#endif

	public:

		static bool Is(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static bool Is(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif


	public:

		static size_t Find(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

	};

	class CharStringObject :public StringObjectBase
	{
		friend StringObjectBase;
		std::basic_string<char> str = ChStd::GetZeroChara<char>();
	};

	class WCharStringObject :public StringObjectBase
	{
		friend StringObjectBase;
		std::basic_string<wchar_t> str = ChStd::GetZeroChara<wchar_t>();
	};

	class U16CharStringObject :public StringObjectBase
	{
		friend StringObjectBase;
		std::basic_string<char16_t> str = ChStd::GetZeroChara<char16_t>();
	};

	class U32CharStringObject :public StringObjectBase
	{
		friend StringObjectBase;
		std::basic_string<char32_t> str = ChStd::GetZeroChara<char32_t>();
	};

#ifdef CPP20
	class U8CharStringObject :public StringObjectBase
	{
		friend StringObjectBase;
		std::basic_string<char8_t> str = ChStd::GetZeroChara<char8_t>();
	};
#endif

}

#endif