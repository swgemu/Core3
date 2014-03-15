--Additional Includes...
-- Spawns
includeFile("dungeon/corvette/spawns/imperial.lua")

--Item-related functions.
includeFile("dungeon/corvette/corvette_items.lua")

-- Convo handlers.
--includeFile("dungeon/corvette/conversation/ticketGiverHandler.lua")

-- Storage for state globals.
stages = { 
	initializeConversation = 1, 
	completedTask = 2,
	receivedTicket = 4,
	completedMission = 8
}



-- The main screenplay.
CorvetteMain = ScreenPlay:new {
	screenplayName = CorvetteMain,
}



registerScreenPlay("CorvetteMain", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function CorvetteMain:start()
	-- Spawn the start NPCs per faction, per mission.


	if (isZoneEnabled("corellia")) then
		-- Rebel Start 1.
		--spawnMobile("corellia", "crowley", 0, 3404, 15, 3092, 110, 0) -- -3404 3092

		-- Rebel Start 2.
		--spawnMobile("corellia", "pashna", 0, 6772, 15, -5697, 110, 0) -- 6772 -5697

		-- Rebel Start 3.
		--spawnMobile("corellia", "adar", 0, -5448, 15, -2674, 110, 0) -- -5448 -2674
	end


	if (isZoneEnabled("naboo")) then
		-- Imperial Start 1.
		spawnMobile("naboo", "lt_velso", 0, 22, 0.2, -20, 180, 1418874) -- 2405 -3967

		-- Imperial Travel Point.
		--spawnMobile("naboo", "cor_imperial_pilot", 0, 2433, 292, -3887, 160, 0)
	end

	if (isZoneEnabled("tatooine")) then
		-- Imperial Start 2.
		spawnMobile("tatooine", "sabol", 0, -1291, 0, -3539, 110, 0) -- -1291 -3539

		-- Imperial Start 3.
		--spawnMobile("tatooine", "darkstone", 0, -5313, 0, 2662, 110, 0) -- -5313 2662

		-- Neutral Start 1.
		--spawnMobile("tatooine", "bruce_mcbrain", 0, -5880, 0, -6220, 110, 0) -- -5880 â€“6220

		-- Neutral Start 2.
		--spawnMobile("tatooine", "bronell", 0, -5880, 0, -6220, 110, 0) -- -5880 â€“6220

		-- Neutral Start 3.
		--spawnMobile("tatooine", "yondalla", 0, -5150, 0, -6588, 110, 0) -- -5150 -6588
	end
end

--------------------------------------
--      Travel Functions.            -
--------------------------------------
function CorvetteMain:travelToDungeon(pCreature, pSui, cancelPressed)
	if (pCreature ~= nil) and (not cancelPressed) then
		local player = LuaCreatureObject(pCreature)
		local playerScene = LuaSceneObject(pCreature)
		if (player:isImperial()) then
			playerScene:switchZone("dungeon1", -20, 0, 0, 4336197)
		elseif (player:isNeutral()) then
			playerScene:switchZone("dungeon1", -20, 0, 0, 4335862)
		elseif (player:isRebel()) then
			playerScene:switchZone("dungeon1", -20, 0, 0, 4336532)
		end
	end
end

function CorvetteMain:findAvailableDungeon(pFaction)
	local faction = readStringData("corvette:faction")
	
	if (faction == "rebel") and (pFaction == "rebel") then
		return false
	elseif (faction == "neutral") and (pFaction == "neutral") then
		return false
	elseif (faction == "imperial") and (pFaction == "imperial") then
		return false
	else
		return true
	end

end

--------------------------------------
--     Instancing Functions.         -
--------------------------------------

function CorvetteMain:startInstance(pFaction, pPlayerOwner)
	writeStringData("corvette:faction", pFaction)

	local ownerCreature = LuaCreatureObject(pPlayerOwner)

	-- You have 1 hour to complete your task.

	if (ownerCreature:isGrouped()) then
		local gSize = ownerCreature:getGroupSize()
		for i = 0, gSize do
			local groupMember = player:getGroupMember(i)
			if (groupMember ~= nil) then
				if (groupMember ~= pPlayerOwner) then
					ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
					createEvent(360000, "CorvetteMain", "instanceFailed", groupMember)
				else
					ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
					createEvent(360000, "CorvetteMain", "instanceFailed", pPlayerOwner)
					createObserver(OBJECTDESTRUCTION, "CorvetteMain", "ownerDied", pPlayerOwner) -- Reset mobs if instance leader dies.
				end
			end
		end
	else
		ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
		createEvent(360000, "CorvetteMain", "instanceFailed", pPlayerOwner)
		createObserver(OBJECTDESTRUCTION, "CorvetteMain", "ownerDied", pPlayerOwner) -- Reset mobs if instance leader dies.
	end
		
	local state = ownerCreature:getScreenPlayState("CorvetteType")		
	
	if (pFaction == "imperial") then
		if (state == 1) then
		-- Destroy Mission: Spawn Scene Objects.
		self:spawnDestroyObjectives()
		elseif (state == 2) then
		-- Assassin Mission: Spawn Additional Mobile.
		elseif (state == 4) then
		-- Rescue Mission: Spawn Additional Mobiles.
		end
	-- Spawn general static mobiles global to imperial missions.
	self:spawnImperialGlobalMobiles()
	-- Spawn global scene objects that are the same no matter the faction.
	self:spawnImperialSceneObjects()
	elseif (pFaction == "neutral") then
	elseif (pFaction == "rebel") then
	end

end

function CorvetteMain:spawnImperialSceneObjects()

	local spawnedSceneObject = LuaSceneObject(nil)
	
	for i,v in ipairs(imperial.globalSceneObjects) do
		pSpawnedSceneObject = spawnSceneObject("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9])

		if (pSpawnedSceneObject ~= nil) then
			spawnedSceneObject:_setObject(pSpawnedSceneObject)

			if (v[10] ~= nil) then
				spawnedSceneObject:setCustomObjectName(v[10])
			end

			if (v[11] ~= nil) then
				spawnedSceneObject:setObjectMenuComponent(v[11])
			end
		end
	end

end

function CorvetteMain:ownerDied(pOwner, pKiller)

	-- Leader died, respawn everything that they killed.

	
	local creatureObject = LuaCreatureObject(pOwner)


	if (creatureObject:isImperial()) then
		for i,v in ipairs(self.spawnMapImperial) do		
			local checkIfKilled = readData(i .. ":imperial:vette:objid")
			if (checkIfKilled == 0) then
				local spawnedSceneObject = LuaSceneObject(nil)
				local spawnedPointer = spawnMobile("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
				if (spawnedPointer ~= nil) then
					spawnedSceneObject:_setObject(spawnedPointer)
					writeData(i .. ":imperial:vette:objid", spawnedSceneObject:getObjectID())
					createObserver(OBJECTDESTRUCTION, "CorvetteMain", "spawnKilled", spawnedPointer)
				end
			end
		end
	elseif (creatureObject:isNeutral()) then
	elseif (creatureObject:isRebel()) then
	end

end

function CorvetteMain:spawnKilled(pSpawn, pKiller)
	local creatureObject = LuaCreatureObject(pKiller)
	local spawnCreature = LuaSceneObject(pSpawn)


	if (creatureObject:isImperial()) then
		for i,v in ipairs(self.spawnMapImperial) do		
			local checkIfKilled = readData(i .. ":imperial:vette:objid")
			if (checkIfKilled == spawnCreature:getObjectID()) then
				deleteData(i .. ":imperial:vette:objid")
			end
		end
	elseif (creatureObject:isNeutral()) then
	elseif (creatureObject:isRebel()) then
	end
	
end

function CorvetteMain:instanceFailed(pPlayer)
	if (pPlayer == nil) then
		createEvent(60000, "CorvetteMain", "instanceFailed", pPlayer)
	end

	local playerCreature = LuaCreatureObject(pPlayer)

	writeStringData("corvette:faction", "")

	-- Kick em out...
	local playerScene = LuaSceneObject(pPlayer)
	local pCell = playerScene:getParent()
	local actualCell = LuaSceneObject(pCell)
	local pSceneObject = getSceneObject(actualCell:getParentID())
	
	local sceneObject = LuaSceneObject(pSceneObject)

	playerCreature:sendSystemMessage("Mission failed. You will be taken back to your shuttle point...")
	
	if (sceneObject:getTemplateObjectPath() == "object/building/general/space_dungeon_corellian_corvette_imperial.iff") then
		-- Going back to Imperial Spawn.
		
		playerScene:switchZone("naboo", 2434, 292, -3924, 0)

	elseif (sceneObject:getTemplateObjectPath() == "object/building/general/space_dungeon_corellian_corvette.iff") then
		-- Going back to Neutral Spawn.

		playerScene:switchZone("tatooine", 1000, 0, -1000, 0)
	
	elseif (sceneObject:getTemplateObjectPath() == "object/building/general/space_dungeon_corellian_corvette_rebel.iff") then
		-- Going back to Rebel Spawn.

		playerScene:switchZone("corellia", 1000, 0, -1000, 0)
	end

		-- Clean up instance of all spawned mobiles and objects.
	if (playerCreature:isImperial()) then
		for i,v in ipairs(self.spawnMapImperial) do
			local deletionCheck = readData(i .. ":imperial:vette:objid")
			local creatureToRemove = getCreatureObject(deletionCheck)

			if (creatureToRemove ~= nil) then
				creatureToRemove:destroyObjectFromWorld()
				creatureToRemove:destroyObjectFromDatabase()
				deleteData(i .. ":imperial:vette:objid")
			end
		end
	elseif (playerCreature:isNeutral()) then
		
	elseif (playerCreature:isRebel()) then

	end
	
end

function CorvetteMain:spawnImperialGlobalMobiles()
	local spawnedSceneObject = LuaSceneObject(nil)

	for i,v in ipairs(imperial.globalMobiles) do
		spawnedPointer = spawnMobile("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		
		if (spawnedPointer ~= nil) then
			spawnedSceneObject:_setObject(spawnedPointer)
			writeData(i ..":imperial:vette:objid", spawnedSceneObject:getObjectID())
			createObserver(OBJECTDESTRUCTION, "CorvetteMain", "spawnKilled", spawnedPointer)
		end
	end
end

function CorvetteMain:spawnDestroyObjectives()

	local spawnedSceneObject = LuaSceneObject(nil)
	
	for i,v in ipairs(imperial.destroySpawns) do
		pSpawnedSceneObject = spawnSceneObject("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9])

		if (pSpawnedSceneObject ~= nil) then
			spawnedSceneObject:_setObject(pSpawnedSceneObject)
			spawnedSceneObject:setCustomObjectName(v[10])
			spawnedSceneObject:setObjectMenuComponent(v[11])
		end
	end
end

--------------------------------------
--     Sui Callback Functions.       -
--------------------------------------

function CorvetteMain:EngineSuiCallback(pCreature, pSui, cancelPressed, okPressed)
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)

	if (cancelPressed) then
	elseif (okPressed) then
	-- Set Engines to 80.

	-- Send the message.
		local setting = 80
		player:sendSystemMessage("You have set the engine to " .. setting .. "%.")

	-- Set it in the screenplay.
		self:setShipComponent("engine", setting, pCreature)
	end
end

function CorvetteMain:FuelSuiCallback(pCreature, pSui, cancelPressed, otherPressed, okPressed)
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)

	-- Set Fuel.
	if (cancelPressed) then
	elseif (okPressed) then
	-- Send the message.
		local setting = 80
		player:sendSystemMessage("@dungeon/corvette:fuel_80")

	-- Set it in the screenplay.
		self:setShipComponent("fuel", setting, pCreature)
	end
end

function CorvetteMain:HyperdriveSuiCallback(pCreature, pSui, cancelPressed, otherPressed, okPressed)
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)

	-- Set Hyperdrive
	if (cancelPressed) then
	elseif (okPressed) then
	-- Send the message.
		local setting = 80
		player:sendSystemMessage("@dungeon/corvette:hypr_60")

	-- Set it in the screenplay.
		self:setShipComponent("hyperdrive", setting, pCreature)
	end
end


function CorvetteMain:setShipComponent(componentName, setting, pCreature)
	
	local player = LuaCreatureObject(pCreature)

	if (componentName == "engine") then
		writeData("corvette:engineSetTo", setting)
		player:sendSystemMessage("Engine is at " .. setting)
	elseif (componentName == "fuel") then
		writeData("corvette:fuelSetTo", setting)
		player:sendSystemMessage("Fuel is at " .. setting)
	elseif (componentName == "hyperdrive") then
		writeData("corvette:hyperdriveSetTo", setting)
		player:sendSystemMessage("Hyperdrive is at " .. setting)
	end
	
	local engineSetTo = readData("corvette:engineSetTo")
	local hyperdriveSetTo = readData("corvette:hyperdriveSetTo")
	local fuelSetTo = readData("corvette:fuelSetTo")

	if ((engineSetTo == 40) and (hyperdriveSetTo == 20) and (fuelSetTo == 80)) then
		-- Done!
		player:sendSystemMessage("@dungeon/corvette:blew_up")
		player:setScreenPlayState(1, "CorvetteMissionStatus")
	else
		player:sendSystemMessage("@dungeon/corvette:engine_result")
	end
end

corvette_destroy_object_menucomponent = { }

function corvette_destroy_object_menucomponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local player = LuaCreatureObject(pPlayer)

	menuResponse:addRadialMenuItem(20, 3, "Use") -- Use the item.

end

function corvette_destroy_object_menucomponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end

	
	if (selectedID == 20) then	
		-- Base the callback on the template name.
		local luaSceneObject = LuaSceneObject(pSceneObject)
		local creatureObject = LuaCreatureObject(pPlayer)
		local creatureSceneObject = LuaSceneObject(pPlayer)

		local objectID = luaSceneObject:getObjectID()
		local suiManager = LuaSuiManager()

		-- Engine.
		if (luaSceneObject:getCustomObjectName() == "Engine Controls") then
			suiManager:sendMessageBox(pSceneObject, pPlayer, "@dungeon/corvette:engine_title", "@dungeon/corvette:engine_settings", "@ok",  "CorvetteMain", "EngineSuiCallback")

		-- Fuel.
		elseif (luaSceneObject:getCustomObjectName() == "Fuel Controls") then
			suiManager:sendMessageBox(pSceneObject, pPlayer, "@dungeon/corvette:fuel_title", "@dungeon/corvette:fuel_settings", "@ok", "CorvetteMain", "FuelSuiCallback")

		-- Hyperdrive.
		elseif (luaSceneObject:getCustomObjectName() == "Hyperdrive Controls") then
			suiManager:sendMessageBox(pSceneObject, pPlayer, "@dungeon/corvette:hyperdrive_title", "@dungeon/corvette:hyperdrive_settings", "@ok", "CorvetteMain", "HyperdriveSuiCallback")

		end
	end
			
	return 0
end

function CorvetteMain:respawnItems(pSceneObject)
	if (pSceneObject ~= nil) then
		local container = LuaCreatureObject(pSceneObject)
		local objectID = container:getObjectID()
			deleteData(objectID .. ":corvette:items:spawned")
	end
end

function CorvetteMain:giveAuthorizationForm(pConversingPlayer, pFaction)
	if (pConversingPlayer ~= nil) then
		local player = LuaCreatureObject(pConversingPlayer)
		local playerInv = LuaSceneObject(pConversingPlayer)

		local pInv = playerInv:getSlottedObject("inventory")
		local pItem = giveItem(pInv, "object/tangible/travel/travel_ticket/dungeon_ticket.iff", -1)

		if (pFaction == "imperial") then
			setDungeonTicketAttributes(pItem, "naboo", "imperial", "imperial")
		elseif (pFaction == "neutral") then
			setDungeonTicketAttributes(pItem, "tatooine", "neutral", "neutral")
		elseif (pFaction == "rebel") then
			setDungeonTicketAttributes(pItem, "tatooine", "rebel", "rebel")
		end
			
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(player:_getObject())
			end
	end
end


