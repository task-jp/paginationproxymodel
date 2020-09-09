#ifndef IDENTITYPROXYMODEL_H
#define IDENTITYPROXYMODEL_H

#include <QtCore/QIdentityProxyModel>

class IdentityProxyModel : public QIdentityProxyModel
{
    Q_OBJECT
    Q_PROPERTY(int countPerPage READ countPerPage WRITE setCountPerPage NOTIFY countPerPageChanged)
public:
    enum Role {
        PageRole = Qt::UserRole
    };
    explicit IdentityProxyModel(QObject* parent = nullptr);
    ~IdentityProxyModel() override;

    QVariant data(const QModelIndex &index, int role) const override;

    int countPerPage() const;

public slots:
    void setCountPerPage(int countPerPage);

signals:
    void countPerPageChanged(int countPerPage);

private:
    class Private;
    QScopedPointer<Private> d;
};

#endif // IDENTITYPROXYMODEL_H
