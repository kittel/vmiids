/*
 * DetectionModuleWidget.cpp
 *
 *  Created on: Sep 24, 2010
 *      Author: kittel
 */

#include "DetectionModuleWidget.h"

DetectionModuleWidget::DetectionModuleWidget(QWidget *parent) : QWidget(parent) {
	QVBoxLayout *layout = new QVBoxLayout();

	m_ple = new QLineEdit();
	layout->addWidget(m_ple);

	QPushButton* insertButton = new QPushButton(tr("insert", "&Insert"));
	layout->addWidget(insertButton);
	QObject::connect(insertButton, SIGNAL(clicked()), this, SLOT(insertClicked()));


	QPushButton* deleteButton = new QPushButton(tr("delete", "&Delete"));
	layout->addWidget(deleteButton);
	QObject::connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteClicked()));

	m_plv = new QListWidget(this);
	m_plv->addItems(this->getListOfDetectionModules());
	m_plv->sortItems();
	layout->addWidget(m_plv);

	this->setLayout(layout);

}

DetectionModuleWidget::~DetectionModuleWidget() {
	// TODO Auto-generated destructor stub
}

void DetectionModuleWidget::insertClicked() {
	if(m_ple->text().compare("") == 0) return;
	QListWidgetItem* item = new QListWidgetItem(m_ple->text());
	item->setBackground(QBrush(Qt::red));
	m_plv->addItem(item);
	m_plv->sortItems();
	m_ple->clear();
	m_ple->setFocus(Qt::OtherFocusReason);
}

void DetectionModuleWidget::deleteClicked() {
	if(m_plv->currentRow() == -1) {
		//TODO Message that list is empty
		return;
	}
	m_plv->takeItem(m_plv->currentRow());
}

QStringList DetectionModuleWidget::getListOfDetectionModules(){
	QStringList stringList;
	stringList.append("ProcessListDetectionModule");
	stringList.append("FileListDetectionModule");
	stringList.append("FileContentDetectionModule");
	return stringList;
}
