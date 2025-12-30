#include "game.h"
#include <QQmlContext>

Game::Game()
{
    // printAppInfo(); // TODO restore this

    gameConfig_ = std::make_unique<GameConfig>();

    model_ = std::make_unique<Model>(*gameConfig_);
    view_ = std::make_unique<QQmlApplicationEngine>();
    controller_ = std::make_unique<Controller>(*gameConfig_, *model_, *view_);

    exposeDataToQml();

    initializeQmlEngine();

    connect(controller_.get(),
            &Controller::applicationShutdownRequested,
            this,
            []()
            {
                QMetaObject::invokeMethod(QCoreApplication::instance(),
                                          []()
                                          {
                                              QCoreApplication::quit();
                                          },
                                          Qt::QueuedConnection);
            });

    connect(QCoreApplication::instance(),
            &QCoreApplication::aboutToQuit,
            []()
            {
                // TODO Future cleanup (save configs, close files, etc.)
                qInfo() << "Exiting application";
            });
}

void Game::printAppInfo()
{
    qInfo() << "Application version:" << APP_VERSION;
    qInfo() << "Qt version:" << QT_VERSION_STR;
    qInfo() << "Build type:" << BUILD_TYPE;

#if defined(Q_OS_WIN)
    qInfo() << "OS: Windows";
#elif defined(Q_OS_LINUX)
    qInfo() << "OS: Linux";
#endif
}

void Game::exposeDataToQml() const
{
    view_->rootContext()->setContextProperty("gameModel", model_.get());
    view_->rootContext()->setContextProperty("Controller", controller_.get());

    view_->rootContext()->setContextProperty("piecesModel", model_->getPiecesModel());
    // view_->rootContext()->setContextProperty("powerPelletsModel", &model_->getPowerPelletsModel()); // TODO remove

    // view_->rootContext()->setContextProperty("pacman", &model_->getPacman()); // TODO remove
    // view_->rootContext()->setContextProperty("blueGhost", &model_->getBlueGhost()); // TODO remove
    // view_->rootContext()->setContextProperty("orangeGhost", &model_->getOrangeGhost()); // TODO remove
    // view_->rootContext()->setContextProperty("purpleGhost", &model_->getPurpleGhost()); // TODO remove
    // view_->rootContext()->setContextProperty("redGhost", &model_->getRedGhost()); // TODO remove
}

void Game::initializeQmlEngine()
{
    /*
     * Rationale for the below QML setup:
     * - QQmlApplicationEngine::load() is effectively asynchronous; rootObjects() may be empty immediately.
     * - We rely on objectCreated() as the reliable success/failure notification.
     * - On failure we queue QCoreApplication::exit(1) (via a queued invoke) so the exit code is honored even
     *   if this runs before the event loop starts. Calling exit/quit directly here can be ignored otherwise.
     * - Qt::SingleShotConnection ensures the handler runs exactly once (avoids double-calls on reloads).
     */
    connect(view_.get(),
            &QQmlApplicationEngine::objectCreated,
            controller_.get(),
            [this](QObject* obj, const QUrl& url)
            {
                if (!obj)
                {
                    qCritical() << "QML root creation failed for" << url;

                    QMetaObject::invokeMethod(QCoreApplication::instance(),
                                              []()
                                              {
                                                  QCoreApplication::exit(1);
                                              },
                                              Qt::QueuedConnection);

                    return;
                }

                controller_->onQmlEngineFullyInitialized();
            },
            Qt::SingleShotConnection);

    view_->loadFromModule("CheckersQml", "Main");
}
