#include "widget.h"
#include "ui_widget.h"
#include "dmtx.h"
#include <QMessageBox>
#include <iostream>
#include <QDebug>
#include <QFile>
#include <QImage>
#include <QTime>
#include <QFileDialog>
#include <QColor>
#include <QPainter>

#pragma execution_character_set("utf-8")
using namespace std;

void dataMatrixDecode();//

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);

    ui->comboBox->addItem("DmtxSymbolRectAuto",DmtxSymbolRectAuto);
    ui->comboBox->addItem("DmtxSymbolSquareAuto",DmtxSymbolSquareAuto);
    //  ui->comboBox->addItem("DmtxSymbolShapeAuto",DmtxSymbolShapeAuto);//出错
    ui->comboBox->addItem("DmtxSymbol10x10",DmtxSymbol10x10);
    ui->comboBox->addItem("DmtxSymbol12x12",DmtxSymbol12x12);
    ui->comboBox->addItem("DmtxSymbol14x14",DmtxSymbol14x14);
    ui->comboBox->addItem("DmtxSymbol16x16",DmtxSymbol16x16);
    ui->comboBox->addItem("DmtxSymbol18x18",DmtxSymbol18x18);
    ui->comboBox->addItem("DmtxSymbol20x20",DmtxSymbol20x20);
    ui->comboBox->addItem("DmtxSymbol22x22",DmtxSymbol22x22);
    ui->comboBox->addItem("DmtxSymbol24x24",DmtxSymbol24x24);
    ui->comboBox->addItem("DmtxSymbol26x26",DmtxSymbol26x26);
    ui->comboBox->addItem("DmtxSymbol32x32",DmtxSymbol32x32);
    ui->comboBox->addItem("DmtxSymbol36x36",DmtxSymbol36x36);
    ui->comboBox->addItem("DmtxSymbol40x40",DmtxSymbol40x40);
    ui->comboBox->addItem("DmtxSymbol44x44",DmtxSymbol44x44);
    ui->comboBox->addItem("DmtxSymbol48x48",DmtxSymbol48x48);
    ui->comboBox->addItem("DmtxSymbol52x52",DmtxSymbol52x52);
    ui->comboBox->addItem("DmtxSymbol64x64",DmtxSymbol64x64);
    ui->comboBox->addItem("DmtxSymbol72x72",DmtxSymbol72x72);
    ui->comboBox->addItem("DmtxSymbol80x80",DmtxSymbol80x80);
    ui->comboBox->addItem("DmtxSymbol88x88",DmtxSymbol88x88);
    ui->comboBox->addItem("DmtxSymbol96x96",DmtxSymbol96x96);
    ui->comboBox->addItem("DmtxSymbol104x104",DmtxSymbol104x104);
    ui->comboBox->addItem("DmtxSymbol120x120",DmtxSymbol120x120);
    ui->comboBox->addItem("DmtxSymbol132x132",DmtxSymbol132x132);
    ui->comboBox->addItem("DmtxSymbol144x144",DmtxSymbol144x144);

    ui->comboBox->addItem("DmtxSymbol8x18",DmtxSymbol8x18);//10
    ui->comboBox->addItem("DmtxSymbol8x32",DmtxSymbol8x32);//20
    ui->comboBox->addItem("DmtxSymbol12x26",DmtxSymbol12x26);//32
    ui->comboBox->addItem("DmtxSymbol16x36",DmtxSymbol16x36);//64
    ui->comboBox->addItem("DmtxSymbol16x48",DmtxSymbol16x48);//98
    ui->comboBox->setCurrentIndex(1);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

    QString str =ui->textEdit->toPlainText();
    if(str.isEmpty())
    {
        QMessageBox::information(this,"信息","没有输入文本");
    }
    else
    {
        QString str2=str;
        qDebug()<<"字节长度："<<str2.size();
        // QRegExp rx("^[0-9]*$");//匹配数字
        QRegExp rx("^\\D*$");//匹配非数字
        QRegExp rx2("^[u4e00-u9fa5]*$");//匹配汉字[u4e00-u9fa5]
        int strL=str2.size();
        for(int i=0; i<str2.size(); i++)
        {
            if(rx.exactMatch(str2.at(i)))
            {
                qDebug()<<"匹配非数字："<<str2.at(i);
                strL++;
            }

            if(rx2.indexIn(str2.at(i)))
            {
                qDebug()<<"匹配汉字："<<str2.at(i);
                strL=strL+4;
            }
        }
        qDebug()<<"字节复核长度："<<strL;

        int flagPass=1;
        if(ui->comboBox->currentData().toInt()>=0)
        {
            int errSize=ui->comboBox->currentData().toInt()+1;
            qDebug()<<"errSize："<<errSize;
            if(errSize==1&&strL>6){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==2&&strL>10){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==3&&strL>16){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==4&&strL>24){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==5&&strL>36){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==6&&strL>44){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==7&&strL>60){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==8&&strL>60){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==9&&strL>88){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==10&&strL>124){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==11&&strL>172){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==12&&strL>228){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==13&&strL>288){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==14&&strL>348){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==15&&strL>408){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==16&&strL>560){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==17&&strL>736){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==18&&strL>912){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==19&&strL>1152){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==20&&strL>1392){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==21&&strL>1632){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==22&&strL>2100){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==23&&strL>2608){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==24&&strL>3116){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}

            if(errSize==25&&strL>10){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==26&&strL>20){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==27&&strL>32){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==28&&strL>44){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==29&&strL>64){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}
            if(errSize==30&&strL>98){QMessageBox::information(this,"信息","超字节无法创建");flagPass=0;}

            qDebug()<<"flagPass："<<flagPass;
        }

        if(flagPass>0)
        {
            DmtxEncode* encode = dmtxEncodeCreate();
            assert(encode != NULL);

            encode->moduleSize =ui->spinBox_moduleSize->value();
            encode->marginSize =ui->spinBox_marginSize->value();

            //        QString comstr=ui->comboBox->currentText();
            qDebug()<<"comboBox："<<ui->comboBox->currentData().toInt();

            encode->sizeIdxRequest=ui->comboBox->currentData().toInt();//DmtxSymbolSquareAuto;//设置类型默认

            //    dmtxEncodeSetProp( encode, DmtxPropModuleSize, 5); // encode->moduleSize = 5;
            //    dmtxEncodeSetProp( encode, DmtxPropMarginSize,20); //  encode->marginSize = 10;
            //    //下面是代码中默认函数设置 dmtxencode.c->dmtxEncodeCreate(void);
            //    encode->scheme = DmtxSchemeAscii;
            //    encode->sizeIdxRequest = DmtxSymbolSquareAuto;
            //    encode->marginSize = 10;
            //    encode->moduleSize = 5;
            //    encode->pixelPacking = DmtxPack24bppRGB;
            //    encode->imageFlip = DmtxFlipNone;
            //    encode->rowPadBytes = 0;
            //    encode->fnc1 = DmtxUndefined;

            //    int ret = dmtxEncodeDataMatrix(encode, strlen(str.toStdString().c_str()), (unsigned char*)str.toStdString().c_str());//案例函数c语言
            int ret = dmtxEncodeDataMatrix(encode, str.size(), (uchar*)str.toStdString().data());
            assert(ret == 1);

            //    QMessageBox::information(this,"信息","打开文件失败");
            //str.toStdString().c_str()//兼容c语言

            int width = dmtxImageGetProp(encode->image, DmtxPropWidth);
            int height = dmtxImageGetProp(encode->image, DmtxPropHeight);
            int bytesPerPixel = dmtxImageGetProp(encode->image, DmtxPropBytesPerPixel);
            int bytesPerLine = dmtxImageGetProp(encode->image, DmtxPropRowSizeBytes);

            uchar *pxlData = (uchar *)malloc(width*height*bytesPerPixel);
            memcpy(pxlData,encode->image->pxl,width*height*bytesPerPixel);
            dmtxEncodeDestroy(&encode);

            qDebug()<<"宽度："<<width;
            qDebug()<<"高度："<<height;
            qDebug()<<"比特："<<bytesPerPixel;
            qDebug()<<"行数："<<bytesPerLine;

            QImage img = QImage(pxlData,width,height,bytesPerLine,QImage::Format_RGB888);

            qDebug()<<"QImage 宽度："<<img.width();
            qDebug()<<"QImage 高度："<<img.height();
            qDebug()<<"QImage 行数："<<img.bytesPerLine();


            QImage imgshow=img.scaled( this->ui->label->width(), this->ui->label->height(),Qt:: KeepAspectRatio);
            ui->label->setPixmap(QPixmap::fromImage(imgshow));

            QString base_str=str.left(8);
            QString label_base_text=QString("基本信息：宽度 %1 高度 %2 字节 %3 内容 %4..").
                    arg(width).arg(height).arg(strL).arg(base_str);
            ui->label_base->setText(label_base_text);
            globalImg=img.copy();//保存用
            globastr=QString("D%1-W%2-L%3").
                    arg(base_str).arg(width).arg(height);
        }
    }

}



