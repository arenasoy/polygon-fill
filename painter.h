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
    QLabel *coordinates;
    void fillPolygon();
    bool finished = false;
    vector<QLine> polygon;

protected:
    void paintGL();

    void mousePressEvent(QMouseEvent *event);

};

#endif
