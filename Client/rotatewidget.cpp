#include "rotatewidget.h"
#include "ui_rotatewidget.h"
#include <QPainter>
#include <QTimer>


struct RotateWidgetPrivate
{
    QPixmap picture;
    int r;// 半径
    QPoint center;// 圆心
    int degree;// 旋转角度
    QTimer timer;//

};

RotateWidget::RotateWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RotateWidget), p(new RotateWidgetPrivate)
{
    ui->setupUi(this);

    // p->timer.start(100);
    connect(&p->timer, &QTimer::timeout, [this]()
    {
        p->degree = (p->degree + 2) % 360;// 每次转两度
        update();// 每次更新
    });


}

RotateWidget::~RotateWidget()
{
    delete ui;
    delete p;
}

// 设置小部件的图像，并初始化用于旋转的相关参数
void RotateWidget::SetPixMap(const QPixmap &m)
{
    p->picture = m;
    p->r = std::min(this->width(), this->height()) / 2;// 半径为 最小的边的一半
    p->center = QPoint(this->width() / 2, this->height() / 2);// 圆心
    p->degree = 0;// 一开始不转
}

void RotateWidget::Start()
{
    p->timer.start(150);
}

void RotateWidget::Stop()
{
    p->timer.stop();
}



// 绘画
void RotateWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);// 抗锯齿

    // 裁剪
    QPainterPath path;// 首先要明确裁剪路径
    path.addEllipse(p->center, p->r, p->r);// 裁剪成正圆

    // 旋转
    QTransform t;
    t.translate(p->center.x(), p->center.y()); // 旋转点
    t.rotate(p->degree);// 旋转角度

    painter.setClipPath(path);// 设置裁剪路径
    painter.setTransform(t);// 设置旋转属性
    painter.drawPixmap(-this->width() / 2, -this->height() / 2, this->width(), this->height(), p->picture);//

}
