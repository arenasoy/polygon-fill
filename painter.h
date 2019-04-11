#ifndef PAINTER_H
#define PAINTER_H

#include <QOpenGLWidget>
#include <QtGui>
#include <QWidget>
#include <vector>
#include <QMouseEvent>
#include <QLabel>

using namespace std;


class Painter : public QOpenGLWidget {

private:
    vector<QPoint> point;
    vector<QLine> line;
    vector<QLabel*> coordinates;
    bool finished = false;
    bool finish = false;
    vector<QLine> polygon;
    void fillPolygon();
    QColor fillColor = Qt::white;

protected:
    void paintGL();
    void mousePressEvent(QMouseEvent *event);

public:
    Painter(QWidget *parent);
    void clear();
    void changeColor( QColor color);

};

#endif
