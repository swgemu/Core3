DarnDroid1 = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DarnDroid1",
}

local questCrc = 3408891851 --CRC of "quest/c_darndroid1"
local imperialCrc = 3679112276 --CRC of "imperial"

--Task Constants
local TASK_GOTOMOENIA = 1 --Go to Moenia Starport
local TASK_TALKTOSELAN = 2 --Talk to Selan Ellison
local TASK_TALKTOAMARENT = 3 --Speak to Amarent Loren
local TASK_FINDSHIP = 4 --Find the crashed ship.
local TASK_TALKTOVALANCE = 5 --Talk to Valance Serth
local TASK_BRIBEDAMARENT = 9 --Bribed Amarent Loren
local TASK_INTIMIDATEDAMARENT = 11 --Intimidated Amarent Loren

registerScreenPlay("DarnDroid1", true)

function DarnDroid1:start()
	self:spawnAreaObjects()
	self:spawnMobiles()
end

function DarnDroid1:spawnAreaObjects()
	if (isZoneEnabled("naboo")) then
		local moeniaStarportArea = spawnActiveArea("naboo", "object/active_area.iff", 4796, 20, -4696, 20, 0)

		if (moeniaStarportArea ~= nil) then
			createObserver(ENTEREDAREA, "DarnDroid1", "notifyEnteredMoeniaStarportArea", moeniaStarportArea)
		end
	end

	if (isZoneEnabled("talus")) then
		local crashedShipArea = spawnActiveArea("talus", "object/active_area.iff", -2380, 0, 2031, 25, 0)

		if (crashedShipArea ~= nil) then
			createObserver(ENTEREDAREA, "DarnDroid1", "notifyEnteredCrashedShipArea", crashedShipArea)
		end
	end
end

function DarnDroid1:spawnMobiles()
	if (isZoneEnabled("naboo")) then
		spawnMobile("naboo", "c3tc", 0, 4723, 3, -4935, -180, 0)
		spawnMobile("naboo", "selan_ellison", 0, 16, 1, 56, -79, 4215410)
	end
	if (isZoneEnabled("corellia")) then
		spawnMobile("corellia", "amarent_loren", 0, 14.7, 0.6, 55.6, -48, 1935687)
	end
	if (isZoneEnabled("talus")) then
		spawnMobile("talus", "valance_serth", 0, -2389, 23, 2043, 0, 0)
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

	if (not PlayerObject(pGhost):isJournalQuestActive(questCrc)) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_GOTOMOENIA) == true) then
		return 0
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_GOTOMOENIA, true);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOSELAN, true);
	return 0
end

function DarnDroid1:notifyEnteredCrashedShipArea(pArea, pPlayer)
	if (pPlayer == nil or not SceneObject(pPlayer):isPlayerCreature()) then
		return 1
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (not PlayerObject(pGhost):isJournalQuestActive(questCrc)) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_FINDSHIP)) then
		return 0
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_FINDSHIP, true);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOVALANCE, true);
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

	if (PlayerObject(pGhost):isJournalQuestComplete(questCrc)) then
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
		PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_TALKTOVALANCE, true);
		PlayerObject(pGhost):completeJournalQuest(questCrc, true);

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

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) or PlayerObject(pGhost):isJournalQuestComplete(questCrc)) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):activateJournalQuest(questCrc, true);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_GOTOMOENIA, false);
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

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) == false or
		PlayerObject(pGhost):isJournalQuestComplete(questCrc) == true or
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_TALKTOSELAN) == true) then

		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_TALKTOSELAN, true);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_TALKTOAMARENT, true);
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

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) == false or
		PlayerObject(pGhost):isJournalQuestComplete(questCrc) == true or
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_TALKTOAMARENT) == true) then

		return
	end

	if (taskType == "bribe") then
		if (CreatureObject(pPlayer):getCashCredits() < 1000) then
			return
		end
		CreatureObject(pPlayer):subtractCashCredits(1000)
		PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_BRIBEDAMARENT, false)
		PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_BRIBEDAMARENT, false)
	elseif (taskType == "threaten") then
		PlayerObject(pGhost):decreaseFactionStanding("imperial", 50)
		PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_INTIMIDATEDAMARENT, false)
		PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_INTIMIDATEDAMARENT, false)
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_TALKTOAMARENT, true)
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_FINDSHIP, true)
	self:giveWaypoint(pPlayer, "talus", "Talus Crash Site", -2368, 2043)
end