#include "MainWindow.hpp"
#include "FileExplorer.hpp"
#include <QPalette>

#include <iostream>
#include <exiv2/exiv2.hpp>

MainWindow::MainWindow() : QMainWindow() {

    setWindowIcon(QIcon(":/img/AppIcon.png"));

    m_splitter = new QSplitter(Qt::Horizontal);
    m_toolbar = new ToolBar(this);

    m_fileExplorer = new FileExplorer;
    m_metadataWidget = new MetadataWidget;

    m_splitter->addWidget(m_fileExplorer);
    m_splitter->addWidget(m_metadataWidget);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 2);

    m_splitter->setMinimumSize(MAIN_WIDGET_MIN_SIZE);

    QObject::connect(m_fileExplorer, &FileExplorer::fileClicked, m_metadataWidget, &MetadataWidget::onFileCLick);
    QObject::connect(m_toolbar, &ToolBar::dirChanged, m_fileExplorer, &FileExplorer::changeRootPath);
    QObject::connect(m_toolbar, &ToolBar::onSaveImageClick, m_fileExplorer, &FileExplorer::saveImageWithText);
    QObject::connect(m_toolbar, &ToolBar::onUserCreateInfoFile, m_fileExplorer, &FileExplorer::onUserCreateInfoFile);
    QObject::connect(m_toolbar, &ToolBar::onLoadExternalData, m_fileExplorer, &FileExplorer::onUserLoadExternalData);

    setCentralWidget(m_splitter);
}


MainWindow::~MainWindow() = default;
