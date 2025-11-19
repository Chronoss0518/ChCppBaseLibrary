
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

		static void Set(StringObjectBase* _in, StringObjectBase* _out);

		virtual void Set(StringObjectBase* _obj) = 0;

	public:

		template<typename CharaType>
		static std::basic_string<CharaType> Get(StringObjectBase* _obj);

	public:

		static bool Is(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static bool Is(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static bool Is(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

		static bool Is(StringObjectBase* _obj, StringObjectBase* _str);

		virtual bool Is(StringObjectBase* _obj) = 0;


		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static bool IsConstain(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

		static bool IsConstain(StringObjectBase* _obj, StringObjectBase* _str);

		virtual bool IsConstain(StringObjectBase* _obj) = 0;

	public:

		static void Add(StringObjectBase* _obj, std::basic_string<char>& _str);
		static void Add(StringObjectBase* _obj, std::basic_string<wchar_t>& _str);
		static void Add(StringObjectBase* _obj, std::basic_string<char16_t>& _str);
		static void Add(StringObjectBase* _obj, std::basic_string<char32_t>& _str);

#ifdef CPP20
		static void Add(StringObjectBase* _obj, std::basic_string<char8_t>& _str);
#endif

		static void Add(StringObjectBase* _base, StringObjectBase* _target);

		virtual void Add(StringObjectBase* _obj) = 0;

	public:

		static size_t Find(StringObjectBase* _obj, const std::basic_string<char>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<wchar_t>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char16_t>& _str);
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char32_t>& _str);

#ifdef CPP20
		static size_t Find(StringObjectBase* _obj, const std::basic_string<char8_t>& _str);
#endif

		static size_t Find(StringObjectBase* _base, StringObjectBase* _target);

		virtual size_t Find(StringObjectBase* _obj) = 0;

	};

	class CharStringObject :public StringObjectBase
	{
	public:

		CharStringObject() { type = Type::Char; }
		
	public:

		void Set(StringObjectBase* _obj)override;

		bool Is(StringObjectBase* _obj)override;

		bool IsConstain(StringObjectBase* _obj)override;

		void Add(StringObjectBase* _obj)override;

		size_t Find(StringObjectBase* _obj)override;

	private:
		friend StringObjectBase;
		std::basic_string<char> str = ChStd::GetZeroChara<char>();
	};

	class WCharStringObject :public StringObjectBase
	{
	public:

		WCharStringObject() { type = Type::WChar; }

	public:

		void Set(StringObjectBase* _obj)override;

		bool Is(StringObjectBase* _obj)override;

		bool IsConstain(StringObjectBase* _obj)override;

		void Add(StringObjectBase* _obj)override;

		size_t Find(StringObjectBase* _obj)override;

	private:
		friend StringObjectBase;
		std::basic_string<wchar_t> str = ChStd::GetZeroChara<wchar_t>();
	};

	class U16CharStringObject :public StringObjectBase
	{
	public:

		U16CharStringObject() { type = Type::U16Char; }

	public:

		void Set(StringObjectBase* _obj)override;

		bool Is(StringObjectBase* _obj)override;

		bool IsConstain(StringObjectBase* _obj)override;

		void Add(StringObjectBase* _obj)override;

		size_t Find(StringObjectBase* _obj)override;

	private:
		friend StringObjectBase;
		std::basic_string<char16_t> str = ChStd::GetZeroChara<char16_t>();
	};

	class U32CharStringObject :public StringObjectBase
	{
	public:

		U32CharStringObject() { type = Type::U32Char; }

	public:

		void Set(StringObjectBase* _obj)override;

		bool Is(StringObjectBase* _obj)override;

		bool IsConstain(StringObjectBase* _obj)override;

		void Add(StringObjectBase* _obj)override;

		size_t Find(StringObjectBase* _obj)override;

	private:
		friend StringObjectBase;
		std::basic_string<char32_t> str = ChStd::GetZeroChara<char32_t>();
	};

#ifdef CPP20
	class U8CharStringObject :public StringObjectBase
	{
	public:

		U8CharStringObject() { type = Type::U8Char; }

	public:

		void Set(StringObjectBase* _obj)override;

		bool Is(StringObjectBase* _obj)override;

		bool IsConstain(StringObjectBase* _obj)override;

		void Add(StringObjectBase* _obj)override;

		size_t Find(StringObjectBase* _obj)override;

	private:
		friend StringObjectBase;
		std::basic_string<char8_t> str = ChStd::GetZeroChara<char8_t>();
	};
#endif

}

#endif