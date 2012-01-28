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

function stresstest_20120128:spawnSceneObjects()
	local pShuttle = spawnSceneObject("corellia", "object/creature/npc/theme_park/lambda_shuttle.iff", -147.3, 28, -4781.8, 0, 1, 0, 0, 0)
	local shuttle = LuaCreatureObject(pShuttle)
	shuttle:setPosture(PRONE)
	
	local pShuttle2 = spawnSceneObject("corellia", "object/creature/npc/theme_park/lambda_shuttle.iff", -169.3, 28, -4781.8, 0, 1, 0, 0, 0)
	local shuttle2 = LuaCreatureObject(pShuttle2)
	shuttle2:setPosture(PRONE)
end

function stresstest_20120128:spawnMobiles()
	local pCollector = spawnSceneObject("corellia", "object/mobile/space_comm_civilian_05.iff", -148, 28, -4783 , 0, 1, 0, 0, 0)
	local collector = LuaSceneObject(pCollector)
	local col2creo = LuaCreatureObject(pCollector)
	col2creo:setOptionsBitmask(136)
	collector:setCustomObjectName("\\#ee3377Travel to the Death Watch Bunker")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportDWB", pCollector)
	
	local pCollector2 = spawnSceneObject("corellia", "object/mobile/space_comm_aynat_ace_03.iff", -170, 28, -4783 , 0, 1, 0, 0, 0)
	local collector2 = LuaSceneObject(pCollector2)
	local col2creo = LuaCreatureObject(pCollector2)
	col2creo:setOptionsBitmask(136)
	collector2:setCustomObjectName("\\#33ee7700Travel to Geonosian Bio Lab")
	createObserver(OBJECTRADIALUSED, "stresstest_20120128", "teleportGEO", pCollector2)
end

function stresstest_20120128:teleportDWB(pCollector, pPlayer)
	local player = LuaSceneObject(pPlayer)
	player:switchZone("endor", -4650, 0, 4294, 0)
end

function stresstest_20120128:teleportGEO(pCollector, pPlayer)
	local player = LuaSceneObject(pPlayer)
	player:switchZone("yavin4", -6490, 0, -446, 0)
end