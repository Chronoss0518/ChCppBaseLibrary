#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"

#include"ChTextChecker.h"

using namespace ChCpp;


template<typename CharaType>
void TextChecker<CharaType>::Release()
{
	ReleaseCheckData(&first);
}

template<typename CharaType>
void TextChecker<CharaType>::ReleaseCheckData(CheckData** _checkData)
{
	if (ChPtr::NullCheck(*_checkData))return;

	ReleaseCheckData(&(*_checkData)->nextData);

	delete (*_checkData);
	(*_checkData) = nullptr;
}

template<typename CharaType>
void TextChecker<CharaType>::SetCheckText(const std::basic_string<CharaType>& _checkText)
{
	if(_checkText == ChStd::GetZeroChara<CharaType>())return;

	if (ChPtr::NullCheck(first))
	{
		first = new CheckData();
		first->textLength = _checkText.length();
		first->strList.push_back(_checkText);
		return;
	}

	if (first->textLength < _checkText.size())
	{
		CheckData* tmpFirst = new CheckData();
		tmpFirst->textLength = _checkText.length();
		tmpFirst->strList.push_back(_checkText);
		tmpFirst->nextData = first;
		first = tmpFirst;
		return;
	}

	SetCheckText(_checkText, &first);
}


template<typename CharaType>
void TextChecker<CharaType>::SetCheckText(
	const std::basic_string<CharaType>& _checkText,
	CheckData** _data)
{
	if (ChPtr::NullCheck(*_data))
	{
		(*_data) = new CheckData();
		(*_data)->textLength = _checkText.length();
		(*_data)->strList.push_back(_checkText);
		return;
	}

	if ((*_data)->textLength > _checkText.length())
	{
		SetCheckText(_checkText, &(*_data)->nextData);
		return;
	}

	std::vector<std::basic_string<CharaType>>& textList = (*_data)->strList;
	auto&& findText = std::find(textList.begin(),textList.end(),_checkText);

	if (findText != textList.end())return;

	textList.push_back(_checkText);
}

template<typename CharaType>
bool TextChecker<CharaType>::IsSetText()const
{
	return ChPtr::NotNullCheck(first);
}

template<typename CharaType>
std::basic_string<CharaType> TextChecker<CharaType>::CheckFirstText(
	const std::basic_string<CharaType>& _targetText,
	const size_t _startPos)const
{
	return CheckText(first, _targetText, _startPos);
}

template<typename CharaType>
std::basic_string<CharaType> TextChecker<CharaType>::CheckLastText(
	const std::basic_string<CharaType>& _targetText,
	const size_t _startPos)const
{
	return CheckText(first, _targetText, _startPos, true);
}

template<typename CharaType>
std::basic_string<CharaType> TextChecker<CharaType>::CheckText(
	CheckData* _checkData,
	const std::basic_string<CharaType>& _targetText,
	const size_t _startPos,
	bool _inversFlg)const
{
	if (ChPtr::NullCheck(_checkData))return ChStd::GetZeroChara<CharaType>();

	if(_targetText.length() < _startPos +_checkData->textLength)
		return CheckText(_checkData->nextData, _targetText, _startPos, _inversFlg);

	std::vector<std::basic_string<CharaType>>& textList = _checkData->strList;
	for (size_t i = 0; i < textList.size(); i++)
	{
		bool isTrue = true;

		for (size_t j = 0; j < _checkData->textLength; j++)
		{
			size_t checkPos = _inversFlg ? _targetText.length() - _checkData->textLength - _startPos + j : _startPos + j;
			
			if (textList[i][j] == _targetText[checkPos])continue;
			isTrue = false;
			break;
		}

		if (!isTrue)continue;
		return textList[i];
	}

	return CheckText(_checkData->nextData, _targetText, _startPos, _inversFlg);

}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::TextChecker);