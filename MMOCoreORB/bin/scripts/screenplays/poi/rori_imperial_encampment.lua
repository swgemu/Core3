RoriImperialEncampmentScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("RoriImperialEncampmentScreenPlay", true)

function RoriImperialEncampmentScreenPlay:start()
	if isZoneEnabled("rori") then
		self:spawnMobiles()

		if getRandomNumber(100) >= 50 then
			self:spawnRebels()
		else
			self:spawnImperials()
		end
	end
end

function RoriImperialEncampmentScreenPlay:spawnImperials()

	--inside the walls (not in buildings)

	spawnMobile("rori", "at_st", 720, -5597.3, 75.9, -5660.5, 0, 0)
	spawnMobile("rori", "at_st", 720, -5531.5, 75.9, -5660.5, 180, 0)

	spawnMobile("rori", "stormtrooper", 300, -5506.5, 75.9, -5661.1, 90, 0)
	spawnMobile("rori", "stormtrooper", 300, -5506.5, 75.9, -5666.9, 90, 0)
	spawnMobile("rori", "stormtrooper", 300, -5502.5, 75.9, -5664.0, 90, 0)

	spawnMobile("rori", "stormtrooper", 300, -5623.5, 75.9, -5665.5, -90, 0)
	spawnMobile("rori", "stormtrooper", 300, -5623.5, 75.9, -5658.7, -90, 0)
	spawnMobile("rori", "stormtrooper", 300, -5627.5, 75.9, -5661.6, -90, 0)

	spawnMobile("rori", "stormtrooper", 300, -5599.3, 75.9, -5633.7, 180, 0)
	spawnMobile("rori", "stormtrooper", 300, -5595.8, 75.9, -5633.7, 180, 0)

	spawnMobile("rori", "stormtrooper", 300, -5532.3, 75.9, -5633.7, 180, 0)
	spawnMobile("rori", "stormtrooper", 300, -5527.8, 75.9, -5633.7, 180, 0)

	spawnMobile("rori", "stormtrooper", 300, -5599.3, 75.9, -5690.0, 0, 0)
	spawnMobile("rori", "stormtrooper", 300, -5595.8, 75.9, -5690.0, 0, 0)

	spawnMobile("rori", "stormtrooper", 300, -5532.3, 75.9, -5690.0, 0, 0)
	spawnMobile("rori", "stormtrooper", 300, -5527.8, 75.9, -5690.0, 0, 0)

	spawnMobile("rori", "assault_trooper", 300, -5569.1, 75.9, -5630.4, 0, 0)
	spawnMobile("rori", "assault_trooper", 300, -5562.1, 75.9, -5630.4, 0, 0)

	--towers

	spawnMobile("rori", "stormtrooper_sniper", 300, -5510.3, 82.9, -5702.1, 135, 0)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, -5516.1, 82.9, -5702.4, 180, 0)

	spawnMobile("rori", "stormtrooper_sniper", 300, -5508.7, 82.9, -5630.7, 90, 0)
	spawnMobile("rori", "stormtrooper_rifleman", 300, -5509.3, 82.9, -5623.6, 45, 0)
	spawnMobile("rori", "stormtrooper_colonel", 300, -5514.7, 82.9, -5622.7, 0, 0)

	spawnMobile("rori", "stormtrooper_sniper", 300, -5612.8, 83.0, -5623.3, 0, 0)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, -5618.4, 83.0, -5623.7, -45, 0)

	spawnMobile("rori", "stormtrooper_sniper", 300, -5619.4, 82.6, -5696.9, -90, 0)
	spawnMobile("rori", "stormtrooper_rifleman", 300, -5618.5, 82.6, -5702.6, -135, 0)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, -5613.1, 82.6, -5703.4, 180, 0)

	--buildings

	spawnMobile("rori", "stormtrooper_captain", 300, 4.9, 0.0, -2.0, -135, 3475375)
	spawnMobile("rori", "stormtrooper_rifleman", 300, 0.0, 0.0, -5.3, 0, 3475373)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, -3.8, 0.0, -3.6, 90, 3475376)

	spawnMobile("rori", "stormtrooper", 300, 0.0, 0.0, -3.6, 0, 3475366)
	spawnMobile("rori", "stormtrooper_rifleman", 300, 0.0, 0.0, -5.3, 0, 3475366)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, 0.0, 0.0, -1.0, 0, 3475366)

	spawnMobile("rori", "stormtrooper_rifleman", 300, 3.9, 0.0, 2.1, 90, 2935496)
	spawnMobile("rori", "stormtrooper_squad_leader", 300, 0.0, 0.0, -5.3, 0, 2935495)

	--main building

	spawnMobile("rori", "dark_trooper", 300, 1.4, 1.0, 9.9, -90, 2935406)
	spawnMobile("rori", "dark_trooper", 300, 6.4, 1.0, -7.2, -90, 2935406)
	spawnMobile("rori", "dark_trooper", 300, 0.0, 1.0, 0.9, 0, 2935406)

	spawnMobile("rori", "imperial_first_lieutenant", 300, 15.7, 1.0, 15.2, 90, 2935407)
	spawnMobile("rori", "imperial_private", 300, -17.7, 1.0, 16.5, 180, 2935408)
	spawnMobile("rori", "imperial_major", 300, 18.3, 1.0, -19.7, -45, 2935410)
	spawnMobile("rori", "imperial_medic", 300, 11.7, 1.0, -19.5, 0, 2935410)
	spawnMobile("rori", "imperial_private", 300, -17.5, 1.0, -19.6, 45, 2935412)

	spawnMobile("rori", "dark_trooper", 300, -9.2, 7.0, -13.5, 0, 2935414)
	spawnMobile("rori", "dark_trooper", 300, -11.7, 7.0, -13.5, 0, 2935414)

	spawnMobile("rori", "imperial_major", 300, -11.5, 7.0, 9.3, 90, 2935415)
	spawnMobile("rori", "imperial_lieutenant_colonel", 300, -9.1, 7.0, 12.5, 0, 2935415)
	spawnMobile("rori", "imperial_first_lieutenant", 300, 0.0, 7.0, 12.6, 0, 2935415)
	spawnMobile("rori", "imperial_medic", 300, 14.1, 7.0, 11.8, 60, 2935416)

