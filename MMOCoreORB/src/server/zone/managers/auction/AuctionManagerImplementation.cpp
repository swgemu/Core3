/*
 * AuctionManagerImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "templates/manager/TemplateManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"
#include "server/zone/packets/auction/CancelLiveAuctionResponseMessage.h"
#include "server/zone/packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "server/zone/packets/auction/RetrieveAuctionItemResponseMessage.h"
#include "server/zone/packets/auction/BidAuctionResponseMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "CheckAuctionsTask.h"
#include "ExpireAuctionTask.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/components/vendor/AuctionTerminalDataComponent.h"
#include "server/zone/objects/player/sessions/TradeSession.h"
#include "AuctionSearchTask.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/transaction/TransactionLog.h"

void AuctionManagerImplementation::initialize() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	auto logLevel = ConfigManager::instance()->getInt("Core3.AuctionManager.LogLevel", (int)-1);

	if (logLevel > -1) {
		setGlobalLogging(false);
		setFileLogger("log/auctions.log", true, ConfigManager::instance()->getRotateLogAtStart());
		setLogSynchronized(true);
		setRotateLogSizeMB(ConfigManager::instance()->getInt("Core3.AuctionManager.RotateLogSizeMB", ConfigManager::instance()->getRotateLogSizeMB()));
		setLogToConsole(false);
		info(true) << "AuctionManager initializing.";
		setLogLevel(static_cast<Logger::LogLevel>(logLevel));
	}

	Core::getTaskManager()->initializeCustomQueue("AuctionSearch", ConfigManager::instance()->getMaxAuctionSearchJobs(), true);

	auctionMap = new AuctionsMap();

	ObjectDatabase* auctionDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("auctionitems", true);
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	ObjectDatabaseIterator iterator(auctionDatabase);

	Time startTime;
	Time progressTime;
	int countDatabaseItems = 0;
	int countDuplicates = 0;
	uint64 objectID = 0;

	Vector<Reference<AuctionItem*> > itemsToDelete;
	Vector<ManagedReference<AuctionItem*> > orphanedBazaarItems;
	ManagedReference<SceneObject*> defaultBazaar = nullptr;
	ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();

	while (iterator.getNextKey(objectID)) {
		countDatabaseItems++;
		Reference<AuctionItem*> auctionItem = Core::getObjectBroker()->lookUp(objectID).castTo<AuctionItem*>();
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		if(auctionItem == nullptr) {
			error() << "Unable to load auction item: " << objectID;
			continue;
		}

		Locker lock(auctionItem);

		if (progressTime.miliDifference() > 5000) {
			progressTime.updateToCurrentTime();
			info(true) << "Scanned " << countDatabaseItems << " auctionitems db object(s) and loaded " << auctionMap->getTotalItemCount() << " object(s).";
		}

		if (auctionItem->getStatus() == AuctionItem::RETRIEVED
		|| (auctionItem->getStatus() == AuctionItem::EXPIRED && auctionItem->getExpireTime() <= time(0))) {
			itemsToDelete.add(auctionItem);
			continue;
		}

		ManagedReference<SceneObject*> vendor = zoneServer->getObject(auctionItem->getVendorID());

		if(vendor == nullptr || vendor->getZone() == nullptr) {
			if(auctionItem->isOnBazaar()) {
				orphanedBazaarItems.add(auctionItem);
				continue;
			}

			if(vendor != nullptr) {
				error() << "Vendor with no zone, deleting vendorObject: " << *vendor;
				vendor->destroyObjectFromWorld(true);
				vendor->destroyObjectFromDatabase();
			}

			warning() << "Auction Item's vendor is gone, deleting auctionItem: " << *auctionItem;
			itemsToDelete.add(auctionItem);
			continue;
		}

		String ownerName = playerManager->getPlayerName(auctionItem->getOwnerID());

		if (ownerName.isEmpty()) {
			error() << "Auction with invalid owner, deleting auctionItem: " << *auctionItem;
			itemsToDelete.add(auctionItem);
			continue;
		}

		uint64 vendorExpire = time(0) + AuctionManager::VENDOREXPIREPERIOD;
		uint64 commodityExpire = time(0) + AuctionManager::COMMODITYEXPIREPERIOD;

		if (auctionItem->getStatus() == AuctionItem::FORSALE && auctionItem->getExpireTime() > vendorExpire) {
			auto oldExpire = auctionItem->getExpireTime();
			auctionItem->setExpireTime(vendorExpire);
			error() << "Invalid expiration time for vendor auction, was: " << oldExpire << " auctionItem: " << *auctionItem;
		}

		if (auctionItem->getStatus() == AuctionItem::OFFERED && auctionItem->getExpireTime() > commodityExpire) {
			auto oldExpire = auctionItem->getExpireTime();
			auctionItem->setExpireTime(commodityExpire);
			error() << "Invalid expiration time for auction, was: " << oldExpire << " auctionItem: " << *auctionItem;
		}

		if(vendor->isBazaarTerminal() && defaultBazaar == nullptr)
			defaultBazaar = vendor;

		int result = auctionMap->addItem(nullptr, vendor, auctionItem);

		// On duplicate item, pick the highest auctionItem oid and arrange to delete the rest
		if (result == ItemSoldMessage::ALREADYFORSALE) {
			countDuplicates++;
			Reference<AuctionItem*> currentItem = auctionMap->getItem(auctionItem->getAuctionedItemObjectID());

			if (auctionItem->getObjectID() > currentItem->getObjectID()) {
				Reference<SceneObject*> currentVendor = zoneServer->getObject(currentItem->getVendorID());

				auctionMap->removeItem(currentVendor, currentItem);
				itemsToDelete.add(currentItem);

				// Try again, result is checked below
				result = auctionMap->addItem(nullptr, vendor, auctionItem);
			} else {
				itemsToDelete.add(auctionItem);
				continue;
			}
		}

		if(result != ItemSoldMessage::SUCCESS) {
			auto msg = error();

			msg << "Failed to addItem to AuctionsMap " << ItemSoldMessage::statusToString(result) << ", auctionItem: " << *auctionItem;

			if (result == ItemSoldMessage::ALREADYFORSALE) {
				Reference<AuctionItem*> otherItem = auctionMap->getItem(auctionItem->getAuctionedItemObjectID());

				if (otherItem != nullptr) {
					msg << "; otherAuctionItem: " << *otherItem;
				}
			}

			msg.flush();
			continue;
		}

		if(auctionItem->isOnBazaar() || auctionItem->getStatus() == AuctionItem::OFFERED)
			auctionMap->addToCommodityLimit(auctionItem);

		if(auctionItem->isAuction()) {
			Reference<Task*> newTask = new ExpireAuctionTask(_this.getReferenceUnsafeStaticCast(), auctionItem);
			newTask->schedule((auctionItem->getExpireTime() - time(0)) * 1000);

			Locker locker(&auctionEvents);
			auctionEvents.put(auctionItem->getAuctionedItemObjectID(), newTask);
		}
	}

	for(int i = 0; i < itemsToDelete.size(); ++i) {
		auto auctionItem = itemsToDelete.get(i);

		if (auctionItem == nullptr) {
			continue;
		}

		Locker lock(auctionItem);

		// By default delete auctioned object on Expired auctions.
		auto deleteAuctionedObject = auctionItem->getStatus() == AuctionItem::EXPIRED;

		auto msg = error();

		msg << "Deleting " << auctionItem->getStatusString() << " item";

		if (auctionMap->containsItem(auctionItem->getAuctionedItemObjectID())) {
			msg << " (Duplicate Listing)";

			deleteAuctionedObject = false; // Other auctionItem holds the object
		}

		Reference<SceneObject*> vendor = zoneServer->getObject(auctionItem->getVendorID());

		if (vendor == nullptr) {
			msg << " (Vendor missing)";
		}

		msg << ", auctionItem: " << *auctionItem;

		if (!deleteAuctionedObject) {
			// If we're not deleting it clear the auctioned item
			auctionItem->setAuctionedItemObjectID(0);
		}

		msg.flush();

		auctionItem->destroyAuctionItemFromDatabase(false, deleteAuctionedObject);
	}

	/// This is in case a bazaar is removed, it could move and item
	/// to a difference city, but at least it doesn't poof
	if(defaultBazaar != nullptr) {

		for(int i = 0; i < orphanedBazaarItems.size(); ++i) {
			ManagedReference<AuctionItem*> auctionItem = orphanedBazaarItems.get(i);

			Locker lock(auctionItem);

			String vuid = getVendorUID(defaultBazaar);
			auctionMap->addItem(nullptr, defaultBazaar, auctionItem);

			Locker alocker(auctionItem);
			auctionItem->setVendorID(defaultBazaar->getObjectID());

			if(auctionItem->isAuction()) {
				Reference<Task*> newTask = new ExpireAuctionTask(_this.getReferenceUnsafeStaticCast(), auctionItem);
				newTask->schedule((auctionItem->getExpireTime() - time(0)) * 1000);

				Locker locker(&auctionEvents);
				auctionEvents.put(auctionItem->getAuctionedItemObjectID(), newTask);
			}
		}
	}

	for(int i = 0; i < pendingUIDUpdates.size(); ++i) {
		ManagedReference<SceneObject*> vendor = pendingUIDUpdates.elementAt(i).getKey();
		String uid = pendingUIDUpdates.get(vendor);
		String oldUID = pendingOldUIDUpdates.get(vendor);

		auctionMap->updateUID(vendor, oldUID, uid);
	}

	locker.release();

	Core::getTaskManager()->executeTask([=] () {
		checkAuctions(true);
		checkVendorItems(true);
	}, "StartupAuctionManagerCheck", "slowQueue");

	auto elapsed = startTime.miliDifference() / 1000.0;
	int ps = elapsed > 0 ? countDatabaseItems / elapsed : countDatabaseItems;
	int skipped = countDatabaseItems - auctionMap->getTotalItemCount();

	info(true)
		<< "Scanned " << countDatabaseItems << " auctionitem db object(s) "
		<< "in " << elapsed << " second(s), (" << ps << "/s), "
		<< "skipped " << skipped << " (" << countDuplicates << " duplicate listings), "
		<< "loaded " << auctionMap->getTotalItemCount() << " object(s) into auctionsMap.";
}

void AuctionManagerImplementation::checkVendorItems(bool startupTask) {
	if (startupTask)
		info("checkVendorItems initial startup task", true);

    	Timer timer(Time::MONOTONIC_TIME);

	timer.start();
	TerminalListVector items = auctionMap->getVendorTerminalData("", "", 0);

	info("Checking " + String::valueOf(items.size()) + " vendor terminals", true);

	doAuctionMaint(&items, "vendor", startupTask);

	auto elapsed = timer.stopMs();

	info("Vendor terminal checks completed in " + String::valueOf(elapsed) + "ms", true);

	if (startupTask) {
		info(true) << "Market enabled";

		marketEnabled = true;
	}
}

void AuctionManagerImplementation::checkAuctions(bool startupTask) {
	if (startupTask)
		info("checkAuctions initial startup task", true);

	Reference<CheckAuctionsTask*> task = new CheckAuctionsTask(_this.getReferenceUnsafeStaticCast());
	task->schedule(CHECKEVERY * 60 * 1000);

    Timer timer(Time::MONOTONIC_TIME);
	timer.start();
	TerminalListVector items = auctionMap->getBazaarTerminalData("", "", 0);

	info("Checking " + String::valueOf(items.size()) + " bazaar terminals", true);

	doAuctionMaint(&items, "bazaar", startupTask);

	auto elapsed = timer.stopMs();

	info("Bazaar terminal checks completed in " + String::valueOf(elapsed) + "ms", true);
}

void AuctionManagerImplementation::doAuctionMaint(TerminalListVector* items, const String& logTag, bool startupTask) {
	Time expireTime;
	Time progressTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;

	int countTotal = 0;
	int countUpdated = 0;
	int countInvalid = 0;

	for (int i = 0; i < items->size(); ++i) {
		Reference<TerminalItemList*>& terminalList = items->get(i);

		if (terminalList == nullptr || terminalList->size() == 0)
			continue;

		// Get a copy of this terminal's list because the loop deletes some objects as it runs
		Reference<TerminalItemList*> list = new TerminalItemList(*terminalList);

		for (int j = 0; j < list->size(); ++j) {
			ManagedReference<AuctionItem*> item = list->get(j);

			if (item == nullptr)
				continue;

			Locker locker(item);

			countTotal++;

			if (progressTime.miliDifference() > 5000) {
				progressTime.updateToCurrentTime();
				info(true) << logTag << ": Checked " << countTotal  << " auctions in " << i << " of " << items->size() << " " << logTag << "s.";
			}

			if (item->getStatus() == AuctionItem::DELETED) {
				error() << "Skipping deleted auctionItem: " << *item;
				continue;
			}

			ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
			ManagedReference<PlayerManager*> playerManager = zoneServer->getPlayerManager();
			String ownerName = playerManager->getPlayerName(item->getOwnerID());

			if(vendor == nullptr || vendor->getZone() == nullptr || ownerName.isEmpty()) {
				StringBuffer errMsg;

				if (vendor == nullptr) {
					errMsg << "missing vendor, ";
				}

				if (vendor != nullptr && vendor->getZone() == nullptr) {
					errMsg << "vendor missing zone, ";
				}

				if (ownerName.isEmpty()) {
					errMsg << "missing owner, ";
				}

				error() << "Auction Item failed validation: " << errMsg.toString() << "deleting auctionItem: " << *item;

				uint64 sellingId = item->getAuctionedItemObjectID();
				auctionMap->deleteItem(vendor, item, true);
				continue;
			}

			uint64 vendorExpire = time(0) + AuctionManager::VENDOREXPIREPERIOD;
			uint64 commodityExpire = time(0) + AuctionManager::COMMODITYEXPIREPERIOD;
			bool updatedExpire = false;
			uint64 oldExpire = 0;

			if (item->getStatus() == AuctionItem::FORSALE && item->getExpireTime() > vendorExpire) {
				oldExpire = item->getExpireTime();
				item->setExpireTime(vendorExpire);
				updatedExpire = true;
			}

			if (item->getStatus() == AuctionItem::OFFERED && item->getExpireTime() > commodityExpire) {
				oldExpire = item->getExpireTime();
				item->setExpireTime(commodityExpire);
				updatedExpire = true;
			}

			if (updatedExpire) {
				if(item->isAuction() && auctionEvents.contains(item->getAuctionedItemObjectID())) {
					Reference<Task*> newTask = auctionEvents.get(item->getAuctionedItemObjectID());

					if(newTask != nullptr)
						newTask->reschedule((item->getExpireTime() - time(0)) * 1000);
				}

				error() << "Auction Item had invalid expiration time. Old: " << oldExpire << ", new: " << item->getExpireTime() << ", auctionItem: " << *item;
			}

			if (item->getExpireTime() <= currentTime) {
				if (item->getStatus() == AuctionItem::EXPIRED) {
					expireSale(item);
					continue;
				}
			}

			if (item->getStatus() == AuctionItem::RETRIEVED) {
				error() << "Found RETRIEVED item in maintenance, auctionItem: " << *item;
				auctionMap->deleteItem(vendor, item);
				continue;
			}

			if (startupTask && ConfigManager::instance()->getBool("Core3.AuctionManager.Startup.ExpireInvalid", false)) {
				String validationError;
				auto sellingId = item->getAuctionedItemObjectID();
				auto sellingItem = zoneServer->getObject(sellingId);

				if (sellingItem == nullptr) {
					validationError = "has null item, deleting";
					auctionMap->deleteItem(vendor, item, true);
				} else if (sellingItem->isNoTrade() || sellingItem->containsNoTradeObjectRecursive()) {
					validationError = "isNoTrade or contains NoTrade items, expiring";
					expireSale(item);
				}

				if (!validationError.isEmpty()) {
					countInvalid++;
					error() << logTag << ": Invalid auction for item " << sellingId << " " << validationError << " auctionItem: " << *item;
					continue;
				}
			}

			if (startupTask && !item->isUpdated()) {
				uint64 sellingId = item->getAuctionedItemObjectID();
				ManagedReference<SceneObject*> sellingItem = zoneServer->getObject(sellingId);

				if (sellingItem != nullptr) {
					if (sellingItem->isFactoryCrate()) {
						Locker clocker(sellingItem, item);
						Reference<FactoryCrate*> crate = sellingItem.castTo<FactoryCrate*>();

						if (crate != nullptr) {
							ManagedReference<TangibleObject*> prototype = crate->getPrototype();

							if (prototype != nullptr) {
								item->setFactoryCrate(true);
								item->setCratedItemType(prototype->getClientGameObjectType());
							}
						}
					} else {
						if (item->isFactoryCrate()) {
							item->setFactoryCrate(false);
						}

						if (item->getCratedItemType() != 0) {
							item->setCratedItemType(0);
						}
					}
				}

				item->setUpdated(true);
				countUpdated++;
			}
		}
	}

	auto elapsed = expireTime.miliDifference() / 1000.0;
	int ps = elapsed > 0 ? countTotal / elapsed : countTotal;

	auto msg = info(true);

	msg << logTag
		<< ": Checked " << countTotal << " auction item(s),"
		<< " updated " << countUpdated << " item(s)"
		;

	if (startupTask && ConfigManager::instance()->getBool("Core3.AuctionManager.Startup.ExpireInvalid", false)) {
		msg << " and found " << countInvalid << " invalid item(s),";
	}

	msg << " in " << int(elapsed) << " second(s) (" << ps << "/s)";
	msg.flush();
}

void AuctionManagerImplementation::addSaleItem(CreatureObject* player, uint64 objectid, SceneObject* vendor, const UnicodeString& description, int price, uint32 duration, bool auction, bool premium) {

	if (vendor == nullptr || (!vendor->isVendor() && !vendor->isBazaarTerminal())) {
		error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Not valid vendor object.";
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::VENDORNOTWORKING);
		player->sendMessage(soldMessage);
		return;
	}

	if (player->isDead() || player->isIncapacitated()) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<TradeSession*> tradeContainer = player->getActiveSession(SessionFacadeType::TRADE).castTo<TradeSession*>();

	if (tradeContainer != nullptr) {
		zoneServer->getPlayerManager()->handleAbortTradeMessage(player);
	}

	ManagedReference<AuctionItem*> oldItem = auctionMap->getItem(objectid);
	ManagedReference<SceneObject*> objectToSell = zoneServer->getObject(objectid);
	String vendorUID = getVendorUID(vendor);
	bool stockroomSale = false;

	if (objectToSell == nullptr || objectToSell->isNoTrade() || objectToSell->containsNoTradeObjectRecursive()) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
		player->sendMessage(soldMessage);

		if (objectToSell != nullptr) {
			player->sendSystemMessage("@container_error_message:container26"); // This item could not be transferred.
		}
		return;
	}

	if(oldItem == nullptr) {
		if (objectToSell == nullptr || !objectToSell->isASubChildOf(player)) {
			if (objectToSell != nullptr)
				error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Selling invalid object.";

			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}
	} else {
		if (oldItem->getStatus() == AuctionItem::DELETED) {
			error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Attempt to sell a DELETED item, auctionItem: " << *oldItem;
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}

		if (oldItem->getStatus() == AuctionItem::RETRIEVED) {
			error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Attempt to sell a RETRIEVED item, auctionItem: " << *oldItem;
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}

		if(oldItem->getStatus() == AuctionItem::FORSALE) {
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::ALREADYFORSALE);
			player->sendMessage(soldMessage);
			return;
		}

		/// Is it being sold from the stockroom
		if (oldItem->getOwnerID() != player->getObjectID()) {
			error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Selling object owned by another player: " << oldItem->getOwnerID();
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}

		stockroomSale = true;

		ManagedReference<SceneObject*> oldVendor = zoneServer->getObject(oldItem->getVendorID());

		if (oldVendor != nullptr && oldVendor->isVendor())
			vendor = oldVendor;
	}

	ManagedReference<Zone*> zone = vendor->getZone();
	if (zone == nullptr) {
		error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): Vendor has null zone?";
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}


	int res = checkSaleItem(player, objectToSell, vendor, price, premium, stockroomSale);

	if (res != 0) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, res);
		player->sendMessage(soldMessage);
		return;
	}

	if (oldItem != nullptr)
		auctionMap->deleteItem(vendor, oldItem);

	if(auctionMap->containsItem(objectToSell->getObjectID())) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::ALREADYFORSALE);
		player->sendMessage(soldMessage);
		return;
	}

	// add city tax to the price
	ManagedReference<CityRegion*> city = vendor->getCityRegion().get();
	if (city != nullptr) {
		price *= (1.0f + (city->getSalesTax() / 100.0f));
	}

	ManagedReference<AuctionItem*> item = createVendorItem(player, objectToSell.get(), vendor, description, price, duration, auction, premium);

	if(item == nullptr) {
		error() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): createVendorItem failed.";
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}

	TransactionLog trx(player, vendor, objectToSell, TrxCode::AUCTIONADDSALE);
	trx.setAutoCommit(false);
	trx.addRelatedObject(item->getAuctionedItemObjectID(), true);
	trx.setExportRelatedObjects(true);

	Locker locker(item);

	int result = auctionMap->addItem(player, vendor, item);

	if(result != ItemSoldMessage::SUCCESS) {
		trx.abort() << "failed to add to auctionMap, result=" << ItemSoldMessage::statusToString(result);
		info() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): " << trx.getErrorMessage() << ", auctionItem: " << *item;
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, result);
		player->sendMessage(soldMessage);
		auctionMap->removeFromCommodityLimit(item);
		return;
	}

	Locker objectToSellLocker(objectToSell);

	objectToSell->destroyObjectFromWorld(true);

	objectToSellLocker.release();

	trx.commit();

	if (vendor->isBazaarTerminal()) {
		StringIdChatParameter str("@base_player:sale_fee"); // The fee for your listing is %DI credits.

		float costReduction = 1;
		if(player->hasSkill("crafting_merchant_sales_01"))
				costReduction = .80f;
		if(player->hasSkill("crafting_merchant_sales_03"))
				costReduction = .60f;

		if (item->isPremiumAuction()) {
			TransactionLog trx(player, TrxCode::BAZAARSYSTEM, costReduction * (SALESFEE * 5), false);
			player->subtractBankCredits(costReduction * (SALESFEE * 5));
			str.setDI(costReduction * (SALESFEE * 5));

		} else {
			TransactionLog trx(player, TrxCode::BAZAARSYSTEM, costReduction * SALESFEE, false);
			player->subtractBankCredits(costReduction * SALESFEE);
			str.setDI(costReduction * SALESFEE);
		}

		player->sendSystemMessage(str);
	}

	if (item->getStatus() == AuctionItem::OFFERED) {

		VendorDataComponent* vendorData = nullptr;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != nullptr && data->get() != nullptr && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if(vendorData != nullptr) {
			ManagedReference<SceneObject*> strongRef = zoneServer->getObject(vendorData->getOwnerId());

			if (strongRef != nullptr && strongRef->isPlayerCreature()) {
				ManagedReference<CreatureObject*> strongOwnerRef = cast<CreatureObject*>(strongRef.get());

				if(strongOwnerRef->isOnline()) {
					strongOwnerRef->sendSystemMessage(player->getFirstName() + " has offered an item to " + vendor->getDisplayedName());
				}
			}
		}
	}

	item->setPersistent(1);

	if(item->isAuction()) {
		Reference<Task*> newTask = new ExpireAuctionTask(_this.getReferenceUnsafeStaticCast(), item);
		newTask->schedule((item->getExpireTime() - time(0)) * 1000);

		Locker locker(&auctionEvents);
		auctionEvents.put(item->getAuctionedItemObjectID(), newTask);
	}

	BaseMessage* msg = new ItemSoldMessage(objectid, ItemSoldMessage::SUCCESS);
	player->sendMessage(msg);

	info() << "addSaleItem(plyer=" << player->getObjectID() << ", objectid=" << objectid << "): SUCCESS, auctionItem: " << *item;
}

String AuctionManagerImplementation::getVendorUID(SceneObject* vendor) {
	if(vendor->getZone() == nullptr) {
		error() << "Vendor missing zone: " << *vendor;
		return "nozone.nozone.sadpandavendor." + String::valueOf(vendor->getObjectID()) + "#0,0";
	}

	String uid = "error.error.errorvendor." + String::valueOf(vendor->getObjectID()) + "#0,0";

	AuctionTerminalDataComponent* terminalData = nullptr;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != nullptr && data->get() != nullptr && data->get()->isAuctionTerminalData())
		terminalData = cast<AuctionTerminalDataComponent*>(data->get());

	if(terminalData != nullptr)
		uid = terminalData->getUID();

	return uid;
}

int AuctionManagerImplementation::checkSaleItem(CreatureObject* player, SceneObject* object, SceneObject* vendor, int price, bool premium, bool stockroomSale) {
	if (vendor == nullptr) {
		error() << "checkSaleItem(player=" << player->getObjectID() << ", object=" << object->getObjectID() << ", vendor=nullptr): Vendor is null";
		return ItemSoldMessage::UNKNOWNERROR;
	}

	if (price < 1)
		return ItemSoldMessage::INVALIDSALEPRICE;

	if (player->getPlayerObject()->getVendorCount() > player->getSkillMod("manage_vendor"))
		return ItemSoldMessage::TOOMANYITEMS;

	auto itemParent = object->getParent().get();

	if (itemParent == nullptr && !stockroomSale) {
		error() << "checkSaleItem(player=" << player->getObjectID() << ", object=" << object->getObjectID() << ", vendor=" << vendor->getObjectID()
				<< "): itemParent is null; stockroomSale=" << stockroomSale;
		return ItemSoldMessage::UNKNOWNERROR;
	}

	if (itemParent != nullptr && !itemParent->checkContainerPermission(player, ContainerPermissions::MOVEOUT)) {
		error() << "checkSaleItem(player=" << player->getObjectID() << ", object=" << object->getObjectID() << ", vendor=" << vendor->getObjectID()
				<< "): No MOVEOUT permission from " << itemParent->getObjectID() << " (" << itemParent->getObjectName()->getFullPath() << ") stockroomSale=" << stockroomSale;
		return ItemSoldMessage::INVALIDITEM;
	}

	if (vendor->isVendor()) {
		VendorDataComponent* vendorData = cast<VendorDataComponent*>(vendor->getDataObjectComponent()->get());

		if (vendorData == nullptr) {
			return ItemSoldMessage::UNKNOWNERROR;
		}

		if (player->getObjectID() == vendorData->getOwnerId()) {
			if (stockroomSale) {
				if (auctionMap->getPlayerItemCount(player) > player->getSkillMod("vendor_item_limit"))
					return ItemSoldMessage::TOOMANYITEMS;
			} else {
				if ((auctionMap->getPlayerItemCount(player) + object->getSizeOnVendorRecursive()) > player->getSkillMod("vendor_item_limit"))
					return ItemSoldMessage::TOOMANYITEMS;
			}
		} else {
			if (auctionMap->getCommodityCount(player) >= MAXSALES)
				return ItemSoldMessage::TOOMANYITEMS;
		}

		if (price > MAXVENDORPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;
	}

	if (vendor->isBazaarTerminal()) {
		if (auctionMap->getCommodityCount(player) >= MAXSALES)
			return ItemSoldMessage::TOOMANYITEMS;

		if (price > MAXBAZAARPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;

		if (player->getBankCredits() < SALESFEE)
			return ItemSoldMessage::NOTENOUGHCREDITS;

		if (premium && player->getBankCredits() < SALESFEE * 5)
			return ItemSoldMessage::NOTENOUGHCREDITS;
	}

	if (object->isIntangibleObject() && !object->isManufactureSchematic())
		return ItemSoldMessage::INVALIDITEM;

	for (int i = 0; i < object->getArrangementDescriptorSize(); ++i) {
		const Vector<String>* descriptors = object->getArrangementDescriptor(i);

		for (int j = 0; j < descriptors->size(); ++j) {
			const String& descriptor = descriptors->get(j);

			if (descriptor == "inventory" || descriptor == "datapad" || descriptor == "default_weapon"
					|| descriptor == "mission_bag" || descriptor == "ghost" || descriptor == "bank" || descriptor == "hair")
				return ItemSoldMessage::INVALIDITEM;
		}
	}

	return ItemSoldMessage::SUCCESS;
}

AuctionItem* AuctionManagerImplementation::createVendorItem(CreatureObject* player, SceneObject* objectToSell, SceneObject* vendor, const UnicodeString& description, int price, unsigned int duration, bool auction, bool premium) {

	Zone* zone = vendor->getZone();

	if (zone == nullptr)
		return nullptr;

	uint64 vendorExpire = time(0) + AuctionManager::VENDOREXPIREPERIOD;
	uint64 commodityExpire = time(0) + AuctionManager::COMMODITYEXPIREPERIOD;

	String playername = player->getFirstName().toLowerCase();
	String descr = description.toString();
	String planetStr = zone->getZoneName();

	AuctionItem* item  = new AuctionItem(objectToSell->getObjectID());

	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion().get();
	String region = "@planet_n:" + planetStr;

	if (cityRegion != nullptr)
		region = cityRegion->getRegionName();

	String name = objectToSell->getDisplayedName();

	Locker locker(item);

	item->setVendorUID(getVendorUID(vendor));
	item->setOnBazaar(vendor->isBazaarTerminal());

	if (premium)
		item->setAuctionPremium();

	item->setVendorID(vendor->getObjectID());
	item->setItemName(name);
	item->setItemDescription(description.toString());

	if (objectToSell->isFactoryCrate()) {
		ManagedReference<FactoryCrate*> crate = cast<FactoryCrate*>(objectToSell);

		if (crate != nullptr) {
			ManagedReference<TangibleObject*> prototype = crate->getPrototype();

			if (prototype != nullptr) {
				item->setFactoryCrate(true);
				item->setCratedItemType(prototype->getClientGameObjectType());
				item->setUpdated(true);
			}
		}
	}

	item->setItemType(objectToSell->getClientGameObjectType());
	item->setPrice(price);
	item->setAuction(auction);
	item->setStatus(AuctionItem::FORSALE);
	item->setBuyerID(0);
	item->setBidderName("");
	item->setSize(objectToSell->getSizeOnVendorRecursive());

	VendorDataComponent* vendorData = nullptr;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != nullptr && data->get() != nullptr && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());

	if (!vendor->isBazaarTerminal()) {
		if(vendorData == nullptr)
			return nullptr;

		// Someone else's Vendor (making this sell item an offer)
		if(vendorData->getOwnershipRightsOf(player) == 1) {
			item->setStatus(AuctionItem::OFFERED);
			item->setOfferToID(vendorData->getOwnerId());
			item->setExpireTime(commodityExpire);
		} else {
			item->setExpireTime(vendorExpire);

			if(auctionMap->getVendorItemCount(vendor, true) == 0)
				sendVendorUpdateMail(vendor, false);
		}
	} else {
		item->setExpireTime(commodityExpire);
	}

	ObjectManager::instance()->persistObject(item, 0, "auctionitems");
	updateAuctionOwner(item, player);

	return item;
}

int AuctionManagerImplementation::checkBidAuction(CreatureObject* player, AuctionItem* item, int price1, int price2) {
	if ((price1 > MAXBAZAARPRICE || price2 > MAXBAZAARPRICE) && item->isOnBazaar()) {
		return BidAuctionResponseMessage::PRICEOVERFLOW;
	}

	if (price1 < 1 || price2 < 1 || price1 < item->getPrice()) {
		return BidAuctionResponseMessage::INVALIDPRICE;
	}

	if (player->getBankCredits() < price1) { // Credit Check
		return BidAuctionResponseMessage::NOTENOUGHCREDITS;
	}

	return 0;
}

void AuctionManagerImplementation::doInstantBuy(CreatureObject* player, AuctionItem* item) {
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

	if (vendor == nullptr)
		return;

	int tax = 0;
	ManagedReference<CityRegion*> city = nullptr;
	String vendorPlanetName("@planet_n:" + vendor->getZone()->getZoneName());
	String vendorRegionName = vendorPlanetName;

	city = vendor->getCityRegion().get();

	if( city != nullptr) {
		tax = item->getPrice() - ( item->getPrice() / ( 1.0f + (city->getSalesTax() / 100.f)));
		vendorRegionName = city->getRegionName();
	}

	String playername = player->getFirstName().toLowerCase();

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

	String sender = "auctioner";
	String sellerName = item->getOwnerName();

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;


	Locker locker(item);

	if(item->isOnBazaar() || item->getStatus() == AuctionItem::OFFERED)
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	updateAuctionOwner(item, player);

	item->setStatus(AuctionItem::SOLD);
	item->setExpireTime(availableTime);
	item->setBuyerID(player->getObjectID());
	item->setBidderName(playername);
	item->clearAuctionWithdraw();

	TransactionLog trx(player, seller, TrxCode::INSTANTBUY, item->getPrice(), false);
	trx.setAutoCommit(false);
	trx.addRelatedObject(item->getAuctionedItemObjectID(), true);
	trx.setExportRelatedObjects(true);
	player->subtractBankCredits(item->getPrice());

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);

	// Waypoint to Vendor / bazaar
	float waypointX = vendor->getWorldPositionX();
	float waypointY = vendor->getWorldPositionY();

	WaypointChatParameter waypointParam;
	waypointParam.set(vendor->getDisplayedName(), waypointX, 0, waypointY, vendor->getPlanetCRC());

	String itemName = removeColorCodes(item->getItemName());

	if (!item->isOnBazaar()) {
		//Setup the mail to the vendor owner

		PlayerManager* pman = zoneServer->getPlayerManager();
		/*ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

		Locker _locker(seller);*/

		StringIdChatParameterVector sellerBodyVector;
		WaypointChatParameterVector sellerWaypointVector;

		UnicodeString sellerSubject("@auction:subject_vendor_seller"); // Vendor Sale Complete
		StringIdChatParameter sellerBodySale("@auction:seller_success_vendor"); // %TU has sold %TO to %TT for %DI credits.
		sellerBodySale.setTU(vendor->getDisplayedName());
		sellerBodySale.setTO(itemName);
		sellerBodySale.setTT(item->getBidderName());
		sellerBodySale.setDI(item->getPrice());

		StringIdChatParameter sellerBodyLoc("@auction:seller_success_location"); // The sale took place at %TT, on %TO.
		sellerBodyLoc.setTO(vendorPlanetName);
		sellerBodyLoc.setTT(vendorRegionName);

		sellerBodyVector.add(sellerBodySale);
		sellerBodyVector.add(sellerBodyLoc);

		sellerWaypointVector.add(waypointParam);

		//Setup the mail to the buyer
		/*ManagedReference<CreatureObject*> buyer = pman->getPlayer(item->getBidderName());

		Locker _locker2(buyer);*/

		StringIdChatParameterVector buyerBodyVector;
		WaypointChatParameterVector buyerWaypointVector;

		UnicodeString buyerSubject("@auction:subject_vendor_buyer"); // Vendor Item Purchased
		StringIdChatParameter buyerBodySale("@auction:buyer_success"); // You have won the auction of "%TO" from "%TT" for %DI credits. See the attached waypoint for location.
		buyerBodySale.setTO(itemName);
		buyerBodySale.setTT(sellerName);
		buyerBodySale.setDI(item->getPrice());

		StringIdChatParameter buyerBodyLoc("@auction:buyer_success_location"); // The sale took place at %TT, on %TO.
		buyerBodyLoc.setTO(vendorPlanetName);
		buyerBodyLoc.setTT(vendorRegionName);

		buyerBodyVector.add(buyerBodySale);
		buyerBodyVector.add(buyerBodyLoc);

		buyerWaypointVector.add(waypointParam);

		//Send the Mail
		locker.release();
		UnicodeString blankBody;
		cman->sendMail(sender, sellerSubject, blankBody, sellerName, &sellerBodyVector, &sellerWaypointVector);
		cman->sendMail(sender, buyerSubject, blankBody, item->getBidderName(), &buyerBodyVector, &buyerWaypointVector);

		if(auctionMap->getVendorItemCount(vendor, true) == 0)
			sendVendorUpdateMail(vendor, true);

	} else {

		StringIdChatParameterVector sellerBodyVector;
		WaypointChatParameterVector sellerWaypointVector;

		// Setup the mail to the seller
		UnicodeString sellerSubject("@auction:subject_instant_seller"); // Instant Sale Complete
		StringIdChatParameter sellerBodySale("@auction:seller_success"); // Your auction of %TO has been sold to %TT for %DI credits
		sellerBodySale.setTO(itemName);
		sellerBodySale.setTT(item->getBidderName());
		sellerBodySale.setDI(item->getPrice());

		StringIdChatParameter sellerBodyLoc("@auction:seller_success_location"); // The sale took place at %TT, on %TO.
		sellerBodyLoc.setTO(vendorPlanetName);
		sellerBodyLoc.setTT(vendorRegionName);

		sellerBodyVector.add(sellerBodySale);
		sellerBodyVector.add(sellerBodyLoc);

		sellerWaypointVector.add(waypointParam);

		// Setup the mail to the buyer
		StringIdChatParameterVector buyerBodyVector;
		WaypointChatParameterVector buyerWaypointVector;

		UnicodeString buyerSubject("@auction:subject_instant_buyer"); // Instant Sale Item Purchased
		StringIdChatParameter buyerBodySale("@auction:buyer_success"); // You have won the auction of "%TO" from "%TT" for %DI credits. See the attached waypoint for location.
		buyerBodySale.setTO(itemName);
		buyerBodySale.setTT(sellerName);
		buyerBodySale.setDI(item->getPrice());

		StringIdChatParameter buyerBodyLoc("@auction:buyer_success_location"); // The sale took place at %TT, on %TO.
		buyerBodyLoc.setTO(vendorPlanetName);
		buyerBodyLoc.setTT(vendorRegionName);

		buyerBodyVector.add(buyerBodySale);
		buyerBodyVector.add(buyerBodyLoc);

		locker.release();

		buyerWaypointVector.add(waypointParam);

		//Send the Mail
		UnicodeString blankBody;
		cman->sendMail(sender, sellerSubject, blankBody, sellerName, &sellerBodyVector, &sellerWaypointVector);
		cman->sendMail(sender, buyerSubject, blankBody, item->getBidderName(), &buyerBodyVector, &buyerWaypointVector);

	}

	if (seller == nullptr) {
		// doInstantBuy(CreatureObject* player, AuctionItem* item)
		trx.errorMessage() << "Null Seller: " + item->getOwnerName();
		trx.commit();
		error("seller null for name " + item->getOwnerName());

		error() << "doInstantBuy(player=" << player->getObjectID() << ", item=" << item->getObjectID() << "): Seller not found [" << item->getOwnerName() << "], auctionItem: " << *item;
		return;
	}

	locker.release();

	Locker slocker(seller);
	seller->addBankCredits(item->getPrice());
	trx.commit();

	if (city != nullptr && tax > 0) {
		TransactionLog trxFee(seller, TrxCode::CITYSALESTAX, tax, false);
		trxFee.groupWith(trx);
		trxFee.addState("cityRegionID", city->getObjectID());
		seller->subtractBankCredits(tax);
	}
	slocker.release();

	if(city != nullptr && !city->isClientRegion() && tax){
		Locker clock(city);
		city->addToCityTreasury(tax);
	}

}

