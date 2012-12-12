TortonCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("TortonCaveScreenPlay", true)

function TortonCaveScreenPlay:start()
	self:spawnMobiles()
end

function TortonCaveScreenPlay:spawnMobiles()
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -1805.5, 92.9, -4543.3, 72, 0)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -1810.3, 91.9, -4529.2, 51, 0)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -1.6, -5.3, -7.5, 1, 5095969)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -9.5, -22.7, -26.3, 87, 5095970)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -9.8, -32.5, -73.0, 1, 5095971)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  9.9, -32.6, -74.5, -33, 5095971)
	spawnMobile("rori", "adolescent_pygmy_torton", 360,  44.4, -38.8, -52.7, -112, 5095972)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -3.6, -37.1, -139.3, 33, 5095973)
	spawnMobile("rori", "adolescent_pygmy_torton", 360,  18.1, -39.2, -131.9, 25, 5095973)
	spawnMobile("rori", "adolescent_pygmy_torton", 360,  62.8, -38.5, -123.9, -94, 5095973)
	spawnMobile("rori", "adult_pygmy_torton", 360,  42.8, -48.7, -180.7, -10, 5095973)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -11.8, -57.8, -216.3, -2, 5095975)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -5.2, -56.9, -240.9, -1, 5095975)
	spawnMobile("rori", "adult_pygmy_torton", 360,  -58.0, -63.0, -181.8, 83, 5095976)
	spawnMobile("rori", "adolescent_pygmy_torton", 360,  -93.5, -65.6, -170.7, 90, 5095976)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -105.8, -62.2, -123.6, 166, 5095976)
	spawnMobile("rori", "adult_pygmy_torton", 360,  -97.3, -61.5, -94.2, -177, 5095976)
	spawnMobile("rori", "adult_pygmy_torton", 360,  -61.3, -60.7, -112.0, -46, 5095977)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -25.2, -61.4, -95.4, -96, 5095977)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -21.3, -71.2, -140.4, -30, 5095978)
	spawnMobile("rori", "pygmy_torton_protector", 360,  -82.2, -92.4, -142.6, 91, 5095976)
	spawnMobile("rori", "torton_pygmy_matriarch", 360,  -90.7, -93.1, -106.5, 166, 5095979)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -84.9, -92.8, -106.2, 173, 5095979)
	spawnMobile("rori", "juvenile_pygmy_torton", 360,  -98.9, -91.7, -108.5, 151, 5095979)
end