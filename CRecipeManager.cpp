#include "CRecipeManager.h"
#include "QDir"
#include "QFileDialog"
#include <qmessagebox.h>

CRecipeManager::CRecipeManager(QWidget *parent)
	: QDialog(parent)
{
	m_Ready = false;
	ui.setupUi(this);
	m_ImageCounts = 0;
	m_InitRecipe = true;
	InitVariables();
	InitRecipeNames();
	InitConnections();
	InitRecipe("","");
	m_LastIndex = 0;
}

void CRecipeManager::RunAlgo(Mat Image, int ImageID, e_CameraType type)
{
	s_ImageInfo ImageInfo;
	ImageInfo.OriginalImage = Image.clone();
	ImageInfo.ImageID = ImageID;
	ImageInfo.Type = type;
	if (ImageInfo.Type == CAMERA_FIRST )
	{
		m_FirstGpuAlgo->RunAlgo(ImageInfo);
	}
	else if (type == CAMERA_SECOND)
	{
		m_SecondGpuAlgo->RunAlgo(ImageInfo);
	}
	else if (type == CAMERA_THIRD)
	{
		m_ThirdGpuAlgo->RunAlgo(ImageInfo);
	}
	else if (type == CAMERA_FOURTH)
	{
		m_FourGpuAlgo->RunAlgo(ImageInfo);
	}
	else
	{
		qDebug() << "RunAlgo error"<< endl;
		return;
	}
	
}
//保存从PLC接收的配方名称
void CRecipeManager::SaveRecipeFromPLC(QString RecipeName, int RecipeNumber, int ImageCount)
{
	QString IniName = QCoreApplication::applicationDirPath() + "/RecipeFolder/" + QString::number(RecipeNumber)+"-"+ RecipeName + ".ini";
	CConfig *cfg = new CConfig(IniName);
	cfg->Write("Recipe_Parameters", "ImageCount", ImageCount);
}

bool CRecipeManager::InitRecipe(QString RecipeNumber, QString RecipeName)
{
	QString errMsg;
	bool rv;
	m_FirstGpuAlgo = new CAlgoManager();
	qRegisterMetaType<s_ImageInfo>("s_ImageInfo");
	connect(m_FirstGpuAlgo, SIGNAL(SendPorcessResult(s_ImageInfo)), this, SLOT(ReceivaAlgoImage(s_ImageInfo)));
	
	rv = m_FirstGpuAlgo->InitAlgo(0, m_zheng_path.toStdString(),m_ce_path.toStdString());
	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化配方失败"));
		return false;
	}
	else
	{
		m_FirstGpuAlgo->start();
	}

	m_SecondGpuAlgo = new CAlgoManager();
	connect(m_SecondGpuAlgo, SIGNAL(SendPorcessResult(s_ImageInfo)), this, SLOT(ReceivaAlgoImage(s_ImageInfo)));
	rv = m_SecondGpuAlgo->InitAlgo(0, m_zheng_path.toStdString(), m_ce_path.toStdString());

	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化配方失败"));
		return false;
	}
	else
	{
		m_SecondGpuAlgo->start();
	}

	m_ThirdGpuAlgo = new CAlgoManager();
	connect(m_ThirdGpuAlgo, SIGNAL(SendPorcessResult(s_ImageInfo)), this, SLOT(ReceivaAlgoImage(s_ImageInfo)));
	rv = m_ThirdGpuAlgo->InitAlgo(1, m_zheng_path.toStdString(), m_ce_path.toStdString());

	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化配方失败"));
		return false;
	}
	else
	{
		m_ThirdGpuAlgo->start();
	}

	m_FourGpuAlgo = new CAlgoManager();
	connect(m_FourGpuAlgo, SIGNAL(SendPorcessResult(s_ImageInfo)), this, SLOT(ReceivaAlgoImage(s_ImageInfo)));
	rv = m_FourGpuAlgo->InitAlgo(1, m_zheng_path.toStdString(), m_ce_path.toStdString());

	if (!rv)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化配方失败"));
		return false;
	}
	else
	{
		m_FourGpuAlgo->start();
	}



	m_Ready = true;
	return true;
}

