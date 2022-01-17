#pragma once

#include <QtWidgets/QMainWindow>
#include <QLabel>
#include <QListView>
#include <QStandardItemModel>
#include "ui_CMainWindow.h"
#include "statisticswidget.h"
#include <opencv2/opencv.hpp>
#include "ParameterSetting.h"
#include "CRecipeManager.h"
#include "adminLoginDialog.h"

using namespace std;
using namespace cv;





class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = Q_NULLPTR);
	~CMainWindow();
private:
	//ÿ��ͼ��
	QVector<QImage> m_Camera1Images;
	QVector<QImage> m_Camera2Images;
	QVector<QImage> m_Camera3Images;
	QVector<QImage> m_Camera4Images;
	//�����ϸ
	QVector<QLabel *> m_Camera1Results;
	QVector<QLabel *> m_Camera2Results;
	QVector<QLabel *> m_Camera3Results;
	QVector<QLabel *> m_Camera4Results;

	QVector<Mat> m_MatCamera1Images;
	//ÿ��ͼ���ս��
	bool m_Camera1Result;
	bool m_Camera2Result;
	bool m_Camera3Result;
	bool m_Camera4Result;

	//������ս��
	QLabel *m_TotalResult;
	QLabel *m_FirstResult;
	QLabel *m_SecondResult;
	QLabel *m_ThirdResult;
	QLabel *m_FourthResult;
	StatisticsWidget *m_Statistics;
	QListView *m_ListView;
	QStandardItemModel *m_LogModel;
	QPushButton *m_ListViewClear;
	
	//�����
	QMap<e_CameraType, bool> m_DetecionResult;

	//״̬��
	QLabel m_PLC;
	QLabel m_Camera1;
	QLabel m_Camera2;
	QLabel m_Camera3;
	QLabel m_Camera4;
	QLabel *Logo;
	QLabel *Logo2;

	//int m_Number;
	int m_Index;        //����ͼ������ͳ��
	bool m_bStart;
	bool m_Ready;
	int m_ImageCounts;  //����ͼ������
private:
	void InitVariables();
	void InitStatusBar();
	void InitConnections();
	void SendPLCResult(QString strResult);
	QImage MattoQImage(Mat image);
	void ProcessDetectionResult();
	void AddLog(QString log);
	void setActionEnable(bool bok);
	//��ʼ�������ϸ
	void InitResultDetails();
	void RefreshResultDetails();

private:
	Ui::CMainWindowClass ui;
	CParameterSetting *m_Parameter;
	CRecipeManager *m_RecipeManager;
	adminLoginDialog *m_admin;
	QPushButton *btn_Clear;
	QMutex m_Mutex;
protected:
	bool eventFilter(QObject *obj, QEvent *event);
private slots:
	void StartDection();
	void StopDection();
	void OpenSetting();
	void RecipeSetting();
	void AdminDection();

	//�������״̬
	void ReceiveCameraStatus(e_CameraType type, bool bOpen);
	//����PLC״̬
	void ReceivePLCStatus(bool bConnected);
	void ReceiveAlgoImage(s_ImageInfo ImageInfo,bool isClean);
	//����PLC���͵ĳ�ʼ��ͼƬ����
	void ReceiveInitImageNumber(int number); 
	//����PLC���͵���ʼ�����ź�
	void ReceiveStartSign();



};
