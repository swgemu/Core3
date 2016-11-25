local ObjectManager = require("managers.object.object_manager")

victorVisalisPhase2ConvoHandler = conv_handler:new {
	}

local tuskenHead = "object/tangible/loot/quest/tusken_head.iff"

function victorVisalisPhase2ConvoHandler:hasTuskenHead(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			return getContainerObjectByTemplate(pInventory, tuskenHead, true)
		end
	end
	return false
end

function victorVisalisPhase2ConvoHandler:giveTuskenReward(pPlayer)
	if (pPlayer ~= nil) then
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			local ptuskenHead = getContainerObjectByTemplate(pInventory,tuskenHead, true)
			if (ptuskenHead ~= nil) then
				SceneObject(ptuskenHead):destroyObjectFromWorld()
				SceneObject(ptuskenHead):destroyObjectFromDatabase()
			end
			createLoot(pInventory, "bestine_election_tusken_quest", 0, true)
			self:removeTuskenQuest(pPlayer)

			local electionNum = BestineElectionScreenPlay:getElectionNumber()
			CreatureObject(pPlayer):setScreenPlayState(2, "bestine_tusken_quest" .. electionNum)
		end
	end
end

function victorVisalisPhase2ConvoHandler:tuskenWaypoint(pPlayer)
	if (pPlayer ~= nil) then

		local playerID = SceneObject(pPlayer):getObjectID()
		local waypointID = readData(playerID .. ":bestine_election:tuskenWaypointID")

		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			PlayerObject(pPlayerObj):removeWaypoint(waypointID, true)
			waypointID = PlayerObject(pPlayerObj):addWaypoint("tatooine", "Fort Tusken", "", -3960, 6233, WAYPOINT_COLOR_PURPLE, true, true, 0,0)
			writeData(playerID .. ":bestine_election:tuskenWaypointID", waypointID)
		end
	end
end

function victorVisalisPhase2ConvoHandler:giveTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		self:tuskenWaypoint(pPlayer)
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		CreatureObject(pPlayer):setScreenPlayState(1, "bestine_tusken_quest" .. electionNum)
	end
end

function victorVisalisPhase2ConvoHandler:removeTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local playerID = SceneObject(pPlayer):getObjectID()
		local waypointID = readData(playerID.. ":bestine_election:tuskenWaypointID")

		local pPlayerObj = CreatureObject(pPlayer):getPlayerObject()
		if (pPlayerObj ~= nil) then
			PlayerObject(pPlayerObj):removeWaypoint(waypointID, true)
			deleteData(playerID .. ":bestine_election:tuskenWaypointID")
		end
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		CreatureObject(pPlayer):removeScreenPlayState(1, "bestine_tusken_quest" .. electionNum)
	end
end


function victorVisalisPhase2ConvoHandler:giveElectionReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
		if (pInventory ~= nil) then
			createLoot(pInventory, "bestine_election_victor_visalis_rewards", 0, true)
		end
		writeScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward", electionNum)
	end
end

function victorVisalisPhase2ConvoHandler:receivedElectionReward(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		local playerCampaign = tonumber(readScreenPlayData(pPlayer, "BestineElection", "receivedVictorReward"))
		if (playerCampaign ~= nil) then
			return (playerCampaign == electionNum)
		end
	end
	return false
end

function victorVisalisPhase2ConvoHandler:onTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (CreatureObject(pPlayer):hasScreenPlayState(1, "bestine_tusken_quest" .. electionNum)) then
			return true
		end
	end
	return false
end

function victorVisalisPhase2ConvoHandler:completedTuskenQuest(pPlayer)
	if (pPlayer ~= nil) then
		local electionNum = BestineElectionScreenPlay:getElectionNumber()
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "bestine_tusken_quest" .. electionNum)) then
			return true
		end
	end
	return false
end


function victorVisalisPhase2ConvoHandler:checkForStones(pPlayer)
	if (pPlayer == nil) then
		return false
	end
	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")
	if (pInventory ~= nil) then
		return (getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/carved_stone.iff", true) or getContainerObjectByTemplate(pInventory, "object/tangible/loot/quest/smooth_stone.iff", true))
	end
	return false
end

function victorVisalisPhase2ConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local electionNum = BestineElectionScreenPlay:getElectionNumber()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local electionWinner = getQuestStatus("bestine:election:electionWinner")

	if (screenID == "victor_inOffice") then
		if self:onTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","inOffice_onTuskenQuest") --How goes your work now that you're in office?
		elseif self:completedTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","tuskenquest_complete")--How goes your work now that you're in office?
		else
			clonedConversation:addOption("@conversation/victor_visalis:s_edafb11b","tuskenquest_intro")--How goes your work now that you're in office?
		end
		if self:hasTuskenHead(pPlayer) then
			if self:onTuskenQuest(pPlayer) then
				if BestineElectionScreenPlay:hasFullInventory(pPlayer) then
					clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","election_reward_noroom") --I have destroyed the intended target.
				else
					clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","destroyed_target") --I have destroyed the intended target.
				end
			elseif self:completedTuskenQuest(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_6641e79e","tusken_reward_given") --I have destroyed the intended target.
			end
		elseif self:onTuskenQuest(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_42c394e0","retell_tusken_quest") --I'm lost. What do I need to do?
			clonedConversation:addOption("@conversation/victor_visalis:s_cbb4f307","still_looking") --I'm still looking for our target.
			clonedConversation:addOption("@conversation/victor_visalis:s_f70821a3","quit_tusken_quest") --I quit!
		end

		if self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","found_stones") --I found these weird stones.
		end

		if BestineElectionScreenPlay:votingrewardCheck(pPlayer,"victor") then
			if self:receivedElectionReward(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","already_received_election_reward")--Hey wait! What about my reward for voting for you?
			elseif BestineElectionScreenPlay:hasFullInventory(pPlayer) then
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","election_reward_noroom")--Hey wait! What about my reward for voting for you?
			else
				clonedConversation:addOption("@conversation/victor_visalis:s_82af0027","give_election_reward")--Hey wait! What about my reward for voting for you?
			end
		end
elseif (screenID == "tuskenquest_complete") then
		if self:checkForStones(pPlayer) then
			clonedConversation:addOption("@conversation/victor_visalis:s_380817dd","tuskenquest_foundstones") --I found these weird stones.
		end
		clonedConversation:addOption("@conversation/victor_visalis:s_30e8118","endconvo_friendly") --Just checking up on things. Bye!
	elseif (screenID == "tuskenquest_accept") then
		self:giveTuskenQuest(pPlayer)
	elseif (screenID == "retell_tusken_quest") or (screenID == "still_looking") then
		self:tuskenWaypoint(pPlayer)
	elseif (screenID == "quit_tusken_quest") then
		self:removeTuskenQuest(pPlayer)
	elseif screenID == "destroyed_target" then
		self:giveTuskenReward(pPlayer)
	elseif screenID == "give_election_reward" then
		self:giveElectionReward(pPlayer)
	end
	return pConvScreen
end

function victorVisalisPhase2ConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local electionWinner = getQuestStatus("bestine:election:electionWinner")

	if (electionWinner == "victor") then
		return convoTemplate:getScreen("victor_inOffice")
	else
		return convoTemplate:getScreen("notInOffice_noElection")
	end
end
