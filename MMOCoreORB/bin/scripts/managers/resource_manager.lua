--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.

buildInitialResourcesFromScript = 1 -- Use a script to build resource database when empty
  -- So that during wipes crafters can mantain spreadsheets with calculations

--  These indicate zone names where resources spawn
activeZones = "corellia,tatooine,lok,naboo,rori,endor,talus,yavin4,dathomir,dantooine"

averageShiftTime = 7200000 -- In milliseconds
  --  This is the time between each time the Resource Manager schedules
  --  itself to run again.
  --  *** Default is 2 hours (7200000) ***
  --  *** Good testing time is (15000) ***

aveduration = 86400 -- In seconds
  -- This is the modifier for how long spawns are in shift
  -- Organics are in shift between (6 * aveduration) and  (22 * aveduration)
  -- Inorganics are in shift between (6 * aveduration) and (11 * aveduration)
  -- JTL resources are in shift between (13 * aveduration) and (22 * aveduration)
  -- Set to 86400 for standard SOE behavior

spawnThrottling = 60 -- *** 10-90 ***
  -- This will add a throttle to the spawner so
  -- that 90% of resources will have stats less than
  -- x * maxGate.  So if a resource has stat 0-1000
  -- and this is set at 70, 90% of resources will have 
  -- a value of < 700 and 10% > 700.
  -- Set to 90 for standard SOE behavior

lowerGateOverride = 1000 -- 1-1000  
  -- This will manually set the lower gate to this 
  -- number if it has a lower gate greater than the
  -- number entered.  ex. if a resource has a SOE gate
  -- of 850-950, and the number is set at 300, it will
  -- change the gate to 300-950.  This allows for resource
  -- quality control, especially for resources with 
  -- very high gates.  
  -- Set to 1000 for standard SOE behavior.
  
maxSpawnQuantity = 0 
  -- This value specifies the quantity that a specific resource
  -- will spawn before automatically despawning.  This value
  -- is disabled (0) by default as it is NOT standard behavior, 
  -- but it is an option for admins to have more control over resources.
  -- Set to 0 for standard SOE behavior

--A function used to insert the JTL resources into a lua table.
function InsertJtlIntoTable(jtlString, tab)
	local jtlTable = { {} }

	for k in string.gmatch(jtlString, "[%a_]+") do
		table.insert(jtlTable, k)
	end

	for i = 2, #jtlTable do
		table.insert(tab, {jtlTable[i], 1})
	end
	return tab
end

--  Resources included in the JTL update
jtlresources = "steel_bicorbantium,steel_arveshian,aluminum_perovskitic,copper_borocarbitic,fiberplast_gravitonic,gas_reactive_organometallic,ore_siliclastic_fermionic,radioactive_polymetric"

  -- The minimum pool includes is a table of resources and occurrences. A resource will always be in spawn a number of times equal to it's occurrence.
  -- The minimum pool will never include the items in the excludes
minimumpoolincludes = { {"steel", 1}, {"copper", 1}, {"aluminum", 1}, {"ore_extrusive", 1}, {"ore_intrusive", 1}, {"ore_carbonate", 1}, {"gemstone_crystalline", 1}, {"gemstone_armophous", 1}, {"radioactive_known", 1}, {"fuel_petrochem_solid", 1}, {"fuel_petrochem_liquid", 1}, {"petrochem_inert_polymer", 2}, {"petrochem_inert_lubricating_oil", 2} }
minimumpoolexcludes = jtlresources

-- The random pool includes is a table of resources and weights. The higher the weight, the more likely the resource is to be chosen when a random pool resource shifts.
  -- The random pool will never include the items in the excludes
  -- The random pool spawns a total number of resources equal to the size
randompoolincludes = { {"metal", 32}, {"ore", 13}, {"fuel_petrochem_solid", 6}, {"radioactive", 4}, {"gemstone", 12}, {"gas", 16}, {"water", 2}, {"fuel_petrochem_liquid", 7}, {"petrochem_inert", 8} }
randompoolexcludes = jtlresources..",iron,fiberplast"
randompoolsize = 27

  -- The fixed pool is a table of resources and occurrences. A resource will always be in spawn a number of times equal to it's occurrence. The function call inserts each JTL resource into the table with an occurrence of 1.
fixedpoolincludes = InsertJtlIntoTable(jtlresources, { {"iron", 14} })
fixedpoolexcludes = ""

  -- The native pool will have one of each of the items listed in the includes spawned on each planet at all times, but planet restricted.
nativepoolincludes = "milk_domesticated,milk_wild,meat_domesticated,meat_wild,meat_herbivore,meat_carnivore,meat_reptilian,meat_avian,meat_egg,meat_insect,seafood_fish,seafood_crustacean,seafood_mollusk,bone_mammal,bone_avian,bone_horn,hide_wooly,hide_bristley,hide_leathery,hide_scaley,corn_domesticated,corn_wild,rice_domesticated,rice_wild,oats_domesticated,oats_wild,wheat_domesticated,wheat_wild,vegetable_greens,vegetable_beans,vegetable_tubers,vegetable_fungi,fruit_fruits,fruit_berries,fruit_flowers,wood_deciduous,softwood_conifer,softwood_evergreen,energy_renewable_unlimited_solar,energy_renewable_unlimited_wind,fiberplast,water_vapor"
nativepoolexcludes = ""

-- The recycled resource types from the client files.
recycledresources = "milk_homogenized,processed_meat,processed_seafood,ground_bones,bone_horn_ground,synthesized_hides,processed_cereal,mixed_vegetables,mixed_fruits,processed_wood,chemical_compound,water_solution,degraded_fuel_petrochem_solid,combined_radioactive_isotpopes,smelted_metal_ferrous_unknown,steel_smelted,iron_smelted,smelted_metal_nonferrous_unknown,aluminum_smelted,copper_smelted,ore_extrusive_low_grade,ore_carbonate_low_grade,ore_siliclastic_low_grade,gemstone_mixed_low_quality,gas_reactive_mixed,gas_inert_mixed,energy_renewable_site_limited_tidal_weak,energy_renewable_site_limited_hydron3_weak,energy_renewable_site_limited_geothermal_weak,energy_renewable_unlimited_wind_weak,energy_renewable_unlimited_solar_weak"

