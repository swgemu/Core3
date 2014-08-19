ImperialDetachmentHQScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("ImperialDetachmentHQScreenPlay", true)

function ImperialDetachmentHQScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
	end
end

function ImperialDetachmentHQScreenPlay:spawnMobiles()

	-- Entrance
	spawnMobile("tatooine", "stormtrooper", 300, -2589.75, 5, 2116.08, -90, 0)
	spawnMobile("tatooine", "stormtrooper", 300, -2590.52, 5, 2111.61, -90, 0)
	spawnMobile("tatooine", "stormtrooper", 300, -2591.35, 5, 2107.1, -90, 0)
	spawnMobile("tatooine", "stormtrooper", 300, -2592.6, 5, 2100.61, -90, 0)
	
	
	-- Shuttle
	spawnMobile("tatooine", "imperial_pilot", 300, -2574.77, 5.42, 2087.59, -120, 0)
	spawnMobile("tatooine", "imperial_trooper", 300, -2579.42, 5.28, 2085.23, 55, 0)
	
	-- Equipment
	spawnMobile("tatooine", "imperial_trooper", 300, -2590.8, 5, 2069.73, 180, 0)
	
	-- Pallet
	spawnMobile("tatooine", "imperial_private", 300, -2558.17, 5.97, 2106.84, 180, 0)
	
	-- Generator
	spawnMobile("tatooine", "imperial_private", 300, -2555.57, 5.77, 2132.51, -45, 0)
		
	-- Office Exterior
	spawnMobile("tatooine", "stormtrooper", 300, -2573.94, 5.5, 2131.27, 180, 0)
	
	-- Barracks Exterior
	spawnMobile("tatooine", "stormtrooper", 300, -2568.7, 5.69, 2118.6, -90, 0)
	
	-- Bunker Exterior
	spawnMobile("tatooine", "stormtrooper", 300, -2576.48, 5.36, 2098.1, -90, 0)
	
	-- Office Interior
	spawnMobile("tatooine", "imperial_second_lieutenant", 300, 5.36, 0.1, 1.85, -90, 1250091)
	spawnMobile("tatooine", "imperial_private", 300, 2.57, 0.1, 1.74, 90, 1250091)
	spawnMobile("tatooine", "imperial_officer", 300, 4.23, 0.1, -2.13, 180, 1250092)
	spawnMobile("tatooine", "imperial_first_lieutenant", 300, 5.43, 0.1, -4.93, -16, 1250092)
	spawnMobile("tatooine", "imperial_private", 300, -4.21, 0.1, -5.33, 0, 1250093)

	-- Barracks Interior
	spawnMobile("tatooine", "imperial_private", 300, 4.00, 0.1, 2.95, 180, 1250084)
	spawnMobile("tatooine", "imperial_officer", 300, 3.97, 0.1, 1.12, -90, 1250084)
	spawnMobile("tatooine", "imperial_medic", 300, 5.02, 0.1, -4.24, -90, 1250085)
	spawnMobile("tatooine", "imperial_private", 300, -3.06, 0.1, -2.13, -177, 1250086)
	
	-- Bunker Interior
	
		-- Corridor
		spawnMobile("tatooine", "stormtrooper", 300, 3.81, 0.25, -3.84, 0, 1250068)
		
		-- Foyer
		spawnMobile("tatooine", "stormtrooper", 300, 5.98, -6.75, -9.32, 0, 1250071)
		spawnMobile("tatooine", "stormtrooper", 300, 3.07, 6.75, -9.71, 0, 1250071)
		spawnMobile("tatooine", "imperial_noncom", 300, 6.81, -6.75, -3.09, 180, 1250071)
		
		-- Mess hall
		spawnMobile("tatooine", "stormtrooper", 300, -5.05, -13.75, 6.70, -176, 1250073)
		spawnMobile("tatooine", "stormtrooper", 300, -2.16, -13.75, 6.70, -176, 1250073)
		spawnMobile("tatooine", "imperial_officer", 300, -6.39, -13.75, -4.39, 32, 1250073)
		spawnMobile("tatooine", "imperial_staff_sergeant", 300, -4.66, -13.75, -3.3, -126, 1250073)
	
		-- Medical Bay
		spawnMobile("tatooine", "imperial_medic", 300, 6.95, -13.75, 10.05, -90, 1250074)
		
		-- Waiting Room
		spawnMobile("tatooine", "imperial_trooper", 300, 14.12, -13.75, -1.94, 0, 1250075)
		spawnMobile("tatooine", "imperial_trooper", 300, 16.82, -13.75, -1.82, 0, 1250075)
		spawnMobile("tatooine", "imperial_first_lieutenant", 300, 18.12, -13.75, 8.64, -109, 1250075)
		spawnMobile("tatooine", "imperial_major", 300, 16.45, -13.75, 11.56, 180, 1250075)
				
		-- Command Center
		spawnMobile("tatooine", "imperial_trooper", 300, 13.70, -13.75, -4.07, 180, 1250076)
		spawnMobile("tatooine", "imperial_trooper", 300, 17.21, -13.75, -4.09, 180, 1250076)
		spawnMobile("tatooine", "imperial_second_lieutenant", 300, 16.44, -11.5, -20.790, -114, 1250076)
		spawnMobile("tatooine", "imperial_captain", 300, 13.72, -11.5, -21.06, -41, 1250076)
		spawnSceneObject("tatooine", "object/tangible/furniture/all/frn_all_technical_console_s02.iff", 14.06, -13.75, -13.93, 1250076, 0, 0, 0, 0 )
		spawnMobile("tatooine", "imperial_major", 300, 14.0, -13.75, -16.2, 0, 1250076)
		spawnMobile("tatooine", "imperial_major_general", 300, 16.0, -13.75, -13.8, 180, 1250076)
		spawnMobile("tatooine", "r5", 300, 14.0, -13.75, -12.1, 180, 1250076)
				
	-- End Bunker Interior
	
end

