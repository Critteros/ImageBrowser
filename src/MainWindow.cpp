#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QWidget>
#include <QToolBar>
#include <QIcon>
#include <QAction>
#include <QSplitter>
#include <QTableView>
#include <QStackedWidget>
#include <QLabel>
#include <QListView>

MainWindow::MainWindow():
    QMainWindow(), centralWidget{nullptr} {
    centralWidget = createLayout();
    setCentralWidget(centralWidget);
    createToolBar();
}

void MainWindow::createToolBar() {

    // Toolbar options
    auto* toolBar = addToolBar("Toolbar");
    toolBar->setMovable(false);
    toolBar->setIconSize(toolBar->iconSize()*1.5);  // Scale Icons

    // Adding Icons
    const QIcon openDirIcon = this->style()->standardIcon(QStyle::SP_DirIcon);
    const QIcon generateInfoFileIcon = this->style()->standardIcon(QStyle::SP_FileIcon);
    const QIcon saveImageModifiedIcon = this->style()->standardIcon(QStyle::SP_DialogSaveButton);
    const QIcon loadExternalDataIcon = this->style()->standardIcon(QStyle::SP_ArrowDown);

    // Creating Actions
    auto* openDirAction = new QAction(openDirIcon, "Choose Directory");
    auto* generateInfoFileAction = new QAction(generateInfoFileIcon, "Generate Info File");
    auto* saveImageModifiedAction = new QAction(saveImageModifiedIcon, "Save Image with Parameters");
    auto* loadExternalDataAction = new QAction(loadExternalDataIcon, "Load External Data");
//    newAct->setShortcuts(QKeySequence::New);
//    newAct->setStatusTip(tr("Create a new file"));
//    connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    // Connecting Actions to methods
    //TODO: Implement

    // Adding Actions
    toolBar->addAction(openDirAction);
    toolBar->addAction(generateInfoFileAction);
    toolBar->addAction(saveImageModifiedAction);
    toolBar->addAction(loadExternalDataAction);
}

QSplitter* MainWindow::createLayout() {
    auto* layout = new QSplitter(this);
    auto* metadataView = new QTableView();
    auto* leftPanel = new QStackedWidget();
    auto* imageView = new QLabel();
    auto* fileSystemView = new QListView();

    // TODO: Change to customized views
    leftPanel->addWidget(imageView);
    leftPanel->addWidget(fileSystemView);
    layout->addWidget(leftPanel);
    layout->addWidget(metadataView);
    return layout;
}

void MainWindow::setCurrentDirectory(const QString &dirName) {

}

MainWindow::~MainWindow() = default;
