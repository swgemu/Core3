--Additional Includes
includeFile("dungeon/geonosian_lab/biogenic_scientist_geonosian_convo_handler.lua")
includeFile("dungeon/geonosian_lab/biogenic_scientist_human_convo_handler.lua")


geonosian_labscreenplay = ScreenPlay:new {
	numberOfActs = 1,
	
	states = {
		datapad = {started = 1, done = 2},
		tenloss = {started = 4, noreward = 8, done = 16}		
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
		acklay = 7200, --Acklay normally 7200 (2 hours)
		fbspider = 3600 --Fire Breathing Spider normally 3600 (1 hour)
	},
	
	geonosianLabObjectID = 1627780,

	--debri fields, all respawns are set to 4 minutes
	debrisM = {x = -105.8, z = -29.6, y = -368.3, cell = 1627818, respawn = 240000},
	--acklay doorway
	debrisA1 = {x = 37.5, z = -34.0, y = -333.5, cell = 1627822, respawn = 240000},
	debrisA2 = {x = 37.6, z = -34.0, y = -334.4, cell = 1627822, respawn = 240000},
	debrisA3 = {x = 37.2, z = -34.0, y = -335.2, cell = 1627822, respawn = 240000},
	debrisA4 = {x = 36.4, z = -34.0, y = -335.7, cell = 1627822, respawn = 240000},
	--hallway
	debrisH1 = {x = -121.3, z = -33.5, y = -226.5, cell = 1627809, respawn = 240000},
	debrisH2 = {x = -121.8, z = -33.6, y = -227.7, cell = 1627809, respawn = 240000},
	debrisH3 = {x = -121.5, z = -33.6, y = -228.4, cell = 1627809, respawn = 240000},
	debrisH4 = {x = -122.0, z = -33.6, y = -229.1, cell = 1627809, respawn = 240000},
	debrisH5 = {x = -122.3, z = -33.6, y = -228.4, cell = 1627809, respawn = 240000},
	--spider hallway
	debrisS1 = {x = -74.5, z = -21.9, y = -109.7, cell = 1627792, respawn = 240000},
	debrisS2 = {x = -75.0, z = -21.9, y = -110.3, cell = 1627792, respawn = 240000},
	debrisS3 = {x = -75.2, z = -22.0, y = -111.0, cell = 1627792, respawn = 240000},
	debrisS4 = {x = -75.3, z = -22.0, y = -111.6, cell = 1627792, respawn = 240000},
	debrisS5 = {x = -74.1, z = -22.5, y = -110.7, cell = 1627792, respawn = 240000}, 
	
	
	poisonShutoffDuration = 30000, --30 seconds
	
	geoDatapad = "object/tangible/loot/dungeon/geonosian_mad_bunker/engineering_datapad.iff",

	geoTenloss = "object/tangible/loot/loot_schematic/geonosian_tenloss_dxr6_schematic.iff"

}

