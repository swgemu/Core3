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
	local pNpc = spawnMobile("dantooine", "chiss_male",60,3.0,0.6,0.8,-42,6205496)
	self:setMoodString(pNpc, "npc_sitting_chair")
	pNpc = spawnMobile("dantooine", "patron_devaronian",60,-7.5,0.6,5.7,-95,6205497)
	self:setMoodString(pNpc, "npc_standing_drinking")
	pNpc = spawnMobile("dantooine", "bartender",60,-9.1,0.6,5.3,85,6205497)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("dantooine", "businessman", 60, 8.90672, 0.625, -2.94252, 244, 6205499)
	pNpc = spawnMobile("dantooine", "entertainer",60,-7.77368,0.624999,-5.2158,188,6205498)
	self:setMoodString(pNpc, "happy")

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
	spawnMobile("dantooine", "commoner", 60, 1600, 4, -6402, 245, 0)
	spawnMobile("dantooine", "commoner", 60, 1629, 4, -6370, 39, 0)
	spawnMobile("dantooine", "commoner", 60, 1605, 4, -6377, 55, 0)
	spawnMobile("dantooine", "commoner", 60, 1635, 4, -6397, 57, 0)
	spawnMobile("dantooine", "commoner", 60, 1614, 4, -6428, 192, 0)
	spawnMobile("dantooine", "criminal", 300, 1601, 4, -6367, 109, 0)
	spawnMobile("dantooine", "noble", 60, 1558, 4, -6367, 143, 0)
	spawnMobile("dantooine", "pirate", 300, 1539, 4, -6407, 34, 0)
	spawnMobile("dantooine", "pirate", 300, 1556, 4, -6411, 188, 0)
	spawnMobile("dantooine", "scientist", 60, 1583, 4, -6439, 7, 0)
	spawnMobile("dantooine", "r2", 60, 1583.12, 4, -6407.59, 69, 0)
	spawnMobile("dantooine", "r3", 60, 1592.98, 4, -6400.58, 80, 0)
	spawnMobile("dantooine", "ytzosh", 60, 1636.98, 4, -6402.56, 322, 0)
	spawnMobile("dantooine", "ussox", 60, 1635.07, 4, -6402.37, 322, 0)
	pNpc = spawnMobile("dantooine", "yras_shen_jen",60,1572.26,4,-6417.06,75.0582,0)
	self:setMoodString(pNpc, "neutral")
	spawnMobile("dantooine", "junk_quich", 0, 1579.04, 4, -6374.52, 48, 0)
end
