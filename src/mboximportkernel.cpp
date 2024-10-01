/*
   SPDX-FileCopyrightText: 2013-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboximportkernel.h"

#include <Akonadi/ChangeRecorder>
#include <Akonadi/EntityMimeTypeFilterModel>
#include <Akonadi/EntityTreeModel>
#include <Akonadi/Session>
#include <KIdentityManagementCore/IdentityManager>
#include <KSharedConfig>
#include <MailCommon/FolderCollectionMonitor>

MBoxImporterKernel::MBoxImporterKernel(QObject *parent)
    : QObject(parent)
{
    mIdentityManager = KIdentityManagementCore::IdentityManager::self();
    auto session = new Akonadi::Session("MBox importer Kernel ETM", this);
    mFolderCollectionMonitor = new MailCommon::FolderCollectionMonitor(session, this);

    mEntityTreeModel = new Akonadi::EntityTreeModel(folderCollectionMonitor(), this);
    mEntityTreeModel->setListFilter(Akonadi::CollectionFetchScope::Enabled);
    mEntityTreeModel->setItemPopulationStrategy(Akonadi::EntityTreeModel::LazyPopulation);

    mCollectionModel = new Akonadi::EntityMimeTypeFilterModel(this);
    mCollectionModel->setSourceModel(mEntityTreeModel);
    mCollectionModel->addMimeTypeInclusionFilter(Akonadi::Collection::mimeType());
    mCollectionModel->setHeaderGroup(Akonadi::EntityTreeModel::CollectionTreeHeaders);
    mCollectionModel->setSortCaseSensitivity(Qt::CaseInsensitive);
}

KIdentityManagementCore::IdentityManager *MBoxImporterKernel::identityManager()
{
    return mIdentityManager;
}

MessageComposer::MessageSender *MBoxImporterKernel::msgSender()
{
    return nullptr;
}

Akonadi::EntityMimeTypeFilterModel *MBoxImporterKernel::collectionModel() const
{
    return mCollectionModel;
}

KSharedConfig::Ptr MBoxImporterKernel::config()
{
    return KSharedConfig::openConfig();
}

void MBoxImporterKernel::syncConfig()
{
    Q_ASSERT(false);
}

MailCommon::JobScheduler *MBoxImporterKernel::jobScheduler() const
{
    Q_ASSERT(false);
    return nullptr;
}

Akonadi::ChangeRecorder *MBoxImporterKernel::folderCollectionMonitor() const
{
    return mFolderCollectionMonitor->monitor();
}

void MBoxImporterKernel::updateSystemTray()
{
    Q_ASSERT(false);
}

bool MBoxImporterKernel::showPopupAfterDnD()
{
    return false;
}

qreal MBoxImporterKernel::closeToQuotaThreshold()
{
    return 80;
}

QStringList MBoxImporterKernel::customTemplates()
{
    Q_ASSERT(false);
    return {};
}

bool MBoxImporterKernel::excludeImportantMailFromExpiry()
{
    Q_ASSERT(false);
    return true;
}

Akonadi::Collection::Id MBoxImporterKernel::lastSelectedFolder()
{
    Q_ASSERT(false);
    return Akonadi::Collection::Id();
}

void MBoxImporterKernel::setLastSelectedFolder(Akonadi::Collection::Id col)
{
    Q_UNUSED(col)
}

void MBoxImporterKernel::expunge(Akonadi::Collection::Id col, bool sync)
{
    Q_UNUSED(col)
    Q_UNUSED(sync)
}

#include "moc_mboximportkernel.cpp"
