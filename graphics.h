#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <vector>
#include <iostream>
using namespace std;

// Расширяем класс QGraphicsView
class graphics : public QGraphicsView
{
    Q_OBJECT
public:
    explicit graphics(QWidget *parent = 0);
    ~graphics();

    void FillToDraw1Vec(vector<float> &vecf);
signals:

private slots:
    void slotAlarmTimer();  /* слот для обработчика переполнения таймера
                             * в нём будет производиться перерисовка
                             * виджета
                             * */

private:
    QGraphicsScene      *scene;     // Объявляем сцену для отрисовки
    QGraphicsItemGroup  *group_1;   // Объявляем первую группу элементов
    QGraphicsItemGroup  *group_2;   // Объявляем вторую группу элементов

    /* Таймер для задержки отрисовки.
     * Дело в том, что при создании окна и виджета
     * необходимо некоторое время, чтобы родительский слой
     * развернулся, чтобы принимать от него адекватные параметры
     * ширины и высоты
     * */
    QTimer              *timer;

    vector<vector <pair <float,float>>> ToDraw1;

private:
    /* Перегружаем событие изменения размера окна,
     * чтобы перехватывать его
     * */
    void resizeEvent(QResizeEvent *event);
    /* Метод для удаления всех элементов
     * из группы элементов
     * */
    void deleteItemsFromGroup(QGraphicsItemGroup *group_1);

};

#endif // GRAPHICS_H
