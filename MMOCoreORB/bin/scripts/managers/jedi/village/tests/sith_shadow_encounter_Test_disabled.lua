local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local QuestManagerMocks = require("managers.quest.mocks.quest_manager_mocks")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")
local OldManEncounterMocks = require("managers.jedi.village.mocks.old_man_encounter_mocks")
local SithShadowIntroTheaterMocks = require("managers.jedi.village.mocks.sith_shadow_intro_theater_mocks")

LOOTCREATURE = 53
SITH_SHADOW_THREATEN_STRING = "@quest/force_sensitive/intro:military_threaten"
SITH_SHADOW_MILITARY_TAKE_CRYSTAL = "@quest/force_sensitive/intro:military_take_crystal"
local READ_DISK_1_STRING = "@quest/force_sensitive/intro:read_disk1"
local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"

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
	local pThreatenStringId = { "threatenPointer" }
	local threatenStringId
	local playerFirstName = "firstName"
	local pDatapad = { "datapadPointer" }
	local datapad

	setup(function()
		DirectorManagerMocks.mocks.setup()
		SpawnMobilesMocks.mocks.setup()
		OldManEncounterMocks.mocks.setup()
		QuestManagerMocks.mocks.setup()
		SithShadowIntroTheaterMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
		SpawnMobilesMocks.mocks.teardown()
		OldManEncounterMocks.mocks.teardown()
		QuestManagerMocks.mocks.teardown()
		SithShadowIntroTheaterMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
		SpawnMobilesMocks.mocks.before_each()
		OldManEncounterMocks.mocks.before_each()
		QuestManagerMocks.mocks.before_each()
		SithShadowIntroTheaterMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.getFirstName = spy.new(function() return playerFirstName end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		firstSithShadowObject = {}
		firstSithShadowObject.getObjectID = spy.new(function() return firstSithShadowId end)
		firstSithShadowObject.getSlottedObject = spy.new(function() return pInventory end)
		DirectorManagerMocks.creatureObjects[pFirstSithShadow] = firstSithShadowObject

		secondSithShadowObject = {}
		secondSithShadowObject.getObjectID = spy.new(function() return secondSithShadowId end)
		DirectorManagerMocks.creatureObjects[pSecondSithShadow] = secondSithShadowObject

		threatenStringId = {}
		threatenStringId._getObject = spy.new(function() return pThreatenStringId end)
		threatenStringId.setTT = spy.new(function() end)
		DirectorManagerMocks.stringIds[SITH_SHADOW_THREATEN_STRING] = threatenStringId

		datapad = {}
		datapad.destroyObjectFromWorld = spy.new(function() end)
		datapad.destroyObjectFromDatabase = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pDatapad] = datapad
	end)

	describe("onEncounterSpawned", function()
		describe("When called with a pointer to a player and a list of spawned sith shadows", function()
			it("Should register an observer for LOOTCREATURE on the first sith shadow in the sith shadow list.", function()
				SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedSithShadowList)

				assert.spy(createObserver).was.called_with(LOOTCREATURE, SithShadowEncounter.taskName, "onLoot", pFirstSithShadow)
			end)

			it("Should register an observer for OBJECTDESTRUCTION on the player.", function()
				SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedSithShadowList)

				assert.spy(createObserver).was.called_with(OBJECTDESTRUCTION, SithShadowEncounter.taskName, "onPlayerKilled", pCreatureObject)
			end)

			it("Should activate the sith shadow ambush quest.", function()
				SithShadowEncounter:onEncounterSpawned(pCreatureObject, spawnedSithShadowList)

				assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.TwO_MILITARY)
			end)
		end)
	end)

	describe("onLoot", function()
		describe("When called with a pointer to a creature and a pointer to the looter", function()
			it("Should check if the player has the encounter quest active.", function()
				SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

				assert.spy(QuestManagerMocks.hasActiveQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.TwO_MILITARY)
			end)

			describe("and the player has the quest active", function()
				before_each(function()
					QuestManagerMocks.hasActiveQuest = spy.new(function() return true end)
				end)

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

						it("Should return 1 to remove the observer.", function()
							assert.same(1, SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0))
						end)
					end)

					describe("and both ids are not identical", function()
						it("Should not create loot in the inventory of the looted sith shadow.", function()
							SithShadowEncounter:onLoot(pSecondSithShadow, pCreatureObject, 0)

							assert.spy(createLoot).was.not_called()
						end)

						it("Should return 0 to keep the observer.", function()
							assert.same(0, SithShadowEncounter:onLoot(pSecondSithShadow, pCreatureObject, 0))
						end)
					end)

					it("Should complete the sith shadow ambush quests.", function()
						SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

						assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.TwO_MILITARY)
						assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_1)
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

					it("Should return 0 to keep the observer.", function()
						assert.same(0, SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0))
					end)
				end)
			end)

			describe("and the player does not have the quest active", function()
				it("Should not create loot in the inventory of the looted sith shadow.", function()
					SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0)

					assert.spy(createLoot).was.not_called()
				end)

				it("Should return 0 to keep the observer.", function()
					assert.same(0, SithShadowEncounter:onLoot(pFirstSithShadow, pCreatureObject, 0))
				end)
			end)
		end)
	end)

	describe("onPlayerKilled", function()
		it("Should check if the killer is from the sith shadow spawn of the player.", function()
			SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

			assert.spy(SpawnMobilesMocks.isFromSpawn).was.called_with(pCreatureObject, SithShadowEncounter.taskName, pFirstSithShadow)
		end)

		describe("and the killer is one of the sith shadows of the player", function()
			before_each(function()
				SpawnMobilesMocks.isFromSpawn = spy.new(function() return true end)
			end)

			it("Should remove the crystal from the player.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(OldManEncounterMocks.removeForceCrystalFromPlayer).was.called_with(OldManEncounterMocks, pCreatureObject)
			end)

			it("Should restart the old man encounter.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(OldManEncounterMocks.start).was.called_with(OldManEncounterMocks, pCreatureObject)
			end)

			it("Should reset the sith shadow ambush quests.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.TwO_MILITARY)
				assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_1)
				assert.spy(QuestManagerMocks.resetQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_1)
			end)

			it("Should send spatial chat about returning the crystal.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(spatialChat).was.called_with(pFirstSithShadow, SITH_SHADOW_MILITARY_TAKE_CRYSTAL)
			end)

			it("Should return 1 to remove the observer.", function()
				assert.same(1, SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0))
			end)
		end)

		describe("and the killer is not one of the sith shadows of the player", function()
			it("Should not remove the crystal from the player.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(OldManEncounterMocks.removeForceCrystalFromPlayer).was.not_called()
			end)

			it("Should not restart the old man encounter.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(OldManEncounterMocks.start).was.not_called()
			end)

			it("Should not reset the sith shadow ambush quests.", function()
				SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0)

				assert.spy(QuestManagerMocks.resetQuest).was.not_called()
			end)

			it("Should return 0 to keep the observer.", function()
				assert.same(0, SithShadowEncounter:onPlayerKilled(pCreatureObject, pFirstSithShadow, 0))
			end)
		end)
	end)

	describe("isEncounterFinished", function()
		describe("When called with a player object", function()
			it("Should check if the player has the force crystal or not.", function()
				SithShadowEncounter:isEncounterFinished(pCreatureObject)

				assert.spy(QuestManagerMocks.hasCompletedQuest).was.called(1)
			end)

			describe("and the player has lost the force crystal", function()
				before_each(function()
					QuestManagerMocks.hasCompletedQuest = spy.new(function() return false end)
				end)

				it("Should return true", function()
					assert.is_true(SithShadowEncounter:isEncounterFinished(pCreatureObject))
				end)
			end)

			describe("and the player has not lost the force crystal", function()
				before_each(function()
					QuestManagerMocks.hasCompletedQuest = spy.new(function() return true end)
				end)

				it("Should return false", function()
					assert.is_false(SithShadowEncounter:isEncounterFinished(pCreatureObject))
				end)
			end)
		end)
	end)

	describe("onEncounterClosingIn", function()
		describe("When called with a player and a list of spawned sith shadows", function()
			it("Should get the first name of the player.", function()
				SithShadowEncounter:onEncounterClosingIn(pCreatureObject, spawnedSithShadowList)

				assert.spy(creatureObject.getFirstName).was.called_with(creatureObject)
			end)

			it("Should put the player name in the threaten string.", function()
				SithShadowEncounter:onEncounterClosingIn(pCreatureObject, spawnedSithShadowList)

				assert.spy(threatenStringId.setTT).was.called_with(threatenStringId, playerFirstName)
			end)

			it("Should send the threaten string to the player.", function()
				SithShadowEncounter:onEncounterClosingIn(pCreatureObject, spawnedSithShadowList)

				assert.spy(spatialChat).was.called_with(pFirstSithShadow, pThreatenStringId)
			end)

			it("Should activate the defeat the sith shadow ambush quest.", function()
				SithShadowEncounter:onEncounterClosingIn(pCreatureObject, spawnedSithShadowList)

				assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_1)
			end)
		end)
	end)

	describe("useWaypointDatapad", function()
		describe("When called with a scene object and a player object", function()
			it("Should check if the player object has looted a datapad.", function()
				SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

				assert.spy(QuestManagerMocks.hasCompletedQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.GOT_DATAPAD_1)
			end)

			describe("and the player has looted a datapad", function()
				before_each(function()
					QuestManagerMocks.hasCompletedQuest = spy.new(function() return true end)
				end)

				it("Should activate the sith shadow intro theater for the player.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(SithShadowIntroTheaterMocks.start).was.called_with(SithShadowIntroTheaterMocks, pCreatureObject)
				end)

				it("Should send a system message to the player with information about the data on the disk.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, READ_DISK_1_STRING)
				end)

				it("Should destroy the datapad.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(datapad.destroyObjectFromWorld).was.called_with(datapad)
					assert.spy(datapad.destroyObjectFromDatabase).was.called_with(datapad)
				end)

				it("Should complete the loot datapad 1 quests.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.LOOT_DATAPAD_1)
				end)
			end)

			describe("and the player has not looted a datapad", function()
				it("Should not activate the sith shadow intro theater for the player.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(SithShadowIntroTheaterMocks.start).was.not_called()
				end)

				it("Should send an error string to the player.", function()
					SithShadowEncounter:useWaypointDatapad(pDatapad, pCreatureObject)

					assert.spy(creatureObject.sendSystemMessage).was.called_with(creatureObject, READ_DISK_ERROR_STRING)
				end)
			end)
		end)
	end)
end)
