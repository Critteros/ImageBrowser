#pragma once

#include <QMainWindow>
#include <QSplitter>
#include <QTableView>


#include "MetadataWidget.hpp"
#include "CustomIconProvider.hpp"
#include "ClickableLabel.hpp"
#include "FileExplorer.hpp"


#include "DebugHelpers.hpp"

class MainWindow : public QMainWindow {
Q_OBJECT

public:
    MainWindow();

    ~MainWindow() override;

private:
    // Constants
    inline static const QSize MAIN_WIDGET_MIN_SIZE = QSize(800, 600);
    inline static const QSize FILE_ICON_SIZE = QSize(128, 128);

private:
    // Layout organizer
    QSplitter *m_splitter = nullptr;

    // Components
    FileExplorer *m_fileExplorer = nullptr;


    QTableView *m_metadataView = nullptr;
};