local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")

LOOTCREATURE = 53

describe("Sith Shadow Encounter", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pFirstSithShadow = { "firstSithShadowPointer" }
	local pSecondSithShadow = { "secondSithShadowPointer" }
	local spawnedSithShadowList = {
		pFirstSithShadow,
		pSecondSithShadow
	}
	local creatureObject
	local firstSithShadowObject
	local secondSithShadowObject
	local pInventory = { "inventoryPointer" }
	local firstSithShadowId = 12345
	local secondSithShadowId = 23456

	setup(function()
		DirectorManagerMocks.mocks.setup()
		SpawnMobilesMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
		SpawnMobilesMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
		SpawnMobilesMocks.mocks.before_each()

		creatureObject = {}
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		firstSithShadowObject = {}
		firstSithShadowObject.getObjectID = spy.new(function() return firstSithShadowId end)
		firstSithShadowObject.getSlottedObject = spy.new(function() return pInventory end)
		DirectorManagerMocks.creatureObjects[pFirstSithShadow] = firstSithShadowObject

		secondSithShadowObject = {}
		secondSithShadowObject.getObjectID = spy.new(function() return secondSithShadowId end)
		DirectorManagerMocks.creatureObjects[pSecondSithShadow] = secondSithShadowObject
	end)

	describe("onEncounterSpawned", function()
		describe("When called with a pointer to a player and a list of spawned sith shadows", function()
			it("Should register an observer for LOOTCREATURE on the first sith shadow in the sith shadow list.", function()
				SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedSithShadowList)

				assert.spy(createObserver).was.called_with(LOOTCREATURE, SithShadowEncounter.taskName, "onLoot", pFirstSithShadow)
			end)
		end)
	end)

	describe("onLoot", function()
		describe("When called with a pointer to a creature and a pointer to the looter", function()
			it("Should get the list of spawned sith shadows for the looter.", function()
				SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

				assert.spy(SpawnMobilesMocks.getSpawnedMobiles).was.called_with(pCreatureObject, SithShadowEncounter.taskName)
			end)

			describe("and the player has a list of spawned sith shadows", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return spawnedSithShadowList end)
				end)

				it("Should get the id of the first sith shadow in the list", function()
					SithShadowEncounter:onLoot(pSecondSithShadow, pCreatureObject, 0)

					assert.spy(firstSithShadowObject.getObjectID).was.called_with(firstSithShadowObject)
				end)

				it("Should get the id of the looted creature", function()
					SithShadowEncounter:onLoot(pSecondSithShadow, pCreatureObject, 0)

					assert.spy(secondSithShadowObject.getObjectID).was.called_with(secondSithShadowObject)
				end)

				describe("and both ids are identical", function()
					it("Should create loot in the inventory of the sith shadow.", function()
						SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

						assert.spy(createLoot).was.called_with(pInventory, "sith_shadow_encounter_datapad", 0, true)
					end)
				end)

				describe("and both ids are not identical", function()
					it("Should not create loot in the inventory of the looted sith shadow.", function()
						SithShadowEncounter:onLoot(pSecondSithShadow, pCreatureObject, 0)

						assert.spy(createLoot).was.not_called()
					end)
				end)
			end)

			describe("and the player has no spawned sith shadows", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return nil end)
				end)

				it("Should not create loot in the inventory of the looted sith shadow.", function()
					SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

					assert.spy(createLoot).was.not_called()
				end)
			end)
		end)
	end)
end)
