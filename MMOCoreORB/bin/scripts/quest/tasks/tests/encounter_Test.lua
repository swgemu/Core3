local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local Encounter = require("quest.tasks.encounter")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")

local testEncounter = Encounter:new {
	-- Task properties
	taskName = "testEncounter",
	-- Encounter properties
	minimumTimeUntilEncounter = 10,
	maximumTimeUntilEncounter = 10,
	encounterDespawnTime = 5
}

local TASK_STARTED = 0xABCD
local CLOSING_IN_TIME = 10 * 1000
local AT_PLAYER_TIME = 30 * 1000

describe("Encounter", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local pCityRegion = { "cityRegionPointer" }
	local creatureObject
	local playerObject
	local sceneObjectPlayer
	local cityRegion
	local playerXCoordinate = 33
	local playerYCoordinate = 22
	local playerZoneName = "testzone"
	local encounterTemplateName = "old_man"
	local playerId = 12345678
	local spawnPoints = {
		{ 1, 2, 3 },
		{ 4, 5, 6 },
		{ 7, 8, 9 }
	}
	local playerParentID = 0
	local pSpawnedObject1 = { "spawnedObjectPointer1" }
	local pSpawnedObject2 = { "spawnedObjectPointer2" }
	local pSpawnedObject3 = { "spawnedObjectPointer3" }
	local aiAgentObject1
	local aiAgentObject2
	local aiAgentObject3
	local creatureObject1
	local creatureObject2
	local creatureObject3
	local spawnedObjects = {
		pSpawnedObject1,
		pSpawnedObject2,
		pSpawnedObject3
	}

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
		creatureObject.setScreenPlayState = spy.new(function() end)
		creatureObject.getScreenPlayState = spy.new(function() return 0 end)
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.removeScreenPlayState = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		sceneObjectPlayer = {}
		sceneObjectPlayer.getParentID = spy.new(function() return playerParentID end)
		sceneObjectPlayer.getObjectID = spy.new(function() return playerId end)
		sceneObjectPlayer.getZoneName = spy.new(function() return playerZoneName end)
		sceneObjectPlayer.getWorldPositionX = spy.new(function() return playerXCoordinate end)
		sceneObjectPlayer.getWorldPositionY = spy.new(function() return playerYCoordinate end)
		DirectorManagerMocks.sceneObjects[pCreatureObject] = sceneObjectPlayer

		aiAgentObject1 = {}
		aiAgentObject1.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pSpawnedObject1] = aiAgentObject1

		aiAgentObject2 = {}
		aiAgentObject2.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pSpawnedObject2] = aiAgentObject2

		aiAgentObject3 = {}
		aiAgentObject3.setFollowObject = spy.new(function() end)
		DirectorManagerMocks.aiAgents[pSpawnedObject3] = aiAgentObject3

		creatureObject1 = {}
		creatureObject1.setPvpStatusBitmask = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pSpawnedObject1] = creatureObject1

		creatureObject2 = {}
		creatureObject2.setPvpStatusBitmask = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pSpawnedObject2] = creatureObject2

		creatureObject3 = {}
		creatureObject3.setPvpStatusBitmask = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pSpawnedObject3] = creatureObject3

		playerObject = {}
		playerObject.isOnline = spy.new(function() return true end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		cityRegion = {}
		cityRegion.isClientRegion = spy.new(function() return false end)
		DirectorManagerMocks.cityRegions[pCityRegion] = cityRegion

		testEncounter.spawnObjectList = {
			{ template = encounterTemplateName, referencePoint = 0, minimumDistance = 32, maximumDistance = 64, followPlayer = true, setNotAttackable = true },
			{ template = encounterTemplateName, referencePoint = 0, minimumDistance = 3, maximumDistance = 6, followPlayer = false, setNotAttackable = false },
			{ template = encounterTemplateName, referencePoint = 1, minimumDistance = 16, maximumDistance = 32, followPlayer = true, setNotAttackable = false }
		}
		testEncounter.onEncounterSpawned = spy.new(function() end)
		testEncounter.isEncounterFinished = spy.new(function() return false end)
		testEncounter.onEncounterClosingIn = spy.new(function() end)
		testEncounter.onEncounterAtPlayer = spy.new(function() end)
	end)

	describe("Interface functions", function()
		describe("start", function()
			local realTaskStart

			setup(function()
				realTaskStart = testEncounter.taskStart
			end)

			teardown(function()
				testEncounter.taskStart = realTaskStart
			end)

			before_each(function()
				testEncounter.taskStart = spy.new(function() return true end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskStart function.", function()
					testEncounter:start(pCreatureObject)

					assert.spy(testEncounter.taskStart).was.called_with(testEncounter, pCreatureObject)
				end)
			end)
		end)

		describe("finish", function()
			local realTaskFinish

			setup(function()
				realTaskFinish = testEncounter.taskFinish
			end)

			teardown(function()
				testEncounter.taskFinish = realTaskFinish
			end)

			before_each(function()
				testEncounter.taskFinish = spy.new(function() return true end)
				creatureObject.getScreenPlayState = spy.new(function() return TASK_STARTED end)
			end)

			describe("When called with a player", function()
				it("Should call the private taskFinish function.", function()
					testEncounter:finish(pCreatureObject)

					assert.spy(testEncounter.taskFinish).was.called_with(testEncounter, pCreatureObject)
				end)
			end)
		end)
	end)

	describe("Events", function()
		describe("handleSpawnEvent", function()
			describe("When called with a player", function()
				local realIsPlayerInPositionForEncounter
				local realStart
				local realCreateEncounter

				setup(function()
					testEncounter:setupSpawnAndDespawnEvents()
					realIsPlayerInPositionForEncounter = testEncounter.isPlayerInPositionForEncounter
					realStart = testEncounter.despawnTask.start
					realCreateEncounter = testEncounter.createEncounter
				end)

				teardown(function()
					testEncounter.isPlayerInPositionForEncounter = realIsPlayerInPositionForEncounter
					testEncounter.despawnTask.start = realStart
					testEncounter.createEncounter = realCreateEncounter
				end)

				before_each(function()
					testEncounter.isPlayerInPositionForEncounter = spy.new(function() return false end)
					testEncounter.despawnTask.start = spy.new(function() end)
					testEncounter.createEncounter = spy.new(function() end)
				end)

				describe("and the encounter is not finished yet", function()
					local realDespawnTask

					setup(function()
						testEncounter:setupSpawnAndDespawnEvents()
						realDespawnTask = testEncounter.despawnTask
					end)

					teardown(function()
						testEncounter.despawnTask = realDespawnTask
					end)

					before_each(function()
						testEncounter.despawnTask = {}
						testEncounter.despawnTask.start = spy.new(function() end)
						testEncounter.isEncounterFinished = spy.new(function() return false end)
					end)

					it("Should check if the player is in a position where the encounter can happen.", function()
						testEncounter:handleSpawnEvent(pCreatureObject)

						assert.spy(testEncounter.isPlayerInPositionForEncounter).was.called_with(testEncounter, pCreatureObject)
					end)

					it("Should start the despawn task.", function()
						testEncounter:handleSpawnEvent(pCreatureObject)

						assert.spy(testEncounter.despawnTask.start).was.called_with(testEncounter.despawnTask, pCreatureObject)
					end)

					describe("and the player is in a position where the encounter can be spawned.", function()
						before_each(function()
							testEncounter.isPlayerInPositionForEncounter = spy.new(function() return true end)
						end)

						it("Should call the createEncounter function.", function()
							testEncounter:handleSpawnEvent(pCreatureObject)

							assert.spy(testEncounter.createEncounter).was.called_with(testEncounter, pCreatureObject)
						end)
					end)

					describe("and the player is not in a position where the encounter can be spawned.", function()
						it("Should not call the createEncounter function.", function()
							testEncounter:handleSpawnEvent(pCreatureObject)

							assert.spy(testEncounter.createEncounter).was.not_called()
						end)
					end)
				end)

				describe("and the encounter is finished", function()
					local realFinish

					setup(function()
						realFinish = testEncounter.finish
					end)

					teardown(function()
						testEncounter.finish = realFinish
					end)

					before_each(function()
						testEncounter.isEncounterFinished = spy.new(function() return true end)
						testEncounter.finish = spy.new(function() end)
					end)

					it("Should call finish on the encounter.", function()
						testEncounter:handleSpawnEvent(pCreatureObject)

						assert.spy(testEncounter.finish).was.called_with(testEncounter, pCreatureObject)
					end)
				end)
			end)
		end)

		describe("handleDespawnEvent", function()
			describe("When called with a player", function()
				local realtaskStart
				local realFinish

				setup(function()
					realtaskStart = testEncounter.taskStart
					realFinish = testEncounter.finish
				end)

				teardown(function()
					testEncounter.taskStart = realtaskStart
					testEncounter.finish = realFinish
				end)

				before_each(function()
					testEncounter.taskStart = spy.new(function() return true end)
					testEncounter.finish = spy.new(function() end)
				end)

				it("Should despawn the encounter objects.", function()
					testEncounter:handleDespawnEvent(pCreatureObject)

					assert.spy(SpawnMobilesMocks.despawnMobiles).was.called_with(pCreatureObject, testEncounter.taskName)
				end)

				describe("and the encounter is finished", function()
					before_each(function()
						testEncounter.isEncounterFinished = spy.new(function() return true end)
					end)

					it("Should call the taskStart function.", function()
						testEncounter:handleDespawnEvent(pCreatureObject)

						assert.spy(testEncounter.finish).was.called_with(testEncounter, pCreatureObject)
					end)
				end)

				describe("and the encounter is finished", function()
					it("Should call the taskStart function.", function()
						testEncounter:handleDespawnEvent(pCreatureObject)

						assert.spy(testEncounter.taskStart).was.called_with(testEncounter, pCreatureObject)
					end)
				end)
			end)
		end)
	end)

	describe("Private functions", function()
		describe("taskStart", function()
			describe("When called with a player", function()
				local realSpawnTask
				local realSetupSpawnAndDespawnEvents

				setup(function()
					realSpawnTask = testEncounter.spawnTask
					realSetupSpawnAndDespawnEvents = testEncounter.setupSpawnAndDespawnEvents
				end)

				teardown(function()
					testEncounter.spawnTask = realSpawnTask
					testEncounter.setupSpawnAndDespawnEvents = realSetupSpawnAndDespawnEvents
				end)

				before_each(function()
					testEncounter.spawnTask = {}
					testEncounter.spawnTask.start = spy.new(function() end)
					testEncounter.setupSpawnAndDespawnEvents = spy.new(function() end)
				end)

				it("Should setup the spawn and despawn events.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.spy(testEncounter.setupSpawnAndDespawnEvents).was.called_with(testEncounter)
				end)

				it("Should start the spawn task.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.spy(testEncounter.spawnTask.start).was.called_with(testEncounter.spawnTask, pCreatureObject)
				end)
			end)
		end)

		describe("setupSpawnAndDespawnEvents", function()
			describe("When called with a player", function()
				it("Should set the minimum event time on the spawn task to the minimum spawn time for the encounter.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter.minimumTimeUntilEncounter, testEncounter.spawnTask.minimumTimeUntilEvent)
				end)

				it("Should set the maximum event time on the spawn task to the maximum spawn time for the encounter.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter.maximumTimeUntilEncounter, testEncounter.spawnTask.maximumTimeUntilEvent)
				end)

				it("Should set the encounter variable on the spawn task.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter, testEncounter.spawnTask.encounter)
				end)

				it("Should set the minimum event time on the despawn task to the encounter despawn time.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter.encounterDespawnTime, testEncounter.despawnTask.minimumTimeUntilEvent)
				end)

				it("Should set the maximum event time on the despawn task to the encounter despawn time.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter.encounterDespawnTime, testEncounter.despawnTask.maximumTimeUntilEvent)
				end)

				it("Should set the encounter variable on the despawn task.", function()
					testEncounter:taskStart(pCreatureObject)

					assert.same(testEncounter, testEncounter.despawnTask.encounter)
				end)
			end)
		end)

		describe("isPlayerInPositionForEncounter", function()
			describe("When called with the player as argument", function()
				local realIsPlayerOnline
				local realIsPlayerInNpcCity
				local realIsPlayerInABuilding

				setup(function()
					realIsPlayerOnline = testEncounter.isPlayerOnline
					realIsPlayerInNpcCity = testEncounter.isPlayerInNpcCity
					realIsPlayerInABuilding = testEncounter.isPlayerInABuilding
				end)

				teardown(function()
					testEncounter.isPlayerOnline = realIsPlayerOnline
					testEncounter.isPlayerInNpcCity = realIsPlayerInNpcCity
					testEncounter.isPlayerInABuilding = realIsPlayerInABuilding
				end)

				before_each(function()
					testEncounter.isPlayerOnline = spy.new(function() return true end)
					testEncounter.isPlayerInNpcCity = spy.new(function() return false end)
					testEncounter.isPlayerInABuilding = spy.new(function() return false end)
				end)

				describe("and the player is outside, not in an npc city and online.", function()
					it("Should return true.", function()
						assert.is_true(testEncounter:isPlayerInPositionForEncounter(pCreatureObject))
					end)
				end)

				describe("and the player is offline", function()
					it("Should return false.", function()
						testEncounter.isPlayerOnline = spy.new(function() return false end)

						assert.is_false(testEncounter:isPlayerInPositionForEncounter(pCreatureObject))
					end)
				end)

				describe("and the player is in a NPC city", function()
					it("Should return false.", function()
						testEncounter.isPlayerInNpcCity = spy.new(function() return true end)

						assert.is_false(testEncounter:isPlayerInPositionForEncounter(pCreatureObject))
					end)
				end)

				describe("and the player is inside a building", function()
					it("Should return false.", function()
						testEncounter.isPlayerInABuilding = spy.new(function() return true end)

						assert.is_false(testEncounter:isPlayerInPositionForEncounter(pCreatureObject))
					end)
				end)
			end)
		end)

		describe("isPlayerOnline", function()
			describe("When called with a creature object pointer", function()
				it("Should return true if the player is online.", function()
					playerObject.isOnline = spy.new(function() return true end)

					assert.is_true(testEncounter:isPlayerOnline(pCreatureObject))

					assert.spy(playerObject.isOnline).was.called(1)
				end)

				it("Should return false if the player is offline.", function()
					playerObject.isOnline = spy.new(function() return false end)

					assert.is_false(testEncounter:isPlayerOnline(pCreatureObject))

					assert.spy(playerObject.isOnline).was.called(1)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false.", function()
					assert.is_false(testEncounter:isPlayerOnline(nil))
				end)
			end)
		end)

		describe("isPlayerInABuilding", function()
			describe("When called with a creature object pointer", function()
				it("Should return true if the parent id of the player is not equal to 0", function()
					sceneObjectPlayer.getParentID = spy.new(function() return 1 end)

					assert.is_true(testEncounter:isPlayerInABuilding(pCreatureObject))

					assert.spy(sceneObjectPlayer.getParentID).was.called(1)
				end)

				it("Should return false if the parent id of the player is equal to 0", function()
					sceneObjectPlayer.getParentID = spy.new(function() return 0 end)

					assert.is_false(testEncounter:isPlayerInABuilding(pCreatureObject))

					assert.spy(sceneObjectPlayer.getParentID).was.called(1)
				end)
			end)

			describe("When called with nil as argument", function()
				it("Should return false.", function()
					assert.is_false(testEncounter:isPlayerInABuilding(nil))
				end)
			end)
		end)

		describe("isPlayerInNpcCity", function()
			before_each(function()
				getCityRegionAt = spy.new(function() return pCityRegion end)
			end)

			describe("When called with a nil pointer", function()
				it("Should return false.", function()
					assert.is_false(testEncounter:isPlayerInNpcCity(nil))
				end)
			end)

			describe("When called with a creature object pointer", function()
				after_each(function()
					assert.spy(sceneObjectPlayer.getZoneName).was.called(1)
					assert.spy(sceneObjectPlayer.getWorldPositionX).was.called(1)
					assert.spy(sceneObjectPlayer.getWorldPositionY).was.called(1)
					assert.spy(getCityRegionAt).was.called_with("testzone", 33, 22)
				end)

				describe("and player is in no region", function()
					it("Should return false.", function()
						getCityRegionAt = spy.new(function() return nil end)

						assert.is_false(testEncounter:isPlayerInNpcCity(pCreatureObject))
					end)
				end)

				describe("and the player is in city region", function()
					it("Should return true if the city region belongs to a NPC city.", function()
						cityRegion.isClientRegion = spy.new(function() return false end)

						assert.is_true(testEncounter:isPlayerInNpcCity(pCreatureObject))

						assert.spy(cityRegion.isClientRegion).was.called(1)
					end)

					it("Should return false if the city region belongs to a player city.", function()
						cityRegion.isClientRegion = spy.new(function() return true end)

						assert.is_false(testEncounter:isPlayerInNpcCity(pCreatureObject))

						assert.spy(cityRegion.isClientRegion).was.called(1)
					end)
				end)
			end)
		end)

		describe("createEncounter", function()
			describe("When called with a player", function()
				local realSetSpawnedObjectsToFollow
				local realCreateEncounterEvents

				setup(function()
					realSetSpawnedObjectsToFollow = testEncounter.setSpawnedObjectsToFollow
					realCreateEncounterEvents = testEncounter.createEncounterEvents
				end)

				teardown(function()
					testEncounter.setSpawnedObjectsToFollow = realSetSpawnedObjectsToFollow
					testEncounter.createEncounterEvents = realCreateEncounterEvents
				end)

				before_each(function()
					testEncounter.setSpawnedObjectsToFollow = spy.new(function() end)
					testEncounter.createEncounterEvents = spy.new(function() end)
				end)

				it("Should spawn the encounter objects.", function()
					testEncounter:createEncounter(pCreatureObject)

					assert.spy(SpawnMobilesMocks.spawnMobiles).was.called_with(pCreatureObject, testEncounter.taskName, testEncounter.spawnObjectList)
				end)

				describe("and the objects where spawned", function()
					before_each(function()
						SpawnMobilesMocks.spawnMobiles = spy.new(function() return spawnedObjects end)
					end)

					it("Should set all objects to follow the player.", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.setSpawnedObjectsToFollow).was.called_with(testEncounter, spawnedObjects, pCreatureObject)
					end)

					it("Should create events related to the spawned objects.", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.createEncounterEvents).was.called_with(testEncounter, pCreatureObject, spawnedObjects)
					end)

					it("Should call the onEncounterSpawned function().", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.onEncounterSpawned).was.called_with(testEncounter, pCreatureObject, spawnedObjects)
					end)
				end)

				describe("and no objects where spawned", function()
					it("Should not set all objects to follow the player.", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.setSpawnedObjectsToFollow).was.not_called()
					end)

					it("Should not create events related to the spawned objects.", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.createEncounterEvents).was.not_called()
					end)

					it("Should not call the onEncounterSpawned function().", function()
						testEncounter:createEncounter(pCreatureObject)

						assert.spy(testEncounter.onEncounterSpawned).was.not_called()
					end)
				end)
			end)
		end)

		describe("createEncounterEvents", function()
			describe("When called with a player", function()
				local createEventArgList = {
					{ time = CLOSING_IN_TIME, name = testEncounter.taskName, func = "handleEncounterClosingIn", pSO = pCreatureObject },
					{ time = AT_PLAYER_TIME, name = testEncounter.taskName, func = "handleEncounterAtPlayer", pSO = pCreatureObject }
				}
				local callNumber

				before_each(function()
					callNumber = 1

					createEvent = spy.new(function(time, name, func, pSO)
						assert.same(createEventArgList[callNumber]["time"], time)
						assert.same(createEventArgList[callNumber]["name"], name)
						assert.same(createEventArgList[callNumber]["func"], func)
						assert.same(createEventArgList[callNumber]["pSO"], pSO)
						callNumber = callNumber + 1
					end)
				end)

				it("Should create two events for closing in and at player.", function()
					testEncounter:createEncounterEvents(pCreatureObject)

					assert.spy(createEvent).was.called(2)
				end)
			end)
		end)

		describe("setSpawnedObjectsToFollow", function()
			describe("When called with a player and a list of spawned objects", function()
				before_each(function()
					testEncounter:setSpawnedObjectsToFollow(spawnedObjects, pCreatureObject)
				end)

				it("Should set each object to be not attackable if the spawn object list indicates that the object should be set to not attackable.", function()
					assert.spy(creatureObject1.setPvpStatusBitmask).was.called_with(creatureObject1, 0)
					assert.spy(creatureObject2.setPvpStatusBitmask).was.not_called()
					assert.spy(creatureObject3.setPvpStatusBitmask).was.not_called()
				end)

				it("Should set each object to follow the player if the spawn object list indicates that the object should follow the player.", function()
					assert.spy(aiAgentObject1.setFollowObject).was.called_with(aiAgentObject1, pCreatureObject)
					assert.spy(aiAgentObject2.setFollowObject).was.not_called()
					assert.spy(aiAgentObject3.setFollowObject).was.called_with(aiAgentObject3, pCreatureObject)
				end)
			end)
		end)

		describe("handleEncounterClosingIn", function()
			describe("When called", function()
				before_each(function()
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return spawnedObjects end)
				end)

				it("Should get a list of all spawned mobiles.", function()
					testEncounter:handleEncounterClosingIn(pCreatureObject)

					assert.spy(SpawnMobilesMocks.getSpawnedMobiles).was.called_with(pCreatureObject, testEncounter.taskName)
				end)

				it("Should call the onEncounterClosingIn function.", function()
					testEncounter:handleEncounterClosingIn(pCreatureObject)

					assert.spy(testEncounter.onEncounterClosingIn).was.called_with(testEncounter, pCreatureObject, spawnedObjects)
				end)
			end)
		end)

		describe("handleEncounterAtPlayer", function()
			describe("When called", function()
				local realSetSpawnedObjectsToFollow

				setup(function()
					realSetSpawnedObjectsToFollow = testEncounter.setSpawnedObjectsToFollow
				end)

				teardown(function()
					testEncounter.setSpawnedObjectsToFollow = realSetSpawnedObjectsToFollow
				end)

				before_each(function()
					testEncounter.setSpawnedObjectsToFollow = spy.new(function() end)
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return spawnedObjects end)
				end)

				it("Should get a list of all spawned mobiles.", function()
					testEncounter:handleEncounterAtPlayer(pCreatureObject)

					assert.spy(SpawnMobilesMocks.getSpawnedMobiles).was.called_with(pCreatureObject, testEncounter.taskName)
				end)

				it("Should set all spawned mobiles to stop following the player.", function()
					testEncounter:handleEncounterAtPlayer(pCreatureObject)

					assert.spy(testEncounter.setSpawnedObjectsToFollow).was.called_with(testEncounter, spawnedObjects, nil)
				end)

				it("Should call the onEncounterAtPlayer function.", function()
					testEncounter:handleEncounterAtPlayer(pCreatureObject)

					assert.spy(testEncounter.onEncounterAtPlayer).was.called_with(testEncounter, pCreatureObject, spawnedObjects)
				end)
			end)
		end)
	end)
end)
