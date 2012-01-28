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
	
	lockedCells = {
		1627785,
		1627786,
		1627790,
		1627805,
		1627812,
		1627815,
		1627822,
		1627823
	},
	
	timers = {
		acklay = 900, --Acklay normally 7200 (2 hours)
		fbspider = 450 --Fire Breathing Spider normally 3600 (1 hour)
	},
	
	geonosianLabObjectID = 1627780,
	
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
	
	--Building observer to lock all security doors.
	local pBuilding = getSceneObject(self.geonosianLabObjectID)
	createObserver(ENTEREDBUILDING, "geonosian_lab_screenplay", "notifyEnteredLab", pBuilding)
	
	--Gas Valve
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s1.iff", 2.27, -1.9, -15.73, 1627824, 0.701707, 0, -0.701707, 0)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyGasValveUsed", pSceneObject);
	writeData("geonosian_lab:gasleak", 1) --set the gas leak as started
	
	
	--Keypads
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -34, -18, -31, 1627784, 0.707107, 0, 0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 1)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -47, -18, -56, 1627785, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 2)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -105, -18, -64, 1627789, 0, 0, -1, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 3)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -79, -22, -146, 1627804, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 4)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -67, -34, -260, 1627811, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 5)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -133, -34, -204, 1627814, 0, 0, -1, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 6)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -4, -34, -417, 1627821, 0.707107, 0, -0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 7)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", 38, -34, -333, 1627822, 0.707107, 0, -0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 7)
	createObserver(OBJECTRADIALUSED, "geonosian_lab_screenplay", "notifyKeypadUsed", pSceneObject)
end

