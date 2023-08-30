#pragma once

#include <thread>

class Clicker {
private:
    int          m_Sleep,
                 m_Amount;
    long         m_Clicks,
                 m_TotalClicks;
    bool         m_Running;
    std::thread  m_ClickerThread;

    void click();

public:
    inline Clicker(int amount, int sleep): m_Sleep(sleep), m_Amount(amount), m_Clicks(0), m_TotalClicks(0), m_Running(false) {}
    inline Clicker():                      m_Sleep(0),     m_Amount(0),      m_Clicks(0), m_TotalClicks(0), m_Running(false) {}

    
    inline void start_clicker()  { m_ClickerThread = std::thread(&Clicker::click, this); }
    inline void detach_clicker() { m_ClickerThread.detach(); }


    inline bool*  getRunningPtr()      { return &m_Running; }
    inline int*   getSleepPtr()        { return &m_Sleep; }
    inline int*   getAmountPtr()       { return &m_Amount; }
    inline long*  getClicksPtr()       { return &m_Clicks; }
    inline long*  getTotalClicksPtr()  { return &m_TotalClicks; }
};