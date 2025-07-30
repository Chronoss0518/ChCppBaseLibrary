#ifndef Ch_CPP_FPSCon
#define Ch_CPP_FPSCon

namespace ChCpp
{
	class FPSController
	{
	public:

		//‘S‘Ì‚Å—˜—p‚·‚éFPS‚ğŠÇ—//
		inline void SetFPS(const unsigned long _FPS) { FPS = _FPS; }

	public:

		const inline unsigned long GetFPS() const { return FPS; }

		const inline long double GetNowFPSPoint()const { return lastFPSPoint; }

	public:

		bool Update(unsigned long _nowTime);

	private:

		unsigned long FPS = 60;
		long double lastFPSPoint = 0;
		unsigned long lastFPSTime = 0;

	};
}

#endif