#include "CloseDialog.h"
#include "ui_CloseDialog.h"

CloseDialog::CloseDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CloseDialog)
{
    ui->setupUi(this);

    this->setWindowTitle("关闭程序");
    this->setModal(true);   //设置模态
    this->setFixedSize(300, 100);
    this->hide();
}

CloseDialog::~CloseDialog()
{
    delete ui;
}

void CloseDialog::on_Btn_cancel_clicked()
{
    this->hide();
}


void CloseDialog::on_Btn_confirm_clicked()
{
    //退出还是最小化
    bool isExit = false;
    if(ui->radioButton_quit->isChecked()) isExit = true;

    //是否再次显示
    bool isShowAagin = true;
    if(ui->checkBox_doNotShowAgain->isChecked()) isShowAagin = false;
    emit exitOptions(isExit, isShowAagin);
}

