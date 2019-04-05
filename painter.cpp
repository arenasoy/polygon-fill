#include "painter.h"

void Painter::mousePressEvent(QMouseEvent *event) {
    point.push_back(event->pos());
    update();
}

void Painter::paintGL() {
    QPainter painter(this);
    QPen pen(1);
    pen.setColor(Qt::white);

    painter.setPen(pen);

    for (vector<QPoint>::iterator i = point.begin(); i != point.end(); i++) {
            painter.drawPoint(*i);
    }

    int size = point.size();

    for(int i = 0; i < size - 1; i++) {
        painter.drawLine(point[i], point[i + 1]);
    }

    if (point.size() > 0) {
        //TODO: display coordinates of every point?
        coordinates = new QLabel(this);
        coordinates->setText("(" + QString::number(point[size-1].x()) + ", " + QString::number(point[size-1].y()) + ")");
        coordinates->setStyleSheet("color: white");
        //TODO: verify if point is inside the screen
        coordinates->setGeometry(point[size-1].x(), point[size-1].y(), 200, 15);
        coordinates->show();
    }
}
