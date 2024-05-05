#include "widget.h"
#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>
#include <QFileDialog>

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , roleLabel(new QLabel(this))
    , curFrame(0)
{
    setWindowFlags(Qt::WindowType::FramelessWindowHint); // 去掉窗口的边框
    setAttribute(Qt::WA_TranslucentBackground); // 背景透明

    // 动画更新定时器
    QTimer* updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Widget::updateRoleAnimation);
    updateTimer->start(500);

    // 设置窗口阴影效果
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(QColor(230, 231, 232, 220));
    effect->setBlurRadius(5);
    this->setGraphicsEffect(effect);

    roleLabel->resize(500, 500);

    initBtn();
    this->installEventFilter(this);
}

Widget::~Widget()
{
}

void Widget::updateRoleAnimation()
{
    QString qss("background-repeat:no-repeat;");
    roleLabel->setStyleSheet(qss + QString("background-image:url(:/resource/resource/desktopRole/summerGril/%1.png);").arg(curFrame + 1));
    curFrame = (curFrame + 1) % 6;
}

bool Widget::eventFilter(QObject* watched, QEvent* event)
{
    QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);

    static QPoint startPos;
    if (event->type() == QEvent::MouseButtonPress && mouseEvent->button() == Qt::LeftButton)
    {
        startPos = mouseEvent->globalPosition().toPoint() - this->pos();
    }
    else if (event->type() == QEvent::MouseMove && mouseEvent->buttons() == Qt::LeftButton)
    {
        this->move(mouseEvent->globalPosition().toPoint() - startPos);
    }

    return QWidget::eventFilter(watched, event);
}

void Widget::initBtn()
{
    closeBtn = new QPushButton(this);
    cutBtn = new QPushButton(this);
    openBtn = new QPushButton(this);

    closeBtn->setGeometry(300, 200, 32, 32);
    cutBtn->setGeometry(300, 240, 32, 32);
    openBtn->setGeometry(300, 280, 32, 32);
    closeBtn->setObjectName("closeBtn");

    closeBtn->setStyleSheet("background-image:url(:/resource/assets/images/png/button1.jpg);");
    cutBtn->setStyleSheet("background-image:url(:/resource/button/cut.png);");
    openBtn->setStyleSheet("background-image:url(:/resource/button/open.png);");

    connect(closeBtn, &QPushButton::clicked, this, &QWidget::close);
}
	