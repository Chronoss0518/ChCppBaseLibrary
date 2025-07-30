
#include"../../BaseIncluder/ChBase.h"


#include"../../CPP/ChKeyInputBase/ChKeyInputBase.h"
#include"../../CPP/ChFPSController/ChFPSController.h"

#include"ChBaseSystem.h"

using namespace ChSystem;

///////////////////////////////////////////////////////////////////////////////////////
//ChBaseSystem メソッド
///////////////////////////////////////////////////////////////////////////////////////

//全体で利用するFPSを管理//
void ChSystem::BaseSystem::SetFPS(const unsigned long _FPS) {
	if (ChPtr::NotNullCheck(fpsController))fpsController
		->SetFPS(_FPS);
}

//FPSカウントの取得//
const unsigned long ChSystem::BaseSystem::GetFPS() const
{
	return ChPtr::NotNullCheck(fpsController) ?
		fpsController->GetFPS() :
		0;
}

const long double ChSystem::BaseSystem::GetNowFPSPoint()const
{
	return ChPtr::NotNullCheck(fpsController) ?
		fpsController->GetNowFPSPoint() :
		0;
}

bool ChSystem::BaseSystem::IsPushKey(const int _key)
{
	if (ChPtr::NullCheck(keyInput))return false;

	return keyInput->IsPushKey(_key);
}

bool ChSystem::BaseSystem::IsPushKeyNoHold(const int _key)
{
	if (ChPtr::NullCheck(keyInput))return false;

	return keyInput->IsPushKeyNoHold(_key);
}

bool ChSystem::BaseSystem::IsPause(const int _Key)
{
	bool tmpFlg;
	tmpFlg = IsPushKey(_Key);

	if (tmpFlg && nowKey)return pauseFlg;
	nowKey = false;

	if (!tmpFlg)return pauseFlg;

	pauseFlg = !pauseFlg;
	nowKey = true;

	return pauseFlg;
}

//FPS処理
bool ChSystem::BaseSystem::FPSProcess()
{
	if (ChPtr::NullCheck(fpsController))return true;

	return fpsController->Update(GetNowTime());
}

void ChSystem::SystemManager::Release()
{
	if (!*this)return;

	baseSystems = nullptr;

	SetInitFlg(false);
}
