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

#include "engine/engine.h"
#include "../../../ZoneProcessServerImplementation.h"

#include "PerformanceManager.h"


PerformanceManager::PerformanceManager() {
	loadPerformances();
}

PerformanceManager::~PerformanceManager() {
	if (performances != NULL) {
		for (int i = 0; i < performances->size(); ++i)
			delete performances->get(i);

		delete performances;

		performances = NULL;
	}
}

void PerformanceManager::loadPerformances() {
	performances = new Vector<Performance*>();

	try {
		String query = "SELECT * FROM performance";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			Performance *performance = new Performance();

			performance->setName(res->getString(0));
			performance->setInstrumentAudioId(res->getInt(1));
			performance->setRequiredSong(res->getString(2));
			performance->setRequiredInstrument(res->getString(3));
			performance->setRequiredDance(res->getString(4));
			performance->setDanceVisualId(res->getInt(5));
			performance->setActionPointsPerLoop(res->getInt(6));
			performance->setLoopDuration(res->getFloat(7));
			performance->setType(res->getInt(8));
			performance->setBaseXp(res->getInt(9));
			performance->setFlourishXpMod(res->getInt(10));
			performance->setHealMindWound(res->getInt(11));
			performance->setHealShockWound(res->getInt(12));
			performance->setRequiredSkillMod(res->getString(13));
			performance->setRequiredSkillModValue(res->getInt(14));
			performance->setMainloop(res->getString(15));
			performance->setFlourish1(res->getString(16));
			performance->setFlourish2(res->getString(17));
			performance->setFlourish3(res->getString(18));
			performance->setFlourish4(res->getString(19));
			performance->setFlourish5(res->getString(20));
			performance->setFlourish6(res->getString(21));
			performance->setFlourish7(res->getString(22));
			performance->setFlourish8(res->getString(23));
			performance->setIntro(res->getString(24));
			performance->setOutro(res->getString(25));

			performances->add(performance);
			loadedCount++;
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in PerformanceManager::loadPerformances()\n";
	}

}

Performance *PerformanceManager::getDance(String name) {
	if (performances != NULL) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance *ret = performances->get(i);
			if (ret->isDance() && ret->getName() == name)
				return ret;
		}
	}
	return NULL;
}

Performance *PerformanceManager::getSong(String name, int instrumentType) {
	if (performances != NULL) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance *ret = performances->get(i);
			if (ret->isMusic() && ret->getName() == name && ret->getInstrumentAudioId() == instrumentType)
				return ret;
		}
	}
	return NULL;
}
