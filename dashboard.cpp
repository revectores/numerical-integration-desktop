#include <iostream>
#include <QDebug>
#include <QString>

#include "dashboard.h"


integral_method methods[3] = {
	composite_trapezoid,
	composite_Simpson,
	Romberg
};

std::vector<QString> func_exps {
	"∫_0^{1/4}  (4 − (sin(x))^2)^(1/2) dx",
	"∫_0^1  sin(x)/x dx",
	"∫_0^1  e^x/(4 + x^2) dx",
	"∫_0^1  (ln (1+x))/(1 + x^2) dx"	
};

std::vector<func> funcs {
	sqrt_sin,
	sin_over_x,
	exp_over_square_sum,
	ln_over_square_sum
};

std::vector<interval> intervals {
	{0, 0.25},
	{0, 1},
	{0, 1},
	{0, 1}
};

void Dashboard::func_group_init(){
	func_group = new QGroupBox("Integral");
	QGridLayout *layout = new QGridLayout;

	for (int i = 0; i < FUNC_COUNT; i++){
		func_radios[i] = new QRadioButton(func_exps[i]);
		layout->addWidget(func_radios[i], 0, i);
	    connect(func_radios[i], &QRadioButton::clicked, this, &Dashboard::integrate);
	}

   	func_radios[0]->setChecked(true);
	func_group->setLayout(layout);
}


void Dashboard::method_group_init(){
	method_group = new QGroupBox("Integration Method");

    QRadioButton *composite_trapezoid_radio = new QRadioButton("&Composite Trapezoid");
    QRadioButton *composite_Simpson_radio = new QRadioButton("&Composite Simpson");
    QRadioButton *Romberg_radio = new QRadioButton("&Romberg");

    method_radios[TRAPEZOID_INDEX] = composite_trapezoid_radio;
    method_radios[SIMPSON_INDEX] = composite_Simpson_radio;
    method_radios[ROMBERG_INDEX] = Romberg_radio;

    QGridLayout *layout = new QGridLayout;
    for (int i = 0; i < METHOD_COUNT; i++){
    	layout->addWidget(method_radios[i], 0, i);
	    connect(method_radios[i], &QRadioButton::clicked, this, &Dashboard::integrate);
    }

   	method_radios[0]->setChecked(true);
    method_group->setLayout(layout);
}


void Dashboard::para_group_init(){
	para_group = new QGroupBox("Integration Parameters");

	auto_checkbox = new QCheckBox("Automatic Step Mode");
	para_label = new QLabel("n=");
	para_input = new QLineEdit();

    connect(auto_checkbox, &QPushButton::clicked, this, &Dashboard::change_para_label);
    connect(para_input, &QLineEdit::textChanged, this, &Dashboard::integrate);

	para_input->setFixedWidth(50);
	para_label->setFixedWidth(60);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(auto_checkbox, 0, 0);
	layout->addWidget(para_label, 0, 1);
	layout->addWidget(para_input, 0, 2);
	para_group->setLayout(layout);
}


void Dashboard::result_label_init(){
	result_label = new QLabel();
}


Dashboard::Dashboard(QWidget *parent) : QWidget(parent) {
	 QGridLayout *layout = new QGridLayout(this);
	 
	 func_group_init();
	 method_group_init();
	 para_group_init();
	 result_label_init();

	 layout->addWidget(func_group, 0, 0, 1, 2);
	 layout->addWidget(method_group, 1, 0);
	 layout->addWidget(para_group, 1, 1);
	 layout->addWidget(result_label, 2, 0);
}



void Dashboard::change_para_label(){
	result_label->clear();
	para_input->clear();

	int auto_mode = auto_checkbox->isChecked();

	para_label->setText(auto_mode ? "Precision=" : "n=");
}


int get_checked(QRadioButton* radios[], int radio_count){
	int index = 0;

    while (index < radio_count){
        if (radios[index]->isChecked()){
            break;
        }
        index ++;
    }

    return index;
}


int count_one(int b){
	return b ? count_one(b & (b - 1)) + 1 : 0;
}


void Dashboard::integrate(){
	int func_index = get_checked(func_radios, FUNC_COUNT);
	int method_index = get_checked(method_radios, METHOD_COUNT);
	int auto_mode = auto_checkbox->isChecked();
	double para = para_input->text().toDouble();

	if (para == 0) {
		result_label->clear();
		return;
	}

	if (para < 0) {
		result_label->setText("parameters error.");
		return;
	}

	if (!auto_mode) {
		if ((method_index == SIMPSON_INDEX) && (int(para) % 2)) {
			result_label->setText("composite Simpson rule requires `n` to be even nunmber");
			return;
		}
		if ((method_index == ROMBERG_INDEX) && (count_one(int(para)) > 1)){
			result_label->setText("Romberg rule requires `n` to be exponent of 2");
			return;
		}
	}

	result_label->setText(QString::number(func_index) + QString::number(method_index));

	double result;
	if (auto_mode) {
		sum_step ss = auto_step_integral(methods[method_index], funcs[func_index], intervals[func_index], para);
		if (ss.sum == -1 && ss.step == -1){
			result_label->setText("Incorrect parameters");
			return;
		}
		result_label->setText(func_exps[func_index] + " = " + QString::number(ss.sum, 'G', 20) + "    best step: " + QString::number(ss.step, 'G', 10));
	} else {
		result = methods[method_index](funcs[func_index], intervals[func_index], para);
		if (result == -1){
			result_label->setText("Incorrect parameters");
			return;
		}
		result_label->setText(func_exps[func_index] + " = " + QString::number(result, 'G', 20));
	}

}
