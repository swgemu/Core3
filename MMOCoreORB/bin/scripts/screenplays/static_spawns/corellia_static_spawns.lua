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

	--Need to add rest the of static spawns (Incomplete).

	--Rebels vs Imps (4112 -1252) Smoking small Rebel base
	spawnMobile("corellia", "rebel_army_captain", 360,5.2,0.1,-3.6,-93,6036092)
	spawnMobile("corellia", "rebel_medic", 360,-4.4,0.1,-1.2,-11,6036093)

	spawnMobile("corellia", "rebel_trooper", 360,4110.3,24,-1260.3,-179,0)
	spawnMobile("corellia", "rebel_trooper", 360,4113.2,24,-1260.4,-179,0)
	spawnMobile("corellia", "rebel_trooper", 360,4096.2,24,-1271.5,83,0)
	spawnMobile("corellia", "rebel_first_lieutenant", 360,4098.3,24,-1271.4,-91,0)

	--Power Plant (643 -429) Unknown if there are spawns not populated.

	--Imperial Detachment HQ (-2975 2908) Outside Kor Vella, populated in city kor_vella screenplay
end
