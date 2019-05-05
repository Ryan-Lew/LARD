#ifndef VIDEOTABLEVIEW_H
#define VIDEOTABLEVIEW_H

#include <QAbstractTableModel>
#include <QVariant>
class VideoInfo:public QObject{
    Q_OBJECT
public :
    explicit VideoInfo();
    ~VideoInfo();

    QString filename() const;
    void setFilename(const QString &filename);

private:
    QString m_filename;
};
class VideoTableViewModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit VideoTableViewModel(QObject *parent = nullptr);

    // Header:
    //QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    //Qt::ItemFlags flags(const QModelIndex &index) const;

private:
    QList<QString> m_list;
};

#endif // VIDEOTABLEVIEW_H
