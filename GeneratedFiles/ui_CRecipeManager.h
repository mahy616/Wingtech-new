/********************************************************************************
** Form generated from reading UI file 'CRecipeManager.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRECIPEMANAGER_H
#define UI_CRECIPEMANAGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_CRecipeManagerClass
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QLabel *label;
    QTableWidget *tableWidget;
    QComboBox *comboBox;
    QTableWidget *tableWidget_Camear;
    QPushButton *pushButton_remove;

    void setupUi(QDialog *CRecipeManagerClass)
    {
        if (CRecipeManagerClass->objectName().isEmpty())
            CRecipeManagerClass->setObjectName(QString::fromUtf8("CRecipeManagerClass"));
        CRecipeManagerClass->resize(859, 638);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/CRecipeManager/Resources/recipe.png"), QSize(), QIcon::Normal, QIcon::Off);
        CRecipeManagerClass->setWindowIcon(icon);
        CRecipeManagerClass->setStyleSheet(QString::fromUtf8("font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        gridLayout = new QGridLayout(CRecipeManagerClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSpacer = new QSpacerItem(378, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        pushButton = new QPushButton(CRecipeManagerClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 4, 1, 1);

        label = new QLabel(CRecipeManagerClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        tableWidget = new QTableWidget(CRecipeManagerClass);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 5);

        comboBox = new QComboBox(CRecipeManagerClass);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setMinimumSize(QSize(300, 0));

        gridLayout->addWidget(comboBox, 0, 1, 1, 1);

        tableWidget_Camear = new QTableWidget(CRecipeManagerClass);
        tableWidget_Camear->setObjectName(QString::fromUtf8("tableWidget_Camear"));
        tableWidget_Camear->setMaximumSize(QSize(16777215, 200));

        gridLayout->addWidget(tableWidget_Camear, 2, 0, 1, 5);

        pushButton_remove = new QPushButton(CRecipeManagerClass);
        pushButton_remove->setObjectName(QString::fromUtf8("pushButton_remove"));

        gridLayout->addWidget(pushButton_remove, 0, 3, 1, 1);


        retranslateUi(CRecipeManagerClass);
        QObject::connect(comboBox, SIGNAL(activated(QString)), CRecipeManagerClass, SLOT(SwitchRecipe(QString)));
        QObject::connect(pushButton, SIGNAL(clicked()), CRecipeManagerClass, SLOT(SaveRecipe()));
        QObject::connect(pushButton_remove, SIGNAL(clicked()), CRecipeManagerClass, SLOT(RemoveRecipe()));

        QMetaObject::connectSlotsByName(CRecipeManagerClass);
    } // setupUi

    void retranslateUi(QDialog *CRecipeManagerClass)
    {
        CRecipeManagerClass->setWindowTitle(QCoreApplication::translate("CRecipeManagerClass", "\351\205\215\346\226\271\347\256\241\347\220\206", nullptr));
        pushButton->setText(QCoreApplication::translate("CRecipeManagerClass", "\344\277\235\345\255\230\351\205\215\346\226\271", nullptr));
        label->setText(QCoreApplication::translate("CRecipeManagerClass", "\351\205\215\346\226\271\345\210\207\346\215\242", nullptr));
        pushButton_remove->setText(QCoreApplication::translate("CRecipeManagerClass", "\347\247\273\351\231\244\351\205\215\346\226\271", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CRecipeManagerClass: public Ui_CRecipeManagerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRECIPEMANAGER_H
