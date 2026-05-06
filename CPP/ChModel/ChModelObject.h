
#ifndef Ch_CPP_ModelObject_h
#define Ch_CPP_ModelObject_h

#include<string>
#include<map>
#include<vector>

#include<float.h>

#include"../../ClassParts/ChCPInitializer.h"
#include"../ChTransformObject/ChTransformObject.h"

#include"ChModel.h"

namespace ChCpp
{
	template<typename CharaType>
	class ModelControllerBase;

	template<typename CharaType>
	struct TargetBoneData
	{
		ChLMat boneOffset;
		std::basic_string<CharaType> boneObjectName = ChStd::GetZeroChara<CharaType>();
	};

	template<typename CharaType>
	struct FrameComponent:public ChCpp::BaseComponent
	{
		std::vector<ChPtr::Shared<Ch3D::Primitive>> primitives;
		std::vector<ChPtr::Shared<Ch3D::MaterialData<CharaType>>>materialList;
		std::vector<ChPtr::Shared<Ch3D::SavePolyVertex>> vertexList;
		std::vector<ChPtr::Shared<TargetBoneData<CharaType>>>boneDatas;
		std::map<std::basic_string<CharaType>, size_t>mateNames;

		ChVec3 maxPos = ChVec3((10e+37f) * -1.0f);
		ChVec3 minPos = ChVec3(10e+37f);
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();
	};

	template<typename CharaType>
	struct AnimationComponent:public ChCpp::BaseComponent
	{
		struct AnimationObject
		{
			Ch3D::Transform start;
			Ch3D::Transform end;
			float animationTime = 0;
		};

		std::vector<ChPtr::Shared<AnimationObject>>keyframeAnimation;
		std::basic_string<CharaType> animationName = ChStd::GetZeroChara<CharaType>();
	};

	template<typename CharaType>
	class FrameObject : public ChCpp::TransformObject<CharaType>
	{

		template<typename CharaType>
		friend class ModelControllerBase;

	public:

		inline ChLMat GetOffsetLMatrix() { return offsetMat; }

		inline ChRMat GetOffsetRMatrix() { return offsetMat.GetConvertAxis(); }


	public://Update Functions//

		void SetAnimationName(const std::basic_string<CharaType>& _name);

	protected:

		ChLMat offsetMat;

	private:

		std::basic_string<CharaType> animationName = ChStd::GetZeroChara<CharaType>();
	};

	template<typename CharaType>
	class ModelObject :public FrameObject<CharaType>, public ChCp::Initializer
	{
	public:

		friend ModelControllerBase<CharaType>;

	public:

		virtual ~ModelObject() { Release(); }

	public:

		inline void Init()override { SetInitFlg(true); }

		inline virtual void Release()override { SetInitFlg(false); }

	public:

		inline void SetShaderAxisType(const Ch3D::ShaderAxisType _type) { axisType = _type; }

		void SetModelName(const std::basic_string<CharaType>& _name) { modelName = _name; }

	private:

		inline void SetMaxPos(const ChVec3& _pos) { maxPos = _pos; }

		inline void SetMinPos(const ChVec3& _pos) { minPos = _pos; }

		inline void SetCenterPos(const ChVec3& _pos) { centerPos = _pos; }

		inline void SetBoxSize(const ChVec3& _size) { boxSize = _size; }

	public:

		inline std::basic_string<CharaType> GetModelName() { return modelName; }

		//初期化時に作成した全フレームの最大地点//
		inline ChVec3 GetInitAllFrameMaxPos() { return maxPos; }

		//初期化時に作成した全フレームの最小地点//
		inline ChVec3 GetInitAllFrameMinPos() { return minPos; }

		//初期化時に作成した全フレームの中央地点//
		inline ChVec3 GetInitAllFrameCenterPos() { return centerPos; }

		//初期化時に作成した全フレームの箱のサイズ//
		//CenterToTopLine And CenterToRightLine//
		inline ChVec3 GetInitAllFrameBoxSize() { return boxSize; }

	public:

		void AddAnimationName(const std::basic_string<CharaType>& _name) { animationNames.push_back(_name); }

	public:

		virtual void Create(){}

	private:

		ChVec3 maxPos = ChVec3();
		ChVec3 minPos = ChVec3();
		ChVec3 centerPos = ChVec3();
		ChVec3 boxSize = ChVec3();

		Ch3D::ShaderAxisType axisType = Ch3D::ShaderAxisType::LeftHand;

		std::vector<std::basic_string<CharaType>>animationNames;
		std::basic_string<CharaType> modelName = ChStd::GetZeroChara<CharaType>();
	};

}

#endif