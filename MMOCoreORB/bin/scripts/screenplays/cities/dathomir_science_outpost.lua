DathomirScienceOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "DathomirScienceOutpostScreenPlay"
}

registerScreenPlay("DathomirScienceOutpostScreenPlay", true)

function DathomirScienceOutpostScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
	end
end

function DathomirScienceOutpostScreenPlay:spawnMobiles()

	--In a building
	spawnMobile("dathomir", "criminal", 300, -3.46893, 0.624996, -1.80359, 9.95605, 2835552)

	--Outside
	spawnMobile("dathomir", "businessman", 60, -70.8878, 18, -1646.08, 315.408, 0)
	spawnMobile("dathomir", "businessman", 60, -64.4958, 18, -1581.42, 63.9635, 0)
	spawnMobile("dathomir", "businessman", 60, -79.6404, 18, -1585.09, 131.623, 0)
	spawnMobile("dathomir", "cll8_binary_load_lifter", 60, -107.307, 18, -1603.07, 275.094, 0)
	spawnMobile("dathomir", "commoner", 60, -60.7253, 18, -1596.21, 88.2297, 0)
	spawnMobile("dathomir", "commoner", 60, -37.0445, 18, -1587.75, 47.6817, 0)
	spawnMobile("dathomir", "commoner", 60, -78.5124, 18, -1618.16, 179.85, 0)
	spawnMobile("dathomir", "commoner", 60, -98.9262, 18, -1590.29, 239.412, 0)
	spawnMobile("dathomir", "mercenary", 60, -88.9323, 18, -1606.84, 350.084, 0)
	spawnMobile("dathomir", "mercenary", 60, -100.976, 18, -1573.64, 39.7721, 0)
	spawnMobile("dathomir", "mercenary", 60, -86.3374, 18, -1555.75, 219.418, 0)
	spawnMobile("dathomir", "mercenary", 60, -93.2763, 18, -1569.32, 343.205, 0)
	spawnMobile("dathomir", "mercenary", 60, -43.9919, 18, -1585.86, 220.77, 0)
	spawnMobile("dathomir", "scientist", 60, -136.034, 18, -1592.07, 62.5196, 0)
	spawnMobile("dathomir", "informant_npc_lvl_3", 0,-68,18,-1565,270,0)

		--Left these in dathomir.lua 
	--{"arnecio_ulvaw_op",60,4.06465,0.624999,2.34456,30.9406,2835570, "neutral", ""},
	--{"r3",60,-78.3142,18,-1629.93,144.919,0, "calm", "R3-O0"},
	--{"r4",60,-134.195,18,-1599.14,45.5678,0, "calm", "R4-J5"},
	--{"shibb_nisshil",60,-71.1537,18,-1639.84,66.4233,0, "", "Shibb Nisshil"},
	--{"shaki_hamachil",60,-101.049,18,-1542.62,293.515,0, "calm", "Shaki Hamachil"},

end
