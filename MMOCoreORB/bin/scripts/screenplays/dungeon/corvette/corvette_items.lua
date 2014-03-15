--------------------------------------
--      Item Functions.              -
--------------------------------------


searchable_object_menucomponent = { }

function searchable_object_menucomponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local player = LuaCreatureObject(pPlayer)
	
	if (player:hasScreenPlayState(CorvetteScreenPlay.states.stages.stageOne, "CorvetteScreenPlay") == 1) then
		menuResponse:addRadialMenuItem(121, 3, "Search") -- Get the item.
	end
end

function searchable_object_menucomponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end
	
	local luaSceneObject = LuaSceneObject(pSceneObject)
	local creatureObject = LuaCreatureObject(pPlayer)
	local creatureSceneObject = LuaSceneObject(pPlayer)

	local objectID = luaSceneObject:getObjectID()
	local spawnedCheck = readData(objectID .. ":corvette:items:spawned")
	
	if (selectedID == 121) then
		if (spawnedCheck == 1) then
		    creatureObject:sendSystemMessage("You could not find anything of use here.")
		    return 0
		end


		local pInventory = creatureSceneObject:getSlottedObject("inventory")
		local item1 = nil
		local item2 = nil
		local item3 = nil
		
		-- Base the item received on the template name of the object searched.	

			-- Imperial types.
			if (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_destroy_01.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_destroy_02.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_destroy_03.iff") then
				item1 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff"
				item2 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff"
				item3 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff"

		    elseif (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_assassination_01.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_assassination_02.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_assassination_03.iff") then
				item1 = "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler01.iff"
				item2 = "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_filler02.iff"
				item3 = "object/tangible/loot/dungeon/corellian_corvette/imperial_assassin_intel.iff"

		    elseif (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_rescue_01.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_rescue_02.iff") or
			   (luaSceneObject:getTemplateObjectPath() == "object/tangible/dungeon/corellian_corvette/corvette_search_imperial_rescue_03.iff") then
				item1 = "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_filler01.iff"
				item2 = "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_filler02.iff"
				item3 = "object/tangible/loot/dungeon/corellian_corvette/imperial_rescue_intel.iff"
		    end
		
		
		if (pInventory ~= nil) then
			local rand = math.random(2)
		
			if (rand == 0) then
				local pItem = giveItem(pInventory, item1, -1)
			
				if (pItem ~= nil) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					createEvent(3600000, "CorvetteScreenPlay", "respawnItems", pSceneObject)
					writeData(objectID .. ":corvette:items:spawned", 1)
				end

			elseif (rand == 1) then
				local pItem = giveItem(pInventory, item2, -1)
			
				if (pItem ~= nil) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					createEvent(3600000, "CorvetteScreenPlay", "respawnItems", pSceneObject)
					writeData(objectID .. ":corvette:items:spawned", 1)
				end

			elseif (rand == 2) then
				local pItem = giveItem(pInventory, item3, -1)
			
				if (pItem ~= ni) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					createEvent(3600000, "CorvetteScreenPlay", "respawnItems", pSceneObject)
					writeData(objectID .. ":corvette:items:spawned", 1)
				end
			end	
		end
		
		
	end
			
	return 0
end

escape_pod_menu_component = { }

function escape_pod_menu_component:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "Use") -- Use the item.
	
	local playerCreature = LuaCreatureObject(pPlayer)

	playerCreature:sendSystemMessage("@dungeon/corvette:escape_pod_message")
	
end

function escape_pod_menu_component:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or pSceneObject == nil) then
		return 0
	end
	
	if (selectedID ~= 20) then
		return 0
	end
	
	local playerCreature = LuaCreatureObject(pPlayer)

	writeStringData("corvette:faction", "")

	-- Kick em out...
	local playerScene = LuaSceneObject(pPlayer)
	local pCell = playerScene:getParent()
	local actualCell = LuaSceneObject(pCell)
	local pSceneObject = getSceneObject(actualCell:getParentID())
	
	local sceneObject = LuaSceneObject(pSceneObject)

	local state = playerCreature:getScreenPlayState("CorvetteMissionStatusScreenPlay")
	local stateForBadge = playerCreature:getScreenPlayState("CorvetteTypeScreenPlay")

	if (state == 1) then
		playerCreature:sendSystemMessage("@dungeon/corvette:reward")
		local pGhost = playerCreature:getPlayerObject()
	
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)

			if (stateForBadge == 1) then
				ghost:awardBadge(112)
			elseif (stateForBadge == 2) then
				ghost:awardBadge(114)
			elseif (stateForBadge == 4) then
				ghost:awardBadge(113)
			end
		end
	end

	
	
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
			
	return 0
end
