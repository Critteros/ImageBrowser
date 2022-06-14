#include <QApplication>
#include "DebugHelpers.hpp"
#include "MainWindow.hpp"
#include "utils.hpp"
#include <QStyleFactory>



int main(int argc, char* argv[])
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    QApplication application(argc, argv);
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    application.setPalette(getPalette());
    MainWindow mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.show();

    int result = QApplication::exec();
    return result;
}