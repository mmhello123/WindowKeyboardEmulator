#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMessageBox>
#include <QSettings>
#include <QSystemTrayIcon>
#include <QCloseEvent>

#include "KeyPressEater.h"
#include "GlobalHotkey.h"
#include "CloseDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void init();
    void initClassVariables();                                  //初始化成员变量
    void initByConfig();                                        //根据配置文件进行初始化
    void initUi();
    void initConnect();

    void registerStartHotKey(int key);                          //注册启动按键触发快捷键
    void registerStopHotKey(int key);                           //注册停止按键触发快捷键

    void createSystemTray();                                    //创建系统托盘

private slots:
    void setVirtualKeyCode(quint8 keyCode);
    void triggerKeyboardKeys();
    void showHelpDialog();                                      //显示帮助窗口
    void handleExitOptions(bool isExit, bool isShowAagin);      //处理退出选项

    void on_Btn_startExec_clicked();
    void on_Btn_stopExec_clicked();

    void on_Btn_showKeyPressEaterWidget_clicked();

private:
    Ui::MainWindow *ui;

    uint            m_triggerInterval;          //单位为ms
    QTimer          m_triggerTimer;             //触发定时器
    quint8          m_byteVirtualKey;           //字节类型的虚拟键值

    KeyPressEater   m_keyPressEater;            //识别按下键的窗口
    GlobalHotkey    m_lobalHotkey;              //设置热键

    QSettings*      m_settings;                 //用于保存设置

    QSystemTrayIcon m_systemTray;               //系统托盘
    QMenu*          m_menu;                     //系统托盘所需的菜单

    CloseDialog*    m_closeDialog;              //退出程序的对话框
};
#endif // MAINWINDOW_H
