AfarathuCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("AfarathuCaveScreenPlay", true)

function AfarathuCaveScreenPlay:start()
	self:spawnMobiles()
end

function AfarathuCaveScreenPlay:spawnMobiles()
	-- outside cave
	--spawnCreature("afarathu_ruffian", 300, -2489.6, 2920.0)
	--spawnCreature("afarathu_ruffian", 300, -2494.0, 2913.6)

	-- inside cave
	spawnMobile("corellia", "afarathu_ruffian", 300, -0.6, -13.7, -8.3, 0, 6035620)
	spawnMobile("corellia", "afarathu_ruffian", 300, 11.3, -14.2, -5.5, 0, 6035620)
	spawnMobile("corellia", "afarathu_ruffian", 300, 9.7, -23.9, -28.3, 0, 6035621)
	spawnMobile("corellia", "afarathu_ruffian", 300, -11.3, -30.7, -27.1, 0, 6035621)

	spawnMobile("corellia", "afarathu_cult_follower", 300, -1.8, -40.7, -74.1, 0, 6035622)
	spawnMobile("corellia", "afarathu_cult_follower", 300, 2.6, -40.4, -62.4, 0, 6035622)
	spawnMobile("corellia", "afarathu_cult_follower", 300, 3.4, -41.0, -72.6, 0, 6035622)

	spawnMobile("corellia", "afarathu_ruffian", 300, 49.3, -46.8, -53.7, 0, 6035623)
	spawnMobile("corellia", "afarathu_ruffian", 300, 43.8, -46.1, -95.1, 0, 6035623)
	spawnMobile("corellia", "afarathu_ruffian", 300, 23.6, -45.7, -102.8, 0, 6035623)

	spawnMobile("corellia", "afarathu_cult_savage", 300, -1.7, -45.8, -147.8, 0, 6035624)
	spawnMobile("corellia", "afarathu_cult_savage", 300, -11.0, -44.4, -136.4, 0, 6035624)
	spawnMobile("corellia", "afarathu_cult_savage", 300, -4.2, -64.0, -234.2, 0, 6035626)
	spawnMobile("corellia", "afarathu_cult_savage", 300, -21.7, -65.4, -244.6, 0, 6035626)

	spawnMobile("corellia", "afarathu_cult_follower", 300, -95.3, -73.7, -170.0, 0, 6035627)
	spawnMobile("corellia", "afarathu_brute", 300, -83.5, -71.6, -169.2, 0, 6035627)
	spawnMobile("corellia", "afarathu_brute", 300, -100.5, -72.9, -159.1, 0, 6035627)
	spawnMobile("corellia", "afarathu_brute", 300, -111.7, -69.4, -170.6, 0, 6035627)

	spawnMobile("corellia", "afarathu_brute", 300, -85.4, -101.5, -111.2, 0, 6035630)
	spawnMobile("corellia", "afarathu_brute", 300, -92.8, -101.1, -111.9, 0, 6035630)
	spawnMobile("corellia", "afarathu_cult_leader", 300, -90.7, -101.1, -104.8, 0, 6035630)
end