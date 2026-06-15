#include "mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QMessageBox>
#include <QFont>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupGraph();
    setupUI();
}
MainWindow::~MainWindow() {
}
void MainWindow::setupGraph() {
    graph["ICN"] = {
        {"KE101", "ICN", "JFK", 1200000, "14시간 20분"},
        {"OZ201", "ICN", "NRT", 350000, "2시간 20분"},
        {"LJ301", "ICN", "CJU", 80000, "1시간 10분"}
    };
    graph["CJU"] = {
        {"LJ302", "CJU", "GMP", 85000, "1시간 20분"},
        {"TW701", "CJU", "PUS", 70000, "1시간 00분"}
    };
    graph["JFK"] = {
        {"DL401", "JFK", "LAX", 300000, "6시간 10분"},
        {"AA402", "JFK", "ICN", 1250000, "15시간 00분"}
    };
    graph["NRT"] = {
        {"JL501", "NRT", "ICN", 360000, "2시간 30분"},
        {"NH502", "NRT", "LAX", 900000, "10시간 40분"}
    };
    graph["LAX"] = {
        {"UA601", "LAX", "JFK", 320000, "5시간 50분"},
        {"KE602", "LAX", "ICN", 1300000, "13시간 40분"}
    };
    graph["PUS"] = {
        {"BX801", "PUS", "CJU", 65000, "55분"},
        {"BX802", "PUS", "ICN", 95000, "1시간 05분"}
    };
}
void MainWindow::setupUI() {
    setWindowTitle("항공권 조회 및 예매 프로그램");
    resize(1100, 650);
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mapLabel = new QLabel;
    mapLabel->setFixedSize(760, 560);
    mapLabel->setStyleSheet("background-color: #20252b; border: 1px solid gray;");
    mapLabel->setScaledContents(true);
    QPixmap mapPixmap("world_map.jpg");
    if (!mapPixmap.isNull()) {
        mapLabel->setPixmap(mapPixmap);
    } else {
        mapLabel->setText("world_map.jpg 파일을 프로젝트 폴더에 넣어주세요.");
        mapLabel->setAlignment(Qt::AlignCenter);
        mapLabel->setStyleSheet("color: white; background-color: #20252b;");
    }
    QWidget *mapContainer = new QWidget;
    mapContainer->setFixedSize(760, 560);
    QVBoxLayout *mapContainerLayout = new QVBoxLayout(mapContainer);
    mapContainerLayout->setContentsMargins(0, 0, 0, 0);
    mapContainerLayout->addWidget(mapLabel);
    mapLabel->setParent(mapContainer);
    addCityButton("ICN", 300, 120);
    addCityButton("CJU", 300, 180);
    addCityButton("PUS", 350, 170);
    addCityButton("NRT", 350, 140);
    addCityButton("JFK", 620, 140);
    addCityButton("LAX", 560, 160);
    QWidget *rightPanel = new QWidget;
    rightPanel->setFixedWidth(300);
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    QLabel *titleLabel = new QLabel("항공편 정보");
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    flightList = new QListWidget;
    flightList->setStyleSheet(
        "QListWidget {"
        "  background-color: #1f252b;"
        "  color: white;"
        "  border: 1px solid gray;"
        "}"
        "QListWidget::item {"
        "  padding: 10px;"
        "  border-bottom: 1px solid #444;"
        "}"
        "QListWidget::item:selected {"
        "  background-color: #2d8cff;"
        "}"
        );
    rightLayout->addWidget(titleLabel);
    rightLayout->addWidget(flightList);
    mainLayout->addWidget(mapContainer);
    mainLayout->addWidget(rightPanel);
    connect(flightList, &QListWidget::itemClicked, this, &MainWindow::onFlightClicked);
}
void MainWindow::addCityButton(const QString &city, int x, int y) {
    QPushButton *btn = new QPushButton(city, mapLabel);
    btn->setGeometry(x, y, 50, 28);
    btn->setStyleSheet(
        "QPushButton {"
        "  background-color: rgba(0, 102, 204, 200);"
        "  color: white;"
        "  border-radius: 8px;"
        "  font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "  background-color: rgba(0, 140, 255, 220);"
        "}"
        );
    connect(btn, &QPushButton::clicked, this, [=]() {
        showFlightsFromCity(city);
    });
}
void MainWindow::showFlightsFromCity(const QString &city) {
    flightList->clear();
    if (!graph.contains(city)) {
        return;
    }
    const QVector<Flight> &flights = graph[city];
    for (const Flight &f : flights) {
        QString text = QString("[%1] %2 -> %3 | %4원 | %5")
                           .arg(f.code)
                           .arg(f.from)
                           .arg(f.to)
                           .arg(f.price)
                           .arg(f.duration);
        QListWidgetItem *item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, f.code);
        item->setData(Qt::UserRole + 1, f.from);
        item->setData(Qt::UserRole + 2, f.to);
        item->setData(Qt::UserRole + 3, f.price);
        item->setData(Qt::UserRole + 4, f.duration);
        flightList->addItem(item);
    }
}
void MainWindow::onFlightClicked(QListWidgetItem *item) {
    QString code = item->data(Qt::UserRole).toString();
    QString from = item->data(Qt::UserRole + 1).toString();
    QString to = item->data(Qt::UserRole + 2).toString();
    int price = item->data(Qt::UserRole + 3).toInt();
    QString duration = item->data(Qt::UserRole + 4).toString();
    QString message = QString("예매가 완료되었습니다.\n\n"
                              "항공편: %1\n"
                              "구간: %2 -> %3\n"
                              "가격: %4원\n"
                              "소요 시간: %5")
                          .arg(code)
                          .arg(from)
                          .arg(to)
                          .arg(price)
                          .arg(duration);
    QMessageBox::information(this, "예매 완료", message);
}
