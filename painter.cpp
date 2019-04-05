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

    bool end = false;

    if (point.size() > 2
            && abs(point.back().x() - point.front().x()) <= 5
            && abs(point.back().y() - point.front().y()) <= 5) {
        point.back().setX(point.front().x());
        point.back().setY(point.front().y());
        end = true;
    }

    for (vector<QPoint>::iterator i = point.begin(); i != point.end(); i++) {
            painter.drawPoint(*i);
    }

    int size = point.size();

    for(int i = 0; i < size - 1; i++) {
        line.push_back(QLine(point[i], point[i + 1]));
        painter.drawLine(line.back());
    }

    if (point.size() > 0) {
        //TODO: display coordinates of every point?
        if (end) {
            fillPolygon();
            //TODO end app
        }
        coordinates = new QLabel(this);
        coordinates->setText("(" + QString::number(point.back().x()) + ", " + QString::number(point.back().y()) + ")");
        coordinates->setStyleSheet("color: white");
        //TODO: verify if point is inside the screen
        coordinates->setGeometry(point.back().x(), point.back().y(), 200, 15);
        coordinates->show();
    }
}

void Painter::fillPolygon() {
    QTextStream(stdout) << "filling" << endl;
    QPainter painter(this);

    //TODO define max height
    int height = painter.device()->height();

    vector<tuple<int, double, double>> et[height];

    vector<tuple<int, double, double>> aet;

    for(vector<QLine>::iterator i = line.begin(); i != line.end(); i++) {
        if ((*i).isNull()) break;
        if ((*i).y1() != (*i).y2()) {
            int ymin = ((*i).y1() < (*i).y2() ? (*i).y1() : (*i).y2());
            int xmin = ((*i).x1() < (*i).x2() ? (*i).x1() : (*i).x2());
            int ymax = ((*i).y1() > (*i).y2() ? (*i).y1() : (*i).y2());
            int xmax = ((*i).x1() > (*i).x2() ? (*i).x1() : (*i).x2());
            if (ymin >= 0 && xmin >= 0 && ymax < height) {
                double m = (xmin - xmax);
                if ((*i).x1() == xmin) m /= ((*i).y1() - (*i).y2());
                else m /= ((*i).y2() - (*i).y1());
                et[ymin].push_back(tuple<int, double, double> (ymax, xmin, 1/m));
            }
        }
        line.erase(i);
    }

    QTextStream(stdout) << "et" << endl;

    this->close();
}
