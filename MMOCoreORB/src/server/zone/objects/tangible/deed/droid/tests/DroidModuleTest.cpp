/*
Copyright (C) 2013 <SWGEmu>

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

#include "gtest/gtest.h"
#include "server/zone/objects/tangible/deed/droid/DroidCraftingModule.h"
#include "server/zone/objects/tangible/deed/droid/DroidModule.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"

class DroidModuleTest : public ::testing::Test {
public:

	DroidModuleTest() {
		// Perform creation setup here.
	}

	~DroidModuleTest() {
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(DroidModuleTest, WeaponDroidTest) {

	int craftType = DroidCraftingModule::WEAPON_DROID_GENERIC;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_TRUE( module->isWeaponDroidGeneric() );
	EXPECT_FALSE( module->isClothingArmor());
	EXPECT_FALSE( module->isFoodChemical());
	EXPECT_FALSE( module->isShip());
	EXPECT_FALSE( module->isStructureFurniture());

}

TEST_F(DroidModuleTest, FoodChemicalTest) {

	int craftType = DroidCraftingModule::FOOD_CHEMICAL;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_FALSE( module->isWeaponDroidGeneric() );
	EXPECT_FALSE( module->isClothingArmor());
	EXPECT_TRUE( module->isFoodChemical());
	EXPECT_FALSE( module->isShip());
	EXPECT_FALSE( module->isStructureFurniture());

}

TEST_F(DroidModuleTest, ClothingArmor) {

	int craftType = DroidCraftingModule::CLOTHING_ARMOR;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_FALSE( module->isWeaponDroidGeneric() );
	EXPECT_TRUE( module->isClothingArmor());
	EXPECT_FALSE( module->isFoodChemical());
	EXPECT_FALSE( module->isShip());
	EXPECT_FALSE( module->isStructureFurniture());

}

TEST_F(DroidModuleTest, StructureFurnitureTest) {

	int craftType = DroidCraftingModule::STRUCTURE_FURNITURE;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_FALSE( module->isWeaponDroidGeneric() );
	EXPECT_FALSE( module->isClothingArmor());
	EXPECT_FALSE( module->isFoodChemical());
	EXPECT_FALSE( module->isShip());
	EXPECT_TRUE( module->isStructureFurniture());

}

TEST_F(DroidModuleTest, ShipTest) {

	int craftType = DroidCraftingModule::SHIP;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_FALSE( module->isWeaponDroidGeneric() );
	EXPECT_FALSE( module->isClothingArmor());
	EXPECT_FALSE( module->isFoodChemical());
	EXPECT_TRUE( module->isShip());
	EXPECT_FALSE( module->isStructureFurniture());

}

TEST_F(DroidModuleTest, MultiModuleTest) {

	int craftType = DroidCraftingModule::WEAPON_DROID_GENERIC +
					DroidCraftingModule::FOOD_CHEMICAL +
					DroidCraftingModule::CLOTHING_ARMOR +
					DroidCraftingModule::STRUCTURE_FURNITURE +
					DroidCraftingModule::SHIP;

	CraftingValues values;
	values.addExperimentalProperty("TEST","crafting_module",craftType,craftType,1,true,1);
	values.setCurrentValue("crafting_module",craftType);

	DroidCraftingModule* module = new DroidCraftingModule(&values);

	EXPECT_TRUE( module->isCraftingModule() );
	EXPECT_TRUE( module->isWeaponDroidGeneric() );
	EXPECT_TRUE( module->isClothingArmor());
	EXPECT_TRUE( module->isFoodChemical());
	EXPECT_TRUE( module->isShip());
	EXPECT_TRUE( module->isStructureFurniture());

}
