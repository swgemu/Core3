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

#ifndef DRAFTSCHEMATICINGREDIENTIMPLEMENTATION_H_
#define DRAFTSCHEMATICINGREDIENTIMPLEMENTATION_H_

#include "DraftSchematicIngredient.h"

class ObjectControllerMessage;

class DraftSchematicIngredientImplementation : public DraftSchematicIngredientServant {

	// example: craft_food_ingredients_n
	String templateName;
	// example: dried Fruit
	String titleName;

	// example: organic
	String resourceType;
	// example: 3
	uint32 resourceQuantity;

	// example: 2 = Identical items required, 1 = optional, 0 = standard
	int slotoption;

	// Math Type
	uint32 combineType;

	// Contribution level
	float contribution;

public:

	static const int RESOURCESLOT = 0;
	static const int IDENTICALSLOT = 1;
	static const int MIXEDSLOT = 2;
	static const int OPTIONALIDENTICALSLOT = 3;
	static const int OPTIONALMIXEDSLOT = 4;

public:
	DraftSchematicIngredientImplementation(const String& ingredientTemplateName, const String& ingredientTitleName,
			const int slotoption, const String& resourceType, uint32 resourceQuantity, uint32 combineType,
			float contribution);

	DraftSchematicIngredientImplementation(DraftSchematicIngredient* ingredient);

	void helperSendToPlayer(ObjectControllerMessage* msg);

	// getters
	inline String& getTemplateName() {
		return templateName;
	}

	inline String& getTitleName() {
		return titleName;
	}

	inline String& getResourceType() {
		return resourceType;
	}

	inline uint32 getResourceQuantity() {
		return resourceQuantity;
	}

	inline uint32 getCombineType() {
		return combineType;
	}

	inline bool isOptionalSlot() {
		return (slotoption == OPTIONALIDENTICALSLOT || slotoption == OPTIONALMIXEDSLOT);
	}

	inline bool isIdenticalSlot() {
		return (slotoption == IDENTICALSLOT || slotoption == OPTIONALIDENTICALSLOT);
	}

	inline bool isMixedSlot() {
		return slotoption == MIXEDSLOT;
	}

	inline bool isResourceSlot() {
		return slotoption == RESOURCESLOT;
	}

	inline int getSlotType() {
		return slotoption;
	}

	inline float getContribution() {
		return contribution;
	}

};

#endif /*DRAFTSCHEMATICINGREDIENTIMPLEMENTATION_H_*/
