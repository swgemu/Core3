/*
 * FactoryObjectImplementation.h
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#ifndef FACTORYOBJECTIMPLEMENTATION_H_
#define FACTORYOBJECTIMPLEMENTATION_H_


#include "engine/engine.h"

#include "../../../../db/ServerDatabase.h"

#include "../../tangible/Container.h"

class Zone;
class Player;
class DeedObject;
class FactoryDeed;
class InstallationObject;
class FactoryCreateItemEvent;
class ManufactureSchematic;

#include "FactoryObject.h"

class FactoryObjectImplementation : public FactoryObjectServant {
protected:
	float hopperSizeMax, buildRate;
	ManagedReference<Container> inputHopper;
	ManagedReference<Container> outputHopper;
	FactoryCreateItemEvent* createItemEvent;

public:
	FactoryObjectImplementation(uint64 oid);
	FactoryObjectImplementation(uint64 oid, FactoryDeed *deed);
	~FactoryObjectImplementation();

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);
	void createHoppers(uint64 inputHopperID, uint64 outputHopperID);
	void parseItemAttributes();
	void updateItemForSurroundingPlayers(TangibleObject* item);
	void handleStructureRedeed(Player * player);

	bool containsIngredients(ManufactureSchematic* linkedSchematic, bool doLock = true);
	bool removeIngredients(ManufactureSchematic* linkedSchematic);
	bool putItemInOutputHopper(ManufactureSchematic* linkedSchematic, bool doLock = true);
	void sendEmailToOwner(String subject, String bodyMsg);

	void setOperating(bool state);
	void scheduleItemCreation();
	void createItem();
	void sendInsertManSchemTo(Player* player);
	void sendViewIngredientsTo(Player* player);
	void sendInputHopperTo(Player* player);
	void sendOutputHopperTo(Player* player);
	void loadItems();

	//Attribute setters
	/*
	 * Sets the manufacture schematic WITHOUT returning the current manufacturing schematic to the player.
	 */
	void setManufactureSchem(ManufactureSchematic* manufactureSchem){
		while(_this->getContainerObjectsSize() > 0)
			removeObject(0);

		addObject((SceneObject*)manufactureSchem);
	}

	/*
	 * Sets the manufacture schematic after returing the current schematic to the player.
	 */
	void setManufactureSchem(ManufactureSchematic* manufactureSchem, Player* player);

	inline void setHopperSizeMax(float size) {
		hopperSizeMax = size;
		String attr("hopperSizeMax");
		itemAttributes->setFloatAttribute(attr, (float)hopperSizeMax);
	}

	void serializeHoppers();

	inline void setBuildRate(float rate) {
		buildRate = rate;
		String attr("buildRate");
		itemAttributes->setFloatAttribute(attr, (float)buildRate);
	}

	// Attribute Getters
	inline float getHopperSizeMax() {
		return hopperSizeMax;
	}
	inline float getBuildRate() {
		return buildRate;
	}

	inline ManufactureSchematic* getManufactureSchem(){
		if(_this->getContainerObjectsSize() > 0){
			ManagedReference<SceneObject> scno = getObject(0);
			if(scno->isManufactureSchematic()){
				ManufactureSchematic* manuf = (ManufactureSchematic*) scno.get();
				return manuf;
			}
		}
		return NULL;
	}

	int getFactoryType();
	int getFactoryItemTypes();

	bool isWearablesFactory() {
		return (objectCRC == 0xE9FB1618);
	}

	bool isEquipmentFactory() {
		return (objectCRC == 0x5FE2FCB6);
	}

	bool isFoodFactory() {
		return (objectCRC == 0xC3ECD730);
	}

	bool isStructureFactory() {
		return (objectCRC == 0x5F850B0);
	}

	bool hasSchematic() {
		return _this->getContainerObjectsSize() > 0;
	}

	void clearManufactureSchem() {
		while (_this->getContainerObjectsSize() > 0)
			removeObject(0);
	}

private:
	void init();
};


#endif /* FACTORYOBJECTIMPLEMENTATION_H_ */
