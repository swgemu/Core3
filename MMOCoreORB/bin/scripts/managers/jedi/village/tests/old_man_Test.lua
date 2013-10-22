package.path = package.path .. ";scripts/managers/jedi/village/?.lua"
require("old_man")

describe("Old Man", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pOldMan = { "oldManPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local realCreateEvent
	local playerId = 12345678
	local oldManId = 98765432
	local realReadData
	local realWithCreatureObject
	local creatureObjectPlayer
	local creatureObjectOldMan
	local realWithCreaturePlayerObject
	local playerObject
	local realWithSceneObject
	local sceneObject
	local playerObject
	local realGetCityRegionAt
	local realWithCityRegion
	local cityRegion
	local realGetSpawnPoint
	local realSpawnMobil
	local realWriteData

	setup(function()
		realCreateEvent = createEvent
		realReadData = readData
		realWriteData = writeData
		realWithCreatureObject = OldMan.withCreatureObject
		realWithCreaturePlayerObject = OldMan.withCreaturePlayerObject
		realWithSceneObject = OldMan.withSceneObject
		realGetCityRegionAt = getCityRegionAt
		realWithCityRegion = OldMan.withCityRegion
		realGetSpawnPoint = getSpawnPoint
		realSpawnMobil = spawnMobile
	end)

	teardown(function()
		createEvent = realCreateEvent
		readData = realReadData
		writeData = realWriteData
		OldMan.withCreatureObject = realWithCreatureObject
		OldMan.withCreaturePlayerObject = realWithCreaturePlayerObject
		OldMan.withSceneObject = realWithSceneObject
		getCityRegionAt = realGetCityRegionAt
		OldMan.withCityRegion = realWithCityRegion
		getSpawnPoint = realGetSpawnPoint
		spawnMobile = realSpawnMobile
	end)

	before_each(function()
		createEvent = spy.new(function() end)
		readData = spy.new(function() return oldManId end)
		writeData = spy.new(function() end)
		getCityRegionAt = spy.new(function() return pCityRegion end)
		spawnMobile = spy.new(function() return pOldMan end)
		getSpawnPoint = spy.new(function() return { 1, 2, 3 } end)

		creatureObjectPlayer = { getObjectID = 0 }
		creatureObjectOldMan = { getObjectID = 0 }
		creatureObjectPlayer.getObjectID = spy.new(function() return playerId end)
		creatureObjectOldMan.getObjectID = spy.new(function() return oldManId end)

		sceneObject = { getParentID = 0, getZoneName = 0, getWorldPositionX = 0, getWorldPositionY = 0 }
		sceneObject.getParentID = spy.new(function() return 0 end)
		sceneObject.getZoneName = spy.new(function() return "testzone" end)
		sceneObject.getWorldPositionX = spy.new(function() return 33 end)
		sceneObject.getWorldPositionY = spy.new(function() return 22 end)

		playerObject = { isOnline = 0 }
		playerObject.isOnline = spy.new(function() return true end)

		cityRegion = { isClientRegion = 0 }
		cityRegion.isClientRegion = spy.new(function() return false end)

		OldMan.withCreatureObject = spy.new(function(pco, performThisFunction)
			if pco == pCreatureObject then
				return performThisFunction(creatureObjectPlayer)
			elseif pco == pOldMan then
				return performThisFunction(creatureObjectOldMan)
			else
				return nil
			end
		end)

		OldMan.withCreaturePlayerObject = spy.new(function(pco, performThisFunction)
			if pco == nil then
				return nil
			end
			return performThisFunction(playerObject)
		end)

		OldMan.withSceneObject = spy.new(function(pso, performThisFunction)
			if pso == nil then
				return nil
			end
			return performThisFunction(sceneObject)
		end)

		OldMan.withCityRegion = spy.new(function(pcr, performThisFunction)
			if pcr == nil then
				return nil
			end
			return performThisFunction(cityRegion)
		end)
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

					assert.spy(OldMan.withCreatureObject).was.called(2)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
					assert.spy(creatureObjectOldMan.getObjectID).was.called(1)
					assert.spy(readData).was.called_with(playerId .. OLD_MAN_ID_STRING)
				end)
			end)

			describe("When called with a player and an old man of another player", function()
				it("Should return false", function()
					readData = spy.new(function() return 0 end)

					assert.is_false(OldMan.oldManBelongsToThePlayer(pCreatureObject, pOldMan))

					assert.spy(OldMan.withCreatureObject).was.called(2)
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

					assert.spy(OldMan.withCreaturePlayerObject).was.called(1)
					assert.spy(playerObject.isOnline).was.called(1)
				end)

				it("Should return false if the player is offline.", function()
					playerObject.isOnline = spy.new(function() return false end)

					assert.is_false(OldMan.isPlayerOnline(pCreatureObject))

					assert.spy(OldMan.withCreaturePlayerObject).was.called(1)
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

					assert.spy(OldMan.withSceneObject).was.called(1)
					assert.spy(sceneObject.getParentID).was.called(1)
				end)

				it("Should return false if the parent id of the player is equal to 0", function()
					sceneObject.getParentID = spy.new(function() return 0 end)

					assert.is_false(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(OldMan.withSceneObject).was.called(1)
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

					assert.spy(OldMan.withSceneObject).was.called(1)
				end)
			end)

			describe("When called with a creature object pointer", function()
				after_each(function()
					assert.spy(sceneObject.getZoneName).was.called(1)
					assert.spy(sceneObject.getWorldPositionX).was.called(1)
					assert.spy(sceneObject.getWorldPositionY).was.called(1)
					assert.spy(OldMan.withSceneObject).was.called(1)
					assert.spy(getCityRegionAt).was.called_with("testzone", 33, 22)
				end)			

				describe("and player is in no region", function()
					it("Should return false.", function()
						getCityRegionAt = spy.new(function() return nil end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)
				end)

				describe("and the player is in city region", function()
					it("Should return true if the city region belongs to a NPC city.", function()
						cityRegion.isClientRegion = spy.new(function() return false end)

						assert.is_true(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)

					it("Should return false if the city region belongs to a player city.", function()
						cityRegion.isClientRegion = spy.new(function() return true end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)
				end)
			end)
		end)

		describe("spawnOldMan", function()
			after_each(function()
				assert.spy(sceneObject.getWorldPositionX).was.called(1)
				assert.spy(sceneObject.getWorldPositionY).was.called(1)
				assert.spy(OldMan.withSceneObject).was.called(1)
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
					assert.spy(OldMan.withCreatureObject).was.called(2)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
					assert.spy(creatureObjectOldMan.getObjectID).was.called(1)
				end)
			end)
		end)
	end)
end)
