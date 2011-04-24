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

#include "PlayerCreationManager.h"
#include "RacialCreationData.h"
#include "ProfessionInfo.h"
#include "HairStyleInfo.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/creation/ProfessionDataForm.h"

PlayerCreationManager::PlayerCreationManager()
		: Logger("PlayerCreationManager") {

	setLogging(true);
	setGlobalLogging(false);

	racialCreationData.setNoDuplicateInsertPlan();
	professionInfo.setNoDuplicateInsertPlan();
	hairStyleInfo.setNoDuplicateInsertPlan();

	loadRacialCreationData();
	loadProfessionInfo();
	loadHairStyleInfo();
}

PlayerCreationManager::~PlayerCreationManager() {
}

void PlayerCreationManager::loadRacialCreationData() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile("datatables/creation/attribute_limits.iff");

	if (iffStream == NULL) {
		error("Could not open attribute limits file.");
		return;
	}

	DataTableIff attributeLimitsTable;
	attributeLimitsTable.readObject(iffStream);

	delete iffStream;

	iffStream = templateManager->openIffFile("datatables/creation/racial_mods.iff");

	DataTableIff racialModsTable;
	racialModsTable.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < attributeLimitsTable.getTotalRows(); ++i) {
		DataTableRow* attributeLimitRow = attributeLimitsTable.getRow(i);

		String maleTemplate;
		String femaleTemplate;

		attributeLimitRow->getValue(0, maleTemplate);
		attributeLimitRow->getValue(1, femaleTemplate);

		Vector<DataTableRow*> maleRows = racialModsTable.getRowsByColumn(0, maleTemplate);
		Vector<DataTableRow*> femaleRows = racialModsTable.getRowsByColumn(1, femaleTemplate);

		Reference<RacialCreationData*> rcd = new RacialCreationData();
		rcd->parseAttributeData(attributeLimitRow);

		if (!maleTemplate.isEmpty()) {
			if (maleRows.size() > 0)
				rcd->parseRacialModData(maleRows.get(0));

			racialCreationData.put(maleTemplate, rcd);
		}

		if (!femaleTemplate.isEmpty()) {
			if (femaleRows.size() > 0)
				rcd->parseRacialModData(femaleRows.get(0));

			racialCreationData.put(femaleTemplate, rcd);
		}
	}

	info("Loaded " + String::valueOf(racialCreationData.size()) + " playable species.");
}

void PlayerCreationManager::loadProfessionInfo() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile("creation/profession_defaults.iff");

	if (iffStream == NULL) {
		error("Could not open creation profession data.");
		return;
	}

	ProfessionDataForm pfdt;
	pfdt.readObject(iffStream);

	delete iffStream;

	//Load the data into useful structs and store them in a map.
	for (int i = 0; i < pfdt.getTotalPaths(); ++i) {
		String name = pfdt.getProfessionNameAt(i);
		String path = pfdt.getPathByProfessionName(name);

		iffStream = templateManager->openIffFile(path);

		if (iffStream == NULL)
			continue;

		Reference<ProfessionInfo*> pi = new ProfessionInfo();
		pi->readObject(iffStream);

		delete iffStream;

		professionInfo.put(name, pi);
	}

	//Now we want to load the profession mods.
	iffStream = templateManager->openIffFile("datatables/creation/profession_mods.iff");

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String key;
		row->getValue(0, key);

		//Check if the professionInfo for this exists.
		Reference<ProfessionInfo*> pi = professionInfo.get(key);

		if (pi == NULL)
			continue;

		for (int i = 1; i < 10; ++i) {
			int value = 0;
			row->getValue(i, value);
			pi->setAttributeMod(i - 1, value);
		}
	}

	info("Loaded " + String::valueOf(professionInfo.size()) + " creation professions.");
}

void PlayerCreationManager::loadHairStyleInfo() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("creation/default_pc_hairstyles.iff");

	if (iffStream == NULL) {
		error("Couldn't load creation hair styles.");
		return;
	}

	iffStream->openForm('HAIR');

	uint32 version = iffStream->getNextFormType();
	Chunk* versionChunk = iffStream->openForm(version);

	int totalHairStyles = 0;

	for (int i = 0; i < versionChunk->getChunksSize(); ++i) {
		Reference<HairStyleInfo*> hsi = new HairStyleInfo();
		hsi->readObject(iffStream);

		hairStyleInfo.put(hsi->getPlayerTemplate(), hsi);

		totalHairStyles += hsi->getTotalStyles();

		//info("Loaded " + String::valueOf(hsi->getTotalStyles()) + " hair styles for template " + hsi->getPlayerTemplate());
	}

	iffStream->closeForm(version);
	iffStream->closeForm('HAIR');

	delete iffStream;

	info("Loaded " + String::valueOf(totalHairStyles) + " total creation hair styles.");
}

void PlayerCreationManager::createCharacter() {
	//Validate character name

	//Validate racefile
	//Validate customization

	//validate location - ignore? they choose location in tutorial...

	//validate hair template is valid for the list
	//validate hair customization is valid for this hair template

	//validate profession is in starting profession list

	//unknown byte possibly pre-9 jedi flag

	//validate character height

	//validate biography

	//tutorial flag selected?
	//insertIntoTutorial?
}

bool PlayerCreationManager::validateCharacterName(const String& characterName) {
	return true;
}
