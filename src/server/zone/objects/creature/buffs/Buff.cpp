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

#include "Buff.h"

#include "../../player/Player.h"
#include "../../player/PlayerObject.h"

#include "../CreatureObject.h"

Buff::Buff(uint32 crc) {
	setBuffCRC(crc);
	setBuffDuration(0.0f);
	setBuffDownerCRC(0);
		
		// Defaults
	setBuffType(BuffType::OTHER);
	setHealthBuff(0);
	setActionBuff(0);
	setMindBuff(0);
	setStrengthBuff(0);
	setConstitutionBuff(0);
	setStaminaBuff(0);
	setQuicknessBuff(0);
	setWillpowerBuff(0);
	setFocusBuff(0);
	setForcePowerBuff(0);
	//setForceRegenBuff(0);
	
	active = false;
}
	
Buff::Buff(uint32 crc, int type, float duration) {
	setBuffCRC(crc);
	setBuffType(type);
	setBuffDuration(duration); // set in seconds?
	setBuffDownerCRC(0);

	// Defaults
	setHealthBuff(0);
	setActionBuff(0);
	setMindBuff(0);
	setStrengthBuff(0);
	setConstitutionBuff(0);
	setStaminaBuff(0);
	setQuicknessBuff(0);
	setWillpowerBuff(0);
	setFocusBuff(0);
	setForcePowerBuff(0);
	//setForceRegenBuff(0);
	
	active = false;
}

// TODO:  Need to do a better job with Shock Wounds
bool Buff::activateBuff(CreatureObject* creo) {		
	// default to update client by not specifying true attrib
	if (getHealthBuff() != 0)
	{
		// sets both maxHealthBar and setHealthmax
		creo->setMaxHealthBar(creo->getHealthMax() + getHealthBuff());
		creo->setHealthBar(MIN(creo->getHealth() + getHealthBuff() - creo->getHealthWounds(), creo->getHealthMax() - creo->getHealthWounds()));
	}
	
	if (getActionBuff() != 0) {
		creo->setMaxActionBar(creo->getActionMax() + getActionBuff());
		creo->setActionBar(MIN(creo->getAction() + getActionBuff() - creo->getActionWounds(), creo->getActionMax() - creo->getActionWounds()));
	}
	
	if (getMindBuff() != 0) {
		creo->setMaxMindBar(creo->getMindMax() + getMindBuff());
		creo->setMindBar(MIN(creo->getMind() + getMindBuff() - creo->getMindWounds(), creo->getMindMax() - creo->getMindWounds()));
	}
	
	if (getStrengthBuff() != 0) {
		creo->setMaxStrengthBar(creo->getStrengthMax() + getStrengthBuff());
		creo->setStrengthBar(MIN(creo->getStrength() + getStrengthBuff(), creo->getStrengthMax()));
	}
	
	if (getConstitutionBuff() != 0) {
		creo->setMaxConstitutionBar(creo->getConstitutionMax() + getConstitutionBuff());
		creo->setConstitutionBar(MIN(creo->getConstitution() + getConstitutionBuff(), creo->getConstitutionMax()));
	}
	
	if (getStaminaBuff() != 0) {
		creo->setMaxStaminaBar(creo->getStaminaMax() + getStaminaBuff());
		creo->setStaminaBar(MIN(creo->getStamina() + getStaminaBuff(), creo->getStaminaMax()));
	}
	
	if (getQuicknessBuff() != 0) {
		creo->setMaxQuicknessBar(creo->getQuicknessMax() + getQuicknessBuff());
		creo->setQuicknessBar(MIN(creo->getQuickness() + getQuicknessBuff(), creo->getQuicknessMax()));
	}
	
	if (getWillpowerBuff() != 0) {
		creo->setMaxWillpowerBar(creo->getWillpowerMax() + getWillpowerBuff());
		creo->setWillpowerBar(MIN(creo->getWillpower() + getWillpowerBuff(), creo->getWillpowerMax()));
	}
	
	if (getFocusBuff() != 0) {
		creo->setMaxFocusBar(creo->getFocusMax() + getFocusBuff());
		creo->setFocusBar(MIN(creo->getFocus() + getFocusBuff(), creo->getFocusMax()));
	}
	
	if (getForcePowerBuff() != 0 && creo->isPlayer()) {
		PlayerObject* playerObject = ((Player*)creo)->getPlayerObject();
		
		if (playerObject != NULL) {
			playerObject->setMaxForcePowerBar(playerObject->getForcePowerMax() + getForcePowerBuff());
			playerObject->setForcePowerBar(MIN(playerObject->getForcePower() + getForcePowerBuff(), playerObject->getForcePowerMax()));
		}
	}

	
	
	// TODO: Add Skill Mods

	creo->addBuff(getBuffCRC(), getBuffDuration());

	active = true;
	return true;
	
}


