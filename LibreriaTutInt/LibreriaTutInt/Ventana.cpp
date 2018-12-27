#include "Ventana.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

[STAThread]
void Main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LibreriaTutInt::Ventana form;
	Application::Run(%form);
}