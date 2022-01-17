#include "ChangePswd.h"
#include "qmessagebox.h"
#include <QFileInfo>
#include "Config.h"

ChangePswd *ChangePswd::m_Instance = NULL;

ChangePswd::ChangePswd(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	ui.info_comboBox->addItem(QString::fromLocal8Bit("管理员"));
	ui.info_comboBox->addItem(QString::fromLocal8Bit("操作员"));
	InitVariables();
}

ChangePswd::~ChangePswd()
{
}

ChangePswd *ChangePswd::GetInstall()
{
	if (m_Instance == NULL)
	{
		m_Instance = new ChangePswd();
	}
	return m_Instance;
}

void ChangePswd::confirmChangePswd()
{

	int index = ui.info_comboBox->currentIndex();
	if (index == 0)
	{
		if (!ui.OriginalPasswordLineEdit->text().isEmpty() &&
			!ui.NewPasswordLineEdit->text().isEmpty() &
			!ui.ConfirmPasswordLineEdit->text().isEmpty())
		{
			if (ui.OriginalPasswordLineEdit->text() == GetAdminPswd() && (
				ui.NewPasswordLineEdit->text() == ui.ConfirmPasswordLineEdit->text()))
			{
				QString pswd = ui.ConfirmPasswordLineEdit->text();
				//QString id = QString::fromLocal8Bit("管理员");
				QString id = GetAdminID();
				emit signalFromChangePswd(index, id, pswd);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("请检查输入内容是否正确"));
			}

		}
		else
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("请检查输入内容是否正确"));
		}
	}
	else if (index == 1)
	{
		if (!ui.OriginalPasswordLineEdit->text().isEmpty() &&
			!ui.NewPasswordLineEdit->text().isEmpty() &&
			!ui.ConfirmPasswordLineEdit->text().isEmpty())
		{
			if (ui.OriginalPasswordLineEdit->text() == GetOperatorPswd() && (
				ui.NewPasswordLineEdit->text() == ui.ConfirmPasswordLineEdit->text()))
			{
				QString pswd = ui.ConfirmPasswordLineEdit->text();
				QString id = GetOperatorID();
				emit signalFromChangePswd(index, id, pswd);
			}
			else
			{
				QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("请检查输入内容是否正确"));
			}

		}
		else
		{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("请检查输入内容是否正确"));
		}
	}
	
	ui.ConfirmPasswordLineEdit->clear();
	ui.NewPasswordLineEdit->clear();
	ui.OriginalPasswordLineEdit->clear();
}

void ChangePswd::setAdminID(const QString &id)
{
	m_adminID = id;
}

const QString &ChangePswd::GetAdminID() const
{
	return m_adminID;
}

void ChangePswd::setAdminPswd(const QString &pswd)
{
	m_adminPswd = pswd;
}

const QString &ChangePswd::GetAdminPswd() const
{
	return m_adminPswd;
}

void ChangePswd::setOperatorID(const QString &id)
{
	m_operatorID = id;
}

const QString &ChangePswd::GetOperatorID() const
{
	return m_operatorID;
}

void ChangePswd::setOperatorPswd(const QString &pswd)
{
	m_operatorPswd = pswd;
}

const QString &ChangePswd::GetOperatorPswd() const
{
	return m_operatorPswd;
}

void ChangePswd::InitVariables()
{
	QString IniPath = QCoreApplication::applicationDirPath() + "/parameter_cfg.ini";
	QFileInfo info;
	if (info.exists(IniPath))
	{
		CConfig *cfg = new CConfig(IniPath);

		QString id = cfg->GetString(ID_AND_PSWD, ADMINID);
		QString pswd = cfg->GetString(ID_AND_PSWD, ADMINPSWD);
		setAdminID(id);
		setAdminPswd(pswd);

		id = cfg->GetString(ID_AND_PSWD, OPERATORID);
		pswd = cfg->GetString(ID_AND_PSWD, OPERATORPSWD);
		setOperatorID(id);
		setOperatorPswd(pswd);

		delete cfg;
		cfg = NULL;
	}
}
