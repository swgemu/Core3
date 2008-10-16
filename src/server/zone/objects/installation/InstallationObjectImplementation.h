#ifndef INSTALLATIONOBJECTIMPLEMENTATION_H_
#define INSTALLATIONOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../../../db/ServerDatabase.h"

class Zone;
class Player;
class DeedObject;

#include "InstallationObject.h"

class InstallationObjectImplementation : public InstallationObjectServant {
protected:
	int installationType, destroyCode;
	string file, temp, owner, structureStatus;

	uint32 condition, maintenance, minimumMaintenance, energy;
	float energyRate, maintenanceRate;

public:
	static const int HARVESTER = 1;
	static const int FACTORY = 2;

public:

	InstallationObjectImplementation(uint64 oid);
	InstallationObjectImplementation(uint64 oid, DeedObject* theDeed);
	~InstallationObjectImplementation();

	void init();

	//void insertToZone(Zone* zone);
	void sendTo(Player* player, bool doClose = true);

	void handleStructureRedeed(Player * player);
	void handleStructureRedeedConfirm(Player * player);
	void handleMakeDeed(Player * player);
	void handleStructureStatus(Player* player);
	void handleStructureAddMaintenance(Player* player);
	void handleStructureAddEnergy(Player* player);

	inline string& getFile(){
		return file;
	}
	inline void setObjectSubType(const int type){
		objectSubType = type;
	}
	inline string& getOwner(){
		return owner;
	}
	inline void setOwner(const string own){
		owner = own;
	}
	inline void setStatusPublic(){
		structureStatus = "public";
	}
	inline void setStatusPrivate(){
		structureStatus = "private";
	}
	inline int getDestroyCode(){
		return destroyCode;
	}
	inline void addMaintenance(uint32 maint){
		maintenance = maintenance + maint;
	}
	inline void addEnergy(uint32 powr){
		energy = energy + powr;
	}
	inline uint32 getMaintenance(){
		return maintenance;
	}
	inline uint32 getEnergy(){
		return energy;
	}
};

#endif
