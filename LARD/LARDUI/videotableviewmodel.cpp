#include "videotableviewmodel.h"

#include <QDebug>
VideoTableViewModel::VideoTableViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_list.append("2018-11-19060543");
    m_list.append("2018-11-19070322");
    m_list.append("2018-11-20121155");
    m_list.append("2018-11-20161231");
    m_list.append("2018-11-19060543");
    m_list.append("2018-11-19070322");
    m_list.append("2018-11-20121155");
    m_list.append("2018-11-20161231");
    m_list.append("2018-11-19060543");
    m_list.append("2018-11-19070322");
    m_list.append("2018-11-20121155");
    m_list.append("2018-11-20161231");
    m_list.append("2018-11-19060543");
    m_list.append("2018-11-19070322");
    m_list.append("2018-11-20121155");
    m_list.append("2018-11-20161231");
}

//QVariant VideoTableViewModel::headerData(int section, Qt::Orientation orientation, int role) const
//{

////    switch (role) {
////    case Qt::TextAlignmentRole:
////            return Qt::AlignCenter;
////        break;
////    case Qt::DisplayRole:
////        if(orientation == Qt::Horizontal){
////              if(section == 0){
////                  return QVariant("dsadsa");
////              }else{
////                  return QVariant("");
////              }
////        }
////        break;
////    default:
////        break;
////    }
////    return QVariant();

//    if (role != Qt::DisplayRole)
//         return QVariant();
//     return "sadasda";
//}

int VideoTableViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_list.size();

}

int VideoTableViewModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;

}

QVariant VideoTableViewModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:

        int nRow = index.row();
        int mCol = index.column();
        auto d = m_list.at(nRow);
        if (d == nullptr){
            return QVariant("");
        }

        switch (mCol) {
        case 0:
            return QVariant( d);
            break;
        default:
            break;
        }
        break;

    }
    return QVariant();
}



//Qt::ItemFlags VideoTableViewModel::flags(const QModelIndex &index) const
//{
//    if(index.isValid()){
//        return QAbstractTableModel::flags(index);
//    }
//    Qt::ItemFlags flags;
//    flags = Qt::ItemIsSelectable|Qt::ItemIsEnabled;
//    return flags;
//}



VideoInfo::VideoInfo()
{

}

VideoInfo::~VideoInfo()
{

}

QString VideoInfo::filename() const
{
    return m_filename;
}

void VideoInfo::setFilename(const QString &filename)
{
    m_filename = filename;
}
