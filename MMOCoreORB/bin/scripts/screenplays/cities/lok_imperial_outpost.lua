LokImperialOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "LokImperialOutpostScreenPlay"
}

registerScreenPlay("LokImperialOutpostScreenPlay", true)

function LokImperialOutpostScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
	end
end

function LokImperialOutpostScreenPlay:spawnMobiles()
	spawnMobile("lok", "imperial_recruiter",60, -1844, 0, -3069, 123, 0)

	spawnMobile("lok", "at_st", 400, -1795, 12, -3104, 40, 0)
	spawnMobile("lok", "at_at", 800, -1788, 12, -3025, 120, 0)

	spawnMobile("lok", "stormtrooper", 60, -1840.8, 12, -3080, 90, 0)
	spawnMobile("lok", "stormtrooper", 60, -1840.8, 12, -3089.5, 90, 0)
	spawnMobile("lok", "stormtrooper", 60, -1824.2, 12, -3098.7, 0, 0)
	spawnMobile("lok", "stormtrooper", 60, -1814.8, 12, -3084.3, 90, 0)
	spawnMobile("lok", "stormtrooper", 60, -1809.0, 12, -3098.2, 0, 0)
	spawnMobile("lok", "stormtrooper", 60, -1818.2, 12, -3070.2, 270, 0)
	spawnMobile("lok", "stormtrooper", 60, -1841.8, 12, -3036.2, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1822.4, 12, -3038.9, 220, 0)
	spawnMobile("lok", "stormtrooper", 60, -1842.0, 12, -3060.0, 60, 0)
	spawnMobile("lok", "stormtrooper", 60, -1872.7, 12, -3037.2, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1891.5, 12, -3045.7, 270, 0)
	spawnMobile("lok", "stormtrooper", 60, -1827.8, 12, -3013.5, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1824.0, 12, -3013.5, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1948.0, 12, -2976.5, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1931.0, 12, -2976.0, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -1946.0, 12, -2968.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 60, -1933.0, 12, -2968.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 60, -1928.5, 12, -2987.2, 270, 0)
	spawnMobile("lok", "stormtrooper", 60, -2027.0, 12, -3052.0, 180, 0)
	spawnMobile("lok", "stormtrooper", 60, -2034.0, 12, -3069.0, 270, 0)
	spawnMobile("lok", "stormtrooper", 60, -2034.0, 12, -3059.0, 270, 0)

	spawnMobile("lok", "imperial_private", 60, 2, 1, 15, 0, 8615419)
	spawnMobile("lok", "imperial_private", 60, -2, 1, 15, 0, 8615419)
	spawnMobile("lok", "imperial_officer", 60, 2, 1, 4, 0, 8615420)
	spawnMobile("lok", "imperial_officer", 60, -2, 1, 4, 0, 8615420)
	spawnMobile("lok", "imperial_second_lieutenant", 60, 7, 1, -9, 0, 8615420)
	spawnMobile("lok", "imperial_first_lieutenant", 60, 17, 1, 10, 0, 8615420)
	spawnMobile("lok", "imperial_lieutenant_general", 60, -18, 1, 21, 0, 8615422)
	spawnMobile("lok", "imperial_general", 60, 16, 1, -22, 350, 8615424)
	spawnMobile("lok", "imperial_major", 60, 0, 1, -22, 0, 8615425)
	spawnMobile("lok", "imperial_warrant_officer_i", 60, -11, 1, -21, 280, 8615426)
	spawnMobile("lok", "imperial_staff_sergeant", 60, -18, 1, -21, 40, 8615426)
	spawnMobile("lok", "imperial_warrant_officer_ii", 60, -19, 1, -6, 60, 8615427)
	spawnMobile("lok", "imperial_warrant_officer_i", 60, -4, 7, -11, 40, 8615428)
	spawnMobile("lok", "imperial_sergeant_major", 60, 7, 7, -5, 300, 8615428)
	spawnMobile("lok", "imperial_sharpshooter", 60, -10, 1, 10, 120, 8615429)



end
