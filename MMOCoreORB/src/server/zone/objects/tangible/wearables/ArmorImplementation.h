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

	int armorStyle;

public:

	static const int LIGHT = 0x01;
	static const int MEDIUM = 0x02;
	static const int HEAVY = 0x03;

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

	static const int COMPOSITE = 1;
	static const int ASSAULTTROOPER = 2;
	static const int BONE = 3;
	static const int BOUNTYHUNTERLOOTED = 4;
	static const int BOUNTYHUNTER = 5;
	static const int CHITIN= 6;
	static const int CLONETROOPERIMPERIAL = 7;
	static const int CLONETROOPERNEUTRAL = 8;
	static const int CLONETROOPERREBEL = 9;
	static const int ITHORIANDEFENDER = 10;
	static const int ITHORIANGUARDIAN = 11;
	static const int ITHORIANSENTINEL = 12;
	static const int WOOKIEBLACKMOUNTAIN = 13;
	static const int WOOKIECERIMONIAL = 14;
	static const int WOOKIEHUNTING = 15;
	static const int MANDALORIANIMPERIAL = 16;
	static const int MANDALORIAN = 17;
	static const int MANDALORIANREBEL = 18;
	static const int MARAUDER1 = 19;
	static const int MARAUDER2 = 20;
	static const int MARAUDER3 = 21;
	static const int REBELMARINE = 22;
	static const int SCOUTTROOPER = 23;
	static const int NIGHTSISTER = 24;
	static const int PADDED = 25;
	static const int REBELASSAULT = 26;
	static const int REBELBATTLE = 27;
	static const int RIS = 28;
	static const int SINGINGMOUNTAIN = 29;
	static const int STORMTROOPER = 30;
	static const int TANTEL = 31;
	static const int UBESE = 32;
	static const int MABARI = 33;


