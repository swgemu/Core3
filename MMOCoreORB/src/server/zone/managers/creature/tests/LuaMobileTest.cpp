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

	void checkLootGroupEntryRecursive(LootGroupMap* lootGroupMap, String& entryName, Vector<String>* parentGroups) {
		if (entryName.isEmpty())
			return;

		//Check for infinite recursion
		for (int i = 0; i < parentGroups->size(); i++) {
			String parentName = parentGroups->get(i);

			EXPECT_FALSE( parentName == entryName ) << "Loot group " << std::string(parentName.toCharArray()) << " failed recursion check.";

			if (parentName == entryName)
				return;
		}

		if (lootGroupMap->lootGroupExists(entryName)) {

			LootGroupTemplate* lootGroupTemplate = lootGroupMap->getLootGroupTemplate(entryName);

			for (int j = 0; j < lootGroupTemplate->size(); j++) {

				String entry = lootGroupTemplate->getLootGroupEntryAt(j);

				parentGroups->add(entryName);

				checkLootGroupEntryRecursive(lootGroupMap, entry, parentGroups);
			}

		} else {
			Reference<LootItemTemplate*> itemTemplate = lootGroupMap->getLootItemTemplate( entryName );
			EXPECT_TRUE( itemTemplate != NULL ) << "Item template " << std::string(entryName.toCharArray()) << " from " << std::string(parentGroups->get(parentGroups->size() - 1).toCharArray()) << " was not found in LootGroupMap";
		}
	}
};

