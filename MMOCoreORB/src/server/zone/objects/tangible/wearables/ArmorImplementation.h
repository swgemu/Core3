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

#ifndef ARMORIMPLEMENTATION_H_
#define ARMORIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"

#include "Armor.h"

class ArmorImplementation : public ArmorServant {
private:
	int rating;

	int healthEncumbrance;
	int actionEncumbrance;
	int mindEncumbrance;

	float kinetic;
	bool kineticIsSpecial;

	float energy;
	bool energyIsSpecial;

	float electricity;
	bool electricityIsSpecial;

	float stun;
	bool stunIsSpecial;

	float blast;
	bool blastIsSpecial;

	float heat;
	bool heatIsSpecial;

	float cold;
	bool coldIsSpecial;

	float acid;
	bool acidIsSpecial;

	float lightSaber;
	bool lightSaberIsSpecial;

	int armorType;

	bool sliced;

	int skillMod0Type;
	int skillMod0Value;

	int skillMod1Type;
	int skillMod1Value;

	int skillMod2Type;
	int skillMod2Value;

	int sockets;

	int socket0Type;
	int socket0Value;

	int socket1Type;
	int socket1Value;

	int socket2Type;
	int socket2Value;

	int socket3Type;
	int socket3Value;

	bool firstCraftingUpdate;

	float specialBase;

public:

	static const int LIGHT = 0x10;
	static const int MEDIUM = 0x20;
	static const int HEAVY = 0x30;

