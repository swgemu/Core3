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

#include "SharedLabratory.h"
#include "server/zone/managers/crafting/CraftingManager.h"

SharedLabratory::SharedLabratory() : Logger("SharedLabratory"){
}

SharedLabratory::~SharedLabratory() {
}

bool SharedLabratory::allowFactoryRun(ManufactureSchematic* manufactureSchematic) {
	return manufactureSchematic->allowFactoryRun();
}

void SharedLabratory::initialize(ZoneServer* server) {
	zoneServer = server;
}

float SharedLabratory::calculateExperimentationValueModifier(int experimentationResult, int pointsAttempted) {
	// Make it so failure detract
	float results;
	switch (experimentationResult) {
	case CraftingManager::AMAZINGSUCCESS:
		results = 0.08f;
		break;
	case CraftingManager::GREATSUCCESS:
		results = 0.07f;
		break;
	case CraftingManager::GOODSUCCESS:
		results = 0.055f;
		break;
	case CraftingManager::MODERATESUCCESS:
		results = 0.015f;
		break;
	case CraftingManager::SUCCESS:
		results = 0.01f;
		break;
	case CraftingManager::MARGINALSUCCESS:
		results = 0.00f;
		break;
	case CraftingManager::OK:
		results = -0.04f;
		break;
	case CraftingManager::BARELYSUCCESSFUL:
		results = -0.07f;
		break;
	case CraftingManager::CRITICALFAILURE:
		results = -0.08f;
		break;
	default:
		results = 0;
		break;
	}
	results *= pointsAttempted;
	return results;
}
float SharedLabratory::calculateAssemblyValueModifier(int assemblyResult) {

	if(assemblyResult == CraftingManager::AMAZINGSUCCESS)
		return 1.05f;
	float result = 1.1f - (assemblyResult * .1f);
	return result;
}

float SharedLabratory::getAssemblyPercentage(float value) {

	float percentage = (value * (0.000015f * value + .015f)) * 0.01f;
	return percentage;
}
float SharedLabratory::getWeightedValue(ManufactureSchematic* manufactureSchematic, int type) {

	int nsum = 0;
	float weightedAverage = 0;
	int n = 0;
	int stat = 0;

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		Reference<IngredientSlot* > ingredientslot = manufactureSchematic->getSlot(i);
		Reference<DraftSlot* > draftslot = manufactureSchematic->getDraftSchematic()->getDraftSlot(i);

		/// If resource slot, continue
		if(!ingredientslot->isResourceSlot())
			continue;

		ResourceSlot* resSlot = cast<ResourceSlot*>(ingredientslot.get());

		if(resSlot == NULL)
			continue;

		ManagedReference<ResourceSpawn* > spawn = resSlot->getCurrentSpawn();

		if (spawn == NULL) {
			error("Spawn object is null when running getWeightedValue");
			return 0.0f;
		}

		n = draftslot->getQuantity();
		stat = spawn->getValueOf(type);

		if (stat != 0) {

			nsum += n;
			weightedAverage += (stat * n);
		}
	}

	if (weightedAverage != 0)
		weightedAverage /= float(nsum);

	return weightedAverage;
}

