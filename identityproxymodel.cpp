#include "identityproxymodel.h"

class IdentityProxyModel::Private
{
public:
    int countPerPage = 5;
};

IdentityProxyModel::IdentityProxyModel(QObject *parent)
    : QIdentityProxyModel(parent)
    , d(new Private)
{}

IdentityProxyModel::~IdentityProxyModel() = default;

QVariant IdentityProxyModel::data(const QModelIndex &index, int role) const
{
  if (role != PageRole)
    return QIdentityProxyModel::data(index, role);

  return QString::number(index.row() / d->countPerPage);
}

int IdentityProxyModel::countPerPage() const
{
    return d->countPerPage;
}

void IdentityProxyModel::setCountPerPage(int countPerPage)
{
    if (countPerPage == 0) return;
    if (d->countPerPage == countPerPage) return;
    auto prev = d->countPerPage;
    d->countPerPage = countPerPage;
    emit countPerPageChanged(countPerPage);

    auto topLeft = index(std::min(prev, countPerPage), 0);
    auto bottomRight = index(rowCount() - 1, 0);
    emit dataChanged(topLeft, bottomRight, {PageRole});
}
