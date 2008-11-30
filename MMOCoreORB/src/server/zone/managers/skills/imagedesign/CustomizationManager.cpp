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

#include "CustomizationManager.h"

CustomizationManager::CustomizationManager() {
	loadCustomizationData();

	customizations.setNullValue(NULL);
}


CustomizationManager::~CustomizationManager() {
	for (int i = 0; i < customizations.size(); ++i)
	{
		if (customizations.get(i) != NULL)
			delete customizations.get(i);
	}
}

void CustomizationManager::loadCustomizationData() {
	customizations.removeAll();

	try {
		String query = "SELECT * FROM customization_data";

		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		while (res->next()) {
			CustomizationData *customization = new CustomizationData();

			customization->setSpeciesGender(res->getString(0));
			customization->setCustomizationGroup(res->getString(1));
			customization->setType(res->getString(2));
			customization->setCustomizationName(res->getString(3));
			customization->setVariables(res->getString(4));
			customization->setIsScale(res->getBoolean(5));
			customization->setReverse(res->getBoolean(6));
			customization->setColorLinked(res->getString(7));
			customization->setColorLinkedtoSelf0(res->getString(8));
			customization->setColorLinkedtoSelf1(res->getString(9));
			customization->setCameraYaw(res->getInt(10));
			customization->setDiscrete(res->getBoolean(11));
			customization->setRandomizable(res->getBoolean(12));
			customization->setRandomizableGroup(res->getBoolean(13));
			customization->setIsVarHairColor(res->getBoolean(14));
			customization->setImageDesignSkillMod(res->getString(15));
			customization->setSkillModValue(res->getInt(16));
			customization->setModificationType(res->getString(17));
			customization->setMaxChoices(res->getInt(18));
			customization->setMinScale(res->getFloat(19));
			customization->setMaxScale(res->getFloat(20));

			StringBuffer speciesGenderCustomization;
			speciesGenderCustomization << customization->getSpeciesGender() << "_" << customization->getCustomizationName();
			customizations.put(speciesGenderCustomization.toString(), customization);
			loadedCount++;
		}

		delete res;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << endl;
	} catch (...) {
		System::out << "unreported exception caught in CustomizationManager::loadCustomizationData()\n";
	}
}

CustomizationData* CustomizationManager::getCustomizationData(String speciesGender, String customizationName) {
	StringBuffer speciesGenderCustomization;
	speciesGenderCustomization << speciesGender << "_" << customizationName;

	CustomizationData *customization = customizations.get(speciesGenderCustomization.toString());
	return customization;
}