void AuctionManagerImplementation::doAuctionBid(CreatureObject* player, AuctionItem* item, int price1, int proxyBid) {

	if(price1 <= item->getPrice() || proxyBid <= price1) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 1);
		player->sendMessage(msg);
		return;
	}

	String playername = player->getFirstName().toLowerCase();

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	// don't allow owner bid on the item.  don't allow old auction info
	// send auctioner invalid message
	if (playername == item->getOwnerName() || price1 <= item->getPrice() || proxyBid <= price1) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 1);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<CreatureObject*> priorBidder = pman->getPlayer(item->getBidderName());

	/// Use previous proxy
	if(priorBidder != nullptr && proxyBid < item->getProxy()) {
		Locker locker(item);
		Locker plocker(priorBidder);

		int increase = price1 - item->getPrice();

		int fullPrice = proxyBid + increase - item->getPrice();

		//TODO: prior didnt have enough money -> assert.. fix properly
		if (priorBidder->getBankCredits() < fullPrice) {
			BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::NOTENOUGHCREDITS);
			player->sendMessage(msg);

			return;
		}

		TransactionLog trx(priorBidder, TrxCode::AUCTIONBID, fullPrice, false);
		priorBidder->subtractBankCredits(fullPrice);
		item->setPrice(proxyBid + increase);
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::SUCCEDED);
		player->sendMessage(msg);

		if(priorBidder != player) {
			StringIdChatParameter body("@auction:bidder_outbid");
			body.setTO(item->getItemName());
			priorBidder->sendSystemMessage(body);
		}

		return;
	}

	Locker locker(item);
	Locker plocker(player);

	if (player->getBankCredits() < price1 ||
			player->getBankCredits() < item->getPrice()) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::NOTENOUGHCREDITS);
		player->sendMessage(msg);

		return;
	}

	item->setProxy(proxyBid);

	// send prior bidder their money back
	if (item->getBidderName().length() > 0) {

		String itemName = removeColorCodes(item->getItemName());

		StringIdChatParameter bidderBody("@auction:bidder_outbid"); // You have been outbid on the "%TO" that you were bidding on.
		bidderBody.setTO(itemName);

		// mail prior bidder with outcome
		UnicodeString bidderSubject("@auction:subject_auction_outbid"); // Auction Outbid

		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		// take money from high bidder
		TransactionLog trx(player, TrxCode::AUCTIONBID, item->getPrice(), false);
		player->subtractBankCredits(item->getPrice());

		if (priorBidder != nullptr) {
			Locker clocker(priorBidder, player);

			if (priorBidder != player)
				priorBidder->sendSystemMessage(bidderBody);

			TransactionLog trx(TrxCode::AUCTIONBID, priorBidder, item->getPrice(), false);
			priorBidder->addBankCredits(item->getPrice());
		}

		plocker.release();
		locker.release();

		String sender = "auctioner";
		cman->sendMail(sender, bidderSubject, bidderBody, item->getBidderName());

		// no prior bidder, just take the money
	} else {
		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		TransactionLog trx(player, TrxCode::AUCTIONBID, item->getPrice(), false);
		player->subtractBankCredits(item->getPrice());
	}

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::buyItem(CreatureObject* player, uint64 objectid, int price1, int price2) {
	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectid);

	if (item == nullptr) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

	if (vendor == nullptr || item->getStatus() == AuctionItem::SOLD) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	if (item->getOwnerID() == player->getObjectID()) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::PURCHASEFAILED);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<CityRegion*> city = vendor->getCityRegion().get();

	int totalPrice = item->getPrice();

	int res = checkBidAuction(player, item, totalPrice , price2);

	if (res != 0) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	if (!item->isAuction()) { // Instant buy
		doInstantBuy(player, item);
	} else { // For Auction Bids
		if (price1 < 1) {
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDPRICE);
			player->sendMessage(msg);

			return;
		}

		doAuctionBid(player, item, price1, price2);
	}
}

