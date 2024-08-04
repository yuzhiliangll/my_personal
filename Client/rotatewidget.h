#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QWidget>

namespace Ui {
class RotateWidget;
}

struct RotateWidgetPrivate;

class RotateWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RotateWidget(QWidget *parent = nullptr);
    ~RotateWidget();

    // 设置小部件的图像
    void SetPixMap(const QPixmap &m);

    void Start();// 当音乐播放时开始转
    void Stop(); // 当音乐暂停时停止转动

    // 绘画
    void paintEvent(QPaintEvent * e) override;

private:
    Ui::RotateWidget *ui;
    RotateWidgetPrivate *p;
};

#endif // ROTATEWIDGET_H
