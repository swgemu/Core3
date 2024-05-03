/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */


#include "templates/params/creature/CreatureAttribute.h"
#include "templates/params/creature/CreatureState.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"
#include "DamageOverTime.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/combat/CombatManager.h"

// #define DEBUG_DOTS

DamageOverTime::DamageOverTime() {
	setAttackerID(0);
	setType(CreatureState::BLEEDING);
	setAttribute(CreatureAttribute::HEALTH);
	strength = 0;
	setDuration(0);
	setExpires(Time((uint32) 0));
	setSecondaryStrength(0);
	addSerializableVariables();

	setLoggingName("DamageOverTime");
}

DamageOverTime::DamageOverTime(CreatureObject* attacker, uint64 tp, uint8 attrib, uint32 str, uint32 dur, int secondaryStrength) {
	if (attacker != nullptr)
		setAttackerID(attacker->getObjectID());

	setType(tp);
	setAttribute(attrib);
	strength = str;
	setDuration(dur);
	setSecondaryStrength(secondaryStrength);
	applied.updateToCurrentTime();
	activate();

	addSerializableVariables();

	setLoggingName("DamageOverTime");
}

DamageOverTime::DamageOverTime(const DamageOverTime& dot) : Object(), Serializable(), Logger() {
	addSerializableVariables();

	attackerID = dot.attackerID;
	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	applied = dot.applied;
	expires = dot.expires;
	nextTick = dot.nextTick;
	secondaryStrength = dot.secondaryStrength;

	setLoggingName("DamageOverTime");
}

DamageOverTime& DamageOverTime::operator=(const DamageOverTime& dot) {
	if (this == &dot)
		return *this;

	attackerID = dot.attackerID;
	type = dot.type;
	attribute = dot.attribute;
	strength = dot.strength;
	duration = dot.duration;
	applied = dot.applied;
	expires = dot.expires;
	nextTick = dot.nextTick;
	secondaryStrength = dot.secondaryStrength;

	return *this;
}

void DamageOverTime::addSerializableVariables() {
	addSerializableVariable("attackerID", &attackerID);
	addSerializableVariable("type", &type);
	addSerializableVariable("attribute", &attribute);
	addSerializableVariable("strength", &strength);
	addSerializableVariable("duration", &duration);
	addSerializableVariable("applied", &applied);
	addSerializableVariable("expires", &expires);
	addSerializableVariable("nextTick", &nextTick);
	addSerializableVariable("secondaryStrength", &secondaryStrength);
}

void to_json(nlohmann::json& j, const DamageOverTime& t) {
	j["attackerID"] = t.attackerID;
	j["type"] = t.type;
	j["attribute"] = t.attribute;
	j["strength"] = t.strength;
	j["duration"] = t.duration;
	j["applied"] = t.applied;
	j["expires"] = t.expires;
	j["nextTick"] = t.nextTick;
	j["secondaryStrength"] = t.secondaryStrength;
}

void DamageOverTime::activate() {
	expires.updateToCurrentTime();
	expires.addMiliTime(duration * 1000);
}

uint32 DamageOverTime::applyDot(CreatureObject* victim) {
	if (victim == nullptr) {
		return 0;
	}

#ifdef DEBUG_DOTS
	info(true) << "applyDot called " << victim->getFirstName() << " ID: " << victim->getObjectID() << " Type: " << type;
#endif

	auto zoneServer = victim->getZoneServer();

	if (zoneServer == nullptr) {
		return 0;
	}

	if ((!victim->hasState(type) && type != CommandEffect::FORCECHOKE) || !nextTick.isPast()) {
#ifdef DEBUG_DOTS
		if (!victim->hasState(type))
			info(true) << "Victim does not have the state.";
		else
			info(true) << "nextTick is not past.";
#endif
		return 0;
	}

	bool reschedule = true;

	if (expires.isPast()) {
		reschedule = false;
	}

	nextTick.updateToCurrentTime();

	uint32 power = 0;
	ManagedReference<CreatureObject*> attacker = zoneServer->getObject(attackerID).castTo<CreatureObject*>();

	if (attacker == nullptr) {
		attacker = victim;
	}

	int time = 0;

	switch(type) {
	case CreatureState::BLEEDING:
		power = doBleedingTick(victim, attacker);
		time = 20000;
		break;
	case CreatureState::POISONED:
		power = doPoisonTick(victim, attacker);
		time = 10000;
		break;
	case CreatureState::DISEASED:
		power = doDiseaseTick(victim, attacker);
		time = 40000;
		break;
	case CreatureState::ONFIRE:
		power = doFireTick(victim, attacker);
		time = 10000;
		break;
	case CommandEffect::FORCECHOKE:
		power = doForceChokeTick(victim, attacker);
		time = 5000;
		break;
	}

	if (reschedule) {
		nextTick.addMiliTime(time);
	}

#ifdef DEBUG_DOTS
	info(true) << "applyDot complete " << victim->getFirstName() << " Power: " << power;
#endif

	return power;
}

