local ObjectManager = require("managers.object.object_manager")

SpaceAssassinateScreenplay = SpaceQuestLogic:new {
	className = "SpaceAssassinateScreenplay",
}

function SpaceAssassinateScreenplay:startQuest(pPlayer)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end


end