#pragma once
#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QMutex>
#include "melsec_mc_bin.h"
#include <iostream >
#include<cstdio>
//using namespace std;

typedef struct
{
	int CurrentMachineNumber;
	int CurrentRecipeNumber;
	QString CurrentRecipeName;
	void Init()
	{
		CurrentMachineNumber=0;
		CurrentRecipeNumber=0;
		CurrentRecipeName ="";
	}
}s_CurrentRecipe;


class CPLCManager :public QObject
{
	Q_OBJECT
public:
	static CPLCManager *GetInstance();
	bool TcpConnect(QString ip, quint16 port,int HeartBeat);
		//断开连接
	//	void TcpDisconnect();
	bool GetConnectStatus() { return m_bConnected; }
	//bool GetPLCInitStatus() { return m_bInitPLCSuccess; }
	bool WritePLCData(QString strResult, bool bTest);
	void WritePLCReady(bool bReady);
	bool ReadCurrentRecipe();
	bool WritePLCStartSign();
private:
	//PLC写操作
	bool WritePLC(QString strResult, const char* Station);
	void WritePLCHeartbeat();
	
	QTime m_time;


private:
	CPLCManager(QObject *parent = NULL);
	~CPLCManager();
	static CPLCManager *m_Instace;
	QString m_IP;
	quint16 m_Port;
	//网络连接标志
	bool m_bConnected;
	//PLC初始化成功标志
	//bool m_bInitPLCSuccess;
	QTimer m_Timer;
	QTimer m_TimerRead;
	int m_HeartBeat;
	QMutex m_Mutex;
	QString m_HexLastHost; //PC端IP最后部分的16进制
	QString m_HexLastServer; //PLC端IP最后部分的16进制
	s_CurrentRecipe CurrentRecipe;
	int m_StartIndex;
	int m_fd;
	int m_c;
	bool m_bReady;
private slots:
	void SlotTimeOuter();
	void SlotTimeOuterRead();
	void ReadPLCData();
signals:
	void SendConnectStatus(bool status);
	void SendPLCMessage(QString msg);
	void SendChangePLCRecipe(QString msg, int number,int ImageCounts);
	void SendSavePLCRecipe(QString msg, int number, int ImageCounts);
	void SendStartSign();
	void SendRefreshIndex();
};