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
#include <QVBoxLayout>
#include <QCheckBox>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>

#include "MetadataModel.hpp"
#include "CustomIconProvider.hpp"

#include "DebugHelpers.hpp"

enum class UsageType {
    SAVE_IMAGE_DATA,
    ADD_TEXT_TO_IMAGES
};

class TagSelectionDialog : public QDialog {
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
    explicit TagSelectionDialog(const QString &rootPath, UsageType usageType, QWidget *parent = nullptr);

public slots:

    void onSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection);

private slots:

    void onSaveImageData(bool);

    void onSaveImageWithText(bool);

private:
    QSet<QString> getUniqueTagNames(TAG_TYPE type = TAG_EXIF) const;

    QSet<QString> getSelectedTagNames(TAG_TYPE type = TAG_EXIF) const;

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
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_closeButton = nullptr;
};

