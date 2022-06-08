#include <QApplication>
#include "DebugHelpers.hpp"
#include "MainWindow.hpp"




int main(int argc, char* argv[])
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(800, 600);
    mainWindow.show();

    int result = QApplication::exec();
    return result;
}