	static const int CHEST = 1;
	static const int HAND = 2;
	static const int BRACERL = 3;
	static const int BICEPL = 4;
	static const int BRACERR = 5;
	static const int BICEPR = 6;
	static const int LEG = 7;
	static const int FOOT = 8;
	static const int HEAD = 9;
	static const int BELT = 10;

public:
	ArmorImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);
	ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);

	void parseItemAttributes();

	void initialize();

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void updateCraftingValues(DraftSchematic* draftSchematic);
	void generateSockets(DraftSchematic* draftSchematic);
	void setCraftingKinetic(DraftSchematic* draftSchematic);
	void setCraftingEnergy(DraftSchematic* draftSchematic);
	void setCraftingElectrical(DraftSchematic* draftSchematic);
	void setCraftingStun(DraftSchematic* draftSchematic);
	void setCraftingBlast(DraftSchematic* draftSchematic);
	void setCraftingHeat(DraftSchematic* draftSchematic);
	void setCraftingCold(DraftSchematic* draftSchematic);
	void setCraftingAcid(DraftSchematic* draftSchematic);
	void setCraftingRestrain(DraftSchematic* draftSchematic);

	void decayArmor(int decayRate);

	void generateAttributes(SceneObject* obj);

	void sliceArmor(Player* player);

	int sliceArmorEffectiveness(int min, int max);

	int sliceArmorEncumbrance(int min, int max);

	void repairArmor(Player* player);

	void setArmorStats(int modifier);

	int addSkillMod(int skillModType, int skillModValue);

	void setSocket(int index, int type, int value);
	void setSocketType(int index, int type);
	void setSocketValue(int index, int type);

	int getSocketType(int index);
	int getSocketValue(int index);

	void addAttributes(AttributeListMessage* alm);

	void setArmorPiece();

	void setArmorType();

	bool isVunerableTo(String type);

	// setters
	inline void setRating(int rat) {
		rating = rat;
		String name = "rating";
		itemAttributes->setIntAttribute(name, rat);
	}

	inline void setHealthEncumbrance(int healthEnc) {
		healthEncumbrance = healthEnc;
		String name = "healthEncumberence";
		itemAttributes->setIntAttribute(name, healthEnc);
	}

	inline void setActionEncumbrance(int actionEnc) {
		actionEncumbrance = actionEnc;
		String name = "actionEncumberence";
		itemAttributes->setIntAttribute(name, actionEnc);
	}

	inline void setMindEncumbrance(int mindEnc) {
		mindEncumbrance = mindEnc;
		String name = "mindEncumberence";
		itemAttributes->setIntAttribute(name, mindEnc);
	}

	inline void setKinetic(float kin) {
		kinetic = kin;
		String name = "kinetic";
		itemAttributes->setFloatAttribute(name, kin);
	}

	inline void setKineticIsSpecial(bool kineticIsSpec) {
		kineticIsSpecial = kineticIsSpec;
		if (kineticIsSpec) {
			String name = "kineticIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setEnergy(float ene) {
		energy = ene;
		String name = "energy";
		itemAttributes->setFloatAttribute(name, ene);
	}

	inline void setEnergyIsSpecial(bool energyIsSpec) {
		energyIsSpecial = energyIsSpec;
		if (energyIsSpec) {
			String name = "energyIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setElectricity(float ele) {
		electricity = ele;
		String name = "electricity";
		itemAttributes->setFloatAttribute(name, ele);
	}

	inline void setElectricityIsSpecial(bool electricityIsSpec) {
		electricityIsSpecial = electricityIsSpec;
		if (electricityIsSpec) {
			String name = "electricityIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setStun(float stu) {
		stun = stu;
		String name = "stun";
		itemAttributes->setFloatAttribute(name, stu);
	}

	inline void setStunIsSpecial(bool stunIsSpec) {
		stunIsSpecial = stunIsSpec;
		if (stunIsSpec) {
			String name = "stunIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setBlast(float blst) {
		blast = blst;
		String name = "blast";
		itemAttributes->setFloatAttribute(name, blst);
	}

	inline void setBlastIsSpecial(bool blastIsSpec) {
		blastIsSpecial = blastIsSpec;
		if (blastIsSpec) {
			String name = "blastIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setHeat(float hot) {
		heat = hot;
		String name = "heat";
		itemAttributes->setFloatAttribute(name, hot);
	}

	inline void setHeatIsSpecial(bool heatIsSpec) {
		heatIsSpecial = heatIsSpec;
		if (heatIsSpec) {
			String name = "heatIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setCold(float notHot) {
		cold = notHot;
		String name = "cold";
		itemAttributes->setFloatAttribute(name, notHot);
	}

	inline void setColdIsSpecial(bool coldIsSpec) {
		coldIsSpecial = coldIsSpec;
		if (coldIsSpec) {
			String name = "coldIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setAcid(float aci) {
		acid = aci;
		String name = "acid";
		itemAttributes->setFloatAttribute(name, aci);
	}

	inline void setAcidIsSpecial(bool acidIsSpec) {
		acidIsSpecial = acidIsSpec;
		if (acidIsSpec) {
			String name = "acidIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setLightSaber(float lightSab) {
		lightSaber = lightSab;
		String name = "lightSaber";
		itemAttributes->setFloatAttribute(name, lightSab);
	}

	inline void setLightSaberIsSpecial(bool lightSaberIsSpec) {
		lightSaberIsSpecial = lightSaberIsSpec;
		if (lightSaberIsSpec) {
			String name = "lightsaberIsSpecial";
			itemAttributes->setBooleanAttribute(name, true);
		}
	}

	inline void setArmorPiece(int armorSlot) {
		String name = "armorType";
		armorType = armorSlot;
		itemAttributes->setIntAttribute(name, armorSlot);

		switch (armorSlot) {
		case CHEST:
			objectSubType = TangibleObjectImplementation::BODYARMOR;
			break;
		case HAND:
			objectSubType = TangibleObjectImplementation::HANDARMOR;
			break;
		case BRACERL:
		case BRACERR:
		case BICEPL:
		case BICEPR:
			objectSubType = TangibleObjectImplementation::ARMARMOR;
			break;
		case LEG:
			objectSubType = TangibleObjectImplementation::LEGARMOR;
			break;
		case FOOT:
			objectSubType = TangibleObjectImplementation::FOOTARMOR;
			break;
		case HEAD:
			objectSubType = TangibleObjectImplementation::HEADARMOR;
			break;
		case BELT:
			objectSubType = TangibleObjectImplementation::MISCARMOR;
			break;
		}
	}

	inline void setSliced(bool hacked) {
		sliced = hacked;
		String key = "sliced";
		itemAttributes->setBooleanAttribute(key, hacked);
	}

	inline void setSkillMod0Type(int skillModType) {
		skillMod0Type = skillModType;
		String name = "skillMod0Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod1Type(int skillModType) {
		skillMod1Type = skillModType;
		String name = "skillMod1Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod2Type(int skillModType) {
		skillMod2Type = skillModType;
		String name = "skillMod2Type";
		itemAttributes->setIntAttribute(name, skillModType);
	}

	inline void setSkillMod0Value(int skillModValue) {
		skillMod0Value = skillModValue;
		String name = "skillMod0Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSkillMod1Value(int skillModValue) {
		skillMod1Value = skillModValue;
		String name = "skillMod1Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSkillMod2Value(int skillModValue) {
		skillMod2Value = skillModValue;
		String name = "skillMod2Value";
		itemAttributes->setIntAttribute(name, skillModValue);
	}

	inline void setSockets(int socket) {
		sockets = socket;
		String key = "sockets";
		itemAttributes->setIntAttribute(key, socket);
	}

	inline void setSocket0Type(int socketType) {
		socket0Type = socketType;
		String key = "socket0Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket1Type(int socketType) {
		socket1Type = socketType;
		String key = "socket1Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket2Type(int socketType) {
		socket2Type = socketType;
		String key = "socket2Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket3Type(int socketType) {
		socket3Type = socketType;
		String key = "socket3Type";
		itemAttributes->setIntAttribute(key, socketType);
	}

	inline void setSocket0Value(int socketValue) {
		socket0Value = socketValue;
		String key = "socket0Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline void setSocket1Value(int socketValue) {
		socket1Value = socketValue;
		String key = "socket1Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}

	inline void setSocket2Value(int socketValue) {
		socket2Value = socketValue;
		String key = "socket2Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}


	inline void setSocket3Value(int socketValue) {
		socket3Value = socketValue;
		String key = "socket3Value";
		itemAttributes->setIntAttribute(key, socketValue);
	}


	// getters
	inline int getRating() {
		return rating;
	}

	inline int getMaxCondition() {
		return maxCondition;
	}

	inline int getHealthEncumbrance() {
		return healthEncumbrance;
	}

	inline int getActionEncumbrance() {
		return actionEncumbrance;
	}

	inline int getMindEncumbrance() {
		return mindEncumbrance;
	}

	inline float getKinetic() {
		return kinetic;
	}

	inline bool isKineticSpecial() {
		return kineticIsSpecial;
	}

	inline float getEnergy() {
		return energy;
	}

	inline bool isEnergySpecial() {
		return energyIsSpecial;
	}

	inline float getElectricity() {
		return electricity;
	}

	inline bool isElectricitySpecial() {
		return electricityIsSpecial;
	}

	inline float getStun() {
		return stun;
	}

	inline bool isStunSpecial() {
		return stunIsSpecial;
	}

	inline float getBlast() {
		return blast;
	}

	inline bool isBlastSpecial() {
		return blastIsSpecial;
	}

	inline float getHeat() {
		return heat;
	}

	inline bool isHeatSpecial() {
		return heatIsSpecial;
	}

	inline float getCold() {
		return cold;
	}

	inline bool isColdSpecial() {
		return coldIsSpecial;
	}

	inline float getAcid() {
		return acid;
	}

	inline bool isAcidSpecial() {
		return acidIsSpecial;
	}

	inline float getLightSaber() {
		return lightSaber;
	}

	inline bool isLightSaberSpecial() {
		return lightSaberIsSpecial;
	}

	inline int getType() {
		return armorType;
	}

	inline bool isSliced() {
		return sliced;
	}

	inline int getSkillMod0Type() {
		return skillMod0Type;
	}

	inline int getSkillMod1Type() {
		return skillMod1Type;
	}

	inline int getSkillMod2Type() {
		return skillMod2Type;
	}

	inline int getSkillMod0Value() {
		return skillMod0Value;
	}

	inline int getSkillMod1Value() {
		return skillMod1Value;
	}

	inline int getSkillMod2Value() {
		return skillMod2Value;
	}

	inline int getSockets() {
		return sockets;
	}

	inline int getSocket0Type() {
		return socket0Type;
	}

	inline int getSocket1Type() {
		return socket1Type;
	}

	inline int getSocket2Type() {
		return socket2Type;
	}

	inline int getSocket3Type() {
		return socket3Type;
	}

	inline int getSocket0Value() {
		return socket0Value;
	}

	inline int getSocket1Value() {
		return socket1Value;
	}

	inline int getSocket2Value() {
		return socket2Value;
	}

	inline int getSocket3Value() {
		return socket3Value;
	}

	inline bool isComposite() {
		switch(objectCRC) {
		case 0x9AF51EAA:
		case 0x7B476F26:
		case 0x13A4DA11:
		case 0x63719F82:
		case 0x4DB0192D:
		case 0x3D655CBE:
		case 0x2C35FFA2:
		case 0xC294C432:
		case 0xDB91E9DB:
			return true;
		default:
			return false;
		}
	}
};
#endif /*ARMORIMPLEMENTATION_H_*/
