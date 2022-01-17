#include "adminLoginDialog.h"
#include <QMessageBox>
#include <QFileInfo>
#include "Config.h"
adminLoginDialog::adminLoginDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	this->setWindowTitle(QString::fromLocal8Bit("登录"));
	
	ui.info_comboBox->addItem(QString::fromLocal8Bit("管理员"));
	ui.info_comboBox->addItem(QString::fromLocal8Bit("操作员"));
	InitAccount();
}

adminLoginDialog::~adminLoginDialog()
{

}

void adminLoginDialog::pushButtonAdminLogin()
{	
	QString id = GetCurrentID();
	if (id == QString::fromLocal8Bit("管理员"))
	{
		m_admin.ID = GetCurrentID();
		if (m_admin.Pswd == GetCurrentPswd())
		{
			accept();
		}
		else
		{
			QMessageBox::information(this, tr("error"), tr("password error"));
		}
	}
	else if (id == QString::fromLocal8Bit("操作员"))
	{
		m_operator.ID = GetCurrentID();
		if (m_operator.Pswd == GetCurrentPswd())
		{
			accept();
		}
		else
		{
			QMessageBox::information(this, tr("error"), tr("password error"));
		}
	}

}

void adminLoginDialog::pushButtonCancelLogin()
{
	reject();
}

void adminLoginDialog::pushButtonChangePassword()
{
	this->hide();
	ChangePswd::GetInstall()->show();
}

const QString &adminLoginDialog::GetCurrentPswd() const
{
	return ui.passwordLineEdit->text();
}

const QString &adminLoginDialog::GetCurrentID() const
{
	return ui.info_comboBox->currentText();
}

void adminLoginDialog::InitAccount()
{
	QString IniPath = QCoreApplication::applicationDirPath() + "/parameter_cfg.ini";
	QFileInfo info;
	if (info.exists(IniPath))
	{
		CConfig *cfg = new CConfig(IniPath);
		
		m_admin.ID = cfg->GetString(ID_AND_PSWD, ADMINID);
		m_admin.Pswd = cfg->GetString(ID_AND_PSWD, ADMINPSWD);

		m_operator.ID = cfg->GetString(ID_AND_PSWD, OPERATORID);
		m_operator.Pswd = cfg->GetString(ID_AND_PSWD, OPERATORPSWD);

		delete cfg;
		cfg = NULL;
	}

}