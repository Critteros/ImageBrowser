#include "ImageViewer.hpp"


ImageViewer::ImageViewer(QWidget *parent) : QStackedWidget(parent) {
    setupFileView();
    setupImagePreview();

    addWidget(m_listView);
    addWidget(m_listView);
    setCurrentWidget(m_listView);
}


void ImageViewer::setupFileView() {
    m_listView = new QListView;
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setWordWrap(true);
    m_listView->setResizeMode(QListView::Adjust);

    QObject::connect(m_listView, &QListView::iconSizeChanged, [this](const QSize &newSize) {
        emit iconSizeChanged(newSize);
    });
}

void ImageViewer::setFileModel(QFileSystemModel *model) {
    m_filesystemModel = model;
    m_listView->setModel(model);
    m_listView->setRootIndex(model->index(model->rootPath()));


//    QObject::connect(m_fileView, &QListView::doubleClicked, [this](const QModelIndex &index) {
//        const auto path = qvariant_cast<QString>(index.data(QFileSystemModel::FilePathRole));
//        if (QFileInfo(path).isDir()) {
//            m_filesystemModel->setRootPath(path);
//        } else {
//            QImageReader imageReader(path);
//            imageReader.setAutoTransform(true);
//
//            const QImage readImage = imageReader.read();
//
//            if (!readImage.isNull()) {
//                qDebug() << "Read image from path" << path;
//                m_imageDisplay->setPixmap(QPixmap::fromImage(readImage));
//                m_stackedWidget->setCurrentIndex(1);
//            }
//        }
//    });
//
//    QObject::connect(m_filesystemModel, &QFileSystemModel::rootPathChanged, [this](const QString &newPath) {
//        m_fileView->setRootIndex(m_filesystemModel->index(newPath));
//    });
}

void ImageViewer::setupImagePreview() {
    m_imageLabel = new ClickableLabel;
}

