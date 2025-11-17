#ifndef	Ch_CPP_DocF_h
#define	Ch_CPP_DocF_h

#include<string>
#include<map>

namespace ChCpp
{
	template<typename CharaType>
	class TextChecker;

	template<typename CharaType>
	class DocumentFormatter
	{
	public:
		
		struct InsertTextData
		{
			bool intoBeforeFlg = false;
			bool useIndentCount = false;
			std::basic_string<CharaType>insertText;
		};

		struct IndentTextData
		{
			bool removeFlg = false;
			int count = 0;
		};

	public:

		DocumentFormatter();

		virtual ~DocumentFormatter();

	public:

		void SetInsertText(
			const std::basic_string<CharaType>& _indentText,
			const std::basic_string<CharaType>& _insertText,
			bool _useIndentCount = true,
			bool _intoBeforeFlg = false);

		void SetIndent(
			const std::basic_string<CharaType>& _indentUpDownText,
			int _indentCount,
			bool removeFlg = false);

		void SetIndentText(const std::basic_string<CharaType>& _indentText);

	public:

		std::basic_string<CharaType> Format(const std::basic_string<CharaType>& _base);

	private:

		TextChecker<CharaType>* checker = nullptr;
		std::map<std::basic_string<CharaType>, InsertTextData*>insertTextMap;

		std::basic_string<CharaType>indentText;
		std::map<std::basic_string<CharaType>, IndentTextData*>indentCountMap;

	};
}

#endif