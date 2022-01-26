#include "DataManager.h"
#include "qdir.h"
#include "Config.h"

CDataManager *CDataManager::m_Instance = NULL;

CDataManager::CDataManager(QDialog *parent /* = NULL */)
	:QDialog(parent)
{
	ui.setupUi(this);
	InitVariables();
	InitConnections();
	LoadConfig();
}

CDataManager * CDataManager::GetInstance()
{
	if (m_Instance == NULL)
	{
		m_Instance = new CDataManager();
	}
	return m_Instance;
}

void CDataManager::InitVariables()
{
	m_bConnected = false;
	m_db = QSqlDatabase::addDatabase("QODBC");

	//��������ɫ������tabѡ����ɫ��δѡ�л�ɫ
	ui.tableWidget->setStyleSheet("QTabBar::tab{background-color:rgb(220,200,180);color:rgb(0,0,0);font:25pt '΢���ź�'}\
                                  QTabBar::tab::selected{background-color:rgb(0,170,0);color:rgb(255,255,0);font:25pt '΢���ź�'}\
                                  QTabBar::tab{ width:200 }\
 				                 QTabBar::tab{ height:40 }");
	//�����û������б�
	QFont font("΢���ź�", 12);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.tableWidget->horizontalHeader()->setFont(font);
	ui.tableWidget->horizontalHeader()->setHighlightSections(false);
	ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{color:rgb(255,255,255);background:rgb(41,136,41);}");
	ui.tableWidget->setColumnCount(5);
	ui.tableWidget->setAlternatingRowColors(1);
	//ui.tableWidget_Result->verticalHeader()->hide();
	QStringList header;
	header << QString::fromLocal8Bit("�Ϻ�") << QString::fromLocal8Bit("�����") << QString::fromLocal8Bit("ȱ������")  << QString::fromLocal8Bit("ͼ��·��") << QString::fromLocal8Bit(" ����");
	ui.tableWidget->setHorizontalHeaderLabels(header);

	ui.dateEdit_StartDate->setEnabled(false);
	ui.dateEdit_EndDate->setEnabled(false);
	SetControllerEnabled(false);
}

void CDataManager::InitConnections()
{

}

void CDataManager::LoadConfig()
{
	QString AppDir = QCoreApplication::applicationDirPath();
	QString IniPath = AppDir + "/parameter_cfg.ini";
	CConfig *cfg = new CConfig(IniPath);
	QString DBName = cfg->GetString(DATABASE, DATABASE_NAME);
	QString UserName = cfg->GetString(DATABASE, USER_NAME);
    QString Password = cfg->GetString(DATABASE, PASSWORD);

	if (!DBName.isEmpty() && !UserName.isEmpty() && !Password.isEmpty())
	{
		ui.lineEdit_DBName->setText(DBName);
		ui.lineEdit_UserName->setText(UserName);
		ui.lineEdit_Password->setText(Password);
		ConnectToDB();
	}
}

void CDataManager::SetControllerEnabled(bool bEnabled)
{
	ui.lineEdit_Code->setEnabled(bEnabled);
	ui.pushButton_Query->setEnabled(bEnabled);
	ui.checkBox_Date->setEnabled(bEnabled);
}

bool CDataManager::InsertData(QString Code, bool bOK, QString ImagePath,QString &errMsg, std::map<int, std::string> &DefectType)
{
	QString StrDefectType;
	for (auto map : DefectType)
	{
		StrDefectType= StrDefectType+"."+QString::fromStdString(map.second);
	}
	qDebug() << "InsertData";
	QString result = bOK ? "OK" : "NG";
	QString sql = "insert into " + m_DBName + ".dbo.test values(NEWID(),\'" + Code + "\',";
		    sql += "\'" + result + "\',\'" + StrDefectType + "\',\'" + ImagePath + "\',\'" + QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") + "\')";
	
	qDebug() << "sql:" << sql;
	QSqlQuery query(m_db);
	query.setForwardOnly(true);
	bool rv = query.exec(sql);
	if (!rv)
	{
		errMsg = query.lastError().text();
		qDebug() << "insert data error:" << query.lastError().text();
	}
	else
	{
		qDebug() << "insert data success";
	}
	return rv;
}

