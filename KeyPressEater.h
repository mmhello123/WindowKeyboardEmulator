#ifndef KEYPRESSEATER_H
#define KEYPRESSEATER_H

#include <QDialog>
#include <QKeyEvent>

namespace Ui {
class KeyPressEater;
}

//用于识别按键按下的按键的类
class KeyPressEater : public QDialog
{
    Q_OBJECT

public:
    explicit KeyPressEater(QWidget *parent = nullptr);
    ~KeyPressEater();

protected:
    void keyPressEvent(QKeyEvent *keyEvent) override;

signals:
    void sendVirtualKeyCode(quint8 keycode);            //发送虚拟键码

private slots:
    void on_Btn_confirmKey_clicked();

private:
    void init();
    void initUi();

private:
    Ui::KeyPressEater *ui;

    quint8 m_virtualKeyCode;
};

#endif // KEYPRESSEATER_H
