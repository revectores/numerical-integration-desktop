#include "integral.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QGroupBox>

#include <QLabel>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>
#include <QTableWidget>
#include <QtCharts>

#include <QMessageBox>

const int FUNC_COUNT = 4;
const int METHOD_COUNT = 3;

const int TRAPEZOID_INDEX = 0;
const int SIMPSON_INDEX = 1;
const int ROMBERG_INDEX = 2;


class Dashboard : public QWidget {
private:
	QGroupBox *func_group;
	QGroupBox *method_group;
	QGroupBox *para_group;
	QLabel *result_label;
	QLabel *para_label;
	QCheckBox *auto_checkbox;
	QLineEdit *para_input;

	QRadioButton *func_radios[FUNC_COUNT];
	QRadioButton *method_radios[METHOD_COUNT];

	void func_group_init();
	void method_group_init();
	void para_group_init();
	void result_label_init();

	void change_para_label();
	void integrate();


public:
	Dashboard(QWidget *parent = 0);
};


