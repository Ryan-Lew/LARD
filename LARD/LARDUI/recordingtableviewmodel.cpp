#include "recordingtableviewmodel.h".h"

#include <QDebug>
RecordingTableViewModel::RecordingTableViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_list.append("COURSE CHANGE");
    m_list.append("DONT APPORACH");
    m_list.append("USE SOUND CONNON");
    m_list.append("DECENZO");

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

int RecordingTableViewModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_list.size();

}

int RecordingTableViewModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return 1;

}

QVariant RecordingTableViewModel::data(const QModelIndex &index, int role) const
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


