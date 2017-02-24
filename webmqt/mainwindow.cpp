#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFileDialog>
#include<iostream>
#include<string>
#include "command.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <thread>
#include<regex>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }

    QString path = QFileDialog::getOpenFileName(this, tr("Open file"), homedir);
    if(!path.isEmpty() && !path.isNull()){

        std::string filenamestr = path.toStdString();

        const regex file("(.*)(\\..*$)");
        smatch match;
        string ma;

        if(regex_search(filenamestr, match, file)){

            ma = match[1].str();
        }

        ui->filein->setText(path);
        ui->fileoutin->setText(QString::fromStdString(ma)+".webm");
    }

}

void MainWindow::on_gobutton_clicked()
{
    std::string filename = ui->filein->text().toStdString();
    std::string output = ui->fileoutin->text().toStdString();
    bool muted = ui->mutebox->isChecked();
    std::string width = ui->widthin->text().toStdString();
    std::string height = ui->heightin->text().toStdString();
    bool startfromcheck = ui->startfromcheck->isChecked();
    std::string startfrom = ui->startfrom->text().toStdString();
    bool durationcheck = ui->durationcheck->isChecked();
    std::string duration = ui->duration->text().toStdString();

    //ui->gobutton->setEnabled(false);
    //runcommand(filename,output,width,height,muted,startfromcheck,startfrom,durationcheck,duration);
    std::thread t1(runcommand, filename,output,width,height,muted,startfromcheck,startfrom,durationcheck,duration);
    t1.join();

    QMessageBox msgBox;
    msgBox.setText("webm saved in\n"+QString::fromStdString(output));
    msgBox.exec();
}

void MainWindow::on_filein_textChanged(const QString &arg1)
{
    if(ui->filein->text() == "" || ui->fileoutin->text() == ""){
        ui->gobutton->setEnabled(false);
    }else{
        ui->gobutton->setEnabled(true);
    }
}

void MainWindow::on_fileoutin_textChanged(const QString &arg1)
{
    if(ui->filein->text() == "" || ui->fileoutin->text() == ""){
        ui->gobutton->setEnabled(false);
    }else{
        ui->gobutton->setEnabled(true);
    }
}

void MainWindow::on_startfromcheck_stateChanged(int arg1)
{
    if(ui->startfromcheck->isChecked()){
        ui->startfrom->setEnabled(true);
    }
    else{
        ui->startfrom->setEnabled(false);
    }
}


void MainWindow::on_durationcheck_stateChanged(int arg1)
{
    if(ui->durationcheck->isChecked()){
        ui->duration->setEnabled(true);
    }
    else{
        ui->duration->setEnabled(false);
    }
}
