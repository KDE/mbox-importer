/*
   SPDX-FileCopyrightText: 2013-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>

class MBoxImportWidget;
class MBoxMainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MBoxMainWindow(const QString &filename, QWidget *parent = nullptr);
    ~MBoxMainWindow() override;

private Q_SLOTS:
    void slotImportMBox();

private:
    const QString mFileName;
    MBoxImportWidget *mImportWidget = nullptr;
};
