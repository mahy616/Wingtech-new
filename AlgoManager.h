#pragma once
#include "QObject"
#include "QThread"
#include "qmutex.h"
#include "QQueue"
#include "opencv2/opencv.hpp"
#include "VimoDetectionModule.h"
#include "ImageCapture.h"
#include "ISegmentationModule.h"
#include "wentai_zheng_mian_module.h"
#include "wentai_ce_mian_module.h"
#include "vector"

using namespace std;
using namespace cv;
using namespace smartmore;
typedef struct
{
	Mat OriginalImage;
	Mat RenderImage;
	std::map<int, std::string> DefectType;
	e_CameraType Type;
	bool bok;
	int ImageID;
}s_ImageInfo;

class CAlgoManager :public QThread
{
	Q_OBJECT
public:
	CAlgoManager(QThread *parent = NULL);
	~CAlgoManager();
	bool InitAlgo(int GpuIndex, String ZhengPath, String CePath);
	void RunAlgo(s_ImageInfo ImageInfo);
	void RunAlgoOffline(Mat &Image,bool &bce,int &Time);
	void StopAlgo();
	void GetAlgoThresholdOffLine(vector<int>AlgoThreshold);
	void GetAlgoThreshold(vector<int> AlgoThresholdZheng, vector<int> AlgoThresholdCe);
	Mat convertTo3Channels(const Mat& binImg);
	void SetImage(std::map<int, std::string> names, std::map<int, size_t> nums,Mat &RenderImage);
	void Algo(s_ImageInfo ImageInfo);
private:
	QQueue<s_ImageInfo> m_ImageInfos;
	bool m_bStop;
	QMutex m_mutex;
	//smartmore::WenTaiZhengMianModule firstGpuZhengModule;
	//smartmore::WenTaiCeMianModule firstGpuCeModule;
	//smartmore::WenTaiZhengMianModule secondGpuZhengModule;
	//smartmore::WenTaiCeMianModule secondGpuCeModule;
	smartmore::WenTaiZhengMianModule ZhengModule;
	smartmore::WenTaiCeMianModule CeModule;
	vector<int> m_AlgoThreshold;
	vector<int> m_zhengAlgoThreshold;

private:
	void run();
signals:
	void SendPorcessResult(s_ImageInfo ImageInfo);
	void SendTempImages(s_ImageInfo ImageInfo);
};