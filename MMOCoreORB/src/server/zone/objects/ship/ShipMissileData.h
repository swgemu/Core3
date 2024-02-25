#ifndef SHIPMISSILEDATA_H_
#define SHIPMISSILEDATA_H_

#include "engine/engine.h"
#include "templates/datatables/DataTableRow.h"

class ShipMissileData : public Object {
public:
	enum PlayerMissileType : int {
		CONCUSSION_MK1 = 0,
		CONCUSSION_MK2 = 1,
		CONCUSSION_MK3 = 2,
		IMAGEREC_MK1 = 3,
		IMAGEREC_MK2 = 4,
		PROTON_MK1 = 5,
		PROTON_MK2 = 6,
		PROTON_MK3 = 7,
		PROTON_MK4 = 8,
		SEISMIC_MK1 = 9,
		SEISMIC_MK2 = 10,
		SEISMIC_MK3 = 11,
		SPACEBOMB_MK1 = 12,
		SPACEBOMB_MK2 = 13
	};

	enum AiMissileType : int {
		AI_PROTON_TIER1 = 16,
		AI_PROTON_TIER2 = 17,
		AI_PROTON_TIER3 = 18,
		AI_PROTON_TIER4 = 19,
		AI_PROTON_TIER5 = 20,
	};

	static int getLauncherAmmoType(const String& dataName) {
		switch (dataName.hashCode()) {
		case String::hashCode("wpn_launcher_concussion_mk1"):
			return PlayerMissileType::CONCUSSION_MK1;
		case String::hashCode("wpn_launcher_concussion_mk2"):
			return PlayerMissileType::CONCUSSION_MK2;
		case String::hashCode("wpn_launcher_concussion_mk3"):
			return PlayerMissileType::CONCUSSION_MK3;
		case String::hashCode("wpn_launcher_imagerec_mk1"):
			return PlayerMissileType::IMAGEREC_MK1;
		case String::hashCode("wpn_launcher_imagerec_mk2"):
			return PlayerMissileType::IMAGEREC_MK2;
		case String::hashCode("wpn_launcher_proton_mk1"):
			return PlayerMissileType::PROTON_MK1;
		case String::hashCode("wpn_launcher_proton_mk2"):
			return PlayerMissileType::PROTON_MK2;
		case String::hashCode("wpn_launcher_proton_mk3"):
			return PlayerMissileType::PROTON_MK3;
		case String::hashCode("wpn_launcher_proton_mk4"):
			return PlayerMissileType::PROTON_MK4;
		case String::hashCode("wpn_launcher_seismic_mk1"):
			return PlayerMissileType::SEISMIC_MK1;
		case String::hashCode("wpn_launcher_seismic_mk2"):
			return PlayerMissileType::SEISMIC_MK2;
		case String::hashCode("wpn_launcher_seismic_mk3"):
			return PlayerMissileType::SEISMIC_MK3;
		case String::hashCode("wpn_launcher_spacebomb_mk1"):
			return PlayerMissileType::SPACEBOMB_MK1;
		case String::hashCode("wpn_launcher_spacebomb_mk2"):
			return PlayerMissileType::SPACEBOMB_MK2;
		default:
			return -1;
		}
	}

	static int getMissileAmmoType(uint32 objectCRC) {
		switch (objectCRC) {
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_concussion_missile_mk1.iff"):
			return PlayerMissileType::CONCUSSION_MK1;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_concussion_missile_mk2.iff"):
			return PlayerMissileType::CONCUSSION_MK2;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_concussion_missile_mk3.iff"):
			return PlayerMissileType::CONCUSSION_MK3;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_imagerec_missile_mk1.iff"):
			return PlayerMissileType::IMAGEREC_MK1;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_imagerec_missile_mk2.iff"):
			return PlayerMissileType::IMAGEREC_MK2;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_proton_missile_mk1.iff"):
			return PlayerMissileType::PROTON_MK1;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_proton_missile_mk2.iff"):
			return PlayerMissileType::PROTON_MK2;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_proton_missile_mk3.iff"):
			return PlayerMissileType::PROTON_MK3;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_proton_missile_mk4.iff"):
			return PlayerMissileType::PROTON_MK4;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_seismic_missile_mk1.iff"):
			return PlayerMissileType::SEISMIC_MK1;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_seismic_missile_mk2.iff"):
			return PlayerMissileType::SEISMIC_MK2;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_seismic_missile_mk3.iff"):
			return PlayerMissileType::SEISMIC_MK3;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_spacebomb_missile_mk1.iff"):
			return PlayerMissileType::SPACEBOMB_MK1;
		case String::hashCode("object/tangible/ship/crafted/weapon/missile/wpn_spacebomb_missile_mk2.iff"):
			return PlayerMissileType::SPACEBOMB_MK2;
		default:
			return -1;
		}
	}

protected:
	int missileType;

