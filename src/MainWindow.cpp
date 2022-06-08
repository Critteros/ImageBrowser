#include "MainWindow.hpp"


#include "FileExplorer.hpp"

#include <iostream>
#include <exiv2/exiv2.hpp>

MainWindow::MainWindow() : QMainWindow() {

    m_splitter = new QSplitter(Qt::Horizontal);

    m_fileExplorer = new FileExplorer;
    m_metadataWidget = new MetadataWidget;

    m_splitter->addWidget(m_fileExplorer);
    m_splitter->addWidget(m_metadataWidget);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 2);

    QPalette mainPalette(QColor("#f5edf0"), QColor("#424c55")); // IDK ale działa (Potem pobawie się w ładny wygląd)
    setPalette(mainPalette);

    m_splitter->setMinimumSize(MAIN_WIDGET_MIN_SIZE);

    QObject::connect(m_fileExplorer, &FileExplorer::fileClicked, m_metadataWidget, &MetadataWidget::onFileCLick);


    setCentralWidget(m_splitter);
}


MainWindow::~MainWindow() = default;
