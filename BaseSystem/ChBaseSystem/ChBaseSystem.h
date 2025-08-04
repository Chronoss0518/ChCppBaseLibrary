
#ifndef Ch_CPP_BaseSystem_h
#define Ch_CPP_BaseSystem_h

#include"../../BasePack/ChPtr.h"
#include"../../BasePack/ChMath3D.h"

#include"../../CPP/ChBitBool/ChBitBool.h"
#include"../../ClassParts/ChCPInitializer.h"

namespace ChCpp
{
	class KeyInputBase;
	class FPSController;
}

namespace ChSystem
{
	class SystemManager;

	class BaseSystem : public ChCp::Initializer
	{
	public:

		friend SystemManager;

	protected:

		BaseSystem();

		virtual ~BaseSystem()
		{
			Release();
		}

	public:

		virtual void Release()
		{
			if (ChPtr::NotNullCheck(keyInput)) { delete keyInput; keyInput = nullptr; }
			if (ChPtr::NotNullCheck(fpsController)) { delete fpsController; fpsController = nullptr; }
		};

	public://Set Functions//

		inline void SetUseSystemButtons(const bool _button) { useSystemButtonFlg = _button; }

		//全体で利用するFPSを管理//
		void SetFPS(const unsigned long _FPS);

	public://Get Functions//

		//Windの横幅サイズ取得//
		const inline unsigned int GetWindWidth()const { return windSize.w; }

		//Windの立幅サイズ取得//
		const inline unsigned int GetWindHeight()const { return windSize.h; }

		//FPSカウントの取得//
		const unsigned long GetFPS() const;

		const long double GetNowFPSPoint()const;

	public://Is Functions//

		//キーを押した際のチェックを行う関数//
		bool IsPushKey(const int _key);

		//キーを押した際に長押しを含んだのチェックを行う関数//
		bool IsPushKeyNoHold(const int _key);

		//ポーズ中かどうかを判断する関数。//
		//第一引数はポーズへ移行するボタン//
		//戻り値がTrueだった場合はポーズ中//
		bool IsPause(const int _key);

		virtual bool IsUpdate() { return false; };

		//システムで提供されているボタンを利用するか//
		bool IsUseSystemButtons() { return useSystemButtonFlg; }

	public://Update Functions//

		virtual inline void MouseUpdate() {}

		virtual inline unsigned long GetNowTime() { return 0; }
	
	public://Other Functions//

		//FPS処理
		bool FPSProcess();

	protected:

		ChMath::Vector2Base<unsigned long> windSize;

		bool useSystemButtonFlg = true;

		//Pause用変数//
		bool nowKey = false;
		bool pauseFlg = false;

		ChCpp::KeyInputBase* keyInput = nullptr;
		ChCpp::FPSController* fpsController = nullptr;

	};

	class SystemManager :public ChCp::Initializer
	{
	public:

		friend BaseSystem;
	
	public://Init And Release//

		//初期化を行う(戻り値は、マネージャーが扱うシステムのPointer)//
		template<class C>
		typename std::enable_if
			<std::is_base_of<BaseSystem, C>::value
			&& !std::is_same<BaseSystem, C>::value, C* const>::type Init()
		{
			if (*this)return nullptr;

			baseSystems = nullptr;

			baseSystems = ChPtr::Make_S<C>();
			SetInitFlg(true);

			return ChPtr::SafeCast<C>(baseSystems.get());
		}

		virtual void Release();
	
	public://SetFunction//

		//全体で利用するFPSを管理//
		inline void SetFPS(const unsigned long _FPS) { if (baseSystems != nullptr)baseSystems->SetFPS(_FPS); }

		inline void SetUseSystemButtons(const bool _button) { if(baseSystems != nullptr) baseSystems->SetUseSystemButtons(_button); }

	public://GetFunction//

		//FPSカウントの取得//
		const inline unsigned long GetFPS() const { return baseSystems != nullptr ? baseSystems->GetFPS() : 0; }

		const inline long double GetNowFPSPoint()const { return baseSystems != nullptr ? baseSystems->GetNowFPSPoint() : 0; }

		//ウィンドシステム(BaseSystem継承)を取得する//
		template<class T>
		typename std::enable_if
			<std::is_base_of<BaseSystem, T>::value, T* const>::type GetSystem()
		{
			return ChPtr::SafeCast<T>(baseSystems.get());
		}

	public://Is Functions//

		//BaseSystemより間接的に確認する//
		inline bool IsPushKey(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKey(_key);
		}

		//BaseSystemより間接的に確認する//
		inline bool IsPushKeyNoHold(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPushKeyNoHold(_key);
		}

		//BaseSystemより間接的に確認する//
		inline bool IsPause(const int _key)
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;
			return baseSystems->IsPause(_key);

		}

		//システムを継続するか//
		inline bool IsUpdate()
		{
			if (baseSystems == nullptr)return false;

			return baseSystems->IsUpdate();
		}

		//システムで提供されているボタンを利用するか//
		bool IsUseSystemButtons() { return baseSystems != nullptr ? baseSystems->IsUseSystemButtons() : false; }

	public://Other Functions//

		//FPS処理
		inline bool FPSProcess()
		{
			if (!*this)return false;
			if (baseSystems == nullptr)return false;

			return baseSystems->FPSProcess();
		}

	private:

		ChPtr::Shared<BaseSystem> baseSystems = nullptr;

		SystemManager() {}

		~SystemManager()
		{
			Release();
		}
	public:

		static SystemManager& GetIns()
		{
			static SystemManager ins;

			return ins;
		}

	};
	inline SystemManager& SysManager() { return SystemManager::GetIns(); };
}

#endif