registerScreenPlay("geonosian_labscreenplay", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function geonosian_labscreenplay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnActiveAreas()
		self:spawnSceneObjects()
		self:spawnMobiles()
	end
end

function geonosian_labscreenplay:spawnActiveAreas()
	local pPoisonCloudAA = spawnSceneObject("yavin4", "object/active_area.iff", -6435.5, 85.6, -367, 0, 0, 0, 0, 0)
	
	if (pPoisonCloudAA ~= nil) then
		local activeArea = LuaActiveArea(pPoisonCloudAA)
		activeArea:setCellObjectID(1627783)
		activeArea:setRadius(10)
		createObserver(ENTEREDAREA, "geonosian_labscreenplay", "notifyEnteredPoisonGas", pPoisonCloudAA)
	end


--poison area at entry of the acklay room

	local pPoisonCloudBB = spawnSceneObject("yavin4", "object/active_area.iff", -6181.9, 48.3, -197.2, 0, 0, 0, 0, 0)
	
	if (pPoisonCloudBB ~= nil) then
		local activeArea = LuaActiveArea(pPoisonCloudBB)
		activeArea:setCellObjectID(1627822)
		activeArea:setRadius(4)
		createObserver(ENTEREDAREA, "geonosian_labscreenplay", "notifyEnteredPoisonGasStrong", pPoisonCloudBB)
	end


--electric shock area

	local pElectroShock = spawnSceneObject("yavin4", "object/active_area.iff", -6168.7, 48.3, -380.9, 0, 0, 0, 0, 0)
	
	if (pElectroShock ~= nil) then
		local activeArea = LuaActiveArea(pElectroShock)
		activeArea:setCellObjectID(1627813)
		activeArea:setRadius(3)
		createObserver(ENTEREDAREA, "geonosian_labscreenplay", "notifyElectroShock", pElectroShock)
	end
end




function geonosian_labscreenplay:spawnSceneObjects()
	local pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/poison_gas_cloud.iff", 21.7, 3.3, -29.1, 1627783, 0, 0, 0, 0)
        --graphic for poison cloud in acklay room
	local pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/poison_gas_cloud.iff", 37.6, -34.0, -334.7, 1627822, 0, 0, 0, 0)
	local sceneObject = LuaSceneObject(pSceneObject)
	
	--Building observer to lock all security doors.
	local pBuilding = getSceneObject(self.geonosianLabObjectID)
	createObserver(ENTEREDBUILDING, "geonosian_labscreenplay", "notifyEnteredLab", pBuilding)
	
	--Gas Valve
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s1.iff", 2.27, -1.9, -15.73, 1627824, 0.701707, 0, -0.701707, 0)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyGasValveUsed", pSceneObject);
	writeData("geonosian_lab:gasleak", 1) --set the gas leak as started
	
	
	--Keypads
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -34, -18, -31, 1627784, 0.707107, 0, 0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 1)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -47, -18, -56, 1627785, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 2)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -105, -18, -64, 1627789, 0, 0, -1, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 3)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -79, -22, -146, 1627804, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 4)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -67, -34, -260, 1627811, 1, 0, 0, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 5)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -133, -34, -204, 1627814, 0, 0, -1, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 6)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", -4, -34, -417, 1627821, 0.707107, 0, -0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 7)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	pSceneObject = spawnSceneObject("yavin4", "object/tangible/dungeon/wall_terminal_s3.iff", 38, -34, -333, 1627822, 0.707107, 0, -0.707107, 0)
	sceneObject:_setObject(pSceneObject)
	writeData(sceneObject:getObjectID() .. ":geonosian_lab:keypad_index", 8)
	createObserver(OBJECTRADIALUSED, "geonosian_labscreenplay", "notifyKeypadUsed", pSceneObject)
	
	--debri fields
	--main rock wall
	local pDebrisM = spawnSceneObject("yavin4", "object/static/destructible/destructible_cave_wall_damprock.iff", self.debrisM.x, self.debrisM.z, self.debrisM.y, self.debrisM.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisMDestroyed", pDebrisM)
	--acklay doorway
	local pDebrisA1 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_drum_dented.iff", self.debrisA1.x, self.debrisA1.z, self.debrisA1.y, self.debrisA1.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisADestroyed", pDebrisA1)

	local pDebrisA2 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_drum_storage1.iff", self.debrisA2.x, self.debrisA2.z, self.debrisA2.y, self.debrisA2.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisADestroyed", pDebrisA2)
	
	local pDebrisA3 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_drum_storage1.iff", self.debrisA3.x, self.debrisA3.z, self.debrisA3.y, self.debrisA3.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisADestroyed", pDebrisA3)

	local pDebrisA4 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_drum_storage1.iff", self.debrisA4.x, self.debrisA4.z, self.debrisA4.y, self.debrisA4.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisADestroyed", pDebrisA4)
	--hallway
	local pDebrisH1 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_lg.iff", self.debrisH1.x, self.debrisH1.z, self.debrisH1.y, self.debrisH1.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisHDestroyed", pDebrisH1)

	local pDebrisH2 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisH2.x, self.debrisH2.z, self.debrisH2.y, self.debrisH2.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisHDestroyed", pDebrisH2)

	local pDebrisH3 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisH3.x, self.debrisH3.z, self.debrisH3.y, self.debrisH3.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisHDestroyed", pDebrisH3)

	local pDebrisH4 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisH4.x, self.debrisH4.z, self.debrisH4.y, self.debrisH4.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisHDestroyed", pDebrisH4)

	local pDebrisH5 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisH5.x, self.debrisH5.z, self.debrisH5.y, self.debrisH5.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisHDestroyed", pDebrisH5)
	--spider hallway
	local pDebrisS1 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisS1.x, self.debrisS1.z, self.debrisS1.y, self.debrisS1.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisSDestroyed", pDebrisS1)

	local pDebrisS2 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisS2.x, self.debrisS2.z, self.debrisS2.y, self.debrisS2.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisSDestroyed", pDebrisS2)

	local pDebrisS3 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisS3.x, self.debrisS3.z, self.debrisS3.y, self.debrisS3.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisSDestroyed", pDebrisS3)

	local pDebrisS4 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_med.iff", self.debrisS4.x, self.debrisS4.z, self.debrisS4.y, self.debrisS4.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisSDestroyed", pDebrisS4)

	local pDebrisS5 = spawnSceneObject("yavin4", "object/static/destructible/destructible_tato_cave_rock_lg.iff", self.debrisS5.x, self.debrisS5.z, self.debrisS5.y, self.debrisS5.cell, 1, 0, 0, 0)
	createObserver(OBJECTDESTRUCTION, "geonosian_labscreenplay", "notifyDebrisSDestroyed", pDebrisS5)