void CRecipeManager::InitConnections()
{
	qRegisterMetaType<e_CameraType>("e_CameraType");
	qRegisterMetaType<Mat>("Mat");
	connect(CPLCManager::GetInstance(), SIGNAL(SendChangePLCRecipe(QString,int,int)), this, SLOT(ReceiveChangePlcRecipe(QString,int,int)));
	connect(CPLCManager::GetInstance(), SIGNAL(SendSavePLCRecipe(QString, int,int)), this, SLOT(ReceiveSavePlcRecipe(QString,int,int)));
	connect(CPLCManager::GetInstance(), SIGNAL(SendStartSign()), this, SLOT(ReceiveStartSign()));

}

bool CRecipeManager::SendPLCReadySign(bool bReady)
{
	if (m_Ready && m_InitRecipe)
	{
		CPLCManager::GetInstance()->WritePLCReady(bReady);
		return true;
	}
	else
	{
		return false;
	}
}

int CRecipeManager::GetImageCounts()
{
	return m_ImageCounts;
}

void CRecipeManager::InitVariables()
{
	QFont font("微软雅黑", 12);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.tableWidget->horizontalHeader()->setFont(font);
	ui.tableWidget->horizontalHeader()->setHighlightSections(false);
	ui.tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{color:rgb(255,255,255);background:rgb(41,136,41);}");
	ui.tableWidget->setColumnCount(3);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
	ui.tableWidget->verticalHeader()->setHidden(true);
	QStringList header;
	header << QString::fromLocal8Bit("图像ID") << QString::fromLocal8Bit("模型路径") << QString::fromLocal8Bit("选择模型");
	ui.tableWidget->setHorizontalHeaderLabels(header);

	ui.tableWidget_Camear->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableWidget_Camear->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui.tableWidget_Camear->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.tableWidget_Camear->horizontalHeader()->setFont(font);
	ui.tableWidget_Camear->horizontalHeader()->setHighlightSections(false);
	ui.tableWidget_Camear->horizontalHeader()->setStyleSheet("QHeaderView::section{color:rgb(255,255,255);background:rgb(41,136,41);}");
	ui.tableWidget_Camear->setColumnCount(3);
	ui.tableWidget_Camear->setRowCount(4);
	ui.tableWidget_Camear->horizontalHeader()->setMinimumSectionSize(100);
	ui.tableWidget_Camear->verticalHeader()->setHidden(true);

	ui.tableWidget_Camear->setItem(0, 0, new QTableWidgetItem(QString::fromLocal8Bit("相机一")));
	ui.tableWidget_Camear->setItem(1, 0, new QTableWidgetItem(QString::fromLocal8Bit("相机二")));
	ui.tableWidget_Camear->setItem(2, 0, new QTableWidgetItem(QString::fromLocal8Bit("相机三")));
	ui.tableWidget_Camear->setItem(3, 0, new QTableWidgetItem(QString::fromLocal8Bit("相机四")));

	QStringList headerCamer;
	headerCamer << QString::fromLocal8Bit("相机") << QString::fromLocal8Bit("曝光值") << QString::fromLocal8Bit("增益值");
	ui.tableWidget_Camear->setHorizontalHeaderLabels(headerCamer);

	ui.pushButton->setEnabled(false);


	QString IniPath = QCoreApplication::applicationDirPath() + "/Model/" +"Model.ini";
	QFileInfo info;
	if (info.exists(IniPath))
	{
		CConfig *cfg = new CConfig(IniPath);
		m_ce_path = QCoreApplication::applicationDirPath() + "/Model/" + cfg->GetString(MODEL_PATH, Model_Ce_Path);
		m_zheng_path = QCoreApplication::applicationDirPath() + "/Model/" + cfg->GetString(MODEL_PATH, Model_Zheng_Path);
	}
}

QStringList CRecipeManager::getFileNames(const QString &path)
{
	QDir dir(path);
	return dir.entryList(QStringList("*.ini"), QDir::Files | QDir::Readable, QDir::Name);
}

void CRecipeManager::InitRecipeNames()
{
	QString IniPath = QCoreApplication::applicationDirPath() + "/RecipeFolder";
	QStringList RecipeNames = getFileNames(IniPath);
	ui.comboBox->clear();
	for (int i = 0; i < RecipeNames.size(); ++i)
	{
		QFileInfo info(RecipeNames.at(i));
		QString Name = info.baseName();
		ui.comboBox->addItem(Name);
	}
	QString err;
}

