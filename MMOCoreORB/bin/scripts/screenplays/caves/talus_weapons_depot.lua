TalusWeaponsDepotScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("TalusWeaponsDepotScreenPlay", true)

function TalusWeaponsDepotScreenPlay:start()
	self:spawnMobiles()
end

function TalusWeaponsDepotScreenPlay:spawnMobiles()
   
	spawnMobile("talus", "rebel_trooper", 300, 15.5, -12.0, 28.3, -92, 9686140)
	spawnMobile("talus", "rebel_major", 300, 55.0, -12.0, 55.9, -7, 9686143)
	spawnMobile("talus", "rebel_staff_sergeant", 300, 54.9, -12.0, 62.5, -179, 9686143)
	spawnMobile("talus", "rebel_trooper", 300, 39.2, -12.0, 60.6, -96, 9686143)
	spawnMobile("talus", "rebel_warrant_officer_i", 300, -12.2, -12.0, 94.6, 0, 9686150)
	spawnMobile("talus", "rebel_second_lieutenant", 300, -15.2, -12.0, 96.9, 90, 9686150)
	spawnMobile("talus", "rebel_trooper", 300, -4.0, -12.0, 101.3, -90, 9686150)
	spawnMobile("talus", "rebel_corporal", 300, -1.3, -12.0, 117.5, -50, 9686149)
	spawnMobile("talus", "rebel_corporal", 300, 0.3, -12.0, 115.5, -179, 9686149)
	spawnMobile("talus", "rebel_second_lieutenant", 300, 16.4, -12.0, 92.7, 152, 9686148)
	spawnMobile("talus", "rebel_trooper", 300, 97.4, -20.0, 115.9, 109, 9686160)
	spawnMobile("talus", "rebel_trooper", 300, 105.5, -20.0, 110.8, 109, 9686160)
	spawnMobile("talus", "rebel_trooper", 300, 96.7, -20.0, 105.5, -39, 9686160)
	spawnMobile("talus", "rebel_trooper", 300, 44.8, -20.0, 151.3, 136, 9686155)
	spawnMobile("talus", "rebel_trooper", 300, 49.8, -20.0, 150.0, 139, 9686155)
	spawnMobile("talus", "rebel_trooper", 300, 50.1, -20.0, 139.0, 134, 9686155)
	spawnMobile("talus", "rebel_trooper", 300, 52.6, -20.0, 139.1, -142, 9686155)
	spawnMobile("talus", "rebel_colonel", 300, 47.9, -20.0, 144.4, 2, 9686155)
	spawnMobile("talus", "rebel_medic", 300, 10.1, -12.0, 53.6, -29, 9686144)
	spawnMobile("talus", "rebel_corporal", 300, -2.4, -12.0, 62.0, -90, 9686144)
	spawnMobile("talus", "rebel_warrant_officer_i", 300, -3.5, -12.0, 73.6, 90, 9686144)

end
