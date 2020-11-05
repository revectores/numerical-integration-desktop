#include <QApplication>
#include "dashboard.h"

int main(int argc, char *argv[]){

	QApplication app(argc, argv);

	Dashboard window;

	window.resize(640, 480);
	window.setWindowTitle("Numerical Integration");
	window.show();

	return app.exec();
}
