#include "application.h"
#include <Windows.h>

Application::Application()
	: m_Clicker(5, 1000),
	  m_UI(
		  m_Clicker.getSleepPtr(),
		  m_Clicker.getAmountPtr(),
		  m_Clicker.getRunningPtr(),
		  m_Clicker.getClicksPtr(),
		  m_Clicker.getTotalClicksPtr()
	  ),
	  m_KeyIsPressed(false)
{
	m_ClickerRunning = m_Clicker.getRunningPtr();
	this->run();
	this->cleanup();
}

void Application::checkKey() //checks if the PAUSE button was pressed
{
	//i had to make this so strange to avoid weird things when you keep pressing the button
	if (GetAsyncKeyState(VK_PAUSE) & 0x8000)
	{
		if (!m_KeyIsPressed)
		{
			*m_ClickerRunning = !*m_ClickerRunning;
			m_KeyIsPressed = true;
		}
	}
	else
		m_KeyIsPressed = false;
}

void Application::run() //starts the whole program loop
{
	m_Clicker.start_clicker();

	while (m_UI.draw()) //the loop is much shorter than expecteed
		checkKey();

	m_Clicker.detach_clicker();
}

void Application::cleanup() //cleans up some of the ui things
{
	m_UI.cleanup();
}