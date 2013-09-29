--Additional Includes...
-- Imperial
includeFile("dungeon/corvette/imperial/destroyMission.lua")
includeFile("dungeon/corvette/imperial/travel.lua")



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
	
	},

	-- These are constant booleans for boarding checks in travel.
	groupIsInDungeonRebel = false,
	groupIsInDungeonImperial = false,
	groupIsInDungeonNeutral = false,

	-- Constant ints for Destroy-type mission objectives
	engineSetTo = 0,
	hyperdriveSetTo = 0,
	fuelSetTo = 0,

--------------------------------------------------------------
--   Spawn Map for Imperial Corvette, static norms.             -
--------------------------------------------------------------
spawnMapImperial =  {
		{"rebel_ensign", 0, -10, 0, -10.2, -10, 4336209},
		{"rebel_ensign", 0, 4.9, 0, -30.9, -10, 4336213},
		{"rebel_ensign", 0, 5, 0, -20.9, 170, 4336213},
		{"rebel_ensign", 0, 26.2, 0, 0, -100, 4336207},
		{"rebel_ensign", 0, 20, 0, 16, -10, 4336206},
		{"rebel_sailor", 0, 4.7, 0, 50, -100, 4336203},
		{"rebel_commandant", 0, 14.3, 0, 51.6, -100, 4336203},
		{"rebel_midshipman", 0, -2.6, 0, 60.5, 170, 4336203},
		{"rebel_ensign", 0, -10.9, 0, 18.1, 80, 4336201},
		{"rebel_ensign", 0, -0.1, 0, 9.4, -10, 4336199},
		{"rebel_ensign", 0, 0, 0, 23.3, 170, 4336199},

		{"rebel_ensign", 0, 10, 0, 17.6, 170, 4336208},

		{"rebel_midshipman", 0, -2.9, 12, -16.3, 170, 4336216},
		{"rebel_midshipman", 0, -2.9, 12, 14.9, 170, 4336216},
		{"rebel_admiral", 0, 1, 12, -8.2, -10, 4336217},
		{"rebel_midshipman", 0, 3, 12, -0.7, 170, 4336217},

		{"rebel_rear_admiral", 0, 2.8, 12, 4.1, -10, 4336218},
		{"rebel_commandant", 0, 4.9, 12, 15, 170, 4336218},
	
		{"rebel_engineer", 0, 6.4, 15, 37, -10, 4336219},
		{"rebel_commandant", 0, 3.6, 15, 37, -10, 4336219},
		{"rebel_sailor", 0, 0.9, 15, 33.7, -135, 4336219},

		{"rebel_first_mate", 0, 0, -12, 28.5, -10, 4336227},

		{"rebel_ensign", 0, 26.2, -12, 27.9, -100, 4336230},

		{"rebel_commandant", 0, 10.9, -12, 5.4, -10, 4336229},

		{"rebel_sailor", 0, 2.8, 0, -40.2, -100, 4336220},
		{"rebel_sailor", 0, -7.2, 0, -37.7, -100, 4336220},
		{"death_watch_battle_droid", 0, 16.4, -12, -41.7, 80, 4336220},
		{"death_watch_s_battle_droid", 0, 27.1, -12, -60.8, -10, 4336220},
		{"death_watch_s_battle_droid", 0, 13.4, -12, -58.9, 80, 4336220},
		{"death_watch_s_battle_droid", 0, -11.9, -12, -40.1, -100, 4336220},
		{"death_watch_s_battle_droid", 0, -21.4, -12, -59.8, -50, 4336220},
		{"death_watch_s_battle_droid", 0, -7.6, -14, -45.4, 170, 4336220},

		{"death_watch_s_battle_droid", 0, 7.5, -14, -39, 170, 4336224},

		{"rebel_engineer", 0, -11.2, -12, 5.3, -10, 4336234},
		{"rebel_sailor", 0, -7.4, -12, 11.2, 170, 4336234},
		{"rebel_midshipman", 0, -4.1, -12, 6.3, -100, 4336234},

		{"rebel_ensign", 0, -25, -12, 28, 80, 4336235},

		{"rebel_midshipman", 0, -6.4, -6.7, -36, -100, 4336223},
		{"rebel_commandant", 0, -6, -6.7, -39.9, -10, 4336223},

		{"rebel_first_mate", 0, -7.6, -12, 40.8, -150, 4336238},

		{"rebel_commodore", 0, 2.6, -12, 55, -150, 4336236},

		{"rebel_commodore", 0, -2.7, -12, 71, 80, 4336243},
		{"rebel_commodore", 0, 3.3, -12, 73.6, -10, 4336243},

		{"rebel_admiral", 0, 24.5, -12, 62.8, -100, 4336241},
		{"rebel_commodore", 0, 17.6, -12, 69.5, -10, 4336241},

		{"rebel_ensign", 0, -22.6, -12, 51.8, 80, 4336244},

		{"rebel_midshipman", 0, -21.1, -12, 68.3, 170, 4336242},
		{"rebel_sailor", 0, -24.6, -12, 64.1, 80, 4336242},
		{"rebel_sailor", 0, -17.4, -12, 64.1, -100, 4336242},

		{"rebel_midshipman", 0, 0, -12, 100.7, 170, 4336248},

		{"rebel_midshipman", 0, -17, -12, 112.9, 130, 4336249},
		{"rebel_midshipman", 0, 17, -12, 112.9, -150, 4336249},

		{"rebel_commandant", 0, 0, -12, 117.4, 170, 4336250},
		{"rebel_commandant", 0, -5.8, -12, 127.5, 170, 4336250},

		{"rebel_midshipman", 0, -5.4, -12, 133.6, 170, 4336251},
		{"rebel_commandant", 0, 5.6, -12, 132.7, -100, 4336251},

		{"rebel_midshipman", 0, 0, -24, 98.3, -10, 4336254},

		{"rebel_commodore", 0, 3.3, -27, 75.6, 157, 4336256},
		{"rebel_commandant", 0, 3.2, -27, 78.6, 45, 4336256},

		{"rebel_midshipman", 0, 0.7, 0, 111.5, -100, 4336257},
		{"rebel_admiral", 0, -16.3, 0, 112, -50, 4336257},

		{"rebel_first_mate", 0, 0, 0, 127.8, 170, 4336258},

	--"Rebel Commander", 0, -5.8, 0, 133.1, -10, 4336261},	
		{"rebel_commandant", 0, -3.5, 0, 125.3, -10, 4336261},

		{"rebel_admiral", 0, 3.8, 0, 124.9, -10, 4336260},
		{"rebel_commandant", 0, 6.7, 0, 134.4, 170, 4336260},

		{"rebel_rear_admiral", 0, 0, 0, 150.3, -10, 4336262},
		{"rebel_commandant", 0, -4.4, 0, 148.3, 130, 4336262},
		{"rebel_commandant", 0, 4.5, 0, 148.3, -150, 4336262}
	},