/*
//测试代码
//    QString str = "DataMatrix";
QString str = "123456789";
DmtxEncode* encode = dmtxEncodeCreate();
assert(encode != NULL);

encode->moduleSize = 5;
encode->marginSize = 5;
encode->sizeIdxRequest=DmtxSymbolSquareAuto;//设置类型默认

//    dmtxEncodeSetProp( encode, DmtxPropModuleSize, 5); // encode->moduleSize = 5;
//    dmtxEncodeSetProp( encode, DmtxPropMarginSize,20); //  encode->marginSize = 10;

//    下面是代码中默认函数设置 dmtxencode.c->dmtxEncodeCreate(void);
//    encode->scheme = DmtxSchemeAscii;
//    encode->sizeIdxRequest = DmtxSymbolSquareAuto;
//    encode->marginSize = 10;
//    encode->moduleSize = 5;
//    encode->pixelPacking = DmtxPack24bppRGB;
//    encode->imageFlip = DmtxFlipNone;
//    encode->rowPadBytes = 0;
//    encode->fnc1 = DmtxUndefined;


//    int ret = dmtxEncodeDataMatrix(encode, strlen(str.toStdString().c_str()), (unsigned char*)str.toStdString().c_str());//案例函数c语言
int ret = dmtxEncodeDataMatrix(encode, str.size(), (uchar*)str.toStdString().data());
assert(ret == 1);

qDebug()<<"字节长度："<<str.size();
//    QMessageBox::information(this,"信息","打开文件失败");
//str.toStdString().c_str()//兼容c语言

int width = dmtxImageGetProp(encode->image, DmtxPropWidth);
int height = dmtxImageGetProp(encode->image, DmtxPropHeight);
int bytesPerPixel = dmtxImageGetProp(encode->image, DmtxPropBytesPerPixel);
int bytesPerLine = dmtxImageGetProp(encode->image, DmtxPropRowSizeBytes);

uchar *pxlData = (uchar *)malloc(width*height*bytesPerPixel);
memcpy(pxlData,encode->image->pxl,width*height*bytesPerPixel);
dmtxEncodeDestroy(&encode);

qDebug()<<"宽度："<<width;
qDebug()<<"高度："<<height;
qDebug()<<"比特："<<bytesPerPixel;
qDebug()<<"行数："<<bytesPerLine;

QImage img = QImage(pxlData,width,height,bytesPerLine,QImage::Format_RGB888);
QImage imgshow=img.scaled( this->ui->label->width(), this->ui->label->height(),Qt:: KeepAspectRatio);
ui->label->setPixmap(QPixmap::fromImage(imgshow));

*/

