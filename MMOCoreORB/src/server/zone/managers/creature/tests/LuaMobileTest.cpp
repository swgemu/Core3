/*
 * MobileTest.cpp
 *
 *  Created on: Aug 10, 2013
 *      Author: TheAnswer
 */

#include "gtest/gtest.h"
#include "server/zone/templates/LootItemTemplate.h"
#include "server/zone/templates/LootGroupTemplate.h"
#include "server/zone/managers/loot/LootGroupMap.h"
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

	// Verify that all mobiles load
	EXPECT_EQ(CreatureTemplateManager::instance()->loadTemplates(), 0);

	// Verify loot group map loads
	LootGroupMap* lootGroupMap = LootGroupMap::instance();
	EXPECT_EQ(lootGroupMap->initialize(), 0);

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

						// I'll enable this test when everything that needs to be fixed is merged
//						LootGroupTemplate* foundGroup = lootGroupMap->getLootGroupTemplate( lootGroup->getLootGroupName() );
//						std::string groupName( lootGroup->getLootGroupName().toCharArray() );
//						EXPECT_TRUE( foundGroup != NULL ) << "Loot group " << groupName << " from " << templateName << " was not found in LootGroupMap";

					}

					EXPECT_EQ( 10000000, totalChance ) << "Loot groups total chance is incorrect " << templateName;
				}
			}
		}
	}

}

TEST_F(LuaMobileTest, LuaLootGroupsTest) {

	LootGroupMap* lootGroupMap = LootGroupMap::instance();
	EXPECT_EQ(lootGroupMap->initialize(), 0);

	HashTableIterator<String, Reference<LootGroupTemplate*> > iter = lootGroupMap->groupTemplates.iterator();
	while (iter.hasNext()) {

		LootGroupTemplate* lootGroupTemplate = iter.next();
		std::string groupTemplateName( lootGroupTemplate->getTemplateName().toCharArray() );

		// Check non-empty loot groups
		if( lootGroupTemplate->getLootItemTemplateForRoll(-1).length() > 0  ){
			EXPECT_GT( lootGroupTemplate->getLootItemTemplateForRoll(10000000).length(), 0 ) << "Item total chance is less than 10000000: " << groupTemplateName;
			EXPECT_EQ( lootGroupTemplate->getLootItemTemplateForRoll(10000001).length(), 0 ) << "Item total chance is greater than 10000000: " << groupTemplateName;
		}

		// Check that all items exist
		// I'll enable this test when everything that needs to be fixed is merged
//		for( int i = 0; i < lootGroupTemplate->size(); i++ ){
//
//			String itemTemplateName = lootGroupTemplate->getLootItemTemplateAt(i);
//			if( !itemTemplateName.isEmpty() ){
//				Reference<LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate( itemTemplateName );
//				EXPECT_TRUE( itemTemplate != NULL ) << "Item template " << std::string(itemTemplateName.toCharArray()) << " from " << groupTemplateName << " was not found in LootGroupMap";
//			}
//
//		}

	}

}


