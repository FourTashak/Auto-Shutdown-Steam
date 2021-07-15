#include "MyForm2.h"
#include "fDec.h"
#include "Functions.h"
#include "Source.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CLRforms2::MyForm1 form;
	Application::Run(% form);
}