-- Scene objects created in every instance for the Imperial building.
globalSceneObjectsImperial =  {
		-- Format is: object (string), x, z, y, cell, ow, ox, oz, oy, custom name, custom object menu component.
		{"object/tangible/dungeon/wall_terminal_s3.iff",-25,-12,36.7,4336235,0,0,0,1,"Escape Pod","escape_pod_menu_component"},
		{"object/tangible/dungeon/wall_terminal_s3.iff",-25,-12,-20.7,4336235,-1,0,0,1,"Escape Pod","escape_pod_menu_component"},
		{"object/tangible/dungeon/wall_terminal_s3.iff",25,-12,36.7,4336230,-1,0,0,1,"Escape Pod","escape_pod_menu_component"},
		{"object/tangible/dungeon/wall_terminal_s3.iff",25,-12,-20.7,4336230,0,0,0,1,"Escape Pod","escape_pod_menu_component"},

		-- Elevators have no lua object component, already handled in cpp.
		{"object/tangible/terminal/terminal_elevator_up.iff",0,-12,36.8,4336215,0,0,0,0,nil,nil},
		{"object/tangible/terminal/terminal_elevator_down.iff",0,0,36.8,4336215,0,0,0,0,nil,nil},
		{"object/tangible/terminal/terminal_elevator_up.iff", 5,0,-13.4,4336214,0,0,0,0,nil,nil},
		{"object/tangible/terminal/terminal_elevator_down.iff", 5,10,-13.4,4336214,0,0,0,0,nil,nil},
		{"object/tangible/terminal/terminal_elevator_up.iff",18,-20,120.6,4336248,0,0,0,0,nil,nil},
		{"object/tangible/terminal/terminal_elevator_down.iff",18,-10,120.6,43362480,0,0,0,nil,nil}
	},