end

function geonosian_labscreenplay:spawnMobiles()
	spawnMobile("yavin4", "biogenic_crazyguy", 1, -2.8, 10.8, 10.2, 69, 1627781)--biogen_crazy
	spawnMobile("yavin4", "biogenic_securitytech", 1, -48, -18, -31, -180, 1627785)--biogen_security
        spawnMobile("yavin4", "biogenic_scientist_human", 1, 23.8, -32, -83.2, 130, 1627798)--biogen_human
        spawnMobile("yavin4", "biogenic_construction", 1, -134.5, -21.7, -74.8, 90, 1627794)--biogen_constuc
        spawnMobile("yavin4", "biogenic_engineertech", 1,-107.7,-18,-33.8,176,1627790)--biogen_engineer
        spawnMobile("yavin4", "biogenic_assistant", 1, -36, -21.9, -162.8, 0, 1627803)--biogen_assistant
        spawnMobile("yavin4", "biogenic_scientist_generic_01", 1, -72.0, -34, -272.9, 0, 1627812)--biogen_gen01
	spawnMobile("yavin4", "biogenic_scientist_generic_02", 1, -127.2, -34, -189.0, -93, 1627815)--biogen_gen02
        spawnMobile("yavin4", "biogenic_scientist_geonosian", 1, 7.4, -22, -333, 180, 1627822) -- biogen_geo
	spawnMobileRandom("yavin4", "acklay",self.timers.acklay,101.1,-34.3,-321.6,-136,1627823)
        spawnMobileRandom("yavin4", "enhanced_gaping_spider",self.timers.fbspider,-130,-22.1,-85,-180,1627794)
        spawnMobile("yavin4", "imperial_observer",300,-23,-22,-116,-90,1627802)
        spawnMobile("yavin4", "imperial_observer",300,-16.4,-22,-114.5,-150,1627802)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,1.2,9.1,-8.1,63,1627781)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,0.6,9.5,-3.5,99,1627781)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,26.6,10.3,-13.3,-8,1627782)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,32.3,9.5,-8.1,-105,1627782)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,34.7,10.3,-14.4,-70,1627782)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,37.4,9.8,-8.2,-109,1627782)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-55.9,-18,-33.9,95,1627785)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-55.6,-18,-43.2,72,1627785)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-38.7,-18,-47.5,-75,1627785)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-66.7,-19,-41.2,-77,1627788)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-70.5,-18.9,-34.5,-161,1627788)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-83.9,-18.5,-42.3,85,1627788)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-36,-22,-151.4,180,1627803)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-26.8,-22.9,-158,-90,1627803)
        spawnMobile("yavin4", "crazed_geonosian_guard",300,-19.4,-22.6,-151.7,-135,1627803)
        spawnMobile("yavin4", "cavern_spider",300,-62,-21.8,-109.6,0,1627792)
        spawnMobile("yavin4", "cavern_spider",300,-48,-21.8,-158,0,1627800)
        spawnMobile("yavin4", "cavern_spider",300,-48,-21.8,-143,0,1627800)
        spawnMobile("yavin4", "cavern_spider",300,-41,-21.8,-136,-90,1627801)
        spawnMobile("yavin4", "cavern_spider",300,-88.3,-21.8,-110.3,210,1627793)
        spawnMobile("yavin4", "cavern_spider",300,-98,-21.9,-114.7,50,1627793)
        spawnMobile("yavin4", "cavern_spider",300,-107.3,-22.2,-96.6,180,1627793)
        spawnMobile("yavin4", "cavern_spider",300,-108,-21.8,-126,0,1627793)
        spawnMobile("yavin4", "cavern_spider",300,-123,-22,-109.5,80,1627793)
        spawnMobile("yavin4", "cavern_spider",300,-134.7,-20.9,-112.2,77,1627793)
        spawnMobile("yavin4", "alert_droideka",300,-34.2,-22,-128,-180,1627801)
        spawnMobile("yavin4", "alert_droideka",300,-3.8,-30.2,-92,-180,1627796)
	spawnMobile("yavin4", "cavern_spider",300,-16.8,-30.2,-115.1,22,1627796)
        spawnMobile("yavin4", "alert_droideka",300,-18,-18,-36,0,1627784)
        spawnMobile("yavin4", "alert_droideka",300,-62,-18,-59.5,-180,1627786)
        spawnMobile("yavin4", "alert_droideka",300,-90.5,-18,-76,0,1627789)
        spawnMobile("yavin4", "alert_droideka",300,-53.5,-18.2,-81.7,-90,1627791)
        spawnMobile("yavin4", "alert_droideka",300,-108,-34,-214,89,1627808)
        spawnMobile("yavin4", "alert_droideka",300,-61.5,-34,-252,-90,1627811)
	spawnMobile("yavin4", "geonosian_scientist",300,-116.5,-20,-38.4,88,1627790)
	spawnMobile("yavin4", "enhanced_kwi",300,9.5,-16.0,-27.9,89,1627824)
	spawnMobile("yavin4", "enhanced_kwi",300,10.8,-6.3,-7.8,-93,1627824)
        spawnMobile("yavin4", "enhanced_kwi",300,-104.2,-28.7,-193.4,0,1627807)
	spawnMobile("yavin4", "enhanced_kwi",300,-143.2,-34,-180.8,-139,1627815)
	spawnMobile("yavin4", "enhanced_kliknik",300,-129.0,-34,-192.6,-32,1627815)
	spawnMobile("yavin4", "geonosian_scientist",300,-124.3,-34.0,-199.5,-60,1627815)
	spawnMobile("yavin4", "geonosian_scientist",300,-60.0,-34.0,-273.7,0,1627812)
	spawnMobile("yavin4", "alert_droideka",300,-63.9,-22.0,-143.0,-3,1627804)
	spawnMobile("yavin4", "alert_droideka",300,-129.8,-34.0,-267.9,87,1627816)
        spawnMobile("yavin4", "enhanced_kliknik",300,26,-31.5,-78,170,1627798)
        spawnMobile("yavin4", "enhanced_kliknik",300,36.5,-29.9,-82.7,-120,1627798)
        spawnMobile("yavin4", "enhanced_kliknik",300,29.5,-30.1,-88,-45,1627798)
	spawnMobile("yavin4", "enhanced_kliknik",300,-139.8,-34,-194.3,57,1627815)
	spawnMobile("yavin4", "enhanced_kliknik",300,-64.9,-34,-266.5,-143,1627812)
	spawnMobile("yavin4", "enhanced_kwi",300,-66.5,-34,-283.1,35,1627812)
        spawnMobile("yavin4", "enhanced_kliknik",300,-87,-34.1,-386.5,210,1627819)
	spawnMobile("yavin4", "cavern_spider",300,-128.2,-34.4,-322.4,-30,1627817)
	spawnMobile("yavin4", "cavern_spider",300,-143.5,-33.5,-321.7,134,1627817)
	spawnMobile("yavin4", "cavern_spider",300,-131.1,-33.9,-339.0,145,1627817)
	spawnMobile("yavin4", "cavern_spider",300,-135.5,-33.8,-342.8,-1,1627817)
	spawnMobile("yavin4", "cavern_spider",300,-118.9,-34.0,-349.2,-98,1627818)
	spawnMobile("yavin4", "cavern_spider",300,-134.5,-34.0,-373.2,-2,1627818)
	spawnMobile("yavin4", "enhanced_kliknik",300,-129.4,-33.6,-384.1,-2,1627818)
        spawnMobile("yavin4", "enhanced_force_kliknik",300,-86.5,-33.9,-372.8,-91,1627819)
        spawnMobile("yavin4", "enhanced_force_kliknik",300,-88.0,-34.6,-365.9,-102,1627819)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,-71.5,-34,-348.1,-95,1627819)
        spawnMobile("yavin4", "enhanced_force_kliknik",300,-72.6,-33.8,-376.0,-168,1627819)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,-72.7,-34.2,-382.5,-179,1627819)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,-69.0,-34.0,-407.2,-7,1627820)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,-46.8,-34.0,-407.5,92,1627820)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,-28.5,-34.2,-408.4,-27,1627820)
	spawnMobile("yavin4", "alert_droideka",300,-11.9,-34.0,-412.5,179,1627821)
	spawnMobile("yavin4", "cavern_spider",300,4.1,-34.0,-402.4,171,1627822)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,16.5,-34.0,-368.3,161,1627822)
	spawnMobile("yavin4", "enhanced_kliknik",300,24.0,-34.0,-397.1,117,1627822)
	spawnMobile("yavin4", "enhanced_force_kliknik",300,22.9,-34.0,-370.1,11,1627822)
	spawnMobile("yavin4", "cavern_spider",300,24.8,-24.0,-333.8,87,1627822)
	spawnMobile("yavin4", "cavern_spider",300,13.3,-24.0,-341.6,89,1627822)
	spawnMobile("yavin4", "cavern_spider",300,13.4,-22.0,-337.3,-179,1627822)
	spawnMobile("yavin4", "enhanced_kwi",300,48.0,-34.0,-334.4,0,1627823)
	spawnMobile("yavin4", "cavern_spider",300,91.2,-33.9,-347.9,5,1627823)
	spawnMobile("yavin4", "enhanced_kliknik",300,98.0,-34.1,-334.4,-53,1627823)
	spawnMobile("yavin4", "enhanced_kliknik",300,120.2,-33.9,-330.6,-33,1627823)
	spawnMobile("yavin4", "cavern_spider",300,85.0,-33.8,-309.1,143,1627823)
	spawnMobile("yavin4", "cavern_spider",300,74.7,-34.1,-329.0,-90,1627823)
	spawnMobile("yavin4", "mercenary_sentry",300,-74.9,-22,-153.7,-119,1627805)
	spawnMobile("yavin4", "mercenary_sentry",300,-74.3,-22,-162.3,-40,1627805)
	spawnMobile("yavin4", "mercenary_sentry",300,-82.3,-22,-161.7,74,1627805)
	spawnMobile("yavin4", "mercenary_sentry",300,-82.2,-22,-155.1,106,1627805)
