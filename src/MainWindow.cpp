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
#include <QDebug>
#include <QPalette>
#include <QColor>


#include <iostream>

MainWindow::MainWindow():
    QMainWindow(), centralWidget{nullptr} {
    QPalette mainPalette(QColor("#f5edf0"), QColor("#424c55")); // IDK ale działa (Potem pobawie się w ładny wygląd)
    setPalette(mainPalette);
    centralWidget = createLayout();
    setCentralWidget(centralWidget);
    createToolBar();
    setWindowIcon(QIcon(":/img/AppIcon.png"));

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
