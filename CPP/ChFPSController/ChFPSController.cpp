#include"ChFPSController.h"


bool ChCpp::FPSController::Update(unsigned long _nowTime)
{
	unsigned long tmp = _nowTime - lastFPSTime;

	if (tmp < 1000 / FPS)return false;

	lastFPSPoint = 1000 / tmp;
	lastFPSTime = _nowTime;

	return true;
}