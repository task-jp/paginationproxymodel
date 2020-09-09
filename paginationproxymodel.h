#ifndef PAGINATIONPROXYMODEL_H
#define PAGINATIONPROXYMODEL_H

#include <QtCore/QSortFilterProxyModel>

class PaginationProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QAbstractItemModel *source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(int countPerPage READ countPerPage WRITE setCountPerPage NOTIFY countPerPageChanged)
    Q_PROPERTY(int page READ page WRITE setPage NOTIFY pageChanged)

public:
    explicit PaginationProxyModel(QObject *parent = nullptr);
    ~PaginationProxyModel() override;

    QAbstractItemModel *source() const;
    int countPerPage() const;
    int page() const;

public slots:
    void setSource(QAbstractItemModel *source);
    void setCountPerPage(int countPerPage);
    void setPage(int page);

signals:
    void sourceChanged(QAbstractItemModel *source);
    void countPerPageChanged(int countPerPage);
    void pageChanged(int page);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // PAGINATIONPROXYMODEL_H
