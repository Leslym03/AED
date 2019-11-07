#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "avl.h"
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
    setWindowTitle("Arbol AVL");
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
    t.insert(n);
    ui->graphicsView->close();
    t.show();
}



void MainWindow::on_pushButton_2_clicked()
{
    QString recibir2 = ui->lineEdit_2->text();
    int n= recibir2.toInt();
    t.remove(n);
    ui->graphicsView->close();
    t.show();
}
