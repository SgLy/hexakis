#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog
{
	Q_OBJECT

public:
	explicit SettingsDialog(QWidget *parent = 0);
	~SettingsDialog();

	bool dropPreview;
	int interval;

	void init_settings();
private slots:
	void on_buttonBox_accepted();
private:
	Ui::SettingsDialog *ui;
	QSettings *settings;
};

#endif // SETTINGSDIALOG_H
