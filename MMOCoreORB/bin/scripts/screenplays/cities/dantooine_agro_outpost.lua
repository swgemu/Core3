DantooineAgroOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "DantooineAgroOutpostScreenPlay"
}

registerScreenPlay("DantooineAgroOutpostScreenPlay", true)

function DantooineAgroOutpostScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
	end
end

function DantooineAgroOutpostScreenPlay:spawnMobiles()

	--In the Cantina
	spawnMobile("dantooine", "businessman", 60, 8.90672, 0.625, -2.94252, 244, 6205499)
	spawnMobile("dantooine", "businessman", 60, -7.77368, 0.624999, -5.2158, 188, 6205498)

	--Outside
	spawnMobile("dantooine", "businessman", 60, 1580, 4,-6439, 200, 0)
	spawnMobile("dantooine", "businessman", 60, 1571, 4, -6397, 303, 0)
	spawnMobile("dantooine", "businessman", 60, 1597, 4, -6416, 208, 0)
	spawnMobile("dantooine", "cll8_binary_load_lifter", 60, 1573, 4, -6412, 313, 0)
	spawnMobile("dantooine", "commoner", 60, 1586, 4, -6398, 189, 0)
	spawnMobile("dantooine", "commoner", 60, 1575, 4, -6396, 324, 0)
	spawnMobile("dantooine", "commoner", 60, 1570, 4, -6370, 178, 0)
	spawnMobile("dantooine", "commoner", 60, 1545, 4, -6370, 287, 0)
	spawnMobile("dantooine", "commoner", 60, 1547, 4, -6398, 43, 0)
	spawnMobile("dantooine", "commoner", 60, 1558, 4, -6429, 106, 0)
	spawnMobile("dantooine", "commoner", 60, 1544, 4, -6415, 344, 0)
	spawnMobile("dantooine", "commoner", 60, 1600, 4, -6402, 245, 0)
	spawnMobile("dantooine", "commoner", 60, 1629, 4, -6370, 39, 0)
	spawnMobile("dantooine", "commoner", 60, 1605, 4, -6377, 55, 0)
	spawnMobile("dantooine", "commoner", 60, 1635, 4, -6397, 57, 0)
	spawnMobile("dantooine", "commoner", 60, 1614, 4, -6428, 192, 0)
	spawnMobile("dantooine", "criminal", 300, 1601, 4, -6367, 109, 0)
	spawnMobile("dantooine", "daiv_dekven", 60, 1603, 4, -6434, 102, 0)
	spawnMobile("dantooine", "noble", 60, 1558, 4, -6367, 143, 0)
	spawnMobile("dantooine", "pirate", 60, 1539, 4, -6407, 34, 0)
	spawnMobile("dantooine", "pirate", 60, 1556, 4, -6411, 188, 0)
	spawnMobile("dantooine", "r2", 60, 1583, 4, -6407, 69, 0)
	spawnMobile("dantooine", "r3", 60, 1592, 4, -6400, 80, 0)
	spawnMobile("dantooine", "scientist", 60, 1583, 4, -6439, 7, 0)
	spawnMobile("dantooine", "ussox", 60, 1635, 4, -6402, 321, 0)
	spawnMobile("dantooine", "yras_shen_jen", 60, 1572, 4, -6417, 75, 0)
	spawnMobile("dantooine", "ytzosh", 60, 1636, 4, -6402, 321, 0)

end
