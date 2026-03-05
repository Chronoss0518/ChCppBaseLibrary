#ifndef Ch_CPP_TransformObject_h
#define Ch_CPP_TransformObject_h

#include"../ChBaseObject/ChBaseObject.h"

#include"../../BasePack/ChStd.h"
#include"../../BasePack/ChPtr.h"
#include"../../BasePack/Ch3D.h"

namespace ChCpp
{
	template<typename CharaType>
	class TransformObject: public ChCpp::BaseObject<CharaType>
	{
	public://Set Functions//

		inline void SetOutSideTransform(const Ch3D::Transform& _trans) {
			outSideMat.SetPosition(_trans.pos);
			outSideMat.SetRotation(_trans.rot);
			outSideMat.SetScalling(_trans.scl);
		}
		
		inline void SetOutSideTransform(const ChLMat& _mat) { outSideMat = _mat; }

		inline void SetOutSideTransform(const ChRMat& _mat) { outSideMat = _mat.GetConvertAxis(); }

		inline void SetFrameTransform(const Ch3D::Transform& _trans) {
			frameMat.SetPosition(_trans.pos);
			frameMat.SetRotation(_trans.rot);
			frameMat.SetScalling(_trans.scl);
		}

		inline void SetFrameTransform(const ChLMat& _mat) { frameMat = _mat; }

		inline void SetFrameTransform(const ChRMat& _mat) { frameMat = _mat.GetConvertAxis(); }


	public://Get Functions//

		inline ChLMat GetOutSideTransformLMat() { return outSideMat; }
		
		inline ChLMat GetFrameTransformLMat() { return frameMat; }
		
		inline ChLMat GetDrawLHandMatrix() { UpdateDrawTransform(); return drawMat; }


		inline ChRMat GetOutSideTransformRMat() { return outSideMat.GetConvertAxis(); }

		inline ChRMat GetFrameTransformRMat() { return frameMat.GetConvertAxis(); }

		inline ChRMat GetDrawRHandMatrix() { UpdateDrawTransform(); return drawMat.GetConvertAxis(); }

	public:

		void Update()override { UpdateDrawTransform(); }

		void UpdateDrawTransform()
		{
			ChLMat parentDrawMat;

			{
				auto parent = ChPtr::SharedSafeCast<TransformObject<CharaType>>(ChCpp::BasicObject::GetParent());

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
				auto&& parent = ChPtr::SharedSafeCast<TransformObject<CharaType>>(ChCpp::BasicObject::GetParent());

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