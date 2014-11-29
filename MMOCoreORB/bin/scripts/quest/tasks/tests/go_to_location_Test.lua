local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToLocation = require("quest.tasks.go_to_location")

local READ_DISK_ERROR_STRING = "@quest/force_sensitive/intro:read_disk_error"
local THEATER_SUM_STRING = "@quest/force_sensitive/intro:theater_sum"

local WAYPOINT_ID_STRING = "waypointId"
local ACTIVE_AREA_ID_STRING = "activeAreaId"
local THEATER_ID_STRING = "theaterId"

local ACTIVE_AREA_IFF = "object/active_area.iff"

local testGoToLocation = GoToLocation:new {
    -- Task properties
    taskName = "testGoToLocation",
    -- GoToLocation properties
    waypointDescription = "waypointDescription",
    spawnPoint = { 20, 20, 20 },
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
    local spawnPoint = { 1, 2, 3 }
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
    end)

    teardown(function()
        DirectorManagerMocks.mocks.teardown()
    end)

    before_each(function()
        DirectorManagerMocks.mocks.before_each()

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
        describe("When called with a player", function()
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

            it("Should setup an active area at the target location.", function()
                testGoToLocation:start(pCreatureObject)

                assert.spy(spawnSceneObject).was.called_with(testGoToLocation.spawnPlanet, ACTIVE_AREA_IFF, testGoToLocation.spawnPoint.x, 0, testGoToLocation.spawnPoint.y, 0, 0)
            end)

            describe("and the active area was successfully created", function()
                before_each(function()
                    spawnSceneObject = spy.new(function() return pActiveArea end)
                end)

                it("Should save the active area id on the player.", function()
                    testGoToLocation:start(pCreatureObject)

                    assert.spy(writeData).was.called_with(creatureObject:getObjectID() .. testGoToLocation.taskName .. ACTIVE_AREA_ID_STRING, activeAreaId)
                end)

                it("Should set the radius of the active area.", function()
                    testGoToLocation:start(pCreatureObject)

                    assert.spy(activeArea.setRadius).was.called_with(activeArea, testGoToLocation.spawnRadius)
                end)

                it("Should create an observer for the onEntered event on the active area.", function()
                    testGoToLocation:start(pCreatureObject)

                    assert.spy(createObserver).was.called_with(ENTEREDAREA, testGoToLocation.taskName, "handleEnteredAreaEvent", pActiveArea)
                end)

                it("Should create a waypoint to the location", function()
                    testGoToLocation:start(pCreatureObject)

                    assert.spy(playerObject.addWaypoint).was.called_with(playerObject, testGoToLocation.spawnPlanet, testGoToLocation.waypointDescription, "", testGoToLocation.spawnPoint.x, testGoToLocation.spawnPoint.y, WAYPOINTORANGE, true, true, 0)
                end)

                describe("and the waypoint was successfully created", function()
                    it("Should store the waypoint id on the player.", function()
                        testGoToLocation:start(pCreatureObject)

                        assert.spy(writeData).was.called_with(creatureObject:getObjectID() .. testGoToLocation.taskName .. WAYPOINT_ID_STRING, waypointId)
                    end)

                    it("Should call the onSuccessfulSpawn method.", function()
                        testGoToLocation:start(pCreatureObject)

                        assert.spy(testGoToLocation.onSuccessfulSpawn).was.called_with(testGoToLocation, pCreatureObject, pActiveArea)
                    end)
                end)

                describe("and the waypoint could not be created", function()
                    before_each(function()
                        playerObject.addWaypoint = spy.new(function() return nil end)
                    end)

                    it("Should finish the task to clean up.", function()
                        testGoToLocation:start(pCreatureObject)

                        assert.spy(testGoToLocation.finish).was.called_with(testGoToLocation, pCreatureObject)
                    end)
                end)
            end)

            describe("and an active area could not be created", function()
                before_each(function()
                    spawnSceneObject = spy.new(function() return nil end)
                end)

                it("Should finish the task to clean up.", function()
                    testGoToLocation:start(pCreatureObject)

                    assert.spy(testGoToLocation.finish).was.called_with(testGoToLocation, pCreatureObject)
                end)
            end)
        end)
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

            it("Should read the waypoint id from the player.", function()
                testGoToLocation:taskFinish(pCreatureObject)

                assert.spy(readData).was.called(2)
            end)

            it("Should remove the waypoint from the player.", function()
                testGoToLocation:taskFinish(pCreatureObject)

                assert.spy(playerObject.removeWaypoint).was.called_with(playerObject, waypointId, true)
            end)

            it("Should read the active area id from the player.", function()
                testGoToLocation:taskFinish(pCreatureObject)

                assert.spy(readData).was.called(2)
            end)

            it("Should get the active area pointer with the read id.", function()
                testGoToLocation:taskFinish(pCreatureObject)

                assert.spy(getSceneObject).was.called(1)
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
