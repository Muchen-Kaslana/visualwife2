#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    QLabel* roleLabel;
    int curFrame;
    QPushButton* closeBtn;
    QPushButton* cutBtn;
    QPushButton* openBtn;

    void initBtn();
    void updateRoleAnimation();
};

#endif // WIDGET_H