/*
//自带 example
    size_t          width, height, bytesPerPixel;
    unsigned char   str[] = "30Q324343430794<OQQ";
    unsigned char  *pxl;
    DmtxEncode     *enc;
    DmtxImage      *img;
    DmtxDecode     *dec;
    DmtxRegion     *reg;
    DmtxMessage    *msg;

    //1) ENCODE a new Data Matrix barcode image (in memory only)
    enc = dmtxEncodeCreate();
    //dmtxEncodeSetProp( enc, DmtxPropPixelPacking, DmtxPack16bppRGB );
    //dmtxEncodeSetProp( enc, DmtxPropPixelPacking, DmtxPack32bppRGB );
    //dmtxEncodeSetProp( enc, DmtxPropWidth, 160 );
    //dmtxEncodeSetProp( enc, DmtxPropHeight, 160 );

    assert(enc != NULL);
    dmtxEncodeDataMatrix(enc, strlen((const char *)str), str);
    //2) COPY the new image data before releasing encoding memory
    width = dmtxImageGetProp(enc->image, DmtxPropWidth);
    height = dmtxImageGetProp(enc->image, DmtxPropHeight);
    bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
    pxl = (unsigned char *)malloc(width * height * bytesPerPixel);//malloc c语言的函数
    assert(pxl != NULL);
    memcpy(pxl, enc->image->pxl, width * height * bytesPerPixel);


    //    int width = dmtxImageGetProp(enc->image, DmtxPropWidth);
    //    int height = dmtxImageGetProp(enc->image, DmtxPropHeight);
    //    int bytesPerPixel = dmtxImageGetProp(enc->image, DmtxPropBytesPerPixel);
    int bytesPerLine = dmtxImageGetProp(enc->image, DmtxPropRowSizeBytes);

    dmtxEncodeDestroy(&enc);//清除内存

    fprintf(stdout, "width:  \"%d\"\n", width);
    fprintf(stdout, "height: \"%d\"\n", height);
    fprintf(stdout, "bpp:    \"%d\"\n", bytesPerPixel);

    for (int i=0; i<width*height; i++){
       fprintf(stdout, "%d", (pxl[i*3])==0);
       if (i%width==width-1){
          fprintf(stdout, "\n");}

*/