void CRecipeManager::SwitchRecipe(QString Name)
{
	ui.pushButton->setEnabled(true);
	QString IniName = QCoreApplication::applicationDirPath() + "/RecipeFolder/" + Name + ".ini";
	CConfig *cfg = new CConfig(IniName);
	int ImageCount = cfg->GetInt("Recipe_Parameters", "ImageCount");
	ui.tableWidget->setRowCount(0);
	ui.tableWidget->clearContents();
	for (int i = 0; i < ImageCount; ++i)
	{
		ui.tableWidget->insertRow(ui.tableWidget->rowCount());
		QTableWidgetItem *item = new QTableWidgetItem(QString::number(i+1));
		ui.tableWidget->setItem(i, 0, item);
		QString ModelPath = cfg->GetString("Recipe_Parameters", QString::number(i + 1));
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(ModelPath));
		QPushButton *button = new QPushButton(QString::fromLocal8Bit("浏览..."));
		ui.tableWidget->setCellWidget(i, 2, button);
		connect(button, SIGNAL(clicked()), this, SLOT(BrowseModelPath()));
	}
	SetCameraParameters(cfg);
}

void CRecipeManager::BrowseModelPath()
{
	QPushButton *senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == nullptr)
	{
		return;
	}
	int row = ui.tableWidget->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y())).row();
	QString ModelPath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("模型路径"), "./", "*.smartmore");
	if (!ModelPath.isEmpty())
	{
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(ModelPath));
	}
}

void CRecipeManager::ReceiveSavePlcRecipe(QString msg, int RecipeNumber,int ImageCounts)
{
	SaveRecipeFromPLC(msg, RecipeNumber,ImageCounts);
}

void CRecipeManager::ReceiveChangePlcRecipe(QString msg, int number, int ImageCounts)
{
	qDebug() << "CRecipeManager::ReceiveChangePlcRecipe ImageCounts" << ImageCounts << " msg " << msg << " number " << number;
	m_ImageCounts = ImageCounts;
	m_Number = number;
	InitRecipe(QString::number(number), msg);
}

void CRecipeManager::ReceivaOriginalImage(Mat Image,int ImageID, e_CameraType Type)
{
	qDebug() << "ReceivaOriginalImage:" << ImageID << endl;
	RunAlgo(Image.clone(), ImageID, Type);
}

void CRecipeManager::ReceivaAlgoImage(s_ImageInfo ImageInfo)
{
	qDebug() << "ReceivaAlgoImageindex:" << ImageInfo.ImageID << endl;
	emit SendAlgoImageFromRecipe(ImageInfo,false);
	if (ImageInfo.ImageID == 27)
	{
		m_LastIndex++;
		if (m_LastIndex == 4)
		{
			m_LastIndex = 0;
			emit SendAlgoImageFromRecipe(ImageInfo,true);
		}		
	}
}

void CRecipeManager::ReceiveStartSign()
{
	emit SendStartSign();
}

void CRecipeManager::ReceiveAlgoThreshold(vector<int> AlgoThresholdZheng, vector<int> AlgoThresholdCe)
{
	qDebug() << "CRecipeManager::ReceiveAlgoThreshold, AlgoThresholdZheng: " << AlgoThresholdZheng << " AlgoThresholdCe " << AlgoThresholdCe;
	m_FirstGpuAlgo->GetAlgoThreshold(AlgoThresholdZheng, AlgoThresholdCe);
	m_SecondGpuAlgo->GetAlgoThreshold(AlgoThresholdZheng, AlgoThresholdCe);
	m_ThirdGpuAlgo->GetAlgoThreshold(AlgoThresholdZheng, AlgoThresholdCe);
	m_FourGpuAlgo->GetAlgoThreshold(AlgoThresholdZheng, AlgoThresholdCe);
}

void CRecipeManager::ReceiveOffLineAlgoThreshold(vector<int> AlgoThreshold)
{
	m_FirstGpuAlgo->GetAlgoThresholdOffLine(AlgoThreshold);
}

void CRecipeManager::ReceiveLoadImage(Mat image, bool e)
{
	int Time;
	m_FirstGpuAlgo->RunAlgoOffline(image, e, Time);
	emit SendLoadRenderImage(image, e, Time);
}

