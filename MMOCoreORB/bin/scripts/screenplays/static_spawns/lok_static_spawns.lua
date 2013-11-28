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

	--Torches andarches 720 -3389
	spawnMobile("lok", "gurk",900,731.6,11.9,-3382,142,0)
	spawnMobile("lok", "gurk",900,708,12,-3397,131,0)
	spawnMobile("lok", "gurk",900,699,12,-3384,-97,0)
	spawnMobile("lok", "gurk",900,704.1,12.1,-3359,16,0)
	spawnMobile("lok", "reclusive_gurk_king",1200,720.3,11.9,-3396.6,130,0)

	--Gurk camp -3763 -3477
	spawnMobile("lok", "gurk",900,-3754.7,63.2,-3477.6,150,0)
	spawnMobile("lok", "gurk",900,-3763.7,62,-3485.9,170,0)
	spawnMobile("lok", "reclusive_gurk_king",1200,-3763.4,62.5,-3477.2,160,0)
end
