geonosian_lab_screenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
	},
	
	poisonShutoffDuration = 30000 --30 seconds
}

registerScreenPlay("geonosian_lab_screenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function geonosian_lab_screenplay:start()
	self:spawnActiveAreas()
	self:spawnSceneObjects()
	self:spawnMobiles()
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
	
	--Gas Valve
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s1.iff", 2.27, -1.9, -15.73, 1627824, 0.701707, 0, -0.701707, 0)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyGasValveUsed", pSceneObject);
	writeData("geonosian_lab:gasleak", 1) --set the gas leak as started
	
	local pKeypadTerminal = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -34.5, -17, -31.25, 1627784, 0.707107, 0, 0.707107, 0)
	pKeypadTerminal = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -49.6, -17, -56.48, 1627785, 1, 0, 0, 0)
	pKeypadTerminal = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -105.25, -17, -63.55, 1627789, 0, 0, -1, 0)
	pKeypadTerminal = spawnSceneObject("yavin4", "object/tangible/dungeon/keypad_terminal.iff", -78.83, -21, -146.47, 1627804, 1, 0, 0, 0)
end

function geonosian_lab_screenplay:spawnMobiles()
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

function geonosian_lab_screenplay:restartGasLeak(pGasLeak)
	writeData("geonosian_lab:gasleak", 1)
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