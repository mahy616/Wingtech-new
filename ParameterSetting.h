#pragma once
#include "ui_ParameterSetting.h"
#include "ImageCapture.h"
#include "QButtonGroup"
#include "QFileDialog"
#include "AlgoManager.h"
#include "SaveImage.h"
#include "QFileDialog"
#include "QDateTime"
#include "qtablewidget.h"
#include "QHeaderView"
#include "Config.h"
#include "ChangePswd.h"
#include "CRecipeManager.h"
#include "DataManager.h"
typedef struct
{
	QString CameraName;
	CMvCamera CameraHandle;
	bool bOpenCamera;
	CImageCapture *ImageCapture;
	e_CameraType CameraType;
	void Init()
	{
		CameraName.clear();
		bOpenCamera = false;
		ImageCapture = new CImageCapture();

	}
}s_CameraInfo;

typedef struct
{
	Mat image;
	bool bok;
	int time;
}s_LoadImage;

typedef struct
{
	Mat OriginalImage;
	Mat RenderImage;
	bool bok;
	std::map<int, std::string> DefectType;
}s_StationInfo;

typedef struct
{
	s_StationInfo FirstStation;
	s_StationInfo SecondStation;
	s_StationInfo ThirdStation;
	s_StationInfo FourStation;
}s_SaveImageInfo;

class CParameterSetting :public QDialog
{
	Q_OBJECT
public:
	CParameterSetting(QDialog *parent = NULL);
	~CParameterSetting();
	void StartDetecion(bool bStart);
	void SaveImage(s_SaveImageInfo ImageInfo, const e_CameraType &type,int index);
	void SaveCameraTestImage(s_SaveImageInfo ImageInfo, e_CameraType type, int m, int idx);
	void GetCameraInfo();
	void LoadConfig();
	bool SendDetectionResult(int result, QString Msg, e_CameraType &type, std::map<int, std::string> &DefectType);
	void makePath(int type,QString strData,bool makepath);
private:
	void InitVariables();
	void InitTableWidget();
	bool CloseDevice(int index);
	void InitConnections();
	void InitCamera();
	void SetButtonGroupEnabled(bool enabled, int index);
	bool OpenCamera(MV_CC_DEVICE_INFO device_info, int index);
	QImage MattoQImage(Mat image);

	void LoadModelConfig();
    int GetExposureTime(CMvCamera &CameraHandle, int index);  // ch:设置曝光时间 | en:Set Exposure Time
    int SetExposureTime(CMvCamera &CameraHandle, int index);
    int GetGain(CMvCamera &CameraHandle, int index);  // ch:设置增益 | en:Set Gain
    int SetGain(CMvCamera &CameraHandle, int index);
	void InitThreshold();

	void ShowErrorMsg(QString Message, int nErrorNum) ;
    void getCameraParams(int index);

	void InitFirstGroup();
	void InitSecondGroup();
	void InitThirdtGroup();
	void InitFourthGroup();

	void setFirstEnable(bool checked);
	void setSecondEnable(bool checked);
	void setThirdEnable(bool checked);
	void setFourthEnable(bool checked);

	void SafeParamsSetting();
	//超过日期删除指定文件
	void AutoDeleteFiles(QString path, unsigned int days);
	//如果磁盘空间不足10%提示
	bool hasEnoughSpace(const std::string &full_name);
private slots:
	void OpenFirstCamera();
	void LoadFirstImage();
	void LoadImageCe();
	void SwitchFirstCameraStatus(int index, bool checked);
    void SaveCameraParams1();
	void SaveCameraParams2();
    void SaveCameraParams3();
    void SaveCameraParams4();

	void ChooseFirstOkPath();
	void ChooseFirstNgPath();	
	void ChooseSecondOkPath();
	void ChooseSecondNgPath();
	void ChooseThirdOkPath();
	void ChooseThirdNgPath();
	void ChooseFourthOkPath();
	void ChooseFourthNgPath();

