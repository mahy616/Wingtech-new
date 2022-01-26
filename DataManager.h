#pragma once
#include "ui_DataManager.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QDebug>
#include "QMessageBox"
#include "AlgoManager.h"
//#include "ParametersManager.h"

class CDataManager :public QDialog
{
	Q_OBJECT
public:
	static CDataManager *GetInstance();
	bool GetConnectStatus() { return m_bConnected; }
	bool InsertData(QString Code, bool bOK, QString ImagePath, QString &errMsg, std::map<int, std::string> &DefectType);
private:
	CDataManager(QDialog *parent = NULL);
	static CDataManager *m_Instance;
	QSqlDatabase m_db;
	bool m_bConnected;
	QString m_DBName;
	Ui::DataManager ui;
private:
	void InitVariables();
	void InitConnections();
	QStringList getFileNames(const QString &path);
	QImage MattoQImage(Mat image);
	void LoadConfig();
	void SetControllerEnabled(bool bEnabled);
protected:
	void closeEvent(QCloseEvent *event);
private slots:
	void ConnectToDB();
	void QueryData();
	void SetDateEnabled(bool checked);
	void ClickedOnTableWidget(QModelIndex index);
	void ClearData();
};
