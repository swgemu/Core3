/*
 * AuctionItemImplementation.cpp
 *
 *  Created on: 12/03/2010
 *      Author: victor
 */

#include "server/ServerCore.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/managers/auction/AuctionManager.h"

void AuctionItemImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();
}

void AuctionItemImplementation::clearAuctionWithdraw() {
	if (auctionOptions & OPTION_WITHDRAW)
		auctionOptions &= ~OPTION_WITHDRAW;
}

void AuctionItemImplementation::notifyLoadFromDatabase() {
	clearAuctionWithdraw();

	if (getStatus() == AuctionItem::DELETED) {
		error() << "notifyLoadFromDatabase(), AuctionItem flagged as DELETED: " << *this;
	}
}

bool AuctionItemImplementation::destroyAuctionItemFromDatabase(bool checkAuctionMap, bool deleteAuctionedObject) {
	auto server = ServerCore::getZoneServer();

	if (server == nullptr) {
		error() << "destroyAuctionItemFromDatabase failed to get zone server";
		return false;
	}

	if (checkAuctionMap) {
		auto auctionManager = server->getAuctionManager();

		if (auctionManager == nullptr) {
			error() << "destroyAuctionItemFromDatabase failed to get Auction Manager";
			return false;
		}

		auto auctionsMap = auctionManager->getAuctionMap();

		if (auctionsMap == nullptr) {
			error() << "destroyAuctionItemFromDatabase failed to get AuctionsMap";
			return false;
		}

		if (auctionsMap->containsItem(getAuctionedItemObjectID())) {
			error() << "destroyAuctionItemFromDatabase exists in AuctionsMap: " << toStringData();
			return false;
		}
	}

	if (deleteAuctionedObject) {
		auto sellingID = getAuctionedItemObjectID();

		if (sellingID > 0) {
			setAuctionedItemObjectID(0);

			Core::getTaskManager()->executeTask([
				sellingID,
				aoid = getObjectID(),
				statusString = getStatusString(),
				logger = getLogger()
			] () {
				auto server = ServerCore::getZoneServer();

				if (server == nullptr)
					return;

				auto scno = server->getObject(sellingID);

				if (scno != nullptr) {
					Locker locker(scno);

					if (ConfigManager::instance()->getBool("Core3.AuctionItem.ExportOnDestroy", false)) {
						StringBuffer exportMsg;

						exportMsg << "destroyAuctionItemFromDatabase"
							<< " status=" << statusString
						    << " auctionObjectID: " << aoid
						;

						auto path = scno->exportJSON(exportMsg.toString());

						logger->info() << "[AuctionItem 0x" << hex << aoid << "] destroyAuctionItemFromDatabase: Exported deleted item to " << path;
					}

					scno->destroyObjectFromDatabase(true);
				}
			}, "AuctionItem_destroyAuctionItemFromDatabase", "slowQueue");
		}
	}

	setAuctionedItemObjectID(0);

	setStatus(AuctionItem::DELETED);

	server->destroyObjectFromDatabase(getObjectID());

	setPersistent(0);

	return true;
}

uint64 AuctionItemImplementation::getObjectID() const {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

String AuctionItemImplementation::getStatusString() const {
	switch (status) {
	case FORSALE:	return String("FORSALE");
	case SOLD:		return String("SOLD");
	case EXPIRED:	return String("EXPIRED");
	case OFFERED:	return String("OFFERED");
	case RETRIEVED:	return String("RETRIEVED");
	case DELETED:	return String("DELETED");
	}

	StringBuffer msg;
	msg << "UnknownStatus(" << status << ")";
	return msg.toString();
}

Logger* AuctionItemImplementation::getLogger() const {
	auto server = ServerCore::getZoneServer();

	if (server != nullptr) {
		auto auctionManager = server->getAuctionManager();

		if (auctionManager != nullptr) {
			return auctionManager->getLogger();
		}
	}

	return &Logger::console;
}

LoggerHelper AuctionItemImplementation::error() const {
	auto logHelper = getLogger()->error();

	logHelper << "[AuctionItem 0x" << hex << getObjectID() << "] ";

	return logHelper;
}

LoggerHelper AuctionItemImplementation::info(int forced) const {
	auto logHelper = getLogger()->info(forced);

	logHelper << "[AuctionItem 0x" << hex << getObjectID() << "] ";

	return logHelper;
}

LoggerHelper AuctionItemImplementation::debug() const {
	auto logHelper = getLogger()->debug();

	logHelper << "[AuctionItem 0x" << hex << getObjectID() << "] ";

	return logHelper;
}
