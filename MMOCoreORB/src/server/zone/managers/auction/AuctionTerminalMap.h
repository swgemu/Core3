/*
 * AuctionItemMap.h
 *
 *  Created on: Jun 11, 2012
 *      Author: kyle
 */

#ifndef AUCTIONTERMINALMAP_H_
#define AUCTIONTERMINALMAP_H_

#include "engine/engine.h"
#include "TerminalListVector.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/managers/object/ObjectManager.h"

class AuctionTerminalMap {

	TerminalGalaxyList galaxyListing;

public:
	AuctionTerminalMap() {

	}

	void ensureTerminalDataExists(const String& planet, const String& region, SceneObject* vendor, TerminalItemList* items = NULL) {

		if(planet.isEmpty() || region.isEmpty() || vendor == NULL)
			return;

		if(!galaxyListing.contains(planet)) {

			Reference<TerminalPlanetList*> newPlanet = new TerminalPlanetList();;
			newPlanet->setNoDuplicateInsertPlan();
			newPlanet->setNullValue(NULL);

			galaxyListing.wlock();
			galaxyListing.put(planet, newPlanet);
			galaxyListing.unlock();
		}

		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);
		if(!planetList->contains(region)) {
			Reference<TerminalRegionList*> newRegion = new TerminalRegionList();
			newRegion->setNoDuplicateInsertPlan();
			newRegion->setNullValue(NULL);

			Locker _locker(planetList);
			planetList->put(region, newRegion);
		}

