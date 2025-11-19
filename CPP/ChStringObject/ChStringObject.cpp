
#include"../../BasePack/ChPtr.h"

#include"ChStringObject.h"

#define BASE_METHOD_LIST(_charaType,_stringObjectType)\
void StringObjectBase::Set(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	cast->str = _str;}\
template<> std::basic_string<_charaType> StringObjectBase::Get(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return ChStd::GetZeroChara<_charaType>();\
	return cast->str;}\
template<> _charaType StringObjectBase::GetValue(StringObjectBase* _obj, size_t _position){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return 0;\
	if (cast->str.length() <= _position)return 0;\
	return cast->str[_position];}\
bool StringObjectBase::Is(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return cast->str == _str;}\
bool StringObjectBase::IsConstain(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return cast->str.find(_str, 0) != std::basic_string<_charaType>::npos;}\
void StringObjectBase::AddBefore(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	cast->str = _str + cast->str;}\
void StringObjectBase::AddAfter(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	cast->str = cast->str + _str;}\
size_t StringObjectBase::Find(StringObjectBase* _obj, const std::basic_string<_charaType>& _str){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return std::basic_string<_charaType>::npos;\
	return cast->str.find(_str, 0);}

#define CHILD_METHOD_LIST(_charaType,_stringObjectType)\
void _stringObjectType::Set(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	str = cast->str;}\
size_t _stringObjectType::GetLen(){\
	return str.length();}\
bool _stringObjectType::Is(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return str == cast->str;}\
bool _stringObjectType::IsConstain(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return false;\
	return str.find(cast->str) >= 0;}\
void _stringObjectType::AddBefore(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	str = cast->str + str;}\
void _stringObjectType::AddAfter(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return;\
	str = str + cast->str;}\
size_t _stringObjectType::Find(StringObjectBase* _obj){\
	auto&& cast = dynamic_cast<_stringObjectType*>(_obj);\
	if (ChPtr::NullCheck(cast))return std::basic_string<_charaType>::npos;\
	return str.find(cast->str);}\


using namespace ChCpp;


void StringObjectBase::Set(StringObjectBase* _in, StringObjectBase* _out)
{
	if (ChPtr::NullCheck(_in))return;
	if (ChPtr::NullCheck(_out))return;
	_in->Set(_out);
}

size_t StringObjectBase::GetLen(StringObjectBase* _obj)
{
	if (ChPtr::NullCheck(_obj))return -1;
	return _obj->GetLen();
}

bool StringObjectBase::Is(StringObjectBase* _in, StringObjectBase* _out)
{
	if (ChPtr::NullCheck(_in))return;
	if (ChPtr::NullCheck(_out))return;
	return _in->Is(_out);
}

bool StringObjectBase::IsConstain(StringObjectBase* _in, StringObjectBase* _out)
{
	if (ChPtr::NullCheck(_in))return;
	if (ChPtr::NullCheck(_out))return;
	return _in->IsConstain(_out);
}

void StringObjectBase::Add(StringObjectBase* _before, StringObjectBase* _after)
{
	if (ChPtr::NullCheck(_before))return;
	if (ChPtr::NullCheck(_after))return;
	_before->AddAfter(_after);
}

size_t StringObjectBase::Find(StringObjectBase* _base, StringObjectBase* _target)
{
	if (ChPtr::NullCheck(_base))return;
	if (ChPtr::NullCheck(_target))return;
	return _base->Find(_target);
}

BASE_METHOD_LIST(char, CharStringObject)
BASE_METHOD_LIST(wchar_t, WCharStringObject)
BASE_METHOD_LIST(char16_t, U16CharStringObject)
BASE_METHOD_LIST(char32_t, U32CharStringObject)
BASE_METHOD_LIST(char8_t, U8CharStringObject)

CHILD_METHOD_LIST(char, CharStringObject)
CHILD_METHOD_LIST(wchar_t, WCharStringObject)
CHILD_METHOD_LIST(char16_t, U16CharStringObject)
CHILD_METHOD_LIST(char32_t, U32CharStringObject)
CHILD_METHOD_LIST(char8_t, U8CharStringObject)
