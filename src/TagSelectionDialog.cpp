#include "TagSelectionDialog.hpp"


#include <algorithm>
#include "utils.hpp"

TagSelectionDialog::TagSelectionDialog(const QString &rootPath, UsageType usageType, QWidget *parent) : QDialog(
        parent) {
    setModal(true);

    m_filesystemModel = new QFileSystemModel(this);
    m_filesystemModel->setNameFilters(QStringList() << "*.jpg" << "*.png");
    m_filesystemModel->setNameFilterDisables(false);
    m_filesystemModel->setFilter(QDir::Files);
    m_filesystemModel->setRootPath(rootPath);

    m_fileIconProvider = new CustomIconProvider(this);
    m_filesystemModel->setIconProvider(m_fileIconProvider);

    m_listView = new QListView(this);
    m_listView->setViewMode(QListView::IconMode);
    m_listView->setWordWrap(true);
    m_listView->setResizeMode(QListView::Adjust);


    m_listView->setModel(m_filesystemModel);
    m_listView->setRootIndex(m_filesystemModel->index(m_filesystemModel->rootPath()));
    m_listView->setMinimumSize(300, 400);
    m_listView->setSelectionMode(QAbstractItemView::MultiSelection);

    QObject::connect(m_listView->selectionModel(), &QItemSelectionModel::selectionChanged, this,
                     &TagSelectionDialog::onSelectionChanged);

    //UI

    m_EXIF_group = new QGroupBox("EXIF");
    m_IPTC_group = new QGroupBox("IPTC");

    constexpr int GROUP_BOX_WIDTH = 300;

    m_EXIF_scroll = new QScrollArea(this);
    m_EXIF_scroll->setFixedWidth(GROUP_BOX_WIDTH);
    m_EXIF_scroll->setWidgetResizable(true);

    m_IPTC_scroll = new QScrollArea(this);
    m_IPTC_scroll->setFixedWidth(GROUP_BOX_WIDTH);
    m_IPTC_scroll->setWidgetResizable(true);

    m_EXIF_scroll->setWidget(m_EXIF_group);
    m_IPTC_scroll->setWidget(m_IPTC_group);


    m_EXIF_selectAllButton = new QPushButton("Select all");
    m_EXIF_deselectAllButton = new QPushButton("Deselect all");
    m_IPTC_selectAllButton = new QPushButton("Select all");
    m_IPTC_deselectAllButton = new QPushButton("Deselect all");

    QObject::connect(m_EXIF_selectAllButton, &QPushButton::clicked, [this](bool) {
        for (const auto checkbox: m_exifButtons) {
            checkbox->setChecked(true);
        }
    });
    QObject::connect(m_EXIF_deselectAllButton, &QPushButton::clicked, [this](bool) {
        for (const auto checkbox: m_exifButtons) {
            checkbox->setChecked(false);
        }
    });

    QObject::connect(m_IPTC_selectAllButton, &QPushButton::clicked, [this](bool) {
        for (const auto checkbox: m_iptcButtons) {
            checkbox->setChecked(true);
        }
    });
    QObject::connect(m_IPTC_deselectAllButton, &QPushButton::clicked, [this](bool) {
        for (const auto checkbox: m_iptcButtons) {
            checkbox->setChecked(false);
        }
    });

    auto EXIF_sectionWrapper = new QWidget;
    auto IPTC_sectionWrapper = new QWidget;

    auto FILES_group = new QGroupBox("Select images");
    auto filesLayout = new QVBoxLayout;
    filesLayout->addWidget(m_listView);
    FILES_group->setLayout(filesLayout);

    auto exifButtonLayout = new QHBoxLayout;
    auto iptcButtonLayout = new QHBoxLayout;
    exifButtonLayout->addWidget(m_EXIF_selectAllButton);
    exifButtonLayout->addWidget(m_EXIF_deselectAllButton);
    iptcButtonLayout->addWidget(m_IPTC_selectAllButton);
    iptcButtonLayout->addWidget(m_IPTC_deselectAllButton);

    auto EXIF_buttons_wrapper = new QWidget;
    EXIF_buttons_wrapper->setLayout(exifButtonLayout);
    auto IPTC_buttons_wrapper = new QWidget;
    IPTC_buttons_wrapper->setLayout(iptcButtonLayout);

    auto exif_layout = new QVBoxLayout;
    auto iptc_layout = new QVBoxLayout;
    exif_layout->addWidget(m_EXIF_scroll);
    exif_layout->addWidget(EXIF_buttons_wrapper);
    iptc_layout->addWidget(m_IPTC_scroll);
    iptc_layout->addWidget(IPTC_buttons_wrapper);


    EXIF_sectionWrapper->setLayout(exif_layout);
    IPTC_sectionWrapper->setLayout(iptc_layout);


    auto mainUISectionLayout = new QHBoxLayout;
    auto mainUISectionWidget = new QWidget;
    mainUISectionLayout->addWidget(FILES_group);
    mainUISectionLayout->addWidget(EXIF_sectionWrapper);
    mainUISectionLayout->addWidget(IPTC_sectionWrapper);
    mainUISectionWidget->setLayout(mainUISectionLayout);

    auto buttonsLayout = new QHBoxLayout;
    auto buttonsWidget = new QWidget;
    m_closeButton = new QPushButton("Close");

    if (usageType == UsageType::SAVE_IMAGE_DATA) {
        m_saveButton = new QPushButton("Save Image Data");
    } else if (usageType == UsageType::ADD_TEXT_TO_IMAGES) {
        m_saveButton = new QPushButton("Save Images with Text");
    }

    buttonsLayout->addWidget(m_saveButton);
    buttonsLayout->addWidget((m_closeButton));
    buttonsWidget->setLayout(buttonsLayout);

    if (usageType == UsageType::SAVE_IMAGE_DATA)
        QObject::connect(m_saveButton, &QPushButton::clicked, this, &TagSelectionDialog::onSaveImageData);
    else if (usageType == UsageType::ADD_TEXT_TO_IMAGES)
        QObject::connect(m_saveButton, &QPushButton::clicked, this, &TagSelectionDialog::onSaveImageWithText);
    QObject::connect(m_closeButton, &QPushButton::clicked, this, [this](bool) {
        close();
    });

    auto mainUILayout = new QVBoxLayout(this);
    mainUILayout->addWidget(mainUISectionWidget);
    mainUILayout->addWidget(buttonsWidget);
    setLayout(mainUILayout);


}

