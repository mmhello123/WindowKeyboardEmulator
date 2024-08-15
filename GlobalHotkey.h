#ifndef GLOBALHOTKEY_H
#define GLOBALHOTKEY_H

#include <QObject>
#include <QMessageBox>
#include <QAbstractNativeEventFilter>
#include <QDateTime>

#include <windows.h>

//用于注册和注销全局热键
class GlobalHotkey : public QAbstractNativeEventFilter
{
public:
    explicit GlobalHotkey();

protected:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result) override;

public:
    bool registerHotkey(int modifier, int key, const std::function<void()>& callback);
    void unregisterHotkey();

private:
    QHash<UINT, std::function<void()>> m_callbacks;             //用于保存回调函数
    UINT                               m_startHotKey;           //启动按键触发的热键
    UINT                               m_stopHotKey;            //启动按键触发的热键
    UINT                               m_test;
};

#endif // GLOBALHOTKEY_H