void CDataManager::ConnectToDB()
{
	QString DBName = ui.lineEdit_DBName->text();
	QString UserName = ui.lineEdit_UserName->text();
	QString Password = ui.lineEdit_Password->text();
	if (DBName.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���ݿ�������Ϊ��"));
		return;
	}
	if (UserName.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("�û�������Ϊ��"));
		return;
	}
	if (Password.isEmpty())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("���벻��Ϊ��"));
		return;
	}
	if (!m_bConnected)
	{
		std::cout<< DBName.toStdString()<< UserName.toStdString() <<std::endl;
		qDebug() << "connect database:" << DBName << "," << UserName;
		qDebug() << "ODBC driver?" << m_db.isValid();
		m_db.setHostName("local");                        //ѡ�񱾵�������127.0.1.1  
		m_db.setDatabaseName("QRCodeDataResult");                            //��������Դ����  
		m_db.setUserName(UserName);                               //��¼�û�  
		m_db.setPassword(Password);                           //����  
		m_bConnected = m_db.open();
		if (!m_bConnected)                                      //�����ݿ�  
		{
			qDebug() << m_db.lastError().text();
			QString errMsg = m_db.lastError().text();
			QMessageBox::information(this, QString::fromLocal8Bit("����"), errMsg);
			ui.label_DBStatus->setStyleSheet("background-color: rgb(170, 0, 0);");
		}
		else
		{
			qDebug() << "Scan Database connected success!";
			ui.label_DBStatus->setStyleSheet("background-color: rgb(0, 170, 0);");
			ui.pushButton_ConnectDB->setText(QString::fromLocal8Bit("�Ͽ�"));
			m_DBName = DBName;
			SetControllerEnabled(true);
		}
	}
	else
	{
		m_db.close();
		ui.label_DBStatus->setStyleSheet("background-color: rgb(255, 255, 0);");
		m_bConnected = false;
		ui.pushButton_ConnectDB->setText(QString::fromLocal8Bit("����"));
		SetControllerEnabled(false);
	}
}

void CDataManager::QueryData()
{
	QString Code = ui.lineEdit_Code->text();
	QString sql = "select * from " + m_DBName + ".dbo.test where Code like \'%" + Code + "%\'";
	bool bCheckd = ui.checkBox_Date->isChecked();
	if (bCheckd)
	{
		QDateTime StartDate = ui.dateEdit_StartDate->dateTime();
		QDateTime EndDate = ui.dateEdit_EndDate->dateTime();
		if (EndDate > StartDate)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("����ʱ�䲻�ܴ��ڿ�ʼʱ��"));
			return;
		}
		QString StartTime = StartDate.toString("yyyy-MM-dd hh:mm:ss");
		QString EndTime = EndDate.toString("yyyy-MM-dd hh:mm:ss");
		sql += " and DateTime between \'" + StartTime + "\' and \'" + EndTime + "\'";

	}

	QSqlQuery query(m_db);
	query.setForwardOnly(true);
	bool rv = query.exec(sql);
	//bool rv = query.exec("select * from QRCodeDataResult.dbo.test");
	QString errMsg = query.lastError().text();
	if (rv)
	{
		ui.tableWidget->setRowCount(0);
		ui.tableWidget->clearContents();
//  		for (int i = 0; i < ui.tableWidget->rowCount(); ++i)
//  		{
//  			ui.tableWidget->removeRow(0);
//  		}
		int row = 0;
		while (query.next())
		{
			ui.tableWidget->insertRow(ui.tableWidget->rowCount());
			QString Result = query.value(2).toString();
			bool bOK = Result == "OK";
			for (int col = 1; col < query.record().count(); ++col)
			{
				QString Data = query.value(col).toString();
				if (col == 4)
				{
					Data = Data.replace("T", " ");
				}
				QTableWidgetItem *item = new QTableWidgetItem(Data);
				if (bOK)
				{
					item->setBackgroundColor(QColor(0, 170, 0));
				}
				else
				{
					item->setBackgroundColor(QColor(170, 0, 0));
				}
				ui.tableWidget->setItem(row, col - 1, item);
			}
			row++;
		}
	}
}

void CDataManager::SetDateEnabled(bool checked)
{
	ui.dateEdit_StartDate->setEnabled(checked);
	ui.dateEdit_EndDate->setEnabled(checked);
}


QStringList CDataManager::getFileNames(const QString &path)
{
	QDir dir(path);
	QStringList FileNames;
	QStringList nameFilters;
	nameFilters << "*.jpg" << "*.bmp";
	QFileInfoList files = dir.entryInfoList(nameFilters, QDir::Files | QDir::Readable, QDir::Name);
	for (int i = 0; i < files.size(); ++i)
	{
		QFileInfo fileInfo = files.at(i);
		FileNames.push_back(fileInfo.absoluteFilePath());
	}
	return FileNames;

// 
// 	QDir dir(path);
// 	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
// 	dir.setSorting(QDir::Size | QDir::Reversed);
// 
// 	QFileInfoList list = dir.entryInfoList();
// 	for (int i = 0; i < list.size(); ++i) {
// 		QFileInfo fileInfo = list.at(i);
// 		std::cout << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
// 			.arg(fileInfo.fileName()));
// 		std::cout << std::endl;
// 	}

}

