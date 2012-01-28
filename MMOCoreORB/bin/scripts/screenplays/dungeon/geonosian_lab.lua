geonosian_lab_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
	},
	
	keypadCodes = {
		32281,
		12872,
		51892,
		12753, --Door 4 is short circuited passkey or this code
		86332,
		11380,
		52577,
		78660
	},
	
	poisonShutoffDuration = 30000 --30 seconds
}

registerScreenPlay("geonosian_lab_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function geonosian_lab_screenplay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnActiveAreas()
		self:spawnSceneObjects()
		self:spawnMobiles()
	end
end

function geonosian_lab_screenplay:spawnActiveAreas()
	local pPoisonCloudAA = spawnSceneObject("yavin4", "object/active_area.iff", -6435.5, 85.6, -367, 0, 0, 0, 0, 0)
	
	if (pPoisonCloudAA ~= nil) then
		local activeArea = LuaActiveArea(pPoisonCloudAA)
		activeArea:setCellObjectID(1627783)
		activeArea:setRadius(10)
		createObserver(ENTEREDAREA, "geonosian_lab_screenplay", "notifyEnteredPoisonGas", pPoisonCloudAA)
	end
end

function geonosian_lab_screenplay:spawnSceneObjects()
	local pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/poison_gas_cloud.iff", 21.7, 3.3, -29.1, 1627783, 0, 0, 0, 0)
	local sceneObject = LuaSceneObject(pSceneObject)
	--Gas Valve
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s1.iff", 2.27, -1.9, -15.73, 1627824, 0.701707, 0, -0.701707, 0)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyGasValveUsed", pSceneObject);
	writeData("geonosian_lab:gasleak", 1) --set the gas leak as started
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -34.5, -17, -31.25, 1627784, 0.707107, 0, 0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_code", self.keypadCodes[1])
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -49.6, -17, -56.48, 1627785, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_code", self.keypadCodes[2])
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -105.25, -17, -63.55, 1627789, 0, 0, -1, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_code", self.keypadCodes[3])
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -78.83, -21, -146.47, 1627804, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_code", self.keypadCodes[4])
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
end

function geonosian_lab_screenplay:spawnMobiles()
	spawnMobile("yavin4", "biogenic_crazyguy", 0, -2.8, 10.8, 10.2, 69, 1627781)
	spawnMobile("yavin4", "acklay",1800,117.9,-34,-329.2,-91,1627823)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,1.2,9.1,-8.1,63,1627781)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,0.6,9.5,-3.5,99,1627781)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,26.6,10.3,-13.3,-8,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,32.3,9.5,-8.1,-105,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,34.7,10.3,-14.4,-70,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,37.4,9.8,-8.2,-109,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-55.9,-18,-33.9,95,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-55.6,-18,-43.2,72,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-38.7,-18,-47.5,-75,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-66.7,-19,-41.2,-77,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-70.5,-18.9,-34.5,-161,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-83.9,-18.5,-42.3,85,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-116.5,-20,-38.4,88,1627790)
	spawnMobile("yavin4", "enhanced_kwi",120,23.4,4,-30.6,67,1627783)
	spawnMobile("yavin4", "enhanced_kwi",120,19.9,-13.2,-22.5,-3,1627824)
	spawnMobile("yavin4", "geonosian_technical_assistant",150,-107.7,-18,-33.8,176,1627790)
	spawnMobile("yavin4", "mercenary_sentry",90,-74.9,-22,-153.7,-119,1627805)
	spawnMobile("yavin4", "mercenary_sentry",90,-74,-22,-160.1,-75,1627805)
	spawnMobile("yavin4", "mercenary_sentry",90,-82.3,-22,-161.7,74,1627805)
	spawnMobile("yavin4", "mercenary_sentry",90,-82.2,-22,-155.1,106,1627805)
end

