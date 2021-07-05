/*
 * ThreatMatrix.cpp
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */

#include "ThreatMatrix.h"
#include "ThreatMap.h"
#include "ThreatStates.h"
#include "server/zone/objects/tangible/TangibleObject.h"

ThreatMatrix::ThreatMatrix() : damageMap(1, 0), aggroMap(1, 0), healMap(1, 0) {
	tauntThreat = nullptr;
	focusedThreat = nullptr;
}

ThreatMatrix::~ThreatMatrix() {
}

ThreatMatrix::ThreatMatrix(const ThreatMatrix& e)
	: tauntThreat(e.tauntThreat), focusedThreat(e.focusedThreat), damageMap(e.damageMap), aggroMap(e.aggroMap), healMap(e.healMap) {
}

ThreatMatrix& ThreatMatrix::operator=(const ThreatMatrix& e) {
	if (this == &e)
		return *this;

	tauntThreat = e.tauntThreat;
	focusedThreat = e.focusedThreat;

	damageMap = e.damageMap;
	aggroMap = e.aggroMap;
	healMap = e.healMap;

	return *this;
}

void ThreatMatrix::clear() {
	tauntThreat = nullptr;
	focusedThreat = nullptr;

	if (damageMap.size() > 0)
		damageMap.removeAll();

	if (aggroMap.size() > 0)
		aggroMap.removeAll();

	if (healMap.size() > 0)
		healMap.removeAll();
}

void ThreatMatrix::add(TangibleObject* threat, ThreatMapEntry* entry) {
	// Get Total Damage
	uint32 totalDamage = entry->getTotalDamage() - entry->getNonAggroDamage();

	/// We don't want to add someone who hasn't done
	/// and damage to this
	if (totalDamage > 0)
		damageMap.put(totalDamage, threat);

	/// Anyone with an entry should be in this map
	if (entry->getAggroMod() > 0)
		aggroMap.put(entry->getAggroMod(), threat);

	/// Only healers should be in this map
	if (entry->getHeal() > 0)
		healMap.put(entry->getHeal(), threat);

	if (entry->hasState(ThreatStates::TAUNTED)) {
		tauntThreat = threat;
	}

	if (entry->hasState(ThreatStates::FOCUSED)) {
		focusedThreat = threat;
	}
}

TangibleObject* ThreatMatrix::getLargestThreat() {
	TangibleObject* returnThreat = nullptr;

	if (tauntThreat != nullptr) {
		returnThreat = tauntThreat;

	} else if (focusedThreat != nullptr) {
		returnThreat = focusedThreat;

	} else {
		Vector<TangibleObject*> targetSelection;
		if (damageMap.size() > 0) {
			targetSelection.add(damageMap.elementAt(damageMap.size() - 1).getValue());
			targetSelection.add(damageMap.elementAt(damageMap.size() - 1).getValue());
			targetSelection.add(damageMap.elementAt(System::random(damageMap.size() - 1)).getValue());
		}

		if (aggroMap.size() > 0) {
			targetSelection.add(aggroMap.elementAt(aggroMap.size() - 1).getValue());
			targetSelection.add(aggroMap.elementAt(aggroMap.size() - 1).getValue());
			targetSelection.add(aggroMap.elementAt(System::random(aggroMap.size() - 1)).getValue());
		}

		if (healMap.size() > 0) {
			targetSelection.add(healMap.elementAt(healMap.size() - 1).getValue());
		}

		if (targetSelection.size() > 0)
			returnThreat = targetSelection.get(System::random(targetSelection.size() - 1));
	}

#ifdef DEBUG
	print();

	if (returnThreat != nullptr)
		System::out << "Targeting " << returnThreat->getObjectID() << endl;
	else
		System::out << "Targeting Nothing" << endl;
#endif
	clear();
	return returnThreat;
}

void ThreatMatrix::print() {
	System::out << "************* Targets *****************" << endl;
	System::out << "Taunted by: ";
	if (tauntThreat != nullptr)
		System::out << tauntThreat->getObjectID() << endl;
	else
		System::out << "nullptr" << endl;

	System::out << "Focused on: ";
	if (focusedThreat != nullptr)
		System::out << focusedThreat->getObjectID() << endl;
	else
		System::out << "nullptr" << endl;

	System::out << "************* DamageMap ***************" << endl;
	for (int i = 0; i < damageMap.size(); ++i) {
		System::out << "DamageMap[" << i << "] " << damageMap.elementAt(i).getValue()->getObjectID() << " " << damageMap.elementAt(i).getKey() << endl;
	}

	System::out << "************* AggroMap ***************" << endl;
	for (int i = 0; i < aggroMap.size(); ++i) {
		System::out << "AggroMap[" << i << "] " << aggroMap.elementAt(i).getValue()->getObjectID() << " " << aggroMap.elementAt(i).getKey() << endl;
	}

	System::out << "************* HealMap ***************" << endl;
	for (int i = 0; i < healMap.size(); ++i) {
		System::out << "HealMap[" << i << "] " << healMap.elementAt(i).getValue()->getObjectID() << " " << healMap.elementAt(i).getKey() << endl;
	}
	System::out << "*************************************" << endl;
}
