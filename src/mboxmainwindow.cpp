/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboxmainwindow.h"
#include "mboximportwidget.h"
#include "mboximportkernel.h"
#include "mboximporterinfogui.h"

#include <MailImporter/FilterMBox>
#include <MailImporter/ImportMailsWidget>
#include <MailImporterAkonadi/FilterImporterAkonadi>

#include <MailCommon/MailKernel>

#include <KLocalizedString>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QVBoxLayout>

MBoxMainWindow::MBoxMainWindow(const QString &filename, QWidget *parent)
    : QDialog(parent),
      mFileName(filename)
{
    setWindowTitle(i18nc("@title:window", "Import mbox file"));
    auto *mainLayout = new QVBoxLayout(this);

    auto *kernel = new MBoxImporterKernel(this);
    CommonKernel->registerKernelIf(kernel);   //register KernelIf early, it is used by the Filter classes
    CommonKernel->registerSettingsIf(kernel);   //SettingsIf is used in FolderTreeWidget

    mImportWidget = new MBoxImportWidget(this);
    mainLayout->addWidget(mImportWidget);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &MBoxMainWindow::reject);

    buttonBox->button(QDialogButtonBox::Close)->setDefault(true);
    mainLayout->addWidget(buttonBox);

    connect(mImportWidget, &MBoxImportWidget::importMailsClicked, this, &MBoxMainWindow::slotImportMBox);
    resize(800, 600);
}

MBoxMainWindow::~MBoxMainWindow()
{
}

void MBoxMainWindow::slotImportMBox()
{
    auto *info = new MailImporter::FilterInfo();
    auto *filterImporterAkonadi = new MailImporter::FilterImporterAkonadi(info);
    auto *infoGui = new MBoxImporterInfoGui(mImportWidget);
    info->setFilterInfoGui(infoGui);
    filterImporterAkonadi->setRootCollection(mImportWidget->selectedCollection());
    info->clear(); // Clear info from last time

    info->setStatusMessage(i18n("Import in progress"));
    MailImporter::FilterMBox mbox;
    mbox.setFilterImporter(filterImporterAkonadi);
    mbox.setFilterInfo(info);
    info->clear();
    mbox.importMails({mFileName});
    info->setStatusMessage(i18n("Import finished"));
}

