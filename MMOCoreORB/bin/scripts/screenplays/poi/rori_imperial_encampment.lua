local ObjectManager = require("managers.object.object_manager")

RoriImperialEncampmentScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	buildingID = 2935404,
}

registerScreenPlay("RoriImperialEncampmentScreenPlay", true)

function RoriImperialEncampmentScreenPlay:start()
	if isZoneEnabled("rori") then
		local pBuilding = getSceneObject(self.buildingID)
		self:spawnMobiles()

		if (pBuilding ~= nil) then
			createObserver(FACTIONBASEFLIPPED, "RoriImperialEncampmentScreenPlay", "flipBase", pBuilding)

			if getRandomNumber(100) >= 50 then
				self:spawnRebels(pBuilding)
			else
				self:spawnImperials(pBuilding)
			end
		end
	end
end

function RoriImperialEncampmentScreenPlay:flipBase(pBuilding)
	if (pBuilding == nil) then
		return 1
	end

	BuildingObject(pBuilding):destroyChildObjects()

	if BuildingObject(pBuilding):getFaction() == FACTIONIMPERIAL then
		self:spawnRebels(pBuilding)
	else
		self:spawnImperials(pBuilding)
	end

	return 0
end

function RoriImperialEncampmentScreenPlay:spawnImperials(pBuilding)
	if (pBuilding == nil) then
		return
	end

	BuildingObject(pBuilding):initializeStaticGCWBase(FACTIONIMPERIAL)

	--inside the walls (not in buildings)
	BuildingObject(pBuilding):spawnChildCreature("at_st", 720, -5597.3, 75.9, -5660.5, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("at_st", 720, -5531.5, 75.9, -5660.5, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5506.5, 75.9, -5661.1, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5506.5, 75.9, -5666.9, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5502.5, 75.9, -5664.0, 90, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5623.5, 75.9, -5665.5, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5623.5, 75.9, -5658.7, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5627.5, 75.9, -5661.6, -90, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5599.3, 75.9, -5633.7, 180, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5595.8, 75.9, -5633.7, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5532.3, 75.9, -5633.7, 180, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5527.8, 75.9, -5633.7, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5599.3, 75.9, -5690.0, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5595.8, 75.9, -5690.0, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5532.3, 75.9, -5690.0, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, -5527.8, 75.9, -5690.0, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("assault_trooper", 300, -5569.1, 75.9, -5630.4, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("assault_trooper", 300, -5562.1, 75.9, -5630.4, 0, 0)

	--towers
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_sniper", 300, -5510.3, 82.9, -5702.1, 135, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, -5516.1, 82.9, -5702.4, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_sniper", 300, -5508.7, 82.9, -5630.7, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_rifleman", 300, -5509.3, 82.9, -5623.6, 45, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_colonel", 300, -5514.7, 82.9, -5622.7, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_sniper", 300, -5612.8, 83.0, -5623.3, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, -5618.4, 83.0, -5623.7, -45, 0)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_sniper", 300, -5619.4, 82.6, -5696.9, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_rifleman", 300, -5618.5, 82.6, -5702.6, -135, 0)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, -5613.1, 82.6, -5703.4, 180, 0)

	--buildings
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_captain", 300, 4.9, 0.0, -2.0, -135, 3475375)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_rifleman", 300, 0.0, 0.0, -5.3, 0, 3475373)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, -3.8, 0.0, -3.6, 90, 3475376)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper", 300, 0.0, 0.0, -3.6, 0, 3475366)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_rifleman", 300, 0.0, 0.0, -5.3, 0, 3475366)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, 0.0, 0.0, -1.0, 0, 3475366)

	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_rifleman", 300, 3.9, 0.0, 2.1, 90, 2935496)
	BuildingObject(pBuilding):spawnChildCreature("stormtrooper_squad_leader", 300, 0.0, 0.0, -5.3, 0, 2935495)

	--main building
	BuildingObject(pBuilding):spawnChildCreature("dark_trooper", 300, 1.4, 1.0, 9.9, -90, 2935406)
	BuildingObject(pBuilding):spawnChildCreature("dark_trooper", 300, 6.4, 1.0, -7.2, -90, 2935406)
	BuildingObject(pBuilding):spawnChildCreature("dark_trooper", 300, 0.0, 1.0, 0.9, 0, 2935406)

	BuildingObject(pBuilding):spawnChildCreature("imperial_first_lieutenant", 300, 15.7, 1.0, 15.2, 90, 2935407)
	BuildingObject(pBuilding):spawnChildCreature("imperial_private", 300, -17.7, 1.0, 16.5, 180, 2935408)
	BuildingObject(pBuilding):spawnChildCreature("imperial_major", 300, 18.3, 1.0, -19.7, -45, 2935410)
	BuildingObject(pBuilding):spawnChildCreature("imperial_medic", 300, 11.7, 1.0, -19.5, 0, 2935410)
	BuildingObject(pBuilding):spawnChildCreature("imperial_private", 300, -17.5, 1.0, -19.6, 45, 2935412)

	BuildingObject(pBuilding):spawnChildCreature("dark_trooper", 300, -9.2, 7.0, -13.5, 0, 2935414)
	BuildingObject(pBuilding):spawnChildCreature("dark_trooper", 300, -11.7, 7.0, -13.5, 0, 2935414)

	BuildingObject(pBuilding):spawnChildCreature("imperial_major", 300, -11.5, 7.0, 9.3, 90, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("imperial_lieutenant_colonel", 300, -9.1, 7.0, 12.5, 0, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("imperial_first_lieutenant", 300, 0.0, 7.0, 12.6, 0, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("imperial_medic", 300, 14.1, 7.0, 11.8, 60, 2935416)

end

function RoriImperialEncampmentScreenPlay:spawnRebels(pBuilding)
	if (pBuilding == nil) then
		return
	end

	BuildingObject(pBuilding):initializeStaticGCWBase(FACTIONREBEL)

	--inside the walls (not in buildings)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5506.5, 75.9, -5661.1, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5506.5, 75.9, -5666.9, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5502.5, 75.9, -5664.0, 90, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5623.5, 75.9, -5665.5, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5623.5, 75.9, -5658.7, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5627.5, 75.9, -5661.6, -90, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5599.3, 75.9, -5633.7, 180, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5595.8, 75.9, -5633.7, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5532.3, 75.9, -5633.7, 180, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5527.8, 75.9, -5633.7, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5599.3, 75.9, -5690.0, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5595.8, 75.9, -5690.0, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5532.3, 75.9, -5690.0, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, -5527.8, 75.9, -5690.0, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("rebel_trooper", 300, -5569.1, 75.9, -5630.4, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("rebel_trooper", 300, -5562.1, 75.9, -5630.4, 0, 0)

	--towers
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_pathfinder", 300, -5510.3, 82.9, -5702.1, 135, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, -5516.1, 82.9, -5702.4, 180, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_pathfinder", 300, -5508.7, 82.9, -5630.7, 90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, -5509.3, 82.9, -5623.6, 45, 0)
	BuildingObject(pBuilding):spawnChildCreature("rebel_colonel", 300, -5514.7, 82.9, -5622.7, 0, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_pathfinder", 300, -5612.8, 83.0, -5623.3, 0, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, -5618.4, 83.0, -5623.7, -45, 0)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_pathfinder", 300, -5619.4, 82.6, -5696.9, -90, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, -5618.5, 82.6, -5702.6, -135, 0)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, -5613.1, 82.6, -5703.4, 180, 0)

	--buildings
	BuildingObject(pBuilding):spawnChildCreature("specforce_major", 300, 4.9, 0.0, -2.0, -135, 3475375)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 0.0, 0.0, -5.3, 0, 3475373)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, -3.8, 0.0, -3.6, 90, 3475376)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_marine", 300, 0.0, 0.0, -3.6, 0, 3475366)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 0.0, 0.0, -5.3, 0, 3475366)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, 0.0, 0.0, -1.0, 0, 3475366)

	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_heavy_weapons_specialist", 300, 3.9, 0.0, 2.1, 90, 2935496)
	BuildingObject(pBuilding):spawnChildCreature("senior_specforce_lieutenant", 300, 0.0, 0.0, -5.3, 0, 2935495)

	--main building
	BuildingObject(pBuilding):spawnChildCreature("rebel_surface_marshall", 300, 1.4, 1.0, 9.9, -90, 2935406)
	BuildingObject(pBuilding):spawnChildCreature("rebel_surface_marshall", 300, 6.4, 1.0, -7.2, -90, 2935406)
	BuildingObject(pBuilding):spawnChildCreature("rebel_surface_marshall", 300, 0.0, 1.0, 0.9, 0, 2935406)

	BuildingObject(pBuilding):spawnChildCreature("rebel_first_lieutenant", 300, 15.7, 1.0, 15.2, 90, 2935407)
	BuildingObject(pBuilding):spawnChildCreature("rebel_surface_marshall", 300, -17.7, 1.0, 16.5, 180, 2935408)
	BuildingObject(pBuilding):spawnChildCreature("rebel_major", 300, 18.3, 1.0, -19.7, -45, 2935410)
	BuildingObject(pBuilding):spawnChildCreature("rebel_medic", 300, 11.7, 1.0, -19.5, 0, 2935410)
	BuildingObject(pBuilding):spawnChildCreature("rebel_trooper", 300, -17.5, 1.0, -19.6, 45, 2935412)

	BuildingObject(pBuilding):spawnChildCreature("rebel_trooper", 300, -9.2, 7.0, -13.5, 0, 2935414)
	BuildingObject(pBuilding):spawnChildCreature("rebel_trooper", 300, -11.7, 7.0, -13.5, 0, 2935414)

	BuildingObject(pBuilding):spawnChildCreature("rebel_major", 300, -11.5, 7.0, 9.3, 90, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("rebel_lieutenant_colonel", 300, -9.1, 7.0, 12.5, 0, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("rebel_first_lieutenant", 300, 0.0, 7.0, 12.6, 0, 2935415)
	BuildingObject(pBuilding):spawnChildCreature("rebel_medic", 300, 14.1, 7.0, 11.8, 60, 2935416)

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
