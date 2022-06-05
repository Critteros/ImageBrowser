#pragma once

#include <QFileIconProvider>
#include <QObject>

#include "DebugHelpers.hpp"


class CustomIconProvider : public QObject, public QFileIconProvider {
Q_OBJECT
public:
    explicit CustomIconProvider(QObject *parent = nullptr);

    [[nodiscard]] QIcon icon(const QFileInfo &info) const override;

    void setAllowedExtensions(const QStringList &extensions);

public slots:

    void onIconSizeChange(const QSize &newSize);

private:
    QSize m_thumbSize{60, 60};
    QStringList m_thumbExtensions = {"jpg", "png"};
};


