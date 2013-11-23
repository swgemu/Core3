NabooGunganSacredPlaceScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "NabooGunganSacredPlaceScreenPlay",

}

registerScreenPlay("NabooGunganSacredPlaceScreenPlay", true)

function NabooGunganSacredPlaceScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()

	end
end

function NabooGunganSacredPlaceScreenPlay:spawnMobiles()

	spawnMobile("naboo", "gungan_leader", 360,-1972.6,20.4,-5416,-110,0)
	spawnMobile("naboo", "gungan_guard", 300,-1993.2,5.5,-5419.6,-111,0)
	spawnMobile("naboo", "gungan_guard", 300,-1991,4.8,-5425.4,-111,0)

	spawnMobile("naboo", "gungan_general", 360,-1953.7,8.3,-5453.6,157,0)
	spawnMobile("naboo", "gungan_guard", 300,-1955.9,5.1,-5458.9,157,0)
	spawnMobile("naboo", "gungan_guard", 300,-1948.4,5.5,-5456.4,157,0)

	spawnMobile("naboo", "gungan_boss", 360,-2031.2,10,-5419.6,174,0)
	spawnMobile("naboo", "gungan_guard", 300,-2023.9,8.5,-5425.5,-103,0)
	spawnMobile("naboo", "gungan_guard", 300,-2032.7,5.2,-5425.5,176,0)

	spawnMobile("naboo", "gungan_war_chief", 360,-1978.3,7.7,-5390.3,37,0)
	spawnMobile("naboo", "gungan_guard", 300,-1975.8,7.4,-5389.6,-126,0)
	spawnMobile("naboo", "gungan_guard", 300,-1977.6,7.8,-5387.7,-155,0)

	spawnMobile("naboo", "gungan_captain", 360,-1978.3,3.5,-5456.7,-112,0)
	spawnMobile("naboo", "gungan_guard", 300,-1980.1,3.4,-5459,48,0)
	spawnMobile("naboo", "gungan_guard", 300,-1981.5,3.4,-5456.1,88,0)

	spawnMobile("naboo", "gungan_guard", 300,-1946.7,5.5,-5425.8,65,0)
	spawnMobile("naboo", "gungan_guard", 300,-1944.6,5.1,-5430.6,65,0)
	spawnMobile("naboo", "gungan_guard", 300,-1975,4.1,-5441.4,-115,0)
	spawnMobile("naboo", "gungan_guard", 300,-1976.6,4.5,-5436.4,-115,0)

	spawnMobile("naboo", "gungan_guard", 300,-2059,5.5,-5425.1,84,0)
	spawnMobile("naboo", "gungan_guard", 300,-2061,5.2,-5417.3,63,0)
	spawnMobile("naboo", "gungan_guard", 300,-2071.2,6.3,-5424.2,-104,0)

	spawnMobile("naboo", "gungan_guard", 300,-1942.8,4.5,-5484.7,-37,0)
	spawnMobile("naboo", "gungan_guard", 300,-1934.3,4.7,-5479.8,-11,0)
	spawnMobile("naboo", "gungan_guard", 300,-1934.4,2.5,-5490.7,150,0)

	spawnMobile("naboo", "gungan_guard", 300,-1924.4,6.3,-5413.6,-108,0)
	spawnMobile("naboo", "gungan_guard", 300,-1925.1,5.8,-5404.2,-104,0)
	spawnMobile("naboo", "gungan_guard", 300,-1915.2,6.2,-5407.9,80,0)

	spawnMobile("naboo", "gungan_guard", 300,-1984.5,8.5,-5372.8,172,0)
	spawnMobile("naboo", "gungan_guard", 300,-1976.2,8.3,-5371.5,166,0)
	spawnMobile("naboo", "gungan_guard", 300,-1982.2,8.1,-5363.1,-14,0)

	spawnMobile("naboo", "gungan_guard", 300,-1949,5.1,-5377.1,-165,0)
	spawnMobile("naboo", "gungan_guard", 300,-1954.7,5.4,-5375.5,-164,0)

	spawnMobile("naboo", "gungan_guard", 300,-1919.6,7,-5447.6,-85,0)
	spawnMobile("naboo", "gungan_guard", 300,-1921.1,6.9,-5453,-80,0)

	spawnMobile("naboo", "gungan_guard", 300,-1982.5,2.6,-5483.4,11,0)
	spawnMobile("naboo", "gungan_guard", 300,-1988.2,2.6,-5482.6,6,0)

	spawnMobile("naboo", "gungan_guard", 300,-2027.8,4,-5464.5,20,0)
	spawnMobile("naboo", "gungan_guard", 300,-2032.8,4.2,-5461.6,20,0)

	spawnMobile("naboo", "gungan_guard", 300,-2048.9,5.2,-5387.6,135,0)
	spawnMobile("naboo", "gungan_guard", 300,-2044.7,5.6,-5383.9,135,0)

	spawnMobile("naboo", "gungan_guard", 300,-2016.7,6.6,-5373.7,165,0)
	spawnMobile("naboo", "gungan_guard", 300,-2011.1,7.4,-5373.1,165,0)
end
