#include "windows.h"
#include "SaveImage.h"
#include "QDebug"

CSaveImage::CSaveImage(QThread *parent /* = NULL */)
	:QThread(parent)
{
	m_ImageList.clear();
	m_bStop = false;
}

void CSaveImage::SaveImage(QString FileName, Mat Image,int index)
{
	m_Mutex.lock();
	s_SaveInfo SaveInfo;
	FileName.remove(QRegExp("\\s"));
	SaveInfo.FileName = FileName;
	SaveInfo.Image = Image.clone();// .clone();
	m_ImageList.push_back(SaveInfo);
	qDebug() << "save image index:" << index;
	m_Mutex.unlock();
}

void CSaveImage::StopThread()
{
	m_Mutex.lock();
	m_bStop = true;
	m_Mutex.unlock();
}

void CSaveImage::run()
{
	while (1)
	{
		m_Mutex.lock();
		bool bStop = m_bStop;
		m_Mutex.unlock();
		if (bStop)
		{
			break;
		}
		if (m_ImageList.size() > 0)
		{
			m_Mutex.lock();
			s_SaveInfo SaveInfo = m_ImageList.dequeue();
			m_Mutex.unlock();
			qDebug() << "save image name:" << SaveInfo.FileName;
			QByteArray ba = SaveInfo.FileName.toLocal8Bit();//Unicode
			char *file = ba.data();
			try 
			{
				bool rv = false;
				if (!SaveInfo.Image.empty())
				{
					rv = imwrite(file, SaveInfo.Image.clone());
					if (rv)
					{
						qDebug() << "save image success:" << file;
					}
				}
			}
			catch (cv::Exception& e)
			{
				const char* err_msg = e.what();
				qDebug() << "save image failed:" << file;
			}
		}
		else
		{
			Sleep(10);
		}
	}
	m_ImageList.clear();
}