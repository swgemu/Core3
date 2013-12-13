local OldManEncounter = require("managers.jedi.village.old_man_encounter")
local QuestManagerMocks = require("managers.quest.mocks.quest_manager_mocks")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")
local VillageJediManagerCommonMocks = require("managers.jedi.village.mocks.village_jedi_manager_common_mocks")

local OLD_MAN_GREETING_STRING = "@quest/force_sensitive/intro:oldman_greeting"
local SCHEDULED_OLD_MAN_DESPAWN_TIME = 10 * 1000
local OLD_MAN_FORCE_CRYSTAL_STRING = "object/tangible/loot/quest/force_sensitive/force_crystal.iff"
local OLD_MAN_INVENTORY_STRING = "inventory"

describe("OldManEncounter", function()
	local pOldMan = { "oldManPointer" }
	local pCreatureObject = { "creatureObjectPointer" }
	local spawnedOldManList = {
		pOldMan
	}
	local playerFirstName = "firstName"
	local greetingStringId
	local pGreetingStringId = { "greetingStringIdPointer" }
	local creatureObjectPlayer
	local creatureObjectOldMan
	local pPlayerInventory = { "playerInventoryPointer" }
	local oldManId = 12345
	local otherOldManId = 91234
	local pConversingOldMan = { "conversingOldManPointer" }
	local pOtherOldMan = { "otherOldManPointer" }
	local creatureObjectConversingOldMan
	local creatureObjectOtherOldMan

	setup(function()
		DirectorManagerMocks.mocks.setup()
		QuestManagerMocks.mocks.setup()
		SpawnMobilesMocks.mocks.setup()
		VillageJediManagerCommonMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
		QuestManagerMocks.mocks.teardown()
		SpawnMobilesMocks.mocks.teardown()
		VillageJediManagerCommonMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()
		QuestManagerMocks.mocks.before_each()
		SpawnMobilesMocks.mocks.before_each()
		VillageJediManagerCommonMocks.mocks.before_each()

		creatureObjectPlayer = {}
		creatureObjectPlayer.getFirstName = spy.new(function() return playerFirstName end)
		--creatureObjectPlayer.getObjectID = spy.new(function() return playerId end)
		--creatureObjectPlayer.getPlayerObject = spy.new(function() return pPlayerObject end)
		--creatureObjectPlayer.getScreenPlayState = spy.new(function() return 0 end)
		--creatureObjectPlayer.setScreenPlayState = spy.new(function() end)
		--creatureObjectPlayer.removeScreenPlayState = spy.new(function() end)
		creatureObjectPlayer.getSlottedObject = spy.new(function() return pPlayerInventory end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObjectPlayer

		creatureObjectConversingOldMan = {}
		creatureObjectConversingOldMan.getObjectID = spy.new(function() return oldManId end)
		DirectorManagerMocks.sceneObjects[pConversingOldMan] = creatureObjectConversingOldMan

		creatureObjectOtherOldMan = {}
		creatureObjectOtherOldMan.getObjectID = spy.new(function() return otherOldManId end)
		DirectorManagerMocks.sceneObjects[pOtherOldMan] = creatureObjectOtherOldMan

		greetingStringId = {}
		greetingStringId._getObject = spy.new(function() return pGreetingStringId end)
		greetingStringId.setTT = spy.new(function(object, string) assert.same(string, playerFirstName) end)
		DirectorManagerMocks.stringIds[OLD_MAN_GREETING_STRING] = greetingStringId
	end)

	describe("Properties", function()
		it("Should have taskName set to OldManEncounter.", function()
			assert.same("OldManEncounter", OldManEncounter.taskName)
		end)

		describe("spawnObjectList", function()
			it("Should have one mobile defined.", function()
				assert.same(1, table.getn(OldManEncounter.spawnObjectList))
			end)
			it("Should have template equal to old_man.", function()
				assert.same("old_man", OldManEncounter.spawnObjectList[1]["template"])
			end)
			it("Should have minimumDistance equal to 32.", function()
				assert.same(32, OldManEncounter.spawnObjectList[1]["minimumDistance"])
			end)
			it("Should have maximumDistance equal to 64.", function()
				assert.same(64, OldManEncounter.spawnObjectList[1]["maximumDistance"])
			end)
			it("Should have referencePoint equal to 0.", function()
				assert.same(0, OldManEncounter.spawnObjectList[1]["referencePoint"])
			end)
			it("Should have followPlayer set to true.", function()
				assert.same(true, OldManEncounter.spawnObjectList[1]["followPlayer"])
			end)
		end)
	end)

	describe("Public functions", function()
		describe("scheduleDespawnOfOldMan", function()
			describe("When called with a player", function()
				it("Should create an event to despawn the old man.", function()
					OldManEncounter:scheduleDespawnOfOldMan(pCreatureObject)

					assert.spy(createEvent).was.called_with(SCHEDULED_OLD_MAN_DESPAWN_TIME, "OldManEncounter", "handleScheduledDespawn", pCreatureObject)
				end)
			end)
		end)

		describe("giveForceCrystalToPlayer", function()
			describe("When called with a player as argument", function()
				it("Should get the inventory of the player.", function()
					OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

					assert.spy(creatureObjectPlayer.getSlottedObject).was.called_with(creatureObjectPlayer, OLD_MAN_INVENTORY_STRING)
				end)

				describe("and the inventory pointer return is not nil", function()
					it("Should give the player a force crystal.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(giveItem).was.called_with(pPlayerInventory, OLD_MAN_FORCE_CRYSTAL_STRING, -1)
					end)

					it("Should update the village jedi progression state on the player.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(VillageJediManagerCommonMocks.setJediProgressionScreenPlayState).was.called_with(pCreatureObject, VILLAGE_JEDI_PROGRESSION_HAS_CRYSTAL)
					end)

					it("Should complete the old man initial and the old man force crystal quests.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(QuestManagerMocks.completeQuest).was.called(2)
					end)
				end)

				describe("and the inventory pointer return is not nil", function()
					before_each(function()
						creatureObjectPlayer.getSlottedObject = spy.new(function() return nil end)
					end)

					it("Should not give the player a force crystal.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(giveItem).was.not_called()
					end)

					it("Should not update the village jedi progression state on the player.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(VillageJediManagerCommonMocks.setJediProgressionScreenPlayState).was.not_called()
					end)

					it("Should not complete the old man initial and the old man force crystal quests.", function()
						OldManEncounter:giveForceCrystalToPlayer(pCreatureObject)

						assert.spy(QuestManagerMocks.completeQuest).was.not_called()
					end)
				end)
			end)
		end)

		describe("doesOldManBelongToThePlayer", function()
			describe("When called with a player and his old man", function()
				it("Should get a list with pointer to the spawned old man for the player.", function()
					OldManEncounter:doesOldManBelongToThePlayer(pCreatureObject, pConversingOldMan)

					assert.spy(SpawnMobilesMocks.getSpawnedMobiles).was.called_with(pCreatureObject, OldManEncounter.taskName)
				end)
			end)

			describe("and nil is returned from the getSpawnedMobiles function", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return nil end)
				end)

				it("Should return false.", function()
					assert.is_false(OldManEncounter:doesOldManBelongToThePlayer(pCreatureObject, pConversingOldMan))
				end)
			end)

			describe("and {} is returned from the getSpawnedMobiles function", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return {} end)
				end)

				it("Should return false.", function()
					assert.is_false(OldManEncounter:doesOldManBelongToThePlayer(pCreatureObject, pConversingOldMan))
				end)
			end)

			describe("and correct old man is returned from the getSpawnedMobiles function", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return { pConversingOldMan } end)
				end)

				it("Should return true.", function()
					assert.is_true(OldManEncounter:doesOldManBelongToThePlayer(pCreatureObject, pConversingOldMan))
				end)
			end)

			describe("and an other old man is returned from the getSpawnedMobiles function", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return { pOtherOldMan } end)
				end)

				it("Should return false.", function()
					assert.is_false(OldManEncounter:doesOldManBelongToThePlayer(pCreatureObject, pConversingOldMan))
				end)
			end)
		end)
	end)

	describe("Events", function()
		describe("handleScheduledDespawn", function()
			describe("When called with a pointer to a player", function()
				local realDespawnEncounter

				setup(function()
					realDespawnEncounter = OldManEncounter.despawnEncounter
				end)

				setup(function()
					OldManEncounter.despawnEncounter = realDespawnEncounter
				end)

				setup(function()
					OldManEncounter.despawnEncounter = spy.new(function() end)
				end)

				it("Should despawn the old man.", function()
					OldManEncounter:handleScheduledDespawn(pCreatureObject)

					assert.spy(OldManEncounter.despawnEncounter).was.called_with(OldManEncounter, pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("onEncounterClosingIn", function()
			describe("When called with a player and a list with a pointer to the old man", function()
				local realSendGreetingString

				setup(function()
					realSendGreetingString = OldManEncounter.sendGreetingString
				end)

				teardown(function()
					OldManEncounter.sendGreetingString = realSendGreetingString
				end)

				before_each(function()
					OldManEncounter.sendGreetingString = spy.new(function() end)
				end)


				it("Should send the greeting string.", function()
					OldManEncounter:onEncounterClosingIn(pCreatureObject, spawnedOldManList)

					assert.spy(OldManEncounter.sendGreetingString).was.called_with(OldManEncounter, pOldMan, pCreatureObject)
				end)

				it("Should activate the OLD_MAN_INITIAL quest", function()
					OldManEncounter:onEncounterClosingIn(pCreatureObject, spawnedOldManList)

					assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.OLD_MAN_INITIAL)
				end)
			end)
		end)

		describe("sendGreetingString", function()
			describe("When called with a pointer to an old man and a pointer to a player", function()
				local realGetPlayerFirstName

				setup(function()
					realGetPlayerFirstName = OldManEncounter.getPlayerFirstName
				end)

				teardown(function()
					OldManEncounter.getPlayerFirstName = realGetPlayerFirstName
				end)

				before_each(function()
					OldManEncounter.getPlayerFirstName = spy.new(function() return playerFirstName end)
				end)

				it("Should create a string id for the oldman_greeting string.", function()
					OldManEncounter:sendGreetingString(pOldMan, pCreatureObject)

					assert.spy(LuaStringIdChatParameter).was.called_with(OLD_MAN_GREETING_STRING)
				end)

				it("Should get the name of the player.", function()
					OldManEncounter:sendGreetingString(pOldMan, pCreatureObject)

					assert.spy(OldManEncounter.getPlayerFirstName).was.called_with(OldManEncounter, pCreatureObject)
				end)

				it("Should set the %TT of the string to the name of the player.", function()
					OldManEncounter:sendGreetingString(pOldMan, pCreatureObject)

					assert.spy(greetingStringId.setTT).was.called(1)
				end)

				it("Should send the string id to spatial chat.", function()
					OldManEncounter:sendGreetingString(pOldMan, pCreatureObject)

					assert.spy(spatialChat).was.called_with(pOldMan, pGreetingStringId)
				end)
			end)
		end)

		describe("getPlayerFirstName", function()
			describe("When called with a player", function()
				it("Should return the first name of the player.", function()
					assert.same(playerFirstName, OldManEncounter:getPlayerFirstName(pCreatureObject))

					assert.spy(creatureObjectPlayer.getFirstName).was.called(1)
				end)
			end)
			describe("When called with nil", function()
				it("Should return an empty string.", function()
					assert.same(OldManEncounter:getPlayerFirstName(nil), "")
				end)
			end)
		end)
	end)
end)
