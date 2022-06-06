#include "MainWindow.hpp"

#include <QHBoxLayout>
#include <QWidget>

#include <QHeaderView>
#include <QListView>
#include <QImageReader>


MainWindow::MainWindow() : QMainWindow() {


    setupFileModel();
    setupFileView();


    m_fileView->setIconSize(QSize(128, 128));


    m_imageDisplay = new ClickableLabel;
//    m_imageDisplay->setText("test");
    m_imageDisplay->setScaledContents(true);
    m_imageDisplay->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);


    m_stackedWidget = new QStackedWidget;
    m_stackedWidget->addWidget(m_fileView);
    m_stackedWidget->addWidget(m_imageDisplay);

    m_metadataView = new QTableView;


    m_splitter = new QSplitter(Qt::Horizontal);
    m_splitter->addWidget(m_stackedWidget);
    m_splitter->addWidget(m_metadataView);
    m_splitter->setStretchFactor(0, 4);
    m_splitter->setStretchFactor(1, 2);

    m_splitter->setMinimumSize(800, 600);

    QObject::connect(m_imageDisplay, &ClickableLabel::clicked, [this]() {
        qDebug() << "Clicked on image";
        m_stackedWidget->setCurrentIndex(0);
    });

    setCentralWidget(m_splitter);
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

    QObject::connect(m_fileView, &QListView::doubleClicked, [this](const QModelIndex &index) {
        const auto path = qvariant_cast<QString>(index.data(QFileSystemModel::FilePathRole));
        if (QFileInfo(path).isDir()) {
            m_filesystemModel->setRootPath(path);
        } else {
            QImageReader imageReader(path);
            imageReader.setAutoTransform(true);

            const QImage readImage = imageReader.read();

            if (!readImage.isNull()) {
                qDebug() << "Read image from path" << path;
                m_imageDisplay->setPixmap(QPixmap::fromImage(readImage));
                m_stackedWidget->setCurrentIndex(1);
            }
        }
    });

    QObject::connect(m_filesystemModel, &QFileSystemModel::rootPathChanged, [this](const QString &newPath) {
        m_fileView->setRootIndex(m_filesystemModel->index(newPath));
    });


}

void MainWindow::setupFileModel() {

    m_filesystemModel = new QFileSystemModel(this);
    m_filesystemModel->setRootPath(QDir::currentPath());
//    m_filesystemModel->setRootPath("/");
    m_filesystemModel->setNameFilters(QStringList() << "*.jpg" << "*.png");
    m_filesystemModel->setNameFilterDisables(false);
    m_filesystemModel->setFilter(QDir::AllEntries | QDir::AllDirs);


}

MainWindow::~MainWindow() = default;
