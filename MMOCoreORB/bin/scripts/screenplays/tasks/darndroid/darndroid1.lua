DarnDroid1 = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DarnDroid1",

	questCrc = 3408891851, --CRC of "quest/c_darndroid1"
	imperialCrc = 3679112276, --CRC of "imperial"

	--Task Constants
	TASK_GOTOMOENIA = 1, --Go to Moenia Starport
	TASK_TALKTOSELAN = 2, --Talk to Selan Ellison
	TASK_TALKTOAMARENT = 3, --Speak to Amarent Loren
	TASK_FINDSHIP = 4, --Find the crashed ship.
	TASK_TALKTOVALANCE = 5, --Talk to Valance Serth
	TASK_BRIBEDAMARENT = 9, --Bribed Amarent Loren
	TASK_INTIMIDATEDAMARENT = 11, --Intimidated Amarent Loren
}
registerScreenPlay("DarnDroid1", true)

function DarnDroid1:start()
	self:spawnAreaObjects()
	self:spawnMobiles()
end

function DarnDroid1:spawnAreaObjects()
	if (isZoneEnabled("naboo")) then
		local pMoeniaArea = spawnActiveArea("naboo", "object/active_area.iff", 4796, 20, -4696, 20, 0)

		if (pMoeniaArea ~= nil) then
			createObserver(ENTEREDAREA, "DarnDroid1", "notifyEnteredMoeniaStarportArea", pMoeniaArea)
		end
	end

	if (isZoneEnabled("talus")) then
		local pShipArea = spawnActiveArea("talus", "object/active_area.iff", -2380, 23, 2031, 75, 0)

		if (pShipArea ~= nil) then
			createObserver(ENTEREDAREA, "DarnDroid1", "notifyEnteredCrashedShipArea", pShipArea)
		end
	end
end

function DarnDroid1:spawnMobiles()
	if (isZoneEnabled("naboo")) then
		local pNpc = spawnMobile("naboo", "c3tc", 0, 4723, 3, -4935, -180, 0)

		if (pNpc ~= nil) then
			AiAgent(pNpc):addCreatureFlag(AI_STATIONARY)
		end

		spawnMobile("naboo", "selan_ellison", 0, 16, 1, 56, -79, 4215410)
	end

	if (isZoneEnabled("corellia")) then
		spawnMobile("corellia", "amarent_loren", 0, 14.7, 0.6, 55.6, -48, 1935687)
	end

	if (isZoneEnabled("talus")) then
		local pNpc = spawnMobile("talus", "valance_serth", 0, -2389, 23, 2043, 0, 0)
		if (pNpc ~= nil) then
			AiAgent(pNpc):addCreatureFlag(AI_STATIONARY)
		end

		spawnMobile("talus", "black_sun_minion", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_initiate", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_initiate", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_initiate", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_initiate", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_smuggler", 300, -2389, 23, 2043, 0, 0)
		spawnMobile("talus", "black_sun_smuggler", 300, -2389, 23, 2043, 0, 0)
	end
end

function DarnDroid1:notifyEnteredMoeniaStarportArea(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (not PlayerObject(pGhost):isJournalQuestActive(self.questCrc)) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(self.questCrc, self.TASK_GOTOMOENIA) == true) then
		return 0
	end

	PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_GOTOMOENIA, true);
	PlayerObject(pGhost):activateJournalQuestTask(self.questCrc, self.TASK_TALKTOSELAN, true);
	return 0
end

function DarnDroid1:notifyEnteredCrashedShipArea(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (not PlayerObject(pGhost):isJournalQuestActive(self.questCrc)) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(self.questCrc, self.TASK_FINDSHIP)) then
		return 0
	end

	PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_FINDSHIP, true);
	PlayerObject(pGhost):activateJournalQuestTask(self.questCrc, self.TASK_TALKTOVALANCE, true);
	return 0
end

function DarnDroid1:completeQuest(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return false
	end

	if (PlayerObject(pGhost):isJournalQuestComplete(self.questCrc)) then
		return false
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":darnDroid1WaypointID"))

	if (self:awardQuestItem(pPlayer, "object/tangible/loot/collectible/collectible_parts/blue_rug_adhesive.iff")) then
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":darnDroid1WaypointID")
		end

		CreatureObject(pPlayer):addBankCredits(3000, true)
		CreatureObject(pPlayer):sendSystemMessage("Valance Serth transfers a reward of 3000 Credits")
		PlayerObject(pGhost):increaseFactionStanding("townsperson", 50)
		CreatureObject(pPlayer):awardExperience("combat_general", 1000, true)
		PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_TALKTOVALANCE, true);
		PlayerObject(pGhost):completeJournalQuest(self.questCrc, true);

		return true
	end

	return false
end

function DarnDroid1:awardQuestItem(pPlayer, item)
	if (pPlayer == nil) then
		return false
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		if (SceneObject(pInventory):isContainerFullRecursive()) then
			return false
		end

		local pItem = giveItem(pInventory, item, -1)

		if (pItem ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
			return true
		end
	end

	return false
end

function DarnDroid1:giveQuest(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestActive(self.questCrc) or PlayerObject(pGhost):isJournalQuestComplete(self.questCrc)) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):activateJournalQuest(self.questCrc, true);
	PlayerObject(pGhost):activateJournalQuestTask(self.questCrc, self.TASK_GOTOMOENIA, false);
	DarnDroid1:giveWaypoint(pPlayer, "naboo", "Moenia Starport", 4796, -4696);
end

function DarnDroid1:giveAmarentTask(pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (not PlayerObject(pGhost):isJournalQuestActive(self.questCrc) or PlayerObject(pGhost):isJournalQuestComplete(self.questCrc) or
		PlayerObject(pGhost):isJournalQuestTaskComplete(self.questCrc, self.TASK_TALKTOSELAN)) then

		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_TALKTOSELAN, true);
	PlayerObject(pGhost):activateJournalQuestTask(self.questCrc, self.TASK_TALKTOAMARENT, true);
	DarnDroid1:giveWaypoint(pPlayer, "corellia", "Amarent Loren", -5026, -2259);
end


function DarnDroid1:giveWaypoint(pPlayer, planet, name, x, y)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":darnDroid1WaypointID"))

	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":darnDroid1WaypointID")
	end
	local waypointID = PlayerObject(pGhost):addWaypoint(planet, name, "", x, y, WAYPOINTYELLOW, true, true, 0, 0)
	setQuestStatus(playerID .. ":darnDroid1WaypointID", waypointID)
end


function DarnDroid1:giveShipTask(pPlayer, taskType)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestComplete(questCrc) or not PlayerObject(pGhost):isJournalQuestTaskComplete(self.questCrc, self.TASK_TALKTOAMARENT)) then
		return
	end

	if (taskType == "bribe") then
		if (CreatureObject(pPlayer):getCashCredits() < 1000) then
			return
		end

		CreatureObject(pPlayer):subtractCashCredits(1000)
		PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_BRIBEDAMARENT, false)
	elseif (taskType == "threaten") then
		PlayerObject(pGhost):decreaseFactionStanding("imperial", 50)

		PlayerObject(pGhost):completeJournalQuestTask(self.questCrc, self.TASK_INTIMIDATEDAMARENT, false)
	end

	PlayerObject(pGhost):activateJournalQuestTask(self.questCrc, self.TASK_FINDSHIP, true)
	self:giveWaypoint(pPlayer, "talus", "Talus Crash Site", -2368, 2043)
end