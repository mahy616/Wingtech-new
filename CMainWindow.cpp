#include "CMainWindow.h"
#include "QDockWidget"
#include "ResultDetails.h"
#include "qdebug.h"
#include <QDateTime>
#include <QMouseEvent>
#include <QMutex>
#include <QTextStream>
#include <qdir.h>
#include "QMessageBox"

const QString m_red_SheetStyle = "min-width: 24px; min-height: 24px;max-width:24px; max-height: 24px;border-radius: "
                                 "12px;  border:1px solid black;background:red";
const QString m_green_SheetStyle = "min-width: 24px; min-height: 24px;max-width:24px; max-height: 24px;border-radius: "
                                   "12px;  border:1px solid black;background:green";
const QString m_grey_SheetStyle = "min-width: 24px; min-height: 24px;max-width:16px; max-height: 24px;border-radius: "
                                  "12px;  border:1px solid black;background:grey";
const QString m_yellow_SheetStyle = "min-width: 24px; min-height: 24px;max-width:16px; max-height: 24px;border-radius: "
                                    "12px;  border:1px solid black;background:yellow";

CMainWindow::~CMainWindow()
{
    delete m_Parameter;
    m_Parameter = NULL;
	delete m_RecipeManager;
	m_RecipeManager = nullptr;
	delete m_admin;
	m_admin = nullptr;
}

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch (type)
    {
        case QtDebugMsg:
            text = QString("Debug:");
            break;

        case QtWarningMsg:
            text = QString("Warning:");
            break;

        case QtCriticalMsg:
            text = QString("Critical:");
            break;

        case QtFatalMsg:
            text = QString("Fatal:");
    }

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString::fromLocal8Bit(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1          %2 %3 %4").arg(current_date).arg(text).arg(context_info).arg(msg);
    QString LogPath = QCoreApplication::applicationDirPath();
    LogPath.append("/log");
    QDir dir(LogPath);
    if (!dir.exists(LogPath))
    {
        dir.mkdir(LogPath);
    }
    QString logFile = LogPath + "/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
    logFile.append(".txt");
    QFile file(logFile);
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}

CMainWindow::CMainWindow(QWidget *parent) : QMainWindow(parent)
{
	qDebug() << "CMainWindow::CMainWindow(QWidget *parent) Init !";
    ui.setupUi(this);
    qInstallMessageHandler(outputMessage);
    InitVariables();
	m_Index = 0;      //发往窗口的图片数据统计
    InitResultDetails();
    InitStatusBar();
    InitConnections();
	m_Parameter->LoadConfig();
}

