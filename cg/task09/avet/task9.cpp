#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <array>
#include <cmath>
#include "Transform.h"
#include "Clip.h"
#include "PClip.h"
#include "Form1.h"

using namespace task9;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	Application::Run(gcnew Form1());
	return 0;
}