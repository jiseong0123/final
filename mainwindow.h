#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMap>
#include <QVector>
#include <QString>
QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QListWidget;
class QListWidgetItem;
QT_END_NAMESPACE
struct Flight {
    QString code;
    QString from;
    QString to;
    int price;
    QString duration;
};
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    QMap<QString, QVector<Flight>> graph;
    QWidget *centralWidget;
    QLabel *mapLabel;
    QListWidget *flightList;
    void setupUI();
    void setupGraph();
    void addCityButton(const QString &city, int x, int y);
    void showFlightsFromCity(const QString &city);
private slots:
    void onFlightClicked(QListWidgetItem *item);
};
#endif // MAINWINDOW_H