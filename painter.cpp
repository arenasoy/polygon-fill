#include "painter.h"

Painter::Painter(QWidget *parent) : QOpenGLWidget (parent) {};

bool sortBySecond(const tuple<int, double, double>& a,
               const tuple<int, double, double>& b) {
    return (get<1>(a) < get<1>(b));
}

//on mouse press, save new point and draw an edge between the last and the new
void Painter::mousePressEvent(QMouseEvent *event) {
    point.push_back(event->pos());

    if (point.size() > 2
            && abs(point.back().x() - point.front().x()) <= 5
            && abs(point.back().y() - point.front().y()) <= 5) {
        point.back().setX(point.front().x());
        point.back().setY(point.front().y());
        finish = true;
    }

    if (point.size() > 1)
        line.push_back(QLine(point[point.size() - 2], point.back()));
    update();
}

//clear the screen
void Painter::clear() {

    for(int i = 0; i < coordinates.size(); i++) {
        coordinates[i]->clear();
    }
    coordinates.clear();
    point.clear();
    line.clear();
    finished = false;
    finish = false;
    polygon.clear();
    this->setEnabled(true);
    update();
}

//change color to fill the polygon
void Painter::changeColor( QColor color )
{
    fillColor = color;
}

void Painter::paintGL() {

    QPainter painter(this);
    QPen pen(1);
    pen.setColor(fillColor);
    painter.setPen(pen);

    //if polygon is finished, draw the polygon
    if (finished) {
        for(int i = 0; i < polygon.size(); i++) {
            painter.drawLine(polygon[i]);
        }
        return;
    }

    //if it is not, draw every point
    for (vector<QPoint>::iterator i = point.begin(); i != point.end(); i++) {
            painter.drawPoint(*i);
    }

    int size = line.size();

    //draw every edge
    for(int i = 0; i < size; i++) {
        painter.drawLine(line[i]);
    }

    if (point.size() > 0) {

        //if user just draw the finish point
        //executes the fill algorithm for the first time
        //and saves the result in polygon (to not need
        //to execute the algorithm everytime screens repaint)
        if (finish) {
            fillPolygon();
            this->setEnabled(false);
            finished = true;
            return;
        }

        //or just draw another coordinates point
        coordinates.push_back(new QLabel(this));
        coordinates.back()->setText("(" + QString::number(point.back().x()) + ", " + QString::number(point.back().y()) + ")");
        coordinates.back()->setStyleSheet("color: white");
        coordinates.back()->setGeometry(point.back().x(), point.back().y(), 200, 15);
        coordinates.back()->show();
    }
}

void Painter::fillPolygon() {

    QPainter painter(this);
    QPen pen(1);
    pen.setColor(Qt::white);
    painter.setPen(pen);

    int height = painter.device()->height();

    vector<tuple<int, double, double>> et[height];

    vector<tuple<int, double, double>> aet;

    //fill et
    for(int i = 0; i < line.size(); i++) {
        QLine l = line[i];
        if (l.y1() != l.y2()) {
            int ymin = (l.y1() < l.y2() ? l.y1() : l.y2());
            int xmin = (l.y1() < l.y2() ? l.x1() : l.x2());
            int ymax = (l.y1() < l.y2() ? l.y2() : l.y1());
            int xmax = (l.y1() < l.y2() ? l.x2() : l.x1());
            double m = (ymax - ymin) / double(xmax - xmin);

            et[ymin].push_back(make_tuple(ymax, double(xmin), 1/m));

        }
    }

    for (int i = 0; i < height; i++) {
        //get all et elements of line and put in aet
        while (!et[i].empty()) {
            aet.push_back(et[i].front());
            et[i].erase(et[i].begin());
        }

        //sort by x
        sort(aet.begin(), aet.end(), sortBySecond);

        //erase all that finish at that line
        for (int j = 0; j < aet.size(); j++) {
            if (get<0>(aet[j]) == i) {
                aet.erase(aet.begin() + j);
                j--;
            }
        }

        if (aet.empty()) continue;

        //fill pixels
        for (int j = 0; j < aet.size(); j++) {
            //TODO check rules for rounding
            int start = get<1>(aet[j]);
            int end = ceil(get<1>(aet[++j]));

            painter.drawLine(start, i, end - 1, i);
            polygon.push_back(QLine(start, i, end - 1, i));
        }

        //update x values
        for (int j = 0; j < aet.size(); j++) {
            get<1>(aet[j]) = (get<1>(aet[j]) + get<2>(aet[j]));
        }

    }

}


