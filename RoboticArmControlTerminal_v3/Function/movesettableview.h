#ifndef MOVESETTABLEVIEW_H
#define MOVESETTABLEVIEW_H

#include <QAbstractTableModel>

class MoveSetTableView : public QAbstractTableModel
{
public:
    explicit MoveSetTableView(QObject *parent = nullptr);
    ~MoveSetTableView();
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    void addData(QList<int> data, int index = -1);
    QList<int> getData(int index = -1);
    QList<int> delData(int index = -1);
    int getDataListSize(void);
    int _index;

private:
    QStringList _header;
    QList<QList<int>> _dataList;
};

#endif // MOVESETTABLEVIEW_H