TEST_F(LuaMobileTest, LuaMobileTemplatesTest) {
	CreatureTemplateManager::DEBUG_MODE = 1;

	// Verify that all mobiles load
	ASSERT_EQ(CreatureTemplateManager::instance()->loadTemplates(), 0);

	// Verify loot group map loads
	LootGroupMap* lootGroupMap = LootGroupMap::instance();
	ASSERT_EQ(lootGroupMap->initialize(), 0);

	// Load Templates
	ASSERT_TRUE( TemplateManager::instance() != NULL );
	if( TemplateManager::instance()->loadedTemplatesCount == 0 ){
		TemplateManager::instance()->loadLuaTemplates();
	}

	// Test Creature Templates
	HashTableIterator<uint32, Reference<CreatureTemplate*> > creatureIterator = CreatureTemplateManager::instance()->iterator();
	while (creatureIterator.hasNext()) {
		CreatureTemplate* creature = creatureIterator.next();
		std::string templateName( creature->getTemplateName().toCharArray() );

		// Verify loot group percentages
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

						// Verify loot group is configured correctly
						LootGroupTemplate* foundGroup = lootGroupMap->getLootGroupTemplate( lootGroup->getLootGroupName() );
						std::string groupName( lootGroup->getLootGroupName().toCharArray() );
						EXPECT_TRUE( foundGroup != NULL ) << "Loot group " << groupName << " from " << templateName << " was not found in LootGroupMap";

					}

					EXPECT_EQ( 10000000, totalChance ) << "Loot groups total chance is incorrect " << templateName;
				}
			}
		}

		// Verify weapon groups exist
		Vector<String> weapons = creature->getWeapons();
		for (int i = 0; i < weapons.size(); i++) {
			String weaponGroup = weapons.get(i);
			std::string groupName( weaponGroup.toCharArray() );
			Vector<String> group = CreatureTemplateManager::instance()->getWeapons(weaponGroup);
			EXPECT_TRUE( group.size() > 0 ) << "Weapon group " << groupName << " from " << templateName << " was not found in weaponMap";
		}
	}

	// Test Lair Templates
	HashTableIterator<uint32, Reference<LairTemplate*> > lairIterator = CreatureTemplateManager::instance()->lairTemplateIterator();
	while (lairIterator.hasNext()) {
		LairTemplate* lair = lairIterator.next();
		std::string templateName( lair->getName().toCharArray() );

		// Verify that mobiles exist and that their weighting is positive
		VectorMap<String, int>* mobiles = lair->getMobiles();
		for (int i = 0; i < mobiles->size(); i++) {
			int weighting = mobiles->elementAt(i).getValue();
			String mobile = mobiles->elementAt(i).getKey();
			std::string mobName = mobile.toCharArray();
			EXPECT_TRUE( CreatureTemplateManager::instance()->getTemplate(mobile) != NULL ) << "Mobile " << mobName << " in lair template " << templateName << " does not exist";
			EXPECT_TRUE( weighting > 0 ) << "Mobile " << mobName << " in lair template " << templateName << " has a non positive weighting";
		}

		// Verify that boss mobiles exist and that their count is positive
		VectorMap<String, int>* bossMobiles = lair->getBossMobiles();
		for (int i = 0; i < bossMobiles->size(); i++) {
			int count = bossMobiles->elementAt(i).getValue();
			String bossMob = bossMobiles->elementAt(i).getKey();
			std::string bossName = bossMob.toCharArray();
			EXPECT_TRUE( CreatureTemplateManager::instance()->getTemplate(bossMob) != NULL ) << "Boss mobile " << bossName << " in lair template " << templateName << " does not exist";
			EXPECT_TRUE( count > 0 ) << "Boss mobile " << bossName << " in lair template " << templateName << " has a non positive spawn count";
		}

		// Verify spawn limit is positive
		int limit = lair->getSpawnLimit();
		EXPECT_TRUE( limit > 0 ) << "Spawn limit in lair template " << templateName << " is not positive";

		// Verify any configured buildings exist
		for(int i=0; i<=4; i++){

			Vector<String>* buildings = lair->getBuildings( i );
			if( buildings == NULL )
				continue;

			for( int j=0; j < buildings->size(); j++ ){
				String buildingTemplate = buildings->get(j);
				std::string buildingStr = buildingTemplate.toCharArray();
				SharedObjectTemplate* templateObject = TemplateManager::instance()->getTemplate(buildingTemplate.hashCode());
				EXPECT_TRUE( templateObject != NULL && templateObject->isSharedTangibleObjectTemplate() ) << "Building template " << buildingStr << " in lair template " << templateName << " does not exist";
				if( lair->getBuildingType() == LairTemplate::LAIR ){
					EXPECT_TRUE( buildingTemplate.beginsWith( "object/tangible/lair/") ) << "Building template " << buildingStr << " in lair template " << templateName << " is not a child of object/tangible/lair/";
				}
				if( lair->getBuildingType() == LairTemplate::THEATER ){
					EXPECT_TRUE( buildingTemplate.beginsWith( "object/building/poi/") ) << "Building template " << buildingStr << " in lair template " << templateName << " is not a child of object/building/poi/";
				}
			}
		}

		// TODO: Add test to enforce LAIRs and THEATERs have at least one building configured

	}

	// Test Spawn Groups
	HashTableIterator<uint32, Reference<SpawnGroup*> > spawnIterator = CreatureTemplateManager::instance()->spawnGroupIterator();
	while (spawnIterator.hasNext()) {
		SpawnGroup* group = spawnIterator.next();
		std::string templateName( group->getTemplateName().toCharArray() );

		// Verify spawn limit is not negative
		int limit = group->getMaxSpawnLimit();
		EXPECT_TRUE( limit >= 0 ) << "Max spawn limit in spawn group " << templateName << " is negative";

		// Verify spawn list
		Vector<Reference<LairSpawn*> >* spawnList = group->getSpawnList();
		for (int i = 0; i < spawnList->size(); i++) {
			LairSpawn* spawn = spawnList->get(i);
			std::string lairName( spawn->getLairTemplateName().toCharArray() );

			// Verify lair template exists
			String lairTemplateName = spawn->getLairTemplateName();
			Reference<LairTemplate*> lairTemplate = CreatureTemplateManager::instance()->getLairTemplate(lairTemplateName.hashCode());
			EXPECT_TRUE( lairTemplate != NULL ) << "Lair template " << lairName << " in spawn group " << templateName << " does not exist.";

			// Verify spawn limit is at least -1
			float spawnLimit = spawn->getSpawnLimit();
			EXPECT_TRUE( spawnLimit >= -1 ) << "SpawnLimit for lairTemplate " << lairName << " in spawn group " << templateName << " is less than -1.";

			// Verify difficulties
			int minDiff = spawn->getMinDifficulty();
			int maxDiff = spawn->getMaxDifficulty();
			EXPECT_TRUE( minDiff > 0 ) << "MinDifficulty for lairTemplate " << lairName << " in spawn group " << templateName << " is not positive.";
			EXPECT_TRUE( maxDiff >= minDiff ) << "MaxDifficulty for lairTemplate " << lairName << " in spawn group " << templateName << " is less than min difficulty.";

			// Verify number to spawn is not negative
			int numberToSpawn = spawn->getNumberToSpawn();
			EXPECT_TRUE( numberToSpawn >= 0 ) << "NumberToSpawn for lairTemplate " << lairName << " in spawn group " << templateName << " is negative.";

			// Verify weighting is positive
			int weighting = spawn->getWeighting();
			EXPECT_TRUE( weighting > 0 ) << "Weighting for lairTemplate " << lairName << " in spawn group " << templateName << " is not positive.";

			// Verify size is at least 1
			float size = spawn->getSize();
			EXPECT_TRUE( size >= 1 ) << "Size for lairTemplate " << lairName << " in spawn group " << templateName << " is less than 1.";
		}
	}

	// Test Destroy Mission Spawn Groups
	HashTableIterator<uint32, Reference<SpawnGroup*> > missionIterator = CreatureTemplateManager::instance()->destroyMissionGroupIterator();
	while (missionIterator.hasNext()) {
		SpawnGroup* group = missionIterator.next();
		std::string templateName( group->getTemplateName().toCharArray() );

		// Verify spawn list
		Vector<Reference<LairSpawn*> >* spawnList = group->getSpawnList();
		for (int i = 0; i < spawnList->size(); i++) {
			LairSpawn* spawn = spawnList->get(i);
			std::string lairName( spawn->getLairTemplateName().toCharArray() );

			// Verify lair template exists
			String lairTemplateName = spawn->getLairTemplateName();
			Reference<LairTemplate*> lairTemplate = CreatureTemplateManager::instance()->getLairTemplate(lairTemplateName.hashCode());
			EXPECT_TRUE( lairTemplate != NULL ) << "Lair template " << lairName << " in spawn group " << templateName << " does not exist.";

			// Verify difficulties
			int minDiff = spawn->getMinDifficulty();
			int maxDiff = spawn->getMaxDifficulty();
			EXPECT_TRUE( minDiff > 0 ) << "MinDifficulty for lairTemplate " << lairName << " in spawn group " << templateName << " is not positive.";
			EXPECT_TRUE( maxDiff >= minDiff ) << "MaxDifficulty for lairTemplate " << lairName << " in spawn group " << templateName << " is less than min difficulty.";

			// Verify size is at least 1
			float size = spawn->getSize();
			EXPECT_TRUE( size >= 1 ) << "Size for lairTemplate " << lairName << " in spawn group " << templateName << " is less than 1.";
		}
	}
}

