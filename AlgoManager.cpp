#include <windows.h>
#include "AlgoManager.h"
#include "QTime"
#include "QCoreApplication"

CAlgoManager::CAlgoManager(QThread *parent)
	:QThread(parent)
{
	m_bStop = false;
}

CAlgoManager::~CAlgoManager()
{

}

bool CAlgoManager::InitAlgo(int GpuIndex, String ZhengPath, String CePath)
{
	smartmore::SegmentationRequest req;
	smartmore::WenTaiCeMianResponse rspce;
	smartmore::WenTaiZhengMianResponse rspzheng;
	smartmore::ResultCode res;
	QString zheng_image = QCoreApplication::applicationDirPath() + "/data/zheng.bmp";
	QString ce_image = QCoreApplication::applicationDirPath() + "/data/ce.bmp";
	QByteArray z = zheng_image.toLocal8Bit();
	QByteArray c = ce_image.toLocal8Bit();
	char *file = z.data();
	char *file1 = c.data();
	Mat zhengImage = imread(file,1);
	Mat ceImage = imread(file1, 1);

	if (ZhengModule.Init(ZhengPath, true, GpuIndex) == smartmore::ResultCode::Success)
	{
		req.image = zhengImage;
		res = ZhengModule.Run(req, rspzheng);
		if (res != smartmore::ResultCode::Success)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	if (CeModule.Init(CePath, true, GpuIndex) == smartmore::ResultCode::Success)
	{
		req.image = ceImage;
		res = CeModule.Run(req, rspce);
		if (res != smartmore::ResultCode::Success)
		{
			return false;
		}
	}
	else
	{
		return false;
	}
	
	std::cout << "Init module success!" << std::endl;
	qDebug() << "InitAlgo success";
	return true;
}

void CAlgoManager::RunAlgo(s_ImageInfo ImageInfo)
{
	m_mutex.lock();
	qDebug() << "m_ImageInfosindex:" << ImageInfo.ImageID - 1 << endl;
	m_ImageInfos.push_back(ImageInfo);
	m_mutex.unlock();
	qDebug() << "m_ImageInfos.push_back size()" << m_ImageInfos.size();
}

void CAlgoManager::RunAlgoOffline(Mat &Image,bool &bce,int &Time)
{
	QTime time;
	bool bok=true;
	Mat RenderImage;
	smartmore::SegmentationRequest req;
	smartmore::WenTaiCeMianResponse rspce;
	smartmore::WenTaiZhengMianResponse rspzheng;
	if (req.image.channels() == 1)
	{
		req.image = convertTo3Channels(Image);
	}

	smartmore::ResultCode res;
	std::map<int, std::string> names;
	std::map<int, size_t> nums;
	time.start();
	if (!bce)
	{
		req.thresholds = m_zhengAlgoThreshold;
		qDebug() << "m_zhengAlgoThreshold  " << m_zhengAlgoThreshold << "req.thresholds" << req.thresholds;

		res = ZhengModule.Run(req, rspzheng);
		if (res != smartmore::ResultCode::Success)
		{
			qDebug() << "Position1 Normal run Failure.";
		}
		else
		{
			ZhengModule.Visualize(req, rspzheng, RenderImage);
			if (rspzheng.code != smartmore::QCCode::OK)
			{
				SetImage(rspzheng.names, rspzheng.nums, RenderImage);
				bok = false;
			}

			qDebug() << "smartmore::ResultCode1::Success";
		};
	}
	else
	{
		req.thresholds = m_AlgoThreshold;
		qDebug() << " m_AlgoThreshold " << m_AlgoThreshold << "req.thresholds" << req.thresholds;
		res = CeModule.Run(req, rspce);
		if (res != smartmore::ResultCode::Success)
		{
			qDebug() << "Position2 Normal run Failure.";
		}
		else
		{
			CeModule.Visualize(req, rspce, RenderImage);
			
			if (rspce.code != smartmore::QCCode::OK)
			{
				SetImage(rspce.names, rspce.nums, RenderImage);
				bok = false;
			}

			qDebug() << "smartmore::ResultCode2::Success";
		};
	}
	int AlgoTime = time.elapsed();
	cout << "AlgoTime : " << AlgoTime << endl;
	Image = RenderImage.clone();
	bce=bok;
	Time = AlgoTime;
}

void CAlgoManager::StopAlgo()
{
	m_mutex.lock();
	m_bStop = true;
	m_mutex.unlock();
}


void CAlgoManager::GetAlgoThresholdOffLine(vector<int> AlgoThreshold)
{
	m_mutex.lock();
	if (AlgoThreshold.size() > 2)
	{
		m_AlgoThreshold = AlgoThreshold;
	}
	else
	{
		m_zhengAlgoThreshold = AlgoThreshold;
	}
	m_mutex.unlock();
}

void CAlgoManager::GetAlgoThreshold(vector<int> AlgoThresholdZheng, vector<int> AlgoThresholdCe)
{
	qDebug() << "GetAlgoThreshold : " << " AlgoThresholdZheng " << AlgoThresholdZheng << " AlgoThresholdCe " << AlgoThresholdCe;
	m_mutex.lock();
	m_AlgoThreshold = AlgoThresholdCe;
	m_zhengAlgoThreshold = AlgoThresholdZheng;
	m_mutex.unlock();
	qDebug() << "GetAlgoThreshold : " << " m_AlgoThreshold " << m_AlgoThreshold << " m_zhengAlgoThreshold " << m_zhengAlgoThreshold;
}

void CAlgoManager::run()
{	
	while (!m_bStop)
	{
		if (m_ImageInfos.size() == 0)
		{
			Sleep(10);
			continue;
		}
		m_mutex.lock();
		qDebug() << "m_ImageInfos.size() = " << m_ImageInfos.size();
		s_ImageInfo ImageInfo = m_ImageInfos.dequeue();
		qDebug() << "ImageInfoindex:" << ImageInfo.ImageID - 1 << endl;
		qDebug() << "m_ImageInfos.size() = " << m_ImageInfos.size();
		m_mutex.unlock();
		Algo(ImageInfo);
	}
}


Mat CAlgoManager::convertTo3Channels(const Mat& binImg)
{
	Mat three_channel = Mat::zeros(binImg.rows, binImg.cols, CV_8UC3);
	vector<Mat> channels;
	for (int i = 0; i < 3; i++)
	{
		channels.push_back(binImg);
	}
	merge(channels, three_channel);
	return three_channel;
}

void CAlgoManager::SetImage(std::map<int, std::string> names, std::map<int, size_t> nums, Mat & RenderImage )
{
	map<int, std::string>::iterator iter;
	int p = 0;
	for (iter = names.begin(); iter != names.end(); iter++)
	{
		int index = iter->first;
		string strData = iter->second;
		size_t TypeNums = nums[index];
		string outData = "Type:" + strData +"; Number:" +std::to_string(TypeNums);
		putText(RenderImage, outData, Point(1500, RenderImage.rows - (p * 100)), FONT_HERSHEY_COMPLEX, 2, Scalar(255, 255, 255), 3, 8);
		p++;
	}
}

void CAlgoManager::Algo(s_ImageInfo ImageInfo)
{
	QTime time;
	ImageInfo.bok = true;
	smartmore::SegmentationRequest req;
	smartmore::WenTaiCeMianResponse rspce;
	smartmore::WenTaiZhengMianResponse rspzheng;
	if (req.image.channels() == 1)
	{
		req.image = convertTo3Channels(ImageInfo.OriginalImage.clone());
	}
	smartmore::ResultCode res;
	std::map<int, std::string> names;
	std::map<int, size_t> nums;
	time.start();
	if (ImageInfo.ImageID < 13)
		{
			
			req.thresholds = m_zhengAlgoThreshold;
			qDebug() << "Begin Run zheng";
			res = ZhengModule.Run(req, rspzheng);
			qDebug() << "End Run zheng";
			qDebug() << "CAMERA_1_2 m_zhengAlgoThreshold " << m_zhengAlgoThreshold << " req.thresholds  " << req.thresholds;
			
			if (res != smartmore::ResultCode::Success)
			{
				qDebug() << "firstGpuZhengModule run error!";
				return;
			}
			else
			{
				ZhengModule.Visualize(req, rspzheng, ImageInfo.RenderImage);
				if (rspzheng.code != smartmore::QCCode::OK)
				{
					SetImage(rspzheng.names, rspzheng.nums, ImageInfo.RenderImage);
					ImageInfo.DefectType = rspzheng.names;
					ImageInfo.bok = false;
					qDebug() << "ImageInfo.Type" << ImageInfo.Type << "ImageInfo.ImageID" << ImageInfo.ImageID << "ng";
				}
				else
				{
					qDebug() << "ImageInfo.Type" << ImageInfo.Type << "ImageInfo.ImageID" << ImageInfo.ImageID << "ok";
				}
			};
		}
	else
	{
		req.thresholds = m_AlgoThreshold;
		qDebug() << "Begin Run Ce";
		res = CeModule.Run(req, rspce);
		qDebug() << "End Run Ce";
		qDebug() << "CAMERA_1_2 m_AlgoThreshold " << m_AlgoThreshold << " req.thresholds " << req.thresholds;
		if (res != smartmore::ResultCode::Success)
		{
			qDebug() << "firstGpuCeModule run error!";
			return;
		}
		else
		{
			CeModule.Visualize(req, rspce, ImageInfo.RenderImage);
			if (rspce.code != smartmore::QCCode::OK)
			{
				SetImage(rspce.names, rspce.nums, ImageInfo.RenderImage);
				ImageInfo.DefectType = rspce.names;
				ImageInfo.bok = false;
				qDebug() << "ImageInfo.Type" << ImageInfo.Type << "ImageInfo.ImageID" << ImageInfo.ImageID << "ng";
			}
			else
			{
				qDebug() << "ImageInfo.Type" << ImageInfo.Type << "ImageInfo.ImageID" << ImageInfo.ImageID << "ok";
			}
		};
	}

	int AlgoTime = time.elapsed();
	cout << "AlgoTime:" << AlgoTime << endl;
	qDebug() << "Total AlgoTime: " << AlgoTime;
	ImageInfo.ImageID = ImageInfo.ImageID - 1;
	
	emit SendPorcessResult(ImageInfo);
	qDebug() << "AlgoManagerindex:" << ImageInfo.ImageID << endl;
}
