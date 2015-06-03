#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Transform.h"
#include "clip.h"
#include "Form1.h"

using namespace task4_5;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	Application::Run(gcnew Form1());
	return 0;
}