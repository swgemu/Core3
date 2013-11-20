local QuestManager = require("managers.quest.quest_manager")

local realActivateQuest
local realCompleteQuest
local realHasActiveQuest
local realHasCompletedQuest
local realResetQuest

local QuestManagerMocks = QuestManager
QuestManagerMocks.mocks = {}

function QuestManagerMocks.mocks.setup()
	realActivateQuest = QuestManager.activateQuest
	realCompleteQuest = QuestManager.completeQuest
	realHasActiveQuest = QuestManager.hasActiveQuest
	realHasCompletedQuest = QuestManager.hasCompletedQuest
	realResetQuest = QuestManager.resetQuest
end

function QuestManagerMocks.mocks.teardown()
	QuestManager.activateQuest = realActivateQuest
	QuestManager.completeQuest = realCompleteQuest
	QuestManager.hasActiveQuest = realHasActiveQuest
	QuestManager.hasCompletedQuest = realHasCompletedQuest
	QuestManager.resetQuest = realResetQuest
end

function QuestManagerMocks.mocks.before_each()
	QuestManager.activateQuest = spy.new(function() end)
	QuestManager.completeQuest = spy.new(function() end)
	QuestManager.hasActiveQuest = spy.new(function() return false end)
	QuestManager.hasCompletedQuest = spy.new(function() return false end)
	QuestManager.resetQuest = spy.new(function() end)
end

function QuestManagerMocks.mocks.after_each()
end

return QuestManagerMocks
