#ifndef Ch_CPP_Model_h
#define Ch_CPP_Model_h


#include<vector>
#include<map>
#include<string>

#include"../../BasePack/ChStd.h"
#include"../../BasePack/Ch3D.h"

#include"../ChBaseObject/ChBaseComponent.h"
#include"../ChBaseObject/ChBaseObject.h"

namespace ChCpp
{
	template<typename CharaType>
	struct ModelFrame
	{
		struct VertexData
		{
			ChVec3 pos;
			ChVec3 normal;
			ChUIMat boneNo;
			ChLMat	blendPow;
		};

		struct Material
		{
			ChVec4 diffuse = 1.0f;
			ChVec4 specular = 1.0f;
			ChVec4 ambient = 0.0f;

			std::basic_string<CharaType> materialName = ChStd::GetZeroChara<CharaType>();
			std::vector<std::basic_string<CharaType>>textureNames;
		};

		struct SurFace
		{

			struct SurFaceVertex
			{
				size_t vertexNo = 0;
				ChVec2 uvPos;
			};

			SurFaceVertex vertexData[3];
			unsigned long materialNo = 0;
			ChVec3 normal;
		};

		struct Mesh
		{
			std::vector<ChPtr::Shared<VertexData>>vertexList;
			std::vector<ChPtr::Shared<Material>>materialList;
			std::map<std::basic_string<CharaType>, unsigned long> materialNo;
			std::vector<ChPtr::Shared<SurFace>>faceList;
		};

		struct Frame
		{
			union
			{
				ChLMatrix baseLMat = ChLMat();
				ChRMatrix baseRMat;
			};

			std::basic_string<CharaType> myName = ChStd::GetZeroChara<CharaType>();
			ChPtr::Shared<Mesh>mesh = nullptr;
			ChPtr::Weak<Frame>parent;
			std::vector<ChPtr::Shared<Frame>>childFrames;
		};

		ChPtr::Shared<Frame>modelData = nullptr;
		std::basic_string<CharaType> modelName;
	};
}

#endif
