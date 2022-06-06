#pragma once

#include <QToolBar>

class MainWindow;

class ToolBar : public QObject{

    Q_OBJECT

public:
    ToolBar(MainWindow* mainWindow);
    ~ToolBar() override;

private slots:
    void openDir();
    void generateInfoFile();
    void saveImageModified();
    void loadExternalData();

private:
    QToolBar* toolBar;

};