uint32 DamageOverTime::initDot(CreatureObject* victim, CreatureObject* attacker) {
#ifdef DEBUG_DOTS
	info(true) << "initDot called -- START: Player " << victim->getFirstName() << " ID: " << victim->getObjectID() << " Type: " << type << " Pool: " << attribute;
#endif

	uint32 power = 0;
	int absorptionMod = 0;
	nextTick.updateToCurrentTime();

	switch(type) {
	case CreatureState::BLEEDING:
		absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_bleeding")));
		nextTick.addMiliTime(20000);
		break;
	case CreatureState::ONFIRE:
		absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_fire")));
		nextTick.addMiliTime(10000);
		break;
	case CreatureState::POISONED:
		absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_poison")));
		nextTick.addMiliTime(10000);
		break;
	case CreatureState::DISEASED:
		absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_disease")));
		nextTick.addMiliTime(40000);
		break;
	case CommandEffect::FORCECHOKE:
		nextTick.addMiliTime(5000);
		strength *= ((100 - System::random(20)) * 0.01f);
		victim->showFlyText("combat_effects", "choke", 0xFF, 0, 0);

		break;
	}

	power = (uint32)(strength * (1.f - absorptionMod / 100.f));

#ifdef DEBUG_DOTS
	info(true) << "initDot called " << victim->getFirstName() << " Type: " << type << " Power: " << power << " Absorption Mod: " << absorptionMod << " Pool: " << attribute;
#endif

	//victim->addDamage(attacker,1);

	return power;
}

uint32 DamageOverTime::doBleedingTick(CreatureObject* victim, CreatureObject* attacker) {
	// TODO: Do we try to resist again?
	// we need to allow dots to tick while incapped, but not do damage
	if (victim->isIncapacitated() && victim->isFeigningDeath() == false)
		return 0;

	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_bleeding")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));
	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;
	}

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	auto attribute = this->attribute;

	Core::getTaskManager()->executeTask([victimRef, attackerRef, attribute, damage] () {
		Locker locker(victimRef);

		Locker crossLocker(attackerRef, victimRef);

		victimRef->inflictDamage(attackerRef, attribute, damage, false, "dotDMG", true, false);

		if (victimRef->hasAttackDelay())
			victimRef->removeAttackDelay();

		victimRef->playEffect("clienteffect/dot_bleeding.cef","");
	}, "BleedTickLambda");

#ifdef DEBUG_DOTS
	info(true) << "doBleedingTick -- Pool: " << attribute << " Damage: " << damage;
#endif

	return damage;
}

uint32 DamageOverTime::doFireTick(CreatureObject* victim, CreatureObject* attacker) {
	// we need to allow dots to tick while incapped, but not do damage
	if (victim->isIncapacitated() && victim->isFeigningDeath() == false)
		return 0;

	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_fire")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));
	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;
	}

	int woundsToApply = (int)(secondaryStrength * ((100.f + victim->getShockWounds()) / 100.0f));
	int maxWoundsToApply = victim->getBaseHAM(attribute) - 1 - victim->getWounds(attribute);

	woundsToApply = Math::min(woundsToApply, maxWoundsToApply);

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	auto attribute = this->attribute;
	auto secondaryStrength = this->secondaryStrength;

	Core::getTaskManager()->executeTask([victimRef, attackerRef, attribute, woundsToApply, secondaryStrength, damage] () {
		Locker locker(victimRef);

		Locker crossLocker(attackerRef, victimRef);

		if (woundsToApply > 0) {
			// need to do damage to account for wounds first, or it will possibly get
			// applied twice
			if (attribute % 3 == 0)
				victimRef->inflictDamage(attackerRef, attribute, woundsToApply, true, "dotDMG", true, false);

			victimRef->addWounds(attribute, woundsToApply, true, false);
		}

		victimRef->addShockWounds((int)(secondaryStrength * 0.075f));

		victimRef->inflictDamage(attackerRef, attribute - attribute % 3, damage, true, "dotDMG", true, false);
		if (victimRef->hasAttackDelay())
			victimRef->removeAttackDelay();

		victimRef->playEffect("clienteffect/dot_fire.cef","");
	}, "FireTickLambda");

