/*
   SPDX-FileCopyrightText: 2012-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboximportwidget.h"
#include "ui_mboximportwidget.h"

MBoxImportWidget::MBoxImportWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MBoxImportWidget)
{
    ui->setupUi(this);
    connect(ui->importMails, &QAbstractButton::clicked, this, &MBoxImportWidget::importMailsClicked);
    connect(ui->mCollectionRequestor, &MailCommon::FolderRequester::folderChanged, this, &MBoxImportWidget::collectionChanged);
}

MBoxImportWidget::~MBoxImportWidget()
{
    delete ui;
}

MailImporter::ImportMailsWidget *MBoxImportWidget::mailWidget()
{
    return ui->mMailImporterWidget;
}

void MBoxImportWidget::collectionChanged(const Akonadi::Collection &collection)
{
    ui->importMails->setEnabled(collection.isValid());
}

Akonadi::Collection MBoxImportWidget::selectedCollection() const
{
    return ui->mCollectionRequestor->collection();
}

void MBoxImportWidget::setImportButtonEnabled(bool enabled)
{
    ui->importMails->setEnabled(enabled);
}

#include "moc_mboximportwidget.cpp"
