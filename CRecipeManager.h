#pragma once
#include <QtWidgets/QDialog>
#include "ui_CRecipeManager.h"
#include "QMap"
#include "AlgoManager.h"
#include "PLCManager.h"
#include "Config.h"
//#include "ImageCapture.h"
class CRecipeManager : public QDialog
{
	Q_OBJECT
public:
	CRecipeManager(QWidget *parent = Q_NULLPTR);
	//��ȡ�����䷽�������ص������б���
	void InitRecipeNames();
	//�����㷨,TODO������Ͳ���
	void RunAlgo(Mat Image, int ImageID, e_CameraType type);
	//PLC��ȡ���䷽���ƣ����ػ�����һ�������Ƶ�ini�ļ�
	void SaveRecipeFromPLC(QString RecipeName, int RecipeNumber, int ImageCount);
	//��ʼ���䷽����ʼ���ɹ�����true��֪ͨPLC Ready�źţ����򷵻�false������log��ʾ���������Ϣ
	bool InitRecipe(QString RecipeNumber, QString RecipeName);
	void InitConnections();
	bool SendPLCReadySign(bool bReady);
	int GetImageCounts();
	
public:
	CAlgoManager* m_FirstGpuAlgo;
	CAlgoManager* m_SecondGpuAlgo;
	CAlgoManager* m_ThirdGpuAlgo;
	CAlgoManager* m_FourGpuAlgo;
private:
	void InitVariables();
	void updateTableInfos(void);
	void SetCameraParameters(CConfig *cfg);
	void SaveCameraParameters(CConfig *cfg);
	QStringList getFileNames(const QString &path);

private:
	Ui::CRecipeManagerClass ui;
	//ͼ��ID��Ӧģ�ͱ�
	QMap<int, QString> m_ImageAndModel;
	QMap<QString, CAlgoManager*> m_ModelAndAlgo;

	bool m_Ready;
	int m_ImageID;  //ͼ��ID
	int m_ImageCounts;   //�䷽��ͼ�����
	int m_Number;   //�䷽��ͼ�����
	s_ImageInfo ImageInfo;
	vector<int>m_AlgoThreshold;
	bool m_InitRecipe;
	int m_LastIndex;
	QMutex m_mutex;

	QString m_ce_path;
	QString m_zheng_path;
signals:
	void SendStartSign();
	void SendCameraParameters(QVector<QVector<QString>>AllCameraParameters);
	void SendLoadRenderImage(Mat image,bool e,int time);
signals:
	void SendAlgoImageFromRecipe(s_ImageInfo ImageInfo, bool isClean);
private slots:
	//�л��䷽����ȡ�����ļ���Tabwidget��ʾ��������
	void SwitchRecipe(QString Name);
	//�����䷽�������ͼ��IDû��ѡ��ģ�ͣ����ܱ���
	void SaveRecipe();
	//ɾ���䷽, ɾ��ѡ�е��䷽
	void RemoveRecipe();
	//���ģ��
	void BrowseModelPath();
	//PLC���������䷽
	void ReceiveSavePlcRecipe(QString msg, int number, int ImageCounts);
	//PLC�����л��䷽
	void ReceiveChangePlcRecipe(QString msg, int number, int ImageCounts);
	//����Դͼ
	void ReceivaOriginalImage(Mat Image, int ImageID, e_CameraType Type);
	//�����㷨��Ⱦͼ
	//void ReceivaAlgoImage(Mat image, Mat RenderImage, int index, bool bOK, e_CameraType type);
	void ReceivaAlgoImage(s_ImageInfo ImageInfo);
	//���ܿ�ʼ�����ź�
	void ReceiveStartSign();
	//������ֵ��������ź�
	void ReceiveAlgoThreshold(vector<int> AlgoThresholdZheng, vector<int> AlgoThresholdCe);
	void ReceiveOffLineAlgoThreshold(vector<int> AlgoThreshold);
	void ReceiveLoadImage(Mat image, bool e);
};
