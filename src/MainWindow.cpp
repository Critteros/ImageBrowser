#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QWidget>
#include <QSplitter>
#include <QHeaderView>
#include <QListView>


MainWindow::MainWindow() : QMainWindow() {


    setupFileModel();
    setupFileView();


    m_fileView->setIconSize(QSize(128, 128));

    setCentralWidget(m_fileView);
}

void MainWindow::setupFileView() {

    m_fileView = new QListView;
    m_fileView->setViewMode(QListView::IconMode);
    m_fileView->setWordWrap(true);
    m_fileView->setResizeMode(QListView::Adjust);
//    m_fileView->setUniformItemSizes(true);

    m_fileView->setModel(m_filesystemModel);
    m_fileView->setRootIndex(m_filesystemModel->index(QDir::currentPath()));
    m_iconProvider = new CustomIconProvider(this);
    m_filesystemModel->setIconProvider(m_iconProvider);
    QObject::connect(m_fileView, &QListView::iconSizeChanged, m_iconProvider, &CustomIconProvider::onIconSizeChange);


}

void MainWindow::setupFileModel() {

    m_filesystemModel = new QFileSystemModel(this);
    m_filesystemModel->setRootPath(QDir::currentPath());
    m_filesystemModel->setFilter(QDir::AllEntries | QDir::AllDirs);


}

MainWindow::~MainWindow() = default;
