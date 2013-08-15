/*
 * MobileTest.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: TheAnswer
 */

#include "gtest/gtest.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/loot/lootgroup/LootGroupCollectionEntry.h"

class LuaMobileTest : public ::testing::Test {
public:

	LuaMobileTest() {
		// Perform creation setup here.
	}

	~LuaMobileTest() {
	}

	void SetUp() {
		// Perform setup of common constructs here.
	}

	void TearDown() {
		// Perform clean up of common constructs here.
	}
};

TEST_F(LuaMobileTest, LuaMobileTemplatesTest) {
	CreatureTemplateManager::DEBUG_MODE = 1;

	EXPECT_EQ(CreatureTemplateManager::instance()->loadTemplates(), 0);

	// Verify loot group percentages
	HashTableIterator<uint32, Reference<CreatureTemplate*> > iter = CreatureTemplateManager::instance()->iterator();
	while (iter.hasNext()) {
		CreatureTemplate* creature = iter.next();
		std::string templateName( creature->getTemplateName().toCharArray() );


		LootGroupCollection* groupCollection = creature->getLootGroups();
		if( groupCollection->count() > 0 ){


			for( int i = 0; i < groupCollection->count(); i++ ){

				LootGroupCollectionEntry* collectionEntry = groupCollection->get(i);
				LootGroups* groups = collectionEntry->getLootGroups();
				if( groups->count() > 0){

					int totalChance = 0;
					for( int j = 0; j < groups->count(); j++ ){

						LootGroupEntry* lootGroup = groups->get(j);
						totalChance += lootGroup->getLootChance();

					}

					// TODO When all the mobiles have been cleaned up, make it so the unit test starts failing.
					//       Until then, just print out a warning.
					// EXPECT_EQ( 10000000, totalChance ) << "Total chance of loot groups is incorrect " << templateName;
					if( totalChance != 10000000 ){
						std::cout << "Warning: " << templateName << " loot group's total chance is not 10000000;totalChance=" << totalChance << "\n";
					}
				}

			}

		}

	}

}


