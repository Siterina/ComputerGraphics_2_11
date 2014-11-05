#include "frame.h"
#include "ui_frame.h"
#include "nvector.h"
#include "nmatrix.h"

#define pi 3.1415

Frame::Frame(QWidget *parent) :
    QWidget(parent),
    h_figure(4), r_figure(2),
    alpha(45), beta(0),
    lastX(0), lastY(0),
    visible(false),
    Scale(1), toMove(0),
    ui(new Ui::Frame)
{
    ui->setupUi(this);
}

Frame::~Frame()
{
    delete ui;
}

NVector figurePoint(double phi, double r_figure, double h_figure) {
    NVector result = NVector();
    result.x = r_figure * cos(phi);
    result.y = r_figure * sin(phi);
    result.z = h_figure;
    result.t = 0;
    return result;
}

NVector VectorComposition(const NVector a, const NVector b) {
    NVector result = NVector();
    result.x = a.y * b.z - a.z * b.y;
    result.y = a.z * b.x - a.x * b.z;
    result.z = a.x * b.y - a.y * b.x;
    return result;
}

double ScalarComposition(const NVector a, const NVector b) {
    double result;
    result = a.x * b.x + a.y * b.y + a.z * b.z;
    return result;
}


void Frame::paintEvent(QPaintEvent*)
{

    double max = std::max(1.5 * h_figure * Scale.z, std::max(1.5 * r_figure * Scale.y, 1.5 * r_figure * Scale.x));
    double Ky = height()/(2 * max);
    double Kx = (width())/(2 * max);
    double K = std::min(Kx, Ky);

    QPainter painter(this);

    pen.setColor(Qt::black);
    pen.setWidth(3);
    pen.setStyle(Qt::SolidLine);
    painter.setPen(pen);

    QVector <NVector> points;

    double w  = width() / 2.0;
    double h = height() / 2.0 + 30;

    NMatrix XZMatrix = NMatrix();
    NMatrix YZMatrix = NMatrix();
    NMatrix SMatrix  = NMatrix();
    NMatrix ResMatrix = NMatrix();
    NVector ToCenter = NVector();
    ToCenter.x = w;
    ToCenter.y = h;

    XZMatrix.RotateXZ(beta);
    YZMatrix.RotateYZ(alpha);
    SMatrix.SetScale(K, Scale);

    ResMatrix = XZMatrix * YZMatrix * SMatrix;

    double step = pi / 5;
    for(double phi = 0; phi < 2 * pi; phi += step) {
         points.push_back(ResMatrix * figurePoint(phi, r_figure, -h_figure / 2) + ToCenter + toMove);
         points.push_back(ResMatrix * figurePoint(phi + step, r_figure, -h_figure / 2) + ToCenter + toMove);
         points.push_back(ResMatrix * figurePoint(phi + step, r_figure, h_figure / 2) + ToCenter + toMove);
         points.push_back(ResMatrix * figurePoint(phi, r_figure, h_figure / 2) + ToCenter + toMove);
    }

    int size = points.size();
    NVector a = NVector();
    NVector b = NVector();
    NVector n = NVector();
    NVector k = NVector();
    k.z = -1;
    bool bottom = false;
    bool top = false;
    n = VectorComposition(points[5] - points[4], points[1] - points[0]);
    if(ScalarComposition(n, k) >= 0)
            bottom = true;
    n = VectorComposition(points[3] - points[2], points[7] - points[6]);
    if(ScalarComposition(n, k) >= 0)
            top = true;

    for (int i = 0; i < size; i += 4) {
        a = points[i + 1] - points[i];
        b = points[i + 3] - points[i];
        n = VectorComposition(a, b);

        if(ScalarComposition(n, k) >= 0) {
            painter.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            painter.drawLine(points[i + 1].x, points[i + 1].y, points[i + 2].x, points[i + 2].y);
            painter.drawLine(points[i + 2].x, points[i + 2].y, points[i + 3].x, points[i + 3].y);
            painter.drawLine(points[i + 3].x, points[i + 3].y, points[i].x, points[i].y);
        }
        else if(visible) {
            pen.setColor(Qt::darkGray);
            pen.setWidth(1);
            pen.setStyle(Qt::DashLine);
            painter.setPen(pen);
            painter.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
            painter.drawLine(points[i + 1].x, points[i + 1].y, points[i + 2].x, points[i + 2].y);
            painter.drawLine(points[i + 2].x, points[i + 2].y, points[i + 3].x, points[i + 3].y);
            painter.drawLine(points[i + 3].x, points[i + 3].y, points[i].x, points[i].y);
        }
        pen.setColor(Qt::black);
        pen.setWidth(3);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        if(bottom)
            painter.drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        if(top)
            painter.drawLine(points[i + 2].x, points[i + 2].y, points[i + 3].x, points[i + 3].y);
    }
}


void Frame::mousePressEvent(QMouseEvent *mEvent) {
    lastX = mEvent->x();
    lastY = mEvent->y();
}

void Frame::mouseMoveEvent(QMouseEvent *mEvent) {
    beta  -= (mEvent->x() - lastX) * pi / 360;
    alpha += (mEvent->y() - lastY) * pi / 360;
    lastX = mEvent->x();
    lastY = mEvent->y();
    repaint();
}


void Frame::on_exitButton_clicked() {
    close();
}


void Frame::on_checkBox_toggled(bool checked) {
    if(checked)
        visible = true;
    else visible = false;
    repaint();
}

void Frame::on_ScaleX_valueChanged(int arg1)
{
    Scale.x = (double)arg1;
    repaint();
}

void Frame::on_ScaleY_valueChanged(int arg1)
{
    Scale.y = (double)arg1;
    repaint();
}

void Frame::on_ScaleZ_valueChanged(int arg1)
{
    Scale.z = (double)arg1;
    repaint();
}

void Frame::on_LeftRight_sliderMoved(int position)
{
    toMove.x = (double)position;
    repaint();
}


void Frame::on_UpDown_sliderMoved(int position)
{
    toMove.y = (double)position;
    repaint();
}