int AuctionManagerImplementation::checkRetrieve(CreatureObject* player, uint64 objectIdToRetrieve, SceneObject* vendor) {
    // Check both Bazaar and Vendors

	if (!auctionMap->containsItem(objectIdToRetrieve))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	ManagedReference<SceneObject*> saleItem = zoneServer->getObject(objectIdToRetrieve);

	if (saleItem == nullptr) {
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectIdToRetrieve);
	if (item == nullptr || item->getStatus() == AuctionItem::RETRIEVED) {
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	if(item->isAuction() && item->getStatus() == AuctionItem::FORSALE)
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	int size = item->getSize();
	if(saleItem->isIntangibleObject()) {
		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");
		if (datapad->getCountableObjectsRecursive() + size > datapad->getContainerVolumeLimit())
			return RetrieveAuctionItemResponseMessage::FULLINVENTORY;
	} else {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory->getCountableObjectsRecursive() + size > inventory->getContainerVolumeLimit())
			return RetrieveAuctionItemResponseMessage::FULLINVENTORY;
	}

	/*
	if(item->getStatus() == AuctionItem::SOLD && player->getObjectID() == item->getOwnerID()) {
		item->setStatus(AuctionItem::EXPIRED);
		return RetrieveAuctionItemResponseMessage::DONTRETRIEVE;
	}
	*/

	String playername = player->getFirstName();

	// only the owner can yank his own auction off the vendor
	if (item->getStatus() != AuctionItem::SOLD && (player->getObjectID() != item->getOwnerID()))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	// the bidder is the only one who can get his auction after expiration
	if (item->getStatus() == AuctionItem::SOLD && item->getBuyerID() != player->getObjectID()) {
		player->sendSystemMessage(item->getBidderName() + " bought this, " + player->getFirstName() + " trying to retrieve");
		error(item->getBidderName() + " bought this, " + player->getFirstName() + " trying to retrieve");
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	if(vendor->isVendor() && !vendor->isInRange(player, 8.0f))
		return RetrieveAuctionItemResponseMessage::TOOFAR;


	if (vendor->isBazaarTerminal()) {
		ManagedReference<CityRegion*> region = vendor->getCityRegion().get();

		String location = vendor->getZone()->getZoneName() + ".";

		if (region != nullptr) {
			location += region->getRegionName();
			//String region = terminal->getBazaarRegion();

			if (!item->getVendorUID().beginsWith(location)) {
				return RetrieveAuctionItemResponseMessage::TOOFAR;
			}
		} else {
			StringBuffer msg;
			msg << "null area for bazaar terminal at" << vendor->getPositionX() << " " << vendor->getPositionY() << " zone " << vendor->getZone()->getZoneName();
			error(msg);
		}

		if (!item->getVendorUID().beginsWith(location)) {
			return RetrieveAuctionItemResponseMessage::TOOFAR;
		}
	}

	return 0;
}

void AuctionManagerImplementation::refundAuction(AuctionItem* item) {
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> bidder = pman->getPlayer(item->getBidderName());
	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	String itemName = removeColorCodes(item->getItemName());

	// send the player a mail and system message
	UnicodeString buyerSubject("@auction:subject_auction_cancelled"); // Auction Cancelled
	Reference<StringIdChatParameter*> buyerBody = new StringIdChatParameter("auction", "buyer_canceled"); // The auction of "%TO" that you were bidding on has been canceled by %TT.
	buyerBody->setTO(itemName);
	buyerBody->setTT(item->getOwnerName());

	if (bidder != nullptr) {
		int itemPrice = item->getPrice();

		Core::getTaskManager()->executeTask([=] () {
			Locker locker(bidder);

			TransactionLog trx(TrxCode::AUCTIONBID, bidder, itemPrice, false);
			bidder->addBankCredits(itemPrice);
			bidder->sendSystemMessage(*(buyerBody.get()));
		}, "RefundAuctionLambda");
	}

	String sender = "auctioner";
	cman->sendMail(sender, buyerSubject, *(buyerBody.get()), item->getBidderName());
}

void AuctionManagerImplementation::retrieveItem(CreatureObject* player, uint64 objectid, uint64 vendorID) {

	ManagedReference<SceneObject*> vendor = zoneServer->getObject(vendorID);
	RetrieveAuctionItemResponseMessage* msg = nullptr;

	// check for valid vendor terminal
	if ((vendor == nullptr || !vendor->isVendor()) && !vendor->isBazaarTerminal()) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
		return;
	}

	int res = checkRetrieve(player, objectid, vendor);

	if (res != 0) {
		if(res != RetrieveAuctionItemResponseMessage::TOOFAR) {
			if(res == RetrieveAuctionItemResponseMessage::DONTRETRIEVE)
				res = 0;
			msg = new RetrieveAuctionItemResponseMessage(objectid, res);
			player->sendMessage(msg);
		}
		return;
	}

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectid);
	if (item == nullptr) {
		error() << "retrieveItem(player=" << player->getObjectID() << ", objectid=" << objectid << ", vendorID=" << vendorID << "): Item not found in auctionMap";
		return;
	}

	ManagedReference<SceneObject*> objectToRetrieve = zoneServer->getObject(objectid);

	if (objectToRetrieve == nullptr) {
		error() << "retrieveItem(player=" << player->getObjectID() << ", objectid=" << objectid << ", vendorID=" << vendorID << "): invalid object.";
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	Locker locker(item);
	Locker plocker(player);

	ManagedReference<SceneObject*> destination = nullptr;

	if(objectToRetrieve->isIntangibleObject())
		destination = player->getSlottedObject("datapad");
	else
		destination = player->getSlottedObject("inventory");

	TransactionLog trx(vendor, player, objectToRetrieve, TrxCode::AUCTIONRETRIEVE);
	trx.addRelatedObject(objectid, true);
	trx.setExportRelatedObjects(true);

	if(destination->transferObject(objectToRetrieve, -1, false)) {
		trx.commit();
		destination->broadcastObject(objectToRetrieve, true);

		item->setStatus(AuctionItem::RETRIEVED);

		auctionMap->deleteItem(vendor, item);
		auctionMap->removeFromCommodityLimit(item);

		item->setAuctionedItemObjectID(0);

		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
	} else {
		trx.abort() << "transferObject failed";
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
	}
}

