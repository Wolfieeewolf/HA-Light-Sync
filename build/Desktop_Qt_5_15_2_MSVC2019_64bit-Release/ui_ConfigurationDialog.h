/********************************************************************************
** Form generated from reading UI file 'ConfigurationDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURATIONDIALOG_H
#define UI_CONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConfigurationDialog
{
public:
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *urlLabel;
    QLineEdit *urlEdit;
    QLabel *tokenLabel;
    QLineEdit *tokenEdit;
    QHBoxLayout *horizontalLayout_1;
    QPushButton *connectButton;
    QLabel *statusLabel;
    QGroupBox *lightsGroup;
    QVBoxLayout *verticalLayout_2;
    QTreeWidget *lightsList;
    QHBoxLayout *horizontalLayout;
    QPushButton *refreshButton;
    QPushButton *addSelectedButton;
    QGroupBox *activeGroup;
    QVBoxLayout *verticalLayout_3;
    QListWidget *activeList;
    QPushButton *removeButton;

    void setupUi(QWidget *ConfigurationDialog)
    {
        if (ConfigurationDialog->objectName().isEmpty())
            ConfigurationDialog->setObjectName(QString::fromUtf8("ConfigurationDialog"));
        ConfigurationDialog->resize(400, 500);
        verticalLayout = new QVBoxLayout(ConfigurationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        urlLabel = new QLabel(ConfigurationDialog);
        urlLabel->setObjectName(QString::fromUtf8("urlLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, urlLabel);

        urlEdit = new QLineEdit(ConfigurationDialog);
        urlEdit->setObjectName(QString::fromUtf8("urlEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, urlEdit);

        tokenLabel = new QLabel(ConfigurationDialog);
        tokenLabel->setObjectName(QString::fromUtf8("tokenLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, tokenLabel);

        tokenEdit = new QLineEdit(ConfigurationDialog);
        tokenEdit->setObjectName(QString::fromUtf8("tokenEdit"));
        tokenEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, tokenEdit);


        verticalLayout->addLayout(formLayout);

        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        connectButton = new QPushButton(ConfigurationDialog);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout_1->addWidget(connectButton);

        statusLabel = new QLabel(ConfigurationDialog);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        horizontalLayout_1->addWidget(statusLabel);


        verticalLayout->addLayout(horizontalLayout_1);

        lightsGroup = new QGroupBox(ConfigurationDialog);
        lightsGroup->setObjectName(QString::fromUtf8("lightsGroup"));
        verticalLayout_2 = new QVBoxLayout(lightsGroup);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        lightsList = new QTreeWidget(lightsGroup);
        lightsList->setObjectName(QString::fromUtf8("lightsList"));
        lightsList->setSelectionMode(QAbstractItemView::MultiSelection);

        verticalLayout_2->addWidget(lightsList);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        refreshButton = new QPushButton(lightsGroup);
        refreshButton->setObjectName(QString::fromUtf8("refreshButton"));

        horizontalLayout->addWidget(refreshButton);

        addSelectedButton = new QPushButton(lightsGroup);
        addSelectedButton->setObjectName(QString::fromUtf8("addSelectedButton"));

        horizontalLayout->addWidget(addSelectedButton);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout->addWidget(lightsGroup);

        activeGroup = new QGroupBox(ConfigurationDialog);
        activeGroup->setObjectName(QString::fromUtf8("activeGroup"));
        verticalLayout_3 = new QVBoxLayout(activeGroup);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        activeList = new QListWidget(activeGroup);
        activeList->setObjectName(QString::fromUtf8("activeList"));

        verticalLayout_3->addWidget(activeList);

        removeButton = new QPushButton(activeGroup);
        removeButton->setObjectName(QString::fromUtf8("removeButton"));

        verticalLayout_3->addWidget(removeButton);


        verticalLayout->addWidget(activeGroup);


        retranslateUi(ConfigurationDialog);

        QMetaObject::connectSlotsByName(ConfigurationDialog);
    } // setupUi

    void retranslateUi(QWidget *ConfigurationDialog)
    {
        ConfigurationDialog->setWindowTitle(QCoreApplication::translate("ConfigurationDialog", "HA Light Sync Configuration", nullptr));
        urlLabel->setText(QCoreApplication::translate("ConfigurationDialog", "Home Assistant URL:", nullptr));
        urlEdit->setPlaceholderText(QCoreApplication::translate("ConfigurationDialog", "http://homeassistant.local:8123", nullptr));
        tokenLabel->setText(QCoreApplication::translate("ConfigurationDialog", "Access Token:", nullptr));
        tokenEdit->setPlaceholderText(QCoreApplication::translate("ConfigurationDialog", "Long-Lived Access Token", nullptr));
        connectButton->setText(QCoreApplication::translate("ConfigurationDialog", "Connect", nullptr));
        statusLabel->setText(QCoreApplication::translate("ConfigurationDialog", "Status: Not Connected", nullptr));
        lightsGroup->setTitle(QCoreApplication::translate("ConfigurationDialog", "Available Lights", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = lightsList->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("ConfigurationDialog", "Entity ID", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("ConfigurationDialog", "Name", nullptr));
        refreshButton->setText(QCoreApplication::translate("ConfigurationDialog", "Refresh Lights", nullptr));
        addSelectedButton->setText(QCoreApplication::translate("ConfigurationDialog", "Add Selected", nullptr));
        activeGroup->setTitle(QCoreApplication::translate("ConfigurationDialog", "Active Devices", nullptr));
        removeButton->setText(QCoreApplication::translate("ConfigurationDialog", "Remove Selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConfigurationDialog: public Ui_ConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURATIONDIALOG_H
