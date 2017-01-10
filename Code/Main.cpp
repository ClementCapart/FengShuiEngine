#include "FengShuiEngine_PCH.h"
#include "FengShuiEngine.h"
#include <Windows.h>

#if DIRECTX
bool Register(HINSTANCE instance);
#endif

int main(int argc, char** argv)
{
#if DIRECTX
	HMODULE instance = GetModuleHandle(NULL);
	if (!Register(instance))
		return 0;

	HWND window;
	MSG Msg;
	DWORD Count;

	window = CreateWindowEx(WS_EX_TOPMOST, "MyWin", "", WS_OVERLAPPEDWINDOW, 0, 0, 640, 480, GetDesktopWindow(), NULL, instance, NULL);

	if (window == NULL)
		return 0;

	ShowWindow(window, SW_SHOW);
	UpdateWindow(window);
	SetFocus(window);
#endif

	FengShuiEngine* engine = FengShuiEngine::GetInstance();
		
	FengShuiEngine::Settings settings = engine->ParseStartArguments(argc, argv);

	if (!engine->Init(settings))
		return -1;

	engine->Run();

	return 0;
}

#if DIRECTX
LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
}

bool Register(HINSTANCE instance)
{
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = 0;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = instance;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = "MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&Wc);
}
#endif