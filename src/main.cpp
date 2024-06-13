/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboxmainwindow.h"
#include <KAboutData>
#include <QApplication>

#include "mboximporter-version.h"
#include <KCrash>
#include <KLocalizedString>
#include <QCommandLineParser>
#include <QFileDialog>
#include <QIcon>

#define HAVE_KICONTHEME __has_include(<KIconTheme>)
#if HAVE_KICONTHEME
#include <KIconTheme>
#endif

#define HAVE_STYLE_MANAGER __has_include(<KStyleManager>)
#if HAVE_STYLE_MANAGER
#include <KStyleManager>
#endif

int main(int argc, char *argv[])
{
#if HAVE_KICONTHEME
    KIconTheme::initTheme();
#endif
    QApplication app(argc, argv);
    app.setDesktopFileName(QStringLiteral("org.kde.mboximporter"));
    KCrash::initialize();
#if HAVE_STYLE_MANAGER
    KStyleManager::initStyle();
#else // !HAVE_STYLE_MANAGER
#if defined(Q_OS_WIN) || defined(Q_OS_MACOS)
    QApplication::setStyle(QStringLiteral("breeze"));
#endif
#endif
    KLocalizedString::setApplicationDomain(QByteArrayLiteral("mboximporter"));

    KAboutData aboutData(QStringLiteral("mboximporter"),
                         i18n("MBox importer tool"),
                         QStringLiteral(MBOXIMPORTER_VERSION),
                         i18n("MBox Import Tool"),
                         KAboutLicense::GPL_V2,
                         i18n("Copyright © 2013-%1 MBoxImporter authors", QStringLiteral("2024")));
    aboutData.addAuthor(i18nc("@info:credit", "Laurent Montel"), i18n("Maintainer"), QStringLiteral("montel@kde.org"));

    QApplication::setWindowIcon(QIcon::fromTheme(QStringLiteral("kmail")));
    aboutData.setProductName(QByteArray("mboximporter"));

    KAboutData::setApplicationData(aboutData);

    QString fileName;
    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.addPositionalArgument(QStringLiteral("url"), i18n("URL of mbox to be imported"), QStringLiteral("[url]"));

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
