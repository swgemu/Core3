package.path = package.path .. ";scripts/managers/jedi/village/?.lua;scripts/screenplays/mocks/?.lua"
require("old_man")
local DirectorManagerMocks = require("director_manager_mocks")

describe("Old Man", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pOldMan = { "oldManPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local playerId = 12345678
	local oldManId = 98765432
	local creatureObjectPlayer
	local creatureObjectOldMan
	local playerObject
	local sceneObject
	local playerObject
	local cityRegion

	setup(function()
		DirectorManagerMocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.before_each()

		getCityRegionAt = spy.new(function() return pCityRegion end)
		getSpawnPoint = spy.new(function() return { 1, 2, 3 } end)
		readData = spy.new(function() return oldManId end)
		spawnMobile = spy.new(function() return pOldMan end)

		creatureObjectPlayer = { getObjectID = nil, getPlayerObject = nil }
		creatureObjectOldMan = { getObjectID = nil }
		creatureObjectPlayer.getObjectID = spy.new(function() return playerId end)
		creatureObjectPlayer.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObjectOldMan.getObjectID = spy.new(function() return oldManId end)

		sceneObject = { getParentID = nil, getZoneName = nil, getWorldPositionX = nil, getWorldPositionY = nil }
		sceneObject.getParentID = spy.new(function() return 0 end)
		sceneObject.getZoneName = spy.new(function() return "testzone" end)
		sceneObject.getWorldPositionX = spy.new(function() return 33 end)
		sceneObject.getWorldPositionY = spy.new(function() return 22 end)

		playerObject = { isOnline = nil }
		playerObject.isOnline = spy.new(function() return true end)

		cityRegion = { isClientRegion = nil }
		cityRegion.isClientRegion = spy.new(function() return false end)

		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObjectPlayer
		DirectorManagerMocks.creatureObjects[pOldMan] = creatureObjectOldMan

		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		DirectorManagerMocks.sceneObjects[pCreatureObject] = sceneObject

		DirectorManagerMocks.cityRegions[pCityRegion] = cityRegion
	end)

	describe("Interface methods", function()
		describe("createSpawnOldManEvent", function()
			describe("When called with a player as argument", function()
				it("Should create an event for spawning the old man", function()
					OldMan.createSpawnOldManEvent(pCreatureObject)

					assert.spy(createEvent).was.called(1)
				end)
			end)
		end)

		describe("oldManBelongsToThePlayer", function()
			describe("When called with a player and his old man", function()
				it("Should return true", function()
					assert.is_true(OldMan.oldManBelongsToThePlayer(pCreatureObject, pOldMan))

					assert.spy(LuaCreatureObject).was.called(2)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
					assert.spy(creatureObjectOldMan.getObjectID).was.called(1)
					assert.spy(readData).was.called_with(playerId .. OLD_MAN_ID_STRING)
				end)
			end)

			describe("When called with a player and an old man of another player", function()
				it("Should return false", function()
					readData = spy.new(function() return 0 end)

					assert.is_false(OldMan.oldManBelongsToThePlayer(pCreatureObject, pOldMan))

					assert.spy(LuaCreatureObject).was.called(2)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
					assert.spy(creatureObjectOldMan.getObjectID).was.called(1)
					assert.spy(readData).was.called_with(playerId .. OLD_MAN_ID_STRING)
				end)
			end)
		end)
	end)

	describe("Private methods", function()
		describe("handleSpawnOldManEvent", function()
			describe("When event to spawn old man is triggered", function()
				local realCanOldManBeSpawned
				local realSpawnOldMan
				local realCreateSpawnOldManEvent
				local realSaveOldManIdOnPlayer

				setup(function()
					realCanOldManBeSpawned = OldMan.canOldManBeSpawned
					realSpawnOldMan = OldMan.spawnOldMan
					realCreateSpawnOldManEvent = OldMan.createSpawnOldManEvent
					realSaveOldManIdOnPlayer = OldMan.saveOldManIdOnPlayer
				end)

				teardown(function()
					OldMan.canOldManBeSpawned = realCanOldManBeSpawned
					OldMan.spawnOldMan = realSpawnOldMan
					OldMan.createSpawnOldManEvent = realCreateSpawnOldManEvent
					OldMan.saveOldManIdOnPlayer = realSaveOldManIdOnPlayer
				end)

				before_each(function()
					OldMan.canOldManBeSpawned = spy.new(function() return true end)
					OldMan.spawnOldMan = spy.new(function() return pOldMan end)
					OldMan.createSpawnOldManEvent = spy.new(function() end)
					OldMan.saveOldManIdOnPlayer = spy.new(function() end)
				end)

				it("Should spawn the old man if the player is in a place where the old man can be spawned.", function()
					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.spawnOldMan).was.called_with(pCreatureObject)
					assert.spy(OldMan.createSpawnOldManEvent).was.not_called()
				end)

				it("Should save the object id of the spawned old man on the player.", function()
					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.saveOldManIdOnPlayer).was.called_with(pCreatureObject, pOldMan)
				end)

				it("Should reschedule the event if the player is not in a place where the old man can be spawned.", function()
					OldMan.canOldManBeSpawned = spy.new(function() return false end)

					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.spawnOldMan).was.not_called()
					assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)
				end)

				it("Should reschedule the event if the spawning of the old man fails.", function()
					OldMan.spawnOldMan = spy.new(function() return nil end)

					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.spawnOldMan).was.called_with(pCreatureObject)
					assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)
				end)
			end)
		end)

		describe("canOldManBeSpawned", function()
			describe("When called with a creature object as argument", function()
				local realIsPlayerOnline
				local realIsPlayerInNpcCity
				local realIsPlayerInABuilding

				setup(function()
					realIsPlayerOnline = OldMan.isPlayerOnline
					realIsPlayerInNpcCity = OldMan.isPlayerInNpcCity
					realIsPlayerInABuilding = OldMan.isPlayerInABuilding
				end)

				teardown(function()
					OldMan.isPlayerOnline = realIsPlayerOnline
					OldMan.isPlayerInNpcCity = realIsPlayerInNpcCity
					OldMan.isPlayerInABuilding = realIsPlayerInABuilding
				end)

				before_each(function()
					OldMan.isPlayerOnline = spy.new(function() return true end)
					OldMan.isPlayerInNpcCity = spy.new(function() return false end)
					OldMan.isPlayerInABuilding = spy.new(function() return false end)
				end)

				describe("and the player is outside, not in an npc city and online.", function()
					it("Should return true.", function()
						assert.is_true(OldMan.canOldManBeSpawned(pCreatureObject))
					end)
				end)

				describe("and the player is offline", function()
					it("Should return false.", function()
						OldMan.isPlayerOnline = spy.new(function() return false end)

						assert.is_false(OldMan.canOldManBeSpawned(pCreatureObject))
					end)
				end)

				describe("and the player is in a NPC city", function()
					it("Should return false.", function()
						OldMan.isPlayerInNpcCity = spy.new(function() return true end)

						assert.is_false(OldMan.canOldManBeSpawned(pCreatureObject))
					end)
				end)

				describe("and the player is inside a building", function()
					it("Should return false.", function()
						OldMan.isPlayerInABuilding = spy.new(function() return true end)

						assert.is_false(OldMan.canOldManBeSpawned(pCreatureObject))
					end)
				end)
			end)
		end)

		describe("isPlayerOnline", function()
			describe("When called with a creature object pointer", function()
				it("Should return true if the player is online.", function()
					playerObject.isOnline = spy.new(function() return true end)

					assert.is_true(OldMan.isPlayerOnline(pCreatureObject))

					assert.spy(LuaCreatureObject).was.called_with(pCreatureObject)
					assert.spy(LuaPlayerObject).was.called_with(pPlayerObject)
					assert.spy(playerObject.isOnline).was.called(1)
				end)

				it("Should return false if the player is offline.", function()
					playerObject.isOnline = spy.new(function() return false end)

					assert.is_false(OldMan.isPlayerOnline(pCreatureObject))

					assert.spy(LuaCreatureObject).was.called_with(pCreatureObject)
					assert.spy(LuaPlayerObject).was.called_with(pPlayerObject)
					assert.spy(playerObject.isOnline).was.called(1)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false.", function()
					assert.is_false(OldMan.isPlayerOnline(nil))
				end)
			end)
		end)

		describe("isPlayerInABuilding", function()
			describe("When called with a creature object pointer", function()
				it("Should return true if the parent id of the player is not equal to 0", function()
					sceneObject.getParentID = spy.new(function() return 1 end)

					assert.is_true(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(LuaSceneObject).was.called(1)
					assert.spy(sceneObject.getParentID).was.called(1)
				end)

				it("Should return false if the parent id of the player is equal to 0", function()
					sceneObject.getParentID = spy.new(function() return 0 end)

					assert.is_false(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(LuaSceneObject).was.called(1)
					assert.spy(sceneObject.getParentID).was.called(1)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false.", function()
					assert.is_false(OldMan.isPlayerInABuilding(nil))
				end)
			end)
		end)

		describe("isPlayerInNpcCity", function()
			describe("When called with a nil pointer", function()
				it("Should return false", function()
					assert.is_false(OldMan.isPlayerInNpcCity(nil))
				end)
			end)

			describe("When called with a creature object pointer", function()
				after_each(function()
					assert.spy(sceneObject.getZoneName).was.called(1)
					assert.spy(sceneObject.getWorldPositionX).was.called(1)
					assert.spy(sceneObject.getWorldPositionY).was.called(1)
					assert.spy(LuaSceneObject).was.called(1)
					assert.spy(getCityRegionAt).was.called_with("testzone", 33, 22)
				end)			

				describe("and player is in no region", function()
					it("Should return false.", function()
						getCityRegionAt = spy.new(function() return nil end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))
					end)
				end)

				describe("and the player is in city region", function()
					it("Should return true if the city region belongs to a NPC city.", function()
						cityRegion.isClientRegion = spy.new(function() return false end)

						assert.is_true(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(LuaCityRegion).was.called(1)
					end)

					it("Should return false if the city region belongs to a player city.", function()
						cityRegion.isClientRegion = spy.new(function() return true end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(LuaCityRegion).was.called(1)
					end)
				end)
			end)
		end)

		describe("spawnOldMan", function()
			after_each(function()
				assert.spy(sceneObject.getWorldPositionX).was.called(1)
				assert.spy(sceneObject.getWorldPositionY).was.called(1)
				assert.spy(LuaSceneObject).was.called(1)
			end)

			describe("When called with a creature object pointer", function()
				it("Should get a spawn point for the old man.", function()
					OldMan.spawnOldMan(pCreatureObject)

					assert.spy(getSpawnPoint).was.called_with(pCreatureObject, 33, 22, OLD_MAN_MIN_SPAWN_DISTANCE, OLD_MAN_MAX_SPAWN_DISTANCE)
				end)

				describe("and a spawn point is returned", function()
					it("Should spawn the old man.", function()
						OldMan.spawnOldMan(pCreatureObject)

						assert.spy(sceneObject.getZoneName).was.called(1)
						assert.spy(sceneObject.getParentID).was.called(1)
						assert.spy(spawnMobile).was.called_with("testzone", OLD_MAN_TEMPLATE, OLD_MAN_RESPAWN_TIME, 1, 2, 3, OLD_MAN_HEADING, 0)
					end)

					it("Should return a pointer to the spawned old man.", function()
						assert.same(OldMan.spawnOldMan(pCreatureObject), pOldMan)
					end)
				end)

				describe("and no spawn point is returned", function()
					before_each(function()
						getSpawnPoint = spy.new(function() return nil end)
					end)

					it("Should not spawn the old man.", function()
						OldMan.spawnOldMan(pCreatureObject)

						assert.spy(sceneObject.getZoneName).was.not_called()
						assert.spy(sceneObject.getParentID).was.not_called()
						assert.spy(spawnMobile).was.not_called()
					end)

					it("Should return nil.", function()
						assert.is_nil(OldMan.spawnOldMan(pCreatureObject))
					end)
				end)
			end)
		end)

		describe("saveOldManIdOnPlayer", function()
			describe("When called with player and old man", function()
				it("Should store the object id of the old man on the player.", function()
					OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)

					assert.spy(writeData).was.called_with(playerId .. OLD_MAN_ID_STRING, oldManId)
					assert.spy(LuaCreatureObject).was.called(2)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
					assert.spy(creatureObjectOldMan.getObjectID).was.called(1)
				end)
			end)
		end)
	end)
end)
