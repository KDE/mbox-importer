/*
   SPDX-FileCopyrightText: 2013-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboxmainwindow.h"
using namespace Qt::Literals::StringLiterals;

#include <KAboutData>
#include <QApplication>

#include "mboximporter-version.h"
#include <KCrash>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QFileDialog>
#include <QIcon>

#include <KIconTheme>

#include <KStyleManager>

int main(int argc, char *argv[])
{
    KIconTheme::initTheme();
    QApplication app(argc, argv);
    app.setDesktopFileName(u"org.kde.mboximporter"_s);
    KStyleManager::initStyle();
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("mboximporter"));

    KAboutData aboutData(u"mboximporter"_s,
                         i18n("MBox importer tool"),
                         QStringLiteral(MBOXIMPORTER_VERSION),
                         i18n("MBox Import Tool"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2013-%1 MBoxImporter authors", u"2025"_s));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), u"montel@kde.org"_s);

    QApplication::setWindowIcon(QIcon::fromTheme(u"kmail"_s));
    aboutData.setProductName(QByteArray("mboximporter"));

    KAboutData::setApplicationData(aboutData);
    KCrash::initialize();

    QString fileName;
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.addPositionalArgument(u"url"_s, i18n("URL of mbox to be imported"), u"[url]"_s);

    parser.process(app);
    aboutData.processCommandLine(&parser);

    const QStringList &args = parser.positionalArguments();
    if (!args.isEmpty()) {
        fileName = args.at(0);
    } else {
        fileName = QFileDialog::getOpenFileName();
    }
    if (fileName.isEmpty()) {
        return 0;
    }
    auto w = new MBoxMainWindow(fileName);
    w->show();
    QObject::connect(w, &MBoxMainWindow::rejected, &app, &QApplication::quit);
    const int ret = app.exec();
    delete w;
    return ret;
}
