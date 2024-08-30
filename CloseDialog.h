#ifndef CLOSEDIALOG_H
#define CLOSEDIALOG_H

#include <QDialog>

namespace Ui {
class CloseDialog;
}

class CloseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CloseDialog(QWidget *parent = nullptr);
    ~CloseDialog();

signals:
    void exitOptions(bool isExit, bool isShowAagin);

private slots:
    void on_Btn_cancel_clicked();

    void on_Btn_confirm_clicked();

private:
    Ui::CloseDialog *ui;
};

#endif // CLOSEDIALOG_H
