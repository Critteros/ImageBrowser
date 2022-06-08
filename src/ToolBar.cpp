
#include "ToolBar.hpp"
#include "MainWindow.hpp"
#include "QStyle"


ToolBar::ToolBar(MainWindow* mainWindow)
    : toolBar{mainWindow->addToolBar("ToolBar")}{
    // Toolbar options
    toolBar->setMovable(false);
    toolBar->setIconSize(toolBar->iconSize()*1.5);  // Scale Icons
//    toolBar->setStyleSheet("QToolBar { spacing: 20px; background-color:  }");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//    mainWindow->setStyleSheet("QToolButton {color: ; }");

    // Adding Icons
    const QIcon openDirIcon = mainWindow->style()->standardIcon(QStyle::SP_DirIcon);
    const QIcon generateInfoFileIcon = mainWindow->style()->standardIcon(QStyle::SP_FileIcon);
    const QIcon saveImageModifiedIcon = mainWindow->style()->standardIcon(QStyle::SP_DialogSaveButton);
    const QIcon loadExternalDataIcon = mainWindow->style()->standardIcon(QStyle::SP_ArrowDown);


    // Creating Actions
    auto* openDirAction = new QAction(openDirIcon, "Choose Directory");
    auto* generateInfoFileAction = new QAction(generateInfoFileIcon, "Generate Info File");
    auto* saveImageModifiedAction = new QAction(saveImageModifiedIcon, "Save Image with Parameters");
    auto* loadExternalDataAction = new QAction(loadExternalDataIcon, "Load External Data");
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Create a new file"));

    // Connecting Actions to methods
    connect(openDirAction, &QAction::triggered, this, &ToolBar::openDir);
    connect(generateInfoFileAction, &QAction::triggered, this, &ToolBar::generateInfoFile);
    connect(saveImageModifiedAction, &QAction::triggered, this, &ToolBar::saveImageModified);
    connect(loadExternalDataAction, &QAction::triggered, this, &ToolBar::loadExternalData);

    // Adding Actions
    toolBar->addAction(openDirAction);
    toolBar->addAction(generateInfoFileAction);
    toolBar->addAction(saveImageModifiedAction);
    toolBar->addAction(loadExternalDataAction);
}


#include <iostream> // For debugging
#define LOG(X) std::cout<<(X)<<std::endl;

void ToolBar::openDir() {
    LOG("OPEN DIR")
}

void ToolBar::generateInfoFile() {
    LOG("GENERATE INFO FILE ")
}

void ToolBar::saveImageModified() {
    LOG("SAVE IMAGE MODIFIED")
}

void ToolBar::loadExternalData() {
    LOG("LOAD EXTERNAL DATA")
}

ToolBar::~ToolBar() = default;