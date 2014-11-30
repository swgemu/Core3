local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToTheater = require("quest.tasks.go_to_theater")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")

local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"
local THEATER_SUM_STRING = "@quest/force_sensitive/intro:theater_sum"

local WAYPOINT_ID_STRING = "waypointId"
local ACTIVE_AREA_ID_STRING = "activeAreaId"
local THEATER_ID_STRING = "theaterId"

local testGoToTheater = GoToTheater:new {
	taskName = "testGoToTheater",
	minimumDistance = 768,
	maximumDistance = 1280,
	theater = "theater",
	waypointDescription = "waypointDescription",
	mobileList = { "mobileList" },
	despawnTime = 10,
	activeAreaRadius = 20,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil
}

describe("GoToTheater", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local positionX = 1234
	local positionY = 5678
	local minDistance = 768
	local maxDistance = 1280
	local creatureObject
	local spawnAreaPosition = {1, 2, 3}
	local zoneName = "testZone"
	local pSpawnedMobile = { "spawnedMobilePointer" }
	local spawnedMobilesList = { pSpawnedMobile }
	local playerObjectId = 12345678
	local theaterObjectId = 45678901
	local theaterObject
	local pTheater = { "theaterObjectPointer" }
	local pActiveArea = { "activeAreaPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local playerObject
	local waypointId = 1234
	local activeArea
	local activeAreaId = 34567890
	local pSpawnedMobile1 = { "spawnedMobilePointer1" }
	local pSpawnedMobile2 = { "spawnedMobilePointer2" }
	local spawnedMobiles = { pSpawnedMobile1, pSpawnedMobile2 }

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

		testGoToTheater.onFailedSpawn = spy.new(function() end)
		testGoToTheater.onSuccessfulSpawn = spy.new(function() end)
		testGoToTheater.onEnteredActiveArea = spy.new(function() end)

		creatureObject = {}
		creatureObject.getObjectID = spy.new(function() return playerObjectId end)
		creatureObject.getZoneName = spy.new(function() return zoneName end)
		creatureObject.setScreenPlayState = spy.new(function() end)
		creatureObject.getScreenPlayState = spy.new(function() return 0 end)
		creatureObject.getWorldPositionX = spy.new(function() return positionX end)
		creatureObject.getWorldPositionY = spy.new(function() return positionY end)
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		creatureObject.sendSystemMessage = spy.new(function() end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.addWaypoint = spy.new(function() return waypointId end)
		playerObject.removeWaypoint = spy.new(function() end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject

		theaterObject = {}
		theaterObject.getObjectID = spy.new(function() return theaterObjectId end)
		theaterObject.destroyObjectFromWorld = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pTheater] = theaterObject

		activeArea = {}
		activeArea.getObjectID = spy.new(function() return activeAreaId end)
		activeArea.destroyObjectFromWorld = spy.new(function() end)
		activeArea.setRadius = spy.new(function() end)
		DirectorManagerMocks.sceneObjects[pActiveArea] = activeArea
		DirectorManagerMocks.activeAreas[pActiveArea] = activeArea

	end)

	describe("start", function()
		local realFinish

		setup(function()
			realFinish = testGoToTheater.finish
		end)

		teardown(function()
			testGoToTheater.finish = realFinish
		end)

		before_each(function()
			testGoToTheater.finish = spy.new(function() end)
		end)

		describe("When called with a player", function()
			it("Should find a spawn point for the theater.", function()
				testGoToTheater:start(pCreatureObject)

				assert.spy(getSpawnArea).was.called_with(pCreatureObject, positionX, positionY, minDistance, maxDistance, 10, 5)
			end)

			describe("and a spawn area was found", function()
				before_each(function()
					getSpawnArea = spy.new(function() return spawnAreaPosition end)
					spawnSceneObject = spy.new(function(zn, script, x, z, y, parentId, heading)
						assert.same(zoneName, zn)
						assert.same(testGoToTheater.theater, script)
						assert.same(spawnAreaPosition[1], x)
						assert.same(spawnAreaPosition[2], z)
						assert.same(spawnAreaPosition[3], y)
						assert.same(0, parentId)
					end)
				end)

				it("Should spawn the theater at the spawn point.", function()
					testGoToTheater:start(pCreatureObject)

					assert.spy(spawnSceneObject).was.called(1)
				end)

				describe("and the theater was spawned", function()
					before_each(function()
						spawnSceneObject = spy.new(function() return pTheater end)
					end)

					it("Should save the object id of the theater on the player.", function()
						testGoToTheater:start(pCreatureObject)

						assert.spy(writeData).was.called_with(playerObjectId .. testGoToTheater.taskName .. THEATER_ID_STRING, theaterObjectId)
					end)

					it("Should spawn the mobiles at the theater.", function()
						testGoToTheater:start(pCreatureObject)

						assert.spy(SpawnMobilesMocks.spawnMobiles).was.called_with(pTheater, testGoToTheater.taskName, testGoToTheater.mobileList, true)
					end)

					describe("and the mobiles was spawned", function()
						local spawnSceneObjectTimes

						before_each(function()
							spawnSceneObjectTimes = 0

							SpawnMobilesMocks.spawnMobiles = spy.new(function() return spawnedMobilesList end)

							spawnSceneObject = spy.new(function()
								spawnSceneObjectTimes = spawnSceneObjectTimes + 1
								if spawnSceneObjectTimes == 1 then
									return pTheater
								else
									return pActiveArea
								end
							end)
						end)

						it("Should setup and active area at the spawn point.", function()
							testGoToTheater:start(pCreatureObject)

							assert.spy(spawnSceneObject).was.called_with(zoneName, "object/active_area.iff", spawnAreaPosition[1], 0, spawnAreaPosition[3], 0, 0)
						end)

						describe("and the active area was spawned", function()
							local writeDataTimes

							before_each(function()
								writeDataTimes = 0

								writeData = spy.new(function(string, value)
									writeDataTimes = writeDataTimes + 1
									if writeDataTimes == 2 then
										assert.same(playerObjectId .. testGoToTheater.taskName .. ACTIVE_AREA_ID_STRING, string)
										assert.same(activeAreaId, value)
									end
									if writeDataTimes == 3 then
										assert.same(playerObjectId .. testGoToTheater.taskName .. WAYPOINT_ID_STRING, string)
										assert.same(waypointId, value)
									end
								end)
							end)

							it("Should set the radius of the active area.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(activeArea.setRadius).was.called_with(activeArea, testGoToTheater.activeAreaRadius)
							end)

							it("Should create an observer for entering the active area.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(createObserver).was.called_with(ENTEREDAREA, testGoToTheater.taskName, "handleEnteredAreaEvent", pActiveArea)
							end)

							it("Should save the id of the active area on the player.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(writeData).was.called(3)
							end)

							it("Should generate an active waypoint for the player to the theater.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(playerObject.addWaypoint).was.called_with(playerObject, zoneName, testGoToTheater.waypointDescription, "", spawnAreaPosition[1], spawnAreaPosition[3], WAYPOINTWHITE, true, true, 0)
							end)

							it("Should store the id of the waypoint on the player", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(writeData).was.called(3)
							end)

							it("Should schedule the despawn event.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(createEvent).was.called_with(testGoToTheater.despawnTime, "handleDespawnTheater", testGoToTheater.taskName, pCreatureObject)
							end)

							it("Should call the onSuccessfulSpawn function.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(testGoToTheater.onSuccessfulSpawn).was.called_with(testGoToTheater, pCreatureObject, spawnedMobilesList)
							end)

							it("Should not finish the task.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(testGoToTheater.finish).was.not_called()
							end)
						end)

						describe("and the active area was not spawned", function()
							local spawnSceneObjectTimes = 0

							before_each(function()
								spawnSceneObject = spy.new(function()
									spawnSceneObjectTimes = spawnSceneObjectTimes + 1
									if spawnSceneObjectTimes == 1 then
										return pTheater
									else
										return nil
									end
								end)
							end)

							it("Should call the onFailedSpawn function.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(testGoToTheater.onFailedSpawn).was.called_with(testGoToTheater, pCreatureObject)
							end)

							it("Should finish the task.", function()
								testGoToTheater:start(pCreatureObject)

								assert.spy(testGoToTheater.finish).was.called_with(testGoToTheater, pCreatureObject)
							end)
						end)
					end)

					describe("and the mobiles was not spawned", function()
						before_each(function()
							SpawnMobilesMocks.spawnMobiles = spy.new(function() return nil end)
						end)

						it("Should call the onFailedSpawn function.", function()
							testGoToTheater:start(pCreatureObject)

							assert.spy(testGoToTheater.onFailedSpawn).was.called_with(testGoToTheater, pCreatureObject)
						end)

						it("Should finish the task.", function()
							testGoToTheater:start(pCreatureObject)

							assert.spy(testGoToTheater.finish).was.called_with(testGoToTheater, pCreatureObject)
						end)
					end)
				end)

				describe("and the theater was not spawned", function()
					before_each(function()
						spawnSceneObject = spy.new(function() return nil end)
					end)

					it("Should call the onFailedSpawn function.", function()
						testGoToTheater:start(pCreatureObject)

						assert.spy(testGoToTheater.onFailedSpawn).was.called_with(testGoToTheater, pCreatureObject)
					end)

					it("Should finish the task.", function()
						testGoToTheater:start(pCreatureObject)

						assert.spy(testGoToTheater.finish).was.called_with(testGoToTheater, pCreatureObject)
					end)
				end)
			end)

			describe("and no spawn area was found", function()
				it("Should call the onFailedSpawn function.", function()
					testGoToTheater:start(pCreatureObject)

					assert.spy(testGoToTheater.onFailedSpawn).was.called_with(testGoToTheater, pCreatureObject)
				end)

				it("Should finish the task.", function()
					testGoToTheater:start(pCreatureObject)

					assert.spy(testGoToTheater.finish).was.called_with(testGoToTheater, pCreatureObject)
				end)
			end)
		end)
	end)

	describe("taskFinish", function()
		describe("When called with a pointer to a creature object", function()
			before_each(function()
				readData = spy.new(function(key)
					if key == playerObjectId .. testGoToTheater.taskName .. WAYPOINT_ID_STRING then
						return waypointId
					end
					if key == playerObjectId .. testGoToTheater.taskName .. ACTIVE_AREA_ID_STRING then
						return activeAreaId
					end
					if key == playerObjectId .. testGoToTheater.taskName .. THEATER_ID_STRING then
						return theaterObjectId
					end
				end)

				getSceneObject = spy.new(function(id)
					if id == activeAreaId then
						return pActiveArea
					end
					if id == theaterObjectId then
						return pTheater
					end
				end)
			end)

			it("Should read the waypoint id from the player.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(readData).was.called(3)
			end)

			it("Should remove the waypoint from the player.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(playerObject.removeWaypoint).was.called_with(playerObject, waypointId, true)
			end)

			it("Should read the active area id from the player.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(readData).was.called(3)
			end)

			it("Should get the active area pointer with the read id.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(getSceneObject).was.called(2)
			end)

			describe("and a pointer to an object was returned", function()
				it("Should remove the active area from the world.", function()
					testGoToTheater:taskFinish(pCreatureObject)

					assert.spy(activeArea.destroyObjectFromWorld).was.called_with(activeArea)
				end)
			end)

			describe("and a pointer to an object was not returned", function()
				before_each(function()
					getSceneObject = spy.new(function() return nil end)
				end)

				it("Should not remove the active area from the world.", function()
					testGoToTheater:taskFinish(pCreatureObject)

					assert.spy(activeArea.destroyObjectFromWorld).was.not_called()
				end)
			end)

			it("Should despawn the mobiles.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(SpawnMobilesMocks.despawnMobiles).was.called_with(pTheater, testGoToTheater.taskName)
			end)

			it("Should read the theater id from the player.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(readData).was.called(3)
			end)

			it("Should get the theater pointer with the read id.", function()
				testGoToTheater:taskFinish(pCreatureObject)

				assert.spy(getSceneObject).was.called(2)
			end)

			describe("and a pointer to an object was returned", function()
				it("Should remove the theater from the world.", function()
					testGoToTheater:taskFinish(pCreatureObject)

					assert.spy(theaterObject.destroyObjectFromWorld).was.called_with(theaterObject)
				end)
			end)

			describe("and a pointer to an object was not returned", function()
				before_each(function()
					getSceneObject = spy.new(function() return nil end)
				end)

				it("Should not remove the theater from the world.", function()
					testGoToTheater:taskFinish(pCreatureObject)

					assert.spy(theaterObject.destroyObjectFromWorld).was.not_called()
				end)
			end)
		end)
	end)

	describe("handleDespawnTheater", function()
		describe("When called with a player object", function()
			local realFinish

			setup(function()
				realFinish = testGoToTheater.finish
			end)

			teardown(function()
				testGoToTheater.finish = realFinish
			end)

			before_each(function()
				testGoToTheater.finish = spy.new(function() end)
			end)

			it("Should call finish.", function()
				testGoToTheater:handleDespawnTheater(pCreatureObject)

				assert.spy(testGoToTheater.finish).was.called_with(testGoToTheater, pCreatureObject)
			end)
		end)
	end)

	describe("handleEnteredAreaEvent", function()
		describe("When called with an active area and a pointer to the player", function()
			it("Should check if the theater is for the player", function()
				testGoToTheater:handleEnteredAreaEvent(pActiveArea, pCreatureObject, 0)

				assert.spy(readData).was.called_with(playerObjectId .. testGoToTheater.taskName .. ACTIVE_AREA_ID_STRING)
			end)

			describe("and the theater is for the player", function()
				before_each(function()
					readData = spy.new(function() return activeAreaId end)
					SpawnMobilesMocks.getSpawnedMobiles = spy.new(function() return spawnedMobiles end)
				end)

				it("Should call the onEnteredActiveArea function.", function()
					testGoToTheater:handleEnteredAreaEvent(pActiveArea, pCreatureObject, 0)

					assert.spy(testGoToTheater.onEnteredActiveArea).was.called_with(testGoToTheater, pCreatureObject, spawnedMobiles)
				end)
			end)

			describe("and the theater isn't for the player", function()
				it("Should not call the onEnteredActiveArea function.", function()
					testGoToTheater:handleEnteredAreaEvent(pActiveArea, pCreatureObject, 0)

					assert.spy(testGoToTheater.onEnteredActiveArea).was.not_called()
				end)
			end)
		end)
	end)
end)
