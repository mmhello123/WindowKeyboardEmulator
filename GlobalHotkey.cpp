#include "GlobalHotkey.h"

GlobalHotkey::GlobalHotkey() : QAbstractNativeEventFilter()
{
    m_startHotKey = 0;
    m_stopHotKey  = 0;
    m_test = 0xD009;
}

//处理从操作系统传递到 Qt 应用程序的原始事件
bool GlobalHotkey::nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result)
{
    //判断是否是Windows通用消息
    if (eventType != "windows_generic_MSG") return false;

    MSG* msg = static_cast<MSG*>(message);

    //判断是否是热键消息
    if (msg->message != WM_HOTKEY) return false;

    //获取虚拟键码
    UINT byteVirtualKey = HIWORD(msg->lParam);
    //获取修饰键码
    UINT fsModifiers = LOWORD(msg->lParam);
    UINT id = byteVirtualKey | fsModifiers;
    qDebug() << "id: " << QString("0x%1").arg(id, 4, 16, QChar('0'));
    if (m_callbacks.contains(id))
    {
        qDebug() << QDateTime::currentDateTime().toString("yy-MM-dd hh:mm:ss.zzz");
        m_callbacks[id]();
        return true;
    }
    return false;
}

/**
*@brief 注册热键函数
*@param1 按键修饰符（ctrl、shift等）
*@param2 按键虚拟键码
*@param3 回调函数
*/
bool GlobalHotkey::registerHotkey(int modifier, int key, const std::function<void()> &callback)
{
    // 将Qt的修饰键转换为 Windows 的修饰键
    UINT winModifier = 0;
    if (modifier & Qt::CTRL) winModifier |= MOD_CONTROL;
    if (modifier & Qt::SHIFT) winModifier |= MOD_SHIFT;
    if (modifier & Qt::ALT)   winModifier |= MOD_ALT;
    if (modifier & Qt::META)  winModifier |= MOD_WIN;

    // 注册热键(1.窗口句柄 2.热键的标识符 3.Windows的修饰符 4.虚拟键码)
    if (::RegisterHotKey(nullptr, m_test++, winModifier, key) == false)
    {
        qDebug() << "注册Windows热键失败！";
        return false;
    }

    //保存回调函数，将Windows的修饰符和虚拟键码组合成一个Hash键
    UINT id = winModifier | key;
    m_callbacks[id] = callback;
    return true;
}

//注销回调函数
void GlobalHotkey::unregisterHotkey()
{
    // 注销热键
    ::UnregisterHotKey(nullptr, reinterpret_cast<UINT>(this));
    m_callbacks.remove(reinterpret_cast<UINT>(this));
}
