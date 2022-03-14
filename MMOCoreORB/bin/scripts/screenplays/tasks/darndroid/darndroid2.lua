DarnDroid2 = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DarnDroid2",
}

local quest1Crc = 3408891851 --CRC of "quest/c_darndroid1"
local quest2Crc = 3329009938 --CRC of "quest/c_darndroid2"

--Task Constants
local TASK_FINDSTAGING = 0 --Go to the Black Sun staging camp and scout the camp.
local TASK_KILLMINION = 1 --Kill 1 Black Sun Minion.
local TASK_KILLSMUGGLER = 2 --Kill 5 Black Sun Smugglers.
local TASK_KILLINITIATE = 3 --Kill 8 Black Sun Initiates.
local TASK_RETURNTOVALANCE = 4 --Once you have killed 8 Black Sun Initiates, 5 Black Sun Smugglers, and 1 Black Sun Minion, return to Valance Serth.
local TASK_KILLTRANSPORT = 5 --Talk to Valance once the space transport is dead.
local TASK_WIPEMEM = 6 --Wipe C-3TC's memory.

registerScreenPlay("DarnDroid2", true)

function DarnDroid2:start()
	self:spawnAreaObjects()
	self:spawnMobiles()
end

function DarnDroid2:spawnAreaObjects()
	if (isZoneEnabled("talus")) then
		local blackSunArea = spawnActiveArea("talus", "object/active_area.iff", 5353, 131, 5632, 10, 0)

		if (blackSunArea ~= nil) then
			createObserver(ENTEREDAREA, "DarnDroid2", "notifyEnteredBlackSunArea", blackSunArea)
		end
	end
end

function DarnDroid2:spawnMobiles()
	if (isZoneEnabled("talus")) then
		local npc = spawnMobile("talus", "black_sun_minion", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyMinionDead", npc)
		npc = spawnMobile("talus", "black_sun_smuggler", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifySmugglerDead", npc)
		npc = spawnMobile("talus", "black_sun_smuggler", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifySmugglerDead", npc)
		npc = spawnMobile("talus", "black_sun_smuggler", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifySmugglerDead", npc)
		npc = spawnMobile("talus", "black_sun_smuggler", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifySmugglerDead", npc)
		npc = spawnMobile("talus", "black_sun_smuggler", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifySmugglerDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
		npc = spawnMobile("talus", "black_sun_initiate", 480, 5379, 97, 5675, 0, 0)
		createObserver(OBJECTDESTRUCTION, "DarnDroid2", "notifyInitiateDead", npc)
	end
end

function DarnDroid2:notifyEnteredBlackSunArea(pArea, pPlayer)
	if (SceneObject(pPlayer):isCreatureObject() == false) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestActive(quest2Crc) == false) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_FINDSTAGING) == true) then
		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_FINDSTAGING, true);
	PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_KILLMINION, false);
	PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_KILLSMUGGLER, false);
	PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_KILLINITIATE, true);
	setQuestStatus(playerID .. "darnDroid2SmugglersKilled", 0)
	setQuestStatus(playerID .. "darnDroid2InitiatesKilled", 0)
	return 0
end

function DarnDroid2:notifyMinionDead(pMinion, pPlayer)
	if (SceneObject(pPlayer):isCreatureObject() == false) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLMINION) == true) then
		return 0
	end

	PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_KILLMINION, true);
	self:returnToValance(pPlayer)
	return 0
end

function DarnDroid2:notifySmugglerDead(pSmuggler, pPlayer)
	if (SceneObject(pPlayer):isCreatureObject() == false) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLSMUGGLER) == true) then
		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local count = tonumber(getQuestStatus(playerID .. "darnDroid2SmugglersKilled"))
	if (count == nil) then
		count = 0
	end
	count = count + 1
	setQuestStatus(playerID .. "darnDroid2SmugglersKilled", count)
	if (count >= 5) then
		PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_KILLSMUGGLER, true);
		self:returnToValance(pPlayer)
	end

	return 0
end

function DarnDroid2:notifyInitiateDead(pSmuggler, pPlayer)
	if (SceneObject(pPlayer):isCreatureObject() == false) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLINITIATE) == true) then
		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local count = tonumber(getQuestStatus(playerID .. "darnDroid2InitiatesKilled"))
	if (count == nil) then
		count = 0
	end
	count = count + 1
	setQuestStatus(playerID .. "darnDroid2InitiatesKilled", count)

	if (count >= 8) then
		PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_KILLINITIATE, true);
		self:returnToValance(pPlayer)
	end

	return 0
end

function DarnDroid2:returnToValance(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLMINION) == true and
		PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLSMUGGLER) == true and
		PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_KILLINITIATE) == true) then

		DarnDroid2:clearValanceWaypoint(pPlayer)
		DarnDroid2:giveWaypoint(pPlayer,  "talus", "Return to Valance Serth", -2389, 2043)
		PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_RETURNTOVALANCE, true);
	end
end

function DarnDroid2:giveSpaceMission(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(quest2Crc, TASK_RETURNTOVALANCE) == false and
		PlayerObject(pGhost):isJournalQuestTaskActive(quest2Crc, TASK_KILLTRANSPORT) == false) then

		PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_RETURNTOVALANCE, true);
		PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_KILLTRANSPORT, true);
		--TODO Give the space mission here when possible
	end
end

