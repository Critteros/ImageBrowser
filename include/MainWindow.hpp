#pragma once

#include <QMainWindow>
#include <QFileSystemModel>
#include <QListView>
#include <QSplitter>
#include <QLabel>
#include <QStackedWidget>
#include <QTableView>


#include "MetadataWidget.hpp"
#include "CustomIconProvider.hpp"
#include "ClickableLabel.hpp"
#include "ImageViewer.hpp"


#include "DebugHelpers.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    void setupFileView();

    void setupFileModel();


private:
    QFileSystemModel *m_filesystemModel = nullptr;
    QListView *m_fileView = nullptr;
    QSplitter *m_splitter = nullptr;
    QTableView *m_metadataView = nullptr;
    QStackedWidget *m_stackedWidget = nullptr;
    ClickableLabel *m_imageDisplay = nullptr;


    CustomIconProvider *m_iconProvider = nullptr;
};