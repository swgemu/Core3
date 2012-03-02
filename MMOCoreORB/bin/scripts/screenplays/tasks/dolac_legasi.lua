dolac_legasi_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	loc = {
		dolac = {x = 0, z = 0, y = 0},
		prisoner = {x = -5866, z = 129, y = 809},
		djk = {x = -5699.5, z = 134.2, y = 850.7},
		nsspellweaver = {x = 0, z = 0, y = 0},
		nsprotector = {x = 0, z = 0, y = 0},
		djm = {x = -5650, z = 120, y = 630}
	},
	
	states = {
		quest1 = {started = 1, escorting = 2, completed = 8},
		quest2 = {started = 16, defeated = 32, completed = 64},
		quest3 = {started = 128, defeated1 = 256, defeated2 = 512, defeated3 = 1024, completed = 2048}
	}
}

registerScreenPlay("dolac_legasi_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function dolac_legasi_screenplay:start()
	self:spawnActiveAreas()
	self:spawnMobiles()
end

function dolac_legasi_screenplay:spawnActiveAreas()
	local pActiveArea1 = spawnSceneObject("dathomir", "object/active_area.iff", self.loc.prisoner.x, self.loc.prisoner.z, self.loc.prisoner.y, 0, 0, 0, 0, 0)
	local pActiveArea2 = spawnSceneObject("dathomir", "object/active_area.iff", self.loc.djk.x, self.loc.djk.z, self.loc.djk.y, 0, 0, 0, 0, 0)
	local pActiveArea3 = spawnSceneObject("dathomir", "object/active_area.iff", self.loc.djm.x, self.loc.djm.z, self.loc.djm.y, 0, 0, 0, 0, 0)
	
	if (pActiveArea1 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea1)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "dolac_legasi_screenplay", "notifyEnteredArea1", pActiveArea1)
	end
	
	if (pActiveArea2 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea2)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "dolac_legasi_screenplay", "notifyEnteredArea2", pActiveArea2)
	end
	
	if (pActiveArea3 ~= nil) then
		local activeArea = LuaActiveArea(pActiveArea3)
		activeArea:setRadius(50)
		activeArea:setNoBuildArea(true)
		createObserver(ENTEREDAREA, "dolac_legasi_screenplay", "notifyEnteredArea3", pActiveArea3)
	end
end

function dolac_legasi_screenplay:spawnMobiles()
	spawnMobile("dathomir", "dolac_legasi", 1, 2.3, 0.1, -3.6, -96, 5335776)
end

--------------------------------------
--   Common functions                -
--------------------------------------
function dolac_legasi_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "dolac_legasi")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function dolac_legasi_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":dolac_legasi:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function dolac_legasi_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":dolac_legasi:spawned:" .. key, 1)
end

function dolac_legasi_screenplay:deleteSpawnedSetting(objectID, key)
	deleteData(objectID .. ":dolac_legasi:spawned:" .. key)
end

function dolac_legasi_screenplay:writeObjectData(objectID, key, value)
	if (objectID == nil) then
		return 0
	end
	
	writeData(objectID .. ":dolac_legasi:" .. key, value)
end

function dolac_legasi_screenplay:readObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	return readData(objectID .. ":dolac_legasi:" .. key)
end

function dolac_legasi_screenplay:deleteObjectData(objectID, key)
	if (objectID == nil) then
		return 0
	end
	
	deleteData(objectID .. ":dolac_legasi:" .. key)
end

function dolac_legasi_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "dolac_legasi")
end

