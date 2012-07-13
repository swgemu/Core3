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

class AuctionTerminalMap : public VectorMap<uint64, Reference<TerminalItemList*> >, public Logger, public ReadWriteLock {

	TerminalGalaxyList galaxyListing;

public:
	AuctionTerminalMap() {
		setNullValue(NULL);
		setNoDuplicateInsertPlan();

		galaxyListing.setNoDuplicateInsertPlan();
		galaxyListing.setNullValue(NULL);

		setLoggingName("AuctionTerminalMap");
	}

	bool createTerminalListing(const String& planet, const String& region, SceneObject* vendor) {

		Locker locker(this);
		Locker glocker(&galaxyListing);

		if(vendor == NULL) {
			warning("unable to create NULL vendor");
			return false;
		}

		if(!galaxyListing.contains(planet) && !addPlanetListing(planet)) {
			error("Unable to create planet listing");
			return false;
		}


		Reference<TerminalPlanetList*> planetList = galaxyListing.get(planet);
		if(planetList == NULL || (!planetList->contains(region) && !addRegionListing(planetList, region))) {
			error("unable to create region listing");
			return false;
		}

		Reference<TerminalRegionList*> targetRegion = planetList->get(region);
		Reference<TerminalRegionList*> existingRegion = getVendorRegion(vendor);

		if(!targetRegion->contains(vendor->getObjectID()) || !contains(vendor->getObjectID())) {

			Reference<TerminalItemList*> itemList = NULL;

			if(existingRegion != NULL) {
				itemList = existingRegion->get(vendor->getObjectID());

				existingRegion->drop(vendor->getObjectID());
			}

			if(itemList == NULL)
				itemList = get(vendor->getObjectID());

			if(itemList == NULL) {
				itemList = new TerminalItemList();
				itemList->setNoDuplicateInsertPlan();
			}

			targetRegion->put(vendor->getObjectID(), itemList);
			put(vendor->getObjectID(), itemList);
		}
		return true;
	}

	bool dropTerminalListing(SceneObject* vendor) {

		if(vendor == NULL) {
			warning("unable to drop NULL vendor");
			return false;
		}

		Locker locker(this);
		Locker glocker(&galaxyListing);

		Reference<TerminalRegionList*> existingRegion = getVendorRegion(vendor);
		if(existingRegion == NULL)
			return drop(vendor->getObjectID());

		if(existingRegion->drop(vendor->getObjectID()))
			return drop(vendor->getObjectID());

		return false;
	}

	bool updateTerminalUID(const String& planet, const String& region, SceneObject* vendor, const String& newVuid) {


		if(!createTerminalListing(planet, region, vendor)) {
			error("unable to update terminal UID");
			return false;
		}

		Reference<TerminalItemList*> itemList = get(vendor->getObjectID());

		if(itemList == NULL)
			return false;

		if(itemList->isEmpty())
			return true;

		Locker locker(itemList);
		for(int i = 0; i < itemList->size(); ++i) {
			ManagedReference<AuctionItem* > item = itemList->get(i);
			if(item == NULL)
				continue;

			Locker locker(item);
			item->setVendorUID(newVuid);
		}

		return true;

	}

	void updateTerminalSearch(SceneObject* vendor, bool enabled) {

		if(vendor == NULL || vendor->isBazaarTerminal())
			return;

		Reference<TerminalItemList*> itemList = get(vendor->getObjectID());

		if(itemList == NULL)
			return;

		Locker locker(itemList);
		itemList->setSearchable(enabled);
	}

	TerminalListVector getTerminalData(const String& planet, const String& region, SceneObject* vendor) {

		if(planet.isEmpty())
			return getGalaxyListing();

		if(region.isEmpty())
			return getPlanetListing(planet);

		if(vendor == NULL)
			return getRegionListing(planet, region);

		TerminalListVector terminals;

		Reference<TerminalItemList*> itemList = get(vendor->getObjectID());
		if(itemList != NULL)
			terminals.add(itemList);

		return terminals;
	}

	TerminalListVector getGalaxyListing() {

		TerminalListVector terminals;

		try {

			rlock();

			for(int i = 0; i < size(); ++i) {

				Reference<TerminalItemList*> itemList = get(i);

				if(itemList == NULL)
					continue;

				terminals.add(itemList);

			}

			unlock();
		}
		catch(Exception& e) {
			unlock();
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

private:
	bool addPlanetListing(const String& planet) {

		if(galaxyListing.contains(planet))
			return true;

		Reference<TerminalPlanetList*> newPlanet = new TerminalPlanetList();
		newPlanet->setNoDuplicateInsertPlan();
		newPlanet->setNullValue(NULL);

		return (galaxyListing.put(planet, newPlanet) != -1);
	}

	bool removePlanetListing(const String& planet) {

		if(!galaxyListing.contains(planet))
			return true;

		return galaxyListing.drop(planet);
	}

	bool addRegionListing(TerminalPlanetList* planetList, const String& region) {

		if(planetList->contains(region))
			return true;

		Reference<TerminalRegionList*> newRegion = new TerminalRegionList();
		newRegion->setNoDuplicateInsertPlan();
		newRegion->setNullValue(NULL);

		return (planetList->put(region, newRegion) != -1);
	}

	bool removeRegionListing(TerminalPlanetList* planetList, const String& region) {

		if(!planetList->contains(region))
			return true;

		return planetList->drop(region);
	}

	/// Pre Locked
	TerminalRegionList* getVendorRegion(SceneObject* vendor) {

		for(int i = 0; i < galaxyListing.size(); ++i) {

			Reference<TerminalPlanetList*> planetList = galaxyListing.get(i);
			if(planetList != NULL) {

				for(int j = 0; j < planetList->size(); ++j) {

					Reference<TerminalRegionList*> regionList = planetList->get(j);

					if(regionList != NULL) {

						for(int k = 0; k < regionList->size(); ++k) {
							if(regionList->elementAt(k).getKey() == vendor->getObjectID()) {
								return regionList;
							}
						}
					}
				}
			}
		}
		return NULL;
	}

	void getPlanetListing(TerminalListVector* terminals, TerminalPlanetList* planetList) {

		if(planetList != NULL) {

			try {

				planetList->rlock();

				for(int j = 0; j < planetList->size(); ++j) {

					Reference<TerminalRegionList*> regionList = planetList->get(j);

					if(regionList != NULL)
						getRegionListing(terminals, regionList);
				}
				planetList->unlock();
			}
			catch(Exception& e) {
				planetList->unlock();
			}
		}
	}

	void getRegionListing(TerminalListVector* terminals, TerminalRegionList* regionList) {

		if(regionList != NULL) {
			try {

				regionList->rlock();

				for(int i = 0; i < regionList->size(); ++i) {

					Reference<TerminalItemList*> itemList = regionList->get(i);

					if(itemList == NULL)
						continue;

					terminals->add(itemList);
				}

				regionList->unlock();
			}
			catch(Exception& e) {
				regionList->unlock();
			}
		}
	}

};

#endif /* AUCTIONTERMINALMAP_H_ */
