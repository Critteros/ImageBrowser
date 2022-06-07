#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#pragma once


#include <QAbstractTableModel>
#include <QList>
#include <QString>
#include <QPair>

#include "DebugHelpers.hpp"


class MetadataModel : public QAbstractTableModel {
Q_OBJECT

    enum {
        FIELD_KEY = 0,
        FIELD_VALUE
    };

    struct ImageMetadata {
        using KVList = QList<QPair<QString, QString>>;

        ImageMetadata &addExif(const QString &key, const QString &value);

        ImageMetadata &addIptc(const QString &key, const QString &value);

        ImageMetadata &clear();

        ImageMetadata &clearExif();

        ImageMetadata &clearIptc();

        [[nodiscard]] qsizetype exifCount() const;

        [[nodiscard]] qsizetype iptcCount() const;

        KVList EXIF_metadata;
        KVList IPTC_metadata;
    };

    struct PresentationDetails {
        using index_t = int;
        inline static const QString EXIF_LABEL = "EXIF";
        inline static const QString IPTC_LABEL = "IPTC";
        inline static const index_t INVALID_INDEX = -1;

        index_t exifLabelLocation = INVALID_INDEX;
        index_t iptcLabelLocation = INVALID_INDEX;
        index_t exifDataStart = 0;
        index_t exifDataEnd = 0;
        index_t iptcDataStart = 0;
        index_t iptcDataEnd = 0;
    };

public:
    explicit MetadataModel(QObject *parent = nullptr);

    [[nodiscard]] int rowCount(const QModelIndex &parent) const override;

    [[nodiscard]] int columnCount(const QModelIndex &parent) const override;

    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;

    static ImageMetadata loadImageMetadata(const QString &filepath);

public slots:

    void clearStoredMetadata();

    void loadAndParseImage(const QString &filepath);

private:
    void calculatePresentationDetails();

    [[nodiscard]] QVariant dataForDisplay(const QModelIndex &index) const;

private:
    // Current metadata
    ImageMetadata m_metadata;

    // Current presentation details
    PresentationDetails m_presentationDetails;
};


#pragma clang diagnostic pop