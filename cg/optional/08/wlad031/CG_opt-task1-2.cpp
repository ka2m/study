// CG_opt-task1-2.cpp : main project file.

#include "stdafx.h"

#include <fstream>
#include <sstream>

#include "Transform.h"
#include "Clip.h"

#include "Form1.h"

using namespace CG_opttask12;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1());
	return 0;
}
