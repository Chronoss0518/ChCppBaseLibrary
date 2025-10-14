#ifndef	Ch_CPP_CText_h
#define	Ch_CPP_CText_h

#include<string>
#include<vector>

namespace ChCpp
{
	template<typename CharaType>
	class TextChecker
	{
	private:

		struct CheckData
		{
			size_t textLength = 0;
			std::vector<std::basic_string<CharaType>>strList;
			CheckData* nextData = nullptr;
		};

	public:

		virtual ~TextChecker() { Release(); }

	public:

		void Release();

	private:

		void ReleaseCheckData(CheckData** _checkData);

	public:

		void SetCheckText(const std::basic_string<CharaType>& _checkText);

	private:

		void SetCheckText(
			const std::basic_string<CharaType>& _checkText,
			CheckData** _data);

	public:

		bool IsSetText()const;

	public:

		std::basic_string<CharaType> CheckFirstText(
			const std::basic_string<CharaType>& _targetText,
			const size_t _startPos = 0)const;

		std::basic_string<CharaType>CheckLastText(
			const std::basic_string<CharaType>& _targetText,
			const size_t _startPos = 0)const;

	private:

		std::basic_string<CharaType> CheckText(
			CheckData* _checkData,
			const std::basic_string<CharaType>& _targetText,
			const size_t _startPos,
			bool _inversFlg = false)const;

	private:

		//max length datas//
		CheckData* first = nullptr;

	};
}

#endif