function DarnDroid2:giveMemWipeTask(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	--If we are here, then we've already verified the space mission was a success, so we just have to award the next step
	PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_KILLTRANSPORT, true);
	PlayerObject(pGhost):activateJournalQuestTask(quest2Crc, TASK_WIPEMEM, true);
	self:giveWaypoint(pPlayer, "naboo", "C-3TC", 4723, -4935)
end

function DarnDroid2:completeQuest(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return false
	end

	if (PlayerObject(pGhost):isJournalQuestComplete(quest2Crc) == true) then
		return false
	end

	if (self:awardQuestItem(pPlayer, "object/tangible/loot/loot_schematic/droid_head_schematic.iff")) then
		local playerID = CreatureObject(pPlayer):getObjectID()
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":DarnDroid2WaypointID"))

		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":DarnDroid2WaypointID")
		end

		CreatureObject(pPlayer):addBankCredits(1000, true)
		CreatureObject(pPlayer):sendSystemMessage("Valance Serth transfers a reward of 1000 Credits")
		PlayerObject(pGhost):increaseFactionStanding("townsperson", 50)
		CreatureObject(pPlayer):awardExperience("combat_general", 1000, true)
		PlayerObject(pGhost):completeJournalQuestTask(quest2Crc, TASK_WIPEMEM, true);
		PlayerObject(pGhost):completeJournalQuest(quest2Crc, true);
	end

	return true
end

function DarnDroid2:awardQuestItem(pPlayer, item)
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

function DarnDroid2:giveQuest(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestActive(quest2Crc) == true or
		PlayerObject(pGhost):isJournalQuestComplete(quest2Crc) == true) then

		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	PlayerObject(pGhost):activateJournalQuest(quest2Crc, true);
	DarnDroid2:giveWaypoint(pPlayer, "talus", "Black Sun Staging Camp", 5353, 5632);
    DarnDroid2:giveValanceWaypoint(pPlayer)
end

function DarnDroid2:giveValanceWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":DarnDroidValanceWaypointID"))

	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":DarnDroidValanceWaypointID")
	end
	local waypointID = PlayerObject(pGhost):addWaypoint("talus", "Valance Serth", "", -2389, 2043, WAYPOINTYELLOW, false, true, 0, 0)
	setQuestStatus(playerID .. ":DarnDroidValanceWaypointID", waypointID)
end

function DarnDroid2:clearValanceWaypoint(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":DarnDroidValanceWaypointID"))

	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":DarnDroidValanceWaypointID")
	end
end

function DarnDroid2:giveWaypoint(pPlayer, planet, name, x, y)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":DarnDroid2WaypointID"))

	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":DarnDroid2WaypointID")
	end
	local waypointID = PlayerObject(pGhost):addWaypoint(planet, name, "", x, y, WAYPOINTYELLOW, true, true, 0, 0)
	setQuestStatus(playerID .. ":DarnDroid2WaypointID", waypointID)
end

function DarnDroid2:isPlayerOnQuest1(pPlayer)
	if (PlayerObject(pPlayer):isJournalQuestTaskActive(quest1Crc, 5) == true and
		PlayerObject(pPlayer):isJournalQuestActive(quest1Crc) == true) then
		return true
	end
	return false
end

function DarnDroid2:isPlayerReadyForQuest2(pPlayer)
	if (PlayerObject(pPlayer):isJournalQuestComplete(quest1Crc) == true and
		PlayerObject(pPlayer):isJournalQuestActive(quest2Crc) == false) then
		return true
	end
	return false
end

function DarnDroid2:isPlayerDoneQuest2Part2(pPlayer)
	if (PlayerObject(pPlayer):isJournalQuestTaskActive(quest2Crc, TASK_RETURNTOVALANCE) == true and
		PlayerObject(pPlayer):isJournalQuestTaskComplete(quest2Crc, TASK_KILLMINION) == true and
		PlayerObject(pPlayer):isJournalQuestTaskComplete(quest2Crc, TASK_KILLSMUGGLER) == true and
		PlayerObject(pPlayer):isJournalQuestTaskComplete(quest2Crc, TASK_KILLINITIATE) == true) then
		return true
	end
	return false
end

function DarnDroid2:isPlayerDoneSpaceMission(pPlayer)
	--TODO Fix when space missions are possible
	return false
end

function DarnDroid2:isPlayerOnQuest2Part1(pPlayer)
	if (PlayerObject(pPlayer):isJournalQuestTaskActive(quest2Crc, TASK_FINDSTAGING) == true or
		PlayerObject(pPlayer):isJournalQuestTaskActive(quest2Crc, TASK_KILLMINION) == true or
		PlayerObject(pPlayer):isJournalQuestTaskActive(quest2Crc, TASK_KILLSMUGGLER) == true or
		PlayerObject(pPlayer):isJournalQuestTaskActive(quest2Crc, TASK_KILLINITIATE) == true) then
		return true
	end
	return false
end

function DarnDroid2:isPlayerFailedSpaceMission(pPlayer)
	--TODO Fix when space missions are possible
	return false
end

function DarnDroid2:isPlayerCompletedAll(pPlayer)
	if (PlayerObject(pPlayer):isJournalQuestComplete(quest1Crc) == true and
		PlayerObject(pPlayer):isJournalQuestComplete(quest2Crc) == true) then
		return true
	end
	return false
end