bool AuctionManagerImplementation::checkItemCategory(int category, AuctionItem* item) {
	int itemType = item->getItemType();
	bool isCrate = item->isFactoryCrate();
	int cratedItemType = item->getCratedItemType();

	if (category & 255) { // Searching a sub category
		if (itemType == category || (isCrate && cratedItemType > 0 && cratedItemType == category)) {
			return true;
		}
	} else if ((itemType & category) || (isCrate && cratedItemType > 0 && (cratedItemType & category))) { // Searching main category
		return true;
	} else if ((category == 8192) && (itemType < 256 || (isCrate && cratedItemType < 256))) {
		return true;
	} else if (category == 0) { // Searching all items
		return true;
	}

	return false;
}
AuctionQueryHeadersResponseMessage* AuctionManagerImplementation::fillAuctionQueryHeadersResponseMessage(CreatureObject* player, SceneObject* vendor, TerminalListVector* terminalList, int searchType, uint32 itemCategory, const UnicodeString& filterText, int minPrice, int maxPrice, bool includeEntranceFee, int clientCounter, int offset) {
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(searchType, clientCounter, player);

	String pname = player->getFirstName().toLowerCase();
	uint32 now = time(0);
	int displaying = 0;
	/*System::out << "Screen =" + String::valueOf(screen) << endl;
	System::out << "Category =" + String::valueOf(category) << endl;
	System::out << "VendorItemSize =" + String::valueOf(auctionMap->getVendorItemCount()) << endl;
	System::out << "AuctionItemSize =" + String::valueOf(auctionMap->getAuctionCount()) << endl;
	System::out << "______________________________" << endl;*/

	if (!isMarketEnabled()) {
		player->sendSystemMessage("@ui_auc:err_vendor_terminal_error"); // This market is unavailable.
		reply->createMessage(offset, true);
		return reply;
	}

	for (int j = 0; (j < terminalList->size()) && (displaying < (offset + 100)); ++j) {

		auto& items = terminalList->get(j);

		if(items == nullptr)
			continue;

		/// Exclude non-searchable vendor Items
		if(vendor->isBazaarTerminal() && searchType == ST_VENDOR_SELLING && !items->isSearchable())
			continue;

		try {
			items->rlock();

			for (int i = 0; (i < items->size()) && (displaying < (offset + 100)); i++) {
				ManagedReference<AuctionItem*>& item = items->get(i);

				if(item == nullptr)
					continue;

				if (item->getStatus() == AuctionItem::DELETED || item->getStatus() == AuctionItem::RETRIEVED) {
					info() << "fillAuctionQueryHeadersResponseMessage(): Skipping " << item->getStatusString() << " auctionItem: " << *item;
					continue;
				}

				if(!item->isAuction() && item->getExpireTime() <= now) {
					Core::getTaskManager()->executeTask([=] () {
						expireSale(item);
					}, "ExpireSaleLambda");

					continue;
				}

				switch(searchType) {
				case ST_VENDOR_SELLING: // Vendor search Bazaar && Vendor

					if(vendor->isVendor() && item->getVendorID() != vendor->getObjectID()) {
						if(item->getOwnerID() != player->getObjectID())
							continue;
					}
				case ST_ALL: // All Auctions (Bazaar)
					if (item->getStatus() == AuctionItem::FORSALE) {
						if (!checkItemCategory(itemCategory, item))
							continue;

						if (minPrice != 0 || maxPrice != 0) {
							int itemPrice = item->getPrice();

							if (includeEntranceFee) {
								ManagedReference<SceneObject*> itemVendor = player->getZoneServer()->getObject(item->getVendorID());

								if (itemVendor != nullptr && itemVendor->isVendor()) {
									int accessFee = 0;
									ManagedReference<SceneObject*> parent = itemVendor->getRootParent();

									if(parent != nullptr && parent->isBuildingObject()) {
										BuildingObject* building = cast<BuildingObject*>(parent.get());

										if(building != nullptr)
											accessFee = building->getAccessFee();
									}

									itemPrice += accessFee;
								}
							}

							if ((minPrice != 0 && itemPrice < minPrice) || (maxPrice != 0 && itemPrice > maxPrice))
								continue;
						}

						if (!filterText.isEmpty()) {
							String lowerFilter = filterText.toString().toLowerCase();
							String itemName = item->getItemName().toLowerCase();

							if (itemName.indexOf(lowerFilter) == -1)
								continue;
						}


						if (displaying >= offset) {
							reply->addItemToList(item);
						}

						displaying++;
					}
					break;
				case ST_PLAYER_SALES: // My auctions/sales
					if (item->getStatus() == AuctionItem::FORSALE && (item->getOwnerID() == player->getObjectID())) {
						if(checkItemCategory(itemCategory, item)) {
							if (displaying >= offset) {
								reply->addItemToList(item);
							}

							displaying++;
						}
					}
					break;
				case ST_PLAYER_BIDS: // My Bids
					if (item->isAuction() && item->getStatus() == AuctionItem::FORSALE && (item->getBidderName() == pname)) {
						reply->addItemToList(item);
					}
					break;
				case ST_PLAYER_STOCKROOM: // Retrieve items screen
					if ((item->getStatus() == AuctionItem::SOLD && item->getBuyerID() == player->getObjectID()) ||
							(item->getStatus() == AuctionItem::EXPIRED && item->getOwnerID() == player->getObjectID())) {
						reply->addItemToList(item);
					}
					break;
				case ST_VENDOR_OFFERS: // Offers to Vendor (vendor owner)
					if (item->getStatus() == AuctionItem::OFFERED && item->getOfferToID() == player->getObjectID()) {
						if(checkItemCategory(itemCategory, item)) {
							if (displaying >= offset) {
								reply->addItemToList(item);
							}

							displaying++;
						}
					}
					break;
				case ST_VENDOR_STOCKROOM: // Stockroom
					if ((item->getStatus() == AuctionItem::EXPIRED && item->getOwnerID() == player->getObjectID()) ||
							(item->getStatus() == AuctionItem::SOLD && item->getBuyerID() == player->getObjectID())) {
						if(checkItemCategory(itemCategory, item)) {
							if (displaying >= offset) {
								reply->addItemToList(item);
							}

							displaying++;
						}
					}
					break;
				case ST_PLAYER_OFFERS_TO_VENDOR: // Offers to vendor (browsing player)
					if (item->getStatus() == AuctionItem::OFFERED && item->getOwnerID() == player->getObjectID()) {
						if(checkItemCategory(itemCategory, item)) {
							if (displaying >= offset) {
								reply->addItemToList(item);
							}

							displaying++;
						}
					}
					break;
				}
			}
			items->runlock();
		} catch(Exception& e) {
			error(e.getMessage());
			items->runlock();
		}
	}

	if (displaying == (offset + 100))
		reply->createMessage(offset, true);
	else
		reply->createMessage(offset);

	return reply;
}

