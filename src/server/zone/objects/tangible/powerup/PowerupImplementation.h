#ifndef POWERUPIMPLEMENTATION_H_
#define POWERUPIMPLEMENTATION_H_
 
#include "engine/engine.h"
#include "Powerup.h"
 
class Zone;
class Player;
 
class PowerupImplementation : public PowerupServant {
protected:
	int type;
	int subType;
	
	int powerup0Type;
	float powerup0Value;
	int powerup1Type;
	float powerup1Value;
	int powerup2Type;
	float powerup2Value;
	
	int uses;
	
public:
	static const int MELEE = 1;
	static const int RANGED = 2;
	static const int MINE = 3;
	static const int THROWN = 4;
	
	static const int BARREL = 1;
	static const int COUPLER = 2;
	static const int GRIP = 3;
	static const int MUZZLE = 4;
	static const int SCOPE = 5;
	static const int STOCK = 6;

public:
	PowerupImplementation(uint64 objID, uint32 tempCRC, const unicode& n, const string& tempn);
	PowerupImplementation(uint64 objID);
	
	virtual ~PowerupImplementation();

	void initialize();

	void generateName();
	
	void generateAttributes(SceneObject* obj);
	
	void parseItemAttributes();
	
	void addAttributes(AttributeListMessage* alm);
	
	void setPowerupStats(int modifier);
	
	void apply(Weapon* weapon);
	
	void remove(Player* player);

	inline void setPowerupType(int value) {
		type = value;
		string name = "type";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline void setPowerupSubType(int value) {
		subType = value;
		string name = "subType";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline void setPowerup0Type(int value) {
		powerup0Type = value;
		string name = "powerup0Type";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline void setPowerup1Type(int value) {
		powerup1Type = value;
		string name = "powerup1Type";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline void setPowerup2Type(int value) {
		powerup2Type = value;
		string name = "powerup2Type";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline void setPowerup0Value(float value) {
		powerup0Value = value;
		string name = "powerup0Value";
		itemAttributes->setFloatAttribute(name, value);
	}
	
	inline void setPowerup1Value(float value) {
		powerup1Value = value;
		string name = "powerup1Value";
		itemAttributes->setFloatAttribute(name, value);
	}
	
	inline void setPowerup2Value(float value) {
		powerup2Value = value;
		string name = "powerup2Value";
		itemAttributes->setFloatAttribute(name, value);
	}
	
	inline void setPowerupUses(int value) {
		uses = value;
		string name = "uses";
		itemAttributes->setIntAttribute(name, value);
	}
	
	inline int getPowerup0Type() {
		return powerup0Type;
	}
	inline int getPowerup1Type() {
		return powerup1Type;
	}
	inline int getPowerup2Type() {
		return powerup2Type;
	}
	inline float getPowerup0Value() {
		return powerup0Value;
	}
	inline float getPowerup1Value() {
		return powerup1Value;
	}
	inline float getPowerup2Value() {
		return powerup2Value;
	}
	inline int getPowerupUses() {
		return uses;
	}
	inline int getPowerupType() {
		return type;
	}
	inline int getPowerupSubType() {
		return subType;
	}

};
 
#endif