end

function geonosian_labscreenplay:notifyGasValveUsed(pGasValve, pPlayer, radialSelected)
	if (radialSelected == 20) then
		local player = LuaCreatureObject(pPlayer)
		local isGasLeaking = readData("geonosian_lab:gasleak")
		
		if (isGasLeaking == 1) then
			player:sendSystemMessage("@dungeon/geonosian_madbio:gas_off") --You have shut off the gas leak.
			writeData("geonosian_lab:gasleak", 0)
			createEvent(self.poisonShutoffDuration, "geonosian_labscreenplay", "restartGasLeak", pGasValve)
		else
				player:sendSystemMessage("@dungeon/geonosian_madbio:gas_already_off") --The gas leak has already been repaired...
		end
	end
end

function geonosian_labscreenplay:notifyKeypadUsed(pKeypad, pPlayer, radialSelected)
	if (radialSelected == 20) then
		--We need to show to the user the keypad sui.
		local suiManager = LuaSuiManager()
		suiManager:sendKeypadSui(pKeypad, pPlayer, "geonosian_labscreenplay", "keypadSuiCallback")
	end
end

function geonosian_labscreenplay:restartGasLeak(pGasLeak)
	writeData("geonosian_lab:gasleak", 1)
end

function geonosian_labscreenplay:keypadSuiCallback(pCreature, pSui, cancelPressed, enteredCode)
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
			updateCellPermission(pCell, 1, pCreature)
		end
	else
		player:sendSystemMessage("@dungeon/geonosian_madbio:bad_code") --The number that you entered is not a valid code for this door.
	end
