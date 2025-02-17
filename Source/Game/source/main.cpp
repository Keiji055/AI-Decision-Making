#include "stdafx.h"
#include "GameWorld.h"

#include <CommonUtilities/InputHandler.h>

void Go(void);

int main(const int /*argc*/, const char* /*argc*/[])
{
	Go();
	return 0;
}

LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	CommonUtilities::InputHandler::UpdateEvents(message, wParam, lParam);
	hWnd;
	switch (message)
	{
		// this message is read when the window is closed
		case WM_DESTROY:
		{
			// close the application entirely
			PostQuitMessage(0);
			return 0;
		}
	}

	return 0;
}


void InitCallBack()
{
	unsigned short windowWidth = 1280;
	unsigned short windowHeight = 720;

	Tga::EngineCreateParameters createParameters;
#ifdef _DEBUG
		createParameters.myActivateDebugSystems = Tga::DebugFeature::Fps | Tga::DebugFeature::Mem | Tga::DebugFeature::Filewatcher | Tga::DebugFeature::Cpu | Tga::DebugFeature::Drawcalls | Tga::DebugFeature::OptimizeWarnings;
#else
		createParameters.myActivateDebugSystems = Tga::DebugFeature::Filewatcher;
#endif

	createParameters.myWindowHeight = windowHeight;
	createParameters.myWindowWidth = windowWidth;
	createParameters.myRenderHeight = windowHeight;
	createParameters.myRenderWidth = windowWidth;
	createParameters.myTargetWidth = windowWidth;
	createParameters.myTargetHeight = windowHeight;
	createParameters.myWindowSetting = Tga::WindowSetting::Overlapped;
	createParameters.myStartInFullScreen = false;
	createParameters.myPreferedMultiSamplingQuality = Tga::MultiSamplingQuality::High;

	createParameters.myApplicationName = L"TGE Game";
	createParameters.myEnableVSync = true;
}

void Go()
{
	Tga::LoadSettings(TGE_PROJECT_SETTINGS_FILE);

	Tga::EngineCreateParameters createParameters;
	createParameters.myWinProcCallback = [](HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {return WinProc(hWnd, message, wParam, lParam); };

	if (!Tga::Engine::Start(createParameters))
	{
		ERROR_PRINT("Fatal error! Engine could not start!");
		system("pause");
		return;
	}
	
	{
		GameWorld gameWorld;
		gameWorld.Init();

		Tga::Engine& engine = *Tga::Engine::GetInstance();

		while (engine.BeginFrame({0,0,0}))
		{
			CommonUtilities::InputHandler::UpdateInput();

			gameWorld.Update(engine.GetDeltaTime());
			gameWorld.Render();

			engine.EndFrame();
		}
	}

	Tga::Engine::GetInstance()->Shutdown();
}

