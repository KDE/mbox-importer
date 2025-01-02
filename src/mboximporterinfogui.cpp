/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboximporterinfogui.h"
#include "mboximportwidget.h"

#include <MailImporter/ImportMailsWidget>

#include <KMessageBox>

#include <QApplication>
#include <QListWidgetItem>

MBoxImporterInfoGui::MBoxImporterInfoGui(MBoxImportWidget *parent)
    : MailImporter::FilterInfoGui()
    , mParent(parent)
{
}

MBoxImporterInfoGui::~MBoxImporterInfoGui() = default;

void MBoxImporterInfoGui::setStatusMessage(const QString &status)
{
    mParent->mailWidget()->setStatusMessage(status);
}

void MBoxImporterInfoGui::setFrom(const QString &from)
{
    mParent->mailWidget()->setFrom(from);
}

void MBoxImporterInfoGui::setTo(const QString &to)
{
    mParent->mailWidget()->setTo(to);
}

void MBoxImporterInfoGui::setCurrent(const QString &current)
{
    mParent->mailWidget()->setCurrent(current);
    qApp->processEvents();
}

void MBoxImporterInfoGui::setCurrent(int percent)
{
    mParent->mailWidget()->setCurrent(percent);
    qApp->processEvents(); // Be careful - back & finish buttons disabled, so only user event that can happen is cancel/close button
}

void MBoxImporterInfoGui::setOverall(int percent)
{
    mParent->mailWidget()->setOverall(percent);
}

void MBoxImporterInfoGui::addInfoLogEntry(const QString &log)
{
    auto item = new QListWidgetItem(log);
    item->setForeground(Qt::blue);
    mParent->mailWidget()->addItem(item);
    mParent->mailWidget()->setLastCurrentItem();
    qApp->processEvents();
}

void MBoxImporterInfoGui::addErrorLogEntry(const QString &log)
{
    auto item = new QListWidgetItem(log);
    item->setForeground(Qt::red);
    mParent->mailWidget()->addItem(item);
    mParent->mailWidget()->setLastCurrentItem();
    qApp->processEvents();
}

void MBoxImporterInfoGui::clear()
{
    mParent->mailWidget()->clear();
}

void MBoxImporterInfoGui::alert(const QString &message)
{
    KMessageBox::information(mParent, message);
}

QWidget *MBoxImporterInfoGui::parent() const
{
    return mParent;
}
