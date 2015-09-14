#ifndef TP1MG2_H
#define TP1MG2_H

#include <QtWidgets/QMainWindow>
#include "ui_tp1mg2.h"

class TP1MG2 : public QMainWindow
{
	Q_OBJECT

public:
	TP1MG2(QWidget *parent = 0);
	~TP1MG2();

private:
	Ui::TP1MG2Class ui;
};

#endif // TP1MG2_H
