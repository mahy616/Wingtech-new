#pragma  once
#include "qsettings.h"



const QString MODEL = "Model";
const QString INDEX = "Index";
//相机相关
const QString CAMERA_SECTION = "Camera";
const QString FIRST_CAMERA_NAME = "First_CameraName";
const QString SECOND_CAMERA_NAME = "Second_CameraName";
const QString THIRD_CAMERA_NAME = "Third_CameraName";
const QString FOURTH_CAMERA_NAME = "Fourth_CameraName";


//通讯相关
const QString COMMUNICATION_SECTOIN = "Communication";
const QString COM_STATUS = "Com_Status";
const QString IP = "Ip";
const QString HEARTBEAT = "Heartbeat";
const QString PORT = "Port";

//数据相关
const QString DATA_SECTION = "Data_Section";

const QString SAVEDAYS = "Savedays";

const QString SAVE_NG_FIRST = "Save_NG_FIRST";
const QString SAVE_OK_FIRST = "Save_OK_FIRST";
const QString NG_PATH_FIRST = "NG_Path_FIRST";
const QString OK_PATH_FIRST = "OK_Path_FIRST";
const QString FREE_GRAB_FIRST = "FREE_GRAB_FIRST";
const QString EXTERNAL_FIRST = "EXTERNAL_FIRST";
const QString SOFT_FIRST = "SOFT_FIRST";

const QString SAVE_NG_SECOND = "Save_NG_SECOND";
const QString SAVE_OK_SECOND = "Save_OK_SECOND";
const QString NG_PATH_SECOND = "NG_Path_SECOND";
const QString OK_PATH_SECOND = "OK_Path_SECOND";
const QString FREE_GRAB_SECOND = "FREE_GRAB_SECOND";
const QString EXTERNAL_SECOND = "EXTERNAL_SECOND";
const QString SOFT_SECOND = "SOFT_SECOND";

const QString SAVE_NG_THIRD = "Save_NG_THIRD";
const QString SAVE_OK_THIRD = "Save_OK_THIRD";
const QString NG_PATH_THIRD = "NG_Path_THIRD";
const QString OK_PATH_THIRD = "OK_Path_THIRD";
const QString FREE_GRAB_THIRD = "FREE_GRAB_THIRD";
const QString EXTERNAL_THIRD = "EXTERNAL_THIRD";
const QString SOFT_THIRD = "SOFT_THIRD";

const QString SAVE_NG_FOURTH = "Save_NG_FOURTH";
const QString SAVE_OK_FOURTH = "Save_OK_FOURTH";
const QString NG_PATH_FOURTH = "NG_Path_FOURTH";
const QString OK_PATH_FOURTH = "OK_Path_FOURTH";
const QString FREE_GRAB_FOURTH = "FREE_GRAB_FOURTH ";
const QString EXTERNAL_FOURTH = "EXTERNAL_FOURTH ";
const QString SOFT_FOURTH = "SOFT_FOURTH ";
//工位一阈值
const QString FIRST_THRESHOLD = "First_Threshold";

const QString FIRST_AREA_THRESHOLDZHENG = "First_Area_Thresholdzheng";
const QString FIRST_WH_THRESHOLDZHENG = "First_Wh_Thresholdzheng";

const QString FIRST_AREA_YaShang = "First_Area_YaShang";
const QString FIRST_AREA_PengShang = "First_Area_PengShang";
const QString FIRST_AREA_HuaShang = "First_Area_HuaShang";
const QString FIRST_AREA_CaShang = "First_Area_CaShang";
const QString FIRST_AREA_TieFen = "First_Area_TieFen";

const QString FIRST_WH_THRESHOLD6 = "First_Wh_Threshold6";
const QString FIRST_WH_THRESHOLD7 = "First_Wh_Threshold7";
const QString FIRST_WH_THRESHOLD8 = "First_Wh_Threshold8";
const QString FIRST_WH_THRESHOLD9 = "First_Wh_Threshold9";
const QString FIRST_WH_THRESHOLD10 = "First_Wh_Threshold10";

//身份密码
const QString ID_AND_PSWD = "ID_AND_PSWD";
const QString ADMINID = "ADMINID";
const QString ADMINPSWD = "ADMINPSWD";
const QString OPERATORID = "OPERATOR";
const QString OPERATORPSWD = "OPERATORPSWD";

//模型路径
const QString MODEL_PATH = "Model_Path";

const QString Model_Ce_Path = "Model_Ce_Path";
const QString Model_Zheng_Path = "Model_Zheng_Path";



class CConfig
{
public:
	CConfig(QString IniPath);
	~CConfig();
	bool SectionExists(QString section);
	QStringList GetChildKeys(QString Section);
	int GetInt(QString Section,QString Key);
	double GetDouble(QString Section,QString Key);
	QString GetString(QString Section,QString Key);
	bool GetBool(QString Section,QString Key);
	void Write(QString Section,QString Key,QVariant Value);
	void RemoveKey(QString Section);
private:
	QString m_IniPath;
	QSettings *m_Settings;
};