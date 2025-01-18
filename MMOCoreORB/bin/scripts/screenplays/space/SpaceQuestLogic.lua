require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

SpaceQuestLogic = ScreenPlay:new {
	className = "SpaceQuestLogic",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,

	sideQuest = false,
	sideQuestType = "",
	sideQuestStart = 0, -- Patrol Point Number
	sideQuestDelay = 0, -- Time in seconds to wait to trigger side quest

	parentQuest = "",
	parentQuestType = "", -- Quest type of parent quest, used for completing tasks
}

registerScreenPlay("SpaceQuestLogic", false)

function SpaceQuestLogic:start()
end

function SpaceQuestLogic:rewardPlayer(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	if (self.creditReward <= 0) then
		return
	end

	-- Quest Reward Message
	SpaceHelpers:sendQuestReward(pPlayer, "@spacequest/" ..self.questType .. "/" .. self.questName .. ":title")

	-- Give player reward credits
	SpaceHelpers:spaceCreditReward(pPlayer, self.creditReward)
end