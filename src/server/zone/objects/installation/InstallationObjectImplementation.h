#ifndef INSTALLATIONOBJECTIMPLEMENTATION_H_
#define INSTALLATIONOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

class Zone;
class Player;
class DeedObject;
class InstallationSyncUIEvent;


class InstallationObjectImplementation : public InstallationObjectServant {
protected:
	bool operating;

	int installationType, destroyCode;
	string file, temp, owner, structureStatus;

	uint32 condition, maintenance, minimumMaintenance, energy;
	float energyRate, maintenanceRate;

	Vector<ManagedReference<SceneObject> > operatorList; // track synchronizeduilisten and synchronizeduistoplistening to send packet updates

	//INSO6 operands
	uint32 defenderUpdateCounter;
	uint64 defenderID;

	InstallationSyncUIEvent* syncEvent;

	Vector<ManagedReference<SceneObject> > defenderList;

	VectorMap<CreatureObject*, uint32> damageMap;

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
	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void handleStructureRedeed(Player * player);
	void handleStructureRedeedConfirm(Player * player);
	void handleMakeDeed(Player * player);
	void handleStructureStatus(Player* player);
	void handleStructureAddMaintenance(Player* player);
	void handleStructureAddEnergy(Player* player);

	virtual void updateOperators() {
		// operatorList
	}

	inline uint32 getOperatorListSize() {
		return operatorList.size();
	}
	inline SceneObject* getOperator(int idx) {
		return operatorList.get(idx);
	}
	inline void addOperator(SceneObject *op) {
		if (op == _this)
			return;

		for (int i = 0; i < operatorList.size(); ++i) {
			if (op == operatorList.get(i))
				return;
		}

		operatorList.add(op);
	}
	inline void removeOperator(SceneObject *op) {
		if (op == _this)
			return;

		for (int i = 0; i < operatorList.size(); ++i) {
			if (op == operatorList.get(i)) {
				operatorList.remove(i);
				return;
			}
		}
	}

	void activateSync();

	inline bool isOperating(){
		return operating;
	}
	inline void setOperating(bool state){
		operating = state;
	}
	inline string& getFile(){
		return file;
	}
	int getObjectSubType();
	inline void setObjectSubType(const int type) {
		objectSubType = type;
	}
	inline string& getOwner() {
		return owner;
	}
	inline void setOwner(const string own) {
		owner = own;
	}
	inline void setStatusPublic() {
		structureStatus = "public";
	}
	inline void setStatusPrivate() {
		structureStatus = "private";
	}
	inline int getDestroyCode() {
		return destroyCode;
	}
	inline void addMaintenance(uint32 maint) {
		maintenance = maintenance + maint;
	}
	inline uint32 getMaintenance() {
		return maintenance;
	}
	inline float getMaintenanceRate() {
		return maintenanceRate;
	}
	inline void addEnergy(uint32 powr) {
		energy = energy + powr;
	}
	inline uint32 getEnergy() {
		return energy;
	}
	inline float getEnergyRate() {
		return energyRate;
	}


	// Hopper Stuff
	virtual void updateHopper() {
	}
	virtual inline float getHopperSize() {
		return 0;
	}
	virtual inline float getHopperSizeMax() {
		return 0.0f;
	}
	virtual inline int getHopperItemCount() {
		return 0;
	}
	virtual inline uint64 getHopperItemID(int index) {
		return 0;
	}
	virtual inline float getHopperItemQuantity(int index) {
		return 0.0f;
	}
	virtual inline float getHopperItemQuantity(uint64 rid) {
		return 0.0f;
	}
	virtual float removeHopperItem(uint64 rid, uint32 quantity) {
		return 0.0f;
	}
	virtual inline void setHopperUpdateCounter(uint32 counter) {
	}
	virtual inline uint32 getHopperUpdateCounter() {
		return 0;
	}
	virtual inline uint32 getNewHopperUpdateCounter(uint32 update) {
		return 0;
	}

	// Harvester Stuff
	virtual inline float getSpecRate() {
		return 0.0f;
	}
	virtual inline float getActualRate() {
		return 0.0f;
	}
	virtual inline uint64 getActiveResourceID(){
		return 0;
	}


	// Combat Items
	void setCombatState();
	void clearCombatState(bool removedefenders);
	void setDefender(SceneObject* defender);
	void addDefender(SceneObject* defender);
	void removeDefender(SceneObject* defender);
	void removeDefenders();
	bool hasDefender(SceneObject* defender);

	inline void setDefenderID(uint64 did) {
		defenderID = did;
	}
	inline uint64 getDefenderID() {
		return defenderID;
	}
	inline uint32 getDefenderListSize() {
		return defenderList.size();
	}
	inline SceneObject* getDefender(int idx) {
		return defenderList.get(idx);
	}
	inline uint32 getDefenderUpdateCounter() {
		return defenderUpdateCounter;
	}
	inline uint32 getNewDefenderUpdateCounter(int cnt) {
		return defenderUpdateCounter += cnt;
	}

};

#endif
