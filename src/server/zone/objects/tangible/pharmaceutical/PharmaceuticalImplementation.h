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

#ifndef PHARMACEUTICALIMPLEMENTATION_H_
#define PHARMACEUTICALIMPLEMENTATION_H_

#include "Pharmaceutical.h"

#include "../../player/Player.h"
#include "../../../Zone.h"
#include "../../../managers/item/ItemManager.h"

class PharmaceuticalImplementation : public PharmaceuticalServant {
protected:
	int medpackType;
	int usesRemaining;
	int medicineUseRequired;

public:
	//Medical Pack Types
	static const int ENHANCEPACK = 1;
	static const int WOUNDPACK = 2;
	static const int CUREPACK = 3;
	static const int STIMPACK = 4;
	static const int STATEPACK = 5;
	static const int REVIVEPACK = 6;
	static const int CUREAREAPACK = 7;
	static const int RANGEDSTIMPACK = 8;
	static const int POISONDELIVERYUNIT = 9;
	static const int DISEASEDELIVERYUNIT = 10;

public:

	PharmaceuticalImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn, int mptype);
	PharmaceuticalImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn, int mptype);
	PharmaceuticalImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, int mptype);

	~PharmaceuticalImplementation();

	void init();

	void sendDeltas(Player* player);

	void generateAttributes(SceneObject* obj);

	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);

	void useCharge(Player* player);

	inline void setUsesRemaining(int uses) {
		usesRemaining = uses;
		objectCount = uses;
		String attr = "usesRemaining";
		itemAttributes->setIntAttribute(attr, usesRemaining);
	}

	inline void setMedicineUseRequired(int meduse) {
		medicineUseRequired = meduse;
		String attr = "medicineUseRequired";
		itemAttributes->setIntAttribute(attr, medicineUseRequired);
	}

	inline void setMedpackType(int mptype) {
		medpackType = mptype;
		String attr = "medpackType";
		itemAttributes->setIntAttribute(attr, medpackType);
	}

	inline int getUsesRemaining() {
		return usesRemaining;
	}

	inline int getMedicineUseRequired() {
		return medicineUseRequired;
	}

	inline int getMedpackType() {
		return medpackType;
	}

	inline bool isEnhancePack() {
		return medpackType == ENHANCEPACK;
	}

	inline bool isWoundPack() {
		return medpackType == WOUNDPACK;
	}

	inline bool isStimPack() {
		return medpackType == STIMPACK;
	}

	inline bool isStatePack() {
		return medpackType == STATEPACK;
	}

	inline bool isCurePack() {
		return medpackType == CUREPACK;
	}

	inline bool isRevivePack() {
		return medpackType == REVIVEPACK;
	}

	inline bool isCureAreaPack() {
		return medpackType == CUREAREAPACK;
	}

	inline bool isRangedStimPack() {
		return medpackType == RANGEDSTIMPACK;
	}

	inline bool isPoisonDeliveryUnit() {
		return medpackType == POISONDELIVERYUNIT;
	}

	inline bool isDiseaseDeliveryUnit() {
		return medpackType == DISEASEDELIVERYUNIT;
	}

	inline bool isGeneralMedicItem() {
		return medpackType < RANGEDSTIMPACK;
	}

	inline bool isCombatMedicItem() {
		return medpackType > CUREAREAPACK;
	}

	virtual bool isArea() {
		return false;
	}

	virtual float getRange(CreatureObject* creature = NULL) {
		return 5.0f;
	}

	virtual float getArea() {
		return 0.0f;
	}
};

#endif /* PHARMACEUTICALIMPLEMENTATION_H_ */