function geonosian_lab_screenplay:notifyGasValveUsed(pGasValve, pPlayer, radialSelected)
	if (radialSelected == 20) then
		local player = LuaCreatureObject(pPlayer)
		local isGasLeaking = readData("geonosian_lab:gasleak")
		
		if (isGasLeaking == 1) then
			player:sendSystemMessage("@dungeon/geonosian_madbio:gas_off") --You have shut off the gas leak.
			writeData("geonosian_lab:gasleak", 0)
			createEvent(self.poisonShutoffDuration, "geonosian_lab_screenplay", "restartGasLeak", pGasValve)
		else
				player:sendSystemMessage("@dungeon/geonosian_madbio:gas_already_off") --The gas leak has already been repaired...
		end
	end
end

function geonosian_lab_screenplay:notifyKeypadUsed(pKeypad, pPlayer, radialSelected)
	if (radialSelected == 20) then
		--We need to show to the user the keypad sui.
		local suiManager = LuaSuiManager()
		suiManager:sendKeypadSui(pKeypad, pPlayer, "geonosian_lab_screenplay", "keypadSuiCallback")
	end
end

function geonosian_lab_screenplay:restartGasLeak(pGasLeak)
	writeData("geonosian_lab:gasleak", 1)
end

function geonosian_lab_screenplay:keypadSuiCallback(pCreature, pSui, cancelPressed, enteredCode)
	if (pCreature ~= nil) then
	end
	
	local suiBox = LuaSuiBox(pSui)
	
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)
	
	local objectID = usingObject:getObjectID()
	
	local keypadCode = readData(objectID .. ":geonosian_lab:keypad_code");
	
	if (tonumber(enteredCode) == keypadCode) then
		--printf("Keypad codes matched!\n")
	else
		--printf("Keypad codes didn't match\n")
	end
end

--------------------------------------
--   ActiveArea observers            -
--------------------------------------
function geonosian_lab_screenplay:notifyEnteredPoisonGas(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		--Check if gas is currently leaking
		local isGasLeaking = readData("geonosian_lab:gasleak")
		
		if (isGasLeaking == 1) then
			--Check for rebreathing mod
			if (self:hasRebreather(movingObject) == 1) then
				player:sendSystemMessage("@dungeon/geonosian_madbio:gasmask") --Your gasmask diffuses the poison gas and you are able to breathe with no difficulty.
			else
				player:addDotState(POISONED, math.random(20) + 80, HEALTH, 10000, 40.0, 0)
				player:sendSystemMessage("@dungeon/geonosian_madbio:toxic_fumes") --You breathe in toxic fumes!
			end
		end
	end
	
	return 0
end

function geonosian_lab_screenplay:hasRebreather(scno)
	--TODO: Change this to be a skill mod check for private_poison_rebreather
	local pRebreather = scno:getSlottedObject("head")
	
	if (pRebreather ~= nil) then
		local rebreather = LuaSceneObject(pRebreather)
		local headSlot = rebreather:getTemplateObjectPath()
		
		if (headSlot == "object/tangible/wearables/goggles/rebreather.iff") then
			return 1
		elseif (headSlot == "object/tangible/wearables/armor/mandalorian/armor_mandalorian_helmet.iff") then
			return 1
		end
	end
	
	return 0
end

--------------------------------------
--   Common functions                -
--------------------------------------
function geonosian_lab_screenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "geonosian_lab")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function geonosian_lab_screenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":geonosian_lab:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function geonosian_lab_screenplay:setSpawned(objectID, key)
	writeData(objectID .. ":geonosian_lab:spawned:" .. key)
end

function geonosian_lab_screenplay:deleteSpawned(objectID, key)
	deleteData(objectID .. ":geonosian_lab:spawned:" .. key)
end

function geonosian_lab_screenplay:writeObjectData(objectID, key, value)
	writeData(objectID .. ":geonosian_lab:" .. key, value)
end

function geonosian_lab_screenplay:readObjectData(objectID, key)
	return readData(objectID .. ":geonosian_lab:" .. key)
end

function geonosian_lab_screenplay:deleteObjectData(objectID, key)
	deleteData(objectID .. ":geonosian_lab:" .. key)
end

function geonosian_lab_screenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "geonosian_lab")
end