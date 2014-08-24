local DirectorManagerMocks = require("screenplays.mocks.director_manager_mocks")
local QuestManager = require("managers.quest.quest_manager")

local TEST_QUEST = 33
local QUEST_ACTIVE = 1
local QUEST_COMPLETED = 1

describe("Quest Manager", function()
	local pCreatureObject = { "creatureObjectPointer" }
	local pPlayerObject = { "playerObjectPointer" }
	local creatureObject
	local playerObject

	setup(function()
		DirectorManagerMocks.mocks.setup()
	end)

	teardown(function()
		DirectorManagerMocks.mocks.teardown()
	end)

	before_each(function()
		DirectorManagerMocks.mocks.before_each()

		creatureObject = {}
		creatureObject.getPlayerObject = spy.new(function() return pPlayerObject end)
		DirectorManagerMocks.creatureObjects[pCreatureObject] = creatureObject

		playerObject = {}
		playerObject.setActiveQuestsBit = spy.new(function() end)
		playerObject.clearActiveQuestsBit = spy.new(function() end)
		playerObject.hasActiveQuestBitSet = spy.new(function() return false end)
		playerObject.hasCompletedQuestsBitSet = spy.new(function() return false end)
		playerObject.setCompletedQuestsBit = spy.new(function() end)
		playerObject.clearCompletedQuestsBit = spy.new(function() end)
		DirectorManagerMocks.playerObjects[pPlayerObject] = playerObject
	end)

	describe("Interface functions", function()
		describe("activateQuest", function()
			describe("When called with a player", function()
				it("Should activate the quest.", function()
					QuestManager.activateQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.setActiveQuestsBit).was.called_with(playerObject, TEST_QUEST, QUEST_ACTIVE)
				end)
			end)
		end)

		describe("completeQuest", function()
			describe("When called with a player", function()
				it("Should deactivate the quest.", function()
					QuestManager.completeQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.clearActiveQuestsBit).was.called_with(playerObject, TEST_QUEST)
				end)

				it("Should complete the quest.", function()
					QuestManager.completeQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.setCompletedQuestsBit).was.called_with(playerObject, TEST_QUEST, QUEST_COMPLETED)
				end)
			end)
		end)

		describe("resetQuest", function()
			describe("When called with a player", function()
				it("Should deactivate the quest.", function()
					QuestManager.resetQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.clearActiveQuestsBit).was.called_with(playerObject, TEST_QUEST)
				end)

				it("Should uncomplete the quest.", function()
					QuestManager.resetQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.clearCompletedQuestsBit).was.called_with(playerObject, TEST_QUEST)
				end)
			end)
		end)

		describe("hasActiveQuest", function()
			describe("When called with a player", function()
				it("Should call hasActiveQuestBitSet.", function()
					QuestManager.hasActiveQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.hasActiveQuestBitSet).was.called_with(playerObject, TEST_QUEST)
				end)

				describe("and hasActiveQuestBitSet returns true", function()
					it("Should return true.", function()
						playerObject.hasActiveQuestBitSet = spy.new(function() return true end)

						assert.is_true(QuestManager.hasActiveQuest(pCreatureObject, TEST_QUEST))
					end)
				end)

				describe("and hasActiveQuestBitSet returns false", function()
					it("Should return true.", function()
						assert.is_false(QuestManager.hasActiveQuest(pCreatureObject, TEST_QUEST))
					end)
				end)
			end)
		end)

		describe("hasCompletedQuest", function()
			describe("When called with a player", function()
				it("Should call hasCompletedQuestsBitSet.", function()
					QuestManager.hasCompletedQuest(pCreatureObject, TEST_QUEST)

					assert.spy(playerObject.hasCompletedQuestsBitSet).was.called_with(playerObject, TEST_QUEST)
				end)

				describe("and hasCompletedQuestsBitSet returns true", function()
					it("Should return true.", function()
						playerObject.hasCompletedQuestsBitSet = spy.new(function() return true end)

						assert.is_true(QuestManager.hasCompletedQuest(pCreatureObject, TEST_QUEST))
					end)
				end)

				describe("and hasCompletedQuestsBitSet returns false", function()
					it("Should return true.", function()
						assert.is_false(QuestManager.hasCompletedQuest(pCreatureObject, TEST_QUEST))
					end)
				end)
			end)
		end)
	end)
end)
