#include "MetadataModel.hpp"

#include "utils.hpp"

#include <QFont>
#include <QDebug>
#include <exiv2/exiv2.hpp>

MetadataModel::MetadataModel(QObject *parent) : QAbstractTableModel(parent) {

}

int MetadataModel::rowCount(const QModelIndex &parent) const {
    const auto exifCount = m_metadata.exifCount();
    const auto iptcCount = m_metadata.iptcCount();

    qsizetype total = 0;
    if (exifCount != 0) {
        total += 1 + exifCount;
    }
    if (iptcCount != 0) {
        total += 1 + iptcCount;
    }

    return static_cast<int>(total);
}

int MetadataModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant MetadataModel::data(const QModelIndex &index, int role) const {

    switch (role) {
        case Qt::DisplayRole: {
            return dataForDisplay(index);
        }

        case Qt::FontRole: {
            if (index.row() == m_presentationDetails.exifLabelLocation ||
                index.row() == m_presentationDetails.iptcLabelLocation) {
                QFont font;
                font.setBold(true);
                return font;
            } else return {};
        }

        default:
            return {};
    }

}

void MetadataModel::clearStoredMetadata() {
    qDebug() << "Clearing stored metadata";
    beginResetModel();
    m_metadata.clear();
    endResetModel();

}

void MetadataModel::loadAndParseImage(const QString &filepath) {
//    saveImageWithText(filepath, QStringList{"EXIF", "IPTC"});     // FOR TESTING
    qDebug() << "Loading image: " << filepath;
    beginResetModel();

    m_metadata = loadImageMetadata(filepath);
    calculatePresentationDetails();
    endResetModel();
}

MetadataModel::ImageMetadata MetadataModel::loadImageMetadata(const QString &filepath) {
    // There extract metadata
    auto metadataContainer = MetadataModel::ImageMetadata();

    qDebug() << filepath;

    try {
        auto image = Exiv2::ImageFactory::open(filepath.toStdString());
        assert(image.get() != nullptr);
        image->readMetadata();

        // Exif
        auto &exifData = image->exifData();
        if (exifData.empty()) {
            qDebug() << "Empty EXIF";
            metadataContainer.addExif("No Exif data found in the file", "");
        }

        auto endExif = exifData.end();
        for (auto i = exifData.begin(); i != endExif; ++i) {
            metadataContainer.addExif(QString::fromStdString(i->key()),
                                      QString::fromStdString(i->value().toString()));
        }

        // Iptc
        auto &iptcData = image->iptcData();
        if (iptcData.empty()) {
            qDebug() << "Empty IPTC";
            metadataContainer.addIptc("No Iptc data found in the file", "");
        }

        auto endIptc = iptcData.end();
        for (auto i = iptcData.begin(); i != endIptc; ++i) {
            metadataContainer.addIptc(QString::fromStdString(i->key()),
                                      QString::fromStdString(i->value().toString()));
        }
    } catch (std::exception &exception) {
        qDebug() << exception.what();
    }


    return metadataContainer;
}

void MetadataModel::calculatePresentationDetails() {

    auto container = MetadataModel::PresentationDetails();
    const auto exifCount = m_metadata.exifCount();
    const auto iptcCount = m_metadata.iptcCount();

    MetadataModel::PresentationDetails::index_t indexer = 0;

    if (exifCount != 0) {
        container.exifLabelLocation = indexer++;
        container.exifDataStart = indexer++;

        indexer += static_cast<decltype(indexer)>(exifCount) - 1;
        container.exifDataEnd = indexer;
    }

    if (iptcCount != 0) {
        container.iptcLabelLocation = indexer++;
        container.iptcDataStart = indexer++;

        indexer += static_cast<decltype(indexer)>(iptcCount) - 1;
        container.iptcDataEnd = indexer;
    }

    // To be implemented
    m_presentationDetails = container;
    emit dataChanged(createIndex(0, 0), createIndex(rowCount(QModelIndex()), 2));
}

QVariant MetadataModel::dataForDisplay(const QModelIndex &index) const {

    const auto row = index.row();
    const auto field = index.column();

    if (row == m_presentationDetails.iptcLabelLocation) {
        if (field == MetadataModel::FIELD_VALUE) {
            return {};
        }
        return MetadataModel::PresentationDetails::IPTC_LABEL;
    }

    if (row == m_presentationDetails.exifLabelLocation) {
        if (field == MetadataModel::FIELD_VALUE) {
            return {};
        }
        return MetadataModel::PresentationDetails::EXIF_LABEL;
    }

    //If to display exif
    if (row >= m_presentationDetails.exifDataStart && row < m_presentationDetails.exifDataEnd) {
        const auto accessIndex = row - m_presentationDetails.exifDataStart;
        if (field == MetadataModel::FIELD_KEY) {
            return m_metadata.EXIF_metadata[accessIndex].first;
        }
        if (field == MetadataModel::FIELD_VALUE) {
            return m_metadata.EXIF_metadata[accessIndex].second;
        }
    }

    //If to display IPTC
    if (row >= m_presentationDetails.iptcDataStart && row < m_presentationDetails.iptcDataEnd) {
        const auto accessIndex = row - m_presentationDetails.iptcDataStart;
        if (field == MetadataModel::FIELD_KEY) {
            return m_metadata.IPTC_metadata[accessIndex].first;
        }
        if (field == MetadataModel::FIELD_VALUE) {
            return m_metadata.IPTC_metadata[accessIndex].second;
        }
    }


    return QString("ERROR");
}

Qt::ItemFlags MetadataModel::flags(const QModelIndex &index) const {
    if (index.row() == m_presentationDetails.iptcLabelLocation ||
        index.row() == m_presentationDetails.exifLabelLocation) {
        return Qt::NoItemFlags;
    }

    return QAbstractTableModel::flags(index);
}


MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::addExif(const QString &key, const QString &value) {
    EXIF_metadata << QPair<QString, QString>(key, value);
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::addIptc(const QString &key, const QString &value) {
    IPTC_metadata << QPair<QString, QString>(key, value);
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clear() {
    clearExif();
    clearIptc();
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clearExif() {
    EXIF_metadata.clear();
    return *this;
}

MetadataModel::ImageMetadata &MetadataModel::ImageMetadata::clearIptc() {
    IPTC_metadata.clear();
    return *this;
}

qsizetype MetadataModel::ImageMetadata::exifCount() const {
    return EXIF_metadata.count();

}

qsizetype MetadataModel::ImageMetadata::iptcCount() const {
    return IPTC_metadata.count();
}
