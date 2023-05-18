#include "noteview.h"
#include <QImage>
#include <QPixmap>
#include "SnDataLoad.h"
#include <QRectF>
#include <QSGClipNode>
NoteView::NoteView()
{

}

void NoteView::paint(QPainter *painter)
{
    qDebug() << "paint";
    //    painter->setPen(QPen(Qt::black,1));//设置画笔形式
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawRect(0, 0, width(), height());

    painter->setPen(QPen(Qt::black,1));//设置画笔形式
    painter->drawRect(0, 0, width()-1, height()-1);

    SnDataLoad load;
    QString layer("MAINLAYER");
    unsigned char *data =load.loadImageData(mNotePath.toLocal8Bit().toStdString(), mPageIndex, layer.toLocal8Bit().toStdString());
//    for(int i=3600;i<3650;++i){
//        qDebug()<<data[i]<<",";
//    }
    if(data==nullptr){
        qDebug() << "data is null";
        return;
    }
    painter->setPen(Qt::NoPen);
    //    painter->setRenderHint(QPainter::Antialiasing, true);
    //    painter->setRenderHint(QPainter::SmoothPixmapTransform, true );
    QImage image(data, 1404, 1872,QImage::Format_ARGB32);
//    image=image.scaled(1404*0.7,1872*0.7);
    //    QPixmap pixmap=QPixmap::fromImage(image);
    painter->drawImage(0,0,image);
    //    painter->drawPixmap(0, 0, pixmap);
    delete [] data;
}

void NoteView::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry)
    //        setClipRect(newGeometry);
    //        update();
}

int NoteView::getPageIndex()
{
    return mPageIndex;
}

void NoteView::setPageIndex(const int &index)
{
    qDebug()<<"setPageIndex:"<<index;
    this->mPageIndex=index;
    emit pageIndexChanged();
}

void NoteView::setNotePath(const QString &path)
{
    qDebug()<<"setNotePath:"<<path;
    this->mNotePath=path;
    emit notePathChanged();
}

QString NoteView::getNotePath()
{
    return mNotePath;
}