public:
	ArmorImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);
	ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);

	void parseItemAttributes();

	void init();

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void updateCraftingValues(DraftSchematic* draftSchematic);
	void generateSockets(DraftSchematic* draftSchematic);
	void addSpecialProtectionBasedOnType(DraftSchematic* draftSchematic);
	void setCraftingKinetic(DraftSchematic* draftSchematic, float base);
	void setCraftingEnergy(DraftSchematic* draftSchematic, float base);
	void setCraftingElectrical(DraftSchematic* draftSchematic, float base);
	void setCraftingStun(DraftSchematic* draftSchematic, float base);
	void setCraftingBlast(DraftSchematic* draftSchematic, float base);
	void setCraftingHeat(DraftSchematic* draftSchematic, float base);
	void setCraftingCold(DraftSchematic* draftSchematic, float base);
	void setCraftingAcid(DraftSchematic* draftSchematic, float base);
	void setCraftingRestrain(DraftSchematic* draftSchematic, float base);

	void decay(float decayRate);

	void generateAttributes(SceneObject* obj);

	void sliceArmor(Player* player);

	int sliceArmorEffectiveness(int min, int max);

	int sliceArmorEncumbrance(int min, int max);

	void setArmorStats(int modifier);

	int addSkillMod(int skillModType, int skillModValue);

	void setSocket(int index, int type, int value);
	void setSocketType(int index, int type);
	void setSocketValue(int index, int type);

	int getSocketType(int index);
	int getSocketValue(int index);

	void addAttributes(AttributeListMessage* alm);

	void setArmorPiece();

	//void setArmorType();

	void setArmorType(int type) {
		armorType = type;
	}

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

	inline int getArmorType() {
		return armorType;
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

	inline int getArmorStyle() {
		return armorStyle;
	}

	inline void setArmorStyle() {
		switch (objectCRC) {
		case 0x9AF51EAA:
		case 0x7B476F26:
		case 0x13A4DA11:
		case 0x63719F82:
		case 0x4DB0192D:
		case 0x3D655CBE:
		case 0x2C35FFA2:
		case 0xC294C432:
		case 0xDB91E9DB:
			armorStyle = COMPOSITE;
			setElectricityIsSpecial(true);
			break;
		case 0xEADBF3ED:
		case 0xF14843C9:
		case 0xDDFD80F6:
		case 0xAD28C565:
		case 0x75EECEBE:
		case 0x053B8B2D:
		case 0x5C1B12E5:
		case 0xFACA13A1:
		case 0x48C9992B:
			armorStyle = ASSAULTTROOPER;
			break;
		case 0x46BE7E7F:
		case 0xD3C024EE:
		case 0x7C53DF9C:
		case 0xC0F6A8B3:
		case 0x0C869A0F:
		case 0x2E5FEF07:
		case 0x5E8AAA94:
		case 0xF07E9F77:
		case 0xA17B3218:
		case 0x2FD71E30:
			armorStyle = BONE;
			setEnergyIsSpecial(true);
			break;
		case 0x30DB6875:
		case 0x4FD29AA3:
		case 0xE37785C9:
		case 0x93A2C05A:
		case 0x17573C24:
		case 0x678279B7:
		case 0x861B987D:
		case 0x9873E13B:
		case 0x219DF586:
			armorStyle = BOUNTYHUNTERLOOTED;
			break;
		case 0x6B80CA32:
		case 0x4DD537AA:
		case 0xEB09A2AF:
		case 0x9BDCE73C:
		case 0x4F78B79C:
		case 0x3FADF20F:
		case 0xDD402B3A:
		case 0xC05C6A83:
		case 0xB233F039:
			armorStyle = BOUNTYHUNTER;
			break;
		case 0x286C8D19:
		case 0x232BEF27:
		case 0x3E8BDF01:
		case 0x4E5E9A92:
		case 0xCB5B391E:
		case 0xBB8E7C8D:
		case 0x9EAC6C11:
		case 0x447FE401:
		case 0x74EA10A3:
		case 0x92F3A5A7: // Acklay Variant
		case 0x2151257A:
		case 0x33173AA9:
		case 0x43C27F3A:
		case 0x667317CD:
		case 0x16A6525E:
		case 0x243344AF:
		case 0xE957CAD2:
		case 0x85DDF66B:
			armorStyle = CHITIN;
			setKineticIsSpecial(true);
			break;
		case 0x6D79791D:
		case 0xE5305A03:
		case 0x083CC01D:
		case 0x78E9858E:
		case 0xB2F0053C:
		case 0xC22540AF:
		case 0xDBB99815:
		case 0x3DD4D823:
		case 0xDA62A4A1:
			armorStyle = CLONETROOPERIMPERIAL;
			break;
		case 0x7F0A7908:
		case 0xDF0DA91A:
		case 0x3EAF3505:
		case 0x4E7A7090:
		case 0xEFB13B1E:
		case 0x9F647E8D:
		case 0xC9CA9800:
		case 0x6095E601:
		case 0x6FDA2C47:
			armorStyle = CLONETROOPERNEUTRAL;
			break;
		case 0x7795247C:
		case 0x7D30AB00:
		case 0x87FAACBB:
		case 0xF72FE928:
		case 0x25DFFE6F:
		case 0x550ABBFC:
		case 0xC155C574:
		case 0xAAFB2370:
		case 0xD1530337:
			armorStyle = CLONETROOPERREBEL;
			break;
		case 0x353894F0:
		case 0x7BB4F363:
		case 0x174E6BA2:
		case 0x679B2E31:
		case 0xB405DCF1:
		case 0xC4D09962:
		case 0x83F875F8:
		case 0x3B2101EE:
		case 0xA4E6DFF1:
			armorStyle = ITHORIANDEFENDER;
			setKineticIsSpecial(true);
			break;
		case 0x83C052A4:
		case 0x5D06B751:
		case 0x4830FF6E:
		case 0x38E5BAFD:
		case 0x8A49064B:
		case 0xFA9C43D8:
		case 0x3500B3AC:
		case 0x056DDB54:
		case 0x7B79F3C1:
			armorStyle = ITHORIANGUARDIAN;
			setKineticIsSpecial(true);
			break;
		case 0x24E0753F:
		case 0x169D55D8:
		case 0x877F6265:
		case 0xF7AA27F6:
		case 0xA011206F:
		case 0xD0C465FC:
		case 0x92209437:
		case 0x2F35FD70:
		case 0xECE5898D:
			armorStyle = ITHORIANSENTINEL;
			setKineticIsSpecial(true);
			break;
		case 0x9F9C111B:
		case 0xE55C868E:
		case 0x8654BD2A:
		case 0xF681F8B9:
		case 0x8F0F72D8:
		case 0xFFDA374B:
		case 0x002BAFC7:
			armorStyle = WOOKIEBLACKMOUNTAIN;
			setKineticIsSpecial(true);
			break;
		case 0x8BA52D06:
		case 0x09B81A0F:
		case 0x419E1070:
		case 0x314B55E3:
		case 0x066FE844:
		case 0x76BAADD7:
		case 0x894B355B:
			armorStyle = WOOKIECERIMONIAL;
			setKineticIsSpecial(true);
			break;
		case 0xE11CC6F9:
		case 0x92DCF514:
		case 0x82B60ABA:
		case 0xF2634F29:
		case 0x7EBC9404:
		case 0x0E69D197:
		case 0xF198491B:
			armorStyle = WOOKIEHUNTING;
			setKineticIsSpecial(true);
			break;
		case 0x152CDE9B:
		case 0x1129C977:
		case 0x9B27B642:
		case 0xEBF2F3D1:
		case 0x81D8477B:
		case 0xF10D02E8:
		case 0xA3EC3F93:
		case 0x0EFC9A64:
			armorStyle = MANDALORIANIMPERIAL;
			setBlastIsSpecial(true);
			break;
		case 0x37A4683E:
		case 0x24525C1C:
		case 0x82309ECC:
		case 0xF2E5DB5F:
		case 0xF828E204:
		case 0x88FDA797:
		case 0x81648936:
		case 0x770C3F1B:
		case 0xA1D10ED0:
			armorStyle = MANDALORIAN;
			setBlastIsSpecial(true);
			break;
		case 0x30E02815:
		case 0xDC7CA03F:
		case 0xD837E5C9:
		case 0xA8E2A05A:
		case 0xA84E9AD5:
		case 0xD89BDF46:
		case 0x8620C91D:
		case 0x276A47CA:
		case 0x836563AB:
			armorStyle = MANDALORIANREBEL;
			setBlastIsSpecial(true);
			break;
		case 0x2658E2C1:
		case 0xAE077DF7:
		case 0x366AA70B:
		case 0x46BFE298:
		case 0x0C2BDEA6:
		case 0x7CFE9B35:
		case 0x909803C9:
		case 0x830F03B9:
		case 0xDE3A814C:
			armorStyle = MARAUDER1;
			break;
		case 0x2E43C7CB:
		case 0x96722E10:
		case 0x0B4740B3:
		case 0x7B920520:
		case 0xC4338DE5:
		case 0xB4E6C876:
		case 0x988326C3:
		case 0x4B1750FA:
		case 0xD00E14C9:
			armorStyle = MARAUDER2;
			break;
		case 0x3B0E1963:
		case 0x29B524CD:
		case 0x81A11F4D:
		case 0xE3E316B6:
		case 0x93365325:
		case 0x83C44324:
		case 0xF31106B7:
		case 0x9F75C5C5:
		case 0x0CE09E3B:
		case 0x29A29327:
			armorStyle = MARAUDER3;
			break;
		case 0x1890B6F4:
		case 0x98A41A65:
		case 0x16825F91:
		case 0x66571A02:
		case 0x7CF0F246:
		case 0x0C25B7D5:
		case 0xAE5057FC:
		case 0xF3D42F59:
		case 0x0A06D625:
		case 0xCC2DF763:
			armorStyle = REBELMARINE;
			break;
		case 0xDFD90681:
		case 0xB0CD9C67:
		case 0x1CFFEA0D:
		case 0x6C2AAF9E:
		case 0x2ECFB890:
		case 0x5E1AFD03:
		case 0x6919E789:
		case 0xA1EB65BF:
		case 0x1D93C91E:
			armorStyle = SCOUTTROOPER;
			break;
		case 0x2E943BD2:
			armorStyle = NIGHTSISTER;
			break;
		case 0x1179DA8E:
		case 0x374CE8CA:
		case 0xDD27D59E:
		case 0xADF2900D:
		case 0xAFBBA6BE:
		case 0xDF6EE32D:
		case 0xA7B93B86:
		case 0x209F7BA1:
		case 0x147FA032:
			armorStyle = PADDED;
			setBlastIsSpecial(true);
			break;
		case 0xF11ED8BD:
		case 0x59A76FA0:
		case 0x7F8CC0E7:
		case 0x0F598574:
		case 0xFC03B2DE:
		case 0x8CD6F64D:
		case 0x47DE39B5:
		case 0x73276FC1:
		case 0x29262900:
			armorStyle = REBELASSAULT;
			break;
		case 0x895B64E3:
		case 0x125FE423:
		case 0xFC8C6EB8:
		case 0x8C592B2B:
		case 0x98E22BE9:
		case 0xE8376E7A:
		case 0x2F9B85EB:
		case 0x17C6F6F6:
		case 0xE85B36EA:
			armorStyle = REBELBATTLE;
			break;

		case 0x2C06918C:
		case 0x6C18B779:
		case 0x47933CDD:
		case 0x3746794E:
		case 0x11C508F6:
		case 0x61104D65:
		case 0x9AC67084:
		case 0x9EE1D5E9:
		case 0x43240F82:
			armorStyle = RIS;
			setKineticIsSpecial(true);
			break;
		case 0xF83A5E23:
		case 0x88EF1BB0:
		case 0x3DD6C635:
		case 0x4D0383A6:
			armorStyle = SINGINGMOUNTAIN;
			break;
		case 0xC499637D:
		case 0x0F22790E:
		case 0x3BC0061C:
		case 0x4B15438F:
		case 0x97474F75:
		case 0xE7920AE6:
		case 0x72598275:
		case 0x1863926A:
		case 0x7833E9D6:
		case 0x347F64A4:
		case 0x42ED86AA:
		case 0xB46EC87C:
			armorStyle = STORMTROOPER;
			break;
		case 0x56EE9000:
		case 0x115816CF:
		case 0x60AC7BEC:
		case 0x10793E7F:
		case 0xA8E6DF13:
		case 0xD8339A80:
		case 0xE02E7108:
		case 0x27C2020C:
		case 0x36A996F5:
		case 0x3E8FDEDE:
		case 0x67A5B2AE:
		case 0x01D62C68:
			armorStyle = TANTEL;
			setEnergyIsSpecial(true);
			break;
		case 0xE9F5A650:
		case 0xDC4ECF46:
		case 0xF6158787:
		case 0x86C0C214:
		case 0x5F354758:
		case 0x3EA9A48D:
		case 0x47F2F8C3:
		case 0x7240A9E8:
		case 0xCB32836B:
			armorStyle = UBESE;
			setKineticIsSpecial(true);
			break;
		case 0x1EF5A158:
		case 0xC4EA554A:
		case 0xA8354050:
		case 0x1E5FA69F:
		case 0x8A927B5C:
		case 0x9793D045:
			armorStyle = MABARI;
			setHeatIsSpecial(true);
			setBlastIsSpecial(true);
			break;
		}
	}

	//Event Handlers
	void onBroken();
	void onEncumbranceSliced(Player* slicer, uint8 percentage);
	void onEffectivenessSliced(Player* slicer, uint8 percentage);
	void onSlicingFailure(Player* slicer);

	//Actions
	void slice(Player* slicer);
	void sliceEncumbrance(Player* slicer, uint8 percentage);
	void sliceEffectiveness(Player* slicer, uint8 percentage);

	void conditionReduction(float damage);
};
#endif /*ARMORIMPLEMENTATION_H_*/