void Widget::on_pushButton_2_clicked()
{
     QImage images=globalImg;
     QString dirPath;//创建文件夹路径
     QString filePath;//存储保存路径
     QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
     QString str = time.toString("yyyy-MM-dd-hhmmss"); //设置显示格式
     //      QString str = time.toString("yyyyMMdd_hhmmss"); //设置显示格式
     QString saveName=QString("%1-%2").arg(globastr).arg(str);//保存图片名字


     if(images.isNull())
     {
         QMessageBox::information(this,"信息","无生成图像");
     }
     else
     {
         filePath = QFileDialog::getExistingDirectory(this,"");//获取文件夹路径
         if(filePath.isEmpty())
         {
             QMessageBox::information(this,"信息","保存失败");
         }
         else
         {
             //         dirPath=QString("%1/保存实验%2").arg(filePath).arg(str);
             //         QDir *temp = new QDir;//声明文件对象
             //         temp->mkdir(dirPath);//创建文件夹
             //将图片重新命名并保存至刚刚创建的文件夹里
             QString savePath=QString("%1//%2.jpg").arg(filePath).arg(saveName);
             images.save(savePath);//QImage保存方法
             QMessageBox::information(this,"信息","保存成功");
         }
     }
}

void Widget::on_pushButton_3_clicked()
{

    ui->label->clear();//先清除label内容
    //打开图片操作
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("open image file"),
                "./", tr("Image files(*.bmp *.jpg *.pbm *.pgm *.png *.ppm *.xbm *.xpm);;All files (*.*)"));

    if(fileName.isEmpty())
    {
        QMessageBox mesg;
        mesg.warning(this,"警告","打开图片失败!");
        return;
    }
    else
    {
        ui->label->clear();
        QPixmap pix(fileName);
        pix=pix.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);
        ui->label->setPixmap(pix);
        ui->textEdit->clear();

        QImage img(fileName);
        // QImage imgcp=img.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);//Qt::KeepAspectRatio自适应大小，不变形
        // ui->label->setPixmap(QPixmap::fromImage(imgcp));//QImage 显示速度慢
        globalImg2=img.copy();
        qDebug()<<"src.format() "<<img.format();

    }



}

