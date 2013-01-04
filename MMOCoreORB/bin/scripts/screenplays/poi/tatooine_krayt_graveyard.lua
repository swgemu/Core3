KraytGraveyardScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("KraytGraveyardScreenPlay", true)

function KraytGraveyardScreenPlay:start()
	self:spawnMobiles()
end

function KraytGraveyardScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "canyon_krayt_dragon", 1800, 7227.5, 33.2, 4495.8, -116, 0)
	spawnMobile("tatooine", "canyon_krayt_dragon", 1800, 7178, 24.5, 4429.9, -100, 0)
	spawnMobile("tatooine", "canyon_krayt_dragon", 1800, 7035.7, 22.8, 4337.2, -55, 0)
	spawnMobile("tatooine", "canyon_krayt_dragon", 1800, 6872.9, 41.7, 4246.9, -99, 0)

	spawnMobile("tatooine", "giant_canyon_krayt_dragon", 1800, 7515.6, 8.7, 4556.5, -35, 0)
	spawnMobile("tatooine", "giant_canyon_krayt_dragon", 1800, 7417.3, 7.7, 4597.9, -128, 0)
	spawnMobile("tatooine", "giant_canyon_krayt_dragon", 1800, 7345.2, 15.2, 4493.8, -116,0)
	spawnMobile("tatooine", "giant_canyon_krayt_dragon", 1800, 7140.4, 57, 4322.5, -86, 0)

	spawnMobile("tatooine", "krayt_dragon_ancient", 1800, 6836.7, 25.4, 4321.8, -150, 0)
	spawnMobile("tatooine", "krayt_dragon_ancient", 1800, 7491.3, 8.4, 4484.8, -150, 0)

	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 7483.1, 4.2, 4648.2, -158, 0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 7417.7, 22.2, 4429.1, 4, 0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 7269.8, 62.4, 4352.7, -77,0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 7077.4, 20.0, 4447.3, -123, 0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 6960.0, 14.2, 4366.2, -170, 0)
	spawnMobile("tatooine", "juvenile_canyon_krayt_dragon", 1500, 6763.8, 21.4, 4282.3, -91, 0)
end