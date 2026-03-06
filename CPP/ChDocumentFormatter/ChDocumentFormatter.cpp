#include"../../BasePack/ChStd.h"

#include"../ChTextChecker/ChTextChecker.h"
#include"ChDocumentFormatter.h"

using namespace ChCpp;


template<typename CharaType>
DocumentFormatter<CharaType>::DocumentFormatter()
{
	checker = new TextChecker<CharaType>();

	indentText = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
DocumentFormatter<CharaType>::~DocumentFormatter()
{
	delete checker;

	for (auto&& insert : insertTextMap)
	{
		delete insert.second;
	}

	insertTextMap.clear();

	for (auto&& indent : indentCountMap)
	{
		delete indent.second;
	}

	indentCountMap.clear();
}

template<typename CharaType>
void DocumentFormatter<CharaType>::SetInsertText(
	const std::basic_string<CharaType>& _indentText,
	const std::basic_string<CharaType>& _insertText,
	bool _intoBeforeFlg)
{
	if (_indentText == ChStd::GetZeroChara<CharaType>())return;
	if (_insertText == ChStd::GetZeroChara<CharaType>())return;
	if (insertTextMap.find(_indentText) != insertTextMap.end())return;

	auto&& test = insertTextMap.find(_indentText);
	InsertTextData* data = test == insertTextMap.end() ?
		new InsertTextData() :
		test->second;

	checker->SetCheckText(_indentText);
	data->insertText = _insertText;
	data->intoBeforeFlg = _intoBeforeFlg;
	insertTextMap[_indentText] = data;
}

template<typename CharaType>
void DocumentFormatter<CharaType>::SetIndent(
	const std::basic_string<CharaType>& _indentUpDownText,
	int _indentCount,
	bool _removeFlg)
{
	if (_indentUpDownText == ChStd::GetZeroChara<CharaType>())return;
	if (_indentCount == 0)return;
	auto&& test = indentCountMap.find(_indentUpDownText);
	IndentTextData* data = test == indentCountMap.end() ?
		new IndentTextData() :
		test->second;
	checker->SetCheckText(_indentUpDownText);
	data->count = _indentCount;
	data->removeFlg = _removeFlg;
	indentCountMap[_indentUpDownText] = data;
}

template<typename CharaType>
void DocumentFormatter<CharaType>::SetIndentText(
	const std::basic_string<CharaType>& _indentBeforeText,
	const std::basic_string<CharaType>& _indentText)
{
	if (_indentBeforeText == ChStd::GetZeroChara<CharaType>())return;
	if (_indentText == ChStd::GetZeroChara<CharaType>())return;

	checker->SetCheckText(_indentBeforeText);

	indentBeforeText = _indentBeforeText;
	indentText = _indentText;
}

template<typename CharaType>
std::basic_string<CharaType> DocumentFormatter<CharaType>::Format(const std::basic_string<CharaType>& _base)
{
	std::basic_string<CharaType> resultBase = ChStd::GetZeroChara<CharaType>();

	if (_base.length() <= 0)return resultBase;
	if (insertTextMap.empty() && indentCountMap.empty())return _base;

	std::basic_string<CharaType>insertTextData = ChStd::GetZeroChara<CharaType>();
	
	std::basic_string<CharaType> checkText = ChStd::GetZeroChara<CharaType>();
	std::basic_string<CharaType> baseText = _base;

	for (size_t i = 0; i < baseText.length() && i < std::basic_string<CharaType>::npos; i++)
	{
		checkText = checker->CheckFirstText(baseText, i);

		auto&& insertData = insertTextMap.find(checkText);
		if (insertData == insertTextMap.end())
		{
			resultBase += baseText[i];
			continue;
		}

		std::basic_string<CharaType> tmp = insertData->second->insertText;

		if (insertData->second->intoBeforeFlg)
		{
			resultBase += tmp;
		}

		resultBase += insertData->first;
		i += insertData->first.length() - 1;

		if (!insertData->second->intoBeforeFlg)
		{
			resultBase += tmp;
		}

	}

	std::basic_string<CharaType>result = ChStd::GetZeroChara<CharaType>();

	int nowIndent = 0;
	for (size_t i = 0; i < resultBase.length(); i++)
	{
		checkText = checker->CheckFirstText(resultBase, i);

		if (checkText == indentBeforeText)
		{
			result += indentBeforeText;

			std::basic_string<CharaType>indent = ChStd::GetZeroChara<CharaType>();

			for (size_t j = 0; j < nowIndent; j++)
			{
				indent += indentText;
			}

			result += indent;

			continue;
		}

		auto&& indentData = indentCountMap.find(checkText);
		if (indentData != indentCountMap.end())
		{
			nowIndent += indentData->second->count;
			if (indentData->second->removeFlg)
			{
				result.pop_back();
			}
		}

		result += resultBase[i];
	}

	return result;
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::DocumentFormatter);
