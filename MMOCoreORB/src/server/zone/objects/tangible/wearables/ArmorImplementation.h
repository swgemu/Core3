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

	float kinetic;
	float energy;
	float electricity;
	float stun;
	float blast;
	float heat;
	float cold;
	float acid;
	float lightSaber;

	/*
	 * Associated armor piece:  Helmet, Chestplate, etc
	 */
	int armorPiece;

	/*
	 * Associated armor type:   Composite, Mabari, etc
	 */
	int armorStyle;

	Vector<String> specialResistsVector;
	Vector<String> vunerabilitesVector;

	float specialBase;

public:

	static const int LIGHT = 0x1;
	static const int MEDIUM = 0x2;
	static const int HEAVY = 0x3;

	static const int CHEST = 0x100;
	static const int HAND = 0x101;
	static const int BRACERL = 0x102;
	static const int BICEPL = 0x103;
	static const int BRACERR = 0x104;
	static const int BICEPR = 0x105;
	static const int LEG = 0x106;
	static const int FOOT = 0x107;
	static const int HEAD = 0x108;
	static const int BELT = 0x109;

	static const int COMPOSITE = 0x1001;
	static const int ASSAULTTROOPER = 0x1002;
	static const int BONE = 0x1003;
	static const int BOUNTYHUNTERLOOTED = 0x1004;
	static const int BOUNTYHUNTER = 0x1005;
	static const int CHITIN= 0x1006;
	static const int CLONETROOPERIMPERIAL = 0x1007;
	static const int CLONETROOPERNEUTRAL = 0x1008;
	static const int CLONETROOPERREBEL = 0x1009;
	static const int ITHORIANDEFENDER = 0x100A;
	static const int ITHORIANGUARDIAN = 0x100B;
	static const int ITHORIANSENTINEL = 0x100C;
	static const int WOOKIEBLACKMOUNTAIN = 0x100D;
	static const int WOOKIECERIMONIAL = 0x100E;
	static const int WOOKIEHUNTING = 0x100F;
	static const int MANDALORIANIMPERIAL = 0x1010;
	static const int MANDALORIAN = 0x1011;
	static const int MANDALORIANREBEL =0x1012;
	static const int MARAUDER1 = 0x1013;
	static const int MARAUDER2 = 0x1014;
	static const int MARAUDER3 = 0x1015;
	static const int REBELMARINE = 0x1016;
	static const int SCOUTTROOPER = 0x1017;
	static const int NIGHTSISTER = 0x1018;
	static const int PADDED = 0x1019;
	static const int REBELASSAULT = 0x101A;
	static const int REBELBATTLE = 0x101B;
	static const int RIS = 0x101C;
	static const int SINGINGMOUNTAIN = 0x101D;
	static const int STORMTROOPER = 0x101E;
	static const int TANTEL = 0x101F;
	static const int UBESE = 0x1020;
	static const int MABARI = 0x1021;


public:
	ArmorImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);
	ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp = false);

	void init();

	void sendTo(Player* player, bool doClose = true);

	void sendRadialResponseTo(Player* player, ObjectMenuResponse* omr);

	void parseItemAttributes();

	void generateAttributes(SceneObject* obj);

	void addAttributes(AttributeListMessage* alm);

	void updateCraftingValues(DraftSchematic* draftSchematic);
	void calculateSpecalProtection(DraftSchematic* draftSchematic);

	void setProtection(DraftSchematic* draftSchematic, String type, float base);
	void setProtectionValue(String type, float value);

	void decay(float decayRate);

	void setArmorStats(int modifier);

	void setArmorPiece();

	void sliceArmor(Player* player);
	int sliceArmorEffectiveness(int min, int max);
	int sliceArmorEncumbrance(int min, int max);

	// setters
	inline void setRating(int rat) {
		rating = rat;
		String name = "rating";
		itemAttributes->setIntAttribute(name, rat);
	}

	inline void setKinetic(float kin) {
		kinetic = kin;
		String name = "kinetic";
		itemAttributes->setFloatAttribute(name, kin);
	}

	inline void setEnergy(float ene) {
		energy = ene;
		String name = "energy";
		itemAttributes->setFloatAttribute(name, ene);
	}

	inline void setElectricity(float ele) {
		electricity = ele;
		String name = "electricity";
		itemAttributes->setFloatAttribute(name, ele);
	}

	inline void setStun(float stu) {
		stun = stu;
		String name = "stun";
		itemAttributes->setFloatAttribute(name, stu);
	}

	inline void setBlast(float blst) {
		blast = blst;
		String name = "blast";
		itemAttributes->setFloatAttribute(name, blst);
	}

	inline void setHeat(float hot) {
		heat = hot;
		String name = "heat";
		itemAttributes->setFloatAttribute(name, hot);
	}

	inline void setCold(float notHot) {
		cold = notHot;
		String name = "cold";
		itemAttributes->setFloatAttribute(name, notHot);
	}

	inline void setAcid(float aci) {
		acid = aci;
		String name = "acid";
		itemAttributes->setFloatAttribute(name, aci);
	}

	inline void setLightSaber(float lightSab) {
		lightSaber = lightSab;
		String name = "lightSaber";
		itemAttributes->setFloatAttribute(name, lightSab);
	}

	inline void setSpecial(String s) {
		for(int i = 0; i < specialResistsVector.size(); ++i) {
			if(specialResistsVector.get(i) == s)
				return;
		}
		specialResistsVector.add(s);
	}

	inline void setVunerable(String v) {
		for(int i = 0; i < vunerabilitesVector.size(); ++i) {
			if(vunerabilitesVector.get(i) == v)
				return;
		}
		vunerabilitesVector.add(v);
	}

	inline void setArmorStyle(int style) {
		armorStyle = style;
	}

	inline void setArmorPiece(int piece) {
		String name = "armorPiece";
		armorPiece = piece;
		itemAttributes->setIntAttribute(name, piece);

		switch (armorPiece) {
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

	// getters
	inline int getRating() {
		return rating;
	}

	inline float getKinetic() {
		return kinetic;
	}

	inline float getEnergy() {
		return energy;
	}

	inline float getElectricity() {
		return electricity;
	}

	inline float getStun() {
		return stun;
	}

	inline float getBlast() {
		return blast;
	}

	inline float getHeat() {
		return heat;
	}

	inline float getCold() {
		return cold;
	}

	inline float getAcid() {
		return acid;
	}

	inline float getLightSaber() {
		return lightSaber;
	}

	inline int getArmorPiece() {
		return armorPiece;
	}

	inline int getArmorStyle() {
		return armorStyle;
	}

	inline bool isSpecial(String special) {
		for(int i = 0; i < specialResistsVector.size(); ++i) {
			if(specialResistsVector.get(i) == special)
				return true;
		}
		return false;
	}

	inline bool isVunerable(String v) {
		for(int i = 0; i < vunerabilitesVector.size(); ++i) {
			if(vunerabilitesVector.get(i) == v)
				return true;
		}
		return false;
	}

	//Event Handlers
	void onBroken();
	void onEncumbranceSliced(Player* slicer, uint8 percentage);
	void onEffectivenessSliced(Player* slicer, uint8 percentage);
	void onSlicingFailure(Player* slicer);
	void onEquip(Player* player);
	void onUnequip(Player* player);


	//Actions
	void slice(Player* slicer);
	void sliceEncumbrance(Player* slicer, uint8 percentage);
	void sliceEffectiveness(Player* slicer, uint8 percentage);
};
#endif /*ARMORIMPLEMENTATION_H_*/
