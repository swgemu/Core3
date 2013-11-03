package.path = package.path .. ";scripts/managers/jedi/village/?.lua;scripts/screenplays/mocks/?.lua"
require("old_man")
local DirectorManagerMocks = require("director_manager_mocks")

describe("Old Man", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pOldMan = { "oldManPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local pGreetingStringId = { "greetingStringIdPointer" }
	local playerId = 12345678
	local oldManId = 98765432
	local creatureObjectPlayer
	local creatureObjectOldMan
	local playerObject
	local sceneObjectPlayer
	local sceneObjectOldMan
	local playerObject
	local cityRegion
	local aiAgent
	local greetingStringId
	local playerFirstName = "firstName"

	setup(function()
		DirectorManagerMocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.before_each()

		getCityRegionAt = spy.new(function() return pCityRegion end)
		getSceneObject = spy.new(function() return pOldMan end)
		getSpawnPoint = spy.new(function() return { 1, 2, 3 } end)
		readData = spy.new(function() return oldManId end)
		spawnMobile = spy.new(function() return pOldMan end)

		creatureObjectPlayer = {}
		creatureObjectPlayer.getFirstName = spy.new(function() return playerFirstName end)
		creatureObjectPlayer.getObjectID = spy.new(function() return playerId end)
		creatureObjectPlayer.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObjectPlayer.getScreenPlayState = spy.new(function() return 0 end)
		creatureObjectPlayer.setScreenPlayState = spy.new(function() end)
		creatureObjectPlayer.removeScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObjectPlayer
		
		creatureObjectOldMan = {}
		creatureObjectOldMan.getObjectID = spy.new(function() return oldManId end)
		DirectorManagerMocks.creatureObjects[pOldMan] = creatureObjectOldMan

		sceneObjectPlayer = {}
		sceneObjectPlayer.getParentID = spy.new(function() return 0 end)
		sceneObjectPlayer.getZoneName = spy.new(function() return "testzone" end)
		sceneObjectPlayer.getWorldPositionX = spy.new(function() return 33 end)
		sceneObjectPlayer.getWorldPositionY = spy.new(function() return 22 end)
		DirectorManagerMocks.sceneObjects[pCreatureObject] = sceneObjectPlayer
		
		sceneObjectOldMan = {}
		sceneObjectOldMan.destroyObjectFromWorld = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pOldMan] = sceneObjectOldMan		

		playerObject = {}
		playerObject.isOnline = spy.new(function() return true end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		cityRegion = {}
		cityRegion.isClientRegion = spy.new(function() return false end)
		DirectorManagerMocks.cityRegions[pCityRegion] = cityRegion
		
		aiAgent = {}
		aiAgent.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pOldMan] = aiAgent
		
		greetingStringId = {}
		greetingStringId._getObject = spy.new(function() return pGreetingStringId end)
		greetingStringId.setTT = spy.new(function(object, string) assert.same(string, playerFirstName) end)
		DirectorManagerMocks.stringIds[OLD_MAN_GREETING_STRING] = greetingStringId
	end)

	describe("Interface methods", function()
		describe("createSpawnOldManEvent", function()
			describe("When called with a player as argument", function()
				local realHasOldManSpawnEventScheduled
				local realReadOldManIdFromPlayer
				
				setup(function()
					realHasOldManSpawnEventScheduled = OldMan.hasOldManSpawnEventScheduled
					realReadOldManIdFromPlayer = OldMan.readOldManIdFromPlayer
				end)
				
				teardown(function()
					OldMan.hasOldManSpawnEventScheduled = realHasOldManSpawnEventScheduled
					OldMan.readOldManIdFromPlayer = realReadOldManIdFromPlayer
				end)
				
				before_each(function()
					OldMan.hasOldManSpawnEventScheduled = spy.new(function() return false end)
					OldMan.readOldManIdFromPlayer = spy.new(function() return OLD_MAN_NO_OLD_MAN_SPAWNED end)
				end)
				
				--[[
				it("Should check if the player has an event already scheduled.", function()
					OldMan.createSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.hasOldManSpawnEventScheduled).was.called_with(pCreatureObject)
				end)
				
				it("Should check if the player has an old man already spawned.", function()
					OldMan.createSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.readOldManIdFromPlayer).was.called_with(pCreatureObject)
				end)
				
				describe("and no event is scheduled", function()
					it("Should create an event for spawning the old man", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(createEvent).was.called(1)
					end)
					
					it("Should save information about event being scheduled on the player", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(creatureObjectPlayer.setScreenPlayState).was.called_with(creatureObjectPlayer, OLD_MAN_SCHEDULED, OLD_MAN_EVENT_SCHEDULED_STRING)
					end)
				end)
				
				describe("and an event is already scheduled", function()
					before_each(function()
						OldMan.hasOldManSpawnEventScheduled = spy.new(function() return true end)
					end)
					
					it("Should not create an event for spawning the old man.", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(createEvent).was.not_called()
					end)
					
					it("Should not save information about event being scheduled on the player", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(creatureObjectPlayer.setScreenPlayState).was.not_called()
					end)
				end)
				
				describe("and an old man has already been spawned", function()
					before_each(function()
						OldMan.readOldManIdFromPlayer = spy.new(function() return oldManId end)
					end)
					
					it("Should not create an event for spawning the old man.", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(createEvent).was.not_called()
					end)
					
					it("Should not save information about event being scheduled on the player", function()
						OldMan.createSpawnOldManEvent(pCreatureObject)
	
						assert.spy(creatureObjectPlayer.setScreenPlayState).was.not_called()
					end)
				end)
				]]
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
		
		describe("scheduleDespawnOfOldMan", function()
			describe("When called with a player and a time", function()
				it("Should create an event to despawn the old man.", function()
					OldMan.scheduleDespawnOfOldMan(pCreatureObject, OLD_MAN_DESPAWN_TIME)
					
					assert.spy(createEvent).was.called_with(OLD_MAN_DESPAWN_TIME, "OldMan", "handleDespawnEvent", pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Private methods", function()
		describe("handleSpawnOldManEvent", function()
			describe("When event to spawn old man is triggered", function()
				local realCanOldManBeSpawned
				local realTryToSpawnOldMan
				local realCreateSpawnOldManEvent
				local realSaveOldManIdOnPlayer

				setup(function()
					realCanOldManBeSpawned = OldMan.canOldManBeSpawned
					realTryToSpawnOldMan = OldMan.tryToSpawnOldMan
					realCreateSpawnOldManEvent = OldMan.createSpawnOldManEvent
					realSaveOldManIdOnPlayer = OldMan.saveOldManIdOnPlayer
				end)

				teardown(function()
					OldMan.canOldManBeSpawned = realCanOldManBeSpawned
					OldMan.tryToSpawnOldMan = realTryToSpawnOldMan
					OldMan.createSpawnOldManEvent = realCreateSpawnOldManEvent
					OldMan.saveOldManIdOnPlayer = realSaveOldManIdOnPlayer
				end)

				before_each(function()
					OldMan.canOldManBeSpawned = spy.new(function() return true end)
					OldMan.tryToSpawnOldMan = spy.new(function() return true end)
					OldMan.createSpawnOldManEvent = spy.new(function() end)
					OldMan.saveOldManIdOnPlayer = spy.new(function() end)
				end)
				
				it("Should reset screen play state about old man being scheduled.", function()
					OldMan:handleSpawnOldManEvent(pCreatureObject)
					
					assert.spy(creatureObjectPlayer.removeScreenPlayState).was.called_with(creatureObjectPlayer, OLD_MAN_SCHEDULED, OLD_MAN_EVENT_SCHEDULED_STRING)
				end)

				it("Should try to spawn the old man if the player is in a place where the old man can be spawned.", function()
					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.tryToSpawnOldMan).was.called_with(pCreatureObject)
					assert.spy(OldMan.createSpawnOldManEvent).was.not_called()
				end)

				it("Should reschedule the event if the player is not in a place where the old man can be spawned.", function()
					OldMan.canOldManBeSpawned = spy.new(function() return false end)

					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.tryToSpawnOldMan).was.not_called()
					assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)
				end)

				it("Should reschedule the event if the spawning of the old man fails.", function()
					OldMan.tryToSpawnOldMan = spy.new(function() return false end)

					OldMan:handleSpawnOldManEvent(pCreatureObject)

					assert.spy(OldMan.canOldManBeSpawned).was.called_with(pCreatureObject)
					assert.spy(OldMan.tryToSpawnOldMan).was.called_with(pCreatureObject)
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
					sceneObjectPlayer.getParentID = spy.new(function() return 1 end)

					assert.is_true(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(LuaSceneObject).was.called(1)
					assert.spy(sceneObjectPlayer.getParentID).was.called(1)
				end)

				it("Should return false if the parent id of the player is equal to 0", function()
					sceneObjectPlayer.getParentID = spy.new(function() return 0 end)

					assert.is_false(OldMan.isPlayerInABuilding(pCreatureObject))

					assert.spy(LuaSceneObject).was.called(1)
					assert.spy(sceneObjectPlayer.getParentID).was.called(1)
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
					assert.spy(sceneObjectPlayer.getZoneName).was.called(1)
					assert.spy(sceneObjectPlayer.getWorldPositionX).was.called(1)
					assert.spy(sceneObjectPlayer.getWorldPositionY).was.called(1)
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
				assert.spy(sceneObjectPlayer.getWorldPositionX).was.called(1)
				assert.spy(sceneObjectPlayer.getWorldPositionY).was.called(1)
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

						assert.spy(sceneObjectPlayer.getZoneName).was.called(1)
						assert.spy(sceneObjectPlayer.getParentID).was.called(1)
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

						assert.spy(sceneObjectPlayer.getZoneName).was.not_called()
						assert.spy(sceneObjectPlayer.getParentID).was.not_called()
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
		
		describe("tryToSpawnOldMan", function()
			describe("When called with a player creature object", function()
				local realSpawnOldMan
				local realSaveOldManIdOnPlayer
				local realSetToFollow
				
				setup(function()
					realSpawnOldMan = OldMan.spawnOldMan
					realSaveOldManIdOnPlayer = OldMan.saveOldManIdOnPlayer
					realSetToFollow = OldMan.setToFollow
				end)
				
				teardown(function()
					OldMan.spawnOldMan = realSpawnOldMan
					OldMan.saveOldManIdOnPlayer = realSaveOldManIdOnPlayer
					OldMan.setToFollow = realSetToFollow
				end)
				
				before_each(function()
					OldMan.spawnOldMan = spy.new(function() end)
					OldMan.saveOldManIdOnPlayer = spy.new(function() end)
					OldMan.setToFollow = spy.new(function() end)
				end)
			
				it("Should spawn the old man.", function()
					OldMan.tryToSpawnOldMan(pCreatureObject)
					
					assert.spy(OldMan.spawnOldMan).was.called_with(pCreatureObject)
				end)
				
				describe("and spawning the old man was successful", function()
					before_each(function()
						OldMan.spawnOldMan = spy.new(function() return pOldMan end)
					end)
					
					it("Should save the id of the old man on the player.", function()
						OldMan.tryToSpawnOldMan(pCreatureObject)
						
						assert.spy(OldMan.saveOldManIdOnPlayer).was.called_with(pCreatureObject, pOldMan)
					end)
					
					it("Should return true.", function()
						assert.is_true(OldMan.tryToSpawnOldMan(pCreatureObject))
					end)
					
					it("Should set the old man to follow the player.", function()
						OldMan.tryToSpawnOldMan(pCreatureObject)
						
						assert.spy(OldMan.setToFollow).was.called_with(pOldMan, pCreatureObject)
					end)
					
					it("Should create events for the old man to send greeting string, to stop follow the player and for despawning.", function()
						OldMan.tryToSpawnOldMan(pCreatureObject)
						
						assert.spy(createEvent).was.called(3)
					end)
				end)
				
				describe("and spawning the old man failed", function()
					before_each(function()
						OldMan.spawnOldMan = spy.new(function() return nil end)
					end)
					
					it("Should not save the id of the old man on the player, not make the old man follow the player nor create an event.", function()
						OldMan.tryToSpawnOldMan(pCreatureObject)
						assert.spy(OldMan.saveOldManIdOnPlayer).was.not_called()
						assert.spy(OldMan.setToFollow).was.not_called()
						assert.spy(createEvent).was.not_called()
					end)
					
					it("Should return false.", function()
						assert.is_false(OldMan.tryToSpawnOldMan(pCreatureObject))
					end)
				end)
			end)
		end)
		
		describe("setToFollow", function()
			describe("When called with a old man and a player", function()
				it("Should set the old man to follow the player", function()
					OldMan.setToFollow(pOldMan, pCreatureObject)
					
					assert.spy(aiAgent.setFollowObject).was.called_with(aiAgent, pCreatureObject)
				end)
			end)
			
			describe("When called with old man argument equal to nil", function()
				it("Should not do anything.", function()
					OldMan.setToFollow(nil, pCreatureObject)
					
					assert.spy(aiAgent.setFollowObject).was.not_called()
				end)
			end)
			
			describe("When called with player argument equal to nil", function()
				it("Should not do anything.", function()
					OldMan.setToFollow(pOldMan, nil)
					
					assert.spy(aiAgent.setFollowObject).was.called_with(aiAgent, nil)
				end)
			end)
		end)
		
		describe("handleStopFollowPlayerEvent", function()
			local realSetToFollow
			local realReadOldManIdFromPlayer
			
			setup(function()
				realSetToFollow = OldMan.setToFollow
				realReadOldManIdFromPlayer = OldMan.readOldManIdFromPlayer
			end)
			
			teardown(function()
				OldMan.setToFollow = realSetToFollow
				OldMan.readOldManIdFromPlayer = realReadOldManIdFromPlayer
			end)
			
			before_each(function()
				OldMan.setToFollow = spy.new(function() end)
				OldMan.readOldManIdFromPlayer = spy.new(function() return oldManId end)
			end)
			
			describe("When called with the player as argument", function()
				it("Should read the old man id from the player.", function()
					OldMan:handleStopFollowPlayerEvent(pCreatureObject)
					
					assert.spy(OldMan.readOldManIdFromPlayer).was.called_with(pCreatureObject)
				end)
				
				it("Should get a pointer to the old man.", function()
					OldMan:handleStopFollowPlayerEvent(pCreatureObject)
					
					assert.spy(getSceneObject).was.called_with(oldManId)
				end)
				
				it("Should tell the old man to follow no one.", function()
					OldMan:handleStopFollowPlayerEvent(pCreatureObject)
					
					assert.spy(OldMan.setToFollow).was.called_with(pOldMan, nil)
				end)
			end)
		end)
		
		describe("handleSpatialChatEvent", function()
			local realSendGreetingString
			local realReadOldManIdFromPlayer
			
			setup(function()
				realSendGreetingString = OldMan.sendGreetingString
				realReadOldManIdFromPlayer = OldMan.readOldManIdFromPlayer
			end)
			
			teardown(function()
				OldMan.sendGreetingString = realSendGreetingString
				OldMan.readOldManIdFromPlayer = realReadOldManIdFromPlayer
			end)
			
			before_each(function()
				OldMan.sendGreetingString = spy.new(function() end)
				OldMan.readOldManIdFromPlayer = spy.new(function() return oldManId end)
			end)
			
			describe("When called with the player as argument", function()
				it("Should read the old man id from the player.", function()
					OldMan:handleSpatialChatEvent(pCreatureObject)
					
					assert.spy(OldMan.readOldManIdFromPlayer).was.called_with(pCreatureObject)
				end)
				
				it("Should get a pointer to the old man.", function()
					OldMan:handleSpatialChatEvent(pCreatureObject)
					
					assert.spy(getSceneObject).was.called_with(oldManId)
				end)
				
				it("Should send the greeting string.", function()
					OldMan:handleSpatialChatEvent(pCreatureObject)
					
					assert.spy(OldMan.sendGreetingString).was.called_with(pOldMan, pCreatureObject)
				end)
			end)
		end)
		
		describe("readOldManIdFromPlayer", function()
			describe("When called with a pointer to a creature object of a player as argument", function()
				it("Should read the old man id from the player.", function()
					OldMan.readOldManIdFromPlayer(pCreatureObject)
					
					assert.spy(readData).was.called_with(playerId .. OLD_MAN_ID_STRING)
					assert.spy(LuaCreatureObject).was.called(1)
					assert.spy(creatureObjectPlayer.getObjectID).was.called(1)
				end)
			end)
		end)
		
		describe("sendGreetingString", function()
			describe("When called with old man and player", function()
				local realGetPlayerFirstName
				
				setup(function()
					realGetPlayerFirstName = OldMan.getPlayerFirstName
				end)
				
				teardown(function()
					OldMan.getPlayerFirstName = realGetPlayerFirstName
				end)
				
				before_each(function()
					OldMan.getPlayerFirstName = spy.new(function() return playerFirstName end)
				end)
				
				it("Should create a string id for the oldman_greeting string.", function()
					OldMan.sendGreetingString(pOldMan, pCreatureObject)
					
					assert.spy(LuaStringIdChatParameter).was.called_with(OLD_MAN_GREETING_STRING)
				end)
				
				it("Should get the name of the player.", function()
					OldMan.sendGreetingString(pOldMan, pCreatureObject)
					
					assert.spy(OldMan.getPlayerFirstName).was.called_with(pCreatureObject)
				end)
				
				it("Should set the %TT of the string to the name of the player.", function()
					OldMan.sendGreetingString(pOldMan, pCreatureObject)
					
					assert.spy(greetingStringId.setTT).was.called(1)
				end)
				
				it("Should send the string id to spatial chat.", function()
					OldMan.sendGreetingString(pOldMan, pCreatureObject)
					
					assert.spy(spatialChat).was.called_with(pOldMan, pGreetingStringId)
				end)
			end)
		end)
		
		describe("getPlayerFirstName", function()
			describe("When called with a player", function()
				it("Should return the first name of the player.", function()
					assert.same(OldMan.getPlayerFirstName(pCreatureObject), playerFirstName)
					
					assert.spy(creatureObjectPlayer.getFirstName).was.called(1)
				end)
			end)
			describe("When called with nil", function()
				it("Should return an empty string.", function()
					assert.same(OldMan.getPlayerFirstName(nil), "")
				end)
			end)
		end)
		
		describe("handleDespawnEvent", function()
			local realDespawnOldMan
			local realReadOldManIdFromPlayer
			local realCreateSpawnOldManEvent
			
			setup(function()
				realDespawnOldMan = OldMan.despawnOldMan
				realReadOldManIdFromPlayer = OldMan.readOldManIdFromPlayer
				realCreateSpawnOldManEvent = OldMan.createSpawnOldManEvent
			end)
			
			teardown(function()
				OldMan.despawnOldMan = realDespawnOldMan
				OldMan.readOldManIdFromPlayer = realReadOldManIdFromPlayer
				OldMan.createSpawnOldManEvent = realCreateSpawnOldManEvent
			end)
			
			before_each(function()
				OldMan.despawnOldMan = spy.new(function() end)
				OldMan.readOldManIdFromPlayer = spy.new(function() return oldManId end)
				OldMan.createSpawnOldManEvent = spy.new(function() end)
			end)
			
			describe("When called with the player as argument", function()
				it("Should read the old man id from the player.", function()
					OldMan:handleDespawnEvent(pCreatureObject)
					
					assert.spy(OldMan.readOldManIdFromPlayer).was.called_with(pCreatureObject)
				end)
				
				it("Should get a pointer to the old man.", function()
					OldMan:handleDespawnEvent(pCreatureObject)
					
					assert.spy(getSceneObject).was.called_with(oldManId)
				end)
				
				it("Should despawn the old man.", function()
					OldMan:handleDespawnEvent(pCreatureObject)
					
					assert.spy(OldMan.despawnOldMan).was.called_with(pOldMan)
				end)
				
				it("Should set the id of the spawned old man to 0 to indicate that he is despawned.", function()
					OldMan:handleDespawnEvent(pCreatureObject)
					
					assert.spy(writeData).was.called_with(playerId .. OLD_MAN_ID_STRING, OLD_MAN_NO_OLD_MAN_SPAWNED)
				end)
				
				it("Should reschedule the old man.", function()
					OldMan:handleDespawnEvent(pCreatureObject)
					
					assert.spy(OldMan.createSpawnOldManEvent).was.called_with(pCreatureObject)
				end)
			end)
		end)
		
		describe("despawnOldMan", function()
			describe("When called with an old man as argument", function()
				it("Should destroy the old man from the world.", function()
					OldMan.despawnOldMan(pOldMan)
					
					assert.spy(sceneObjectOldMan.destroyObjectFromWorld).was.called(1)
				end)
			end)
			
			describe("When called with nil as argument", function()
				it("Should not try to destroy the old man from the world.", function()
					OldMan.despawnOldMan(nil)
					
					assert.spy(sceneObjectOldMan.destroyObjectFromWorld).was.not_called()
				end)
			end)
		end)
		
		describe("hasOldManSpawnEventScheduled", function()
			describe("When called with a player as argument", function()
				it("Should read the event scheduled information from the player.", function()
					OldMan.hasOldManSpawnEventScheduled(pCreatureObject)
					
					assert.spy(creatureObjectPlayer.getScreenPlayState).was.called_with(creatureObjectPlayer, OLD_MAN_EVENT_SCHEDULED_STRING)
				end)
				
				describe("and the data stored on the player indicates that the event is scheduled", function()
					it("Should return true.", function()
						creatureObjectPlayer.getScreenPlayState = spy.new(function() return OLD_MAN_SCHEDULED end)
					
						assert.is_true(OldMan.hasOldManSpawnEventScheduled(pCreatureObject))
					end)
				end)
				
				describe("and the data stored on the player indicates that the event is not scheduled", function()
					it("Should return false.", function()
						creatureObjectPlayer.getScreenPlayState = spy.new(function() return OLD_MAN_NOT_SCHEDULED end)
					
						assert.is_false(OldMan.hasOldManSpawnEventScheduled(pCreatureObject))
					end)
				end)
			end)
		end)		
	end)
end)
