--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
LokStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "LokStaticSpawnsScreenPlay",
}

registerScreenPlay("LokStaticSpawnsScreenPlay", true)

function LokStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
	end
end

function LokStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

	--Cave (4772 946) Suppose to be empty? not populated yet

	--Nym Pirate Cave (-2996 -668) Sulfur Lake Pirates Nym themepark part 1 screenplay up for review

	--Mining Cave (6475 3895) "Gas Mine" Nym themepark part 2 needs to be populated

	--Nym Mercenary Bunker (916 -4185) "Research facility" Nym themepark part 3 needs to be populated

	--Rebel House (-4743 3531) Leia Story part 3 needs to be populated

	--Imperial lookout (-2568 -862) Imperial Contact Story part 3 needs to be populated

end
