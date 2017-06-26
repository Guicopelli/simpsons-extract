#ifndef COLORPROCESS_H
#define COLORPROCESS_H

#include <QString>

class ColorProcess {

public:
    ColorProcess( ){ }
    ColorProcess(int colorR, int colorG, int colorB){ R = colorR; G = colorG; B = colorB; }
    ColorProcess(int colorR, int colorG, int colorB, QString ref){ R = colorR; G = colorG; B = colorB; atributo = ref; }

    int getR() const{ return R; }
    void setR(int value){ R = value; }

    int getG() const{ return G; }
    void setG(int value){ G = value; }

    int getB() const{ return B; }
    void setB(int value){ B = value; }

    int getCount() const{ return Count; }
    void setCount(int value){ Count = value; }

    QString getKey() const{ return key; }
    void setKey(const QString& value){ key = value; }

    double getPeImg() const{ return peImg; }
    void setPeImg(double value){ peImg = value; }

    QString getAtributo() const { return atributo; }
    void setAtributo(const QString& value){ atributo = value; }

    QString getPeImgStr() const{ return peImgStr; }
    void setPeImgStr(const QString &value){ peImgStr = value; }


private:
    int R;
    int G;
    int B;
    int Count;
    QString key;
    double peImg = 0;
    QString atributo;
    QString peImgStr;

};

#endif // COLORPROCESS_H
