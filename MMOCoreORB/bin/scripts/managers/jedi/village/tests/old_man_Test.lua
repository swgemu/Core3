package.path = package.path .. ";scripts/managers/jedi/village/?.lua"
require("old_man")

describe("Old Man", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pOldMan = { "oldManPointer" }

	describe("Interface methods", function()
		describe("createSpawnOldManEvent", function()
			describe("When called with a player as argument", function()
				it("Should create an event for spawning the old man", function()
					local realCreateEvent = createEvent
					createEvent = spy.new(function() end)

					OldMan.createSpawnOldManEvent(pCreatureObject)

					assert.spy(createEvent).was.called(1)

					createEvent = realCreateEvent
				end)
			end)
		end)

		describe("oldManBelongsToThePlayer", function()
			local playerId = 12345678
			local oldManId = 98765432
			local getObjectIDPlayerSpy
			local getObjectIDOldManSpy
			local creatureObjectPlayer
			local creatureObjectOldMan
			local realWithCreatureObject
			local realReadData

			setup(function()
				realWithCreatureObject = OldMan.withCreatureObject
				realReadData = readData
			end)

			teardown(function()
				OldMan.withCreatureObject = realWithCreatureObject
				readData = realReadData
			end)

			before_each(function()
				getObjectIDPlayerSpy = spy.new(function() return playerId end)
				getObjectIDOldManSpy = spy.new(function() return oldManId end)
				creatureObjectPlayer = { getObjectID = getObjectIDPlayerSpy }
				creatureObjectOldMan = { getObjectID = getObjectIDOldManSpy }
				OldMan.withCreatureObject = spy.new(function(pco, performThisFunction)
					if pco == pCreatureObject then
						return performThisFunction(creatureObjectPlayer)
					elseif pco == pOldMan then
						return performThisFunction(creatureObjectOldMan)
					else
						return nil
					end
				end)
			end)

			describe("When called with a player and his old man", function()
				it("Should return true", function()
					readData = spy.new(function() return oldManId end)

					assert.is_true(OldMan.oldManBelongsToThePlayer(pCreatureObject, pOldMan))

					assert.spy(OldMan.withCreatureObject).was.called(2)
					assert.spy(getObjectIDPlayerSpy).was.called(1)
					assert.spy(getObjectIDOldManSpy).was.called(1)
					assert.spy(readData).was.called_with(playerId .. OLD_MAN_ID_STRING)
				end)
			end)

			describe("When called with a player and an old man of another player", function()
				it("Should return false", function()
					readData = spy.new(function() return 0 end)

					assert.is_false(OldMan.oldManBelongsToThePlayer(pCreatureObject, pOldMan))

					assert.spy(OldMan.withCreatureObject).was.called(2)
					assert.spy(getObjectIDPlayerSpy).was.called(1)
					assert.spy(getObjectIDOldManSpy).was.called(1)
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

				after_each(function()
					--assert.spy(OldMan.isPlayerOnline).was.called_with(pCreatureObject)
					--assert.spy(OldMan.isplayerInNpcCity).was.called_with(pCreatureObject)
					--assert.spy(OldMan.isPlayerInABuilding).was.called_with(pCreatureObject)
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
				local realWithCreaturePlayerObject

				setup(function()
					realWithCreaturePlayerObject = OldMan.withCreaturePlayerObject
				end)

				teardown(function()
					OldMan.withCreaturePlayerObject = realWithCreaturePlayerObject
				end)
			
				it("Should return true if the player is online.", function()
					local isOnlineSpy = spy.new(function() return true end)
					local playerObject = { isOnline = isOnlineSpy }

					OldMan.withCreaturePlayerObject = spy.new(function(pco, performThisFunction)
						assert.same(pco, pCreatureObject)
						return performThisFunction(playerObject)
					end)

					assert.is_true(OldMan.isPlayerOnline(pCreatureObject))

					assert.spy(OldMan.withCreaturePlayerObject).was.called(1)
					assert.spy(isOnlineSpy).was.called(1)
				end)

				it("Should return false if the player is offline.", function()
					local isOnlineSpy = spy.new(function() return false end)
					local playerObject = { isOnline = isOnlineSpy }

					OldMan.withCreaturePlayerObject = spy.new(function(pco, performThisFunction)
						assert.same(pco, pCreatureObject)
						return performThisFunction(playerObject)
					end)

					assert.is_false(OldMan.isPlayerOnline(pCreatureObject))

					assert.spy(OldMan.withCreaturePlayerObject).was.called(1)
					assert.spy(isOnlineSpy).was.called(1)
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
				local realWithSceneObject

				setup(function()
					realWithSceneObject = OldMan.withSceneObject
				end)

				teardown(function()
					OldMan.withSceneObject = realWithSceneObject
				end)

				it("Should return true if the parent id of the player is not equal to 0", function()
					local getParentIDSpy = spy.new(function() return 1 end)
					local playerObject = { getParentID = getParentIDSpy }

					OldMan.withSceneObject = spy.new(function(pso, performThisFunction)
						assert.same(pso, pCreatureObject)
						return performThisFunction(playerObject)
					end)

					assert.is_true(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(OldMan.withSceneObject).was.called(1)
					assert.spy(getParentIDSpy).was.called(1)
				end)

				it("Should return false if the parent id of the player is equal to 0", function()
					local getParentIDSpy = spy.new(function() return 0 end)
					local playerObject = { getParentID = getParentIDSpy }

					OldMan.withSceneObject = spy.new(function(pso, performThisFunction)
						assert.same(pso, pCreatureObject)
						return performThisFunction(playerObject)
					end)

					assert.is_false(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(OldMan.withSceneObject).was.called(1)
					assert.spy(getParentIDSpy).was.called(1)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false.", function()
					assert.is_false(OldMan.isPlayerInABuilding(nil))
				end)
			end)
		end)

		describe("isPlayerInNpcCity", function()
			local realWithSceneObject

			setup(function()
				realWithSceneObject = OldMan.withSceneObject
			end)

			teardown(function()
				OldMan.withSceneObject = realWithSceneObject
			end)

			describe("When called with a nil pointer", function()
				it("Should return false", function()
					OldMan.withSceneObject = spy.new(function() return nil end)

					assert.is_false(OldMan.isPlayerInNpcCity(nil))

					assert.spy(OldMan.withSceneObject).was.called(1)
				end)
			end)

			describe("When called with a creature object pointer", function()
				local getZoneNameSpy
				local getWorldPositionXSpy
				local getWorldPositionYSpy
				local sceneObject
				local realGetCityRegionAt
				local realWithCityRegion

				setup(function()
					realGetCityRegionAt = getCityRegionAt
					realWithCityRegion = OldMan.withCityRegion
				end)

				teardown(function()
					getCityRegionAt = realGetCityRegionAt
					OldMan.withCityRegion = realWithCityRegion
				end)

				before_each(function()
					getZoneNameSpy = spy.new(function() return "testzone" end)
					getWorldPositionXSpy = spy.new(function() return 33 end)
					getWorldPositionYSpy = spy.new(function() return 22 end)
					sceneObject = { getZoneName = getZoneNameSpy, getWorldPositionX = getWorldPositionXSpy, getWorldPositionY = getWorldPositionYSpy }			
		
					OldMan.withSceneObject = spy.new(function(sco, performThisFunction) 
						assert.same(sco, pCreatureObject)
						return performThisFunction(sceneObject)
					end)
				end)

				after_each(function()
					assert.spy(getZoneNameSpy).was.called(1)
					assert.spy(getWorldPositionXSpy).was.called(1)
					assert.spy(getWorldPositionYSpy).was.called(1)
					assert.spy(OldMan.withSceneObject).was.called(1)
					assert.spy(getCityRegionAt).was.called_with("testzone", 33, 22)
				end)			

				describe("and player is in no region", function()
					it("Should return false.", function()
						getCityRegionAt = spy.new(function() return nil end)
						OldMan.withCityRegion = spy.new(function(pcr)
							assert.same(pcr, nil)
							return nil
						end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)
				end)

				describe("and the player is in city region", function()
					local pCityRegion = { "cityRegionPointer" }

					it("Should return true if the city region belongs to a NPC city.", function()
						local isClientRegionSpy = spy.new(function() return false end)
						local cityRegion = { isClientRegion = isClientRegionSpy }

						getCityRegionAt = spy.new(function() return pCityRegion end)
						OldMan.withCityRegion = spy.new(function(pcr, performThisFunction)
							assert.same(pcr, pCityRegion)
							return performThisFunction(cityRegion)
						end)

						assert.is_true(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)

					it("Should return false if the city region belongs to a player city.", function()
						local isClientRegionSpy = spy.new(function() return true end)
						local cityRegion = { isClientRegion = isClientRegionSpy }

						getCityRegionAt = spy.new(function() return pCityRegion end)
						OldMan.withCityRegion = spy.new(function(pcr, performThisFunction)
							assert.same(pcr, pCityRegion)
							return performThisFunction(cityRegion)
						end)

						assert.is_false(OldMan.isPlayerInNpcCity(pCreatureObject))

						assert.spy(OldMan.withCityRegion).was.called(1)
					end)
				end)
			end)
		end)

		describe("spawnOldMan", function()
			local realWithSceneObject
			local getZoneNameSpy
			local getParentIDSpy
			local getWorldPositionXSpy
			local getWorldPositionYSpy
			local sceneObject
			local realGetSpawnPoint
			local realSpawnMobil

			setup(function()
				realWithSceneObject = OldMan.withSceneObject
				realGetSpawnPoint = getSpawnPoint
				realSpawnMobil = spawnMobile
			end)

			teardown(function()
				OldMan.withSceneObject = realWithSceneObject
				getSpawnPoint = realGetSpawnPoint
				spawnMobile = realSpawnMobile
			end)

			before_each(function()
				getZoneNameSpy = spy.new(function() return "testzone" end)
				getParentIDSpy = spy.new(function() return 0 end)
				getWorldPositionXSpy = spy.new(function() return 33 end)
				getWorldPositionYSpy = spy.new(function() return 22 end)
				sceneObject = { getZoneName = getZoneNameSpy, getParentID = getParentIDSpy, getWorldPositionX = getWorldPositionXSpy, getWorldPositionY = getWorldPositionYSpy }
				OldMan.withSceneObject = spy.new(function(pso, performThisFunction)
					assert.same(pso, pCreatureObject)
					return performThisFunction(sceneObject)
				end)
				spawnMobile = spy.new(function() return pOldMan end)
			end)

			after_each(function()
				assert.spy(getWorldPositionXSpy).was.called(1)
				assert.spy(getWorldPositionYSpy).was.called(1)
				assert.spy(OldMan.withSceneObject).was.called(1)
			end)

			describe("When called with a creature object pointer", function()
				it("Should get a spawn point for the old man.", function()
					getSpawnPoint = spy.new(function() return { 1, 2, 3 } end)

					OldMan.spawnOldMan(pCreatureObject)

					assert.spy(getSpawnPoint).was.called_with(pCreatureObject, 33, 22, OLD_MAN_MIN_SPAWN_DISTANCE, OLD_MAN_MAX_SPAWN_DISTANCE)
				end)

				describe("and a spawn point is returned", function()
					before_each(function()
						getSpawnPoint = spy.new(function() return { 1, 2, 3 } end)
					end)

					it("Should spawn the old man.", function()
						OldMan.spawnOldMan(pCreatureObject)

						assert.spy(getZoneNameSpy).was.called(1)
						assert.spy(getParentIDSpy).was.called(1)
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

						assert.spy(getZoneNameSpy).was.not_called()
						assert.spy(getParentIDSpy).was.not_called()
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
					local playerId = 12345678
					local oldManId = 98765432
					local realWriteData = writeData
					writeData = spy.new(function() end)
					getObjectIDPlayerSpy = spy.new(function() return playerId end)
					getObjectIDOldManSpy = spy.new(function() return oldManId end)
					local creatureObjectPlayer = { getObjectID = getObjectIDPlayerSpy }
					local creatureObjectOldMan = { getObjectID = getObjectIDOldManSpy }
					local realWithCreatureObject = OldMan.withCreatureObject
					OldMan.withCreatureObject = spy.new(function(pco, performThisFunction)
						if pco == pCreatureObject then
							return performThisFunction(creatureObjectPlayer)
						elseif pco == pOldMan then
							return performThisFunction(creatureObjectOldMan)
						else
							return nil
						end
					end)					

					OldMan.saveOldManIdOnPlayer(pCreatureObject, pOldMan)

					assert.spy(writeData).was.called_with(playerId .. OLD_MAN_ID_STRING, oldManId)
					assert.spy(OldMan.withCreatureObject).was.called(2)
					assert.spy(getObjectIDPlayerSpy).was.called(1)
					assert.spy(getObjectIDOldManSpy).was.called(1)

					writeData = realWriteData
					OldMan.withCreatureObject = realWithCreatureObject
				end)
			end)
		end)
	end)
end)
