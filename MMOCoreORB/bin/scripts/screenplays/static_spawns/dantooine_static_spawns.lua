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
	
	-- Vexed Voritor Lizard Spawn (-5500 -1800)
	spawnMobile("dantooine", "vexed_voritor_lizard", 300, -5500, 15, -1780, getRandomNumber(360), 0)
	spawnMobile("dantooine", "vexed_voritor_lizard", 300, -5502, 15, -1790, getRandomNumber(360), 0)
	spawnMobile("dantooine", "vexed_voritor_lizard", 300, -5483, 15, -1777, getRandomNumber(360), 0)
	

end
