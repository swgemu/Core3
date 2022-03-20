RishaSinan = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RishaSinan",
}

local questCrc = 1871002803 --CRC of "quest/lf_deadmite"

--Task Constants
local TASK_GOTOCAVE = 0 --Go to the Giant Bark Mite Cave
local TASK_LOOTQUEEN = 1 --Collect 1 Mutant Bark Mite Queen Sample
local TASK_LOOTSOLDIER = 2 --Collect 1 Mutant Bark Mite Soldier Sample
local TASK_LOOTMITE = 3 --Collect Giant Bark Mite Samples
local TASK_LOOTWORKER = 4 --Collect 3 Mutant Bark Mite Worker Samples
local TASK_LOOTHATCHLING = 5 --Collect 5 Bark Mite Hatchling Samples
local TASK_RETURNTORISHA = 6 --When all the samples are collected, return to Risha Sinan in Restuss

local lootTasks = {
	[TASK_LOOTQUEEN] = { statusKey = "", mobName = "Mutant Bark Mite Queen", reward = 2000, requiredSamples = 0 },
	[TASK_LOOTSOLDIER] = { statusKey = "", mobName = "Mutant Bark Mite Soldier", reward = 2000, requiredSamples = 0 },
	[TASK_LOOTMITE] = { statusKey = ":rishaSinanDeadMites", mobName = "Giant Bark Mite", reward = 1500, requiredSamples = 3 },
	[TASK_LOOTWORKER] = { statusKey = ":rishaSinanDeadWorkers", mobName = "Giant Bark Mite Worker", reward = 1200, requiredSamples = 3 },
	[TASK_LOOTHATCHLING] = { statusKey = ":rishaSinanDeadHatchlings", mobName = "Giant Bark Mite Hatchling", reward = 1000, requiredSamples = 5 }
}

registerScreenPlay("RishaSinan", true)

function RishaSinan:start()
	if (isZoneEnabled("rori")) then
		self:spawnAreaObjects()
		self:spawnMobiles()
	end
end

function RishaSinan:spawnAreaObjects()
	local miteCaveArea = spawnActiveArea("rori", "object/active_area.iff", 3572, 91, 5424, 10, 0)

	if (miteCaveArea ~= nil) then
		createObserver(ENTEREDAREA, "RishaSinan", "notifyEnteredMiteCaveArea", miteCaveArea)
	end
end

function RishaSinan:spawnMobiles()
	spawnMobile("rori", "risha_sinan", 0, 5335, 80, 5637, 0, 0)
end

function RishaSinan:notifyEnteredMiteCaveArea(miteCaveArea, pPlayer)
	if (pPlayer == nil) then
		return 0
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) == false) then
		return 0
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_GOTOCAVE) == true) then
		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanCaveWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanCaveWaypointID")
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_GOTOCAVE, true);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_LOOTQUEEN, false);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_LOOTSOLDIER, false);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_LOOTMITE, false);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_LOOTWORKER, false);
	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_LOOTHATCHLING, true);

	return 0
end

function RishaSinan:isQuestComplete(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_GOTOCAVE) and
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_LOOTQUEEN) and
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_LOOTSOLDIER) and
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_LOOTMITE) and
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_LOOTWORKER) and
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_LOOTHATCHLING)) then
			return true;
	end

	return false;
end

function RishaSinan:finalTask(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_RETURNTORISHA)) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanCaveWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanCaveWaypointID")
	end

	oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanWaypointID")
	end
	local waypointID = PlayerObject(pGhost):addWaypoint("rori", "Return to Risha Sinan", "", 5335, 5637, WAYPOINTYELLOW, true, true, 0, 0)
	setQuestStatus(playerID .. ":rishaSinanWaypointID", waypointID)

	PlayerObject(pGhost):activateJournalQuestTask(questCrc, TASK_RETURNTORISHA, true);
end

function RishaSinan:completeQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanCaveWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanCaveWaypointID")
	end

	oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanWaypointID")
	end

	PlayerObject(pGhost):completeJournalQuestTask(questCrc, TASK_RETURNTORISHA, true)
	PlayerObject(pGhost):completeJournalQuest(questCrc, true)

	removeQuestStatus(playerID .. lootTasks[TASK_LOOTMITE].statusKey)
	removeQuestStatus(playerID .. lootTasks[TASK_LOOTWORKER].statusKey)
	removeQuestStatus(playerID .. lootTasks[TASK_LOOTHATCHLING].statusKey)
end

function RishaSinan:giveQuest(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) == true or
		PlayerObject(pGhost):isJournalQuestComplete(questCrc) == true) then

		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	setQuestStatus(playerID .. lootTasks[TASK_LOOTMITE].statusKey, 0)
	setQuestStatus(playerID .. lootTasks[TASK_LOOTWORKER].statusKey, 0)
	setQuestStatus(playerID .. lootTasks[TASK_LOOTHATCHLING].statusKey, 0)

	PlayerObject(pGhost):activateJournalQuest(questCrc, true);
	RishaSinan:giveWaypoints(pPlayer);
end

