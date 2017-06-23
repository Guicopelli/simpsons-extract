#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QFileDialog"
#include <QDebug>
#include "colorprocess.h"
#include <QtMath>

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

    extract( "/home/bruno/Documentos/simpsons-extract/resource/Test/bart116.bmp");
}

void MainWindow::extract(QString arg){
    QImage img( arg );
    qDebug() << arg;

    if ( false == img.isNull() ){
        height = img.height();
        width = img.width();

        //pega todas as cores adiciona em um map e conta a quantidade de cada uma
        for ( int row = 1; row < img.height() + 1; ++row ){
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
    }

    //Processa as cores obtidas em um objeto
    for(QString key : mapColors.keys()){
        QStringList list;
        list = key.split(",", QString::SkipEmptyParts);

        ColorProcess* color = new ColorProcess;
        color->setR( list[0].toInt());
        color->setG( list[1].toInt());
        color->setB( list[2].toInt());

        color->setCount( mapColors.value( key));
        color->setKey( key);

        if (mapColorsProcess.contains( color->getKey() )){
            mapColorsProcess[color->getKey()] = mapColorsProcess.value( color->getKey() );
        }else {
            mapColorsProcess.insert(color->getKey(), color);
        }
    }

    //calcular distancia euclidiana entre a paleta de cores e as cores coletadas
    //faz a troco pela cor na paeta de cores
    //D = raiz( (R1-R2)^2 + (G1-G2)^2 + (B1-B2)^2 )
    for(ColorProcess* colorToProcess : mapColorsProcess.values()){
        double result;
        double mimResult = 999999999;

        ColorProcess* colorSub = new ColorProcess; //cor para substituir

        for(ColorProcess* colorPaleta : getPaleta()){
            result = qPow((colorToProcess->getR() - colorPaleta->getR()), 2) +
                    qPow((colorToProcess->getG() - colorPaleta->getG()), 2) +
                    qPow((colorToProcess->getB() - colorPaleta->getB()), 2);

            result = qSqrt(result);

            if(result < mimResult){
                *colorSub = *colorPaleta;
                mimResult = result;
            }
        }

        colorSub->setCount( colorToProcess->getCount());

        colorSub->setKey( QString::number(colorSub->getR()) + " ," +
                          QString::number(colorSub->getG()) + " ," +
                          QString::number(colorSub->getB()));


        if (mapColorsProcessed.contains( colorSub->getKey() )){
            ColorProcess* colorUpdate = new ColorProcess;
            colorUpdate = mapColorsProcessed[ colorSub->getKey() ];
            colorUpdate->setCount( mapColorsProcessed[colorSub->getKey()]->getCount() + colorSub->getCount());

            mapColorsProcessed.remove( colorSub->getKey());

            mapColorsProcessed.insert(colorSub->getKey(), colorUpdate);
        }else {
            mapColorsProcessed.insert(colorSub->getKey(), colorSub);
        }
    }

    for(ColorProcess* colorToProcess : mapColorsProcessed.values()){
        //(ocorrencias / (largura*altura))*100
        double ocur = colorToProcess->getCount();
        double peImg = ( ( ocur / (width*height) ) * 100 );
        colorToProcess->setPeImg( peImg );

        qDebug() << colorToProcess->getKey() << " ocorrencias: " << colorToProcess->getCount() << " percento: " << peImg;
    }


}

QList<ColorProcess*> MainWindow::getPaleta(){
    QList<ColorProcess*> colors;

    colors.append(new ColorProcess( 246,188,0 ));// amarelo
    colors.append(new ColorProcess( 255,86,0 ));// laranja camiseta bart
    colors.append(new ColorProcess( 10,50,138 ));// azulcalca bart
    colors.append(new ColorProcess( 50,201,0 ));// verde
    colors.append(new ColorProcess( 10,10,10 ));// preto
    colors.append(new ColorProcess( 255,255,255 ));// branco
    colors.append(new ColorProcess( 211,172,106 ));// barba Homer
    colors.append(new ColorProcess( 65,115,178 ));// calca Homer
    colors.append(new ColorProcess( 200,0,200 ));// chiclete 1, 22
    colors.append(new ColorProcess( 255,0,0 ));// vermelho
    colors.append(new ColorProcess( 52,208,255 ));// azul marinho
    colors.append(new ColorProcess( 121,132,141 ));// cinza
    colors.append(new ColorProcess( 199,101,0 ));// marrom quadro bart
    colors.append(new ColorProcess( 13,155,100 ));// verde chapeu bart

    return colors;
}
