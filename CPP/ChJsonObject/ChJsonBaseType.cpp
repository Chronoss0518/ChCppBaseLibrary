#include"ChJsonBaseType.h"

#include"ChJsonBoolean.h"
#include"ChJsonString.h"
#include"ChJsonNumber.h"
#include"ChJsonArray.h"
#include"ChJsonObject.h"


using namespace ChCpp;

#define CH_JSON_NULL_TEXT_FUNCTION(type) CH_NUMBER_FUNCTION(ChCpp::Json::GetNullText,type)


namespace ChCpp
{
	namespace Json
	{
		CH_TO_NUMBER_FUNCTION(CH_JSON_NULL_TEXT_FUNCTION, "\"");
	}
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonNull<CharaType>::GetRawData()const
{
	return ChCpp::Json::GetNullText<CharaType>();
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBaseType<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameter(const std::basic_string<CharaType>& _json)
{
	if (_json == ChCpp::Json::GetNullText<CharaType>())return ChPtr::Make_S<JsonNull<CharaType>>();

	ChPtr::Shared<JsonBaseType<CharaType>> res = nullptr;

	res = GetParameterToObject(_json);

	if (res != nullptr)return res;

	res = GetParameterToArray(_json);

	if (res != nullptr)return res;

	res = GetParameterToString(_json);

	if (res != nullptr)return res;

	res = GetParameterToBoolean(_json);

	if (res != nullptr)return res;

	res = GetParameterToNumber(_json);

	if (res != nullptr)return res;

	return  ChPtr::Make_S<JsonNull<CharaType>>();
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::FormatDocument(const std::basic_string<CharaType>& _str)
{
	std::vector<CharaType>testCharList = {
		ChStd::GetStartBracketChara<CharaType>()[0],
		ChStd::GetStartBraceChara<CharaType>()[0],
		ChStd::GetCommaChara<CharaType>()[0],
		ChStd::GetEndBraceChara<CharaType>()[0],
		ChStd::GetEndBracketChara<CharaType>()[0] };

	ChCpp::Cumulative<CharaType> objectCount = ChCpp::Cumulative<CharaType>(
		ChStd::GetStartBraceChara<CharaType>()[0],
		ChStd::GetEndBraceChara<CharaType>()[0]);

	ChCpp::Cumulative<CharaType> arrayCount = ChCpp::Cumulative<CharaType>(
		ChStd::GetStartBracketChara<CharaType>()[0],
		ChStd::GetEndBracketChara<CharaType>()[0]);

	bool beforeCrFlg = false;
	bool afterCrFlg = false;

	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _str.length(); i++)
	{
		beforeCrFlg = false;
		afterCrFlg = false;

		for (unsigned char j = 0; j < testCharList.size(); j++)
		{
			if (_str[i] != testCharList[j])continue;
			beforeCrFlg = j > 2;

			afterCrFlg = j <= 2;
			break;
		}

		objectCount.Update(_str[i]);
		arrayCount.Update(_str[i]);

		if ((beforeCrFlg) && i > 0)
		{
			res += ChStd::GetLFChara<CharaType>()[0] + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}

		res += _str[i];

		if (afterCrFlg)
		{
			res += ChStd::GetLFChara<CharaType>()[0] + GetTabText(objectCount.GetCount() + arrayCount.GetCount());
		}
	}

	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonObject<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToObject(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonObject<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonArray<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToArray(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonArray<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonString<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToString(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonString<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonBoolean<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToBoolean(const std::basic_string<CharaType>& _json)
{
	auto&& res = ChPtr::Make_S<JsonBoolean<CharaType>>();
	if (!res->SetRawData(_json))return nullptr;

	return res;
}

template<typename CharaType>
ChPtr::Shared<ChCpp::JsonNumber<CharaType>> ChCpp::JsonBaseType<CharaType>::GetParameterToNumber(const std::basic_string<CharaType>& _json)
{
	if (_json.size() <= 0)return nullptr;
	if (_json.size() <= 1 && (_json[0] > 57 || _json[0] < 48))return nullptr;

	bool floatingPointFlg = false;

	auto&& res = ChPtr::Make_S<JsonNumber<CharaType>>();

	*res = ChStr::GetNumFromText<long double>(_json);

	return res;
}

template<typename CharaType>
std::basic_string<CharaType> ChCpp::JsonBaseType<CharaType>::GetTabText(unsigned long _count)
{
	std::basic_string<CharaType> res = ChStd::GetZeroChara<CharaType>();

	for (unsigned long i = 0; i < _count; i++)
		res += ChStd::GetHTabChara<CharaType>();

	return res;
}

template<typename CharaType>
std::vector<std::basic_string<CharaType>> ChCpp::JsonBaseType<CharaType>::GetCutTextLine(const std::basic_string<CharaType>& _val)
{
	bool inString = false;

	ChCpp::Cumulative<CharaType> objectCount = ChCpp::Cumulative<CharaType>(
		ChStd::GetStartBraceChara<CharaType>()[0],
		ChStd::GetEndBraceChara<CharaType>()[0]);

	ChCpp::Cumulative<CharaType> arrayCount = ChCpp::Cumulative<CharaType>(
		ChStd::GetStartBracketChara<CharaType>()[0],
		ChStd::GetEndBracketChara<CharaType>()[0]);

	const char whiteSpaceInterfaceChar = 0x20;
	const char delCharNum = 127;

	std::vector<std::basic_string<CharaType>> res;

	std::basic_string<CharaType>tmp = ChStd::GetZeroChara<CharaType>();

	for (int i = 0; i < _val.length(); i++)
	{
		if (!inString && arrayCount.GetCount() <= 0 && objectCount.GetCount() <= 0)
		{
			if (_val[i] <= whiteSpaceInterfaceChar) continue;
			if (_val[i] == delCharNum) continue;
		}

		if (_val[i] == ChStd::GetDBQuotation<CharaType>()[0])inString = !inString;

		arrayCount.Update(_val[i]);
		objectCount.Update(_val[i]);


		if (!inString && arrayCount.GetCount() <= 0 && objectCount.GetCount() <= 0)
		{
			if (_val[i] == ChStd::GetCommaChara<CharaType>()[0])
			{
				res.push_back(tmp);
				tmp = ChStd::GetZeroChara<CharaType>();
				continue;
			}

		}

		tmp += _val[i];
	}

	if (tmp != ChStd::GetZeroChara<CharaType>())
	{
		res.push_back(tmp);
	}


	return res;
}


CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonBaseType);
CH_STRING_TYPE_EXPLICIT_DECLARATION(ChCpp::JsonNull);