void AuctionManagerImplementation::getData(CreatureObject* player, int locationType, uint64 vendorObjectID, int searchType, unsigned int itemCategory, const UnicodeString& filterText, int minPrice, int maxPrice, bool includeEntranceFee, int clientCounter, int offset) {
	auto errorMessage = [=] () -> LoggerHelper {
		auto msg = error();

		msg << "getData(player=" << player->getObjectID()
			<< ", locationType=" << locationType
			<< ", vendor=" << vendorObjectID
			<< ", searchType=" << searchType
			<< ", itemCategory=" << itemCategory
			<< ", filterText=[" << filterText << "]"
			<< ", minPrice=" << minPrice
			<< ", maxPrice=" << maxPrice
			<< ", includeEntranceFee=" << includeEntranceFee
			<< ", clientCounter=" << clientCounter
			<< ", offset=" << offset
			<< "): ";

		return msg;
	};

	if (player->getAuctionSearchTask().get() != nullptr)
		return;

	ManagedReference<TangibleObject*> vendorInUse = (zoneServer->getObject(vendorObjectID)).castTo<TangibleObject*>();

	if (vendorInUse == nullptr || (!vendorInUse->isVendor() && !vendorInUse->isBazaarTerminal())) {
		errorMessage() << "Vendor not found.";
		return;
	}

	ManagedReference<SceneObject*> parent = vendorInUse->getRootParent();

	if (parent != nullptr && parent != player->getRootParent())
		return;

	if(player->getZone() == nullptr) {
		errorMessage() << "Player not in a zone.";
		return;
	}

	ManagedReference<BuildingObject*> rootParent = cast<BuildingObject*>(parent.get());
	if(rootParent != nullptr && !rootParent->isAllowedEntry(player))
		return;

	//Handle Merchant XP for players using other players vendors...
	if (!vendorInUse->isBazaarTerminal()) {

		DataObjectComponentReference* data = vendorInUse->getDataObjectComponent();
		if(data == nullptr || data->get() == nullptr || !data->get()->isVendorData()) {
			errorMessage() << "Vendor has no data component.";
			return;
		}

		VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
		if(vendorData == nullptr) {
			errorMessage() << "Vendor has wrong data component.";
			return;
		}

		vendorData->awardUseXP();
	}

	String planet = "";
	String region = "";
	ManagedReference<SceneObject*> vendor = nullptr;
	ManagedReference<CityRegion*> city = nullptr;

	switch (locationType) {
	case LT_MARKET:
		vendor = vendorInUse;
	case LT_REGION:
		city = player->getCityRegion().get();
		if (city != nullptr)
			region = city->getRegionName();
		else {
			region = "@planet_n:" + player->getZone()->getZoneName();
			vendor = vendorInUse;
		}
	case LT_PLANET:
		planet = player->getZone()->getZoneName();
	default:
		break;
	}

	AuctionSearchTask* task = new AuctionSearchTask(_this.getReferenceUnsafeStaticCast(), player, vendorInUse, planet, region, vendor, searchType, itemCategory, filterText, minPrice, maxPrice, includeEntranceFee, clientCounter, offset);
	player->setAuctionSearchTask(task);
	task->schedule(100);
}

