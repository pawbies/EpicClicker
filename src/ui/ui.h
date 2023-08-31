#pragma once

//apparently it already get's defined automatically by linking against the static version in cmake
//#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"


class UI
{
	GLFWwindow *m_Window;

	bool       m_ShowStats,
			   m_ShowProgress;

	int*       m_SleepPtr;
	int*       m_AmountPtr;
	bool*      m_RunningPtr;
	long*      m_ClicksPtr;
	long*      m_TotalClicksPtr;


	void drawStats(int sleep, long clicks, long totalClicks);
	void drawProgress(bool forever, int clicks, int max);
	void drawMain();

public:
	UI(int* m_SleepPtr, int* m_AmountPtr, bool* m_RunningPtr, long* m_ClicksPtr, long* m_TotalClicksPtr);

	int  draw();
	void cleanup();
};