void Widget::on_pushButton_4_clicked()
{
    QTime time;
    time.start();
    QImage img=globalImg2;
    if(img.isNull())
    {
        QMessageBox::information(this,"信息","打开文件失败");
    }

    else
    {
        DmtxMessage *msg;
        DmtxRegion *reg;
        QImage src =img.copy();
        DmtxImage *imgdtx;
        QPixmap pix=QPixmap::fromImage(src);
        QString str;
        int leftLineAngle;
        int bottomLineAngle;
        int cornerx;
        int cornery;

        qDebug()<<"src.format() "<<src.format();

        if(src.format()==QImage::Format_Mono)
        {
        src=src.convertToFormat(QImage::Format_ARGB32);
        qDebug()<<"转换后：src.format() "<<src.format();
        }

        int pack=DmtxPack32bppXRGB;
        switch(src.format())
            {
            case QImage::Format_ARGB32:
            pack=DmtxPack32bppXRGB;
            break;
            case QImage::Format_RGB32:
            pack=DmtxPack32bppXRGB;
            break;
            case QImage::Format_RGB888:
            pack=DmtxPack24bppRGB;
            break;
            case QImage::Format_Indexed8:
            pack=DmtxPack8bppK;
            break;
            case  QImage::Format_Grayscale8:
            pack=DmtxPack8bppK;
            }

        // 增加超时时间。
        DmtxTime beginTime = dmtxTimeNow();	// 根据系统设置情况，获得当前时间
        long timeout_ms = 200;
        DmtxTime stopTime = dmtxTimeAdd(beginTime, timeout_ms);	// 增加xx ms

        imgdtx = dmtxImageCreate(src.bits(),src.width(),src.height(),pack);
        assert(imgdtx != NULL);

        DmtxDecode *dec = dmtxDecodeCreate(imgdtx, 1);
        assert(dec != NULL);

        reg = dmtxRegionFindNext(dec,&stopTime);	// 如果超时则认为没有找到
        // assert(reg != NULL);

        if(dmtxTimeExceeded(stopTime))
        {
            qDebug()<<"超时";
             QMessageBox::information(this,"信息","解码超时间");
        }
       else
        {
            if (reg != NULL)
            {
                msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);
                if (msg != NULL)
                {
                    //                    cout << msg->output << endl;
                    //                    cout << msg->outputIdx << endl;

                    string strout = (char*)msg->output;//解码信息
                    str=QString::fromStdString(strout);
                    QString outmsg=QString("<font color=\"#00FF00\">%1</font>").arg(QString::fromStdString(strout));
                    ui->textEdit->setText(outmsg);

                    //  qDebug()<<"reg->leftAngle "<<reg->leftAngle;
                    //  qDebug()<<"reg->leftAngle "<<reg->bottomAngle;
                    //   qDebug()<<"reg->finalPos.X "<<reg->finalPos.X;
                    //   qDebug()<<"reg->finalPos.Y "<<reg->finalPos.Y;
                    //qDebug()<<"reg->leftLine.mag"<<reg->leftLine.mag;
                    //qDebug()<<"reg->leftLine.hOffset"<<reg->leftLine.hOffset;
                    //qDebug()<<"reg->leftLine.stepBeg"<<reg->leftLine.stepBeg;
                    //qDebug()<<"reg->leftLine.stepPos"<<reg->leftLine.stepPos;
                    //qDebug()<<"reg->leftLine.stepNeg"<<reg->leftLine.stepNeg;
                    //qDebug()<<"reg->leftLine.distSq"<<reg->leftLine.distSq;
                    //qDebug()<<"reg->leftLine.locBeg.X "<<reg->leftLine.locBeg.X;
                    //qDebug()<<"reg->leftLine.locBeg.Y "<<reg->leftLine.locBeg.Y;

                    qDebug()<<"reg->leftLine.locPos.X "<<reg->leftLine.locPos.X;//准的
                    qDebug()<<"reg->leftLine.locPos.Y "<<reg->leftLine.locPos.Y;//准的
                    qDebug()<<"reg->leftLine.locNeg.X "<<reg->leftLine.locNeg.X;//准的
                    qDebug()<<"reg->leftLine.locNeg.Y "<<reg->leftLine.locNeg.Y;//准的
                    qDebug()<<"bottomLine.locPos.X "<<reg->bottomLine.locPos.X;
                    qDebug()<<"bottomLine.locPos.Y "<<reg->bottomLine.locPos.Y;
                    qDebug()<<"bottomLine.locNeg.X "<<reg->bottomLine.locNeg.X;
                    qDebug()<<"bottomLine.locNeg.y "<<reg->bottomLine.locNeg.Y;

                    QPainter p;
                    p.begin(&pix);
                    p.setPen(QPen(Qt::blue, 2));
                    p.drawEllipse(reg->leftLine.locPos.X-5,pix.height()-reg->leftLine.locPos.Y-5, 10, 10);//准的
                    p.setPen(QPen(Qt::yellow, 2));
                    p.drawEllipse(reg->leftLine.locNeg.X-5,img.height()-reg->leftLine.locNeg.Y-5, 10, 10);//准的

                    p.setPen(QPen(Qt::darkRed, 2));
                    p.drawEllipse(reg->bottomLine.locPos.X-5,img.height()-reg->bottomLine.locPos.Y-5, 10, 10);//准的
                    p.setPen(QPen(Qt::darkGreen, 2));
                    p.drawEllipse(reg->bottomLine.locNeg.X-5,img.height()-reg->bottomLine.locNeg.Y-5, 10, 10);//准的

                    int lineOriginX=(reg->leftLine.locNeg.X+reg->bottomLine.locPos.X)/2;
                    int lineOriginY=img.height()-(reg->leftLine.locNeg.Y+reg->bottomLine.locPos.Y)/2;
                    int lineLeftX=reg->leftLine.locPos.X;
                    int lineLeftY=pix.height()-reg->leftLine.locPos.Y;
                    int lineBottomX=reg->bottomLine.locNeg.X;
                    int lineBottomY=img.height()-reg->bottomLine.locNeg.Y;

                    p.setPen(QPen(Qt::red, 2));
                    p.drawLine(lineOriginX,lineOriginY,lineLeftX,lineLeftY);
                    p.drawLine(lineOriginX,lineOriginY,lineBottomX,lineBottomY);
                    p.end();

                    leftLineAngle=reg->leftLine.angle;
                    bottomLineAngle=reg->bottomAngle;
                    cornerx=lineOriginX;
                    cornery=lineOriginY;

                    dmtxMessageDestroy(&msg);
                }
                else
                {
                    qDebug()<<"无法检测到2";
                    QMessageBox::information(this,"信息","无法检测到2");
                }
                dmtxRegionDestroy(&reg);
            }
            else
            {
                qDebug()<<"无法检测到1";
                QMessageBox::information(this,"信息","无法检测到1");
            }

        }

        dmtxDecodeDestroy(&dec);
        dmtxImageDestroy(&imgdtx);

        qDebug()<<time.elapsed()/1000.0<<"s";

        ui->label->clear();
//        src=src.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);//Qt::KeepAspectRatio自适应大小，不变形
//        ui->label->setPixmap(QPixmap::fromImage(src));//QImage 显示速度慢
        pix=pix.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio);//Qt::KeepAspectRatio自适应大小，不变形
        ui->label->setPixmap(pix);

        ui->label_base->clear();
        QString base_str=str.left(8);
        QString label_base_text=QString("信息:左边 %1°底边 %2°角点X %3 角点Y %4 内容 %5..").
                arg(leftLineAngle).arg(bottomLineAngle).arg(cornerx).arg(cornery).arg(base_str);
        ui->label_base->setText(label_base_text);

        QString timestr=QString("解码耗时：%1s").arg(time.elapsed()/1000.0);
        ui->label_time->setText(timestr);
    }

    dataMatrixDecode();//简化版本
}


