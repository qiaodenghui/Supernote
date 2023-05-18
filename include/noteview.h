#ifndef NOTEVIEW_H
#define NOTEVIEW_H
#include <QtQml>
#include <QPainter>
#include <QQuickPaintedItem>

class NoteView : public QQuickPaintedItem {
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int pageIndex READ getPageIndex WRITE setPageIndex NOTIFY pageIndexChanged)
    Q_PROPERTY(QString notePath READ getNotePath WRITE setNotePath NOTIFY notePathChanged)
public:
    NoteView();
    void paint(QPainter *painter) override;
    int getPageIndex();
    void setPageIndex(const int &index);
    void setNotePath(const QString &path);
    QString getNotePath();

  protected:
  void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;

signals:
    void pageIndexChanged();
    void notePathChanged();
private:
    int mPageIndex=0;
    QString mNotePath;
};

#endif // NOTEVIEW_H
