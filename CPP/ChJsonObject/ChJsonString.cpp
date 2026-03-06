#include"ChJsonString.h"

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString()
{
	value = ChStd::GetZeroChara<CharaType>();
}

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString(const JsonString& _str)
{
	value = _str.value;
}

template<typename CharaType>
ChCpp::JsonString<CharaType>::JsonString(const std::basic_string<CharaType>& _str)
{
	auto&& res = ChPtr::Make_S<JsonString>();
	*res = _str;
}

template<typename CharaType>
bool ChCpp::JsonString<CharaType>::SetRawData(const std::basic_string<CharaType>& _jsonText)
{
	if (_jsonText.size() < 2)return false;
	if (_jsonText[0] != ChStd::GetDBQuotation<CharaType>()[0])return false;
	if (_jsonText[_jsonText.size() - 1] != ChStd::GetDBQuotation<CharaType>()[0])return false;

	value = ChStr::StringToEscapeSequence(_jsonText.substr(1, _jsonText.size() - 2));

	return true;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonString<CharaType>::GetRawData()const
{
	return ChStd::GetDBQuotation<CharaType>() + ChStr::StringFromEscapeSequence(value) + ChStd::GetDBQuotation<CharaType>();
}

template<typename CharaType>
bool ChCpp::JsonString<CharaType>::AddDecimal(std::basic_string<CharaType>& _outText, const std::basic_string<CharaType>& _inText, const std::basic_string<CharaType>& _baseDecimal)
{
	if (!ChStd::IsBaseNumbers(_inText, _baseDecimal))return false;

	_outText += ChStd::ToBaseNumber<CharaType>(_inText, _baseDecimal, ChStd::DECIMAL_NUMBUR<CharaType>());

	return true;
}

CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonString);
