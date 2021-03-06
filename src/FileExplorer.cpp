#include "FileExplorer.hpp"

#include <QImageReader>
#include <QFileDialog>
#include "TagSelectionDialog.hpp"
#include "utils.hpp"

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
    QObject::connect(m_filesystemModel, &QFileSystemModel::rootPathChanged, [this](const QString &newPath) {
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

void FileExplorer::changeRootPath() {
    auto dirPath = QFileDialog::getExistingDirectory(dynamic_cast<QWidget *>(parent()),
                                                     QString("Open Directory"),
                                                     qvariant_cast<QString>(
                                                             m_listView->rootIndex().data(
                                                                     QFileSystemModel::FilePathRole)),
                                                     QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if(dirPath != ""){
        m_filesystemModel->setRootPath(dirPath);
    }
}

void FileExplorer::saveImageWithText() {
    TagSelectionDialog dialog(m_filesystemModel->rootPath(), UsageType::ADD_TEXT_TO_IMAGES, this);
    dialog.exec();
}

void FileExplorer::onUserCreateInfoFile() {

    TagSelectionDialog dialog(m_filesystemModel->rootPath(), UsageType::SAVE_IMAGE_DATA, this);
    dialog.exec();
}

void FileExplorer::onUserLoadExternalData() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter("Text FIle (*.txt)");


    bool status = dialog.exec();

    if (!status)
        return;

    QString filename = dialog.selectedFiles().front();

    QFile fileHandle(filename);
    fileHandle.open(QFile::ReadOnly | QFile::Text);


    QTextStream in(&fileHandle);
    while (!in.atEnd()) {
        QString line = in.readLine();

        auto tokens = line.split(" ");
        QString imageName = tokens.front();

        tokens.removeAt(0);
        auto text = tokens.join(' ');

        const QString filepath = QDir(m_filesystemModel->rootDirectory()).absoluteFilePath(imageName);
        QFileInfo imageHandle(filepath);
        if (imageHandle.exists()) {
            ::saveImageWithText(imageHandle.absoluteFilePath(), text);
        }
    }
}