void AuctionManagerImplementation::getAuctionData(CreatureObject* player, SceneObject* usedVendor, const String& planet, const String& region, SceneObject* vendor, int searchType, uint32 itemCategory, const UnicodeString& filterText, int minPrice, int maxPrice, bool includeEntranceFee, int clientCounter, int offset) {
	TerminalListVector terminalList;

	if (usedVendor->isBazaarTerminal() && searchType != ST_VENDOR_SELLING) { // This is to prevent bazaar items from showing on Vendor Search
		terminalList = auctionMap->getBazaarTerminalData(planet, region, vendor);
	} else {
		terminalList = auctionMap->getVendorTerminalData(planet, region, vendor);
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, usedVendor, &terminalList, searchType, itemCategory, filterText, minPrice, maxPrice, includeEntranceFee, clientCounter, offset);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::getItemAttributes(CreatureObject* player, uint64 objectid) {
	Reference<AuctionItem*> auctionItem = auctionMap->getItem(objectid);

	if (auctionItem == nullptr)
		return;

	Reference<SceneObject*> object = zoneServer->getObject(auctionItem->getAuctionedItemObjectID());

	if (object == nullptr) {
		error() << "getItemAttributes(player=" << player->getObjectID() << ", objectid=" << objectid << ") getObject failed.";
		return;
	}

	UnicodeString description(auctionItem->getItemDescription());
	AttributeListMessage* msg = new AttributeListMessage(objectid, description);

	// For objects that don't fill the attribute list normally...
	if (object->getAttributeListComponent() != nullptr) {
		object->getAttributeListComponent()->fillAttributeList(msg, player, object);
	} else
		object->fillAttributeList(msg, player);

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost != nullptr && ghost->isPrivileged()) {
		msg->insertAttribute("Auction OID", String::valueOf(auctionItem->getObjectID()));
		msg->insertAttribute("Item Type", auctionItem->getItemType());
		bool isCrate = auctionItem->isFactoryCrate();
		msg->insertAttribute("Is Factory Crate:", isCrate);

		if (isCrate) {
			msg->insertAttribute("Crated Item Type:", auctionItem->getCratedItemType());
		}
	}

	//msg->insertInt(0);
	String templateFile = TemplateManager::instance()->getTemplateFile(object->getClientObjectCRC());
	msg->insertAscii(templateFile);

	String cust = "";
	if(object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object.get());
		if(tano != nullptr)
			tano->getCustomizationString(cust);
	}

	msg->insertAscii(cust);

	player->sendMessage(msg);
}