	void SaveConfig();
	void SaveConfig_2();
	void OpenSecondCamera();
	void SwitchSecondCameraStatus(int index, bool checked);
	void OpenThirdCamera();
	void SwitchThirdCameraStatus(int index, bool checked);
	void OpenFourthCamera();
	void SwitchFourthCameraStatus(int index, bool checked);
	void ReceiveConnectStatus(bool bConnected);
	void ConnectToPLC();
	void SendOKToPLC();
	void SendNGToPLC();
	void SetSystemType(int index);
	void GetFormula();
	void SetThreshold();
	void OnBtnClicked();

	void ReceiveCameraImage(Mat image, e_CameraType index, int m, int idx);
	void ReceivaOriginalImage(Mat OriginalImage, e_CameraType type, int Index);
	void SaveOriginalImage(Mat OriginalImage, e_CameraType type, int Index);

	void slotChangePswd(int index, QString m_ID, QString m_pswd);
	void slotFromChangeAdminPswd(QString id, QString pswd);
	void slotFromChangeOperatorPswd(QString id, QString pswd);
	void ReceiveCameraParameters(QVector<QVector<QString>>AllCameraParameters);
	void ReceiveLoadRenderImage(Mat image,bool e,int time);
	void SoftwareRegister();
	void CopyRegisterCode();
	void ReceiveQRcode(QString code,int index);

signals:
	void SendOriginalImage(Mat image, int index, e_CameraType type);
	void SendThreshold(vector<int> Threshold);
	void SendThresholds(vector<int> ThresholdZheng,vector<int> ThresholCe);
	void SendLoadImage(Mat OriginalImage, bool e);
	void SendCameraStatus(e_CameraType type, bool bOpened);
	void signalFromChangeAdminPswd(QString ID, QString Pswd);
	void signalFromChangeOperatorPswd(QString ID, QString Pswd);
	void SendPLCStatus(bool);
private:
	Ui::DialogSetting ui;
	s_CameraInfo m_FirstCameraInfo;
	s_CameraInfo m_SecondCameraInfo;
	s_CameraInfo m_ThirdCameraInfo;
	s_CameraInfo m_FourCameraInfo;
	QButtonGroup *m_FirstGroup;
	QButtonGroup *m_SecondGroup;
	QButtonGroup *m_ThirdGroup;
	QButtonGroup *m_FourthGroup;
	MV_CC_DEVICE_INFO_LIST m_stDevList;
	bool m_bFirstAlgoSuccess;
	Mat m_FirstOriginalImage;
	Mat m_FirstRenderImage;

	Mat m_SecondOriginalImage;
	Mat m_SecondRenderImage;

	Mat m_ThirdOriginalImage;
	Mat m_ThirdRenderImage;

	Mat m_FourthOriginalImage;
	Mat m_FourthRenderImage;
	//s_AlgoInfo m_FirstAlgo;
	CSaveImage m_SaveImage;
    // ch:曝光时间 | en:Exposure Time
    double m_dExposureEdit{0.0};
    // ch:增益 | en:Gain
    double m_dGainEdit{0.0};
    // ch:帧率 | en:Frame Rate
    double m_dFrameRateEdit{0.0};
	//相机曝光增益是否保存成功
	bool bIsSetSucceed{true};

	QTableWidget m_ModelChoice;
	QVector<QString>vtModelName;
	QPushButton* pBtn;
	QList<QPushButton*> btnPushlist;//动态创建按钮的列表

	vector<int>m_AlgoThreshold;
	vector<int>m_zhengAlgoThreshold;

	QString m_path;
	QString m_okpath1;
	QString m_ngpath1;
	QString m_okpath2;
	QString m_ngpath2;
	QString m_okpath3;
	QString m_ngpath3;
	QString m_okpath4;
	QString m_ngpath4;


	CRecipeManager *m_RecipeManager;
	int m_index{0};
	s_LoadImage m_LoadImage;
	bool m_bPLCConnected;

	bool m_bConnectedServer;
	QString m_PartNumber;

	QString m_FirstCode;
	QString m_SecondCode;
	QString m_ThirdCode;
	QString m_FourthCode;

	QString m_FirstPath;
	QString m_SecondPath;
	QString m_ThirdPath;
	QString m_FourthPath;
	bool m_MakePath;
	bool m_MakePath2;
	bool m_MakePath3;
	bool m_MakePath4;
	QString m_PathTime;
	QString m_PathTime2;
	QString m_PathTime3;
	QString m_PathTime4;
};
