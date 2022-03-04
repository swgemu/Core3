RishaSinan = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RishaSinan",
}

local questHashCode = 1871002803, --CRC of "quest/lf_deadmite"

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

	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestActive(questHashCode) == false) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 0) == true) then
		return 0
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	local oldWaypointID = tonumber(getQuestStatus(playerID .. ":rishaSinanCaveWaypointID"))
	if (oldWaypointID ~= 0) then
		PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
		removeQuestStatus(playerID .. ":rishaSinanCaveWaypointID")
	end

	PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 0, true);
	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 1, false);
	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 2, false);
	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 3, false);
	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 4, false);
	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 5, true);

	return 0
end

function RishaSinan:isQuestComplete(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 0) and
		PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 1) and
		PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 2) and
		PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 3) and
		PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 4) and
		PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 5)) then
			return true;
	end

	return false;
end

function RishaSinan:finalTask(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 6)) then
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

	PlayerObject(pGhost):questActivateQuestTask(questHashCode, 6, true);
end

function RishaSinan:giveQuest(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	PlayerObject(pGhost):questActivateQuest(questHashCode, true);
	RishaSinan:giveWaypoints(pPlayer);
end

function RishaSinan:giveWaypoints(pPlayer)
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

function RishaSinan:notifyLootMite(pLootedCreature, pLooter, nothing)
	--Need 3 Mites
	local pGhost = CreatureObject(pLooter):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 3)) then
		return 0
	end

	local playerID = CreatureObject(pLooter):getObjectID()
	local deadMites = tonumber(getQuestStatus(playerID .. ":rishaSinanDeadMites"))
	if (deadMites == nil) then
		deadMites = 0
	end
	deadMites = deadMites + 1;
	setQuestStatus(playerID .. ":rishaSinanDeadMites", deadMites)

	CreatureObject(pLooter):sendSystemMessage("Collected Giant Bark Mite Sample")

	if (deadMites >= 3) then
		PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 3, true)
		CreatureObject(pLooter):addBankCredits(1500, true)
		CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of 1500 Credits")
	end

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end

	return 0
end

function RishaSinan:notifyLootWorker(pLootedCreature, pLooter, nothing)
	--Need 3 Workers
	local pGhost = CreatureObject(pLooter):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 4)) then
		return 0
	end

	local playerID = CreatureObject(pLooter):getObjectID()
	local deadWorkers = tonumber(getQuestStatus(playerID .. ":rishaSinanDeadWorkers"))
	if (deadWorkers == nil) then
		deadWorkers = 0;
	end
	deadWorkers = deadWorkers + 1;
	setQuestStatus(playerID .. ":rishaSinanDeadWorkers", deadWorkers)

	CreatureObject(pLooter):sendSystemMessage("Collected Mutant Bark Mite Worker Sample")

	if (deadWorkers >= 3) then
		PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 4, true)
		CreatureObject(pLooter):addBankCredits(1200, true)
		CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of 1200 Credits")
	end

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end

	return 0
end

function RishaSinan:notifyLootHatchling(pLootedCreature, pLooter, nothing)
	--Need 5 Hatchlings
	local pGhost = CreatureObject(pLooter):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 5)) then
		return 0
	end

	local playerID = CreatureObject(pLooter):getObjectID()
	local deadHatchlings = tonumber(getQuestStatus(playerID .. ":rishaSinanDeadHatchlings"))
	if (deadHatchlings == nil) then
		deadHatchlings = 0
	end
	deadHatchlings = deadHatchlings + 1;
	setQuestStatus(playerID .. ":rishaSinanDeadHatchlings", deadHatchlings)

	CreatureObject(pLooter):sendSystemMessage("Collected Mutant Bark Mite Hatchling Sample")

	if (deadHatchlings >= 5) then
		PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 5, true)
		CreatureObject(pLooter):addBankCredits(1000, true)
		CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of 1000 Credits")
	end

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end

	return 0
end

function RishaSinan:notifyLootSoldier(pLootedCreature, pLooter, nothing)
	--Need 1 Soldier
	local pGhost = CreatureObject(pLooter):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 2)) then
		return 0
	end

	CreatureObject(pLooter):sendSystemMessage("Collected Mutant Bark Mite Soldier Sample")

	PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 2, true)
	CreatureObject(pLooter):addBankCredits(2000, true)
	CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of 2000 Credits")

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end

	return 0
end

function RishaSinan:notifyLootQueen(pLootedCreature, pLooter, nothing)
	--Need 1 Queen
	local pGhost = CreatureObject(pLooter):getPlayerObject()

	if (pGhost == nil) then
		return 0
	end

	if (PlayerObject(pGhost):questIsQuestTaskComplete(questHashCode, 1)) then
		return 0
	end

	CreatureObject(pLooter):sendSystemMessage("Collected Mutant Bark Mite Queen Sample")

	PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 1, true)
	CreatureObject(pLooter):addBankCredits(2000, true)
	CreatureObject(pLooter):sendSystemMessage("Risha Sinan transfers a reward of 2000 Credits")

	if (self:isQuestComplete(pLooter)) then
		self:finalTask(pLooter);
	end

	return 0
end

--Conversation Handler
risha_sinan_convo_handler = conv_handler:new {}

function risha_sinan_convo_handler:getInitialScreen(pPlayer, pNpn, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):questIsQuestComplete(questHashCode) == true) then
		return convoTemplate:getScreen("nice_to_see_you")
	elseif (PlayerObject(pGhost):questIsQuestActive(questHashCode) == true) then
		return convoTemplate:getScreen("how_goes")
	else
		return convoTemplate:getScreen("first_screen")
	end
end

function risha_sinan_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pItem = giveItem(pInventory, "object/tangible/loot/loot_schematic/bubble_tank_schematic.iff", -1)

			if (pItem ~= nil) then
				PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 6, true)
				PlayerObject(pGhost):questCompleteQuest(questHashCode, true)
				CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
			end
		end
	elseif (screenID == "give_stim") then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

		if (pInventory ~= nil) then
			local pItem = giveItem(pInventory, "object/tangible/skill_buff/skill_buff_pistol_accuracy.iff", -1)

			if (pItem ~= nil) then
				PlayerObject(pGhost):questCompleteQuestTask(questHashCode, 6, true)
				PlayerObject(pGhost):questCompleteQuest(questHashCode, true)
				CreatureObject(pPlayer):sendSystemMessage("@system_msg:give_item_success")
			end
		end
	end

	return pConvScreen
end