function geonosian_lab_screenplay:spawnMobiles()
	spawnMobile("yavin4", "biogenic_crazyguy", 1, -2.8, 10.8, 10.2, 69, 1627781)
	spawnMobile("yavin4", "biogenic_securitytech", 1, -48, -18, -31, -180, 1627785)
	spawnMobile("yavin4", "biogenic_scientist_human", 1, 23.8, -32, -83.2, 130, 1627798)
	spawnMobile("yavin4", "biogenic_construction", 1, -134.5, -21.7, -74.8, 90, 1627794)
	spawnMobile("yavin4", "biogenic_engineertech", 1,-107.7,-18,-33.8,176,1627790)
	spawnMobile("yavin4", "biogenic_assistant", 1, -36, -21.9, -162.8, 0, 1627803)
	spawnMobile("yavin4", "biogenic_scientist_generic_01", 1, -72.1, -34, -272.2, 130, 1627812)
	spawnMobile("yavin4", "biogenic_scientist_generic_02", 1, -127.4, -34, -183.5, -120, 1627815)
	spawnMobile("yavin4", "biogenic_scientist_geonosian", 1, 7.4, -22, -333, 180, 1627822)
	
	spawnMobile("yavin4", "acklay",self.timers.acklay,117.9,-34,-329.2,-90,1627823)
	spawnMobile("yavin4", "enhanced_gaping_spider",self.timers.fbspider,-130,-22.1,-85,-180,1627794)
	spawnMobile("yavin4", "imperial_observer",90,-23,-22,-116,-90,1627802)
	spawnMobile("yavin4", "imperial_observer",90,-16.4,-22,-114.5,-150,1627802)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,1.2,9.1,-8.1,63,1627781)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,0.6,9.5,-3.5,99,1627781)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,26.6,10.3,-13.3,-8,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,32.3,9.5,-8.1,-105,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,34.7,10.3,-14.4,-70,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,37.4,9.8,-8.2,-109,1627782)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-55.9,-18,-33.9,95,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-55.6,-18,-43.2,72,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-38.7,-18,-47.5,-75,1627785)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-36,-22,-151.4,180,1627803)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-66.7,-19,-41.2,-77,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-70.5,-18.9,-34.5,-161,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-83.9,-18.5,-42.3,85,1627788)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-36,-22,-151.4,180,1627803)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-26.8,-22.9,-158,-90,1627803)
	spawnMobile("yavin4", "crazed_geonosian_guard",90,-19.4,-22.6,-151.7,-135,1627803)
	spawnMobile("yavin4", "cavern_spider",90,-62,-21.8,-109.6,0,1627792)
	spawnMobile("yavin4", "cavern_spider",90,-48,-21.8,-158,0,1627800)
	spawnMobile("yavin4", "cavern_spider",90,-48,-21.8,-143,0,1627800)
	spawnMobile("yavin4", "cavern_spider",90,-41,-21.8,-136,-90,1627801)
	spawnMobile("yavin4", "cavern_spider",90,-88.3,-21.8,-110.3,90,1627793)
	spawnMobile("yavin4", "cavern_spider",90,-98,-21.9,-114.7,50,1627793)
	spawnMobile("yavin4", "cavern_spider",90,-107.3,-22.2,-96.6,180,1627793)
	spawnMobile("yavin4", "cavern_spider",90,-108,-21.8,-126,0,1627793)
	spawnMobile("yavin4", "cavern_spider",90,-123,-22,-109.5,80,1627793)
	spawnMobile("yavin4", "cavern_spider",90,-134.7,-20.9,-112.2,77,1627793)
	spawnMobile("yavin4", "cavern_spider",90,85,-33.9,-348.1,46,1627823)
	spawnMobile("yavin4", "cavern_spider",90,90.2,-34,-312.3,-180,1627823)
	spawnMobile("yavin4", "alert_droideka",90,-34.2,-22,-128,-180,1627801)
	spawnMobile("yavin4", "alert_droideka",90,-3.8,-30.2,-92,-180,1627796)
	spawnMobile("yavin4", "alert_droideka",90,-18,-18,-36,0,1627784)
	spawnMobile("yavin4", "alert_droideka",90,-62,-18,-59.5,-180,1627786)
	spawnMobile("yavin4", "alert_droideka",90,-90.5,-18,-76,0,1627789)
	spawnMobile("yavin4", "alert_droideka",90,-53.5,-18.2,-81.7,-90,1627791)
	spawnMobile("yavin4", "alert_droideka",90,-108,-34,-214,90,1627808)
	spawnMobile("yavin4", "alert_droideka",90,-61.5,-34,-252,-90,1627811)
	spawnMobile("yavin4", "geonosian_technical_assistant",90,-116.5,-20,-38.4,88,1627790)
	spawnMobile("yavin4", "enhanced_kwi",90,23.4,4,-30.6,67,1627783)
	spawnMobile("yavin4", "enhanced_kwi",90,19.9,-13.2,-22.5,-3,1627824)
	spawnMobile("yavin4", "enhanced_kwi",90,-104.2,-28.7,-193.4,0,1627807)
	spawnMobile("yavin4", "enhanced_kwi",90,-130,-33.8,-239.1,0,1627813)
	spawnMobile("yavin4", "enhanced_kwi",90,-137.4,-34,-183.5,160,1627815)
	spawnMobile("yavin4", "enhanced_kwi",90,-128.6,-34,-192.3,-120,1627815)
	spawnMobile("yavin4", "enhanced_kwi",90,-62.4,-34,-280.4,-15,1627812)
	spawnMobile("yavin4", "enhanced_kwi",90,102.3,-33.7,-310.8,-156,1627823)
	spawnMobile("yavin4", "enhanced_kliknik",90,26,-31.5,-78,170,1627798)
	spawnMobile("yavin4", "enhanced_kliknik",90,98.7,-33.4,-344.9,-37,1627823)
	spawnMobile("yavin4", "enhanced_kliknik",90,85.6,-34.2,-310.4,150,1627823)
	spawnMobile("yavin4", "enhanced_kliknik",90,36.5,-29.9,-82.7,-120,1627798)
	spawnMobile("yavin4", "enhanced_kliknik",90,29.5,-30.1,-88,-45,1627798)
	spawnMobile("yavin4", "enhanced_kliknik",90,-139.8,-34,-194.3,160,1627815)
	spawnMobile("yavin4", "enhanced_kliknik",90,-57.2,-34,-264.9,-105,1627812)
	spawnMobile("yavin4", "enhanced_kliknik",90,-74.8,-34,-276.6,67,1627812)
	spawnMobile("yavin4", "enhanced_kliknik",90,-153.6,-34.2,-372,60,1627818)
	spawnMobile("yavin4", "enhanced_kliknik",90,-87,-34.1,-386.5,90,1627819)
	spawnMobile("yavin4", "enhanced_force_kliknik",90,-127.6,-34.5,-324.3,-30,1627817)
	spawnMobile("yavin4", "enhanced_force_kliknik",90,-143.8,-33.7,-326.1,63,1627817)
	spawnMobile("yavin4", "enhanced_force_kliknik",90,-125,-34,-375.6,-30,1627818)
	spawnMobile("yavin4", "enhanced_force_kliknik",90,-71.5,-34,-348.1,-95,1627819)
	spawnMobile("yavin4", "enhanced_force_kliknik",90,-54.5,-33.3,-373.4,-60,1627819)
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
	local player = LuaCreatureObject(pCreature)
	local suiBox = LuaSuiBox(pSui)
	local pUsingObject = suiBox:getUsingObject()
	
	if (pUsingObject == nil) then
		return 0
	end
	
	local usingObject = LuaSceneObject(pUsingObject)
	
	local objectID = usingObject:getObjectID()
	
	local keypadIndex = readData(objectID .. ":geonosian_lab:keypad_index")
	
	local keypadCode = self.keypadCodes[keypadIndex]
	
	if (tonumber(enteredCode) == keypadCode) then
		--printf("Keypad codes matched!\n")
		player:sendSystemMessage("@dungeon/geonosian_madbio:right_code") --You have successfully entered the code for this door.
		
		local lockedCell = self.lockedCells[keypadIndex]
		
		local pCell = getSceneObject(lockedCell)
		
		--Unlock the door for them.
		if (pCell ~= nil) then
			local cell = LuaSceneObject(pCell)
			cell:updateCellPermission(1, pCreature)
		end
	else
		player:sendSystemMessage("@dungeon/geonosian_madbio:bad_code") --The number that you entered is not a valid code for this door.
	end
end

function geonosian_lab_screenplay:notifyEnteredLab(pBuilding, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	
	if (player:isAiAgent()) then
		return 0
	end
	
	for k, v in pairs(self.lockedCells) do
		local pCell = getSceneObject(v) 
		
		if (pCell ~= nil) then
			local cell = LuaSceneObject(pCell)
			cell:updateCellPermission(0, pPlayer)
		end
	end
	
	player:sendSystemMessage("@dungeon/geonosian_madbio:relock") --Security systems at this facility have been cycled and reset.
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