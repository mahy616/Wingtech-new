#include "PLCManager.h"
#include "windows.h"


CPLCManager *CPLCManager::m_Instace = NULL;

CPLCManager::CPLCManager(QObject *parent)
	:QObject(parent)
{
	m_IP = "";
	m_Port = 0;
	m_bConnected = false;
	m_bReady = false;
	m_HeartBeat = 3;	
	//connect(m_TcpClient, SIGNAL(readyRead()), this, SLOT(ReadPLCData()));
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(SlotTimeOuter()));
	connect(&m_TimerRead, SIGNAL(timeout()), this, SLOT(SlotTimeOuterRead()));
	
}

CPLCManager::~CPLCManager()
{
	if (m_Timer.isActive())
	{
		qDebug() << "m_Timer.isActive() CPLCManager::~CPLCManager()";
		m_Timer.stop();
	}
	if (m_TimerRead.isActive())
	{
		qDebug() << "m_Timer.isActive() CPLCManager::~CPLCManager()";
		m_TimerRead.stop();
	}
}

CPLCManager *CPLCManager::GetInstance()
{
	if (m_Instace == NULL)
	{
		m_Instace = new CPLCManager();
	}
	return m_Instace;
}

bool CPLCManager::TcpConnect(QString ip, quint16 port, int HeartBeat)
{
	qDebug() << "1=TcpConnect ip:" << ip << ",port:" << port << ",heart beat:" << HeartBeat;
	if (m_bConnected)
		return true;
	qDebug() << "2=TcpConnect ip:" << ip << ",port:" << port << ",heart beat:" << HeartBeat;
	QByteArray ba = ip.toLocal8Bit();
	char *strIp = ba.data();
	m_fd = mc_connect(strIp, port, 0, 0);
	if (m_fd > 0)
	{
		m_bConnected = true;
		m_Timer.start(500);
		m_TimerRead.start(3000);
		emit SendConnectStatus(m_bConnected);
	}
	else
	{
		return false;
	}
	return true;
}

bool CPLCManager::WritePLCData(QString strResult,bool bTest)
{
	if (m_bConnected)
	{
		qDebug() << "CPLCManager::WritePLCData strResult = " << strResult << ",m_StartIndex" << m_StartIndex;
		if (bTest)
		{
			if (!WritePLC(strResult, "D200"))
				return false;
			if (!WritePLC(strResult, "D210"))
				return false;
		}
		if (m_StartIndex==1)
		{
			if (!WritePLC(strResult, "D200"))
			{
				qDebug() << "strResult" << strResult << ",D200 false";
				return false;
			}
				
		}
		
		if (m_StartIndex == 2)
		{
			if (!WritePLC(strResult, "D210"))//D210检测返回值
			{
				qDebug() << "strResult" << strResult << ",D210 false";
				return false;
			}

		}
		return true;
	}
	else
	{
		qDebug() << "CPLCManager::WritePLCData false";
		return false;
	}
}


bool CPLCManager::WritePLC(QString strResult,const char* Station)
{
	char *stop;
	int result =strtol(strResult.toLocal8Bit(), &stop, 2);
	if (!mc_write_short(m_fd, Station, result))
		return false;

	return true;
}



void CPLCManager::WritePLCHeartbeat()
{
	short heart = 0;
	//for (int i=0;i<5;i++)
	//{
		if (m_bConnected&&m_bReady)
		{
			qDebug() << "2 = m_bConnected " << m_bConnected << " m_bReady," << m_bReady;
			if (!mc_write_short(m_fd, "D222", 1))
				qDebug() << "WritePLCHeartbeat error";
			if (mc_read_short(m_fd, "D222", &heart))//
			{
				std::cout << "after heart:" << heart<<std::endl;
				qDebug() << "after heart:" << heart;
				//if (heart == 1)
					//break;
			}
			else
			{
				std::cout<< "heart error:" << heart << std::endl;
				qDebug() << "heart error:" << heart ;
			}
			std::cout << "heart:" << heart << std::endl;
		}

	//}
	
}

bool CPLCManager::WritePLCStartSign()
{
	short heart = 0;
	qDebug() << "CPLCManager::WritePLCStartSign() m_StartIndex" << m_StartIndex;
	if (m_StartIndex == 1)
	{
		if (!mc_write_short(m_fd, "D220", 1))//1#允许拍照
		{
			qDebug() << "write D220 false";
			return false;
		}
		if (mc_read_short(m_fd, "D220", &heart))//
		{
			qDebug() << "WritePLCStartSign1:" << heart;
		}
		else
		{
			qDebug() << "WritePLCStartSign1 error:" << heart;
		}
		return true;
	}
	else if (m_StartIndex == 2)
	{
		if (!mc_write_short(m_fd, "D221", 1))
		{
			qDebug() << "write D221 false";
			return false;
		}
		if (mc_read_short(m_fd, "D221", &heart))//
		{
			qDebug() << "WritePLCStartSign2:" << heart;
		}
		else
		{
			qDebug() << "WritePLCStartSign2 error:" << heart;
		}
		return true;
	}
	else
	{
		qDebug() << "WritePLCStartSign D220 or D221 Failed";
		return false;
	}
}

