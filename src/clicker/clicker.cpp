#include "clicker.h"
#include <chrono>
#include <windows.h>

void Clicker::click() //clicker function
{
    INPUT input = { 0 };
    input.type = INPUT_MOUSE;

    auto sleep = [](int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); };
    
    auto c = [&]() { //lambda for one click
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &input, sizeof(input));
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        SendInput(1, &input, sizeof(input));
    };

    while (true)
    {
        while (!m_Running) { sleep(100); } //waiting for the clicker to be started
        if (m_Amount == 0)
        {
            while (m_Running)
            {
                sleep(m_Sleep);
                c();
                m_Clicks++;
            }
        }
        else
        {
            for (int i = 0; i < m_Amount && m_Running != 0; i++)
            {
                sleep(m_Sleep);
                c();
                m_Clicks++;
            }
        }
        m_Running = false;
        m_TotalClicks += m_Clicks;
        m_Clicks = 0;
    }
}