end

function RoriImperialEncampmentScreenPlay:spawnRebels()

	--inside the walls (not in buildings)

	spawnMobile("rori", "senior_specforce_marine", 300, -5506.5, 75.9, -5661.1, 90, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5506.5, 75.9, -5666.9, 90, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5502.5, 75.9, -5664.0, 90, 0)

	spawnMobile("rori", "senior_specforce_marine", 300, -5623.5, 75.9, -5665.5, -90, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5623.5, 75.9, -5658.7, -90, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5627.5, 75.9, -5661.6, -90, 0)

	spawnMobile("rori", "senior_specforce_marine", 300, -5599.3, 75.9, -5633.7, 180, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5595.8, 75.9, -5633.7, 180, 0)

	spawnMobile("rori", "senior_specforce_marine", 300, -5532.3, 75.9, -5633.7, 180, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5527.8, 75.9, -5633.7, 180, 0)

	spawnMobile("rori", "senior_specforce_marine", 300, -5599.3, 75.9, -5690.0, 0, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5595.8, 75.9, -5690.0, 0, 0)

	spawnMobile("rori", "senior_specforce_marine", 300, -5532.3, 75.9, -5690.0, 0, 0)
	spawnMobile("rori", "senior_specforce_marine", 300, -5527.8, 75.9, -5690.0, 0, 0)

	spawnMobile("rori", "rebel_trooper", 300, -5569.1, 75.9, -5630.4, 0, 0)
	spawnMobile("rori", "rebel_trooper", 300, -5562.1, 75.9, -5630.4, 0, 0)

	--towers

	spawnMobile("rori", "senior_specforce_pathfinder", 300, -5510.3, 82.9, -5702.1, 135, 0)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, -5516.1, 82.9, -5702.4, 180, 0)

	spawnMobile("rori", "senior_specforce_pathfinder", 300, -5508.7, 82.9, -5630.7, 90, 0)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, -5509.3, 82.9, -5623.6, 45, 0)
	spawnMobile("rori", "rebel_colonel", 300, -5514.7, 82.9, -5622.7, 0, 0)

	spawnMobile("rori", "senior_specforce_pathfinder", 300, -5612.8, 83.0, -5623.3, 0, 0)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, -5618.4, 83.0, -5623.7, -45, 0)

	spawnMobile("rori", "senior_specforce_pathfinder", 300, -5619.4, 82.6, -5696.9, -90, 0)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, -5618.5, 82.6, -5702.6, -135, 0)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, -5613.1, 82.6, -5703.4, 180, 0)

	--buildings

	spawnMobile("rori", "specforce_major", 300, 4.9, 0.0, -2.0, -135, 3475375)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 0.0, 0.0, -5.3, 0, 3475373)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, -3.8, 0.0, -3.6, 90, 3475376)

	spawnMobile("rori", "senior_specforce_marine", 300, 0.0, 0.0, -3.6, 0, 3475366)
	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 0.0, 0.0, -5.3, 0, 3475366)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, 0.0, 0.0, -1.0, 0, 3475366)

	spawnMobile("rori", "senior_specforce_heavy_weapons_specialist", 300, 3.9, 0.0, 2.1, 90, 2935496)
	spawnMobile("rori", "senior_specforce_lieutenant", 300, 0.0, 0.0, -5.3, 0, 2935495)

	--main building

	spawnMobile("rori", "rebel_surface_marshall", 300, 1.4, 1.0, 9.9, -90, 2935406)
	spawnMobile("rori", "rebel_surface_marshall", 300, 6.4, 1.0, -7.2, -90, 2935406)
	spawnMobile("rori", "rebel_surface_marshall", 300, 0.0, 1.0, 0.9, 0, 2935406)

	spawnMobile("rori", "rebel_first_lieutenant", 300, 15.7, 1.0, 15.2, 90, 2935407)
	spawnMobile("rori", "rebel_surface_marshall", 300, -17.7, 1.0, 16.5, 180, 2935408)
	spawnMobile("rori", "rebel_major", 300, 18.3, 1.0, -19.7, -45, 2935410)
	spawnMobile("rori", "rebel_medic", 300, 11.7, 1.0, -19.5, 0, 2935410)
	spawnMobile("rori", "rebel_trooper", 300, -17.5, 1.0, -19.6, 45, 2935412)

	spawnMobile("rori", "rebel_trooper", 300, -9.2, 7.0, -13.5, 0, 2935414)
	spawnMobile("rori", "rebel_trooper", 300, -11.7, 7.0, -13.5, 0, 2935414)

	spawnMobile("rori", "rebel_major", 300, -11.5, 7.0, 9.3, 90, 2935415)
	spawnMobile("rori", "rebel_lieutenant_colonel", 300, -9.1, 7.0, 12.5, 0, 2935415)
	spawnMobile("rori", "rebel_first_lieutenant", 300, 0.0, 7.0, 12.6, 0, 2935415)
	spawnMobile("rori", "rebel_medic", 300, 14.1, 7.0, 11.8, 60, 2935416)

end

function RoriImperialEncampmentScreenPlay:spawnMobiles()
	--outside the walls

	spawnMobile("rori", "thug", 300, -5574.1, 75.9, -5759.4, 120, 0)
	spawnMobile("rori", "thug", 300, -5559.4, 75.9, -5761.8, 90, 0)
	spawnMobile("rori", "thug", 300, -5557.3, 75.9, -5773.4, 0, 0)
	spawnMobile("rori", "thug", 300, -5562.1, 75.9, -5772.7, -90, 0)
	spawnMobile("rori", "thug", 300, -5569.1, 75.9, -5778.4, -30, 0)
	spawnMobile("rori", "thug", 300, -5551.1, 75.9, -5782.5, 30, 0)
	spawnMobile("rori", "thug", 300, -5559.1, 75.9, -5781.4, -75, 0)
	spawnMobile("rori", "thug", 300, -5562.1, 75.9, -5784.3, 45, 0)
		
end
