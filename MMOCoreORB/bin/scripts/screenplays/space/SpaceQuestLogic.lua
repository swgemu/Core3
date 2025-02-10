require("screenplays.screenplay")
local ObjectManager = require("managers.object.object_manager")

SpaceQuestLogic = ScreenPlay:new {
	className = "SpaceQuestLogic",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

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

	-- Quest Reward Message
	SpaceHelpers:sendQuestReward(pPlayer, "@spacequest/" ..self.questType .. "/" .. self.questName .. ":title")

	if (self.creditReward > 0) then
		-- Give player reward credits
		SpaceHelpers:spaceCreditReward(pPlayer, self.creditReward)
	end

	local rewardOptions = self.itemReward
	local playerSpecies = CreatureObject(pPlayer):getSpecies()
	local rewardString = ""

	for i = 1, #rewardOptions, 1 do
		local itemTable = rewardOptions[i]

		for j = 1, #itemTable.species, 1 do
			local speciesIdentifier = itemTable.species[j]

			if (rewardString == "" and speciesIdentifier == playerSpecies or speciesIdentifier == -1) then
				rewardString = itemTable.item

				break
			end
		end
	end

	if (rewardString == "") then
		return
	end

	-- Give player reward item
	SpaceHelpers:spaceItemReward(pPlayer, rewardString)
end

--[[

	Basic Quest Logic Functions

]]

function SpaceQuestLogic:startQuest(pPlayer, pNpc)

end

function SpaceQuestLogic:completeQuest(pPlayer, notifyClient)

end

function SpaceQuestLogic:failQuest(pPlayer, notifyClient)

end