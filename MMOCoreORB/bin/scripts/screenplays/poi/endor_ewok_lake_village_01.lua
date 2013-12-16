EndorEwokLakeVillage01ScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorEwokLakeVillage01ScreenPlay", true)

function EndorEwokLakeVillage01ScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorEwokLakeVillage01ScreenPlay:spawnMobiles()

	spawnMobile("endor", "skilled_gondula_worker",300, 1514.5, 5.1, -3137.6, -46, 0)
	spawnMobile("endor", "skilled_gondula_worker",300, 1509, 5.1, -3143, -46, 0)
	spawnMobile("endor", "skilled_gondula_worker",300, 1549.6, 5.1, -3174.8, 141, 0)	
	spawnMobile("endor", "skilled_gondula_worker",300, 1544.2, 5.1, -3180, 141, 0)

	spawnMobile("endor", "gondula_ritualist",300, 1418.2, 1, -3164, -6, 0)
	spawnMobile("endor", "gondula_ritualist",300, 1425.9, 1.1, -3164.3, -6, 0)

	spawnMobile("endor", "gondula_matriarch",300, 1422, 1, -3221.4, -5, 0)

	spawnMobile("endor", "gondula_cub",300, 1414, 2, -3214.1, -45, 0)
	spawnMobile("endor", "gondula_cub",300, 1413.9, 2, -3210.1, -123, 0)
	spawnMobile("endor", "gondula_cub",300, 1409.3, 2, -3209.3, 132, 0)
	spawnMobile("endor", "gondula_cub",300, 1409.2, 2, -3213.3, 51, 0)

	spawnMobile("endor", "gondula_cub",300, 1430.1, 2, -3213.7, 48, 0)
	spawnMobile("endor", "gondula_cub",300, 1434, 2, -3214, -30, 0)
	spawnMobile("endor", "gondula_cub",300, 1434.8, 2, -3209.7, -130, 0)
	spawnMobile("endor", "gondula_cub",300, 1431.6, 2, -3208.7, 157, 0)

	spawnMobile("endor", "gondula_cub",300, 1430, 2, -3229.9, 139, 0)
	spawnMobile("endor", "gondula_cub",300, 1429.9, 2, -3233.8, 65, 0)
	spawnMobile("endor", "gondula_cub",300, 1434.3, 2, -3234.5, -54, 0)
	spawnMobile("endor", "gondula_cub",300, 1434.5, 2, -3230.5, -136, 0)

	spawnMobile("endor", "gondula_cub",300, 1414.2, 2, -3229.8, -135, 0)
	spawnMobile("endor", "gondula_cub",300, 1409.2, 2, -3230.1, 145, 0)
	spawnMobile("endor", "gondula_cub",300, 1409.7, 2, -3234.1, 47, 0)
	spawnMobile("endor", "gondula_cub",300, 1413.5, 2, -3234.4, -41, 0)

	spawnMobile("endor", "wise_gondula_ritualist",300, 1466.2, 1, -3318.2, -88, 0)
	spawnMobile("endor", "gifted_gondula_shaman",300, 1472.9, 1.9, -3308.3, 39, 0)
	spawnMobile("endor", "gifted_gondula_shaman",300, 1472.5, 1.9, -3327.6, 144, 0)

	spawnMobile("endor", "gondula_elder",300, 1404.7, 1.0, -3319.6, 80, 0)
	spawnMobile("endor", "gondula_elder",300, 1404.8, 1.0, -3318, 86, 0)
	spawnMobile("endor", "gondula_elder",300, 1405, 1.0, -3315.8, 99, 0)
	spawnMobile("endor", "gondula_chief",300, 1408.5, 1.0, -3316.5, -108, 0)
	spawnMobile("endor", "hardened_gondula_warrior",300, 1408.3, 1.0, -3318.8, -33, 0)
	spawnMobile("endor", "hardened_gondula_warrior",300, 1432.4, 1.4, -3319.9, 75, 0)
	spawnMobile("endor", "hardened_gondula_warrior",300, 1432.3, 1.4, -3315.9, 83, 0)

	spawnMobile("endor", "gondula_loremaster",300, 1429.7, 1.9, -3352.5, -135, 0)
	spawnMobile("endor", "gondula_veteran",300, 1436, 1.4, -3345.7, 40, 0)
	spawnMobile("endor", "gondula_tribesman",300, 1454.3, 1, -3333, 42, 0)
	spawnMobile("endor", "gondula_tribesman",300, 1449.4, 1, -3328.1, 44, 0)

	spawnMobile("endor", "weathered_gondula_shaman",300, 1464.1, 2, -3361.8, -12, 0)
	spawnMobile("endor", "gondula_veteran",300, 1466.4, 2, -3358.4, -143, 0)
	spawnMobile("endor", "gondula_veteran",300, 1462.4, 2, -3356.6, 153, 0)
	spawnMobile("endor", "gondula_veteran",300, 1461.3, 2, -3358.3, 142, 0)

	spawnMobile("endor", "gondula_worker",300, 1486.1, 1, -3266.6, 87, 0)
	spawnMobile("endor", "gondula_worker",300, 1486.1, 1, -3273.3, 81, 0)

	spawnMobile("endor", "wise_gondula_ritualist",300, 1463.7, 1.9, -3259.8, 50, 0)
	spawnMobile("endor", "wise_gondula_ritualist",300, 1463.3, 1.9, -3279.6, 131, 0)

	spawnMobile("endor", "gondula_matriarch",300, 1413.7, 1, -3278.9, 62, 0)
	spawnMobile("endor", "gondula_matriarch",300, 1412.9, 1, -3261.8, 97, 0)
	spawnMobile("endor", "gifted_gondula_shaman",300, 1432.4, 1.8, -3280.3, -52, 0)
end
