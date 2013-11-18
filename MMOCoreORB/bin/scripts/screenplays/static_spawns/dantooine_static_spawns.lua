--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
DantooineStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "DantooineStaticSpawnsScreenPlay",
}

registerScreenPlay("DantooineStaticSpawnsScreenPlay", true)

function DantooineStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
	end
end

function DantooineStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

end
