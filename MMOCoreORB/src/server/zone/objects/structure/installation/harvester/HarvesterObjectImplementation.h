/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef HARVESTEROBJECTIMPLEMENTATION_H_
#define HARVESTEROBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../tangible/deed/installationdeed/InstallationDeed.h"
#include "HarvesterObject.h"

class HarvestResourceEvent;

class HarvesterObjectImplementation : public HarvesterObjectServant {
	VectorMap<uint64, float> resourceHopper; // uint64 resourceid, float quantity

	HarvestResourceEvent* harvestEvent;

	uint64 selectedResourceID;

	float baseExtractionRate;
	float hopperSizeMax;

	int spawnDensity;

	uint8 harvesterType;

	void init();

public:

public:
	HarvesterObjectImplementation(uint64 objid);
	HarvesterObjectImplementation(uint64 objid, InstallationDeed* deed);
	~HarvesterObjectImplementation();

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);
	virtual void sendHopperUpdatesToOperators();

	void parseItemAttributes();

	// Updaters
	void changeSelectedResourceID(uint64 resourceid);

	virtual void serialize();
	virtual void deserialize();

	virtual void loadHopper(const String& hopperstring);

	void cleanOperatorsList();

	void insertToZone(Zone* zone);

	void harvestResource(bool reschedule = true);
	void rescheduleHarvestEvent(uint32 miliseconds = 5000);
	void clearHarvestEvent();
	bool isSelectedResourceSpawning();

	bool retrieveResource(Player* player, uint64 resourceid, float amount);
	bool discardResource(Player* player, uint64 resourceid, float amount);
	bool emptyHarvester(Player* player);

	bool start(Player* player);
	void shutdown(uint8 errorcode = ERR_NONE);
	InstallationDeed* redeed(Player* player);

	/**
	 * Adds an item to the hopper. If that item already exists, it adds the new quantity.
	 * \param resourceid The id of the resource to add to the hopper.
	 * \param quantity How much of the resource is to be added to the hopper.
	 */
	inline void addHopperItem(uint64 resourceid, float quantity) {
		if (resourceHopper.contains(resourceid))
			resourceHopper.get(resourceid) += quantity;
		else
			resourceHopper.put(resourceid, quantity);
	}

	/**
	 * Removes a specified amount of resource from the hopper and returns the remaining amount.
	 * \param resourceid The resource to remove.
	 * \param quantity The amount of remove.
	 * \return Returns the amount removed.
	 */
	float removeHopperItem(uint64 resourceid, float quantity) {
		if (!resourceHopper.contains(resourceid))
			return 0.0f;

		//How much is actually in the hopper
		float hopperquantity = resourceHopper.get(resourceid);

		if (quantity >= hopperquantity) {
			resourceHopper.get(resourceid) = 0.0f;
			return hopperquantity;
		} else {
			resourceHopper.get(resourceid) -= quantity;
		}

		return quantity;
	}

	// Setters
	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		String attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, hopperSizeMax);
	}

	inline void setBaseExtractionRate(float max) {
		baseExtractionRate = max;
		String attr("baseExtractionRate");
		itemAttributes->setFloatAttribute(attr, baseExtractionRate);
	}

	inline void setSelectedResourceID(uint64 resourceid) {
		selectedResourceID = resourceid;
		String attr("selectedResourceID");
		itemAttributes->setUnsignedLongAttribute(attr, selectedResourceID);
	}

	inline void setSpawnDensity(int dens) {
		spawnDensity = dens;
		String attr("spawnDensity");
		itemAttributes->setIntAttribute(attr, spawnDensity);
	}

	inline void setHarvesterType(uint8 type) {
		harvesterType = type;
		String attr("harvesterType");
		itemAttributes->setIntAttribute(attr, harvesterType);
	}

	//Getters
	inline uint64 getSelectedResourceID() {
		return selectedResourceID;
	}

	inline float getExtractionRate() {
		if (!isOperating())
			return 0.0f;

		return baseExtractionRate * ((float) spawnDensity) / 100.0f;
	}

	inline float getBaseExtractionRate() {
		return baseExtractionRate;
	}

	inline float getDisplayedBaseExtractionRate() {
		return floor(baseExtractionRate);
	}

	inline float getHopperSize() {
		float quantity = 0.0f;

		for (int i = 0; i < resourceHopper.size(); i++)
			quantity += resourceHopper.get(i);

		return quantity;
	}

	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}

	inline uint32 getHopperListSize() {
		return resourceHopper.size();
	}

	inline uint64 getHopperItemID(int index) {
		return resourceHopper.elementAt(index)->getKey();
	}

	inline float getHopperItemQuantity(int index) {
		return resourceHopper.get(index);
	}

	inline float getHopperItemQuantity(uint64 resourceid) {
		if (resourceHopper.contains(resourceid))
			return resourceHopper.get(resourceid);

		return 0.0f;
	}

	inline int getHopperItemIndex(uint64 resourceid) {
		return resourceHopper.find(resourceid);
	}

	inline int getSpawnDensity() {
		return spawnDensity;
	}

	inline uint8 getHarvesterType() {
		return harvesterType;
	}

	inline bool hasOperators() {
		return (operatorsList.size() > 0);
	}
};

#endif /*HARVESTEROBJECTIMPLEMENTATION_H_*/
