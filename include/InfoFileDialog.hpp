#pragma once

#include <QDialog>
#include <QString>
#include <QFileSystemModel>
#include <QHBoxLayout>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QSet>
#include <QGroupBox>
#include <QScrollArea>
#include <QPushButton>
#include <QCheckBox>

#include "MetadataModel.hpp"
#include "CustomIconProvider.hpp"

#include "DebugHelpers.hpp"

class InfoFileDialog : public QDialog {
Q_OBJECT

    struct MetadataForFile {

        MetadataForFile(const QString &filename, const MetadataModel::ImageMetadata &metadata)
                : filename{filename}, metadata{metadata} {}

        QString filename;
        MetadataModel::ImageMetadata metadata;
    };

    enum TAG_TYPE {
        TAG_EXIF = 0,
        TAG_IPTC
    };

public:
    explicit InfoFileDialog(const QString &rootPath, QWidget *parent = nullptr);

public slots:

    void onSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection);

    void onSaveImages(bool);

private:
    QSet<QString> getUniqueTagNames(TAG_TYPE type = TAG_EXIF) const;

    void addWidgetButtons();

private:
    QFileSystemModel *m_filesystemModel = nullptr;
    QListView *m_listView = nullptr;
    CustomIconProvider *m_fileIconProvider = nullptr;

    QList<MetadataForFile> m_allFilesMetadata;
    QList<QCheckBox *> m_exifButtons;
    QList<QCheckBox *> m_iptcButtons;

    // UI
    QScrollArea *m_EXIF_scroll = nullptr;
    QScrollArea *m_IPTC_scroll = nullptr;
    QGroupBox *m_EXIF_group = nullptr;
    QGroupBox *m_IPTC_group = nullptr;
    QPushButton *m_EXIF_selectAllButton = nullptr;
    QPushButton *m_EXIF_deselectAllButton = nullptr;
    QPushButton *m_IPTC_selectAllButton = nullptr;
    QPushButton *m_IPTC_deselectAllButton = nullptr;
    QPushButton *m_saveImagesButton = nullptr;
    QPushButton *m_closeButton = nullptr;
};

