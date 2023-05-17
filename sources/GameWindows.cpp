#include "GameWindows.h"
#include <QDebug>
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QStatusBar>

void GameWindows::widgetFinishGame(int n) {
    if (n != 0) {
        this->setStyleSheet("background-color: lavender;");
        if (n == 1) {
            auto *label = new QLabel("You've lost", this);
            label->setFont(QFont("Courier New", 30));
            label->move(435, 385);
        }
        if (n == 2) {
            auto *label = new QLabel("You WIN!!!!", this);
            label->setFont(QFont("Courier New", 30));
            label->move(435, 385);
        }

        auto *exit = new QPushButton("Exit", this);
        exit->resize(160, 80);
        exit->setFont(QFont("Courier New", 20));
        exit->move(235, 600);

        connect(exit, &QPushButton::clicked, this, [&] {
            qApp->exit();
        });

        auto *replay = new QPushButton("Replay", this);
        replay->resize(160, 80);
        replay->setFont(QFont("Courier New", 20));
        replay->move(735, 600);

        connect(replay, &QPushButton::clicked, this, [&] {
            close();
            emit Replay();
        });
        showFullScreen();
        this->setFixedSize(1200, 800);
        this->move(360, 140);
    }

}

void GameWindows::widgetStartGame() {
    this->setStyleSheet(
            "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgb(128,128,255), stop:1 rgb(128,255,208));");
    auto *label = new QLabel("Hello my friend", this);
    label->setFont(QFont("Courier New", 30));
    label->move(705, 400);
    label->setStyleSheet("background-color: transparent");

    auto *play = new QPushButton("Play", this);
    play->resize(250, 80);
    play->setFont(QFont("Courier New", 20));
    play->move(835, 600);
    play->setStyleSheet("background-color: rgb(128,160,255);");

    auto *settings = new QPushButton("Settings", this);
    settings->resize(250, 80);
    settings->setFont(QFont("Courier New", 20));
    settings->move(835, 700);
    settings->setStyleSheet("background-color: rgb(128,160,255);");


    auto *exit = new QPushButton("Exit", this);
    exit->resize(250, 80);
    exit->setFont(QFont("Courier New", 20));
    exit->move(835, 800);
    exit->setStyleSheet("background-color: rgb(128,160,255);");


    connect(play, &QPushButton::clicked, this, [&] {
        close();
        emit Start();
    });

    connect(settings, &QPushButton::clicked, this, [&] {
        auto *widget = new QWidget;
        widget->setStyleSheet(
                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1,   stop:0 rgb(64,64,255), stop:1 rgb(128,128,128));");
        auto *actions = new QLabel("ACTIONS", widget);
        actions->setFont(QFont("Courier New", 30));
        actions->move(100, 150);
        actions->setStyleSheet("background-color: transparent");

        auto *move_up = new QLabel("Move up", widget);
        move_up->setFont(QFont("Courier New", 20));
        move_up->move(100, 300);
        move_up->setStyleSheet("background-color: transparent");

        auto *move_down = new QLabel("Move down", widget);
        move_down->setFont(QFont("Courier New", 20));
        move_down->move(100, 375);
        move_down->setStyleSheet("background-color: transparent");

        auto *move_right = new QLabel("Move right", widget);
        move_right->setFont(QFont("Courier New", 20));
        move_right->move(100, 450);
        move_right->setStyleSheet("background-color: transparent");

        auto *move_left = new QLabel("Move left", widget);
        move_left->setFont(QFont("Courier New", 20));
        move_left->move(100, 525);
        move_left->setStyleSheet("background-color: transparent");

        auto *move_diagonal = new QLabel("Move diagonal", widget);
        move_diagonal->setFont(QFont("Courier New", 20));
        move_diagonal->move(100, 600);
        move_diagonal->setStyleSheet("background-color: transparent");

        auto *keyboard = new QLabel("KEYBOARD", widget);
        keyboard->setFont(QFont("Courier New", 30));
        keyboard->move(700, 150);
        keyboard->setStyleSheet("background-color: transparent");

        auto *up = new QPushButton("W", widget);
        up->setFont(QFont("Courier New", 20));
        up->resize(500, 50);
        up->move(700, 300);
        up->setStyleSheet(("QPushButton"
                           "{"
                           "background-color : rgb(64,64,255);"
                           "}"
                           "QPushButton::pressed"
                           "{"
                           "background-color : rgb(128,128,128);"
                           "}"
                          ));

        auto *down = new QPushButton("S", widget);
        down->setFont(QFont("Courier New", 20));
        down->resize(500, 50);
        down->move(700, 375);
        down->setStyleSheet(("QPushButton"
                             "{"
                             "background-color : rgb(64,64,255);"
                             "}"
                             "QPushButton::pressed"
                             "{"
                             "background-color : rgb(128,128,128);"
                             "}"
                            ));

        auto *right = new QPushButton("D", widget);
        right->setFont(QFont("Courier New", 20));
        right->resize(500, 50);
        right->move(700, 450);
        right->setStyleSheet(("QPushButton"
                              "{"
                              "background-color : rgb(64,64,255);"
                              "}"
                              "QPushButton::pressed"
                              "{"
                              "background-color : rgb(128,128,128);"
                              "}"
                             ));

        auto *left = new QPushButton("A", widget);
        left->setFont(QFont("Courier New", 20));
        left->resize(500, 50);
        left->move(700, 525);
        left->setStyleSheet(("QPushButton"
                             "{"
                             "background-color : rgb(64,64,255);"
                             "}"
                             "QPushButton::pressed"
                             "{"
                             "background-color : rgb(128,128,128);"
                             "}"
                            ));

        auto *diagonal = new QPushButton("A or D + W or S", widget);
        diagonal->setFont(QFont("Courier New", 20));
        diagonal->resize(500, 50);
        diagonal->move(700, 600);
        diagonal->setStyleSheet(("QPushButton"
                                 "{"
                                 "background-color : rgb(64,64,255);"
                                 "}"
                                 "QPushButton::pressed"
                                 "{"
                                 "background-color : rgb(128,128,128);"
                                 "}"
                                ));

        auto *back = new QPushButton("<< back <<", widget);
        back->setFont(QFont("Courier New", 15));
        back->setStyleSheet("QPushButton {font-weight: bold}");
        back->resize(200, 50);
        back->move(100, 50);
        back->setStyleSheet("background-color: transparent");

        connect(back, &QPushButton::clicked, [widget]() {
            widget->deleteLater();
        });
        widget->showFullScreen();
    });

    connect(exit, &QPushButton::clicked, this, [&] {
//        auto answer = QMessageBox::question(this, "Question", "Are you sure?");
//        QStatusBar statusBar;
//        statusBar.showMessage(answer == QMessageBox::Yes ? "YES" : "NO");
//        if (answer == QMessageBox::Yes) {
        qApp->exit();
//        }
    });
    showFullScreen();
}

GameWindows::GameWindows(QWidget *parent, QGraphicsScene *scene) : scene_(scene) {}

