#include <Qt\qapplication.h>
#include <Qt\qstyle.h>
#include <Qt\qdesktopwidget.h>
#include <MeGlWindow.h>
#include <stdlib.h>
#include <MeWidget.h>
int main(int argc, char* argv[])
{

	QApplication app(argc, argv);
	MeWidget widg;
	widg.show();
		return app.exec();
}