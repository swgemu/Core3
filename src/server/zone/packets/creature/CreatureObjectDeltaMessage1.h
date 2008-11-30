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

#ifndef CREATUREOBJECTDELTAMESSAGE1_H_
#define CREATUREOBJECTDELTAMESSAGE1_H_

#include "../../packets/DeltaMessage.h"

#include "../../objects/creature/CreatureObjectImplementation.h"

class CreatureObjectDeltaMessage1 : public DeltaMessage {
	CreatureObjectImplementation* creo;
	
public:
	CreatureObjectDeltaMessage1(CreatureObjectImplementation* cr)
			: DeltaMessage(cr->getObjectID(), 0x4352454F, 1) {
		creo = cr;
	}

	void startSkillBoxListUpdate(int skillBoxesToUpdate) {
		startUpdate(0x03);
		startList(skillBoxesToUpdate, creo->skillBoxesUpdateCounter += skillBoxesToUpdate);
	}
	
	void addSkillBox(const String& name) {
		insertByte(0x01);
		insertAscii(name.toCharArray());
	}

	void removeSkillBox(const String& name) {
		insertByte(0x00);
		insertAscii(name.toCharArray());
	}
	
	void updateBankCredits() {
		startUpdate(0x00);
		insertInt(creo->getBankCredits());
	}
	
	void updateBaseStats()
	{
		startUpdate(0x02);
		
		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(9);
		startList(9, updatecount);
						
		uint32 healthCreo = creo->getBaseHealth();
		addBar(0, healthCreo);
		uint32 strengthCreo = creo->getBaseStrength();
		addBar(1, strengthCreo);
		uint32 constCreo = creo->getBaseConstitution();
		addBar(2, constCreo);
		uint32 actionCreo = creo->getBaseAction();
		addBar(3, actionCreo);
		uint32 quicknessCreo = creo->getBaseQuickness();
		addBar(4, quicknessCreo);
		uint32 staminaCreo = creo->getBaseStamina();
		addBar(5, staminaCreo);
		uint32 mindCreo = creo->getBaseMind();
		addBar(6, mindCreo);
		uint32 focusCreo = creo->getBaseFocus();
		addBar(7, focusCreo);
		uint32 willpowerCreo = creo->getBaseWillpower();
		addBar(8, willpowerCreo);
		
	}
	
	void updateBaseHealthBar(uint32 health) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseHealthCreo = creo->getBaseHealth();
		addBar(0, baseHealthCreo, health);

		creo->setBaseHealth(baseHealthCreo);
	}
	
	void updateBaseStrengthBar(uint32 strength) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseStrengthCreo = creo->getBaseStrength();
		addBar(1, baseStrengthCreo, strength);

		creo->setBaseStrength(baseStrengthCreo);
	}
	
	void updateBaseConstitutionBar(uint32 constitution) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseConstitutionCreo = creo->getBaseConstitution();
		addBar(2, baseConstitutionCreo, constitution);

		creo->setBaseConstitution(baseConstitutionCreo);
	}
	
	void updateBaseActionBar(uint32 action) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseActionCreo = creo->getBaseAction();
		addBar(3, baseActionCreo, action);

		creo->setBaseAction(baseActionCreo);
	}
		
	void updateBaseQuicknessBar(uint32 quickness) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseQuicknessCreo = creo->getBaseQuickness();
		addBar(4, baseQuicknessCreo, quickness);

		creo->setBaseQuickness(baseQuicknessCreo);
	}
	
	void updateBaseStaminaBar(uint32 stamina) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseStaminaCreo = creo->getBaseStamina();
		addBar(5, baseStaminaCreo, stamina);

		creo->setBaseStamina(baseStaminaCreo);
	}
	
	void updateBaseMindBar(uint32 mind) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseMindCreo = creo->getBaseMind();
		addBar(6, baseMindCreo, mind);

		creo->setBaseMind(baseMindCreo);
	}
	
	void updateBaseFocusBar(uint32 focus) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseFocusCreo = creo->getBaseFocus();
		addBar(7, baseFocusCreo, focus);

		creo->setBaseFocus(baseFocusCreo);
	}
	
	void updateBaseWillpowerBar(uint32 willpower) {
		startUpdate(0x02);

		uint32 updatecount = creo->getNewHAMBaseUpdateCounter(1);
		startList(1, updatecount);
		
		uint32 baseWillpowerCreo = creo->getBaseWillpower();
		addBar(8, baseWillpowerCreo, willpower);

		creo->setBaseWillpower(baseWillpowerCreo);
	}
	
	void addBar(uint16 index, uint32& value, uint32 nvalue) {
		removeListIntElement(index, value = nvalue);
	}

	void addBar(uint16 index, uint32 value) {
		removeListIntElement(index, value);
	}
	
	void updateCashCredits() {
		startUpdate(0x01);
		insertInt(creo->getCashCredits());	
	}



};

#endif /*CREATUREOBJECTDELTAMESSAGE1_H_*/
