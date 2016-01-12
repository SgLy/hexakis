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
}

SettingsDialog::~SettingsDialog()
{
	delete ui;
}

void SettingsDialog::init_settings()
{
	ui->dropPreview->setChecked(dropPreview);
	ui->intervalEdit->setText(QString::asprintf("%d",interval));
}

void SettingsDialog::on_buttonBox_accepted()
{
	qDebug() << "on_buttonBox_accepted";
	dropPreview = ui->dropPreview->isChecked();
	interval = ui->intervalEdit->text().toInt();
}