#ifdef DEBUG_DOTS
	info(true) << "doFireTick -- Pool: " << attribute << " Damage: " << damage;
#endif

	return damage;
}

uint32 DamageOverTime::doPoisonTick(CreatureObject* victim, CreatureObject* attacker) {
	if (victim == nullptr || attacker == nullptr)
		return 0;

	if (strength <= 0)
		return 0;

	// we need to allow dots to tick while incapped, but not do damage
	if (victim->isIncapacitated() && !victim->isFeigningDeath())
		return 0;

	uint32 attr = victim->getHAM(attribute);
	int absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_poison")));

	// absorption reduces the strength of a dot by the given %.
	int damage = (int)(strength * (1.f - absorptionMod / 100.f));

#ifdef DEBUG_DOTS
	info(true) << "doPoisonTick -- Victim: " << victim->getDisplayedName() << " Attribute: " << attr << " Absorption Mod: " << absorptionMod << " Damage: " << damage << " Strength: " << strength;
#endif

	if (attr < damage) {
		//System::out << "setting strength to " << attr -1 << endl;
		damage = attr - 1;

#ifdef DEBUG_DOTS
		info(true) << "Attribute < damage -- new damage: " << damage;
#endif
	}

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	auto attribute = this->attribute;

	Core::getTaskManager()->executeTask([victimRef, attackerRef, attribute, damage] () {
		Locker locker(victimRef);

		Locker crossLocker(attackerRef, victimRef);

		victimRef->inflictDamage(attackerRef, attribute, damage, false, "dotDMG", true, false);
		if (victimRef->hasAttackDelay())
			victimRef->removeAttackDelay();

		victimRef->playEffect("clienteffect/dot_poisoned.cef","");
	}, "PoisonTickLambda");

#ifdef DEBUG_DOTS
	info(true) << "doPoisonTick -- Pool: " << attribute << " Damage: " << damage;
#endif

	return damage;
}

uint32 DamageOverTime::doDiseaseTick(CreatureObject* victim, CreatureObject* attacker) {
	// we need to allow dots to tick while incapped, but not do damage
	if (victim->isIncapacitated() && !victim->isFeigningDeath()) {
		return 0;
	}

	int absorptionMod = Math::max(0, Math::min(50, victim->getSkillMod("absorption_disease")));

	// absorption reduces the strength of a dot by the given %.
	// make sure that the CM dots modify the strength
	int damage = (int)(strength * (1.f - absorptionMod / 100.f) * (1.f + victim->getShockWounds() / 100.0f));
	int maxDamage = victim->getBaseHAM(attribute) - 1 - victim->getWounds(attribute);

	damage = Math::min(damage, maxDamage);

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	auto attribute = this->attribute;
	auto strength = this->strength;

	Core::getTaskManager()->executeTask([victimRef, attackerRef, attribute, damage, strength] () {
		Locker locker(victimRef);
		Locker crossLocker(attackerRef, victimRef);

		int damageInt = (int)damage;
		int shockWounds = (int)(strength * 0.075f);

#ifdef DEBUG_DOTS
		info(true) << "Disease tick on Victim: " << victimRef->getDisplayedName() << " Attribute #" << attribute << " Damage: " << damageInt << " Shock Wounds: " << shockWounds;
#endif // DEBUG_DOTS

		if (damageInt > 0) {
			// need to do damage to account for wounds first, or it will possibly get
			// applied twice
			if (attribute % 3 == 0) {
				victimRef->inflictDamage(attackerRef, attribute, damage, true, "dotDMG", true, false);
			}

			victimRef->addWounds(attribute, damage, true, false);
		}

		victimRef->addShockWounds(shockWounds);

		if (victimRef->hasAttackDelay()) {
			victimRef->removeAttackDelay();
		}

		victimRef->playEffect("clienteffect/dot_diseased.cef","");
	}, "DiseaseTickLambda");

#ifdef DEBUG_DOTS
	info(true) << "doDiseaseTick  -- Attribute #" << attribute << " Damage: " << damage;
#endif

	return damage;
}

