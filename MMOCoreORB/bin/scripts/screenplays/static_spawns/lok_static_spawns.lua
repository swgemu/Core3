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

	--Cave (4772 946)
	spawnMobile("lok", "young_spined_snake",720,-26.3,-118.8,-370.0,66,7475374)
	spawnMobile("lok", "kimogila_hatchling",3600,-28.2,-78.7,-353.3,13,7475370)
	spawnMobile("lok", "kimogila_hatchling",3600,-100.0,-82.8,-345.1,-54,7475371)
	spawnMobile("lok", "enraged_dune_kimogila",7200,-29.9,-53.5,-190.9,59,7475359)
	spawnMobile("lok", "ig_assassin_droid",360,-27.1,-38.2,-64.2,0,7475357)

	--Rebel House (-4743 3531) Leia Story part 3 needs to be populated

	--Imperial lookout (-2568 -862) Imperial Contact Story part 3 needs to be populated

	--Torches and arches 720 -3389
	spawnMobile("lok", "gurk",900,731.6,11.9,-3382,142,0)
	spawnMobile("lok", "gurk",900,708,12,-3397,131,0)
	spawnMobile("lok", "gurk",900,699,12,-3384,-97,0)
	spawnMobile("lok", "gurk",900,704.1,12.1,-3359,16,0)
	spawnMobile("lok", "reclusive_gurk_king",1200,720.3,11.9,-3396.6,130,0)

	--Gurk camp -3763 -3477
	spawnMobile("lok", "gurk",900,-3754.7,63.2,-3477.6,150,0)
	spawnMobile("lok", "gurk",900,-3763.7,62,-3485.9,170,0)
	spawnMobile("lok", "reclusive_gurk_king",1200,-3763.4,62.5,-3477.2,160,0)

	--Tribal Stone Claws Site (-6000, 6400)
	spawnMobile("lok", "kimogila_dwarf", 4200, -6014.5, 56.2, 6429.9, 131, 0)

	--Rare Lokkian Fountain (6400, 5000)
	spawnMobile("lok", "aged_kimogila", 4200, 6426.0, 100.1, 5142.2, -151, 0)
	spawnMobile("lok", "kimogila_dwarf", 4200, 6443.7, 92.1, 5106.4, -108, 0)

	--Abandoned Settlers Camp (-130, -350)
	spawnMobile("lok", "aged_kimogila", 4200, -252.0, 11.1, -455.0, -6, 0)

	--Abandoned Settlers Camp Ruins (5000, -4100)
	spawnMobile("lok", "aged_kimogila", 4200, 5086.8, 12.1, -4114.6, 139, 0)
	spawnMobile("lok", "kimogila_dwarf", 4200, 5097.4, 11.9, -4113.3, 124, 0)

	--Mysterious Shrine (-2100, 5900)
	spawnMobile("lok", "langlatch_giant", 900, getRandomNumber(5) + -2110.8, 87.8, getRandomNumber(5) + 5935.2, getRandomNumber(360), 0)
	spawnMobile("lok", "langlatch_giant", 900, getRandomNumber(5) + -2110.8, 87.8, getRandomNumber(5) + 5935.2, getRandomNumber(360), 0)

	--Broken Wall Hill (-4400, -5800)
	spawnMobile("lok", "langlatch_giant", 900, getRandomNumber(10) + -4448.2, 11.9, getRandomNumber(10) + -5769.9, getRandomNumber(360), 0)
	spawnMobile("lok", "langlatch_giant", 900, getRandomNumber(10) + -4448.2, 11.9, getRandomNumber(10) + -5769.9, getRandomNumber(360), 0)
	spawnMobile("lok", "langlatch_giant", 900, getRandomNumber(10) + -4448.2, 11.9, getRandomNumber(10) + -5769.9, getRandomNumber(360), 0)

end
