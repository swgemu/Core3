/*
 * ThreatMatrix.cpp
 *
 *  Created on: 1/23/2012
 *      Author: Kyle
 */

#include "ThreatMatrix.h"
#include "ThreatMap.h"
#include "server/zone/objects/creature/CreatureObject.h"

ThreatMatrix::ThreatMatrix() : damageMap(1, 0), aggroMap(1, 0), healMap(1, 0) {
	tauntThreat = NULL;
	focusedThreat = NULL;
}

ThreatMatrix::~ThreatMatrix() {

}

ThreatMatrix::ThreatMatrix(const ThreatMatrix& e) {

}

ThreatMatrix& ThreatMatrix::operator=(const ThreatMatrix& e) {
	//VectorMap<ManagedReference<WeaponObject*>, uint32>::operator=(e);

	return *this;
}

void ThreatMatrix::clear() {

	tauntThreat = NULL;
	focusedThreat = NULL;

	if (damageMap.size() > 0)
		damageMap.removeAll();

	if (aggroMap.size() > 0)
		aggroMap.removeAll();

	if (healMap.size() > 0)
		healMap.removeAll();
}

void ThreatMatrix::add(CreatureObject* creature, ThreatMapEntry* entry) {

	if(!creature->isPlayerCreature())
		return;

	// Get Total Damage
	uint32 totalDamage = entry->getTotalDamage() - entry->getNonAggroDamage();

	/// We don't want to add someone who hasn't done
	/// and damage to this
	if(totalDamage > 0)
		damageMap.put(totalDamage, creature);

	/// Anyone with an entry should be in this map
	if (entry->getAggroMod() > 0)
		aggroMap.put(entry->getAggroMod(), creature);

	/// Only healers should be in this map
	if(entry->getHeal() > 0)
		healMap.put(entry->getHeal(), creature);

	if (entry->hasState(ThreatStates::TAUNTED)) {
		tauntThreat = creature;
	}

	if (entry->hasState(ThreatStates::FOCUSED)) {
		focusedThreat = creature;
	}
}

CreatureObject* ThreatMatrix::getLargestThreat() {

	CreatureObject* returnThreat = NULL;

	if(tauntThreat != NULL) {

		returnThreat = tauntThreat;

	} else if(focusedThreat != NULL) {

		returnThreat = focusedThreat;

	} else {

		Vector<CreatureObject*> targetSelection;
		if(damageMap.size() > 0) {
			targetSelection.add(damageMap.elementAt(damageMap.size() -1).getValue());
			targetSelection.add(damageMap.elementAt(damageMap.size() -1).getValue());
			targetSelection.add(damageMap.elementAt(System::random(damageMap.size() -1)).getValue());
		}

		if(aggroMap.size() > 0) {
			targetSelection.add(aggroMap.elementAt(aggroMap.size() -1).getValue());
			targetSelection.add(aggroMap.elementAt(aggroMap.size() -1).getValue());
			targetSelection.add(aggroMap.elementAt(System::random(aggroMap.size() -1)).getValue());
		}

		if(healMap.size() > 0) {
			targetSelection.add(healMap.elementAt(healMap.size() -1).getValue());
		}

		if (targetSelection.size() > 0)
			returnThreat = targetSelection.get(System::random(targetSelection.size()- 1));
	}


#ifdef DEBUG
	print();

	if(returnThreat != NULL)
		System::out << "Targeting " << returnThreat->getFirstName() << endl;
	else
		System::out << "Targeting Nothing" << endl;
#endif
	clear();
	return returnThreat;
}

void ThreatMatrix::print() {
	System::out << "************* Targets *****************" << endl;
	System::out << "Taunted by: ";
	if(tauntThreat != NULL)
		System::out << tauntThreat->getFirstName() << endl;
	else
		System::out << "NULL" << endl;

	System::out << "Focused on: ";
	if(focusedThreat != NULL)
		System::out << focusedThreat->getFirstName() << endl;
	else
		System::out << "NULL" << endl;

	System::out << "************* DamageMap ***************" << endl;
	for(int i = 0; i < damageMap.size(); ++i) {
		System::out << "DamageMap["  << i << "] "
				<< damageMap.elementAt(i).getValue()->getFirstName()
				<< " " << damageMap.elementAt(i).getKey() << endl;

	}

	System::out << "************* AggroMap ***************" << endl;
	for(int i = 0; i < aggroMap.size(); ++i) {
		System::out << "AggroMap["  << i << "] "
				<< aggroMap.elementAt(i).getValue()->getFirstName()
				<< " " << aggroMap.elementAt(i).getKey() << endl;

	}

	System::out << "************* HealMap ***************" << endl;
	for(int i = 0; i < healMap.size(); ++i) {
		System::out << "HealMap["  << i << "] "
				<< healMap.elementAt(i).getValue()->getFirstName()
				<< " " << healMap.elementAt(i).getKey() << endl;
	}
	System::out << "*************************************" << endl;

}



