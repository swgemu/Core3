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
#include "../events/CreatureBuffEvent.h"

Buff::Buff(uint32 crc) {
	setBuffCRC(crc);
	setBuffDuration(0.0f);
	setBuffDownerCRC(0);
	setBuffDowner(false);

	setBuffEvent(NULL);
	setZoneProcessServer(NULL);

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

	active = false;
}

Buff::Buff(uint32 crc, int type, float duration) {
	setBuffCRC(crc);
	setBuffType(type);
	setBuffDuration(duration); // set in seconds?
	setBuffDownerCRC(0);
	setBuffDowner(false);

	setBuffEvent(NULL);
	setZoneProcessServer(NULL);

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

	active = false;
}

// TODO:  Need to do a better job with Shock Wounds
bool Buff::activateBuff(CreatureObject* creo, ZoneProcessServerImplementation* serv) {
	setZoneProcessServer(serv);

	// default to update client by not specifying true attrib
	if (getHealthBuff() != 0)
	{
		// sets both maxHealthBar and setHealthmax
		creo->setHealthBar(MAX(MIN(creo->getHealth() - creo->getHealthWounds() + getHealthBuff(), creo->getHealthMax() - creo->getHealthWounds() + getHealthBuff()), 1));
		creo->changeMaxHealthBar(getHealthBuff());
	}

	if (getActionBuff() != 0) {
		creo->setActionBar(MAX(MIN(creo->getAction() - creo->getActionWounds() + getActionBuff(), creo->getActionMax() - creo->getActionWounds() + getActionBuff()), 1));
		creo->changeMaxActionBar(getActionBuff());
	}

	if (getMindBuff() != 0) {
		creo->setMindBar(MAX(MIN(creo->getMind() - creo->getMindWounds() + getMindBuff(), creo->getMindMax() - creo->getMindWounds() + getMindBuff()), 1));
		creo->changeMaxMindBar(getMindBuff());
	}

	if (getStrengthBuff() != 0) {
		creo->setStrengthBar(MAX(MIN(creo->getStrength() - creo->getStrengthWounds() + getStrengthBuff(), creo->getStrengthMax() - creo->getStrengthWounds() + getStrengthBuff()), 1));
		creo->changeMaxStrengthBar(getStrengthBuff());
	}

	if (getConstitutionBuff() != 0) {
		creo->setConstitutionBar(MAX(MIN(creo->getConstitution() - creo->getConstitutionWounds() + getConstitutionBuff(), creo->getConstitutionMax() - creo->getConstitutionWounds() + getConstitutionBuff()), 1));
		creo->changeMaxConstitutionBar(getConstitutionBuff());
	}

	if (getStaminaBuff() != 0) {
		creo->setStaminaBar(MAX(MIN(creo->getStamina() - creo->getStaminaWounds() + getStaminaBuff(), creo->getStaminaMax() - creo->getStaminaWounds() + getStaminaBuff()), 1));
		creo->changeMaxStaminaBar(getStaminaBuff());
	}

	if (getQuicknessBuff() != 0) {
		creo->setQuicknessBar(MAX(MIN(creo->getQuickness() - creo->getQuicknessWounds() + getQuicknessBuff(), creo->getQuicknessMax() - creo->getQuicknessWounds() + getQuicknessBuff()), 1));
		creo->changeMaxQuicknessBar(getQuicknessBuff());
	}

	if (getWillpowerBuff() != 0) {
		creo->setWillpowerBar(MAX(MIN(creo->getWillpower() - creo->getWillpowerWounds() + getWillpowerBuff(), creo->getWillpowerMax() - creo->getWillpowerWounds() + getWillpowerBuff()), 1));
		creo->changeMaxWillpowerBar(getWillpowerBuff());
	}

	if (getFocusBuff() != 0) {
		creo->setFocusBar(MAX(MIN(creo->getFocus() - creo->getFocusWounds() + getFocusBuff(), creo->getFocusMax() - creo->getFocusWounds() + getFocusBuff()), 1));
		creo->changeMaxFocusBar(getFocusBuff());
	}

	removeBuffEvent();

	// TODO: Add Skill Mods
	buffEvent = new CreatureBuffEvent(creo, buffCRC, buffDuration);
	if (server != NULL)
		server->addEvent(buffEvent);

	creo->addBuff(getBuffCRC(), getBuffDuration());

	active = true;
	return true;

}

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

	buff->setBuffDowner(true);

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
		creo->changeMaxHealthBar(-1 * getHealthBuff(), updateClient);

	if (getActionBuff() != 0)
		creo->changeMaxActionBar(-1 * getActionBuff(), updateClient);

	if (getMindBuff() != 0)
		creo->changeMaxMindBar(-1 * getMindBuff(), updateClient);

	if (getStrengthBuff() != 0) {
		//System::out << "deActivateBuff (strength max original): " << creo->getStrengthMax() << endl;
		creo->changeMaxStrengthBar(-1 * getStrengthBuff(), updateClient);
		//System::out << "deActivateBuff (strength max new): " << creo->getStrengthMax() << endl;
		creo->setStrengthBar(MAX(creo->getStrengthMax() - creo->getConstitutionWounds(), 1));
	}

	if (getConstitutionBuff() != 0) {
		//System::out << "deActivateBuff (constitution max original): " << creo->getConstitutionMax() << endl;
		creo->changeMaxConstitutionBar(-1 * getConstitutionBuff(), updateClient);
		//System::out << "deActivateBuff (constitution max new): " << creo->getConstitutionMax() << endl;
		creo->setConstitutionBar(MAX(creo->getConstitutionMax() - creo->getConstitutionWounds(), 1));
	}

	if (getStaminaBuff() != 0) {
		creo->changeMaxStaminaBar(-1 * getStaminaBuff(), updateClient);
		creo->setStaminaBar(MAX(creo->getStaminaMax() - creo->getStaminaWounds(), 1));
	}

	if (getQuicknessBuff() != 0) {
		creo->changeMaxQuicknessBar(-1 * getQuicknessBuff(), updateClient);
		creo->setQuicknessBar(MAX(creo->getQuicknessMax() - creo->getQuicknessWounds(), 1));
	}

	if (getWillpowerBuff() != 0) {
		creo->changeMaxWillpowerBar(-1 * getWillpowerBuff(), updateClient);
		creo->setWillpowerBar(MAX(creo->getWillpowerMax() - creo->getWillpowerWounds(), 1));
	}

	if (getFocusBuff() != 0) {
		creo->changeMaxFocusBar(-1 * getFocusBuff(), updateClient);
		creo->setFocusBar(MAX(creo->getFocusMax() - creo->getFocusWounds(), 1));
	}

	creo->activateRecovery();

	// TODO: Remove Skill Mods

	removeBuffEvent();

	// Remove from client buff list
	if (updateClient)
		creo->addBuff(getBuffCRC(), 0.0f);

	active = false;

	// Activate Downer
	if (getBuffType() == BuffType::SPICE && updateClient && getBuffDownerCRC() > 0)
		downerBuff(creo);

	return true;
}
