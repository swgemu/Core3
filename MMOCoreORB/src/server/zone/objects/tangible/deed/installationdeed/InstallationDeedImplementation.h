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

#ifndef INSTALLATIONDEEDIMPLEMENTATION_H_
#define INSTALLATIONDEEDIMPLEMENTATION_H_


#include "InstallationDeed.h"

class InstallationDeedImplementation : public InstallationDeedServant {
	float maintenanceRate;
	float powerRate;
	float baseExtractionRate;
	float hopperSizeMax;

	uint32 surplusMaintenance;
	uint32 surplusPower;
	uint32 targetConstructionObjectCRC;
	uint32 targetConditionMax;

	uint32 reclaimFee;

	uint8 harvesterType;
	uint8 lotSize;

	void init();

public:
	InstallationDeedImplementation(CreatureObject* creature, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	InstallationDeedImplementation(uint64 objid, uint32 objcrc, const UnicodeString& customname, const String& stfname);
	~InstallationDeedImplementation();

	int useObject(Player* player);

	SceneObject* generateObject(Player* player);

	void parseItemAttributes();
	void addAttributes(AttributeListMessage* alm);

	//Setters
	inline void setReclaimFee(uint32 fee) {
		reclaimFee = fee;
		String attr("reclaimFee");
		itemAttributes->setIntAttribute(attr, reclaimFee);
	}

	inline void setMaintenanceRate(float rate) {
		maintenanceRate = rate;
		String attr("maintenanceRate");
		itemAttributes->setFloatAttribute(attr, maintenanceRate);
	}

	inline void setPowerRate(float rate) {
		powerRate = rate;
		String attr("powerRate");
		itemAttributes->setFloatAttribute(attr, powerRate);
	}

	inline void setBaseExtractionRate(float rate) {
		baseExtractionRate = rate;
		String attr("baseExtractionRate");
		itemAttributes->setFloatAttribute(attr, baseExtractionRate);
	}

	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		String attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, hopperSizeMax);
	}

	inline void setSurplusMaintenance(uint32 maint) {
		surplusMaintenance = maint;
		String attr("surplusMaintenance");
		itemAttributes->setIntAttribute(attr, surplusMaintenance);
	}

	inline void setSurplusPower(uint32 power) {
		surplusPower = power;
		String attr("surplusPower");
		itemAttributes->setIntAttribute(attr, surplusPower);
	}

	inline void setTargetConstructionObjectCRC(uint32 objcrc) {
		targetConstructionObjectCRC = objcrc;
		String attr("targetConstructionObjectCRC");
		itemAttributes->setIntAttribute(attr, targetConstructionObjectCRC);
	}

	inline void setTargetConditionMax(uint32 condmax) {
		targetConditionMax = condmax;
		String attr("targetConditionMax");
		itemAttributes->setIntAttribute(attr, targetConditionMax);
	}

	inline void setLotSize(uint8 lotsize) {
		lotSize = lotsize;
		String attr("lotSize");
		itemAttributes->setIntAttribute(attr, lotSize);
	}

	inline void setHarvesterType(uint8 type) {
		harvesterType = type;
		String attr("harvesterType");
		itemAttributes->setIntAttribute(attr, harvesterType);
	}

	//Getters
	inline float getMaintenanceRate() {
		return maintenanceRate;
	}

	inline float getPowerRate() {
		return powerRate;
	}

	inline float getBaseExtractionRate() {
		return baseExtractionRate;
	}

	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}

	inline uint32 getSurplusMaintenance() {
		return surplusMaintenance;
	}

	inline uint32 getSurplusPower() {
		return surplusPower;
	}

	inline uint32 getTargetConstructionObjectCRC() {
		return targetConstructionObjectCRC;
	}

	inline uint32 getTargetConditionMax() {
		return targetConditionMax;
	}

	inline uint32 getReclaimFee() {
		return reclaimFee;
	}

	inline uint8 getHarvesterType() {
		return harvesterType;
	}

	inline uint8 getLotSize() {
		return lotSize;
	}

	inline bool isMaintenanceEmpty() {
		return (surplusMaintenance <= 0);
	}

	inline bool isPowerEmpty() {
		return (surplusPower <= 0);
	}

	inline bool isFactoryDeed() {
		return (targetObjectSubType == TangibleObjectImplementation::FACTORY);
	}

	inline bool isGeneratorDeed() {
		return (targetObjectSubType == TangibleObjectImplementation::GENERATOR);
	}

	inline bool isHarvesterDeed() {
		return (targetObjectSubType == TangibleObjectImplementation::HARVESTER);
	}

	inline bool isTurretDeed() {
		return (targetObjectSubType == TangibleObjectImplementation::TURRET);
	}

	inline bool isMinefieldDeed() {
		return (targetObjectSubType == TangibleObjectImplementation::MINEFIELD);
	}
};

#endif /* INSTALLATIONDEEDIMPLEMENTATION_H_ */
