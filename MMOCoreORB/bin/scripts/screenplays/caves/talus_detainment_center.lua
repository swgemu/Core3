TalusDetainmentCenterScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("TalusDetainmentCenterScreenPlay", true)

function TalusDetainmentCenterScreenPlay:start()
	if (isZoneEnabled("talus")) then
		self:spawnMobiles()
	end
	
end

function TalusDetainmentCenterScreenPlay:spawnMobiles()
	spawnMobile("talus", "imperial_staff_corporal", 300, 3.5, -9.0, 32.6, 179, 9686212)
   	spawnMobile("talus", "command_security_guard", 300, 4.4, -9.0, 35.5, 179, 9686212)
	spawnMobile("talus", "command_security_guard", 300, 2.5, -9.0, 35.5, 179, 9686212)
	spawnMobile("talus", "imperial_warrant_officer_i", 300, -48.1, -9.0, -6.6, 90, 9686214)
	spawnMobile("talus", "imperial_private", 300, -58.4, -9.0, 3.2, 0, 9686214)
	spawnMobile("talus", "imperial_noncom", 300, -72.9, -9.0, 21.2,  165, 9686214)
	spawnMobile("talus", "imperial_staff_corporal", 300, -54.5, -9.0, 67.1, 179, 9686214)
	spawnMobile("talus", "imperial_noncom", 300, -52.3, -9.0, 63.2, 90, 9686214)
	spawnMobile("talus", "imperial_noncom", 300, -53.2, -9.0, 59.0, 90, 9686214)
	spawnMobile("talus", "imperial_noncom", 300, -57.0, -9.0, 60.9, -120, 9686214)
	spawnMobile("talus", "command_security_guard", 300, -24.9, -9.0, 28.5, 90, 9686213)
	spawnMobile("talus", "command_security_guard", 300, -24.8, -9.0, 26.0, 90, 9686213)	
	spawnMobile("talus", "command_security_guard", 300, 12.1, -17.0, 65.0, 179, 9686215)
	spawnMobile("talus", "command_security_guard", 300, 12.1, -17.0, 62.0, -1, 9686215)
	spawnMobile("talus", "stormtrooper", 300, 30.4, -17.0, 60.7, 1, 9686215)
	spawnMobile("talus", "stormtrooper", 300, 30.4, -17.0, 65.9, 179, 9686215)
	spawnMobile("talus", "imperial_captain", 300, 34.5, -17.0, 63.5, -90, 9686215)
	spawnMobile("talus", "dark_trooper", 300, -1.2, -23.0, 225.4, 179, 9686222)
	spawnMobile("talus", "dark_trooper", 300, -3.8, -23.0, 225.4, 179, 9686222)
	spawnMobile("talus", "imperial_first_lieutenant", 300, -19.8, -23.0, 234.4, 179, 9686222)
	spawnMobile("talus", "stormtrooper", 300, 1.0, -23.0, 192.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -2.0, -23.0, 192.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -5.0, -23.0, 192.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -8.0, -23.0, 192.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, 1.0, -23.0, 196.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -2.0, -23.0, 196.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -5.0, -23.0, 196.3, 90, 9686217)
	spawnMobile("talus", "stormtrooper", 300, -8.0, -23.0, 196.3, 90, 9686217)
	spawnMobile("talus", "imperial_first_lieutenant", 300, 7.1, -23.0, 198.5, -135, 9686217)

end