void AuctionManagerImplementation::cancelItem(CreatureObject* player, uint64 objectID) {

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectID);

	// Item wasnt found. it doesn't exist
	if (item == nullptr) {
		error() << "cancelItem(player=" << player->getObjectID() << ", objectID=" << objectID << "): Item not found in auctionMap.";
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;
	bool forSaleOnVendor = false;

	if (item->getStatus() == AuctionItem::FORSALE) {
		if(item->getOwnerID() != player->getObjectID()) {
			error() << "cancelItem(player=" << player->getObjectID() << ", objectID=" << objectID << "): Not owner of item, owner: " << item->getOwnerID();
			BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::NOTOWNER);
			player->sendMessage(msg);
			return;
		}

		if(item->isOnBazaar())
			availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
		else {
			availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;
			forSaleOnVendor = true;
		}

	} else if (item->getStatus() == AuctionItem::OFFERED) {
		if(item->getOfferToID() != player->getObjectID() &&
				item->getOwnerID() != player->getObjectID()) {
			error() << "cancelItem(player=" << player->getObjectID() << ", objectID=" << objectID << "): Not the target of offer, auctionItem: " << *item;
			BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::INVALIDITEM);
			player->sendMessage(msg);
			return;
		}
		/// 7 Days
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;

	} else {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	if (item->getExpireTime() <= 0) {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	// refund auction money
	if (item->isAuction()) {
		refundAuction(item);
		Locker locker(&auctionEvents);

		if(auctionEvents.contains(item->getAuctionedItemObjectID())) {
			Reference<Task*> newTask = auctionEvents.get(item->getAuctionedItemObjectID());

			if(newTask != nullptr)
				newTask->cancel();

			auctionEvents.drop(item->getAuctionedItemObjectID());
		}
	}

	/// If the offeree cancels
	if(item->getStatus() == AuctionItem::OFFERED && item->getOfferToID() == player->getObjectID()) {

		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

		if(vendor != nullptr) {
			ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
			String sender = "auctioner";

			// Waypoint to Vendor / bazaar
			float waypointX = vendor->getWorldPositionX();
			float waypointY = vendor->getWorldPositionY();

			ManagedReference<WaypointObject*> waypoint = zoneServer->createObject(0xc456e788, 0).castTo<WaypointObject*>();
			Locker waypointLocker(waypoint);
			waypoint->setPlanetCRC(vendor->getPlanetCRC());
			waypoint->setPosition(waypointX, 0, waypointY);

			waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

			String itemName = removeColorCodes(item->getItemName());

			UnicodeString sellerSubject("@auction:subject_auction_unsuccessful"); // Auction Unsuccessful
			StringIdChatParameter sellerBody("@auction:seller_fail"); // Your auction of %TO has been completed and has not been purchased.
			sellerBody.setTO(itemName);

			//Send the Mail
			cman->sendMail(sender, sellerSubject, sellerBody, item->getOwnerName(), waypoint);
		}
	}

	Locker locker(item);

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, 0);
	player->sendMessage(msg);

	if(forSaleOnVendor) {
		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

		if(vendor != nullptr && auctionMap->getVendorItemCount(vendor, true) == 0)
			sendVendorUpdateMail(vendor, true);
	}
}

void AuctionManagerImplementation::expireSale(AuctionItem* item) {
	Locker locker(item);

	if(item->getStatus() == AuctionItem::EXPIRED) {
		deleteExpiredSale(item);
		return;
	}

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	String itemName = removeColorCodes(item->getItemName());

	//Send the mail to the vendor owner
	String sender = "auctioner";

	UnicodeString sellerSubject("@auction:subject_auction_unsuccessful"); // Auction Unsuccessful

	StringIdChatParameter sellerBody("@auction:seller_fail"); // Your auction of %TO has been completed and has not been purchased.
	sellerBody.setTO(itemName);

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;

	if(item->isOnBazaar())
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	locker.release();

	cman->sendMail(sender, sellerSubject, sellerBody, item->getOwnerName());

	if (!item->isOnBazaar()) {
		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

		if(vendor != nullptr && auctionMap->getVendorItemCount(vendor, true) == 0)
			sendVendorUpdateMail(vendor, true);
	}
}