void TagSelectionDialog::onSelectionChanged(const QItemSelection &newSelection, const QItemSelection &oldSelection) {


    //Check if something got remove
    for (const auto &modelIndex: oldSelection.indexes()) {
        if (newSelection.contains(modelIndex))
            continue;

        QFileInfo fileInfo(m_filesystemModel->data(modelIndex, QFileSystemModel::FilePathRole).toString());
        qDebug() << "Removing" << fileInfo.fileName();

        const auto target = std::find_if(std::cbegin(m_allFilesMetadata), std::cend(m_allFilesMetadata),
                                         [&fileInfo](const MetadataForFile &obj) {
                                             return obj.filename == fileInfo.fileName();
                                         });

        if (target != std::end(m_allFilesMetadata)) {
            m_allFilesMetadata.erase(target);
        }

        addWidgetButtons();
    }

    for (const auto &modelIndex: newSelection.indexes()) {
        if (oldSelection.contains(modelIndex))
            continue;
        QFileInfo fileInfo(m_filesystemModel->data(modelIndex, QFileSystemModel::FilePathRole).toString());
        qDebug() << "Adding" << fileInfo.fileName();

        m_allFilesMetadata << MetadataForFile(fileInfo.fileName(),
                                              MetadataModel::loadImageMetadata(fileInfo.absoluteFilePath()));
        addWidgetButtons();
    }
}

QSet<QString> TagSelectionDialog::getUniqueTagNames(TAG_TYPE type) const {
    QSet<QString> data;

    for (const auto &block: m_allFilesMetadata) {

        const auto &metadata = block.metadata;
        if (type == TAG_EXIF) {
            for (const auto &tag: metadata.EXIF_metadata) {
                data.insert(tag.first);
            }
        } else if (type == TAG_IPTC) {
            for (const auto &tag: metadata.IPTC_metadata) {
                data.insert(tag.first);
            }
        }
    }

    return data;
}

