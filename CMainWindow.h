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
	//每张图像
	QVector<QImage> m_Camera1Images;
	QVector<QImage> m_Camera2Images;
	QVector<QImage> m_Camera3Images;
	QVector<QImage> m_Camera4Images;
	//结果明细
	QVector<QLabel *> m_Camera1Results;
	QVector<QLabel *> m_Camera2Results;
	QVector<QLabel *> m_Camera3Results;
	QVector<QLabel *> m_Camera4Results;

	QVector<Mat> m_MatCamera1Images;
	//每组图最终结果
	bool m_Camera1Result;
	bool m_Camera2Result;
	bool m_Camera3Result;
	bool m_Camera4Result;

	//检测最终结果
	QLabel *m_TotalResult;
	QLabel *m_FirstResult;
	QLabel *m_SecondResult;
	QLabel *m_ThirdResult;
	QLabel *m_FourthResult;
	StatisticsWidget *m_Statistics;
	QListView *m_ListView;
	QStandardItemModel *m_LogModel;
	QPushButton *m_ListViewClear;
	
	//检测结果
	QMap<e_CameraType, bool> m_DetecionResult;

	//状态栏
	QLabel m_PLC;
	QLabel m_Camera1;
	QLabel m_Camera2;
	QLabel m_Camera3;
	QLabel m_Camera4;
	QLabel *Logo;
	QLabel *Logo2;

	//int m_Number;
	int m_Index;        //界面图像数量统计
	bool m_bStart;
	bool m_Ready;
	int m_ImageCounts;  //界面图像数量

	std::map<int, std::string> m_FitstDefectType;
	std::map<int, std::string> m_SecondDefectType;
	std::map<int, std::string> m_ThirdDefectType;
	std::map<int, std::string> m_FourthDefectType;



private:
	void InitVariables();
	void InitStatusBar();
	void InitConnections();
	void SendPLCResult(QString strResult);
	QImage MattoQImage(Mat image);
	void ProcessDetectionResult();
	void AddLog(QString log);
	void setActionEnable(bool bok);
	//初始化结果明细
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
	void OpenDataManager();

	//接收相机状态
	void ReceiveCameraStatus(e_CameraType type, bool bOpen);
	//接收PLC状态
	void ReceivePLCStatus(bool bConnected);
	void ReceiveAlgoImage(s_ImageInfo ImageInfo,bool isClean);
	//接受PLC发送的初始化图片数量
	void ReceiveInitImageNumber(int number); 
	//接收PLC发送的起始拍照信号
	void ReceiveStartSign();



};
