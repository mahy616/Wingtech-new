/********************************************************************************
** Form generated from reading UI file 'DataManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAMANAGER_H
#define UI_DATAMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DataManager
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_DBName;
    QLineEdit *lineEdit_UserName;
    QLineEdit *lineEdit_Password;
    QPushButton *pushButton_ConnectDB;
    QLabel *label_DBStatus;
    QLineEdit *lineEdit_Code;
    QDateEdit *dateEdit_StartDate;
    QDateEdit *dateEdit_EndDate;
    QPushButton *pushButton_Query;
    QCheckBox *checkBox_Date;
    QTableWidget *tableWidget;
    QPushButton *pushButton_clear;

    void setupUi(QDialog *DataManager)
    {
        if (DataManager->objectName().isEmpty())
            DataManager->setObjectName(QString::fromUtf8("DataManager"));
        DataManager->resize(920, 742);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CMainWindow/Resources/data.png"), QSize(), QIcon::Normal, QIcon::Off);
        DataManager->setWindowIcon(icon);
        gridLayout_3 = new QGridLayout(DataManager);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        groupBox = new QGroupBox(DataManager);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setMaximumSize(QSize(800, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lineEdit_DBName = new QLineEdit(groupBox);
        lineEdit_DBName->setObjectName(QString::fromUtf8("lineEdit_DBName"));

        gridLayout->addWidget(lineEdit_DBName, 0, 0, 1, 1);

        lineEdit_UserName = new QLineEdit(groupBox);
        lineEdit_UserName->setObjectName(QString::fromUtf8("lineEdit_UserName"));

        gridLayout->addWidget(lineEdit_UserName, 0, 1, 1, 1);

        lineEdit_Password = new QLineEdit(groupBox);
        lineEdit_Password->setObjectName(QString::fromUtf8("lineEdit_Password"));
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEdit_Password, 0, 2, 1, 1);

        pushButton_ConnectDB = new QPushButton(groupBox);
        pushButton_ConnectDB->setObjectName(QString::fromUtf8("pushButton_ConnectDB"));

        gridLayout->addWidget(pushButton_ConnectDB, 0, 3, 1, 1);

        label_DBStatus = new QLabel(groupBox);
        label_DBStatus->setObjectName(QString::fromUtf8("label_DBStatus"));
        label_DBStatus->setMinimumSize(QSize(21, 21));
        label_DBStatus->setMaximumSize(QSize(21, 21));
        label_DBStatus->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);"));

        gridLayout->addWidget(label_DBStatus, 0, 4, 1, 1);

        lineEdit_Code = new QLineEdit(groupBox);
        lineEdit_Code->setObjectName(QString::fromUtf8("lineEdit_Code"));

        gridLayout->addWidget(lineEdit_Code, 1, 0, 1, 1);

        dateEdit_StartDate = new QDateEdit(groupBox);
        dateEdit_StartDate->setObjectName(QString::fromUtf8("dateEdit_StartDate"));
        dateEdit_StartDate->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_StartDate, 1, 1, 1, 1);

        dateEdit_EndDate = new QDateEdit(groupBox);
        dateEdit_EndDate->setObjectName(QString::fromUtf8("dateEdit_EndDate"));
        dateEdit_EndDate->setCalendarPopup(true);

        gridLayout->addWidget(dateEdit_EndDate, 1, 2, 1, 1);

        pushButton_Query = new QPushButton(groupBox);
        pushButton_Query->setObjectName(QString::fromUtf8("pushButton_Query"));

        gridLayout->addWidget(pushButton_Query, 1, 3, 1, 1);

        checkBox_Date = new QCheckBox(groupBox);
        checkBox_Date->setObjectName(QString::fromUtf8("checkBox_Date"));

        gridLayout->addWidget(checkBox_Date, 1, 4, 1, 1);

        tableWidget = new QTableWidget(groupBox);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 2, 0, 1, 5);

        pushButton_clear = new QPushButton(groupBox);
        pushButton_clear->setObjectName(QString::fromUtf8("pushButton_clear"));

        gridLayout->addWidget(pushButton_clear, 3, 3, 1, 2);


        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        retranslateUi(DataManager);
        QObject::connect(pushButton_ConnectDB, SIGNAL(clicked()), DataManager, SLOT(ConnectToDB()));
        QObject::connect(pushButton_Query, SIGNAL(clicked()), DataManager, SLOT(QueryData()));
        QObject::connect(checkBox_Date, SIGNAL(clicked(bool)), DataManager, SLOT(SetDateEnabled(bool)));
        QObject::connect(tableWidget, SIGNAL(clicked(QModelIndex)), DataManager, SLOT(ClickedOnTableWidget(QModelIndex)));
        QObject::connect(pushButton_clear, SIGNAL(clicked()), DataManager, SLOT(ClearData()));

        QMetaObject::connectSlotsByName(DataManager);
    } // setupUi

    void retranslateUi(QDialog *DataManager)
    {
        DataManager->setWindowTitle(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\346\237\245\350\257\242", nullptr));
        lineEdit_DBName->setText(QCoreApplication::translate("DataManager", "QRCodeDataResult", nullptr));
        lineEdit_DBName->setPlaceholderText(QCoreApplication::translate("DataManager", "\346\225\260\346\215\256\345\272\223\345\220\215\347\247\260", nullptr));
        lineEdit_UserName->setText(QCoreApplication::translate("DataManager", "my", nullptr));
        lineEdit_UserName->setPlaceholderText(QCoreApplication::translate("DataManager", "\347\224\250\346\210\267\345\220\215", nullptr));
        lineEdit_Password->setText(QCoreApplication::translate("DataManager", "123456", nullptr));
        lineEdit_Password->setPlaceholderText(QCoreApplication::translate("DataManager", "\345\257\206\347\240\201", nullptr));
        pushButton_ConnectDB->setText(QCoreApplication::translate("DataManager", "\350\277\236\346\216\245", nullptr));
        label_DBStatus->setText(QString());
        lineEdit_Code->setPlaceholderText(QCoreApplication::translate("DataManager", "\346\226\231\345\217\267", nullptr));
        dateEdit_StartDate->setDisplayFormat(QCoreApplication::translate("DataManager", "yyyy-MM-dd hh:mm:ss", nullptr));
        dateEdit_EndDate->setDisplayFormat(QCoreApplication::translate("DataManager", "yyyy-MM-dd hh:mm:ss", nullptr));
        pushButton_Query->setText(QCoreApplication::translate("DataManager", "\346\237\245\350\257\242", nullptr));
        checkBox_Date->setText(QCoreApplication::translate("DataManager", "\346\227\266\351\227\264", nullptr));
        pushButton_clear->setText(QCoreApplication::translate("DataManager", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataManager: public Ui_DataManager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAMANAGER_H
