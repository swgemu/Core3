--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
local ObjectManager = require("managers.object.object_manager")

CorelliaStaticSpawnsScreenPlay = ScreenPlay:new
	{
		numberOfActs = 1,

		screenplayName = "CorelliaStaticSpawnsScreenPlay",

		turret = { template = "object/installation/turret/turret_dish_sm.iff", x = 4111.26, z = 24, y = -1274.28 }

}

registerScreenPlay("CorelliaStaticSpawnsScreenPlay", true)

function CorelliaStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:spawnSceneObjects()
	end
end

function CorelliaStaticSpawnsScreenPlay:spawnSceneObjects()
	local turretData = self.turret
	local pTurret = spawnSceneObject("corellia", turretData.template, turretData.x, turretData.z, turretData.y, 0, 0, 0, -1, 0)

	if pTurret ~= nil then
		local turret = TangibleObject(pTurret)
		turret:setFaction(FACTIONREBEL)
		turret:setPvpStatusBitmask(1)
	end

	createObserver(OBJECTDESTRUCTION, "CorelliaStaticSpawnsScreenPlay", "notifyTurretDestroyed", pTurret)

	spawnSceneObject("corellia", "object/static/vehicle/static_speeder_bike.iff", 615.7, 26.1, -434.0, 0, math.rad(84) )
	spawnSceneObject("corellia", "object/static/structure/general/droid_probedroid_powerdown.iff", 640.5, 27.1, -424.0, 0, math.rad(-138) )

end

function CorelliaStaticSpawnsScreenPlay:notifyTurretDestroyed(pTurret, pPlayer)
	if (pTurret == nil) then
		return 1
	end

	SceneObject(pTurret):destroyObjectFromWorld()
	createEvent(1800, "CorelliaStaticSpawnsScreenPlay", "respawnTurret", pTurret, "")

	CreatureObject(pPlayer):clearCombatState(1)
	return 0
end

function CorelliaStaticSpawnsScreenPlay:respawnTurret(pTurret)
	if pTurret == nil then return end

	TangibleObject(pTurret):setConditionDamage(0, false)
	local pZone = getZoneByName("corellia")

	if pZone == nil then return end

	SceneObject(pZone):transferObject(pTurret, -1, true)
end