--------------------------------------
--   ActiveArea observers            -
--------------------------------------
function dolac_legasi_screenplay:notifyEnteredArea1(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (self:hasState(player, self.states.quest1.started)) and (not self:hasState(player, self.states.quest1.escorting)) then
			if (not self:hasSpawned(objectID, "prisoner")) then
				self:setSpawned(objectID, "prisoner")
				
				local pPrisoner = spawnMobile("dathomir", "dolac_escaped_prisoner", 0, self.loc.prisoner.x, self.loc.prisoner.z, self.loc.prisoner.y, 0, 0)
				local prisoner = LuaSceneObject(pPrisoner)
				
				local pTamer = spawnMobile("dathomir", "nightsister_rancor_tamer", 0, self.loc.prisoner.x - 10, self.loc.prisoner.z, self.loc.prisoner.y + 3, 0, 0)
				local tamer = LuaSceneObject(pTamer)
				
				self:writeObjectData(objectID, "prisoner", prisoner:getObjectID())
				self:writeObjectData(objectID, "tamer", tamer:getObjectID())
				self:writeObjectData(tamer:getObjectID(), "questOwnerID", objectID)
				
				createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedTamer", pTamer)
				createObserver(OBJECTINRANGEMOVED, "dolac_legasi_screenplay", "notifyPrisonerBark", pPrisoner)
				createObserver(STOPCONVERSATION, "dolac_legasi_screenplay", "notifyEscortStarted", pPrisoner)
			end
		end
	end
	
	return 0
end

function dolac_legasi_screenplay:notifyEnteredArea2(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)

	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
	
		if (self:hasState(player, self.states.quest2.started)) and (not self:hasState(player, self.states.quest2.defeated)) then
			if (not self:hasSpawned(objectID, "shadowstone")) then
				self:setSpawned(objectID, "shadowstone")
				
				local pDjk = spawnMobile("dathomir", "dark_jedi_knight", 0, self.loc.djk.x, self.loc.djk.z, self.loc.djk.y, 0, 0)
				local djk = LuaSceneObject(pDjk)
				
				self:writeObjectData(objectID, "djk", djk:getObjectID())
				self:writeObjectData(djk:getObjectID(), "questOwnerID", objectID)
				
				createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedKnight", pDjk)
			end
		end
	end
	
	return 0
end

function dolac_legasi_screenplay:notifyEnteredArea3(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (self:hasState(player, self.states.quest3.started)) and (not self:hasState(player, self.states.quest3.completed)) then
			if (not self:hasState(player, self.states.quest3.defeated1)) then
				if (not self:hasSpawned(objectID, "spellweaver")) then
					self:setSpawned(objectID, "spellweaver")
					
					local pSpellweaver = spawnMobile("dathomir", "nightsister_spell_weaver", 0, self.loc.djm.x, self.loc.djm.z, self.loc.djm.y, 0, 0)
					local spellweaver = LuaSceneObject(pSpellweaver)
					
					if (pSpellweaver ~= nil) then
						self:writeObjectData(objectID, "spellweaver", spellweaver:getObjectID())
						self:writeObjectData(spellweaver:getObjectID(), "questOwnerID", objectID)
						createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedSpellweaver", pSpellweaver)
					end
				end
				
			elseif (not self:hasState(player, self.states.quest3.defeated2)) then
				if (not self:hasSpawned(objectID, "protectors")) then
					self:setSpawned(objectID, "protectors")
					
					local pProtector1 = spawnMobile("dathomir", "nightsister_protector", 0, self.loc.djm.x, self.loc.djm.z, self.loc.djm.y, 0, 0)
					local pProtector2 = spawnMobile("dathomir", "nightsister_protector", 0, self.loc.djm.x, self.loc.djm.z, self.loc.djm.y, 0, 0)
					local protector1 = LuaSceneObject(pProtector1)
					local protector2 = LuaSceneObject(pProtector2)
					
					self:writeObjectData(objectID, "protector1", protector1:getObjectID())
					self:writeObjectData(objectID, "protector2", protector2:getObjectID())
					self:writeObjectData(protector1:getObjectID(), "questOwnerID", objectID)
					self:writeObjectData(protector1:getObjectID(), "internalID", "protector1")
					self:writeObjectData(protector2:getObjectID(), "questOwnerID", objectID)
					self:writeObjectData(protector2:getObjectID(), "internalID", "protector2")
					
					createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedProtector", pProtector1)
					createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedProtector", pProtector2)
				end
			elseif (not self:hasState(player, self.states.quest3.defeated3)) then
				if (not self:hasSpawned(objectID, "djm")) then
					self:setSpawned(objectID, "djm")
					
					local pDjm = spawnMobile("dathomir", "dark_jedi_master", 0, self.loc.djm.x, self.loc.djm.z, self.loc.djm.y, 0, 0)
					local djm = LuaSceneObject(pDjm)
					
					self:writeObjectData(objectID, "djm", djm:getObjectID())
					self:writeObjectData(djm:getObjectID(), "questOwnerID", objectID)
					
					createObserver(OBJECTDESTRUCTION, "dolac_legasi_screenplay", "notifyDefeatedMaster", pDjm)
				end
			end
		end
	end
	
	return 0
end

--------------------------------------
--   Destruction Observers           -
--------------------------------------
function dolac_legasi_screenplay:notifyDefeatedTamer(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
	
	--TODO: We want to allow the prisoner to talk now.
	
	self:deleteObjectData(objectID, "tamer")
	self:deleteObjectData(victim:getObjectID(), "questOwnerID")
	
	return 1
end

function dolac_legasi_screenplay:notifyDefeatedKnight(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
	
	local ownerObject = LuaSceneObject(pOwner)
	local ownerCreature = LuaCreatureObject(pOwner)
	
	local pInventory = ownerObject:getSlottedObject("inventory")
	
	--Sith Altar
	local pSithAltar = giveItem(pInventory, "object/tangible/mission/quest_item/dolac_legasi_q2_needed.iff", -1)
	
	if (pSithAltar == nil) then
		return 0
	end
	
	local sithAltar = LuaSceneObject(pSithAltar)
	sithAltar:sendTo(pOwner)
	
	--Incase the server resets, we need to keep the object id of the sith altar persistent, to avoid having to loop through inventory later.
	writeScreenPlayData(pOwner, "dolac_legasi", "sithAltarID", sithAltar:getObjectID())
	
	self:setState(ownerCreature, self.states.quest2.defeated)
	
	return 1
end

function dolac_legasi_screenplay:notifyDefeatedSpellweaver(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
	
	local ownerCreature = LuaCreatureObject(pOwner)
	
	self:setState(ownerCreature, self.states.quest3.defeated1)
	
	self:deleteObjectData(objectID, "spellweaver")
	self:deleteObjectData(victim:getObjectID(), "questOwnerID")
	
	return 1
end

function dolac_legasi_screenplay:notifyDefeatedProtector(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
	
	local ownerCreature = LuaCreatureObject(pOwner)
	
	self:setState(ownerCreature, self.states.quest3.defeated2)
	
	local internalID = self:readObjectData(victim:getObjectID(), "internalID")
	self:deleteObjectData(objectID, internalID)
	self:deleteObjectData(victim:getObjectID(), "questOwnerID")
	self:deleteObjectData(victim:getObjectID(), "internalID")
	
	return 1
end

function dolac_legasi_screenplay:notifyDefeatedMaster(pVictim, pAttacker)
	local victim = LuaCreatureObject(pVictim)
	local ownerID = self:readObjectData(victim:getObjectID(), "questOwnerID")
	local pOwner = getCreatureObject(ownerID)
	
	if (pOwner == nil) then
		return 0;
	end
	
	local ownerCreature = LuaCreatureObject(pOwner)
	
	self:setState(ownerCreature, self.states.quest3.defeated3)
	
	self:deleteObjectData(objectID, "djm")
	self:deleteObjectData(victim:getObjectID(), "questOwnerID")
	
	return 1
end


--------------------------------------
--   Movement Observers              -
--------------------------------------
function dolac_legasi_screenplay:notifyPrisonerBark(pPrisoner, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local prisoner = LuaCreatureObject(pPrisoner)
		local distance = prisoner:getDistanceTo(pMovingObject)
		
		if (distance == 0 or distance > 16) then
			return 0
		end
		
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
			
		if (self:hasState(player, self.states.quest1.started)) and (not self:hasState(player, self.states.quest1.escorted)) then
			if (self:hasSpawned(objectID, "prisoner")) then
				if (self:readObjectData(objectID, "prisoner_spoken") ~= 1) then
					spatialChat(pPrisoner, "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_takeme_1") --Can you see them? The wraiths? There is no escaping them! They will always be there!
					self:writeObjectData(objectID, "prisoner_spoken", 1)
				
					return 1
				end
			end
		end
	end
	
	return 0
end

function dolac_legasi_screenplay:notifyEscortStarted(pPrisoner, pPlayer)
	local prisonerCreature = LuaCreatureObject(pPrisoner)
	local prisonerAi = LuaAiAgent(pPrisoner)
	local player = LuaCreatureObject(pPlayer)
	
	local distance = prisonerCreature:getDistanceTo(pPlayer)
	
	if (distance == 0 or distance > 32) then
		return 0
	end
	
	prisonerAi:setFollowObject(pPlayer)
	
	self:setState(player, self.states.quest1.escorting)
	
	return 1
end

--------------------------------------
--   Data cleanup functions          -
--------------------------------------
function dolac_legasi_screenplay:despawnQuest1(objectID)
	local prisonerID = self:readObjectData(objectID, "prisoner")
	local tamerID = self:readObjectData(objectID, "tamer")
	
	local pPrisoner = getCreatureObject(prisonerID)
	local pTamer = getCreatureObject(tamerID)
	
	if (pPrisoner ~= nil) then
		local prisoner = LuaSceneObject(pPrisoner)
		prisoner:destroyObjectFromWorld()
		prisoner:destroyObjectFromDatabase()
	end
	
	if (pTamer ~= nil) then
		local tamer = LuaSceneObject(pTamer)
		tamer:destroyObjectFromWorld()
		tamer:destroyObjectFromDatabase()
	end
	
	self:deleteObjectData(objectID, "prisoner")
	self:deleteObjectData(objectID, "tamer")
	self:deleteObjectData(objectID, "prisoner_spoken")
	self:deleteSpawnedSetting(objectID, "prisoner")
	self:deleteObjectData(tamerID, "questOwnerID")
end

function dolac_legasi_screenplay:despawnQuest2(objectID, pSithAltar)
	local djkID = self:readObjectData(objectID, "djk")
	local pDjk = getCreatureObject(djkID)
	
	if (pDjk ~= nil) then
		local djk = LuaSceneObject(pDjk)
		djk:destroyObjectFromWorld()
		djk:destroyObjectFromDatabase()
	end 

	if (pSithAltar ~= nil) then
		local sithAltar = LuaSceneObject(pSithAltar)
		sithAltar:destroyObjectFromWorld()
		sithAltar:destroyObjectFromDatabase()
	end
	
	self:deleteObjectData(objectID, "djk")
	self:deleteObjectData(djkID, "questOwnerID")
	self:deleteSpawnedSetting(objectID, "shadowstone")
end

function dolac_legasi_screenplay:despawnQuest3(objectID)
	local spellweaverID = self:readObjectData(objectID, "spellweaver")
	local protector1ID = self:readObjectData(objectID, "protector1")
	local protector2ID = self:readObjectData(objectID, "protector2")
	local djmID = self:readObjectData(objectID, "djm")
	
	local pSpellweaver = getCreatureObject(spellweaverID)
	
	if (pSpellweaver ~= nil) then
		local spellweaver = LuaSceneObject(pSpellweaver)
		spellweaver:destroyObjectFromWorld()
		spellweaver:destroyObjectFromDatabase()
	end
	
	local pProtector1 = getCreatureObject(protector1ID)
	
	if (pProtector1 ~= nil) then
		local protector1 = LuaSceneObject(pProtector1)
		protector1:destroyObjectFromWorld()
		protector1:destroyObjectFromDatabase()
	end
	
	local pProtector2 = getCreatureObject(protector2ID)
	
	if (pProtector2 ~= nil) then
		local protector2 = LuaSceneObject(pProtector2)
		protector2:destroyObjectFromWorld()
		protector2:destroyObjectFromDatabase()
	end
	
	local pDjm = getCreatureObject(djmID)
	
	if (pDjm ~= nil) then
		local djm = LuaSceneObject(pDjm)
		djm:destroyObjectFromWorld()
		djm:destroyObjectFromDatabase()
	end
	
	self:deleteSpawnedSetting("spellweaver")
	self:deleteSpawnedSetting("protectors")
	self:deleteSpawnedSetting("djm")
	self:deleteObjectData(objectID, "spellweaver")
	self:deleteObjectData(objectID, "protector1")
	self:deleteObjectData(objectID, "protector2")
	self:deleteObjectData(objectID, "djm")
	self:deleteObjectData(spellweaverID, "questOwnerID")
	self:deleteObjectData(protector1ID, "questOwnerID")
	self:deleteObjectData(protector1ID, "internalID")
	self:deleteObjectData(protector2ID, "questOwnerID")
	self:deleteObjectData(protector2ID, "internalID")
	self:deleteObjectData(djmID, "questOwnerID")
end

--------------------------------------
--   Reward/Completions              -
--------------------------------------
function dolac_legasi_screenplay:rewardQuest1(player, playerObject)
	self:despawnQuest1(player:getObjectID())
	
	player:addCashCredits(350, true)
	playerObject:increaseFactionStanding("imperial", 10)
	
	self:setState(player, self.states.quest1.completed)
end

function dolac_legasi_screenplay:rewardQuest2(player, playerObject, pSithAltar)
	self:despawnQuest2(player:getObjectID(), pSithAltar)
	
	player:addCashCredits(450, true)
	playerObject:increaseFactionStanding("imperial", 10)
	
	self:setState(player, self.states.quest2.completed)
end

function dolac_legasi_screenplay:rewardQuest3(player, playerObject)
	self:despawnQuest3(player:getObjectID())
	
	player:addCashCredits(1800, true)
	playerObject:increaseFactionStanding("imperial", 20)
	
	clearScreenPlayData(player, "dolac_legasi")
	
	self:setState(player, self.states.quest3.completed)
end






--------------------------------------
-- Dolac Legasi Conversation Handler -
--------------------------------------
dolac_legasi_handler = Object:new {
}

function dolac_legasi_handler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
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

function dolac_legasi_handler:beginQuest1(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_name_1", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_description_1", dolac_legasi_screenplay.loc.prisoner.x, dolac_legasi_screenplay.loc.prisoner.y, WAYPOINTBLUE, true, true)

	dolac_legasi_screenplay:setState(player, dolac_legasi_screenplay.states.quest1.started)
end

function dolac_legasi_handler:beginQuest2(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_name_2", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_description_2", dolac_legasi_screenplay.loc.djk.x, dolac_legasi_screenplay.loc.djk.y, WAYPOINTBLUE, true, true)
	dolac_legasi_screenplay:setState(player, dolac_legasi_screenplay.states.quest2.started)
end

function dolac_legasi_handler:beginQuest3(player)
	local pPlayerObject = player:getPlayerObject()
	local playerObject = LuaPlayerObject(pPlayerObject)

	playerObject:addWaypoint("dathomir", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_name_3", "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:waypoint_description_3", dolac_legasi_screenplay.loc.djm.x, dolac_legasi_screenplay.loc.djm.y, WAYPOINTBLUE, true, true)
	dolac_legasi_screenplay:setState(player, dolac_legasi_screenplay.states.quest3.started)
end

function dolac_legasi_handler:resetQuest(player)
end

function dolac_legasi_handler:getInitialScreen(pPlayer, npc, pConversationTemplate)
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
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest3.completed, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("nextQuest")
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest3.defeated3, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_reward_3")
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest3.started, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_work_3") --Already working for me.
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest2.completed, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_1_3")
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest2.defeated, "dolac_legasi") == 1) then
		--At this point, he should have the Sith Altar. Check his inventory.
		local sithAltarID = readScreenPlayData(pPlayer, "dolac_legasi", "sithAltarID")
		local pSithAltar = inventory:getContainerObjectById(sithAltarID)
	
		if (pSithAltar ~= nil) then
			dolac_legasi_screenplay:rewardQuest2(conversingPlayer, playerObject, pSithAltar)
	
			return convoTemplate:getScreen("npc_reward_2")
		end
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest2.started, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_work_2") --Already working for me.
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest1.completed, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_1_2")
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest1.escorting, "dolac_legasi") == 1) then
		dolac_legasi_screenplay:rewardQuest1(conversingPlayer, playerObject)
	
		return convoTemplate:getScreen("npc_reward_1")
	end
	
	if (conversingPlayer:hasScreenPlayState(dolac_legasi_screenplay.states.quest1.started, "dolac_legasi") == 1) then
		return convoTemplate:getScreen("npc_work_1") --Already working for me.
	end
	
	--If they are not an Imperial, then show them a random "don't know you" message.
	if (faction ~= 3679112276) then
		local val = math.random(2)
	
		if (val == 1) then
			return convoTemplate:getScreen("dontknowyou_1")
		else
			return convoTemplate:getScreen("dontknowyou_3")
		end
	end
	
	--TODO: Check for Mozo Bondog quests.
	
	return convoTemplate:getScreen("npc_1_1") --First quest
end





function dolac_legasi_handler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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
