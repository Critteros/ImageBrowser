#include "MainWindow.hpp"
#include "ToolBar.hpp"

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
    setWindowIcon(QIcon("C:/Users/Alan/CLionProjects/ImageBrowser/img/AppIcon.png"));   // Hardcodowałem bo do embedowania trzeba qrc
}

void MainWindow::createToolBar() {
    auto* toolBar = new ToolBar(this);
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



MainWindow::~MainWindow() = default;