QImage CDataManager::MattoQImage(Mat image)
{
	switch (image.type())
	{
	case CV_8UC1:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols, QImage::Format_Grayscale8);
		return img;
	}
	break;
	case CV_8UC3:
	{
		QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols * 3, QImage::Format_RGB888);
		return img.rgbSwapped();
	}
	break;
	default:
	{
		QImage img;
		return img;
	}
	break;
	}
}

void CDataManager::closeEvent(QCloseEvent *event)
{
	if (m_bConnected)
	{
		QString AppDir = QCoreApplication::applicationDirPath();
		QString IniPath = AppDir + "/parametercfg.ini";
		CConfig *cfg = new CConfig(IniPath);
		cfg->Write(DATABASE, DATABASE_NAME, ui.lineEdit_DBName->text());
		cfg->Write(DATABASE, USER_NAME, ui.lineEdit_UserName->text());
		cfg->Write(DATABASE, PASSWORD, ui.lineEdit_Password->text());
	}
}

void CDataManager::ClickedOnTableWidget(QModelIndex index)
{
	//int row = index.row();
	//QString JPN = ui.tableWidget->item(row, 0)->text();
	//QString Path = ui.tableWidget->item(row, 2)->text();
	//QString CurTime = ui.tableWidget->item(row, 3)->text();
	//CurTime = CurTime.left(10);
	//QString ImagePath = Path + "/" + CurTime + "/" + JPN;

	//QStringList Images = getFileNames(ImagePath);
	//if (Images.size() == 0)
	//{
	//	QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ͼ���ļ�������"));
	//	return;
	//}

	////int Count = CParametersManager::GetInstance()->GetImageCount();

	////if (Count != Images.size())
	////{
	////	QString msg = QString::fromLocal8Bit("�ļ��к����ͼ�����\n�ļ���ͼ������:") + QString::number(Images.size());
	////	msg += QString::fromLocal8Bit("\n���ͼ������:") + QString::number(Count);
	////	QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), msg);
	////	return;
	////}

	//QByteArray ba = Images.at(0).toLocal8Bit();
	//char *file = ba.data();
	//Mat Image = imread(file);
	//Mat CombineImage;
	//CombineImage.create(Image.rows*Images.size(), Image.cols, CV_8UC3);
	//vector<Mat> ReadImages;
	//int height = 0;
	//int width = 0;
	//for (int i = 0; i < Images.size(); ++i)
	//{
	//	QString CurImageName = ImagePath + "/" + QString::number(i+1) + ".jpg";
	//	QFileInfo info;
	//	if (!info.exists(CurImageName))
	//	{
	//		QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("�ļ�������:") + CurImageName);
	//		return;
	//	}
	//	QByteArray ba = CurImageName.toLocal8Bit();
	//	char *file = ba.data();
	//	Mat CurImage = imread(file);
	//	if (i == 0)
	//	{
	//		height = CurImage.rows;
	//		width = CurImage.cols;
	//		printf("first image height = %d,width = %d\n",height,width);
	//	}
	//	else
	//	{
	//		if (height != CurImage.rows || width != CurImage.cols)
	//		{
	//			printf("current index = %d,height = %d,width = %d\n", i + 1, CurImage.rows, CurImage.cols);
	//			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("ͼ���߲�һ��"));
	//			return;
	//		}
	//	}
	//	ReadImages.push_back(CurImage.clone());
	//}
	//vconcat(ReadImages, CombineImage);
	//QImage image = MattoQImage(CombineImage);
	//ui.label_Image->SetImage(image);
	//ui.label_CurPath->setText(Path + "/" + CurTime + "/" + JPN);
}

void CDataManager::ClearData()
{
	QMessageBox message(QMessageBox::NoIcon, QString::fromLocal8Bit("��ʾ"), QString::fromLocal8Bit("��ȷ���Ƿ�Ҫ�������?"), QMessageBox::Yes | QMessageBox::No, NULL);
	if (message.exec() == QMessageBox::Yes)
	{
		QString sql = "delete from " + m_DBName + ".dbo.test";
		QSqlQuery query(m_db);
		query.setForwardOnly(true);
		bool rv = query.exec(sql);
		if (!rv)
		{
			QString errMsg = query.lastError().text();
			qDebug() << "insert data error:" << query.lastError().text();
		}
		else
		{
			qDebug() << "insert data success";
		}
	}

}