function CorelliaStaticSpawnsScreenPlay:spawnMobiles()

	--random Power Plant (643 -429)
	local pNpc = spawnMobile("corellia", "twilek_slave", 60,621.013,26.31,-435.848,-50,0)
	self:setMoodString(pNpc, "sad")
	pNpc = spawnMobile("corellia", "surgical_droid_21b", 60,632.614,26.8166,-438.739,135,0)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "twilek_slave", 60,637.195,26.9908,-434.182,135,0)
	self:setMoodString(pNpc, "npc_use_terminal_high")
	pNpc = spawnMobile("corellia", "r4", 60,637.837,27.0342,-433.138,-172,0)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "r5", 60,620.512,26.3006,-437.168,-25,0)
	self:setMoodString(pNpc, "worried")
	pNpc = spawnMobile("corellia", "seeker", 60,626.362,26.6092,-440.824,-45,0)
	self:setMoodString(pNpc, "neutral")
	pNpc = spawnMobile("corellia", "contractor", 60,618.957,26.2465,-433.424,130,0)
	self:setMoodString(pNpc, "angry")

	--Rebels vs Imps (4112 -1252) Smoking small Rebel base
	spawnMobile("corellia", "rebel_army_captain", 360,5.2,0.1,-3.6,-93,6036092)
	spawnMobile("corellia", "rebel_medic", 360,-4.4,0.1,-1.2,-11,6036093)
	spawnMobile("corellia", "rebel_commando", 360,4110.3,24,-1260.3,-179,0)
	spawnMobile("corellia", "rebel_commando", 360,4113.2,24,-1260.4,-179,0)
	spawnMobile("corellia", "rebel_trooper", 360,4096.2,24,-1271.5,83,0)
	spawnMobile("corellia", "rebel_first_lieutenant", 360,4098.3,24,-1271.4,-91,0)
	spawnMobile("corellia", "at_st", 360,4110.43,24.008,-1297.13,7,0)
	spawnMobile("corellia", "stormtrooper", 360, 4106.75,23.9281,-1295.73,7,0)
	spawnMobile("corellia", "stormtrooper", 360,4117.07,24.2994,-1293.08,-7,0)
	spawnMobile("corellia", "imperial_sergeant", 360, 4115.11,24.0521,-1289.97,-5,0)
	spawnMobile("corellia", "imperial_trooper", 360, 4142.95,24,-1267.66,-77,0)
	spawnMobile("corellia", "imperial_trooper", 360, 4132.13,24,-1269.63,-75,0)
	spawnMobile("corellia", "imperial_trooper", 360, 4075.41,26.4493,-1269.93,90,0)
	spawnMobile("corellia", "imperial_trooper", 360, 4066.41,35.4493,-1268.93,90,0)

	--Imperial Detachment HQ (-2975 2908) Outside Kor Vella, populated in city kor_vella screenplay

	-- Research Camp (-1421 1980)
	spawnMobile("corellia", "commoner_technician", 1, -1416.0, 85.2822, 1985.7, 25, 0)
	spawnMobile("corellia", "scientist", 1, -1419.6, 85.2822, 1985.4, -55, 0)
	spawnMobile("corellia", "r4", 1, -1423.0, 85.2822, 1986.6, 93, 0)
	spawnMobile("corellia", "scientist", 1, -1424.6, 85.2822, 1977.2, -9, 0)
	spawnMobile("corellia", "scientist", 1, -1425.6, 85.2822, 1979.5, 139, 0)
	spawnSceneObject("corellia", "object/tangible/furniture/all/frn_all_toolchest_lg_s01.iff", -1415.72, 85.2822, 1987.44, 0, -0.2, 0, 0.9, 0 )
	spawnSceneObject("corellia", "object/tangible/furniture/all/frn_all_toolchest_med_s01.iff", -1414.63, 85.2822, 1986.44, 0, -0.4, 0, 0.9, 0 )
	spawnSceneObject("corellia", "object/tangible/camp/campfire_logs_smoldering.iff", -1424.5, 85.2822, 1978.57, 0, 1, 0, 0, 0 )
	spawnSceneObject("corellia", "object/tangible/camp/camp_light_s2.iff", -1419.5, 85.2822, 1981.3, 0, 1, 0, 0, 0 )
	spawnSceneObject("corellia", "object/tangible/camp/camp_light_s2.iff", -1423.3, 85.2822, 1981.3, 0, 1, 0, 0, 0 )
	spawnSceneObject("corellia", "object/tangible/camp/camp_stool_tall.iff", -1419.5, 85.2822, 1978.6, 0, 1, 0, 0, 0 )
	spawnSceneObject("corellia", "object/tangible/camp/camp_stool_tall.iff", -1420.0, 85.2822, 1976.9, 0, 1, 0, 0, 0 )

	--Abandoned Tower (4950, 2900)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + 4976, 3.5, getRandomNumber(5) + 2888, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + 4976, 3.5, getRandomNumber(5) + 2888, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + 4976, 3.5, getRandomNumber(5) + 2888, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + 4976, 3.5, getRandomNumber(5) + 2888, getRandomNumber(360), 0)

	--Forgotten Spires (750, 2500)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + 755, 393.6, getRandomNumber(10) + 2509, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + 755, 393.6, getRandomNumber(10) + 2509, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + 755, 393.6, getRandomNumber(10) + 2509, getRandomNumber(360), 0)

	--Mysterious Shrine (-6900, 4500)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -6919, 449.7, getRandomNumber(5) + 4506, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -6919, 449.7, getRandomNumber(5) + 4506, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -6919, 449.7, getRandomNumber(5) + 4506, getRandomNumber(360), 0)

	--Rock Formations (-1650, 6850)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + -1686, 375.3, getRandomNumber(10) + 6885, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + -1686, 375.3, getRandomNumber(10) + 6885, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(10) + -1686, 375.3, getRandomNumber(10) + 6885, getRandomNumber(360), 0)

	--Weather Station (-7400, -3900)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -7482, 236.8, getRandomNumber(5) + -3955, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -7482, 236.8, getRandomNumber(5) + -3955, getRandomNumber(360), 0)
	spawnMobile("corellia", "vicious_slice_hound", 300, getRandomNumber(5) + -7482, 236.8, getRandomNumber(5) + -3955, getRandomNumber(360), 0)

end