void dataMatrixDecode()
{
    //简化版本
    QTime time;
    QImage src("D:/code/QtLearning/dmtxMaker/1.jpg");
    DmtxMessage *msg;
    DmtxRegion *reg;
    DmtxImage *imgdtx;
    QString outstr;

    time.start();//qt开始计时

    qDebug()<<"src.format() "<<src.format();//注意图片格式要对应 dmtxImageCreate的 不然无法解码

    // 增加超时时间。
    DmtxTime beginTime = dmtxTimeNow();	// 根据系统设置情况，获得当前时间
    long timeout_ms = 200;
    DmtxTime stopTime = dmtxTimeAdd(beginTime, timeout_ms);	// 增加xx ms

    //创建dmtxImage，将qt读取到的图片存储到dmtxImage
    imgdtx = dmtxImageCreate(src.bits(),src.width(),src.height(),DmtxPack32bppXRGB);
    assert(imgdtx != NULL);
    DmtxDecode *dec = dmtxDecodeCreate(imgdtx, 1);//解码
    assert(dec != NULL);
    reg = dmtxRegionFindNext(dec,&stopTime);//查找下一个，如果超时则认为没有找到
    assert(reg != NULL);

    if(dmtxTimeExceeded(stopTime))
    {
        qDebug()<<"超时";
    }
    else
    {
        if (reg != NULL)
        {
            msg = dmtxDecodeMatrixRegion(dec, reg, DmtxUndefined);//获取解码信息
            if (msg != NULL)
            {
                cout << msg->output << endl;//输出解码信息
                cout << msg->outputIdx << endl;

                //qt输出解码信息string->QString
                string strout = (char*)msg->output;//解码信息
                outstr=QString::fromStdString(strout);
                qDebug()<<"解码信息:"<<outstr;//解码信息
                qDebug()<<"解码信息xx:"<<msg->output;//解码信息

                //二维码坐标信息
                qDebug()<<"reg->leftLine.locPos.X "<<reg->leftLine.locPos.X;
                qDebug()<<"reg->leftLine.locPos.Y "<<reg->leftLine.locPos.Y;
                qDebug()<<"reg->leftLine.locNeg.X "<<reg->leftLine.locNeg.X;
                qDebug()<<"reg->leftLine.locNeg.Y "<<reg->leftLine.locNeg.Y;
                qDebug()<<"bottomLine.locPos.X "<<reg->bottomLine.locPos.X;
                qDebug()<<"bottomLine.locPos.Y "<<reg->bottomLine.locPos.Y;
                qDebug()<<"bottomLine.locNeg.X "<<reg->bottomLine.locNeg.X;
                qDebug()<<"bottomLine.locNeg.y "<<reg->bottomLine.locNeg.Y;

                dmtxMessageDestroy(&msg);
            }
            else{qDebug()<<"无法检测到2";}

            dmtxRegionDestroy(&reg);
        }
        else{qDebug()<<"无法检测到1";}
    }

    dmtxDecodeDestroy(&dec);
    dmtxImageDestroy(&imgdtx);
    qDebug()<<time.elapsed()/1000.0<<"s";
}
