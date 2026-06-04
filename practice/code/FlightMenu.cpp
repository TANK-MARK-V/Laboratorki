#include "FlightMenu.h" 
#include <Windows.h> 
using namespace MarkflightsUI; // Название проекта 

[STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SetConsoleCP(1251); SetConsoleOutputCP(1251);
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew FlightMenu);
	return 0;
}