#pragma once
#include "clicker/clicker.h"
#include "ui/ui.h"

class Application {
private:
	Clicker  m_Clicker;
	UI       m_UI;
	bool     m_KeyIsPressed;
	bool*    m_ClickerRunning;

	void checkKey();
	void run();
	void cleanup();

public:
	Application();
	~Application();
};