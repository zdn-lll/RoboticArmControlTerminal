#include "movesettableview.h"

MoveSetTableView::MoveSetTableView(QObject *parent)
    : QAbstractTableModel{parent}
{
    _index = 0;
    _header << "时间（ms）"
            << "J1"
            << "J2"
            << "J3"
            << "J4"
            << "J5"
            << "J6";
    QList<int> data0;
    QList<int> data1;
    data0 << 1000
          << 180
          << 90
          << 2
          << 43
          << 23
          << 34;
    data1 << 23
          << 23
          << 23
          << 345
          << 35
          << 65
          << 34;
    _dataList.append(data0);
    _dataList.append(data1);
}

MoveSetTableView::~MoveSetTableView()
{

}

int MoveSetTableView::rowCount(const QModelIndex& parent) const
{
    return 100;
}

int MoveSetTableView::columnCount(const QModelIndex& parent) const
{
    return _header.count();
}

QVariant MoveSetTableView::data(const QModelIndex& index, int role) const
{
    if(index.row() < _dataList.size())
    {
        if(role == Qt::DisplayRole)
        {
            return _dataList[index.row()][index.column()];
        }
    }

    return QVariant();
}

QVariant MoveSetTableView::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        return _header[section];
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

void MoveSetTableView::addData(QList<int> data, int index)
{
    if(data.isEmpty())
    {
        return;
    }
    if(_dataList.size() >= 100)
    {
        return;
    }
    if(index <= -1 || index >= _dataList.size())
    {
        _dataList.append(data);
    }
    else {
        _dataList.insert(index, data);
    }
}

QList<int> MoveSetTableView::getData(int index)
{
    if(_dataList.isEmpty())
    {
        return QList<int>();
    }
    if(index <= -1)
    {
        return _dataList.last();
    }
    else if (index < _dataList.size()) {
        return _dataList.at(index);
    }
    else {
        return QList<int>();
    }
}

QList<int> MoveSetTableView::delData(int index)
{
    QList<int> del_data;
    if(_dataList.isEmpty())
    {
        return del_data;
    }
    if(index <= -1)
    {
        del_data = _dataList.last();
        _dataList.pop_back();
    }
    else if (index  < _dataList.size()) {
        del_data = _dataList[index];
        _dataList.removeAt(index);
    }
    return del_data;
}

int MoveSetTableView::getDataListSize()
{
    return _dataList.size();
}

