#ifndef INSTALLATIONOBJECTIMPLEMENTATION_H_
#define INSTALLATIONOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "InstallationObject.h"

#include "../StructurePermissionList.h"
#include "../../tangible/deed/installationdeed/InstallationDeed.h"

class StructureStatusPollEvent;

class InstallationObjectImplementation : public InstallationObjectServant {
protected:
	StructurePermissionList* permissionList;

	Vector<ManagedReference<Player> > operatorsList;

	StructureStatusPollEvent* structureStatusPollEvent;
	Time lastStatusPoll;

	String deedStfName;
	String objectFile;

	uint32 structureID;
	uint32 destroyCode;
	uint32 reclaimFee;
	uint32 deedCRC;
	uint32 updateCounter;

	float maintenanceRate;
	float powerRate;
	float maintenancePool;
	float powerReserves;

	uint8 lotSize;

	bool operating;
	bool publicStructure;

	void init();

public:
	//Error codes for when shutting down an installation.
	static const uint8 ERR_NONE = 0;
	static const uint8 ERR_OUTOFPOWER = 1;
	static const uint8 ERR_OUTOFMAINTENANCE = 2;
	static const uint8 ERR_HOPPERFULL = 3;

public:
	InstallationObjectImplementation(uint64 oid);
	InstallationObjectImplementation(uint64 oid, InstallationDeed* deed);
	~InstallationObjectImplementation();

	virtual void serialize();
	virtual void deserialize();

