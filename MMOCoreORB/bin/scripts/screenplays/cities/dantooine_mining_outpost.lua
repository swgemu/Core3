DantooineMiningOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "DantooineMiningOutpostScreenPlay"
}

registerScreenPlay("DantooineMiningOutpostScreenPlay", true)

function DantooineMiningOutpostScreenPlay:start()
	if (isZoneEnabled("dantooine")) then
		self:spawnMobiles()
	end
end

function DantooineMiningOutpostScreenPlay:spawnMobiles()

	--In The Cantina
	spawnMobile("dantooine", "adwan_turoldine", 60, -9.3, 0.6, 3.1, 83, 6205565)
	spawnMobile("dantooine", "businessman", 60, -8, 0.6, -6, 83, 6205566)

	--Outside
	spawnMobile("dantooine", "businessman", 60, -603, 3, 2485, 345, 0)
	spawnMobile("dantooine", "businessman", 60, -647, 3, 2456, 181, 0)
	spawnMobile("dantooine", "businessman", 60, -636, 3, 2507, 155, 0)
	spawnMobile("dantooine", "businessman", 60, -575, 3, 2503, 36, 0)
	spawnMobile("dantooine", "businessman", 60, -627, 3, 2531, 81, 0)
	spawnMobile("dantooine", "commando", 300, -616, 3, 2509, 314, 0)
	spawnMobile("dantooine", "commando", 300, -562, 3, 2512, 108, 0)
	spawnMobile("dantooine", "commoner", 60, -643, 3, 2449, 341,0)
	spawnMobile("dantooine", "commoner", 60, -600, 3, 2548, 16, 0)
	spawnMobile("dantooine", "commoner", 60, -580, 3, 2530, 29, 0)
	spawnMobile("dantooine", "commoner", 60, -611, 3, 2533, 209, 0)
	spawnMobile("dantooine", "commoner", 60, -628, 3, 2509, 149, 0)
	spawnMobile("dantooine", "commoner", 60, -615, 3, 2518, 76, 0)
	spawnMobile("dantooine", "commoner", 60, -621, 3, 2500, 334, 0)
	spawnMobile("dantooine", "commoner", 60, -641, 3, 2472, 264, 0)
	spawnMobile("dantooine", "commoner", 60, -662, 3, 2482, 92, 0)
	spawnMobile("dantooine", "commoner", 60, -655, 3, 2461, 14, 0)
	spawnMobile("dantooine", "commoner", 60, -631, 3, 2463, 302, 0)
	spawnMobile("dantooine", "commoner", 60, -647, 3, 2449, 73, 0)
	spawnMobile("dantooine", "commoner", 60, -611, 3, 2488, 311, 0)
	spawnMobile("dantooine", "commoner", 60, -602, 3, 2506, 285, 0)
	spawnMobile("dantooine", "commoner", 60, -568, 3, 2511, 51, 0)
	spawnMobile("dantooine", "criminal", 300, -620, 3, 2450, 281, 0)
	spawnMobile("dantooine", "fern_yarrow", 60, -625, 3, 2481, 119, 0)
	spawnMobile("dantooine", "kess_yarrow", 60, -623, 3, 2481, 149, 0)
	spawnMobile("dantooine", "mercenary", 300, -665, 3, 2462, 261, 0)
	spawnMobile("dantooine", "mercenary", 300, -594, 3, 2500, 47, 0)
	spawnMobile("dantooine", "mercenary", 300, -658, 3, 2480, 334, 0)
	spawnMobile("dantooine", "mercenary", 300, -665, 3, 2465, 120, 0)
	spawnMobile("dantooine", "r2", 60, -635, 3, 2503, 353, 0)
	spawnMobile("dantooine", "r4", 60, -643, 3, 2506, 129, 0)
	spawnMobile("dantooine", "r4", 60, -666, 3, 2494, 121, 0)
	spawnMobile("dantooine", "imperial_colonel", 450, -588, 3, 2499, 264, 0)
	spawnMobile("dantooine", "rane_yarrow", 60, -625, 3, 2479, 86, 0)
	spawnMobile("dantooine", "stranded_imperial_soldier", 60, -604, 3, 2538, 200, 0)

end