// TODO:  Need to do a better job with Shock Wounds
void Buff::downerBuff(CreatureObject* creo) {		
	Buff *buff = new Buff(getBuffDownerCRC(), BuffType::SPICE, round(getBuffDuration() / 3.0));
	
	// The Min Value of their total bar - 1 or the downer
	buff->setHealthBuff(-1 * MIN(creo->getHealthMax() - 1, getHealthBuff()));
	buff->setActionBuff(-1 * MIN(creo->getActionMax() - 1, getActionBuff()));
	buff->setMindBuff(-1 * MIN(creo->getMindMax() - 1, getMindBuff()));
	buff->setStrengthBuff(-1 * MIN(creo->getStrengthMax() - 1, getStrengthBuff()));
	buff->setConstitutionBuff(-1 * MIN(creo->getConstitutionMax() - 1, getConstitutionBuff()));
	buff->setStaminaBuff(-1 * MIN(creo->getStaminaMax() - 1, getStaminaBuff()));
	buff->setQuicknessBuff(-1 * MIN(creo->getQuicknessMax() - 1, getQuicknessBuff()));
	buff->setWillpowerBuff(-1 * MIN(creo->getWillpowerMax() - 1, getWillpowerBuff()));
	buff->setFocusBuff(-1 * MIN(creo->getFocusMax() - 1, getFocusBuff()));
	
	if (creo->isPlayer()) {
		buff->setForcePowerBuff(-1 * MIN(((Player*)creo)->getForcePowerMax() - 1, getForcePowerBuff()));
	}
	
	// TODO: Switch Skill Mods?
	BuffObject* bo = new BuffObject(buff);
	creo->applyBuff(bo);
}

bool Buff::deActivateBuff(CreatureObject* creo, bool updateClient) {
	if (!active) {
		creo->sendSystemMessage("buff not active - report repo steps to McMahon");
		return false;
	}
	
	if (getHealthBuff() != 0)
		creo->setMaxHealthBar(creo->getHealthMax() - getHealthBuff(), updateClient);
	
	if (getActionBuff() != 0)
		creo->setMaxActionBar(creo->getActionMax() - getActionBuff(), updateClient);
	
	if (getMindBuff() != 0)
		creo->setMaxMindBar(creo->getMindMax() - getMindBuff(), updateClient);
	
	if (getStrengthBuff() != 0)
		creo->setMaxStrengthBar(creo->getStrengthMax() - getStrengthBuff(), updateClient);
	
	if (getConstitutionBuff() != 0)
		creo->setMaxConstitutionBar(creo->getConstitutionMax() - getConstitutionBuff(), updateClient);
	
	if (getStaminaBuff() != 0)
		creo->setMaxStaminaBar(creo->getStaminaMax() - getStaminaBuff(), updateClient);
	
	if (getQuicknessBuff() != 0)
		creo->setMaxQuicknessBar(creo->getQuicknessMax() - getQuicknessBuff(), updateClient);
	
	if(getWillpowerBuff() != 0)
		creo->setMaxWillpowerBar(creo->getWillpowerMax() - getWillpowerBuff(), updateClient);
	
	if (getFocusBuff() != 0)
		creo->setMaxFocusBar(creo->getFocusMax() - getFocusBuff(), updateClient);
	
	if (getForcePowerBuff() != 0 && creo->isPlayer()) {
		PlayerObject* playerObject = ((Player*)creo)->getPlayerObject();
		
		if (playerObject != NULL)
			playerObject->setMaxForcePowerBar(playerObject->getForcePowerMax() - getForcePowerBuff(), updateClient);
	}


	// TODO: Remove Skill Mods
	
	// Remove from client buff list
	if (updateClient)
		creo->addBuff(getBuffCRC(), 0.0f);
	
	active = false;
	
	// Activate Downer
	if (getBuffType() == BuffType::SPICE && updateClient && getBuffDownerCRC() > 0)
		downerBuff(creo);
	
	return true;
}
