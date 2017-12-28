/*
 * PerformanceBuffImplementation.cpp
 *
 *  Created on: 04/03/2011
 *      Author: Itac
 */

#include <math.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/core/ManagedWeakReference.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/buffs/Buff.h"
#include "server/zone/objects/creature/buffs/PerformanceBuff.h"
#include "server/zone/objects/creature/buffs/PerformanceBuffType.h"
#include "templates/params/creature/CreatureAttribute.h"

void PerformanceBuffImplementation::activate(bool applyModifiers) {

	if(type == PerformanceBuffType::DANCE_MIND) {
		int mindStrength = round(strength * (float)creature.get()->getBaseHAM(CreatureAttribute::MIND));
		setAttributeModifier(CreatureAttribute::MIND, mindStrength);
		creature.get()->sendSystemMessage("@healing:performance_enhance_dance_mind_d");

	}
	else if(type == PerformanceBuffType::MUSIC_FOCUS) {
		int focusStrength = round(strength * (float)creature.get()->getBaseHAM(CreatureAttribute::FOCUS));
		setAttributeModifier(CreatureAttribute::FOCUS, focusStrength);
		creature.get()->sendSystemMessage("@healing:performance_enhance_music_focus_d");

	}
	else if(type == PerformanceBuffType::MUSIC_WILLPOWER) {
		int willStrength = round(strength * (float)creature.get()->getBaseHAM(CreatureAttribute::WILLPOWER));
		setAttributeModifier(CreatureAttribute::WILLPOWER, willStrength);
		creature.get()->sendSystemMessage("@healing:performance_enhance_music_willpower_d");
	}

	BuffImplementation::activate(true);

}

void PerformanceBuffImplementation::deactivate(bool removeModifiers) {
	BuffImplementation::deactivate(true);
}
