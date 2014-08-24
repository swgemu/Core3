local DathomirGoTo = require("managers.jedi.village.dathomir_go_to")
local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local QuestManagerMocks = require("managers.quest.mocks.quest_manager_mocks")

describe("DathomirGoTo", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local creatureObject
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
		creatureObject.getObjectID = spy.new(function() return playerObjectId end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject
	end)

	describe("onEnteredActiveArea", function()
		describe("When a player enters the active area", function()
			it("Task should complete with the quest.", function()
				DathomirGoTo:onEnteredActiveArea(pCreatureObject)
				assert.spy(QuestManagerMocks.completeQuest).was.called_with(pCreatureObject, QuestManagerMocks.quests.FS_VILLAGE_ELDER)
			end)
		end)
	end)
end)
