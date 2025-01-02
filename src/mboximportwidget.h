/*
   SPDX-FileCopyrightText: 2012-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

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
    ~MBoxImportWidget() override;
    MailImporter::ImportMailsWidget *mailWidget();
    [[nodiscard]] Akonadi::Collection selectedCollection() const;
    void setImportButtonEnabled(bool enabled);

private Q_SLOTS:
    void collectionChanged(const Akonadi::Collection &collection);

Q_SIGNALS:
    void importMailsClicked();

private:
    Ui::MBoxImportWidget *const ui;
};
