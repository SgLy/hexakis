#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include "consts.h"

#include <QVariant>
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::SettingsDialog)
{
	ui->setupUi(this);
	ui->dropPreview->setChecked(dropPreview);
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::on_buttonBox_accepted()
{
	qDebug() << "on_buttonBox_accepted";
	dropPreview = ui->dropPreview->isChecked();
}
