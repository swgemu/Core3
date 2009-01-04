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
	String file, temp, owner, structureStatus;

	uint64 ownerID;

	uint32 condition, surplusMaintenance, minimumMaintenance, surplusPower;
	float powerRate, maintenanceRate;

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

	// Attribute Setters
	inline void setOperating(bool state) {
		setUpdated(true);
		operating = state;
		String attr("operating");
		itemAttributes->setBooleanAttribute(attr, operating);
	}
	inline void setOwner(const String own) {
		setUpdated(true);
		owner = own;
		String attr("owner");
		itemAttributes->setStringAttribute(attr, owner);
	}
	inline void setOwnerID(uint64 ownerid) {
		setUpdated(true);
		ownerID = ownerid;
		String attr("ownerID");
		itemAttributes->setUnsignedLongAttribute(attr, ownerID);
	}
	inline void setSurplusMaintenance(uint32 maint) {
		setUpdated(true);
		surplusMaintenance = maint;
		String attr("surplusMaintenance");
		itemAttributes->setIntAttribute(attr, (int)surplusMaintenance);
	}
	inline void setMaintenanceRate(float rate) {
		setUpdated(true);
		 maintenanceRate = rate;
		 String attr("maintenanceRate");
		 itemAttributes->setFloatAttribute(attr, (float)maintenanceRate);
	}
	inline void setSurplusPower(uint32 pow) {
		setUpdated(true);
		surplusPower = pow;
		String attr("surplusPower");
		itemAttributes->setIntAttribute(attr, (int)surplusPower);
	}
	inline void setPowerRate(float rate) {
		setUpdated(true);
		powerRate = rate;
		String attr("powerRate");
		itemAttributes->setFloatAttribute(attr, (float)powerRate);
	}

	// Attribute Getters
	inline bool isOperating(){
		return operating;
	}
	inline String& getOwner() {
		return owner;
	}
	inline uint64 getOwnerID() {
		return ownerID;
	}
	inline uint32 getSurplusMaintenance() {
		return surplusMaintenance;
	}
	inline float getMaintenanceRate() {
		return maintenanceRate;
	}
	inline uint32 getSurplusPower() {
		return surplusPower;
	}
	inline float getPowerRate() {
		return powerRate;
	}
	virtual float getExtractionRate() { // packets use it
		return 0.0f;
	}


	// Attribute Modifiers
	inline void addMaintenance(uint32 maint) {
		setSurplusMaintenance(getSurplusMaintenance() + maint);
	}
	inline void addPower(uint32 powr) {
		setSurplusPower(getSurplusPower() + powr);
	}
	inline void setStatusPublic() {
		structureStatus = "public";
	}
	inline void setStatusPrivate() {
		structureStatus = "private";
	}

	// Object Handlers
	void sendTo(Player* player, bool doClose = true);
	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	// Other Methods
	void handleStructureRedeed(Player * player);
	void handleStructureRedeedConfirm(Player * player);
	virtual void handleMakeDeed(Player * player);
	void handleStructureStatus(Player* player);
	void handleStructureManageMaintenance(Player* player);
	void handleStructureAddEnergy(Player* player);


	// Object Attribute
	void generateAttributes(SceneObject* obj);

	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);


	// Handle Multiple Operators
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

	inline String& getFile(){
		return file;
	}
	int getObjectSubType();
	uint32 getDeedCRC();
	inline void setObjectSubType(const int type) {
		objectSubType = type;
	}
	inline int getDestroyCode() {
		return destroyCode;
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
