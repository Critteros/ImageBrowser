#pragma once

#include <QToolBar>

class MainWindow;

class ToolBar : public QObject{

    Q_OBJECT

public:
    explicit ToolBar(MainWindow* mainWindow);
    ~ToolBar() override;

private slots:
    void openDir();
    void generateInfoFile();
    void saveImageModified();
    void loadExternalData();

signals:
    void dirChanged(const QString &dirPath);

private:
    QToolBar* toolBar;

};