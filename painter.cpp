#include "painter.h"

bool sortBySecond(const tuple<int, double, double>& a,
               const tuple<int, double, double>& b) {
    return (get<1>(a) < get<1>(b));
}

void Painter::mousePressEvent(QMouseEvent *event) {
    point.push_back(event->pos());
    if (point.size() > 1)
        line.push_back(QLine(point[point.size() - 2], point.back()));
    update();
}

void Painter::paintGL() {

    QPainter painter(this);
    QPen pen(1);
    pen.setColor(Qt::white);

    painter.setPen(pen);

    if (finished) {
        for(int i = 0; i < polygon.size(); i++) {
            painter.drawLine(polygon[i]);
        }
        return;
    }

    bool finish = false;

    if (point.size() > 2
            && abs(point.back().x() - point.front().x()) <= 5
            && abs(point.back().y() - point.front().y()) <= 5) {
        point.back().setX(point.front().x());
        point.back().setY(point.front().y());
        finish = true;
    }

    for (vector<QPoint>::iterator i = point.begin(); i != point.end(); i++) {
            painter.drawPoint(*i);
    }

    int size = line.size();

    for(int i = 0; i < size; i++) {
        painter.drawLine(line[i]);
    }

    if (point.size() > 0) {
        //TODO: display coordinates of every point?
        if (finish) {
            //TODO start thread?
            fillPolygon();
            this->setEnabled(false);
            finished = true;
            return;
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
    QPen pen(1);
    pen.setColor(Qt::white);

    painter.setPen(pen);

    //TODO define max height
    int height = painter.device()->height();

    vector<tuple<int, double, double>> et[height];

    vector<tuple<int, double, double>> aet;

    while(!line.empty()) {
        QLine l = line.front();
        if (l.y1() != l.y2()) {
            int ymin = (l.y1() < l.y2() ? l.y1() : l.y2());
            int xmin = (l.x1() < l.x2() ? l.x1() : l.x2());
            int ymax = (l.y1() > l.y2() ? l.y1() : l.y2());
            //int xmax = (l.x1() > l.x2() ? l.x1() : l.x2());
            if (ymin >= 0 && xmin >= 0 && ymax < height) {
                double m = (ymin - ymax);
                if (l.y1() == ymin) m /= (l.x1() - l.x2());
                else m /= (l.x2() - l.x1());
                //QTextStream(stdout) << "linha: " << ymin << ": " << ymax << ", " << xmin << ", " << 1/m << endl;
                et[ymin].push_back(make_tuple(ymax, double(xmin), 1/m));
            }
        }
        line.erase(line.begin());
    }

    for (int i = 0; i < height || !aet.empty(); i++) {
        //get all et elements of line and put in aet
        if (i >= height) return;
        while (!et[i].empty()) {
            aet.push_back(et[i].front());
            et[i].erase(et[i].begin());
        }

        //sort by x
        sort(aet.begin(), aet.end(), &sortBySecond);

        //erase all that finish at that line
        for (int j = 0; j < aet.size(); j++) {
            if (get<0>(aet[j]) <= i) {
                aet.erase(aet.begin() + j);
            }
        }

        if (aet.empty()) continue;

        QTextStream(stdout) << "i: " << i << endl;
        //fill pixels
        for (int j = 0; j < aet.size() - 1; j++) {
            //TODO check rules for rounding
            QTextStream(stdout) << "j: " << j << " ";
            int start = get<1>(aet[j]);
            QTextStream(stdout) << "start: " << start << endl;
            if (start < 0) break;
            int end = get<1>(aet[++j]);

            painter.drawLine(start, i, end - 1, i);
            polygon.push_back(QLine(start, i, end - 1, i));
        }

        //update x values
        for (int j = 0; j < aet.size(); j++) {
            get<1>(aet[j]) = (get<1>(aet[j]) + get<2>(aet[j]));
        }

        //TODO sort again?
    }

    /*
    for (int i = 0; i < height; i++) {
        if (!et[i].empty()) {
            sort(et[i].begin(), et[i].end(), &sortBySecond);

        }
    }*/



    /*
    for (int i = 0; i < height; i++) {
        if (!et[i].empty()) {
            QTextStream(stdout) << "Linha " << i << ": ";
            for (int j = 0; j < et[i].size(); j++) {
                QTextStream(stdout) << "(" << get<0>(et[i][j]) << ", " << get<1>(et[i][j]) << ", " << get<2>(et[i][j]) << ") ";
            }
            QTextStream(stdout) << "" << endl;
        }
    }*/


    //this->close();
}