uint32 DamageOverTime::doForceChokeTick(CreatureObject* victim, CreatureObject* attacker) {
	// we need to allow dots to tick while incapped, but not do damage
	if (victim->isIncapacitated() && victim->isFeigningDeath() == false)
		return 0;

	Reference<CreatureObject*> attackerRef = attacker;
	Reference<CreatureObject*> victimRef = victim;
	auto attribute = this->attribute;
	auto strength = this->strength;

	Core::getTaskManager()->executeTask([victimRef, attackerRef, attribute, strength] () {
		Locker locker(victimRef);

		Locker crossLocker(attackerRef, victimRef);

		uint32 chokeDam = strength;

		float jediBuffDamage = 0;
		float rawDamage = chokeDam;

		// Force Shield
		int forceShield = victimRef->getSkillMod("force_shield");
		if (forceShield > 0) {
			jediBuffDamage = rawDamage - (chokeDam *= 1.f - (forceShield / 100.f));
			victimRef->notifyObservers(ObserverEventType::FORCESHIELD, attackerRef, jediBuffDamage);
			CombatManager::instance()->sendMitigationCombatSpam(victimRef, nullptr, (int)jediBuffDamage, CombatManager::FORCESHIELD);
		}

		//PSG with lightsaber resistance only
		ManagedReference<ArmorObject*> psg = CombatManager::instance()->getPSGArmor(victimRef);
		if (psg != nullptr && !psg->isVulnerable(SharedWeaponObjectTemplate::LIGHTSABER)) {
			float armorReduction =  CombatManager::instance()->getArmorObjectReduction(psg, SharedWeaponObjectTemplate::LIGHTSABER);

		if (armorReduction > 0)
			chokeDam *= 1.f - (armorReduction / 100.f);

		}

		CombatManager::instance()->broadcastCombatSpam(attackerRef, victimRef, nullptr, chokeDam, "cbt_spam", "forcechoke_hit", 1);
		victimRef->inflictDamage(attackerRef, attribute, chokeDam, true, "dotDMG", true, false);

		if (victimRef->hasAttackDelay())
			victimRef->removeAttackDelay();

		victimRef->playEffect("clienteffect/pl_force_choke.cef", "");
		victimRef->sendSystemMessage("@combat_effects:choke_single");
		victimRef->showFlyText("combat_effects", "choke", 0xFF, 0, 0);
	}, "ForceChokeTickLambda");

#ifdef DEBUG_DOTS
	info(true) << "doForceChokeTick -- Damage: " << strength;
#endif

	return strength;
}

float DamageOverTime::reduceTick(float reduction) {
#ifdef DEBUG_DOTS
	info(true) << "reduceTick -- Pool: " << attribute << " Strength = " << strength << " Reduction: " << reduction;
#endif

	// this ensures we can't increase a dot strength
	if (reduction <= 0.f) {
#ifdef DEBUG_DOTS
		info(true) << "Reduction is less than 0 RETURNING: " << reduction;
#endif
		return reduction;
	}

	int reducRemaining = reduction - strength;

	strength -= reduction;
	strength = (strength < 0 ? 0 : strength);

#ifdef DEBUG_DOTS
	info(true) << "Remaining Cure: " << reducRemaining << " New Strength: " << strength;
#endif

	if (reducRemaining > 0) {
#ifdef DEBUG_DOTS
		info(true) << "DoT has been cured";
#endif
		expireTick();
	}

#ifdef DEBUG_DOTS
	info(true) << "reduceTick -- END";
#endif

	return reducRemaining;
}

void DamageOverTime::multiplyDuration(float multiplier) {
	Time newTime;
	uint64 timeToAdd = (expires.getMiliTime() - newTime.getMiliTime()) * multiplier;
	newTime.addMiliTime(timeToAdd);
	expires = newTime;

}