-- Scene objects spawned in destroy-type missions only for the Imperial building.
destroySceneObjectsImperial = {
		{"object/tangible/dungeon/wall_terminal_s4.iff",-25,-12,-20.7,4336235,0,0,0,0,"Engine Controls","corvette_destroy_object_menucomponent"},
{"object/tangible/dungeon/wall_terminal_s4.iff",-25,-12,-20.7,4336235,0,0,0,0,"Fuel Terminal","corvette_destroy_object_menucomponent"},
{"object/tangible/dungeon/wall_terminal_s4.iff",-25,-12,-20.7,4336235,0,0,0,0,"Hyperdrive Controls","corvette_destroy_object_menucomponent"}
},

}

registerScreenPlay("CorvetteScreenPlay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function CorvetteScreenPlay:start()
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
		spawnMobile("naboo", "cor_imperial_pilot", 0, 2433, 292, -3887, 160, 0)
	end

	if (isZoneEnabled("tatooine")) then
		-- Imperial Start 2.
		spawnMobile("tatooine", "sabol", 0, -1291, 0, -3539, 110, 0) -- -1291 -3539

		-- Imperial Start 3.
		--spawnMobile("tatooine", "darkstone", 0, -5313, 0, 2662, 110, 0) -- -5313 2662

		-- Neutral Start 1.
		--spawnMobile("tatooine", "bruce_mcbrain", 0, -5880, 0, -6220, 110, 0) -- -5880 –6220

		-- Neutral Start 2.
		--spawnMobile("tatooine", "bronell", 0, -5880, 0, -6220, 110, 0) -- -5880 –6220

		-- Neutral Start 3.
		--spawnMobile("tatooine", "yondalla", 0, -5150, 0, -6588, 110, 0) -- -5150 -6588
	end
end

--------------------------------------
--      Travel Functions.            -
--------------------------------------
function CorvetteScreenPlay:travelToDungeon(pCreature, pSui, cancelPressed)
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

function CorvetteScreenPlay:findAvailableDungeon(pFaction)
	if (groupIsInDungeonRebel == true) and (pFaction == "rebel") then
		return false
	elseif (groupIsInDungeonNeutral == true) and (pFaction == "neutral") then
		return false
	elseif (groupIsInDungeonImperial == true) and (pFaction == "imperial") then
		return false
	else 
		return true
	end
end

--------------------------------------
--     Instancing Functions.         -
--------------------------------------

function CorvetteScreenPlay:startInstance(pFaction, pPlayerOwner)
	-- Set the group boolean to true.
	if (pFaction == "rebel") then
		groupIsInDungeonRebel = true
	elseif (pFaction == "neutral") then
		groupIsInDungeonNeutral = true
	elseif (pFaction == "imperial") then
		groupIsInDungeonImperial = true
	end

	local ownerCreature = LuaCreatureObject(pPlayerOwner)

	-- You have 1 hour to complete your task.

	if (ownerCreature:isGrouped()) then
		local gSize = ownerCreature:getGroupSize()
		for i = 0, gSize do
			local groupMember = player:getGroupMember(i)
			if (groupMember ~= nil) then
				if (groupMember ~= pPlayerOwner) then
					ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
					createEvent(360000, "CorvetteScreenPlay", "instanceFailed", groupMember)
				else
					ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
					createEvent(360000, "CorvetteScreenPlay", "instanceFailed", pPlayerOwner)
					createObserver(OBJECTDESTRUCTION, "CorvetteScreenPlay", "ownerDied", pPlayerOwner) -- Reset mobs if instance leader dies.
				end
			end
		end
	else
		ownerCreature:sendSystemMessage("You have one hour to complete your objective.")
		createEvent(360000, "CorvetteScreenPlay", "instanceFailed", pPlayerOwner)
		createObserver(OBJECTDESTRUCTION, "CorvetteScreenPlay", "ownerDied", pPlayerOwner) -- Reset mobs if instance leader dies.
	end
		
	local state = ownerCreature:getScreenPlayState("CorvetteTypeScreenPlay")		
	
	if (pFaction == "imperial") then
		if (state == 1) then
		-- Destroy Mission: Spawn Scene Objects.
		self:spawnDestroySceneObjectsImperial()
		elseif (state == 2) then
		-- Assassin Mission: Spawn Additional Mobile.
		elseif (state == 4) then
		-- Rescue Mission: Spawn Additional Mobiles.
		end
	-- Spawn general static mobiles global to imperial missions.
	self:spawnMobilesImperial()
	-- Spawn global scene objects that are the same no matter the faction.
	self:spawnGlobalSceneObjectsImperial()
	elseif (pFaction == "neutral") then
	elseif (pFaction == "rebel") then
	end

end

function CorvetteScreenPlay:spawnGlobalSceneObjectsImperial()

	local spawnedSceneObject = LuaSceneObject(nil)
	
	for i,v in ipairs(self.globalSceneObjectsImperial) do
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

function CorvetteScreenPlay:spawnDestroySceneObjectsImperial()

	local spawnedSceneObject = LuaSceneObject(nil)
	
	for i,v in ipairs(self.destroySceneObjectsImperial) do
		pSpawnedSceneObject = spawnSceneObject("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7], v[8], v[9])

		if (pSpawnedSceneObject ~= nil) then
			spawnedSceneObject:_setObject(pSpawnedSceneObject)
			spawnedSceneObject:setCustomObjectName(v[10])
			spawnedSceneObject:setObjectMenuComponent(v[11])
		end
	end

end

function CorvetteScreenPlay:ownerDied(pOwner, pKiller)

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
					createObserver(OBJECTDESTRUCTION, "CorvetteScreenPlay", "spawnKilled", spawnedPointer)
				end
			end
		end
	elseif (creatureObject:isNeutral()) then
	elseif (creatureObject:isRebel()) then
	end

end

function CorvetteScreenPlay:spawnKilled(pSpawn, pKiller)
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

function CorvetteScreenPlay:instanceFailed(pPlayer)
	if (pPlayer == nil) then
		createEvent(60000, "CorvetteScreenPlay", "instanceFailed", pPlayer)
	end

	local playerCreature = LuaCreatureObject(pPlayer)

	-- Set the group boolean to false.
	if (playerCreature:isRebel()) then
		groupIsInDungeonRebel = false
	elseif (playerCreature:isNeutral()) then
		groupIsInDungeonNeutral = false
	elseif (playerCreature:isImperial()) then
		groupIsInDungeonImperial = false
	end

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

function CorvetteScreenPlay:spawnMobilesImperial()
	local spawnedSceneObject = LuaSceneObject(nil)

	for i,v in ipairs(self.spawnMapImperial) do
		spawnedPointer = spawnMobile("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
		
		if (spawnedPointer ~= nil) then
			spawnedSceneObject:_setObject(spawnedPointer)
			writeData(i ..":imperial:vette:objid", spawnedSceneObject:getObjectID())
			createObserver(OBJECTDESTRUCTION, "CorvetteScreenPlay", "spawnKilled", spawnedPointer)
		end
	end
end

function CorvetteScreenPlay:spawnSceneObjectsDestroy()

	for i,v in ipairs(self.sceneObjectsDestroy) do
		spawnSceneObject("dungeon1", v[1], v[2], v[3], v[4], v[5], v[6], v[7])
	end
end

--------------------------------------
--     Sui Callback Functions.       -
--------------------------------------

function CorvetteScreenPlay:EngineSuiCallback(pCreature, pSui, cancelPressed, otherPressed, okPressed)
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)

	if (cancelPressed) then
	-- Set Engines to 40.

	-- Send the message.
		local setting = 40
		player:sendSystemMessage("You have set the engine to " .. setting .. "%.")

	-- Set it in the screenplay.
		self:setShipComponent("engine", setting, pCreature)
	
	elseif (otherPressed) then
	-- Set Engines to 60.

	-- Send the message.
		local setting = 60
		player:sendSystemMessage("You have set the engine to " .. setting .. "%.")

	-- Set it in the screenplay.
		self:setShipComponent("engine", setting, pCreature)

	elseif (okPressed) then
	-- Set Engines to 80.

	-- Send the message.
		local setting = 80
		player:sendSystemMessage("You have set the engine to " .. setting .. "%.")

	-- Set it in the screenplay.
		self:setShipComponent("engine", setting, pCreature)
	end
end

function CorvetteScreenPlay:FuelSuiCallback(pCreature, pSui, cancelPressed, otherPressed, okPressed)
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)

	-- Set Fuel.
	if (cancelPressed) then
	-- Send the message.
		local setting = 30
		player:sendSystemMessage("@dungeon/corvette:fuel_30")

	-- Set it in the screenplay.
		self:setShipComponent("fuel", setting, pCreature)
	
	elseif (otherPressed) then
	-- Send the message.
		local setting = 50
		player:sendSystemMessage("@dungeon/corvette:fuel_50")

	-- Set it in the screenplay.
		self:setShipComponent("fuel", setting, pCreature)

	elseif (okPressed) then
	-- Send the message.
		local setting = 80
		player:sendSystemMessage("@dungeon/corvette:fuel_80")

	-- Set it in the screenplay.
		self:setShipComponent("fuel", setting, pCreature)
	end
end


function CorvetteScreenPlay:setShipComponent(componentName, setting, pCreature)
	
	local player = LuaCreatureObject(pCreature)

	if (componentName == "engine") then
		engineSetTo = setting
		player:sendSystemMessage("Engine is at " .. setting)
	elseif (componentName == "fuel") then
		fuelSetTo = setting
		player:sendSystemMessage("Fuel is at " .. setting)
	end

	if ((engineSetTo == 40) and (hyperdriveSetTo == 20) and (fuelSetTo == 80)) then
		-- Done!
		player:sendSystemMessage("@dungeon/corvette:blew_up")
		player:setScreenPlayState(1, "CorvetteMissionStatusScreenPlay")
	else
		player:sendSystemMessage("@dungeon/corvette:engine_result")
	end
end

corvette_destroy_object_menucomponent = { }

function corvette_destroy_object_menucomponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	
	local player = LuaCreatureObject(pPlayer)
	
	if (player:hasScreenPlayState(CorvetteScreenPlay.states.types.ImperialDestroy, "CorvetteTypeScreenPlay") == 1) or
	   (player:hasScreenPlayState(CorvetteScreenPlay.states.types.NeutralDestroy, "CorvetteTypeScreenPlay") == 1) or
	   (player:hasScreenPlayState(CorvetteScreenPlay.states.types.RebelDestroy, "CorvetteTypeScreenPlay") == 1) then
		menuResponse:addRadialMenuItem(20, 3, "Use") -- Use the item.
	end
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
		local numOfButtons = 3 -- It should always be three for each.

		-- Engine.
		if (luaSceneObject:getCustomObjectName() == "Engine Controls") then
			suiManager:sendListBox(pSceneObject, pPlayer, "@dungeon/corvette:engine_title", "@dungeon/corvette:engine_settings", numOfButtons, "40", "60", "80",  "CorvetteScreenPlay", "EngineSuiCallback")

		elseif (luaSceneObject:getCustomObjectName() == "Fuel Controls") then
			suiManager:sendListBox(pSceneObject, pPlayer, "@dungeon/corvette:fuel_title", "@dungeon/corvette:fuel_settings", numOfButtons, "30", "50", "80",  "CorvetteScreenPlay", "FuelSuiCallback")

		end
	end
			
	return 0
end

--------------------------------------
--      Item Functions.              -
--------------------------------------

function CorvetteScreenPlay:respawnItems(pSceneObject)
	if (pSceneObject ~= nil) then
		local container = LuaCreatureObject(pSceneObject)
		local objectID = container:getObjectID()
			deleteData(objectID .. ":corvette:items:spawned")
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

	
	-- Set the group boolean to false.
	if (playerCreature:isRebel()) then
		groupIsInDungeonRebel = false
	elseif (playerCreature:isNeutral()) then
		groupIsInDungeonNeutral = false
	elseif (playerCreature:isImperial()) then
		groupIsInDungeonImperial = false
	end

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