	String dataName;

	float minTime;
	float maxTime;
	float serverSpeed;
	float clientSpeed;
	float countermeasureFactor;
	float targetAquisitionTime;
	float targetAquisitionAngle;

	String appearance;
	String trail;
	String fireEffect;
	String hitEffect;
	String counterEffect;

	int counterDifficulty;

public:
	ShipMissileData() : Object() {
		missileType = -1;

		minTime = 0;
		maxTime = 0;

		serverSpeed = 0;
		clientSpeed = 0;
		countermeasureFactor = 0.f;
		targetAquisitionTime = 0;
		targetAquisitionAngle = 0;

		counterDifficulty = 0;
	}

	void readObject(DataTableRow* row) {
		if (row == nullptr || row->getCellsSize() < 15) {
			return;
		}

		row->getCell(0)->getValue(missileType);
		row->getCell(1)->getValue(dataName);
		row->getCell(2)->getValue(maxTime);
		row->getCell(3)->getValue(minTime);
		row->getCell(4)->getValue(serverSpeed);
		row->getCell(5)->getValue(clientSpeed);
		row->getCell(6)->getValue(countermeasureFactor);
		row->getCell(7)->getValue(targetAquisitionTime);
		row->getCell(8)->getValue(targetAquisitionAngle);
		row->getCell(9)->getValue(appearance);
		row->getCell(10)->getValue(trail);
		row->getCell(11)->getValue(fireEffect);
		row->getCell(12)->getValue(hitEffect);
		row->getCell(13)->getValue(counterEffect);
		row->getCell(14)->getValue(counterDifficulty);
	}

	// set
	void setMissileType(int value) {
		missileType = value;
	}

	void setDataName(const String& value) {
		dataName = value;
	}

	void setMinTime(int value) {
		minTime = value;
	}

	void setMaxTime(int value) {
		maxTime = value;
	}

	void setServerSpeed(int value) {
		serverSpeed = value;
	}

	void setClientSpeed(int value) {
		clientSpeed = value;
	}

	void setCountermeasureFactor(float value) {
		countermeasureFactor = value;
	}

	void setTargetAquisitionTime(int value) {
		targetAquisitionTime = value;
	}

	void setTargetAquisitionAngle(int value) {
		targetAquisitionAngle = value;
	}

	void setAppearance(const String& value) {
		appearance = value;
	}

	void setTrail(const String& value) {
		trail = value;
	}

	void setFireEffect(const String& value) {
		fireEffect = value;
	}

	void setHitEffect(const String& value) {
		hitEffect = value;
	}

	void setCounterEffect(const String& value) {
		counterEffect = value;
	}

	void setCounterDifficulty(int value) {
		counterDifficulty = value;
	}

	// get
	int getMissileType() const {
		return missileType;
	}

	const String& getDataName() const {
		return dataName;
	}

	float getMinTime() const {
		return minTime;
	}

	float getMaxTime() const {
		return maxTime;
	}

	float getServerSpeed() const {
		return serverSpeed;
	}

	float getClientSpeed() const {
		return clientSpeed;
	}

	float getCountermeasureFactor() const {
		return countermeasureFactor;
	}

	float getTargetAquisitionTime() const {
		return targetAquisitionTime;
	}

	float getTargetAquisitionAngle() const {
		return targetAquisitionAngle;
	}

	const String& getAppearance() const {
		return appearance;
	}

	const String& getTrail() const {
		return trail;
	}

	const String& getFireEffect() const {
		return fireEffect;
	}

	const String& getHitEffect() const {
		return hitEffect;
	}

	const String& getCounterEffect() const {
		return counterEffect;
	}

	int getCounterDifficulty() const {
		return counterDifficulty;
	}
};

#endif //SHIPMISSILEDATA_H_