		Reference<TerminalRegionList*> regionList = planetList->get(region);
		if(!regionList->contains(vendor->getObjectID())) {
			Reference<TerminalItemList*> newItemList = new TerminalItemList();
			newItemList->setNoDuplicateInsertPlan();

			if(items != NULL) {
				Locker locker(items);
				while(items->size() > 0) {
					newItemList->add(items->remove(0));
				}
			}

			Locker _locker(regionList);
			regionList->put(vendor->getObjectID(), newItemList);
		}
	}

	void removeTerminal(SceneObject* vendor) {

		if(vendor == NULL)
			return;

		Reference<TerminalItemList*> vendorItems = NULL;
		Reference<TerminalRegionList*> vendorRegion = NULL;

		for(int i = 0; i < galaxyListing.size(); ++i) {

			Reference<TerminalPlanetList*> planetList = galaxyListing.get(i);

			if(planetList != NULL) {
				for(int j = 0; j < planetList->size(); ++j) {

					Reference<TerminalRegionList*> regionList = planetList->get(j);

					if(regionList != NULL) {
						for(int k = 0; k < regionList->size(); ++k) {
							if(regionList->elementAt(k).getKey() == vendor->getObjectID()) {
								vendorItems = regionList->get(k);
								vendorRegion = regionList;
								i = galaxyListing.size();
								j = planetList->size();
								break;
							}
						}
					}
				}
			}
		}

		if(vendorItems != NULL) {
			Locker _locker(vendorItems);
			while(vendorItems->size() > 0) {
				ManagedReference<AuctionItem*> item = vendorItems->remove(0);
				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
			}

			Locker locker(vendorRegion);
			vendorRegion->drop(vendor->getObjectID());
		}
	}

	void updateTerminalUID(const String& planet, const String& region, SceneObject* vendor, const String& newVuid) {

		if(moveVendorListing(vendor, planet, region)) {

			Reference<TerminalItemList*> items = getVendorListing(planet, region, vendor);

			if(items == NULL)
				items = findVendorItems(vendor);

			if(items == NULL || items->isEmpty())
				return;

			Locker locker(items);
			for(int i = 0; i < items->size(); ++i) {
				ManagedReference<AuctionItem* > item = items->get(i);
				if(item == NULL)
					continue;

				Locker locker(item);
				item->setVendorUID(newVuid);
			}
			return;
		}
	}

	void updateTerminalSearch(const String& planet, const String& region, SceneObject* vendor, bool enabled) {

		if(vendor == NULL || vendor->isBazaarTerminal())
			return;

		Reference<TerminalItemList*> items = getVendorListing(planet, region, vendor);
		if(items == NULL || items->isEmpty())
			return;

		Locker locker(items);
		for(int i = 0; i < items->size(); ++i) {
			ManagedReference<AuctionItem* > item = items->get(i);
			if(item == NULL)
				continue;

			Locker _locker(item);
			item->setSearchable(enabled);
		}
	}

	TerminalListVector getTerminalData(const String& planet, const String& region, SceneObject* vendor) {

		if(planet.isEmpty())
			return getGalaxyListing();

		if(region.isEmpty())
			return getPlanetListing(planet);

		if(vendor == NULL)
			return getRegionListing(planet, region);

		TerminalListVector terminals;

		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);
		if(planetList == NULL)
			return terminals;

		Reference<TerminalRegionList*> regionList = planetList->get(region);
		if(regionList == NULL)
			return terminals;

		Reference<TerminalItemList*> itemList = getVendorListing(planet, region, vendor);
		if(itemList != NULL)
			terminals.add(itemList);

		return terminals;
	}

	TerminalListVector getGalaxyListing() {

		TerminalListVector terminals;

		for(int i = 0; i < galaxyListing.size(); ++i) {

			Reference<TerminalPlanetList*> planetList = galaxyListing.get(i);

			getPlanetListing(&terminals, planetList);
		}

		return terminals;
	}

	TerminalListVector getPlanetListing(const String& planet) {

		TerminalListVector terminals;

		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);

		if(planetList != NULL)
			getPlanetListing(&terminals, planetList);

		return terminals;
	}

	void getPlanetListing(TerminalListVector* terminals, TerminalPlanetList* planetList) {

		if(planetList != NULL) {

			for(int j = 0; j < planetList->size(); ++j) {

				Reference<TerminalRegionList*> regionList = planetList->get(j);

				if(regionList != NULL) {

					for(int k = 0; k < regionList->size(); ++k) {
						terminals->add(regionList->get(k));
					}
				}
			}
		}
	}

	TerminalListVector getRegionListing(const String& planet, const String& region) {

		TerminalListVector terminals;

		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);

		if(planetList != NULL) {
			Reference<TerminalRegionList*> regionList = planetList->get(region);

			if(regionList != NULL)
				getRegionListing(&terminals, regionList);
		}

		return terminals;
	}

	void getRegionListing(TerminalListVector* terminals, TerminalRegionList* regionList) {

		if(regionList != NULL) {
			try {

				regionList->rlock();

				for(int k = 0; k < regionList->size(); ++k)
					terminals->add(regionList->get(k));

				regionList->unlock();
			}
			catch(Exception& e) {
				regionList->unlock();
			}
		}
	}

	TerminalItemList* getVendorListing(const String& planet, const String& region, SceneObject* vendor) {


		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);
		if(planetList == NULL)
			return NULL;

		Reference<TerminalRegionList*> regionList = planetList->get(region);
		if(regionList == NULL)
			return NULL;

		Reference<TerminalItemList*> itemList = regionList->get(vendor->getObjectID());

		if(itemList == NULL)
			return NULL;

		return itemList;
	}

	TerminalItemList* findVendorItems(SceneObject* vendor) {

		for(int i = 0; i < galaxyListing.size(); ++i) {

			Reference<TerminalPlanetList*> planetList = galaxyListing.get(i);

			if(planetList != NULL) {
				for(int j = 0; j < planetList->size(); ++j) {

					Reference<TerminalRegionList*> regionList = planetList->get(j);

					if(regionList != NULL) {

						try {
							regionList->rlock();
							for(int k = 0; k < regionList->size(); ++k) {
								if(regionList->elementAt(k).getKey() == vendor->getObjectID())
									return regionList->get(k);
							}
							regionList->unlock();
						}
						catch(Exception& e) {
							regionList->unlock();
						}
					}
				}
			}
		}
		return NULL;
	}

	bool moveVendorListing(SceneObject* vendor, const String& planet, const String& region) {

		Reference<TerminalItemList*> vendorItems = NULL;
		Reference<TerminalRegionList*> vendorRegion = NULL;

		Locker locker(&galaxyListing);
		for(int i = 0; i < galaxyListing.size(); ++i) {

			Reference<TerminalPlanetList*> planetList = galaxyListing.get(i);

			if(planetList != NULL) {

				Locker plocker(planetList);
				for(int j = 0; j < planetList->size(); ++j) {

					Reference<TerminalRegionList*> regionList = planetList->get(j);

					if(regionList != NULL) {

						Locker rlocker(regionList);

						for(int k = 0; k < regionList->size(); ++k) {
							if(regionList->elementAt(k).getKey() == vendor->getObjectID()) {
								vendorItems = regionList->get(k);
								vendorRegion = regionList;
								i = galaxyListing.size();
								j = planetList->size();
								break;
							}
						}
					}
				}
			}
		}

		if(vendorItems == NULL)
			return false;

		ensureTerminalDataExists(planet, region, vendor, vendorItems);

		Locker rlocker(vendorRegion);
		vendorRegion->drop(vendor->getObjectID());

		return true;
	}
};

#endif /* AUCTIONTERMINALMAP_H_ */
