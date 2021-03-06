/*
   SPDX-FileCopyrightText: 2013-2021 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mboximportkernel.h"

#include <AkonadiCore/session.h>
#include <KIdentityManagement/kidentitymanagement/identitymanager.h>
#include <KSharedConfig>
#include <MailCommon/FolderCollectionMonitor>
#include <changerecorder.h>
#include <entitymimetypefiltermodel.h>
#include <entitytreemodel.h>

MBoxImporterKernel::MBoxImporterKernel(QObject *parent)
    : QObject(parent)
{
    mIdentityManager = KIdentityManagement::IdentityManager::self();
    Akonadi::Session *session = new Akonadi::Session("MBox importer Kernel ETM", this);
    mFolderCollectionMonitor = new MailCommon::FolderCollectionMonitor(session, this);

    mEntityTreeModel = new Akonadi::EntityTreeModel(folderCollectionMonitor(), this);
    mEntityTreeModel->setListFilter(Akonadi::CollectionFetchScope::Enabled);
    mEntityTreeModel->setItemPopulationStrategy(Akonadi::EntityTreeModel::LazyPopulation);

    mCollectionModel = new Akonadi::EntityMimeTypeFilterModel(this);
    mCollectionModel->setSourceModel(mEntityTreeModel);
    mCollectionModel->addMimeTypeInclusionFilter(Akonadi::Collection::mimeType());
    mCollectionModel->setHeaderGroup(Akonadi::EntityTreeModel::CollectionTreeHeaders);
    mCollectionModel->setDynamicSortFilter(true);
    mCollectionModel->setSortCaseSensitivity(Qt::CaseInsensitive);
}

KIdentityManagement::IdentityManager *MBoxImporterKernel::identityManager()
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
    return QStringList();
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
