local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local GoToDathomir = require("managers.jedi.village.go_to_dathomir")
local QuestManagerMocks = require("managers.quest.mocks.quest_manager_mocks")

describe("GoToDathomir", function()
    local pCreatureObject = { "creatureObjectPointer" }
    local pPlayerObject = { "playerObjectPointer" }
    local creatureObject
    local playerObject
    local playerObjectId = 12345678
    local activeAreaObjectId = 45678901

    setup(function()
        DirectorManagerMocks.mocks.setup()
        QuestManagerMocks.mocks.setup()
    end)

    teardown(function()
        DirectorManagerMocks.mocks.teardown()
        QuestManagerMocks.mocks.teardown()
    end)

    before_each(function()
        DirectorManagerMocks.mocks.before_each()
        QuestManagerMocks.mocks.before_each()

        creatureObject = {}
        creatureObject.getScreenPlayState = spy.new(function() return 0 end)
        creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
        creatureObject.getObjectID = spy.new(function() return playerObjectId end)
        DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

        playerObject = {}
        playerObject.removeWaypoint = spy.new(function() end)
        DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
    end)

    describe("onSuccessfulSpawn", function()
    	describe("When the task is started with a player as argument", function()
    		it("Should activate the village elder quest.", function()
                GoToDathomir:onSuccessfulSpawn(pCreatureObject)

                assert.spy(QuestManagerMocks.activateQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_VILLAGE_ELDER)
    		end)
    	end)
    end)

    describe("onEnteredActiveArea", function()
        describe("When a player enters the active area", function()
            it("Task should complete with the quest.", function()
                GoToDathomir:onEnteredActiveArea(pCreatureObject)

                assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_VILLAGE_ELDER)
            end)
        end)
    end)
end)