function RishaSinan:giveWaypoints(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = CreatureObject(pPlayer):getObjectID()
	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanCaveWaypointID"))

	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanCaveWaypointID")
	end
	local waypointID = PlayerObject(pGhost):addWaypoint("rori", "Giant Mite Cave", "", 3572, 5424, WAYPOINTYELLOW, true, true, 0, 0)
	setQuestStatus(playerID .. ":rishaSinanCaveWaypointID", waypointID)

	oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanWaypointID")
	end
	waypointID = PlayerObject(pGhost):addWaypoint("rori", "Risha Sinan", "", 5335, 5637, WAYPOINTYELLOW, false, true, 0, 0)
	setQuestStatus(playerID .. ":rishaSinanWaypointID", waypointID)
end

function RishaSinan:onLoot(pLooter, taskID)
	local pGhost = CreatureObject(pLooter):getPlayerObject()
	local statusKey = ""
	local mobName = ""
	local reward = 0
	local requiredSamples = 0
	local deadMites = 0;

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestActive(questCrc) == false or
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, TASK_GOTOCAVE) == false or
		PlayerObject(pGhost):isJournalQuestTaskComplete(questCrc, taskID) == true) then
		return
	end

	if (taskID < TASK_LOOTQUEEN or taskID > TASK_LOOTHATCHLING ) then
		return
	end

	if (lootTasks[taskID].statusKey ~= "") then
		local playerID = CreatureObject(pLooter):getObjectID()
		local oldMites = tonumber(getQuestStatus(playerID .. lootTasks[taskID].statusKey))
		if (oldMites == nil) then
			oldMites = 0
		end
		deadMites = oldMites + 1;
		setQuestStatus(playerID .. lootTasks[taskID].statusKey, deadMites)
	end

	CreatureObject(pLooter):sendSystemMessage("Collected " .. lootTasks[taskID].mobName .. " Sample")

	if (deadMites >= lootTasks[taskID].requiredSamples) then
		PlayerObject(pGhost):completeJournalQuestTask(questCrc, taskID, true)
		CreatureObject(pLooter):addBankCredits(lootTasks[taskID].reward, true)
		CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of " .. lootTasks[taskID].reward .. " Credits")
	end

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end
end

function RishaSinan:notifyLootMite(pLootedCreature, pLooter, nothing)
	RishaSinan:onLoot(pLooter, TASK_LOOTMITE)

	return 0
end

function RishaSinan:notifyLootWorker(pLootedCreature, pLooter, nothing)
	RishaSinan:onLoot(pLooter, TASK_LOOTWORKER)

	return 0
end

function RishaSinan:notifyLootHatchling(pLootedCreature, pLooter, nothing)
	RishaSinan:onLoot(pLooter, TASK_LOOTHATCHLING)

	return 0
end

function RishaSinan:notifyLootSoldier(pLootedCreature, pLooter, nothing)
	RishaSinan:onLoot(pLooter, TASK_LOOTSOLDIER)

	return 0
end

function RishaSinan:notifyLootQueen(pLootedCreature, pLooter, nothing)
	RishaSinan:onLoot(pLooter, TASK_LOOTQUEEN)

	return 0
end

function RishaSinan:awardQuestItem(pPlayer, item)
	if (pPlayer == nil) then
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if (pInventory ~= nil) then
		local pItem = giveItem(pInventory, item, -1)

		if (pItem ~= nil) then
			RishaSinan:completeQuest(pPlayer)
			CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
		end
	end
end

--Conversation Handler
risha_sinan_convo_handler = conv_handler:new {}

function risha_sinan_convo_handler:getInitialScreen(pPlayer, pNpn, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestComplete(questCrc) == true) then
		return convoTemplate:getScreen("nice_to_see_you")
	elseif (PlayerObject(pGhost):isJournalQuestActive(questCrc) == true) then
		return convoTemplate:getScreen("how_goes")
	else
		return convoTemplate:getScreen("first_screen")
	end
end

function risha_sinan_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (screenID == "happy_to_help")  then
		CreatureObject(pPlayer):setScreenPlayState(1, "risha_sinan")
		RishaSinan:giveQuest(pPlayer)
	elseif(screenID == "how_goes") then
		if (RishaSinan:isQuestComplete(pPlayer) == true) then
			clonedConversation:addOption("@conversation/lf_killmite:s_191","tasks_complete") --I got all the samples that you wanted.  Didn't you get my data transfers?
		else
			clonedConversation:addOption("@conversation/lf_killmite:s_207","not_done") --I'm not done yet.
		end
		clonedConversation:addOption("@conversation/lf_killmite:s_212", "got_lost") --I got lost.  Do you have the location of the cave?
	elseif (screenID == "got_lost") then
		RishaSinan:giveWaypoints(pPlayer)
	elseif (screenID == "give_schematic") then
		RishaSinan:awardQuestItem(pPlayer, "object/tangible/loot/loot_schematic/bubble_tank_schematic.iff");
	elseif (screenID == "give_stim") then
		RishaSinan:awardQuestItem(pPlayer, "object/tangible/skill_buff/skill_buff_pistol_accuracy.iff");
	end

	return pConvScreen
end
