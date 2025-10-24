require("screenplays.screenplay")

SpaceQuestLogic = ScreenPlay:new {
	className = "SpaceQuestLogic",

	questName = "",
	questType = "",

	questZone = "",

	creditReward = 0,
	itemReward = {
		--{species = {}, item = ""},
	},

	-- Side Quest Split Flag
	SIDE_QUEST_SPLIT_TYPES = {
		NONE = 0,
		COMPLETION = 1,
		FAILURE = 2,
		BIDIRECTIONAL = 3,
		PATROL_POINT = 4,
	},

	-- Flags used to tie side quest to parent quest
	parentQuest = "",
	parentQuestType = "",
	parentQuestName = "",

	-- Side Quest Bool
	sideQuest = false,
	-- Side Quest Type String
	sideQuestType = "",
	-- Side Quest Name String
	sideQuestName = "",
	-- Side Quest Split Type
	sideQuestSplitType = 0,
	-- Delay in seconds to trigger side quest when triggered
	sideQuestDelay = 2, -- Time in seconds to wait to trigger side quest

	-- Fail Side Quest Type String
	sideFailQuestType = "",
	-- Fail Side Quest Name String
	sideFailQuestName = "",

	-- Patrol point to start side quest for PATROL_POINT split type
	sideQuestPatrolStart = 0,
}

registerScreenPlay("SpaceQuestLogic", false)

function SpaceQuestLogic:start()
end

function SpaceQuestLogic:rewardPlayer(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.questType .. " -- Failed to completeQuest due to pPlayer being nil.", LT_ERROR)
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