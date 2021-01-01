/*
   SPDX-FileCopyrightText: 2012-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MBOXIMPORTWIDGET_H
#define MBOXIMPORTWIDGET_H

#include <QWidget>

namespace Ui
{
class MBoxImportWidget;
}

namespace Akonadi
{
class Collection;
}

namespace MailImporter
{
class ImportMailsWidget;
}

class MBoxImportWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MBoxImportWidget(QWidget *parent = nullptr);
    ~MBoxImportWidget();
    MailImporter::ImportMailsWidget *mailWidget();
    Q_REQUIRED_RESULT Akonadi::Collection selectedCollection() const;
    void setImportButtonEnabled(bool enabled);

private Q_SLOTS:
    void collectionChanged(const Akonadi::Collection &collection);

Q_SIGNALS:
    void importMailsClicked();

private:
    Ui::MBoxImportWidget *const ui;
};

#endif // MBOXIMPORTWIDGET_H
