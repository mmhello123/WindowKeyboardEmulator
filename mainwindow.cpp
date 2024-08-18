#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();
}

MainWindow::~MainWindow()
{
    delete m_settings;
    m_settings = nullptr;
    delete ui;
}

/*----------------------------------------------------------------------------*/

// 初始化
void MainWindow::init()
{
    initUi();
    initClassVariables();
    initByConfig();
    initConnect();

    // 安装本机事件监听
    qApp->installNativeEventFilter(&m_lobalHotkey);

    // 注册启动按键触发快捷键（F6）
    registerStartHotKey(0x75);
    // 注册停止按键触发快捷键（F7）
    registerStopHotKey(0x76);
}

// 初始化成员变量
void MainWindow::initClassVariables()
{
    m_triggerInterval = 1000;
    m_byteVirtualKey = 0x00;

    QString settingSavePath = QCoreApplication::applicationDirPath() + "/config.ini";
    m_settings = new QSettings(settingSavePath, QSettings::IniFormat);
}

// 根据配置文件进行初始化
void MainWindow::initByConfig()
{
    //初始化虚拟键值
    QVariant byteVirtualKey = m_settings->value("triggeredKey", 0x00);
    m_byteVirtualKey = static_cast<quint8>(byteVirtualKey.toUInt());

    //初始化按键触发间隔
    int triggerInterval = m_settings->value("triggerInterval", 1000).toInt();
    ui->spinBox_triggerInterval->setValue(triggerInterval);
}

// 初始化Ui
void MainWindow::initUi()
{
    this->setWindowTitle("键盘触发器");

    // 停止按钮禁用
    ui->Btn_stopExec->setDisabled(true);
}

// 初始化信号与槽
void MainWindow::initConnect()
{
    connect(&m_triggerTimer, &QTimer::timeout, this, &MainWindow::triggerKeyboardKeys);
    connect(&m_keyPressEater, &KeyPressEater::sendVirtualKeyCode, this, &MainWindow::setVirtualKeyCode);
    connect(ui->action_help, &QAction::triggered, this, &MainWindow::showHelpDialog);
}

/*----------------------------------------------------------------------------*/

// 注册启动按键触发快捷键
void MainWindow::registerStartHotKey(int key)
{
    int ret = m_lobalHotkey.registerHotkey(0, key, [=]()
    {
        on_Btn_startExec_clicked();
    });

    if(ret == false) QMessageBox::critical(this, "错误", "注册全局启动热键失败!");
}

// 注册停止按键触发快捷键
void MainWindow::registerStopHotKey(int key)
{
    int ret = m_lobalHotkey.registerHotkey(0, key, [=]()
    {
        on_Btn_stopExec_clicked();
    });

    if(ret == false) QMessageBox::critical(this, "错误", "注册全局停止热键失败!");
}

/*----------------------------------------------------------------------------*/

// 设置要触发的虚拟键码
void MainWindow::setVirtualKeyCode(quint8 keyCode)
{
    m_byteVirtualKey = keyCode;

    //将触发的按键写入配置文件
    m_settings->setValue("triggeredKey", keyCode);
}

// 按键触发
void MainWindow::triggerKeyboardKeys()
{
    //参数1：虚拟键值代码 参数2：键盘系统硬件产生的扫描码 参数3：未指定是按下的作用 参数4：与键盘动作关联的附加信息
    keybd_event(m_byteVirtualKey, 0, 0, 0);
    //KEYEVENTF_KEYUP 模拟用户松开某个键
    keybd_event(m_byteVirtualKey, 0, KEYEVENTF_KEYUP, 0);
}

// 显示帮助窗口
void MainWindow::showHelpDialog()
{
    // 创建一个 QMessageBox 显示帮助信息
    QMessageBox helpBox(this);
    helpBox.setWindowTitle("帮助");
    helpBox.setText("1.先点击“捕获按键”来设置要触发的按键\n2.点击“开始执行”或按快捷键F6来自动触发按键\n3.点击“停止执行”或按快捷键F7来停止触发按键");
    helpBox.setStandardButtons(QMessageBox::Ok);
    helpBox.exec();
}

/*----------------------------------------------------------------------------*/

// 开始执行按键触发
void MainWindow::on_Btn_startExec_clicked()
{
    if(m_byteVirtualKey == 0x00)
    {
        QMessageBox::warning(this, "警告", "请先选择触发的按键!");
        return;
    }

    //将触发的时间间隔写入配置文件
    m_settings->setValue("triggerInterval", ui->spinBox_triggerInterval->value());

    ui->Btn_startExec->setDisabled(true);
    ui->Btn_stopExec->setEnabled(true);

    m_triggerInterval = ui->spinBox_triggerInterval->value();
    m_triggerTimer.start(m_triggerInterval);
}

// 停止执行按键触发
void MainWindow::on_Btn_stopExec_clicked()
{
    ui->Btn_startExec->setEnabled(true);
    ui->Btn_stopExec->setDisabled(true);
    m_triggerTimer.stop();
}

// 显示按键捕获窗口
void MainWindow::on_Btn_showKeyPressEaterWidget_clicked()
{
    m_keyPressEater.show();
}

