local ObjectManager = require("managers.object.object_manager")

SpaceSurpriseAttackScreenplay = SpaceQuestLogic:new {
	className = "SpaceSurpriseAttackScreenplay",
}

function SpaceSurpriseAttackScreenplay:startQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end


end