void TagSelectionDialog::addWidgetButtons() {
    const auto EXIF_KEYS = getUniqueTagNames(TAG_EXIF);
    const auto IPTC_KEYS = getUniqueTagNames(TAG_IPTC);

    m_exifButtons.clear();
    m_iptcButtons.clear();

    delete m_EXIF_group;
    delete m_IPTC_group;

    m_EXIF_group = new QGroupBox("EXIF", this);
    m_IPTC_group = new QGroupBox("IPTC", this);


    QVBoxLayout *exif_layout, *iptc_layout;
    exif_layout = new QVBoxLayout(m_EXIF_scroll);
    iptc_layout = new QVBoxLayout(m_IPTC_scroll);

    for (const auto &name: EXIF_KEYS) {
        auto newButton = new QCheckBox(name);
        exif_layout->addWidget(newButton);
        m_exifButtons.push_back(newButton);
    }
    for (const auto &name: IPTC_KEYS) {
        auto newButton = new QCheckBox(name);
        iptc_layout->addWidget(newButton);
        m_iptcButtons.push_back(newButton);
    }

    m_IPTC_group->setLayout(iptc_layout);
    m_EXIF_group->setLayout(exif_layout);

    m_IPTC_scroll->setWidget(m_IPTC_group);
    m_EXIF_scroll->setWidget(m_EXIF_group);
}

void TagSelectionDialog::onSaveImageData(bool) {

    const auto exif_keys = getSelectedTagNames(TAG_EXIF);
    const auto iptc_keys = getSelectedTagNames(TAG_IPTC);

//    const QString filename = "saved_image_data.json";
    const QString filename = QDir(m_filesystemModel->rootDirectory()).absoluteFilePath("saved_image_data.json");
    QFile fileHandle{filename};


    auto jsonHandle = QJsonDocument();
    auto mainJsonArray = QJsonArray();


    for (const auto &metadataFile: m_allFilesMetadata) {
        const auto &metadataFilename = metadataFile.filename;
        const auto &exifMetadata = metadataFile.metadata.EXIF_metadata;
        const auto &iptcMetadata = metadataFile.metadata.IPTC_metadata;

        auto fileJsonObject = QJsonObject();
        fileJsonObject.insert("filename", metadataFilename);

        auto exifMetadataArray = QJsonArray();
        auto iptcMetadataArray = QJsonArray();

        // EXIF
        for (const auto &[key, value]: exifMetadata) {
            if (exif_keys.contains(key)) {
                auto jsonObject = QJsonObject();
                jsonObject.insert("type", "EXIF");
                jsonObject.insert("tag", key);
                jsonObject.insert("value", value);
                exifMetadataArray.append(jsonObject);
            }
        }

        // IPTC
        for (const auto &[key, value]: iptcMetadata) {
            if (iptc_keys.contains(key)) {
                auto jsonObject = QJsonObject();
                jsonObject.insert("type", "IPTC");
                jsonObject.insert("tag", key);
                jsonObject.insert("value", value);

                iptcMetadataArray.append(jsonObject);
            }
        }


        fileJsonObject.insert("EXIF", exifMetadataArray);
        fileJsonObject.insert("IPTC", iptcMetadataArray);

        mainJsonArray.append(fileJsonObject);

    }

    jsonHandle.setArray(mainJsonArray);


    auto dumpedJson = jsonHandle.toJson(QJsonDocument::Indented);
    fileHandle.open(QFile::WriteOnly | QFile::Text);
    fileHandle.write(dumpedJson);

    close();
}

QSet<QString> TagSelectionDialog::getSelectedTagNames(TagSelectionDialog::TAG_TYPE type) const {
    QSet<QString> data;

    if (type == TAG_EXIF) {
        for (const auto checkbox: m_exifButtons) {
            if (checkbox->isChecked()) {
                data.insert(checkbox->text());
            }
        }
    } else if (type == TAG_IPTC) {
        for (const auto checkbox: m_iptcButtons) {
            if (checkbox->isChecked()) {
                data.insert(checkbox->text());
            }
        }
    }

    return data;
}

void TagSelectionDialog::onSaveImageWithText(bool) {
    const auto exif_keys = getSelectedTagNames(TAG_EXIF);
    const auto iptc_keys = getSelectedTagNames(TAG_IPTC);


    for (const auto &metadataFile: m_allFilesMetadata) {
        const auto &metadataFilename = metadataFile.filename;
        const auto &exifMetadata = metadataFile.metadata.EXIF_metadata;
        const auto &iptcMetadata = metadataFile.metadata.IPTC_metadata;

        QString s;
        QTextStream ss(&s);

        ss << "EXIF:\n";
        for (const auto &[key, value]: exifMetadata) {
            if (exif_keys.contains(key)) {
                ss << key << ": " << value << '\n';
            }
        }
        ss << "\nIPTC:";
        for (const auto &[key, value]: iptcMetadata) {
            if (iptc_keys.contains(key)) {
                ss << key << ": " << value << '\n';
            }
        }
        const QString filepath = QDir(m_filesystemModel->rootDirectory()).absoluteFilePath(metadataFilename);
        saveImageWithText(filepath, s);
    }
    close();
}
