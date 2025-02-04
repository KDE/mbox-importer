/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <MailImporter/FilterInfoGui>
class MBoxImportWidget;

class MBoxImporterInfoGui : public MailImporter::FilterInfoGui
{
public:
    explicit MBoxImporterInfoGui(MBoxImportWidget *parent);
    ~MBoxImporterInfoGui() override;

    void setStatusMessage(const QString &status) override;
    void setFrom(const QString &from) override;
    void setTo(const QString &to) override;
    void setCurrent(const QString &current) override;
    void setCurrent(int percent = 0) override;
    void setOverall(int percent = 0) override;
    void addErrorLogEntry(const QString &log) override;
    void addInfoLogEntry(const QString &log) override;
    void clear() override;
    void alert(const QString &message) override;
    QWidget *parent() const override;

private:
    MBoxImportWidget *const mParent;
};
