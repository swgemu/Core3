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

#include "DraftSchematicIngredientImplementation.h"

#include "../../packets/object/ObjectControllerMessage.h"

DraftSchematicIngredientImplementation::DraftSchematicIngredientImplementation(const String& ingredientTemplateName, const String& ingredientTitleName,
		const int slotoption, const String& resourceType, uint32 resourceQuantity, uint32 combineType,
		float contribution) : DraftSchematicIngredientServant() {
	DraftSchematicIngredientImplementation::templateName = ingredientTemplateName;
	DraftSchematicIngredientImplementation::titleName = ingredientTitleName;
	DraftSchematicIngredientImplementation::slotoption = slotoption;
	DraftSchematicIngredientImplementation::resourceType = resourceType;
	DraftSchematicIngredientImplementation::resourceQuantity = resourceQuantity;
	DraftSchematicIngredientImplementation::combineType = combineType;
	DraftSchematicIngredientImplementation::contribution = contribution;
}

DraftSchematicIngredientImplementation::DraftSchematicIngredientImplementation(DraftSchematicIngredient* ingredient) : DraftSchematicIngredientServant() {
	this->templateName = ingredient->getTemplateName();
	this->titleName = ingredient->getTitleName();
	this->slotoption = ingredient->getSlotType();
	this->resourceType = ingredient->getResourceType();
	this->resourceQuantity = ingredient->getResourceQuantity();
	this->combineType = ingredient->getCombineType();
}

void DraftSchematicIngredientImplementation::helperSendToPlayer(ObjectControllerMessage* msg) {
	msg->insertAscii(templateName); // ex: craft_food_ingredients_n
	msg->insertInt(0);
	msg->insertAscii(titleName); // ex: dried_fruit

	if (slotoption == OPTIONALIDENTICALSLOT || slotoption == OPTIONALMIXEDSLOT)
		msg->insertByte(1);  // ex: additive is optional so insertByte(1);
	else
		msg->insertByte(0);

	msg->insertInt(1);

	msg->insertAscii(templateName);  // ex: craft_food_ingredients_n
	msg->insertInt(0);
	msg->insertAscii(titleName);	// ex: dried_fruit

	UnicodeString uniResourceType(resourceType);
	msg->insertUnicode(uniResourceType); // ex: organic

	if (slotoption == MIXEDSLOT || slotoption == OPTIONALMIXEDSLOT) {
		msg->insertByte(5);  // Enables Components
		msg->insertInt(resourceQuantity); // ex: 3
	} else if (slotoption == IDENTICALSLOT || slotoption == OPTIONALIDENTICALSLOT) {
		msg->insertByte(2);
		msg->insertInt(resourceQuantity); // ex: 3
		msg->insertShort(0);
	} else if (slotoption == RESOURCESLOT) {
		msg->insertByte(4);
		msg->insertInt(resourceQuantity); // ex: 3
	}


}
