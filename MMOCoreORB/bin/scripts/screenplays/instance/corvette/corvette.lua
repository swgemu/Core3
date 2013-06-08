--Additional Includes...
-- Imperial
includeFile("instance/corvette/imperial/destroyMission.lua")



-- Main
CorvetteScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
		stages = { 
				stageOne = 1, 
				stageTwo = 2,
			},
		types = {
				ImperialDestroy = 1, 
				ImperialAssassinate = 2,
				ImperialRescue = 4,

				NeutralDestroy = 8, 
				NeutralAssassinate = 16,
				NeutralRescue = 32,

				RebelDestroy = 64, 
				RebelAssassinate = 128,
				RebelRescue = 256,
			},
	
	}
}

registerScreenPlay("CorvetteScreenPlay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function CorvetteScreenPlay:start()
	-- Spawn the start NPCs per faction, per mission.


	if (isZoneEnabled("corellia")) then
		-- Rebel Start 1.
		spawnMobile("corellia", "crowley", 0, 3404, 15, 3092, 110, 0) -- -3404 3092

		-- Rebel Start 2.
		spawnMobile("corellia", "pashna", 0, 6772, 15, -5697, 110, 0) -- 6772 -5697

		-- Rebel Start 3.
		spawnMobile("corellia", "adar", 0, -5448, 15, -2674, 110, 0) -- -5448 -2674
	end


	if (isZoneEnabled("naboo")) then
		-- Imperial Start 1.
		spawnMobile("naboo", "lt_velso", 0, 22, 0.2, -20, 180, 1418874) -- 2405 -3967
	end

	if (isZoneEnabled("tatooine")) then
		-- Imperial Start 2.
		spawnMobile("tatooine", "sabol", 0, 1291, 0, -3539, 110, 0) -- -1291 -3539

		-- Imperial Start 3.
		spawnMobile("tatooine", "darkstone", 0, -5313, 0, 2662, 110, 0) -- -5313 2662

		-- Neutral Start 1.
		spawnMobile("tatooine", "bruce_mcbrain", 0, -5880, 0, -6220, 110, 0) -- -5880 –6220

		-- Neutral Start 2.
		spawnMobile("tatooine", "bronell", 0, -5880, 0, -6220, 110, 0) -- -5880 –6220

		-- Neutral Start 3.
		spawnMobile("tatooine", "yondalla", 0, -5150, 0, -6588, 110, 0) -- -5150 -6588
	end
end

function CorvetteScreenPlay:respawnItems(pPlayer)
	if (pPlayer ~= nil) then
		local player = LuaCreatureObject(pPlayer)
			player:setScreenPlayState(0, "CorvetteItems")
	end
end

function CorvetteScreenPlay:giveAuthorizationForm(pConversingPlayer)
	if (pConversingPlayer ~= nil) then
		local player = LuaCreatureObject(pConversingPlayer)
		local playerInv = LuaSceneObject(pConversingPlayer)

		local pInv = playerInv:getSlottedObject("inventory")
		local pItem = giveItem(pInv, "object/tangible/travel/travel_ticket/dungeon_ticket.iff", -1)
			
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(player:_getObject())
			end
	end
end

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
	
	if (selectedID == 121) then
		if (creatureObject:hasScreenPlayState(1, "CorvetteItems") == 1) then
		    creatureObject:sendSystemMessage("You could not find anything of use here.")
		    return 0
		end


		local pInventory = creatureSceneObject:getSlottedObject("inventory")
		local item1 = nil
		local item2 = nil
		local item3 = nil
		
		-- Base the item on what mission type is...	
			if (creatureObject:getScreenPlayState("CorvetteTypeScreenPlay") == 1) then
				item1 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler01.iff"
				item2 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_filler02.iff"
				item3 = "object/tangible/loot/dungeon/corellian_corvette/imperial_destroy_intel.iff"
			end
		
		
		if (pInventory ~= nil) then
			local rand = math.random(2)
		
			if (rand == 0) then
				local pItem = giveItem(pInventory, item1, -1)
			
				if (pItem ~= nil) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					creatureObject:setScreenPlayState(1, "CorvetteItems")
					createEvent(3600, "CorvetteScreenPlay", "respawnItems", pPlayer)
				end

			elseif (rand == 1) then
				local pItem = giveItem(pInventory, item2, -1)
			
				if (pItem ~= nil) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					createEvent(3600, "CorvetteScreenPlay", "respawnItems", pPlayer)
					creatureObject:setScreenPlayState(1, "CorvetteItems")
				end

			elseif (rand == 2) then
				local pItem = giveItem(pInventory, item3, -1)
			
				if (pItem ~= nil) then
					local item = LuaSceneObject(pItem)
					item:sendTo(creatureObject:_getObject())
					creatureObject:sendSystemMessage("You found something useful.")
					createEvent(3600, "CorvetteScreenPlay", "respawnItems", pPlayer)
					creatureObject:setScreenPlayState(1, "CorvetteItems")
				end
			end	
		end
		
		
	end
			
	return 0
end