void CMainWindow::InitVariables()
{
	qDebug() << "InitVariables";
	ui.toolBar->addSeparator();
	QLabel *Space = new QLabel();
	Space->setMinimumWidth(50);
	ui.toolBar->addWidget(Space);

	QLabel *label = new QLabel();
	label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	ui.toolBar->addWidget(label);
	QLabel *Logo = new QLabel();
	Logo->setFixedWidth(300);
	Logo->setStyleSheet("image: url(:/CMainWindow/Resources/logo.png);");
	ui.toolBar->addWidget(Logo);
	
    //处理结果 OK/NG
    QFont LabelFont("微软雅黑", 142);

	m_FirstResult = new QLabel("OK1");
	m_FirstResult->setStyleSheet(
		"color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
	m_FirstResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);	

	m_SecondResult = new QLabel("OK2");
	m_SecondResult->setStyleSheet(
		"color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
	m_SecondResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_ThirdResult = new QLabel("OK3");
	m_ThirdResult->setStyleSheet(
		"color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
	m_ThirdResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

	m_FourthResult = new QLabel("OK4");
	m_FourthResult->setFont(LabelFont);
	m_FourthResult->setStyleSheet(
		"color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
	m_FourthResult->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
	   //检测最终结果
	QDockWidget *DockResult = new QDockWidget(QString::fromLocal8Bit("检测结果"));
	DockResult->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
	addDockWidget(Qt::RightDockWidgetArea, DockResult);

	QGridLayout *Layout = new QGridLayout();
	Layout->addWidget(m_FirstResult, 0, 0, 1, 1);
	Layout->addWidget(m_SecondResult, 0, 1, 1, 1);
	Layout->addWidget(m_ThirdResult, 1, 0, 1, 1);
	Layout->addWidget(m_FourthResult, 1, 1, 1, 1);

	QWidget *laywidget = new QWidget();
	laywidget->setLayout(Layout);
	DockResult->setWidget(laywidget);
	
    //数据统计
    m_Statistics = new StatisticsWidget();
    QDockWidget *DockStatistics = new QDockWidget(QString::fromLocal8Bit("数据统计"));
    DockStatistics->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, DockStatistics);
    DockStatistics->setWidget(m_Statistics);
	qDebug() << "Init DockStatistics widget";
	m_ListView = new QListView();
    m_LogModel = new QStandardItemModel();
    QFont font("微软雅黑", 12);
    m_ListView->setFont(font);
    m_LogModel = new QStandardItemModel();
    m_ListView->setModel(m_LogModel);
    QDockWidget *LogDock = new QDockWidget(QString::fromLocal8Bit("日志"));
    LogDock->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::RightDockWidgetArea, LogDock);
    LogDock->setWidget(m_ListView);
	
	qDebug() << "Init Log widget";
    m_Camera1Results.clear();
    m_Camera1Images.clear();
    m_Camera1Result = true;

    m_Camera2Results.clear();
    m_Camera2Images.clear();
    m_Camera2Result = true;

    m_Camera3Results.clear();
    m_Camera3Images.clear();
    m_Camera3Result = true;

    m_Camera4Results.clear();
    m_Camera4Images.clear();
    m_Camera4Result = true;

    m_Parameter = new CParameterSetting;
	m_RecipeManager = new CRecipeManager;
	m_admin = new adminLoginDialog;

	setActionEnable(false);
	m_bStart = false;
}

//收到PLC切换配方指令，根据配方中图像数量初始化结果细节
//每行10个图像状态
void CMainWindow::InitResultDetails()
{
	//m_ImageCounts = m_RecipeManager->GetImageCounts();
	m_ImageCounts = 28;
    qDebug() << "InitResultDetials";
    QGridLayout *Camera1Layout = new QGridLayout();

    int row = 0;
    int col = 0;
    for (int i = 0; i < m_ImageCounts; ++i)
    {
        if (col > 9)
        {
            row++;
            col = 0;
        }
        QLabel *label = new QLabel();
        label->installEventFilter(this);
        label->setStyleSheet(m_grey_SheetStyle);
		label->setText(QString::number(i+1));////////////////////////////////////////////////////////////////////////////
        Camera1Layout->addWidget(label, row, col);
        m_Camera1Results.push_back(label);
        col++;
    }
    ui.groupBox_1->setLayout(Camera1Layout);

    QGridLayout *Camera2Layout = new QGridLayout();
    row = 0;
    col = 0;
    for (int i = 0; i < m_ImageCounts; ++i)
    {
        if (col > 9)
        {
            row++;
            col = 0;
        }
        QLabel *label = new QLabel();
        label->installEventFilter(this);
        label->setStyleSheet(m_grey_SheetStyle);
		label->setText(QString::number(i+1));
        Camera2Layout->addWidget(label, row, col);
        m_Camera2Results.push_back(label);
        col++;
    }
    ui.groupBox_2->setLayout(Camera2Layout);

    QGridLayout *Camera3Layout = new QGridLayout();
    row = 0;
    col = 0;
    for (int i = 0; i < m_ImageCounts; ++i)
    {
        if (col > 9)
        {
            row++;
            col = 0;
        }
        QLabel *label = new QLabel();
        label->installEventFilter(this);
        label->setStyleSheet(m_grey_SheetStyle);
		label->setText(QString::number(i+1));
        Camera3Layout->addWidget(label, row, col);
        m_Camera3Results.push_back(label);
        col++;
    }
    ui.groupBox_3->setLayout(Camera3Layout);

    QGridLayout *Camera4Layout = new QGridLayout();
    row = 0;
    col = 0;
    for (int i = 0; i < m_ImageCounts; ++i)
    {
        if (col > 9)
        {
            row++;
            col = 0;
        }
        QLabel *label = new QLabel();
        label->installEventFilter(this);
        label->setStyleSheet(m_grey_SheetStyle);
		label->setText(QString::number(i+1));
		//label->update();
        Camera4Layout->addWidget(label, row, col);
        m_Camera4Results.push_back(label);
        col++;
    }
    ui.groupBox_4->setLayout(Camera4Layout);
}

//收到PLC开始信号后，刷新状态
void CMainWindow::RefreshResultDetails()
{
	qDebug() << "ago-m_Camera1Results:" << m_Camera1Results.size() << ",m_Camera2Images:" << m_Camera2Images.size() << ",m_Camera3Images:" << m_Camera3Images.size() << ",m_Camera4Images:" << m_Camera4Images.size();
    for (int i = 0; i < m_Camera1Results.size(); ++i)
    {
        m_Camera1Results.at(i)->setStyleSheet(m_grey_SheetStyle);
    }
    m_Camera1Images.clear();
    m_Camera1Result = true;

    for (int i = 0; i < m_Camera2Results.size(); ++i)
    {
        m_Camera2Results.at(i)->setStyleSheet(m_grey_SheetStyle);
    }
    m_Camera2Images.clear();
    m_Camera2Result = true;

    for (int i = 0; i < m_Camera3Results.size(); ++i)
    {
        m_Camera3Results.at(i)->setStyleSheet(m_grey_SheetStyle);
    }
    m_Camera3Images.clear();
    m_Camera3Result = true;

    for (int i = 0; i < m_Camera4Results.size(); ++i)
    {
        m_Camera4Results.at(i)->setStyleSheet(m_grey_SheetStyle);
    }
    m_Camera4Images.clear();
    m_Camera4Result = true;
	qDebug() << "after-m_Camera1Images:" << m_Camera1Images.size() << ",m_Camera2Images:" << m_Camera2Images.size() << ",m_Camera3Images:" << m_Camera3Images.size() << ",m_Camera4Images:" << m_Camera4Images.size();

}

bool CMainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseevent = static_cast<QMouseEvent *>(event);
        if (mouseevent->buttons() == Qt::LeftButton)
        {
            for (int i = 0; i < m_Camera1Results.size(); ++i)
            {
                if (obj == m_Camera1Results.at(i))
                {
                    qDebug() << "click at camera1 details index = " << i + 1;
                    if (m_Camera1Images.size() > i)
                    {
                        const QImage image = m_Camera1Images.at(i);
                        CResultDetials::GetInstance()->SetImage(image);
                        CResultDetials::GetInstance()->exec();
                    }
                    break;
                }
            }

            for (int i = 0; i < m_Camera2Results.size(); ++i)
            {
                if (obj == m_Camera2Results.at(i))
                {
                    qDebug() << "click at camera2 details index = " << i + 1;
                    if (m_Camera2Images.size() > i)
                    {
                        const QImage image = m_Camera2Images.at(i);
                        CResultDetials::GetInstance()->SetImage(image);
                        CResultDetials::GetInstance()->exec();
                    }
                    break;
                }
            }

            for (int i = 0; i < m_Camera3Results.size(); ++i)
            {
                if (obj == m_Camera3Results.at(i))
                {
                    qDebug() << "click at camera3 details index = " << i + 1;
                    if (m_Camera3Images.size() > i)
                    {
                        const QImage image = m_Camera3Images.at(i);
                        CResultDetials::GetInstance()->SetImage(image);
                        CResultDetials::GetInstance()->exec();
                    }
                    break;
                }
            }
            for (int i = 0; i < m_Camera4Results.size(); ++i)
            {
                if (obj == m_Camera4Results.at(i))
                {
                    qDebug() << "click at camera4 details index = " << i + 1;
                    if (m_Camera4Images.size() > i)
                    {
                        const QImage image = m_Camera4Images.at(i);
                        CResultDetials::GetInstance()->SetImage(image);
                        CResultDetials::GetInstance()->exec();
                    }
                    break;
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void CMainWindow::InitStatusBar()
{
    qDebug() << "InitStatusBar";
    ui.statusBar->setStyleSheet("QStatusBar::item{ border: 0px }");
    m_PLC.setStyleSheet(m_yellow_SheetStyle);
    ui.statusBar->addWidget(&m_PLC);
    QLabel *label = new QLabel(QString::fromLocal8Bit("PLC:"));
    ui.statusBar->addWidget(label);

    m_Camera1.setStyleSheet(m_yellow_SheetStyle);
    ui.statusBar->addWidget(&m_Camera1);
    label = new QLabel(QString::fromLocal8Bit("相机1:"));
    ui.statusBar->addWidget(label);

    m_Camera2.setStyleSheet(m_yellow_SheetStyle);
    ui.statusBar->addWidget(&m_Camera2);
    label = new QLabel(QString::fromLocal8Bit("相机2:"));
    ui.statusBar->addWidget(label);

    m_Camera3.setStyleSheet(m_yellow_SheetStyle);
    ui.statusBar->addWidget(&m_Camera3);
    label = new QLabel(QString::fromLocal8Bit("相机3:"));
    ui.statusBar->addWidget(label);

    m_Camera4.setStyleSheet(m_yellow_SheetStyle);
    ui.statusBar->addWidget(&m_Camera4);
    label = new QLabel(QString::fromLocal8Bit("相机4:"));
    ui.statusBar->addWidget(label);

	ui.action_Stop->setEnabled(false);
}

void CMainWindow::InitConnections()
{
    connect(ui.action_Start, SIGNAL(triggered()), this, SLOT(StartDection()));
    connect(ui.action_Stop, SIGNAL(triggered()), this, SLOT(StopDection()));
    connect(ui.action_Setting, SIGNAL(triggered()), this, SLOT(OpenSetting()));
	connect(ui.action_Recipe, SIGNAL(triggered()), this, SLOT(RecipeSetting()));
	connect(ui.action_admin, SIGNAL(triggered()), this, SLOT(AdminDection()));
	connect(ui.action_DataManager, SIGNAL(triggered()), this, SLOT(OpenDataManager()));
    qRegisterMetaType<Mat>("Mat");
    qRegisterMetaType<e_CameraType>("e_CameraType");
	qRegisterMetaType<map<int, string>>("map<int,string>");
	qRegisterMetaType<vector<int>>("vector<int>");
	qRegisterMetaType<QVector<QVector<QString>>>("QVector<QVector<QString>>");
	qRegisterMetaType<QVector<QImage>>("QVector<QImage>");
	qRegisterMetaType<s_ImageInfo>("s_ImageInfo");
    connect(m_Parameter, SIGNAL(SendOriginalImage(Mat, int, e_CameraType)), m_RecipeManager, SLOT(ReceivaOriginalImage(Mat, int, e_CameraType)));
	connect(m_Parameter, SIGNAL(SendThreshold(vector<int>)), m_RecipeManager, SLOT(ReceiveOffLineAlgoThreshold(vector<int>)));
	connect(m_Parameter, SIGNAL(SendThresholds(vector<int>, vector<int>)), m_RecipeManager, SLOT(ReceiveAlgoThreshold(vector<int>,vector<int>)));
	connect(m_Parameter, SIGNAL(SendCameraStatus(e_CameraType, bool)), this, SLOT(ReceiveCameraStatus(e_CameraType, bool)));
	connect(m_Parameter, SIGNAL(SendPLCStatus(bool)), this, SLOT(ReceivePLCStatus(bool)));
	connect(m_Parameter, SIGNAL(SendLoadImage(Mat, bool)), m_RecipeManager, SLOT(ReceiveLoadImage(Mat, bool)));

	connect(m_RecipeManager, SIGNAL(SendAlgoImageFromRecipe(s_ImageInfo, bool)), this, SLOT(ReceiveAlgoImage(s_ImageInfo, bool)));
	connect(m_RecipeManager, SIGNAL(SendStartSign()), this, SLOT(ReceiveStartSign()));
	connect(m_RecipeManager, SIGNAL(SendCameraParameters(QVector<QVector<QString>>)), m_Parameter, SLOT(ReceiveCameraParameters(QVector<QVector<QString>>)));
	connect(m_RecipeManager, SIGNAL(SendLoadRenderImage(Mat, bool, int)), m_Parameter, SLOT(ReceiveLoadRenderImage(Mat, bool, int)));

}

void CMainWindow::SendPLCResult(QString strResult)
{
	qDebug() << "CParameterSetting:" << strResult;
	if (CPLCManager::GetInstance()->GetConnectStatus())
	{
		if (!CPLCManager::GetInstance()->WritePLCData(strResult, 0))
		{
			QString Msg = "Write PLC Result Falied ";
			AddLog(Msg);
		}
	}

}

void CMainWindow::AddLog(QString log)
{
    int rows = m_LogModel->rowCount();
    if (rows > 1000)
    {
        m_LogModel->removeRows(0, rows);
    }
    m_LogModel->appendRow(new QStandardItem(log));
    m_ListView->scrollToBottom();
}

void CMainWindow::StartDection()
{
	qDebug() << "CMainWindow::StartDection()";
	if (!m_RecipeManager->SendPLCReadySign(true))
	{
		QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("初始化配方失败") );
		return;
	}

	if (!CDataManager::GetInstance()->GetConnectStatus())
	{
		QMessageBox::information(this, QString::fromLocal8Bit("提示"), QString::fromLocal8Bit("数据库未连接"));
		//return;
	}
	ui.action_Start->setEnabled(false);
	ui.action_Stop->setEnabled(true);
	ui.action_Setting->setEnabled(false);
	ui.action_Recipe->setEnabled(false);
    m_Parameter->StartDetecion(true);
	qDebug() << "CMainWindow::StartDection()->m_Parameter->StartDetecion(true)";
    m_bStart = true;
}

void CMainWindow::StopDection() 
{
	qDebug() << "CMainWindow::StopDection()";
	m_RecipeManager->SendPLCReadySign(false);
	ui.action_Start->setEnabled(true);
	ui.action_Stop->setEnabled(false);
	ui.action_Setting->setEnabled(true);
	if (m_admin->m_admin.ID == QString::fromLocal8Bit("管理员"))
	{
		ui.action_Recipe->setEnabled(true);
	}
	qDebug() << "CMainWindow::StartDection()->m_Parameter->StartDetecion(false)";
	m_Parameter->StartDetecion(false);
	m_bStart = false;
}

void CMainWindow::OpenSetting()
{
    m_Parameter->exec();
}

void CMainWindow::RecipeSetting()
{
	m_RecipeManager->exec();
}

void CMainWindow::AdminDection()
{
	m_admin->exec();
	QString id = m_admin->GetCurrentID();
	QString pswd = m_admin->GetCurrentPswd();
	if (id == QString::fromLocal8Bit("管理员"))
	{
		if (m_admin->m_admin.Pswd == pswd)
		{
			setActionEnable(true);
			ui.action_admin->setEnabled(false);
		}
	}
	else if(id == QString::fromLocal8Bit("操作员"))
	{
		if (m_admin->m_operator.Pswd == pswd)
		{
			ui.action_Start->setEnabled(true);
			ui.action_Setting->setEnabled(false);
			ui.action_Recipe->setEnabled(false);
			ui.action_admin->setEnabled(false);
		}
		
	}
	else
	{
		ui.action_Start->setEnabled(false);
		ui.action_Setting->setEnabled(false);
		ui.action_Recipe->setEnabled(false);
		ui.action_admin->setEnabled(true);
	}

}

void CMainWindow::OpenDataManager()
{
	CDataManager::GetInstance()->setWindowState(Qt::WindowMaximized);
	CDataManager::GetInstance()->exec();

}

void CMainWindow::setActionEnable(bool bok)
{
	ui.action_Start->setEnabled(bok);
	ui.action_Setting->setEnabled(bok);
	ui.action_Recipe->setEnabled(bok);
}

void CMainWindow::ReceiveCameraStatus(e_CameraType type, bool bOpen)
{
    switch (type)
    {
        case CAMERA_FIRST:
            m_Camera1.setStyleSheet(bOpen ? m_green_SheetStyle : m_red_SheetStyle);
            break;
        case CAMERA_SECOND:
            m_Camera2.setStyleSheet(bOpen ? m_green_SheetStyle : m_red_SheetStyle);
            break;
        case CAMERA_THIRD:
            m_Camera3.setStyleSheet(bOpen ? m_green_SheetStyle : m_red_SheetStyle);
            break;
        case CAMERA_FOURTH:
            m_Camera4.setStyleSheet(bOpen ? m_green_SheetStyle : m_red_SheetStyle);
            break;
    }
}

void CMainWindow::ReceivePLCStatus(bool bConnected)
{
    m_PLC.setStyleSheet(bConnected ? m_green_SheetStyle : m_red_SheetStyle);
}

QImage CMainWindow::MattoQImage(Mat image)
{
    switch (image.type())
    {
        case CV_8UC1:
        {
            QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols,
                       QImage::Format_Grayscale8);
            return img;
        }
        break;
        case CV_8UC3:
        {
            QImage img((const unsigned char *)(image.data), image.cols, image.rows, image.cols * 3,
                       QImage::Format_RGB888);
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

void CMainWindow::ReceiveAlgoImage(s_ImageInfo ImageInfo, bool isClean)
{
	qDebug() <<"isClean:"<< isClean;
	if (isClean && m_DetecionResult.size() == 4)
	{
		qDebug() << "ProcessDetectionResult";
		ProcessDetectionResult();
		m_DetecionResult.clear();

	}

	QString Msg = "Receive algo image: type = " + QString::number(ImageInfo.Type) + ",result = " + QString::number(ImageInfo.bok) + "Index =" + QString::number(ImageInfo.ImageID);
	AddLog(Msg);
	qDebug() << Msg;
	QImage QImg = MattoQImage(ImageInfo.OriginalImage);
	QImg.detach();
	s_SaveImageInfo SaveInfo;
	s_StationInfo StationInfo;
	m_Mutex.lock();
	StationInfo.OriginalImage = ImageInfo.OriginalImage.clone();
	StationInfo.RenderImage = ImageInfo.RenderImage.clone();
	StationInfo.bok = ImageInfo.bok;
	StationInfo.DefectType = ImageInfo.DefectType;
	m_Mutex.unlock();
	QImage QRImg = MattoQImage(StationInfo.RenderImage);
	QRImg.detach();
	switch (ImageInfo.Type)
	{
	case CAMERA_FIRST:
	{
		m_Mutex.lock();
		std::map<int, std::string>MidDefectType;
		if (ImageInfo.DefectType.size() > 0)
		{
			for (auto mymap : ImageInfo.DefectType)
			{
				m_FitstDefectType.insert(mymap);
			}
			//MidDefectType.insert(m_FitstDefectType.begin(), ImageInfo.DefectType.end());
			//m_FitstDefectType = MidDefectType;
		}
		m_Camera1Images.push_back(QRImg);
		SaveInfo.FirstStation = StationInfo;
		m_Mutex.unlock();
		qDebug() << "push_back(QRImg)  type  :  CAMERA_FIRST" << "m_Camera1Images.size()" << m_Camera1Images.size();
		if (m_Camera1Images.size() > m_ImageCounts)
			{
				qDebug() << "m_Camera1Images.size()" << m_Camera1Images.size();
				return;
			}

		ui.label_Image1->setPixmap(QPixmap::fromImage(
			QImg.scaled(ui.label_Image1->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

		QLabel *Label = m_Camera1Results.at(ImageInfo.ImageID);
		if (Label == NULL)
		{
			qDebug() << "Camera1 Label is NULL,index = " << ImageInfo.ImageID;
			return;
		}
		if (ImageInfo.bok)
		{
			Label->setStyleSheet(m_green_SheetStyle);
		}
		else
		{
			Label->setStyleSheet(m_red_SheetStyle);
			m_Camera1Result = false;
		}
		if (ImageInfo.ImageID == m_ImageCounts - 1)
		{
			QString Msg = "Receive algo image: type = " + QString::number(ImageInfo.Type) + ",result = " + QString::number(ImageInfo.ImageID);
			qDebug() << "Msg" << Msg;
			AddLog(Msg);
			m_Index = 0;
			m_DetecionResult.insert(CAMERA_FIRST, m_Camera1Result);
		}

		m_Index++;
		break;
	}
	case CAMERA_SECOND:
	{
		m_Mutex.lock();
		std::map<int, std::string>MidDefectType;
		if (ImageInfo.DefectType.size() > 0)
		{
			for (auto mymap : ImageInfo.DefectType)
			{
				m_SecondDefectType.insert(mymap);
			}
			//MidDefectType.insert(m_SecondDefectType.begin(), ImageInfo.DefectType.end());
			//m_SecondDefectType = MidDefectType;
		}
		m_Camera2Images.push_back(QRImg);
		SaveInfo.SecondStation = StationInfo;
		m_Mutex.unlock();
		qDebug() << "push_back(QRImg)  type  :  CAMERA_SECOND" << "m_Camera2Images.size()" << m_Camera2Images.size();
		if (m_Camera2Images.size() > m_ImageCounts)
		{
			qDebug() << "m_Camera2Images.size()" << m_Camera2Images.size();
			return;
		}
		ui.label_Image2->setPixmap(QPixmap::fromImage(
			QImg.scaled(ui.label_Image2->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		QLabel *Label = m_Camera2Results.at(ImageInfo.ImageID);
		if (Label == NULL)
		{
			qDebug() << "Camera1 Label is NULL,index = " << ImageInfo.ImageID;
			return;
		}
		if (ImageInfo.bok)
		{
			Label->setStyleSheet(m_green_SheetStyle);
		}
		else
		{
			Label->setStyleSheet(m_red_SheetStyle);
			m_Camera2Result = false;
		}
		if (ImageInfo.ImageID == m_ImageCounts - 1)
		{
			QString Msg = "Receive algo image: type = " + QString::number(ImageInfo.Type) + ",result = " + QString::number(ImageInfo.ImageID);
			qDebug() << "Msg" << Msg;
			AddLog(Msg);
			m_Index = 0;
			m_DetecionResult.insert(CAMERA_SECOND, m_Camera2Result);
		}

		m_Index++;
		break;
	}
	case CAMERA_THIRD:
	{
		m_Mutex.lock();
		std::map<int, std::string>MidDefectType;
		if (ImageInfo.DefectType.size() > 0)
		{
			for (auto mymap : ImageInfo.DefectType)
			{
				m_ThirdDefectType.insert(mymap);
			}
			//MidDefectType.insert(m_ThirdDefectType.begin(), ImageInfo.DefectType.end());
			//m_ThirdDefectType = MidDefectType;
		}
		m_Camera3Images.push_back(QRImg);
		SaveInfo.ThirdStation = StationInfo;
		m_Mutex.unlock();
		qDebug() << "push_back(QRImg)  type  :  CAMERA_THIRD" << "m_Camera3Images.size()" << m_Camera3Images.size();
		if (m_Camera3Images.size() > m_ImageCounts)
		{
			qDebug() << "m_Camera3Images.size()" << m_Camera3Images.size();
			return;
		}
		ui.label_Image3->setPixmap(QPixmap::fromImage(
			QImg.scaled(ui.label_Image3->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
		QLabel *Label = m_Camera3Results.at(ImageInfo.ImageID);
		if (Label == NULL)
		{
			qDebug() << "Camera3 Label is NULL,index = " << ImageInfo.ImageID;
			return;
		}
		if (ImageInfo.bok)
		{
			Label->setStyleSheet(m_green_SheetStyle);
		}
		else
		{
			Label->setStyleSheet(m_red_SheetStyle);
			m_Camera3Result = false;

		}

		if (ImageInfo.ImageID == m_ImageCounts - 1)
		{
			QString Msg = "Receive algo image: type = " + QString::number(ImageInfo.Type) + ",result = " + QString::number(ImageInfo.ImageID);
			qDebug() << "Msg" << Msg;
			AddLog(Msg);
			m_Index = 0;
			m_DetecionResult.insert(CAMERA_THIRD, m_Camera3Result);
		}

		m_Index++;
		break;
	}
	case CAMERA_FOURTH:
	{
		m_Mutex.lock();
		std::map<int, std::string>MidDefectType;
		if (ImageInfo.DefectType.size() > 0)
		{
			for (auto mymap : ImageInfo.DefectType)
			{
				m_FourthDefectType.insert(mymap);
			}
			//MidDefectType.insert(m_FourthDefectType.begin(), ImageInfo.DefectType.end());
			//m_FourthDefectType = MidDefectType;
		}
		m_Camera4Images.push_back(QRImg);
		SaveInfo.FourStation = StationInfo;
		m_Mutex.unlock();
		qDebug() << "push_back(QRImg)  type  :  CAMERA_FOURTH" << "m_Camera4Images.size()" << m_Camera4Images.size();
		if (m_Camera4Images.size() > m_ImageCounts)
		{
			qDebug() << "m_Camera4Images.size()" << m_Camera4Images.size();
			return;
		}
		ui.label_Image4->setPixmap(QPixmap::fromImage(
			QImg.scaled(ui.label_Image4->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));

		QLabel *Label = m_Camera4Results.at(ImageInfo.ImageID);
		if (Label == NULL)
		{
			qDebug() << "Camera4 Label is NULL,index = " << ImageInfo.ImageID;
			return;
		}
		if (ImageInfo.bok)
		{
			Label->setStyleSheet(m_green_SheetStyle);
		}
		else
		{
			Label->setStyleSheet(m_red_SheetStyle);
			m_Camera4Result = false;
		}
		if (ImageInfo.ImageID == m_ImageCounts - 1)
		{
			QString Msg = "Receive algo image: type = " + QString::number(ImageInfo.Type) + ",result = " + QString::number(ImageInfo.ImageID);
			qDebug() << "Msg" << Msg;
			AddLog(Msg);
			m_Index = 0;
			m_DetecionResult.insert(CAMERA_FOURTH, m_Camera4Result);
		}

		m_Index++;
		break;
	}
	break;
	default:;
	}
	qDebug() << "Station:" << ImageInfo.Type << "SaveImage index:" << ImageInfo.ImageID;
	m_Parameter->SaveImage(SaveInfo, ImageInfo.Type, ImageInfo.ImageID);
}

void CMainWindow::ReceiveInitImageNumber(int number)
{
	m_ImageCounts = number;
}

void CMainWindow::ReceiveStartSign()
{
	QString Msg = "Init Start ";
	AddLog(Msg);
	 Msg = "Init End ";
	AddLog(Msg);
	m_DetecionResult.clear();//========================================================
	RefreshResultDetails();
	m_Parameter->GetCameraInfo();
	qDebug() << "CPLCManager::GetInstance()->WritePLCStartSign()";
	if (!CPLCManager::GetInstance()->WritePLCStartSign())
	{
		Msg = "Write PLC Start Sign Failed ";
		AddLog(Msg);
		return;
	}
	Msg = "Init Success ";
	AddLog(Msg);
}

void CMainWindow::ProcessDetectionResult()
{
#if 1
	QString Msg;
	bool bok = true;
	bool allbok = true;
	qDebug() << "lamdal start";
	auto CameraLocalResult = [&](e_CameraType camera, QLabel* label, bool bok)
	{
		QMap<e_CameraType, bool>::iterator it = m_DetecionResult.find(camera);
		bok &= it.value();
		qDebug() << "camera = " << camera << ", bok = " << bok;

		if (bok)
		{
			Msg = Msg + "01";
		}
		else
		{
			Msg = Msg + "10";
		}
		switch (camera)
		{
		
			case CAMERA_FIRST:
			{
				if (bok)
				{
					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("OK1");
					m_Statistics->SetSuccess();
					m_Parameter->SendDetectionResult(1, Msg, camera, m_FitstDefectType);
				}
				else
				{
					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("NG1");
					m_Statistics->SetFailed();
					m_Parameter->SendDetectionResult(0, Msg, camera, m_FitstDefectType);
				}
				m_FitstDefectType.clear();
				allbok = allbok && bok;
			}
			break;
			case CAMERA_SECOND:
			{
				if (bok)
				{

					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("OK2");
					m_Statistics->SetSuccess();
					m_Parameter->SendDetectionResult(1, Msg, camera, m_SecondDefectType);
				}
				else
				{

					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("NG2");
					m_Statistics->SetFailed();
					m_Parameter->SendDetectionResult(0, Msg, camera, m_SecondDefectType);
				}
				m_SecondDefectType.clear();
				allbok = allbok && bok;
			}
			break;
			case CAMERA_THIRD:
			{
				if (bok)
				{
					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("OK3");
					m_Statistics->SetSuccess();
					m_Parameter->SendDetectionResult(1, Msg, camera, m_ThirdDefectType);
				}
				else
				{

					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("NG3");
					m_Statistics->SetFailed();
					m_Parameter->SendDetectionResult(0, Msg, camera, m_ThirdDefectType);
				}
				m_ThirdDefectType.clear();
				allbok = allbok && bok;
			}
			break;
			case CAMERA_FOURTH:
			{
				if (bok)
				{

					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");
					label->setText("OK4");
					m_Statistics->SetSuccess();
					m_Parameter->SendDetectionResult(1, Msg, camera, m_FourthDefectType);
				}
				else
				{
					label->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);font: 35pt \"微软雅黑\";");

					label->setText("NG4");
					m_Statistics->SetFailed();
					m_Parameter->SendDetectionResult(0, Msg, camera, m_FourthDefectType);
				}
				m_FourthDefectType.clear();
				allbok = allbok && bok;
			}
			break;
			default:break;
		}
	};

	CameraLocalResult(CAMERA_FIRST, m_FirstResult, bok);
	CameraLocalResult(CAMERA_SECOND, m_SecondResult, bok);
	CameraLocalResult(CAMERA_THIRD, m_ThirdResult, bok);
	CameraLocalResult(CAMERA_FOURTH, m_FourthResult, bok);

#else
	QString Msg;
	bool bok = true;
	QMap<e_CameraType, bool>::iterator it = m_DetecionResult.begin(), itEnd = m_DetecionResult.end();
	it = m_DetecionResult.find(CAMERA_FIRST);
	bok &= it.value();
	for (; it != itEnd; ++it)
	{

		bok &= it.value();
		if (bok == true)
		{
			Msg = Msg + "01";
		}
		else
		{
			Msg = Msg + "10";
		}
	}

	if (bok)
	{
		m_TotalResult->setStyleSheet("color: rgb(0, 170, 0);background-color: rgb(255, 255, 150);");
		m_TotalResult->setText("OK");
		m_Statistics->SetSuccess();
	}
	else
	{
		m_TotalResult->setStyleSheet("color: rgb(170, 0, 0);background-color: rgb(255, 255, 150);");
		m_TotalResult->setText("NG");
		m_Statistics->SetFailed();
	}
#endif
	// TODO PLC发送信号
	qDebug() << "SendPLCResult Msg = " << Msg;
	SendPLCResult(Msg);
	AddLog(QString::fromLocal8Bit("发送结果"));

}