#include <QApplication>
#include "DebugHelpers.hpp"
#include "MainWindow.hpp"




int main(int argc, char* argv[])
{
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

    QApplication application(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();


    return QApplication::exec();
}