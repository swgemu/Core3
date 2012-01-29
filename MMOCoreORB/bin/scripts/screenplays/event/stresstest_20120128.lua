stresstest_20120128 = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("stresstest_20120128", true)

--------------------------------------
--   Initialize screenplay           -
--------------------------------------
function stresstest_20120128:start()
	--if (not isZoneEnabled("corellia")) or (not isZoneEnabled("naboo")) or (not isZoneEnabled("tatooine")) then
		--return 0
	--end
	
	self:spawnSceneObjects()
	self:spawnMobiles()
end

function stresstest_20120128:spawnMobiles()
	local pShuttle = spawnMobile("corellia", "lambda_shuttle", 1, -147.3, 28, -4781.8, 0, 0)
	local shuttle = LuaCreatureObject(pShuttle)
	shuttle:setOptionsBitmask(256)
	shuttle:setPosture(PRONE)
	
	local pShuttle2 = spawnMobile("corellia", "lambda_shuttle", 1, -169.3, 28, -4781.8, 0, 0)
	local shuttle2 = LuaCreatureObject(pShuttle2)
	shuttle2:setOptionsBitmask(256)
	shuttle2:setPosture(PRONE)
	
	local pShuttle3 = spawnMobile("yavin4", "lambda_shuttle", 1, -6489.4, 84.5, -454.3, 9, 0)
	local shuttle3 = LuaCreatureObject(pShuttle3)
	shuttle3:setOptionsBitmask(256)
	shuttle3:setPosture(PRONE)
	
	local pBarker = spawnMobile("corellia", "stresstest_shuttleloc_barker", 1, -149, 28, -4706, 140, 0)
	local barker = LuaCreatureObject(pBarker)
	barker:setOptionsBitmask(256)
	self:barkShuttleLocation(pBarker)
end

function stresstest_20120128:spawnSceneObjects()
	local pCollector = spawnSceneObject("corellia", "object/tangible/furniture/imperial/data_terminal_s1.iff", -149, 28, -4783 , 0, 1, 0, 0, 0)
	local collector = LuaSceneObject(pCollector)
	local col2creo = LuaCreatureObject(pCollector)
	col2creo:setOptionsBitmask(264)
	collector:setCustomObjectName("\\#ee3377Travel to the Death Watch Bunker")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportDWB", pCollector)
	
	local pCollector2 = spawnSceneObject("corellia", "object/tangible/furniture/imperial/data_terminal_s1.iff", -171, 28, -4783 , 0, 1, 0, 0, 0)
	local collector2 = LuaSceneObject(pCollector2)
	local col2creo = LuaCreatureObject(pCollector2)
	col2creo:setOptionsBitmask(264)
	collector2:setCustomObjectName("\\#33ee77Travel to the Geonosian Bio Lab")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportGEO", pCollector2)
	
	--Return from DWB
	local pCollector3 = spawnSceneObject("endor", "object/tangible/furniture/imperial/data_terminal_s1.iff", -4660.2, 12.8, 4286 , 0, 0.707107, 0, 0.707107, 0)
	local collector3 = LuaSceneObject(pCollector3)
	local col3creo = LuaCreatureObject(pCollector3)
	col3creo:setOptionsBitmask(264)
	collector3:setCustomObjectName("\\#ee3377Travel to Coronet, Corellia")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportCnet", pCollector3)
	
	--DWB BLUEFROG
	spawnSceneObject("endor", "object/tangible/terminal/terminal_character_builder.iff", -4654.5, 14.6, 4332.6, 0, 0, 0, 1, 0)
	
	--GEO BLUEFROG
	spawnSceneObject("yavin4", "object/tangible/terminal/terminal_character_builder.iff", -6479.1, 84.2, -435.3, 0, 0.4771588, 0, -0.8788171, 0)
	
	--Return from GEO
	local pCollector4 = spawnSceneObject("yavin4", "object/tangible/furniture/imperial/data_terminal_s1.iff", -6493.1, 84.2, -452.3, 0, 0.996917, 0, 0.078459, 0)
	local collector4 = LuaSceneObject(pCollector4)
	local col4creo = LuaCreatureObject(pCollector4)
	col4creo:setOptionsBitmask(264)
	collector4:setCustomObjectName("\\#33ee77Travel to Coronet, Corellia")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportCnet", pCollector4)
end

function stresstest_20120128:barkShuttleLocation(pBarker)
	if (pBarker ~= nil) then
		spatialChat(pBarker, "\\#881100Greetings Testers!\n\nPlease proceed to the shuttles near South Coronet (-154 -4767). Double click the terminals at these locations to arrive at the focus destination. Character Builder Terminals will be available at your destination.\n\nThanks for testing!")
		createEvent(15000, "stresstest_20120128", "barkShuttleLocation", pBarker)
	end
end

function stresstest_20120128:teleportDWB(pCollector, pPlayer)
	local player = LuaSceneObject(pPlayer)
	player:switchZone("endor", -4650, 0, 4294, 0)
end

function stresstest_20120128:teleportGEO(pCollector, pPlayer)
	local player = LuaSceneObject(pPlayer)
	player:switchZone("yavin4", -6490, 0, -446, 0)
end

function stresstest_20120128:teleportCnet(pCollector, pPlayer)
	local player = LuaSceneObject(pPlayer)
	player:switchZone("corellia", -159, 28, -4774, 0)
end