end

function geonosian_labscreenplay:notifyEnteredLab(pBuilding, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	
	if (player:isAiAgent()) then
		return 0
	end
	
	for k, v in pairs(self.lockedCells) do
		local pCell = getSceneObject(v) 
		
		if (pCell ~= nil) then
			updateCellPermission(pCell, 0, pPlayer)
			player:removeScreenPlayState(geonosian_labscreenplay.states.datapad.done, "geonosian_lab")
			player:removeScreenPlayState(geonosian_labscreenplay.states.tenloss.done, "geonosian_lab")
			player:removeScreenPlayState(geonosian_labscreenplay.states.tenloss.noreward, "geonosian_lab")	
		end
	end
	
	player:sendSystemMessage("@dungeon/geonosian_madbio:relock") --Security systems at this facility have been cycled and reset.
end

--------------------------------------
--   ActiveArea observers            -
--------------------------------------
function geonosian_labscreenplay:notifyEnteredPoisonGas(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (not player:isAiAgent()) then
			--Check if gas is currently leaking
			local isGasLeaking = readData("geonosian_lab:gasleak")
			
			if (isGasLeaking == 1) then
				--Check for rebreathing mod
				if (self:hasRebreather(movingObject) == 1) then 
					player:sendSystemMessage("@dungeon/geonosian_madbio:gasmask") --Your gasmask diffuses the poison gas and you are able to breathe with no difficulty.
				else
					local activeArea = LuaSceneObject(pActiveArea)

					player:addDotState(POISONED, math.random(20) + 80, HEALTH, 1000, 2000, activeArea:getObjectID(), 0)

					player:sendSystemMessage("@dungeon/geonosian_madbio:toxic_fumes") --You breathe in toxic fumes!
				end
			end
		end
	end
	
	return 0
end

function geonosian_labscreenplay:notifyEnteredPoisonGasStrong(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		
		if (not player:isAiAgent()) then
			--Check if gas is currently leaking
			local isGasLeaking = readData("geonosian_lab:gasleak")
			
			if (isGasLeaking == 1) then
				--Check for rebreathing mod
				if (self:hasRebreather(movingObject) == 1) then
					player:sendSystemMessage("@dungeon/geonosian_madbio:gasmask") --Your gasmask diffuses the poison gas and you are able to breathe with no difficulty.
				else
					local activeArea = LuaSceneObject(pActiveArea)

					player:addDotState(POISONED, math.random(100) + 200, HEALTH, 1000, 2000, activeArea:getObjectID(), 0)
					player:sendSystemMessage("@dungeon/geonosian_madbio:toxic_fumes") --You breathe in toxic fumes!
				end
			end
		end
	end
	
	return 0
end


function geonosian_labscreenplay:notifyElectroShock(pActiveArea, pMovingObject)
	local movingObject = LuaSceneObject(pMovingObject)
	
	if (movingObject:isCreatureObject()) then
		local player = LuaCreatureObject(pMovingObject)
		local objectID = player:getObjectID()
		local activeArea = LuaSceneObject(pActiveArea)
		player:inflictDamage(pMovingObject, 0, 1000, 0)
		player:sendSystemMessage("@dungeon/geonosian_madbio:shock") --You feel electricity coursing through your body! 
	end

end


function geonosian_labscreenplay:hasRebreather(scno)
	--TODO: Change this to be a skill mod check for private_poison_rebreather
	local pRebreather = scno:getSlottedObject("eyes")

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

function geonosian_labscreenplay:respawnMDebris(pDebrisM)
	if (pDebrisM == nil) then
		return
	end
	
	local pCell = getSceneObject(self.debrisM.cell)
	
	if (pCell ~= nil) then
		local cell = LuaSceneObject(pCell)
		local debris = LuaTangibleObject(pDebrisM)
		debris:setConditionDamage(0, false)
		cell:transferObject(pDebrisM, -1, true)
	end
end

function geonosian_labscreenplay:notifyDebrisMDestroyed(pDebrisM, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	local debris = LuaSceneObject(pDebrisM)
	debris:destroyObjectFromWorld()
	player:clearCombatState(1)
	
	createEvent(self.debrisM.respawn, "geonosian_labscreenplay", "respawnMDebris", pDebrisM)
	
	return 0
end

function geonosian_labscreenplay:respawnADebris(pDebrisA1)
	if (pDebrisA1 == nil) then
		return
	end
	
	local pCell = getSceneObject(self.debrisA1.cell)
	
	if (pCell ~= nil) then
		local cell = LuaSceneObject(pCell)
		local debris = LuaTangibleObject(pDebrisA1)
		debris:setConditionDamage(0, false)
		cell:transferObject(pDebrisA1, -1, true)
	end
end

function geonosian_labscreenplay:notifyDebrisADestroyed(pDebrisA1, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	local debris = LuaSceneObject(pDebrisA1)
	debris:destroyObjectFromWorld()
	player:clearCombatState(1)
	
	createEvent(self.debrisA1.respawn, "geonosian_labscreenplay", "respawnADebris", pDebrisA1)
	createEvent(self.debrisA2.respawn, "geonosian_labscreenplay", "respawnADebris", pDebrisA2)
	createEvent(self.debrisA3.respawn, "geonosian_labscreenplay", "respawnADebris", pDebrisA3)
	createEvent(self.debrisA4.respawn, "geonosian_labscreenplay", "respawnADebris", pDebrisA4)
	
	return 0
end

function geonosian_labscreenplay:respawnHDebris(pDebrisH1)
	if (pDebrisH1 == nil) then
		return
	end
	
	local pCell = getSceneObject(self.debrisH1.cell)
	
	if (pCell ~= nil) then
		local cell = LuaSceneObject(pCell)
		local debris = LuaTangibleObject(pDebrisH1)
		debris:setConditionDamage(0, false)
		cell:transferObject(pDebrisH1, -1, true)
	end
end

function geonosian_labscreenplay:notifyDebrisHDestroyed(pDebrisH1, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	local debris = LuaSceneObject(pDebrisH1)
	debris:destroyObjectFromWorld()
	player:clearCombatState(1)
	
	createEvent(self.debrisH1.respawn, "geonosian_labscreenplay", "respawnHDebris", pDebrisH1)
	createEvent(self.debrisH1.respawn, "geonosian_labscreenplay", "respawnHDebris", pDebrisH2)
	createEvent(self.debrisH1.respawn, "geonosian_labscreenplay", "respawnHDebris", pDebrisH3)
	createEvent(self.debrisH1.respawn, "geonosian_labscreenplay", "respawnHDebris", pDebrisH4)
	createEvent(self.debrisH1.respawn, "geonosian_labscreenplay", "respawnHDebris", pDebrisH5)
	
	return 0
end

function geonosian_labscreenplay:respawnSDebris(pDebrisS1)
	if (pDebrisS1 == nil) then
		return
	end
	
	local pCell = getSceneObject(self.debrisS1.cell)
	
	if (pCell ~= nil) then
		local cell = LuaSceneObject(pCell)
		local debris = LuaTangibleObject(pDebrisS1)
		debris:setConditionDamage(0, false)
		cell:transferObject(pDebrisS1, -1, true)
	end
end

function geonosian_labscreenplay:notifyDebrisSDestroyed(pDebrisS1, pPlayer)
	local player = LuaCreatureObject(pPlayer)
	local debris = LuaSceneObject(pDebrisS1)
	debris:destroyObjectFromWorld()
	player:clearCombatState(1)
	
	createEvent(self.debrisS1.respawn, "geonosian_labscreenplay", "respawnSDebris", pDebrisS1)
	createEvent(self.debrisS1.respawn, "geonosian_labscreenplay", "respawnSDebris", pDebrisS2)
	createEvent(self.debrisS1.respawn, "geonosian_labscreenplay", "respawnSDebris", pDebrisS3)
	createEvent(self.debrisS1.respawn, "geonosian_labscreenplay", "respawnSDebris", pDebrisS4)
	createEvent(self.debrisS1.respawn, "geonosian_labscreenplay", "respawnSDebris", pDebrisS5)
	
	return 0
end

function geonosian_labscreenplay:giveGeoDatapad(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	local player = LuaSceneObject(pPlayer)
	local pPlayerObject = player:getSlottedObject("ghost")
	local playerObject = LuaPlayerObject(pPlayerObject)
	local pInventory = player:getSlottedObject("inventory")
	local pBackpack = player:getSlottedObject("back")
	
	if (pInventory ~= nil) and (pBackpack ~= nil) then
		local pDatapadMain = getContainerObjectByTemplate(pInventory, geonosian_labscreenplay.geoDatapad, true)
		local pDatapadPack = getContainerObjectByTemplate(pBackpack, geonosian_labscreenplay.geoDatapad, true)
		
		if (pDatapadMain == nil) and (pDatapadPack == nil) then

			local pItem = giveItem(pInventory, self.geoDatapad, -1)
	
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(pPlayer)
			end
			
		end

	end

	if (pInventory ~= nil) and (pBackpack == nil) then
		local pDatapadMain = getContainerObjectByTemplate(pInventory, geonosian_labscreenplay.geoDatapad, true)

		if (pDatapadMain == nil) then
		
			local pItem = giveItem(pInventory, self.geoDatapad, -1)
	
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(pPlayer)
			
			end
	
		end

	end

	return

end

function geonosian_labscreenplay:giveGeoTenloss(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	local player = LuaSceneObject(pPlayer)
	local pPlayerObject = player:getSlottedObject("ghost")
	local playerObject = LuaPlayerObject(pPlayerObject)
	local pInventory = player:getSlottedObject("inventory")
	local pBackpack = player:getSlottedObject("back")
	

	if (pInventory ~= nil) and (pBackpack ~= nil) then
		local pTenlossMain = getContainerObjectByTemplate(pInventory, geonosian_labscreenplay.geoTenloss, true)
		local pTenlossPack = getContainerObjectByTemplate(pBackpack, geonosian_labscreenplay.geoTenloss, true)

		if (pTenlossMain == nil) and (pTenlossPack == nil) then
		
			local pItem = giveItem(pInventory, self.geoTenloss, -1)
	
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(pPlayer)
	
			end

		end

	end

	if (pInventory ~= nil) and (pBackpack == nil) then
		local pTenlossMain = getContainerObjectByTemplate(pInventory, geonosian_labscreenplay.geoTenloss, true)

		if (pTenlossMain == nil) then
		
			local pItem = giveItem(pInventory, self.geoTenloss, -1)
	
			if (pItem ~= nil) then
				local item = LuaSceneObject(pItem)
				item:sendTo(pPlayer)
			
			end
	
		end

	end

	return

end
--------------------------------------
--   Common functions                -
--------------------------------------
function geonosian_labscreenplay:hasState(player, state)
	if (player == nil) then
		return false
	end
	
	local val = player:hasScreenPlayState(state, "geonosian_lab")
	
	if (val == 1) then
		return true
	end
	
	return false
end

function geonosian_labscreenplay:hasSpawned(objectID, key)
	local val = readData(objectID .. ":geonosian_lab:spawned:" .. key)
	
	if (val == 1) then
		return true
	end
	
	return false
end

function geonosian_labscreenplay:setSpawned(objectID, key)
	writeData(objectID .. ":geonosian_lab:spawned:" .. key)
end

function geonosian_labscreenplay:deleteSpawned(objectID, key)
	deleteData(objectID .. ":geonosian_lab:spawned:" .. key)
end

function geonosian_labscreenplay:writeObjectData(objectID, key, value)
	writeData(objectID .. ":geonosian_lab:" .. key, value)
end

function geonosian_labscreenplay:readObjectData(objectID, key)
	return readData(objectID .. ":geonosian_lab:" .. key)
end

function geonosian_labscreenplay:deleteObjectData(objectID, key)
	deleteData(objectID .. ":geonosian_lab:" .. key)
end

function geonosian_labscreenplay:setState(creatureObject, state)
	creatureObject:setScreenPlayState(state, "geonosian_lab")
end

function geonosian_labscreenplay:removeState(creatureObject, state)
	creatureObject:removeScreenPlayState(state, "geonosian_lab")
end
