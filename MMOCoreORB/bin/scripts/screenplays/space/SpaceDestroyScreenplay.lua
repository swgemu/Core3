local ObjectManager = require("managers.object.object_manager")

SpaceDestroyScreenplay = SpaceQuestLogic:new {
	className = "SpaceDestroyScreenplay",
}

function SpaceDestroyScreenplay:startQuest(pPlayer, pNpc)
	if (pPlayer == nil) then
		Logger:log("Quest: " .. self.questName .. " Type: " .. self.QuestType .. " -- Failed to startQuest due to pPlayer being nil.", LT_ERROR)
		return
	end

	SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, self.questType, self.QuestName, 1)

	-- Write players quest step status
	--setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":CorsecSquadron", CorsecSquadronScreenplay.ACCEPTED_MISSION_2)

	-- Create inital observer for player entering Corellia Space
	if (not hasObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer)) then
		createObserver(ZONESWITCHED, self.className, "enteredZone", pPlayer, 1)
	end
end

function SpaceDestroyScreenplay:enteredZone(pPlayer, nill, zoneNameHash)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nullptr) then
		return 0
	end

	local pRootParent = SceneObject(pPlayer):getRootParent()

	if (pRootParent ~= nil and SceneObject(pRootParent):getObjectName() == "player_sorosuub_space_yacht") then
		return 0
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local currentStep = getQuestStatus(playerID .. ":" .. self.questScreenplay)
	local spaceCorelliaHash = getHashCode(self.patrolZone)

	if (currentStep == nil) then
		currentStep = 0
	else
		currentStep = tonumber(currentStep)
	end

	if (self.DEBUG_SPACE_PATROL) then
		print(self.questScreenplay .. ":enteredZone called -- Current Quest Step: " .. currentStep .. " Zone Hash: " .. zoneNameHash .. " space_corellia: " .. spaceCorelliaHash)
	end








end