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

	---Left these in dantooine.lua because of the custom name etc
	--{"r2",60,1583.12,4,-6407.59,69.2539,0, "calm", "R2-Y8"},
	--{"r3",60,1592.98,4,-6400.58,80.56,0, "calm", "R3-M0"}
	--{"ytzosh",60,1636.98,4,-6402.56,321.838,0, "calm", "Ytzosh"}
	--{"yras_shen_jen",60,1572.26,4,-6417.06,75.0582,0, "neutral", ""},
	--{"ussox",60,1635.07,4,-6402.37,321.844,0, "calm", "Ussox"},
	--{"daiv_dekven",60,1603.42,4,-6434.54,102.877,0, "calm", "Daiv Dekven"},
	--{"quich_marae",60,1579.04,4,-6374.52,48.4898,0, "calm", "Quich Marae",JUNKJEDI,JUNKCONVQUICHDANTOOINE},

end
