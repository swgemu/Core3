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
#include "server/zone/ZoneProcessServer.h"

#include "PerformanceManager.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/objects/tangible/Instrument.h"

PerformanceManager::PerformanceManager(): Logger("PerformanceManager") {
	loadPerformances();

	danceMap.put("basic", "dance_1");
	danceMap.put("basic2", "dance_2");
	danceMap.put("rhythmic", "dance_3");
	danceMap.put("rhythmic2", "dance_4");
	danceMap.put("exotic", "dance_5");
	danceMap.put("exotic2", "dance_6");
	danceMap.put("exotic3", "dance_7");
	danceMap.put("exotic4", "dance_8");
	danceMap.put("popular", "dance_9");
	danceMap.put("popular2", "dance_10");
	danceMap.put("lyrical", "dance_11");
	danceMap.put("lyrical2", "dance_12");
	danceMap.put("poplock", "dance_13");
	danceMap.put("poplock2", "dance_14");
	danceMap.put("footloose", "dance_15");
	danceMap.put("footloose2", "dance_16");
	danceMap.put("formal", "dance_17");
	danceMap.put("formal2", "dance_18");
	danceMap.put("theatrical", "dance_21");
	danceMap.put("theatrical2", "dance_22");
	danceMap.put("breakdance", "dance_29");
	danceMap.put("breakdance2", "dance_30");
	danceMap.put("tumble", "dance_31");
	danceMap.put("tumble2", "dance_32");

	instrumentIdMap.put("starwars1", 1);
	instrumentIdMap.put("rock", 11);
	instrumentIdMap.put("starwars2", 21);
	instrumentIdMap.put("folk", 31);
	instrumentIdMap.put("starwars3", 41);
	instrumentIdMap.put("ceremonial", 51);
	instrumentIdMap.put("ballad", 61);
	instrumentIdMap.put("waltz", 71);
	instrumentIdMap.put("jazz", 81);
	instrumentIdMap.put("virtuoso", 91);
	instrumentIdMap.put("western", 101);
	instrumentIdMap.put("starwars4", 111);
	instrumentIdMap.put("funk", 121);



}

int PerformanceManager::getInstrumentAnimation(int instrumentType, String& instrumentAnimation) {
	int instrid = 0;

	switch(instrumentType) {
	case Instrument::SLITHERHORN: //SLITHERHORN: yeah!
		instrid += 0;
		instrumentAnimation = "music_3";
		break;
	case Instrument::FIZZ: // yeah
		instrid += 1;
		instrumentAnimation = "music_3";
		break;
	case Instrument::FANFAR: //FANFAR yeah
		instrid += 2;
		instrumentAnimation = "music_3";
		break;
	case Instrument::KLOOHORN: // yeah
		instrid += 3;
		instrumentAnimation = "music_3";
		break;
	case Instrument::MANDOVIOL: //MANDOVIOL
		instrid += 4;
		instrumentAnimation = "music_5";
		break;
	case Instrument::TRAZ: //TRAZ yeah
		instrid += 5;
		instrumentAnimation = "music_3";
		break;
	case Instrument::BANDFILL: // yeah
		instrid += 6;
		instrumentAnimation = "music_1";
		break;
	case Instrument::FLUTEDROOPY: //
		instrid += 7;
		instrumentAnimation = "music_3";
		break;
	case Instrument::OMNIBOX: //OMNIBOX:
		instrid += 8;
		instrumentAnimation = "music_4";
		break;
	case Instrument::NALARGON: //NALARGON:
		instrid += 9;
		instrumentAnimation = "music_2";
		break;
	default:
		//sendSystemMessage("Bad instrument type.");
		break;
	}

	return instrid;
}

String PerformanceManager::getInstrument(int instrumentType) {
	String instrument;

	switch (instrumentType) {
	case Instrument::SLITHERHORN: //SLITHERHORN: yeah!
		instrument = "slitherhorn";
		break;
	case Instrument::FIZZ: // yeah
		instrument = "fizz";
		break;
	case Instrument::FANFAR: //FANFAR yeah
		instrument = "fanfar";
		break;
	case Instrument::KLOOHORN: // yeah
		instrument = "kloohorn";
		break;
	case Instrument::MANDOVIOL: //MANDOVIOL
		instrument = "mandoviol";
		break;
	case Instrument::TRAZ: //TRAZ yeah
		instrument = "traz";
		break;
	case Instrument::BANDFILL: // yeah
		instrument = "bandfill";
		break;
	case Instrument::FLUTEDROOPY: //
		instrument = "flutedroopy";
		break;
	case Instrument::OMNIBOX: //OMNIBOX:
		instrument = "omnibox";
		break;
	case Instrument::NALARGON: //NALARGON:
		instrument = "nalargon";
		break;
	default:
		//sendSystemMessage("Bad instrument type.");
		break;
	}

	return instrument;
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

	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/performance/performance.iff");

	if (iffStream == NULL) {
		error("Could not open performances datatable.");
		return;
	}

	DataTableIff dtable;
	dtable.readObject(iffStream);

	delete iffStream;

	performances = new Vector<Performance*>();
	for (int i = 0; i < dtable.getTotalRows(); ++i) {
		DataTableRow* row = dtable.getRow(i);

		Performance* performance = new Performance();
		performance->parseDataTableRow(row);
		performances->add(performance);
	}

	info("Loaded " + String::valueOf(performances->size()) + " performances.", true);

}

Performance* PerformanceManager::getDance(const String& name) {
	if (performances != NULL) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* ret = performances->get(i);

			if (ret->isDance() && ret->getName() == name)
				return ret;
		}
	}

	return NULL;
}

Performance* PerformanceManager::getSong(const String& name, int instrumentType) {
	if (performances != NULL) {
		for (int i = 0; i < performances->size(); ++i) {
			Performance* ret = performances->get(i);

			if (ret->isMusic() && ret->getName() == name && ret->getInstrumentAudioId() == instrumentType)
				return ret;
		}
	}
	return NULL;
}
