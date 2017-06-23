#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include <QDebug>

#define BASE_ARQUIVO "@relation Simpsons \
    @attribute personagem{bart, homer} \
    @attribute cF6BC0 numeric \
    @attribute cFF560 numeric \
    @attribute cA328A numeric \
    @attribute c32C90 numeric \
    @attribute cAAA numeric \
    @attribute cFFFFFF numeric \
    @attribute cD3AC6A numeric \
    @attribute c4173B2 numeric \
    @attribute cC80C8 numeric \
    @attribute cFF00 numeric \
    @attribute c34D0FF numeric \
    @attribute c79848D numeric \
    @attribute cC7650 numeric \
    @attribute cD9B64 numeric \
    @data"


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

void MainWindow::on_pushButton_clicked(){
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    qDebug() << dir;
    //TODO - percorrer e pegar todas as imagens do diretorio

}

void MainWindow::on_pushButton_2_clicked(){
//    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "/home", tr("Image Files (*.png *.jpg *.bmp)"));

    extract( "/Users/bruno/Downloads/Simpsons/Test/bart116.bmp");
}

void MainWindow::extract(QString arg){
    QImage img( arg );
    qDebug() << arg;

    if ( false == img.isNull() ){
        for ( int row = 1; row < img.height() + 1; ++row )
            for ( int col = 1; col < img.width() + 1; ++col ){
                QColor clrCurrent( img.pixel( row, col ) );

                QString color = QString::number(clrCurrent.red()) + ", "
                          + QString::number(clrCurrent.green()) + ", "
                          + QString::number(clrCurrent.blue());

                if (mapColors.contains( color )){
                    mapColors[color] = mapColors.value( color ) + 1;
                }else {
                    mapColors.insert(color, 1);
                }
            }
    }
    qDebug() << "Cores";

    for(QString key : mapColors.keys()){
        qDebug() << mapColors.value( key) << "" << key;
    }
}
