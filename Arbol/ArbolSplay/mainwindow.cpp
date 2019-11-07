#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "splay.h"
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
#include <QTextEdit>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Arbol Splay");
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    t.init(scene,ui->graphicsView);
    t.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QString recibir = ui->lineEdit->text();
    int n= recibir.toInt();
    t.Insert(n);
    ui->graphicsView->close();
    t.show();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString recibir2 = ui->lineEdit_2->text();
    int n= recibir2.toInt();
    t.Remove(n);
    ui->graphicsView->close();
    t.show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString recibir3 = ui->lineEdit_3->text();
    int n= recibir3.toInt();
    t.Find(n);
    ui->graphicsView->close();
    t.show();
}
