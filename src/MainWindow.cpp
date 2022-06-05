#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QWidget>
#include <QSplitter>

MainWindow::MainWindow(): QMainWindow() {

    auto layout = new QVBoxLayout;

    auto centralWidget = new QWidget;

    layout->addWidget(new MetadataWidget, 1);
    layout->addWidget(new MetadataWidget,2);

    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);




//    setCentralWidget(splitter);

}

MainWindow::~MainWindow() = default;
