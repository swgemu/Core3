local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToLocation = require("quest.tasks.go_to_location")
local SpawnMobilesMocks = require("utils.mocks.spawn_mobiles_mocks")

local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"
local THEATER_SUM_STRING = "@quest/force_sensitive/intro:theater_sum"

local WAYPOINT_ID_STRING = "waypointId"
local ACTIVE_AREA_ID_STRING = "activeAreaId"
local THEATER_ID_STRING = "theaterId"

local testGoToLocation = GoToLocation:new {
	taskName = "testGoToLocation",
	waypointDescription = "waypointDescription",
	spawnPoint = { 20,20,20 },
	spawnPlanet = "testZone",
	spawnRadius = 20,
	onFailedSpawn = nil,
	onSuccessfulSpawn = nil,
	onEnteredActiveArea = nil,
}

describe("GoToLocation", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local creatureObject
	local spawnPlanet = "testZone"
	local spawnPoint = { 1,2,3 }
	local playerObjectId = 12345678
	local theaterObjectId = 45678901
	local theaterObject
	local pActiveArea = { "activeAreaPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local playerObject
	local waypointId = 1234
	local activeArea
	local activeAreaId = 34567890

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

		testGoToLocation.onFailedSpawn = spy.new(function() end)
		testGoToLocation.onSuccessfulSpawn = spy.new(function() end)
		testGoToLocation.onEnteredActiveArea = spy.new(function() end)

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
			realFinish = testGoToLocation.finish
		end)

		teardown(function()
			testGoToLocation.finish = realFinish
		end)

		before_each(function()
			testGoToLocation.finish = spy.new(function() end)
		end)

	describe("taskFinish", function()
		describe("When called with a pointer to a creature object", function()
			before_each(function()
				readData = spy.new(function(key)
					if key == playerObjectId .. testGoToLocation.taskName .. WAYPOINT_ID_STRING then
						return waypointId
					end
					if key == playerObjectId .. testGoToLocation.taskName .. ACTIVE_AREA_ID_STRING then
						return activeAreaId
					end
					if key == playerObjectId .. testGoToLocation.taskName .. THEATER_ID_STRING then
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

			it("Should remove the waypoint from the player.", function()
				testGoToLocation:taskFinish(pCreatureObject)

				assert.spy(playerObject.removeWaypoint).was.called_with(playerObject, waypointId, true)
			end)

			describe("and a pointer to an object was returned", function()
				it("Should remove the active area from the world.", function()
					testGoToLocation:taskFinish(pCreatureObject)

					assert.spy(activeArea.destroyObjectFromWorld).was.called_with(activeArea)
				end)
			end)

			describe("and a pointer to an object was not returned", function()
				before_each(function()
					getSceneObject = spy.new(function() return nil end)
				end)

				it("Should not remove the active area from the world.", function()
					testGoToLocation:taskFinish(pCreatureObject)

					assert.spy(activeArea.destroyObjectFromWorld).was.not_called()
				end)
			end)
		end)
	end)
	end)
end)