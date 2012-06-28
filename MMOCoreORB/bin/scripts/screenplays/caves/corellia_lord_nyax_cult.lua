LordNyaxCultScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("LordNyaxCultScreenPlay", true)

function LordNyaxCultScreenPlay:start()
	self:spawnMobiles()
end

function LordNyaxCultScreenPlay:spawnMobiles()
	--TODO: Implement spawners in radius.
	--spawnCreatures("fanatic_of_lord_nyax", 300, 0, 1350, -322, 50, 4)
	--spawnCreatures("visionary_of_lord_nyax", 300, 0, 1350, -322, 50,4)
	--spawnCreatures("servant_of_lord_nyax", 300, 0, 1350, -322, 50, 4)
	--spawnCreatures("minion_of_lord_nyax", 300, 0, 1350, -322, 50, 4)
	--spawnCreatures("fiend_of_lord_nyax", 300, 0, 1350, -322, 50, 4)
	--spawnCreatures("disciple_of_lord_nyax", 300, 0, 1350, -322, 50, 4)
	--spawnCreatures("zealot_of_lord_nyax", 300, 0, 1350, -322, 50, 4)

	spawnMobile("corellia", "fiend_of_lord_nyax", 300, 0.200391, 0.25, 5.98459, 0, 6035995)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -0.494639, 0.25, 6.25404, 0, 6035995)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, 3.6188, 0.25, -4.09898, 0, 6035996)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, 2.61819, 0.25, -3.44736, 0, 6035996)
	spawnMobile("corellia", "zealot_of_lord_nyax", 300, 4.81463, -6.75, 5.40781, 0, 6035998)
	spawnMobile("corellia", "visionary_of_lord_nyax", 300, 3.44729, -6.75, 4.34948, 0, 6035998)
	spawnMobile("corellia", "zealot_of_lord_nyax", 300, 2.80898, -6.75, -7.19805, 0, 6035999)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, -5.37152, -13.7499, 0.459682, 0, 6036001)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, -3.0171, -13.7499, -0.894038, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -1.05993, -13.7499, -2.09377, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -5.53416, -13.75, -8.46985, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, 16.6905, -13.7584, 4.76515, 0, 6036003)
	spawnMobile("corellia", "visionary_of_lord_nyax", 300, 14.4694, -13.7584, 2.8743, 0, 6036003)
	spawnMobile("corellia", "lord_nyax", 300, 19.4, -11.4, -21.1, 0, 6036004)
end