#include "paginationproxymodel.h"
#include "identityproxymodel.h"

class PaginationProxyModel::Private
{
public:
    IdentityProxyModel source;
    int page = 0;
};

PaginationProxyModel::PaginationProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d(new Private)
{
    setFilterRole(IdentityProxyModel::PageRole);
    connect(this, &PaginationProxyModel::pageChanged, this, [this](int page) {
        setFilterFixedString(QString::number(page));
    });
    setFilterFixedString(QString::number(d->page));
    connect(&d->source, &IdentityProxyModel::countPerPageChanged
            , this, &PaginationProxyModel::countPerPageChanged);
    setSourceModel(&d->source);
}

PaginationProxyModel::~PaginationProxyModel() = default;

QAbstractItemModel *PaginationProxyModel::source() const
{
    return d->source.sourceModel();
}

void PaginationProxyModel::setSource(QAbstractItemModel *source)
{
    if (d->source.sourceModel() == source) return;
    d->source.setSourceModel(source);
    emit sourceChanged(source);
}

int PaginationProxyModel::countPerPage() const
{
    return d->source.countPerPage();
}

void PaginationProxyModel::setCountPerPage(int countPerPage)
{
    d->source.setCountPerPage(countPerPage);
}

int PaginationProxyModel::page() const
{
    return d->page;
}

void PaginationProxyModel::setPage(int page)
{
    if (d->page == page) return;
    d->page = page;
    emit pageChanged(page);
}
