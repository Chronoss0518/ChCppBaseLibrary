#ifndef Ch_CPP_TransformObject_h
#define Ch_CPP_TransformObject_h


#include"../ChBaseObject/ChBaseObject.h"

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/Ch3D.h"


#ifndef CH_FRAME_SET_MATRIX_FUNCTION
#define CH_FRAME_SET_MATRIX_FUNCTION(_methodName,_matrixType) \
void _methodName(const Ch3D::Transform& _trans){\
	_matrixType.SetPosition(_trans.pos);\
	_matrixType.SetRotation(_trans.rot);\
	_matrixType.SetScalling(_trans.scl);\
}\
void _methodName(const ChLMat& _mat) { _matrixType = _mat; }\
void _methodName(const ChRMat& _mat) { _matrixType = _mat.GetConvertAxis(); }
#endif

#ifndef CH_FRAME_GET_MATRIX_FUNCTION
#define CH_FRAME_GET_MATRIX_FUNCTION(_RLType,_returnMethod) \
Ch##_RLType##Mat GetOutSizdTransform##_RLType##Mat() { return outSideMat _returnMethod ; }\
Ch##_RLType##Mat GetFrameTransform##_RLType##Mat() { return frameMat _returnMethod ; }\
Ch##_RLType##Mat GetDraw##_RLType##HandMatrix() { UpdateDrawTransform(); return drawMat _returnMethod ; }\
Ch##_RLType##Mat GetOffset##_RLType##Matrix() { return offsetMat _returnMethod ; }
#endif

namespace ChCpp
{
	template<typename CharaType>
	class TransformObject: public ChCpp::BaseObject<CharaType>
	{
	public://Set Functions//

		CH_FRAME_SET_MATRIX_FUNCTION(SetOutSideTransform, outSideMat);

		CH_FRAME_SET_MATRIX_FUNCTION(SetFrameTransform, frameMat);

	public://Get Functions//


		CH_FRAME_GET_MATRIX_FUNCTION(L, );

		CH_FRAME_GET_MATRIX_FUNCTION(R, .GetConvertAxis());

	public:

		void Update()override { UpdateDrawTransform(); }

		void UpdateDrawTransform()
		{
			ChLMat parentDrawMat;

			{
				auto parent = ChPtr::SharedSafeCast<FrameObject>(ChCpp::BasicObject::GetParent());

				if (parent != nullptr)
				{
					parentDrawMat = parent->drawMat;
				}
			}
			drawMat = outSideMat * frameMat * parentDrawMat;
		}

		void UpdateAllDrawTransform()
		{
			ChLMat parentDrawMat;
			{
				auto&& parent = ChPtr::SharedSafeCast<FrameObject<CharaType>>(ChCpp::BasicObject::GetParent());

				if (parent != nullptr)
				{
					parent->UpdateAllDrawTransform();
					parentDrawMat = parent->drawMat;
				}
			}
			drawMat = outSideMat * frameMat * parentDrawMat;
		}

	protected:

		inline void SetDrawMat(const ChLMat& _mat) { drawMat = _mat; }

	protected:

		ChLMat frameMat;
		ChLMat outSideMat;

	private:

		ChLMat drawMat;
	};
}

#endif