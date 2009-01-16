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

#ifndef DRINKIMPLEMENTATION_H_
#define DRINKIMPLEMENTATION_H_

//#include "../Consumable.h"
#include "Drink.h"

#include "../../../player/Player.h"
#include "../../../../Zone.h"
#include "../../../../managers/item/ItemManager.h"

class DrinkImplementation : public DrinkServant {
private:
	int nutrition;
	int flavor;
	int quantity;
	int filling;

public:

	DrinkImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn);
	DrinkImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn);

	~DrinkImplementation();

	void initialize();

	int useObject(Player* player);

	void generateAttributes(SceneObject* obj);
	void updateCraftingValues(DraftSchematic* draftSchematic);

	virtual void parseItemAttributes();
	virtual void addAttributes(AttributeListMessage* alm);
	void addHeaderAttributes(AttributeListMessage* alm);
	void addFooterAttributes(AttributeListMessage* alm);

	inline void setNutrition(int n){
		nutrition = n;
		String attr("nutrition");//might not need to display this one, i dont remember
		itemAttributes->setIntAttribute(attr, (int)nutrition);
	}

	inline void setFlavor(int f){
		flavor = f;
		String attr("flavor");//might not need to display this one, i dont remember
		itemAttributes->setIntAttribute(attr, (int)flavor);
	}

	inline void setQuantity(int q){
		quantity = q;
		String attr("quantity");
		itemAttributes->setIntAttribute(attr, (int)quantity);
	}

	inline void setFilling(int f){
		filling = f;
		String attr("filling");
		itemAttributes->setIntAttribute(attr, (int)filling);
	}

	inline int getNutrition(){
		return nutrition;
	}

	inline int getFlavor(){
		return flavor;
	}

	inline int getQuantity(){
		return quantity;
	}

	inline int getFilling(){
		return filling;
	}
};

#endif /* DRINKIMPLEMENTATION_H_ */
