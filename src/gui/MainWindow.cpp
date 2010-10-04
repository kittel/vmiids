/*
 * MainWindow.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: kittel
 */

#include "MainWindow.h"

#include "DetectionModuleWidget.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent) {
	// TODO Auto-generated constructor stub
	QMenu* fileMenu = menuBar()->addMenu(tr("&File"));

	QAction* openAct = new QAction(tr("&Open..."), this);
	openAct->setShortcuts(QKeySequence::Open);
	openAct->setStatusTip(tr("Open an existing file"));
	connect(openAct, SIGNAL(triggered()), this, SLOT(open()));
	fileMenu->addAction(openAct);

	fileMenu->addSeparator();

	QAction* quitAct = new QAction(tr("&Quit..."), this);
	quitAct->setShortcuts(QKeySequence::Quit);
	quitAct->setStatusTip(tr("Quit"));
	connect(quitAct, SIGNAL(triggered()), this, SLOT(quit()));
	fileMenu->addAction(quitAct);

	this->setCentralWidget(new DetectionModuleWidget(this));

}

MainWindow::~MainWindow() {
	// TODO Auto-generated destructor stub
}

void MainWindow::open(void) {
	qDebug() << "foo" << endl;
}

void MainWindow::quit(void) {
	QApplication::exit();
}