void CPLCManager::WritePLCReady(bool bReady)
{
	qDebug() << "WritePLCReady bReady = " << bReady;
	m_bReady = bReady;
}


bool CPLCManager::ReadCurrentRecipe()
{
	CurrentRecipe.Init();
	short Number=0;
	char* str_val = NULL;
	short ImageCounts = 0;
	if (!mc_read_string(m_fd, "D342", 30, &str_val))//当前配方名称
		return false;
	if (!mc_read_short(m_fd, "D341", &Number))//当前配方编号
		return false;
	if (!mc_read_short(m_fd, "D340", &ImageCounts))//当前配方拍照次数
		return false;
	QString RecipeName = QString(str_val);
	qDebug() << "ReadCurrentRecipe: " << "RecipeName = " << RecipeName << "," << "number = " << "," << Number << "ImageCounts" << ImageCounts;
	emit SendChangePLCRecipe(RecipeName, Number,ImageCounts);
}

void CPLCManager::SlotTimeOuterRead()
{
	qDebug() << "CPLCManager::SlotTimeOuter() WritePLCHeartbeat()";
	WritePLCHeartbeat();
}

void CPLCManager::ReadPLCData()
{
	qDebug() << "CPLCManager::ReadPLCData()";
	bool ret = false;
	short s_val = 0;
	short counts = 0;
	char* str_val = NULL;
	int length = 30;
	QString RecipeName;
	int number;
	//if (mc_read_short(m_fd, "D320", &s_val))//配方保存
	//{
	//	if (str_val == "1")
	//	{
	//		if (!mc_read_string(m_fd, "D", length, &str_val))
	//			qDebug() << "GetRecipeName error";


	//		if (!mc_read_short(m_fd, "D", &s_val))
	//			qDebug() << "GetRecipeNumber error";

	//		if (!mc_read_short(m_fd, "D", &counts))
	//			qDebug() << "GetRecipeCounts error";
	//		qDebug() << "ReadPLCData SendSavePLCRecipe: " << "RecipeName = " << RecipeName << "," << "number = " << "," << number << "counts" << counts;
	//		emit SendSavePLCRecipe(RecipeName, number,counts);
	//	}
	//}
	//if (mc_read_short(m_fd, "D330", &s_val))//配方切换
	//{
	//	if (str_val == "1")
	//	{
	//		if (!mc_read_string(m_fd, "D", length, &str_val))
	//			qDebug() << "GetRecipeName error";

	//		if (!mc_read_short(m_fd, "D", &s_val))
	//			qDebug() << "GetRecipeNumber error";

	//		if (!mc_read_short(m_fd, "D", &counts))
	//			qDebug() << "GetRecipeCounts error";
	//		qDebug() << "ReadPLCData SendChangePLCRecipe: " << "RecipeName = " << RecipeName << "," << "number = " << "," << number << "counts" << counts;
	//		emit SendChangePLCRecipe(RecipeName, number, counts);
	//	}
	//}
	if (mc_read_short(m_fd, "D310", &s_val))//2#开始拍照
	{
		qDebug() << "2#start D310 s_val = " << s_val;
		if (s_val)
		{
			m_StartIndex = 2;
			emit SendStartSign();
			mc_write_short(m_fd, "D310", 0); 
			//emit SendRefreshIndex();
		}

	}
	if (mc_read_short(m_fd, "D300", &s_val))//1#开始拍照
	{
		qDebug() << "1#start D300 s_val = " << s_val;
		if (s_val)
		{
			m_StartIndex = 1;
			emit SendStartSign();
			mc_write_short(m_fd, "D300", 0);
			//emit SendRefreshIndex();
		}
	}
}

void CPLCManager::SlotTimeOuter()
{
	if (!m_bConnected)
	{
		if (!m_IP.isEmpty())
		{
			//重连
			qDebug() << "reconnect ip:" << m_IP << ",port:" << m_Port;
			QByteArray ba = m_IP.toLocal8Bit();
			char *strIp = ba.data();
			m_fd = mc_connect(strIp, m_Port, 0, 0);
			m_Mutex.lock();

		}
	}
 	else
 	{
		qDebug() << "CPLCManager::SlotTimeOuter() Read()";
		//WritePLCHeartbeat();
		ReadPLCData();
 	}
}