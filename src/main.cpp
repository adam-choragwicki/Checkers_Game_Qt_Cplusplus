#include "game.h"
#include "log_manager.h"
#include <QApplication> // TODO remove eventually

int main(int argc, char* argv[])
{
    try
    {
#if defined(QT_DEBUG)
        LogManager::initialize(LogManager::Mode::LogToFileAndConsole, LogManager::Verbosity::Debug);
#else
        LogManager::initialize(LogManager::Mode::LogToFileOnly, LogManager::Verbosity::Info);
#endif

        QApplication app(argc, argv); // TODO change to QGuiApplication

        Game game;

        return QApplication::exec(); // TODO change to QGuiApplication
    }
    catch (const std::exception& e)
    {
        qCritical() << "Unhandled exception:" << e.what();
        return 1;
    }
    catch (...)
    {
        qCritical() << "Unhandled unknown exception";
        return 1;
    }
}

//TODO add shadows showing possible movements
//TODO get rid of Drawer class
//TODO implement state pattern for Piece state
//TODO optimize multi-capture manager
//TODO optimize player manager
//TODO encapsulate Model's move in progress boolean

//TODO add complete logging and fix subtle movement bugs
