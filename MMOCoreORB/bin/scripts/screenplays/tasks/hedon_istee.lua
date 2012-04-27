hedon_istee_screenplay = ScreenPlay:new {
	numberOfActs = 1,

	states = {
		quest1 = {started = 1, defeated = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64},
		quest3 = {started = 128, delivered = 256, completed = 512}
	},

	loc = {
		hedon = {x = 1390, z = 0, y = 3195},
		drog  = {x = 1553, z = 15, y = 3488},
		rath  = {x = 1800, z = 7, y = 3128},
		monk  = {x = 1560, z = 7, y = 2970}
	}
}

registerScreenPlay("hedon_istee_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function hedon_istee_screenplay:start()
	self:spawnActiveAreas()
	self:spawnMobiles()
end

function hedon_istee_screenplay:spawnActiveAreas()
	local pSereneFloaterArea = spawnSceneObject("tatooine", "object/active_area.iff", self.loc.monk.x, self.loc.monk.z, self.loc.monk.y, 0, 0, 0, 0, 0)

	if (pSereneFloaterArea ~= nil) then
		local activeArea = LuaActiveArea(pSereneFloaterArea)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "hedon_istee_screenplay", "notifyEnteredSereneFloaterArea", pSereneFloaterArea)
	end
end

function hedon_istee_screenplay:spawnMobiles()
	local pHedonIstee = spawnMobile("tatooine", "hedon_istee", 1, self.loc.hedon.x, self.loc.hedon.z, self.loc.hedon.y, 0, 0)
	local pDrognuz = spawnMobile("tatooine", "drognuz", 10, self.loc.drog.x, self.loc.drog.z, self.loc.drog.y, 0, 0)
	local pRathKana = spawnMobile("tatooine", "rath_kana", 60, self.loc.rath.x, self.loc.rath.z, self.loc.rath.y, 0, 0)
	local pSereneFloater = spawnMobile("tatooine", "serene_floater", 60, self.loc.monk.x, self.loc.monk.z, self.loc.monk.y, 0, 0)
	
	createObserver(OBJECTDESTRUCTION, "hedon_istee_screenplay", "notifyDrognuzDefeated", pDrognuz)
end

---
--Observer Notifications
---
function hedon_istee_screenplay:notifyEnteredSereneFloaterArea(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()

		if (self:hasState(player, self.states.quest3.started)) and (not self:hasState(player, self.states.quest3.defeated)) then
		end
	end
end

function hedon_istee_screenplay:notifyDrognuzDefeated(pDrognuz, pAttacker)
	local drognuz = LuaCreatureObject(pDrognuz)
	local attacker = LuaSceneObject(pAttacker)
	
	if (attacker:isCreatureObject()) then
		local creature = LuaCreatureObject(pAttacker)
		creature:sendSystemMessage("Killed drognuz")
	end

	return 1
end


--------------------------------------
--   Common functions                -
--------------------------------------
function hedon_istee_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end

	local val = player:hasScreenPlayState(state, "hedon_istee")

	if (val == 1) then
		return true
	end

	return false
end

function hedon_istee_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":hedon_istee:spawned:" .. key)

	if (val == 1) then
		return true
	end

	return false
end

function hedon_istee_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":hedon_istee:spawned:" .. key, 1)
end

function hedon_istee_screenplay:deleteSpawnedSetting(objectID, key)
	deleteData(objectID .. ":hedon_istee:spawned:" .. key)
end

function hedon_istee_screenplay:writeObjectData(objectID, key, value)
	if (objectID == nil) then
		return 0
	end

	writeData(objectID .. ":hedon_istee:" .. key, value)
end

function hedon_istee_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end

	return readData(objectID .. ":hedon_istee:" .. key)
end

function hedon_istee_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end

	deleteData(objectID .. ":hedon_istee:" .. key)
end

function hedon_istee_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "hedon_istee")
end



---
--Hedon Istee Conversation Handler
---
hedon_istee_handler = Object:new {
}

function hedon_istee_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	local player = LuaCreatureObject(conversingPlayer)
	local playerObjectPointer = player:getPlayerObject()

	if (screenID == "npc_2_1") then
		self:beginQuest1(player)
	elseif (screenID == "npc_2_2") then
		self:beginQuest2(player)
	elseif (screenID == "npc_2_3") then
		self:beginQuest3(player)
	elseif (screenID == "npc_reset") then
		self:resetQuest(player)
	end

	return conversationScreen
end

function hedon_istee_handler:beginQuest1(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--Waypoint to Drognuz
	playerObject:addWaypoint("tatooine", "Drognuz", "", hedon_istee_screenplay.loc.drog.x, hedon_istee_screenplay.loc.drog.y, WAYPOINTBLUE, true, true)

	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest1.started)
end

function hedon_istee_handler:beginQuest2(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_name_2", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_description_2", hedon_istee_screenplay.loc.djk.x, hedon_istee_screenplay.loc.djk.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest2.started)
end

function hedon_istee_handler:beginQuest3(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	--playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_name_3", "@static_npc/dathomir/dathomir_imperialprison_hedon_istee:waypoint_description_3", hedon_istee_screenplay.loc.djm.x, hedon_istee_screenplay.loc.djm.y, WAYPOINTBLUE, true, true)
	hedon_istee_screenplay:setState(player, hedon_istee_screenplay.states.quest3.started)
end

function hedon_istee_handler:resetQuest(player)
end

function hedon_istee_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	local conversingPlayer = LuaCreatureObject(pPlayer)
	local faction = conversingPlayer:getFaction()
	local pPlayerObject = conversingPlayer:getPlayerObject()
	local conversingObject = LuaSceneObject(pPlayer)
	local pInventory = conversingObject:getSlottedObject("inventory")
	local inventory = LuaSceneObject(pInventory)

	if (pPlayerObject == nil) then
		return nil
	end

	local playerObject = LuaPlayerObject(pPlayerObject)

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("nextQuest")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.delivered, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest3.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_3")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.defeated, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest2.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.completed, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.defeated, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_reward_1")
	end

	if (conversingPlayer:hasScreenPlayState(hedon_istee_screenplay.states.quest1.started, "hedon_istee") == 1) then
		return convoTemplate:getScreen("npc_work_1")
	end

	--We need to check skill points here maybe?
	--if (faction ~= 3679112276) then
	--return convoTemplate:getScreen("notyet")
	--end

	return convoTemplate:getScreen("npc_1_1") --First quest
end

function hedon_istee_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local player = LuaCreatureObject(pPlayer)
	local pConversationSession = player:getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then	
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end
