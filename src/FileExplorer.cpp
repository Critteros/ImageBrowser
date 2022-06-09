#include "FileExplorer.hpp"

#include <QImageReader>

FileExplorer::FileExplorer(QWidget *parent) : QStackedWidget(parent) {
    setupModels();
    setupViews();

    addWidget(m_listView);
    addWidget(m_imageLabel);
    setCurrentWidget(m_listView);

    // Start filesystem model at current working directory (.exe dir)
    m_filesystemModel->setRootPath(QDir::currentPath());


}

/**
 * @biref Initializes view and connects them to model
 */
void FileExplorer::setupViews() {
    m_listView = new QListView;
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setWordWrap(true);
    m_listView->setResizeMode(QListView::Adjust);
    m_listView->setModel(m_filesystemModel);

    m_imageLabel = new ClickableLabel;
    m_imageLabel->setScaledContents(true);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    // Clicking on image preview will change back to directory explorer
    QObject::connect(m_imageLabel, &ClickableLabel::clicked, [this]() {
        setCurrentWidget(m_listView);
    });

    // Changing view icon size will change how big icons are served by icon provider
    QObject::connect(m_listView, &QListView::iconSizeChanged, m_fileIconProvider,
                     &CustomIconProvider::onIconSizeChange);

    // Changing model root path will switch currently presented folder in view
    QObject::connect(m_filesystemModel, &QFileSystemModel::rootPathChanged, [this](const QString &newPath){
        m_listView->setRootIndex(m_filesystemModel->index(newPath));
    });

    // Double-clicking on directory will go into it
    // double-clicking on image will preview it
    QObject::connect(m_listView, &QListView::doubleClicked, [this](const QModelIndex &index) {
        const auto path = qvariant_cast<QString>(index.data(QFileSystemModel::FilePathRole));
        if (QFileInfo(path).isDir()) {
            m_filesystemModel->setRootPath(path);
        } else {
            QImageReader imageReader(path);
            imageReader.setAutoTransform(true);
            const QImage readImage = imageReader.read();

            if (!readImage.isNull()) {
                qDebug() << "Opening preview for:" << path;
                m_imageLabel->setPixmap(QPixmap::fromImage(readImage));
                setCurrentWidget(m_imageLabel);
            }
        }
    });

    QObject::connect(m_listView, &QListView::clicked, [this](const QModelIndex &index) {
        const auto path = index.data(QFileSystemModel::FilePathRole).toString();
        emit fileClicked(QFileInfo(path).absoluteFilePath());
    });
}

/**
 * @biref Initializes filesystem model
 */
void FileExplorer::setupModels() {
    m_filesystemModel = new QFileSystemModel(this);
    m_filesystemModel->setNameFilters(QStringList() << "*.jpg" << "*.png");
    m_filesystemModel->setNameFilterDisables(false);
    m_filesystemModel->setFilter(QDir::AllEntries | QDir::AllDirs);

    m_fileIconProvider = new CustomIconProvider(this);
    m_filesystemModel->setIconProvider(m_fileIconProvider);

}

void FileExplorer::setIconSize(const QSize &newSize) {
    m_listView->setIconSize(newSize);
}

void FileExplorer::changeRootIndex(const QString &newPath) {
    m_listView->setRootIndex(m_filesystemModel->index(newPath));
}
