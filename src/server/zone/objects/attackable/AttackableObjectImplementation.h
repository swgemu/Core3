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

#ifndef ATTACKABLEOBJECTIMPLEMENTATION_H_
#define ATTACKABLEOBJECTIMPLEMENTATION_H_

#include "AttackableObject.h"

#include "../../packets.h"

#include "../scene/SceneObject.h"
#include "../player/Player.h"

#include "../tangible/CustomizationVariables.h"

#include "../../packets/attackable/AttackableObjectMessage3.h"
#include "../../packets/attackable/AttackableObjectMessage6.h"
#include "../../packets/attackable/AttackableObjectDeltaMessage3.h"


class AttackableObjectImplementation : public AttackableObjectServant {
protected:

	Zone* zone;

	Vector<ManagedReference<SceneObject> > defenderList;

	bool inCombat;

	int conditionDamage;
	int maxCondition;
	int pvpStatusBitmask;

	bool attackable;

	UnicodeString name;
	String templateTypeName;
	String templateName;
	String templateDetailName;
	String templateDetail;

	CustomizationVariables customizationVars;


public:
	AttackableObjectImplementation(uint64 oid);

	void insertToZone(Zone* zone);
	void removeFromZone(bool doLock = true);
	void broadcastMessage(BaseMessage* msg, int range = 128, bool doLock = true);

	void setDefender(SceneObject* defender);
	virtual void addDefender(SceneObject* defender);
	void removeDefender(SceneObject* defender);
	void removeDefenders();
	bool hasDefender(SceneObject* defender);

	void setCombatState();
	void clearCombatState(bool removeDefenders = true);

	void sendTo(Player* player, bool doClose = true);
	void sendDestroyTo(Player* player);

	virtual void doDamage(int damage, SceneObject* attacker);
	virtual void doDestroyed(SceneObject* attacker);

	inline void setTemplateName(String& stfname) {
		templateName = stfname;
	}

	inline String& getTemplateTypeName() {
		return templateTypeName;
	}

	inline String& getTemplateName() {
		return templateName;
	}

	inline UnicodeString& getName() {
		return name;
	}

	inline String& getTemplateDetailName() {
		return templateDetailName;
	}

	inline String& getTemplateDetail() {
		return templateDetail;
	}

	void getCustomizationString(String& app) {
		return customizationVars.toString(app);
	}

	inline void setConditionDamage(uint32 cond) {
		conditionDamage = cond;
	}

	inline void setMaxCondition(uint32 maxcond) {
		maxCondition = maxcond;
	}

	inline int getConditionDamage() {
		return conditionDamage;
	}

	inline int getMaxCondition() {
		return maxCondition;
	}

	inline bool isAttackableBy(CreatureObject* creature) {
		return attackable;
	}

	inline bool isDestroyed() {
		return (conditionDamage >= maxCondition);
	}
};

#endif /*ATTACKABLEOBJECTIMPLEMENTATION_H_*/
