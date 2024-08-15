#include "KeyPressEater.h"
#include "ui_KeyPressEater.h"

KeyPressEater::KeyPressEater(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyPressEater)
{
    ui->setupUi(this);

    init();
}

KeyPressEater::~KeyPressEater()
{
    delete ui;
}

//重写按键按下事件
void KeyPressEater::keyPressEvent(QKeyEvent *keyEvent)
{
    //设置获取到的虚拟键值
    m_virtualKeyCode = (quint8)keyEvent->key();

    // 获取按下的键并显示在标签上
    QString keyText = QKeySequence(keyEvent->key()).toString();
    QString labelString = QString(" %1 ").arg(keyText);
    ui->label_pressKey->setText(labelString);
    // 设置 QLabel 的尺寸策略为 Preferred
    ui->label_pressKey->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui->label_pressKey->adjustSize();
    // 显示label
    if(!ui->label_pressKey->isVisible()) ui->label_pressKey->show();
}

//初始化
void KeyPressEater::init()
{
    m_virtualKeyCode = 0x00;

    initUi();
}

//初始化Ui
void KeyPressEater::initUi()
{
    this->setWindowTitle("按键捕获窗口");
    ui->label_pressKey->hide();
    this->setModal(true);
}

//确认按键
void KeyPressEater::on_Btn_confirmKey_clicked()
{
    ui->label_pressKey->setText("");
    ui->label_pressKey->hide();
    this->hide();

    //向MainWindow发送虚拟键值
    if(m_virtualKeyCode != 0x00) emit sendVirtualKeyCode(m_virtualKeyCode);
}