void AuctionManagerImplementation::expireBidAuction(AuctionItem* item) {

	Locker locker(item);

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	String itemName = removeColorCodes(item->getItemName());

	//Send the mail to the vendor owner
	String sender = "auctioner";

	UnicodeString sellerSubject("@auction:subject_auction_item_expired"); // Auction Item Expired

	StringIdChatParameter sellerBody("@auction:seller_fail"); // Your auction of %TO has been completed and has not been purchased.
	sellerBody.setTO(itemName);

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;

	if(item->isOnBazaar())
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	locker.release();

	cman->sendMail(sender, sellerSubject, sellerBody, item->getOwnerName());
}

void AuctionManagerImplementation::expireAuction(AuctionItem* item) {
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
	if (vendor == nullptr)
		return;

	String playername = item->getBidderName();
	String sellerName = item->getOwnerName();
	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();

	Zone* zone = vendor->getZone();
	String vendorPlanetName;

	if (zone != nullptr) {
		vendorPlanetName = "@planet_n:" + zone->getZoneName();
	}

	String vendorRegionName = vendorPlanetName;

	ManagedReference<CityRegion*> city = vendor->getCityRegion().get();
	if (city != nullptr) {
		vendorRegionName = city->getRegionName();
	}

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;

	Locker locker(item);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	if (playername.isEmpty()) {
		locker.release();
		expireBidAuction(item);

	} else {
		// Someone won the auction
		ManagedReference<CreatureObject*> buyer = pman->getPlayer(item->getBidderName());

		if (buyer == nullptr) {
			locker.release();
			expireBidAuction(item);
			return;
		}

		item->setStatus(AuctionItem::SOLD);
		updateAuctionOwner(item, buyer);

		// Waypoint to Vendor / bazaar
		float waypointX = vendor->getWorldPositionX();
		float waypointY = vendor->getWorldPositionY();

		WaypointChatParameter waypointParam;
		waypointParam.set(vendor->getDisplayedName(), waypointX, 0, waypointY, vendor->getPlanetCRC());

		String sender = "auctioner";

		StringIdChatParameterVector sellerBodyVector;
		WaypointChatParameterVector sellerWaypointVector;

		StringIdChatParameter sellerBodySale;
		UnicodeString sellerSubject;

		String itemName = removeColorCodes(item->getItemName());

		if (!item->isOnBazaar()) {
			sellerSubject = "@auction:subject_vendor_seller"; // Vendor Sale Complete
			sellerBodySale.setStringId("@auction:seller_success_vendor"); // %TU has sold %TO to %TT for %DI credits.
			sellerBodySale.setTU(vendor->getDisplayedName());
		} else {
			sellerSubject = "@auction:subject_auction_seller"; // Auction Complete
			sellerBodySale.setStringId("@auction:seller_success"); // Your auction of %TO has been sold to %TT for %DI credits
		}
		sellerBodySale.setTO(itemName);
		sellerBodySale.setTT(item->getBidderName());
		sellerBodySale.setDI(item->getPrice());

		StringIdChatParameter sellerBodyLoc("@auction:seller_success_location"); // The sale took place at %TT, on %TO.
		sellerBodyLoc.setTO(vendorPlanetName);
		sellerBodyLoc.setTT(vendorRegionName);

		sellerBodyVector.add(sellerBodySale);
		sellerBodyVector.add(sellerBodyLoc);

		sellerWaypointVector.add(waypointParam);

		StringIdChatParameterVector buyerBodyVector;
		WaypointChatParameterVector buyerWaypointVector;

		UnicodeString buyerSubject;
		if (!item->isOnBazaar()) {
			buyerSubject = "@auction:subject_vendor_buyer"; // Vendor Item Purchased
		} else {
			buyerSubject = "@auction:subject_auction_buyer"; // Auction Won
		}
		StringIdChatParameter buyerBodySale("@auction:buyer_success"); // You have won the auction of "%TO" from "%TT" for %DI credits. See the attached waypoint for location.
		buyerBodySale.setTO(itemName);
		buyerBodySale.setTT(sellerName);
		buyerBodySale.setDI(item->getPrice());

		StringIdChatParameter buyerBodyLoc("@auction:buyer_success_location"); // The sale took place at %TT, on %TO.
		buyerBodyLoc.setTO(vendorPlanetName);
		buyerBodyLoc.setTT(vendorRegionName);

		buyerBodyVector.add(buyerBodySale);
		buyerBodyVector.add(buyerBodyLoc);

		buyerWaypointVector.add(waypointParam);

		//Send the Mail
		locker.release();

		UnicodeString blankBody;
		cman->sendMail(sender, sellerSubject, blankBody, sellerName, &sellerBodyVector, &sellerWaypointVector);
		cman->sendMail(sender, buyerSubject, blankBody, item->getBidderName(), &buyerBodyVector, &buyerWaypointVector);
	}
}

void AuctionManagerImplementation::deleteExpiredSale(AuctionItem* item, bool sendMail) {
	Locker locker(item);

	Reference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

	if (vendor != nullptr && sendMail) {

		Reference<ChatManager*> cman = zoneServer->getChatManager();
		String sender = "auctioner";

		// Waypoint to Vendor / bazaar
		float waypointX = vendor->getWorldPositionX();
		float waypointY = vendor->getWorldPositionY();

		Reference<WaypointObject*> waypoint = zoneServer->createObject(0xc456e788, 0).castTo<WaypointObject*>();

		Locker lockerWaypoint(waypoint);

		waypoint->setPlanetCRC(vendor->getPlanetCRC());
		waypoint->setPosition(waypointX, 0, waypointY);

		waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

		lockerWaypoint.release();

		String itemName = removeColorCodes(item->getItemName());

		UnicodeString sellerSubject("@auction:subject_auction_unsuccessful"); // Auction Unsuccessful
		StringIdChatParameter sellerBody("@auction:item_expired"); // Because you failed to pick it up in time, the "%TO" that you were auctioning has expired.
		sellerBody.setTO(itemName);

		//Send the Mail
		locker.release();

		cman->sendMail(sender, sellerSubject, sellerBody, item->getOwnerName(), waypoint);
	}

	TransactionLog trx(vendor, TrxCode::AUCTIONEXPIRED, zoneServer->getObject(item->getAuctionedItemObjectID()));
	trx.addRelatedObject(item->getAuctionedItemObjectID(), true);
	auctionMap->deleteItem(vendor, item, true);
}

void AuctionManagerImplementation::displayInfo(CreatureObject* player) {
	ManagedReference<SuiListBox*> list = new SuiListBox(player, SuiWindowType::MARKET_INFO, 0x00);
	list->setPromptTitle("Market Info");
	list->setPromptText("Information about the commodities market");

	list->addMenuItem("Terminals with items");
	list->addMenuItem("\tBazaars: " + String::valueOf(auctionMap->getBazaarCount()));
	list->addMenuItem("\tVendors: " + String::valueOf(auctionMap->getVendorCount()));
	list->addMenuItem("Total Items: " + String::valueOf(auctionMap->getTotalItemCount()));

	player->sendMessage(list->generateMessage());
}

void AuctionManagerImplementation::updateAuctionOwner(AuctionItem* item, CreatureObject* player) {

	Locker locker(item);

	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> previousOwner = pman->getPlayer(item->getOwnerName());

	if(player == previousOwner)
		return;

	auctionMap->removeFromCommodityLimit(item);

	item->setOwnerID(player->getObjectID());
	item->setOwnerName(player->getFirstName());

	if(!item->isOnBazaar() && item->getStatus() != AuctionItem::OFFERED)
		return;

	auctionMap->addToCommodityLimit(item);
}

void AuctionManagerImplementation::sendVendorUpdateMail(SceneObject* vendor, bool isEmpty) {
	//Send the mail to the vendor owner
	if (vendor == nullptr || !vendor->isVendor())
		return;

	VendorDataComponent* vendorData = nullptr;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != nullptr && data->get() != nullptr && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());

	if(vendorData == nullptr)
		return;

	ManagedReference<ChatManager*> cman = vendor->getZoneServer()->getChatManager();
	ManagedReference<CreatureObject*> owner = vendor->getZoneServer()->getObject(vendorData->getOwnerId()).castTo<CreatureObject*>();

	String sender = vendor->getDisplayedName();
	UnicodeString subject("@auction:vendor_status_subject");

	if (cman == nullptr || owner == nullptr)
		return;

	if (isEmpty) {
		StringIdChatParameter body("@auction:vendor_status_empty");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
		vendorData->setEmpty();

		if (vendorData->isRegistered())
			VendorManager::instance()->handleUnregisterVendor(owner, cast<TangibleObject*>(vendor));
	} else {
		StringIdChatParameter body("@auction:vendor_status_normal");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
	}

}

String AuctionManagerImplementation::removeColorCodes(const String& name) {
	String itemName = name;

	while (itemName.contains("\\#")) {
		int index = itemName.indexOf("\\#");
		String sub = "\\" + itemName.subString(index, index + 2);
		itemName = itemName.replaceFirst(sub,"");
	}

	return itemName;
}

Logger* AuctionManagerImplementation::getLogger() {
	return dynamic_cast<Logger*>(this);
}
