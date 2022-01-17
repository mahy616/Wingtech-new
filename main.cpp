#include "CMainWindow.h"
#include <QtWidgets/QApplication>
//#include "DumpHelper.h"
#include <Windows.h>
int main(int argc, char *argv[])
{
	//SetUnhandledExceptionFilter(ExceptionFilter);
	QApplication a(argc, argv);
	CMainWindow w;
	w.show();
	return a.exec();
}