TEST_F(LuaMobileTest, LuaLootGroupsTest) {

	LootGroupMap* lootGroupMap = LootGroupMap::instance();
	ASSERT_EQ(lootGroupMap->initialize(), 0);

	//Make sure that no loot items have the same name as a loot group
	HashTableIterator<String, Reference<LootItemTemplate*> > itemIter = lootGroupMap->itemTemplates.iterator();
	while (itemIter.hasNext()) {

		LootItemTemplate* lootItemTemplate = itemIter.next();
		String itemTemplateName( lootItemTemplate->getTemplateName().toCharArray() );

		EXPECT_FALSE( lootGroupMap->lootGroupExists(itemTemplateName) ) << "Loot item " << std::string(itemTemplateName.toCharArray()) << " has the same name as a loot group.";
	}

	HashTableIterator<String, Reference<LootGroupTemplate*> > iter = lootGroupMap->groupTemplates.iterator();
	while (iter.hasNext()) {

		LootGroupTemplate* lootGroupTemplate = iter.next();
		String groupTemplateName( lootGroupTemplate->getTemplateName().toCharArray() );

		// Check non-empty loot groups to make sure their chances total correctly
		if( lootGroupTemplate->getLootGroupEntryForRoll(-1).length() > 0  ){
			EXPECT_GT( lootGroupTemplate->getLootGroupEntryForRoll(10000000).length(), 0 ) << "Item total chance is less than 10000000: " << std::string(groupTemplateName.toCharArray());
			EXPECT_EQ( lootGroupTemplate->getLootGroupEntryForRoll(10000001).length(), 0 ) << "Item total chance is greater than 10000000: " << std::string(groupTemplateName.toCharArray());
		}

		// Check that all loot group entries are valid
		for( int i = 0; i < lootGroupTemplate->size(); i++ ){

			Vector<String> parentGroups;
			parentGroups.add(groupTemplateName);

			String entryName = lootGroupTemplate->getLootGroupEntryAt(i);

			checkLootGroupEntryRecursive(lootGroupMap, entryName, &parentGroups);
		}

	}

}
