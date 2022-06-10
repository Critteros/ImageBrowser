
#include "ToolBar.hpp"
#include "MainWindow.hpp"
#include <QDebug>
#include <QFileDialog>


ToolBar::ToolBar(MainWindow *mainWindow)
        : QObject(mainWindow), toolBar{mainWindow->addToolBar("ToolBar")} {
    // Toolbar options
    toolBar->setMovable(false);
//    toolBar->setIconSize(toolBar->iconSize()*1.5);  // Scale Icons
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    // Adding Icons
    const QIcon openDirIcon = mainWindow->style()->standardIcon(QStyle::SP_DirIcon);
    const QIcon generateInfoFileIcon = mainWindow->style()->standardIcon(QStyle::SP_FileIcon);
    const QIcon saveImageModifiedIcon = mainWindow->style()->standardIcon(QStyle::SP_DialogSaveButton);
    const QIcon loadExternalDataIcon = mainWindow->style()->standardIcon(QStyle::SP_ArrowDown);


    // Creating Actions
    auto *openDirAction = new QAction(openDirIcon, "Choose Directory", this);
    auto *generateInfoFileAction = new QAction(generateInfoFileIcon, "Generate Info File", this);
    auto *saveImageModifiedAction = new QAction(saveImageModifiedIcon, "Save Image with Parameters", this);
    auto *loadExternalDataAction = new QAction(loadExternalDataIcon, "Load External Data", this);
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


//TODO: Implement methods

void ToolBar::openDir() {
    qDebug() << "Open Dir";
     emit dirChanged();
}

void ToolBar::generateInfoFile() {
    qDebug() << "Generate info File";
}

void ToolBar::saveImageModified() {
    qDebug() << "Save image modified";
    emit onSaveImageClick();
}

void ToolBar::loadExternalData() {
    qDebug() << "Load external data";
}

ToolBar::~ToolBar() = default;