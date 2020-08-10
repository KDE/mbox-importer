/*
   SPDX-FileCopyrightText: 2013-2020 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef MBOXMAINWINDOW_H
#define MBOXMAINWINDOW_H

#include <QDialog>

class MBoxImportWidget;
class MBoxMainWindow : public QDialog
{
    Q_OBJECT
public:
    explicit MBoxMainWindow(const QString &filename, QWidget *parent = nullptr);
    ~MBoxMainWindow();

private Q_SLOTS:
    void slotImportMBox();

private:
    QString mFileName;
    MBoxImportWidget *mImportWidget = nullptr;
};

#endif // MBOXMAINWINDOW_H
