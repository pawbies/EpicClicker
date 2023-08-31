#include "ui.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
#include <thread>
#include <Windows.h>

#define WINDOW_HEIGTH 300
#define WINDOW_WIDTH 300


UI::UI(int* sleepPtr, int* amountPtr, bool* runningPtr, long* clicksPtr, long* totalClicksPtr) //setup everything
	: m_ShowStats(false),
	  m_ShowProgress(false),
	  m_SleepPtr(sleepPtr),
	  m_AmountPtr(amountPtr),
	  m_RunningPtr(runningPtr),
	  m_ClicksPtr(clicksPtr),
	  m_TotalClicksPtr(totalClicksPtr)
{
	//I'm using pointer instead of the get... functions because i like it better that way
	//i'm sure that won't cause any problems in the future

	//setup glfw
	if (!glfwInit())
		std::cerr << "failed to init program" << std::endl;

	glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

	m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGTH, "Clicker", nullptr, nullptr);
	if (!m_Window)
		std::cerr << "failed to create window" << std::endl;

	glfwMakeContextCurrent(m_Window);
	glfwSwapInterval(1);

	//setup opengl
	if (glewInit() != GLEW_OK) 
		std::cerr << "Error: GLEW FAILED" << std::endl;
	
	
	//setup imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();
	//ImGui::StyleColorsLight();

	ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

void UI::drawProgress(bool forever, int clicks, int max) //imgui code to draw the progress bar
{
	if (!forever && max != 0)
		ImGui::ProgressBar((float)clicks / (float)max, ImVec2(200, 20), "Progess");
	else
		ImGui::ProgressBar(0, ImVec2(200, 20), "...");
}

void UI::drawStats(int sleep, long clicks, long totalClicks) //the stats
{
	ImGui::Text("Clicks since last stop: %d", clicks);
	ImGui::Text("Total clicks: %d", totalClicks);
	ImGui::Text("Speed: %dCPS", 1000/sleep);
}

void UI::drawMain() //the main menu
{
	int cps = 1000 / *m_SleepPtr;
	//i had to use a seperate variable for forever
	//because i was scared to cast a int* to a bool* 
	bool forever = *m_AmountPtr == 0;


	ImGui::Begin("Main", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

	ImGui::Text("Welcome to this custom made clicker\nthat works really well I must say,\none of my best creations i must say.");

	ImGui::Separator();

	ImGui::SliderInt("Sleep in MS", m_SleepPtr, 1, 1000);

	if (ImGui::SliderInt("CPS", &cps, 1, 1000))
		*m_SleepPtr = 1000 / cps;

	ImGui::SliderInt("Amount", m_AmountPtr, 0, 10000);

	if (ImGui::Checkbox("Forever", &forever))
		forever ? *m_AmountPtr = 0 : *m_AmountPtr = 1;

	if (ImGui::Button(m_ShowStats ? "Hide Stats" : "Show Stats"))
		m_ShowStats = !m_ShowStats;	

	ImGui::SameLine();

	if (ImGui::Button(m_ShowProgress ? "Hide Progress" : "Show Progress"))
		m_ShowProgress = !m_ShowProgress;

	ImGui::SameLine();

	if (ImGui::Button(*m_RunningPtr ? "Stop/PAUSE" : "Start/PAUSE"))
		*m_RunningPtr = !*m_RunningPtr;

	if (m_ShowProgress)
		drawProgress(forever, *m_ClicksPtr, *m_AmountPtr);

	if (m_ShowStats)
		drawStats(*m_SleepPtr, *m_ClicksPtr, *m_TotalClicksPtr);

	ImGui::End();
}

int UI::draw() //the draw calls and everything
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	drawMain();

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_Window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	glfwSwapBuffers(m_Window);
	glfwPollEvents();

	if (glfwWindowShouldClose(m_Window)) 
		return 0;
	else 
		return 1;
}

void UI::cleanup() //shut everything down
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_Window);
	glfwTerminate();
}