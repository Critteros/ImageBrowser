#pragma once

#include <QStackedWidget>
#include <QWidget>
#include <QFileSystemModel>
#include <QListView>


#include "ClickableLabel.hpp"

#include "DebugHelpers.hpp"

class ImageViewer : public QStackedWidget {
Q_OBJECT

public:
    explicit ImageViewer(QWidget *parent = nullptr);

private:
    void setupFileView();

    void setupImagePreview();

    void setFileModel(QFileSystemModel *model);

signals:

    void iconSizeChanged(const QSize &newSize);


private:
    QListView *m_listView = nullptr;
    QFileSystemModel *m_filesystemModel = nullptr;
    ClickableLabel *m_imageLabel = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
};