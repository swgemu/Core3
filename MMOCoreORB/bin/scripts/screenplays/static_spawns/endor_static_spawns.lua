--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
EndorStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "EndorStaticSpawnsScreenPlay",
}

registerScreenPlay("EndorStaticSpawnsScreenPlay", true)

function EndorStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

	--Donkuwah Hut 4031 -7668
	spawnMobile("endor", "tainted_donkuwah_dark_shaman",300, 4031.5, 0.8, -7668.1, -34, 0)

end
