#include "MainWindow.hpp"


#include "FileExplorer.hpp"



MainWindow::MainWindow() : QMainWindow() {

    m_splitter = new QSplitter(Qt::Horizontal);

    m_fileExplorer = new FileExplorer;
    m_metadataView = new QTableView;

    m_splitter->addWidget(m_fileExplorer);
    m_splitter->addWidget(m_metadataView);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 2);

    m_fileExplorer->setIconSize(FILE_ICON_SIZE);

    m_splitter->setMinimumSize(MAIN_WIDGET_MIN_SIZE);


    setCentralWidget(m_splitter);
}


MainWindow::~MainWindow() = default;
