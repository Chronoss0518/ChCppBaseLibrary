
#include"../../BasePack/ChPtr.h"

#include"ChStringObject.h"

#define METHOD_LIST(_charaType,_stringObjectType)\
void StringObjectBase::Set(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	cast->str = _str;}\
void StringObjectBase::Get(StringObjectBase* _obj, std::basic_string<_charaType>& _str){\
	_str = ChStd::GetZeroChara<_charaType>();\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	_str = cast->str;}\
bool StringObjectBase::Is(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return cast->str == _str;}\
bool StringObjectBase::IsConstain(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return cast->str.find(_str, 0) != std::basic_string<_charaType>::npos;}\
size_t StringObjectBase::Find(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return std::basic_string<_charaType>::npos;\
	return cast->str.find(_str, 0);}


using namespace ChCpp;

METHOD_LIST(char, CharStringObject)
METHOD_LIST(wchar_t, WCharStringObject)
METHOD_LIST(char16_t, U16CharStringObject)
METHOD_LIST(char32_t, U32CharStringObject)
METHOD_LIST(char8_t, U8CharStringObject)