void CRecipeManager::SaveRecipe()
{
	QString RecipeName = ui.comboBox->currentText();
	QString IniName = QCoreApplication::applicationDirPath() + "/RecipeFolder/" + RecipeName + ".ini";
	CConfig *cfg = new CConfig(IniName);
	int rows = ui.tableWidget->rowCount();
	cfg->Write("Recipe_Parameters", "ImageCount", rows);
	for (int i = 0; i < rows; ++i)
	{
		QString ModelPath = ui.tableWidget->item(i, 1)->text();
		if (!QFileInfo::exists(ModelPath))
		{
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("模型路径不存在"));
			return;
		}
		cfg->Write("Recipe_Parameters", QString::number(i + 1), ModelPath);
	}
	SaveCameraParameters(cfg);
	delete cfg;
	cfg = nullptr;
	QString errMsg;
	QStringList ListRecipe=RecipeName.split("-");
	InitRecipe(ListRecipe[0], ListRecipe[1]);
}
 
void CRecipeManager::RemoveRecipe()
{
	QString RecipeName = ui.comboBox->currentText();
	QString IniName = QCoreApplication::applicationDirPath() + "/RecipeFolder/" + RecipeName + ".ini";

	if (IniName.isEmpty() || !QDir().exists(IniName))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("该文件不存在"));
	}

	QFileInfo file(IniName);
	if (file.isFile())
		QFile::remove(IniName);

	int i = ui.comboBox->currentIndex();
	ui.comboBox->removeItem(i);
	ui.tableWidget->clear();
}

void CRecipeManager::updateTableInfos(void)
{
	ui.tableWidget->clear();
	QStringList header;
	header << QString::fromLocal8Bit("图像ID") << QString::fromLocal8Bit("模型路径") << QString::fromLocal8Bit("选择模型");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	InitRecipeNames();
}

void CRecipeManager::SetCameraParameters(CConfig * cfg)
{
	ui.tableWidget_Camear->setItem(0, 1, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_FIRST_EXPOSURE")));
	ui.tableWidget_Camear->setItem(1, 1, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_SECOND_EXPOSURE")));
	ui.tableWidget_Camear->setItem(2, 1, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_THIRD_EXPOSURE")));
	ui.tableWidget_Camear->setItem(3, 1, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_FOUR_EXPOSURE")));

	ui.tableWidget_Camear->setItem(0, 2, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_FIRST_GAIN")));
	ui.tableWidget_Camear->setItem(1, 2, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_SECOND_GAIN")));
	ui.tableWidget_Camear->setItem(2, 2, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_THIRD_GAIN")));
	ui.tableWidget_Camear->setItem(3, 2, new QTableWidgetItem(cfg->GetString("Camera_Parameters", "CAMERA_FOUR_GAIN")));
}

void CRecipeManager::SaveCameraParameters(CConfig * cfg)
{
	cfg->Write("Camera_Parameters", "CAMERA_FIRST_EXPOSURE", ui.tableWidget_Camear->item(0, 1)->text());
	cfg->Write("Camera_Parameters", "CAMERA_SECOND_EXPOSURE", ui.tableWidget_Camear->item(1, 1)->text());
	cfg->Write("Camera_Parameters", "CAMERA_THIRD_EXPOSURE", ui.tableWidget_Camear->item(2, 1)->text());
	cfg->Write("Camera_Parameters", "CAMERA_FOUR_EXPOSURE", ui.tableWidget_Camear->item(3, 1)->text());

	cfg->Write("Camera_Parameters", "CAMERA_FIRST_GAIN", ui.tableWidget_Camear->item(0, 2)->text());
	cfg->Write("Camera_Parameters", "CAMERA_SECOND_GAIN", ui.tableWidget_Camear->item(1, 2)->text());
	cfg->Write("Camera_Parameters", "CAMERA_THIRD_GAIN", ui.tableWidget_Camear->item(2, 2)->text());
	cfg->Write("Camera_Parameters", "CAMERA_FOUR_GAIN", ui.tableWidget_Camear->item(3, 2)->text());
	QVector<QVector<QString>> AllCameraParameters;
	for (int row = 0; row < 4; row++)
	{
		QVector<QString>CameraParameters;
		for (int col = 1; col < 3; col++)
		{
			CameraParameters.push_back(ui.tableWidget_Camear->item(row, col)->text());		
		}
		AllCameraParameters.push_back(CameraParameters);
		CameraParameters.clear();
	}	
	emit SendCameraParameters(AllCameraParameters);
}