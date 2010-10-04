/*
 * DetectionModuleWidget.h
 *
 *  Created on: Sep 24, 2010
 *      Author: kittel
 */

#ifndef DETECTIONMODULEWIDGET_H_
#define DETECTIONMODULEWIDGET_H_

#include <QtGui>

class DetectionModuleWidget: public QWidget {
	Q_OBJECT

private:
	QListWidget* m_plv;
	QLineEdit* m_ple;

	QStringList getListOfDetectionModules();

public:
	DetectionModuleWidget(QWidget *parent = 0);
	virtual ~DetectionModuleWidget();

public slots:
	void insertClicked(void);
	void deleteClicked(void);

};

#endif /* DETECTIONMODULEWIDGET_H_ */
