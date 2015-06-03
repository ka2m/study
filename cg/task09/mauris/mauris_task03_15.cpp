// mauris_task03_15.cpp : main project file.

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include "Transform.h"
#include "Clip.h"
#include "Pclip.h"
#include "Form1.h"

using namespace mauris_task03_15;

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
