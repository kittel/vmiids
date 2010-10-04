/*
 * MainWindow.h
 *
 *  Created on: Sep 24, 2010
 *      Author: kittel
 */

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>

class MainWindow  : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

public slots:
	void open(void);
	void quit(void);

};

#endif /* MAINWINDOW_H_ */
