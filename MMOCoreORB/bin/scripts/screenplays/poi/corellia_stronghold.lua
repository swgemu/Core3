StrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "StrongholdScreenPlay",


}

registerScreenPlay("StrongholdScreenPlay", true)

function StrongholdScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()

	end
end

function StrongholdScreenPlay:spawnMobiles()

	spawnMobile("corellia", "dark_trooper", 360, 4696.72, 25, -5797.99, 198.662, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4663.22, 25, -5781.71, 0.4, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4662.22, 25, -5769.71, 177.4, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4694.46, 25, -5803.03, 351.991, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4689.06, 25, -5796.24, 257.913, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4694.47, 25, -5806.45, 224.026, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4696.33, 25, -5804.40, 253.399, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4683.96, 25, -5743.68, 348.127, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4675.06, 25, -5746.75, 279.993, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4687.68, 25, -5754.00, 128.516, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4675.80, 25, -5752.56, 288.664, 0)
	spawnMobile("corellia", "dark_trooper", 360, 4679.01, 25, -5742.91, 9.66, 0)

	spawnMobile("corellia", "imperial_first_lieutenant", 300, 4638.27, 25, -5777.52, 110, 0)
	spawnMobile("corellia", "imperial_first_lieutenant", 300, 4637.55, 25, -5784.69, 185, 0)
	spawnMobile("corellia", "imperial_first_lieutenant", 300, 4635.64, 25, -5802.22, 92, 0)
	spawnMobile("corellia", "imperial_major", 300, 4629.71, 25, -5770.51, 238, 0)
	spawnMobile("corellia", "imperial_surface_marshall", 300, 4531.47, 30.7809, -5823.83, 217, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4497.73, 28.5915, -5829.8, 277.53, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4680.98, 25, -5821.58, 250, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4678.34, 25, -5829.9, 145, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4675.82, 25, -5825, 195, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4678.32, 25, -5824.85, 256, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4688.47, 25, -5766.6, 272, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4693.39, 25, -5762.66, 34, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4695.82, 25, -5761.96, 325, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4691.89, 25, -5774.64, 209, 0)
	spawnMobile("corellia", "stormtrooper", 300, 4691.92, 25, -5763.05, 240, 0)
	spawnMobile("corellia", "stormtrooper_squad_leader", 300, 4675.99, 25, -5809.56, 216, 0)
	spawnMobile("corellia", "stormtrooper_squad_leader", 300, 4678.77, 25, -5757.9, 226, 0)

	spawnMobile("corellia", "imperial_first_lieutenant", 400, -0.197, 0.125, -1.714, 0, 2715881)
	spawnMobile("corellia", "imperial_first_lieutenant", 400, 0.506, 0.125, -1.081, 0, 2716039)
	spawnMobile("corellia", "stormtrooper_medic", 400, 0.673, 0.125, -0.651, 0, 2716032)
	spawnMobile("corellia", "storm_commando", 400, -3.022, 0.125, -3.362, 0, 2716035)
	spawnMobile("corellia", "stormtrooper", 400, -0.207, 0.125, -1.570, 0, 2715952)
	spawnMobile("corellia", "stormtrooper", 400, 1.455, 0.125, -3.532, 0, 2715952)
	spawnMobile("corellia", "stormtrooper", 400, 0.879, 0.125, -2.578, 159, 2715909)
	spawnMobile("corellia", "stormtrooper", 400, -0.805, 0.125, -3.681, 226, 2715909)
	spawnMobile("corellia", "assault_trooper", 240, -0.197, 0.125, 1.538, 239, 2715902)
	spawnMobile("corellia", "imperial_surface_marshall", 400, 4.991, 0.125, -4.244, 64.122, 2715904)
	spawnMobile("corellia", "imperial_noncom", 400, 0, 0.125, -2.85, 0, 2715916)
	spawnMobile("corellia", "imperial_noncom", 400, 0, 0.125, -5.25, 0, 2715916)
	spawnMobile("corellia", "stormtrooper", 400, 0.3, 0.125, 5.747, 202, 2715914)
	spawnMobile("corellia", "imperial_trooper", 400, 0.49, 0.125, -2.033, 0, 2715959)
	spawnMobile("corellia", "imperial_trooper", 400, -1.11, 0.125, -2.76, 0, 2715959)

end
