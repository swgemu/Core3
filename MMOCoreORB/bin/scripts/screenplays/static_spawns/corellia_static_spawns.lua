--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
CorelliaStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "CorelliaStaticSpawnsScreenPlay",
}

registerScreenPlay("CorelliaStaticSpawnsScreenPlay", true)

function CorelliaStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
	end
end

function CorelliaStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

	--Rebels vs Imps (4112 -1252) Smoking small Rebel base
	spawnMobile("corellia", "rebel_army_captain", 30,5.2,0.1,-3.6,-93,6036092)
	spawnMobile("corellia", "rebel_medic", 30,-4.4,0.1,-1.2,-11,6036093)

	spawnMobile("corellia", "rebel_commando", 30,4110.3,24,-1260.3,-179,0)
	spawnMobile("corellia", "rebel_commando", 30,4113.2,24,-1260.4,-179,0)
	spawnMobile("corellia", "rebel_trooper", 30,4096.2,24,-1271.5,83,0)
	spawnMobile("corellia", "rebel_first_lieutenant", 30,4098.3,24,-1271.4,-91,0)
	spawnMobile("corellia", "at_st", 360,4110.43,24.008,-1297.13,7,0)
	spawnMobile("corellia", "stormtrooper", 60, 4106.75,23.9281,-1295.73,7,0)
	spawnMobile("corellia", "stormtrooper", 60,4117.07,24.2994,-1293.08,-7,0)
	spawnMobile("corellia", "imperial_sergeant", 60, 4115.11,24.0521,-1289.97,-5,0)
	spawnMobile("corellia", "imperial_trooper", 60, 4142.95,24,-1267.66,-77,0)
	spawnMobile("corellia", "imperial_trooper", 60, 4132.13,24,-1269.63,-75,0)
	spawnMobile("corellia", "imperial_trooper", 60, 4075.41,26.4493,-1269.93,90,0)
	spawnMobile("corellia", "imperial_trooper", 60, 4066.41,35.4493,-1268.93,90,0)

	--Power Plant (643 -429) Unknown if there are spawns not populated.

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
	
	
end
