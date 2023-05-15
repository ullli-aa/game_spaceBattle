#include "MainWindow.h"
#include <QGraphicsProxyWidget>
#include <QDebug>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          scene_(new QGraphicsScene(this)),
          view_(new QGraphicsView(this)),
          presenter(new Presenter(this)) {
    resize(maximumWidth(), maximumHeight());
    scene_->setSceneRect(1, 1, 1918, 1078);
    view_->setFixedSize(1920, 1080);
    view_->setScene(scene_);
    setUpScene();
    setFocusPolicy(Qt::StrongFocus);
    view_->viewport()->installEventFilter(this);
    animation_timer_.start(20, this);
}

void MainWindow::setUpScene() {
    scene_->addItem(presenter->getModel().hero_);
    for (int i = 0; i < 10; ++i) {
        scene_->addItem(presenter->getModel().heroBullet[i]);
    }
    scene_->addItem(presenter->getModel().boss_);
    scene_->addItem(presenter->getModel().bossBullet);

    for (int i = 0; i < presenter->getModel().enemies_.size(); ++i) {
        scene_->addItem(presenter->getModel().enemies_[i]);
    }

    scene_->addItem(presenter->getModel().firstEnemyBullet);
    scene_->addItem(presenter->getModel().secondEnemyBullet);

    bossHp = scene_->addText(QString::number(presenter->getModel().boss_->getHp()));
    bossHp->setDefaultTextColor(QColor(Qt::darkRed));
    bossHp->setFont(QFont("Courier New", 20));
    bossHp->setPos(25, 25);

    heroHealth = scene_->addText(QString::number(presenter->getModel().hero_->getHealth()));
    heroHealth->setDefaultTextColor(QColor(Qt::darkRed));
    heroHealth->setFont(QFont("Courier New", 20));
    heroHealth->setPos(25, 60);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
//    if (obj == view_->viewport()) {
//        if (event->type() == QEvent::MouseMove) {
//            auto *mouseEvent = dynamic_cast<QMouseEvent *>(event);
//            presenter->getModel().hero_->setCoordinates(mouseEvent->pos());
//        }
//    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    auto xd = presenter->getModel().hero_->getDirection().x();
    auto yd = presenter->getModel().hero_->getDirection().y();
    if (event->key() == Qt::Key_A) {
        presenter->getModel().hero_->setDirection({-1, yd});
    }
    if (event->key() == Qt::Key_S) {
        presenter->getModel().hero_->setDirection({xd, 1});
    }
    if (event->key() == Qt::Key_D) {
        presenter->getModel().hero_->setDirection({1, yd});
    }
    if (event->key() == Qt::Key_W) {
        presenter->getModel().hero_->setDirection({xd, -1});
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    auto xd = presenter->getModel().hero_->getDirection().x();
    auto yd = presenter->getModel().hero_->getDirection().y();
    if (event->key() == Qt::Key_A || event->key() == Qt::Key_D) {
        presenter->getModel().hero_->setDirection({0, yd});
    }
    if (event->key() == Qt::Key_W || event->key() == Qt::Key_S) {
        presenter->getModel().hero_->setDirection({xd, 0});
    }
}

void MainWindow::timerEvent(QTimerEvent *event) {
    if (event->timerId() == animation_timer_.timerId()) {
        presenter->Tick();
        if (timerChange % 8 == 0) {
            presenter->getModel().heroBullet[attack]->setCoordinates(
                    {presenter->getModel().hero_->getCoordinates().x() + 70,
                     presenter->getModel().hero_->getCoordinates().y()});
            presenter->getModel().heroBullet[attack]->setDirection({40, 0});

            if (attack == 0) {
                attack = 10;
            }
            --attack;
        }

        if (timerChange == 200) {
            timerChange = 0;
        }
        ++timerChange;
    }

    presenter->bossMoving();
    presenter->firstEnemyMoving();
    presenter->secondEnemyMoving();
    presenter->bulletFirstEnemyMoving();
    presenter->bulletSecondEnemyMoving();

    if (timerChange % 10 < 5) {
        presenter->getModel().bossBullet->setDirection({-8, -2});
    } else {
        presenter->getModel().bossBullet->setDirection({-8, 2});
    }

    presenter->collidesHeroBullet();
    presenter->collidesBossBullet();
    presenter->collidesFirstEnemyBullet();
    presenter->collidesSecondEnemyBullet();

    bossHp->setPlainText(QString::number(presenter->getModel().boss_->getHp()));

    presenter->getModel().hero_->setHealth(presenter->getModel().hero_->getHp() / 60 + 1);
    if (presenter->getModel().hero_->getHp() == 300) {
        presenter->getModel().hero_->setHealth(5);
    }
    if (presenter->getModel().hero_->getHp() == 0) {
        presenter->getModel().hero_->setHealth(0);
    }
    heroHealth->setPlainText(QString::number(presenter->getModel().hero_->getHealth()));

    if(presenter->finishGame() != 0) {
        widget_ = new QWidget;
        widget_->setStyleSheet("background-color: lavender;");
        if(presenter->finishGame() == 1) {
            auto* label = new QLabel("You've lost", widget_);
            label->setFont(QFont("Courier New", 30));
            label->move(435, 385);
        }
        if(presenter->finishGame() == 2) {
            auto* label = new QLabel("You WIN!!!!", widget_);
            label->setFont(QFont("Courier New", 30));
            label->move(435, 385);
        }

        auto* exit = new QPushButton("Exit", widget_);
        exit->resize(160, 80);
        exit->setFont(QFont("Courier New", 20));
        exit->move(235, 600);

        auto* replay = new QPushButton("Replay", widget_);
        replay->resize(160, 80);
        replay->setFont(QFont("Courier New", 20));
        replay->move(735, 600);

        QGraphicsProxyWidget* item = scene_->addWidget(widget_);
        item->resize(1200, 800);
        item->setPos(360, 140);
        animation_timer_.stop();

        connect(replay, &QPushButton::clicked, this, [&] {
            scene_->removeItem(widget_->graphicsProxyWidget());
            presenter->replayModel();
            animation_timer_.start(20, this);
            timerChange = 0;
        });

        connect(exit, &QPushButton::clicked, this, [&] {
            close();
        });
    }
    presenter->menuProcess();
    presenter->getModel().updateModel();
}