	void sendTo(Player* player, bool doClose = true);
	void sendPermissionListTo(Player* player, const String& listname);
	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);
	void sendCustomNamePromptTo(Player* player);

	void updateCustomName(Player* player, const String& value);

	virtual void insertToZone(Zone* zone);

	//Dialogs for structure management
	virtual void sendStatusTo(Player* player);
	virtual void sendManageMaintenanceTo(Player* player);
	virtual void sendManagePowerTo(Player* player);
	virtual void sendConfirmDestroyTo(Player* player);
	virtual void sendDestroyCodeTo(Player* player);

	virtual bool start(Player* player);
	virtual void shutdown(uint8 errorcode = ERR_NONE, bool sendmail = true);
	virtual bool destroyStructure(Player* player);
	virtual InstallationDeed* redeed(Player* player);

	virtual void modifyPermissionList(Player* player, const String& listname, const String& entryname, bool add = true);

	virtual void pollStatus(bool reschedule = true);
	virtual void consumeMaintenance();
	virtual void consumePower();
	virtual void payTaxes();

	virtual void depositMaintenance(Player* player, uint32 amount);
	virtual void depositPower(Player* player, uint32 amount);

	virtual void addOperator(Player* player);
	virtual void removeOperator(Player* player);

	//Item Attributes
	void generateAttributes(SceneObject* obj);
	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);

	/**
	 * Changes the maintenance reserves. Effectively floors the maintenance at 0.
	 * \param amount The amount to raise or lower the maintenance by.
	 */
	inline void changeMaintenancePool(float amount) {
		maintenancePool += amount;

		if (maintenancePool < 0)
			maintenancePool = 0;

		setUpdated(true);
		String attr("maintenancePool");
		itemAttributes->setFloatAttribute(attr, maintenancePool);
	}

	/**
	 * Changes the power reserves. Effectively floors the power at 0.
	 * \param amount The amount to raise or lower the power by.
	 */
	inline void changePowerReserves(float amount) {
		powerReserves += amount;

		if (powerReserves < 0)
			powerReserves = 0;

		setUpdated(true);
		String attr("powerReserves");
		itemAttributes->setFloatAttribute(attr, powerReserves);
	}

	/**
	 * Generates a random 6 digit number which much be entered to confirm a destroy request.
	 * \return Returns the new 6 digit destroy code as an unsigned integer.
	 */
	inline uint32 generateDestroyCode() {
		destroyCode = (System::random(899999) + 100000);
		return destroyCode;
	}

	/**
	 * Compares the passed in code against the installations destroy code.
	 * \return Returns true if the passed code matches the installations destroy code.
	 */
	inline bool isValidDestroyCode(uint32 code) {
		return (destroyCode == code);
	}

	// Setters
	inline void setStructureID(uint32 structureid) {
		setUpdated(true);
		structureID = structureid;
		String attr("structureID");
		itemAttributes->setIntAttribute(attr, structureID);
	}

	inline void setDeedCRC(uint32 crc) {
		setUpdated(true);
		deedCRC = crc;
		String attr("deedCRC");
		itemAttributes->setIntAttribute(attr, deedCRC);
	}

	inline void setDeedStfName(const String& stfname) {
		setUpdated(true);
		deedStfName = stfname;
		String attr("deedStfName");
		itemAttributes->setStringAttribute(attr, deedStfName);
	}

	inline void setObjectFile(const String& objectfile) {
		setUpdated(true);
		objectFile = objectfile;
		String attr("objectFile");
		itemAttributes->setStringAttribute(attr, objectFile);
	}

	inline void setReclaimFee(uint32 fee) {
		setUpdated(true);
		reclaimFee = fee;
		String attr("reclaimFee");
		itemAttributes->setIntAttribute(attr, reclaimFee);
	}

	inline void setMaintenancePool(float maint) {
		setUpdated(true);
		maintenancePool = maint;
		String attr("maintenancePool");
		itemAttributes->setFloatAttribute(attr, maintenancePool);
	}

	inline void setMaintenanceRate(float rate) {
		setUpdated(true);
		maintenanceRate = rate;
		String attr("maintenanceRate");
		itemAttributes->setFloatAttribute(attr, maintenanceRate);
	}

	inline void setPowerReserves(float pow) {
		setUpdated(true);
		powerReserves = pow;
		String attr("powerReserves");
		itemAttributes->setFloatAttribute(attr, powerReserves);
	}

	inline void setPowerRate(float rate) {
		setUpdated(true);
		powerRate = rate;
		String attr("powerRate");
		itemAttributes->setFloatAttribute(attr, powerRate);
	}

	inline void setOperating(bool state) {
		setUpdated(true);
		operating = state;
		String attr("operating");
		itemAttributes->setBooleanAttribute(attr, operating);
	}

	inline void setPublicStructure(bool status) {
		setUpdated(true);
		publicStructure = status;
		String attr("publicStructure");
		itemAttributes->setBooleanAttribute(attr, publicStructure);
	}

	inline void setLotSize(uint8 size) {
		setUpdated(true);
		lotSize = size;
		String attr("lotSize");
		itemAttributes->setIntAttribute(attr, lotSize);
	}

	inline void setPermissionsFromString(const String& permissionstring) {
		permissionList->parsePermissionsString(permissionstring);
	}

	//Getters
	inline uint32 getStructureID() {
		return structureID;
	}

	inline uint32 getDestroyCode() {
		return destroyCode;
	}

	inline uint32 getDeedCRC() {
		return deedCRC;
	}

	inline uint32 getReclaimFee() {
		return reclaimFee;
	}

	inline String& getDeedStfName() {
		return deedStfName;
	}

	inline String& getObjectFile() {
		return objectFile;
	}

	inline float getPowerRate() {
		return powerRate;
	}

	inline float getMaintenanceRate() {
		return maintenanceRate;
	}

	inline float getMaintenancePool() {
		return maintenancePool;
	}

	inline float getPowerReserves() {
		return powerReserves;
	}

	inline uint8 getLotSize() {
		return lotSize;
	}

	inline String& getPermissionsString() {
		return permissionList->getPermissionsString();
	}

	/** Gets a new hopper update counter for sending in packets.
	 * \param update How many updates is the packet sending
	 */
	inline uint32 getNewUpdateCounter(uint32 update) {
		return updateCounter += update;
	}

	inline uint32 getUpdateCounter() {
		return updateCounter;
	}

	inline bool isRedeedable() {
		return (getReclaimFee() <= getMaintenancePool());
	}

	inline bool isOperating() {
		return operating;
	}

	inline bool isHopperEmpty() {
		return (getHopperSize() == 0.0f);
	}

	inline bool isHopperFull() {
		return (getHopperSize() == getHopperSizeMax());
	}

	inline bool isOutOfMaintenance() {
		return (maintenancePool <= 0);
	}

	inline bool isOutOfPower() {
		return (powerReserves <= 0);
	}

	inline bool isHarvester() {
		return objectSubType == TangibleObjectImplementation::HARVESTER;
	}

	inline bool isGenerator() {
		return objectSubType == TangibleObjectImplementation::GENERATOR;
	}

	inline bool isFactory() {
		return objectSubType == TangibleObjectImplementation::FACTORY;
	}

	inline bool isTurret() {
		return objectSubType == TangibleObjectImplementation::TURRET;
	}

	inline bool isMinefield() {
		return objectSubType == TangibleObjectImplementation::MINEFIELD;
	}

	inline bool isPublicStructure() {
		return publicStructure;
	}

	inline bool isOnAdminList(Player* player) {
		return permissionList->isOnAdminList(player);
	}

	inline bool isOnHopperList(Player* player) {
		return permissionList->isOnHopperList(player);
	}


	/**
	 * Methods which aren't used in every installation, but are sent in every INSO7.
	 */

	//Overridable Setters
	inline virtual void setBaseExtractionRate(float rate) {
		return;
	}

	inline virtual void setHopperSizeMax(float maxsize) {
		return;
	}

	inline virtual void setHarvesterType(uint8 type) {
		return;
	}


	//Overridable Getters
	inline virtual uint64 getSelectedResourceID() {
		return 0;
	}

	/// Returns the current operating extraction rate.
	inline virtual float getExtractionRate() {
		return 0.0f;
	}

	/// Returns the installations maximum allowed extraction rate.
	inline virtual float getBaseExtractionRate() {
		return 0.0f;
	}

	// Returns the installations maximum allowed extraction rate converted to an integer and floored.
	inline virtual float getDisplayedBaseExtractionRate() {
		return 0.0f;
	}

	/// Returns the combined quantity of all items in the hopper.
	inline virtual float getHopperSize() {
		return 0.0f;
	}

	/// Returns the maximum quantity that the hopper can hold.
	inline virtual float getHopperSizeMax() {
		return 0;
	}

	/// How many individual items are in the hopper (each item is 1 regardless of quantity).
	inline virtual uint32 getHopperListSize() {
		return 0;
	}

	/// Get the Resource ID of the specified hopper item.
	inline virtual uint64 getHopperItemID(int index) {
		return 0;
	}

	/// Returns the quantity of the specified hopper item by index.
	inline virtual float getHopperItemQuantity(int index) {
		return 0;
	}

	/// Returns the quantity of the specified hopper item by resource id.
	inline virtual float getHopperItemQuantity(uint64 resourceid) {
		return 0;
	}

	/// Returns the index in the list of the hopper item.
	inline virtual int getHopperItemIndex(uint64 resourceid) {
		return 0;
	}
};

#endif
