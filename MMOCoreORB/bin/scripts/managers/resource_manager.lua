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

--  Resources included in the JTL update
jtlresources = "steel_bicorbantium,steel_arveshian,aluminum_perovskitic,copper_borocarbitic,fiberplast_gravitonic,gas_reactive_organometallic,ore_siliclastic_fermionic,radioactive_polymetric"

  -- The minimum pool must have one of each of the items listed above spawned at all times.
  -- The minimum pool must never include the items in the excludes
--minimumpoolincludes = "steel,copper,aluminum,ore_extrusive,ore_intrusive,ore_carbonate,gemstone_crystalline,gemstone_armophous,radioactive_known,fuel_petrochem_solid,fuel_petrochem_liquid,petrochem_inert_polymer,petrochem_inert_polymer,petrochem_inert_lubricating_oil,petrochem_inert_lubricating_oil"
  -- The statement below spawn all resources all the time for development
minimumpoolincludes = "petrochem_fuel_liquid_type1,radioactive_type1,petrochem_fuel_solid_type1,petrochem_fuel_liquid_type2,radioactive_type2,petrochem_fuel_solid_type2,petrochem_fuel_liquid_type3,radioactive_type3,petrochem_fuel_solid_type3,petrochem_fuel_liquid_type4,radioactive_type4,petrochem_fuel_solid_type4,petrochem_fuel_liquid_type5,radioactive_type5,petrochem_fuel_solid_type5,petrochem_fuel_liquid_type6,radioactive_type6,petrochem_fuel_solid_type6,petrochem_fuel_liquid_type7,radioactive_type7,petrochem_fuel_solid_type7,energy_renewable_unlimited_solar_corellia,energy_renewable_unlimited_wind_corellia,energy_renewable_unlimited_solar_dantooine,energy_renewable_unlimited_wind_dantooine,energy_renewable_unlimited_solar_dathomir,energy_renewable_unlimited_wind_dathomir,energy_renewable_unlimited_solar_endor,energy_renewable_unlimited_wind_endor,radioactive_polymetric,energy_renewable_unlimited_solar_lok,energy_renewable_unlimited_wind_lok,energy_renewable_unlimited_solar_naboo,energy_renewable_unlimited_wind_naboo,energy_renewable_unlimited_solar_rori,energy_renewable_unlimited_wind_rori,energy_renewable_unlimited_solar_talus,energy_renewable_unlimited_wind_talus,energy_renewable_unlimited_solar_tatooine,energy_renewable_unlimited_wind_tatooine,gas_reactive_organometallic,energy_renewable_unlimited_solar_yavin4,energy_renewable_unlimited_wind_yavin4,fiberplast_corellia,fiberplast_dantooine,fiberplast_dathomir,fiberplast_endor,fiberplast_lok,fiberplast_naboo,fiberplast_rori,fiberplast_talus,fiberplast_tatooine,fiberplast_gravitonic,fiberplast_yavin4,steel_arveshian,steel_bicorbantium,aluminum_perovskitic,copper_borocarbitic,ore_siliclastic_fermionic,armophous_baltaran,armophous_baradium,gas_inert_bilal,armophous_bospridium,crystalline_byrothsis,gas_inert_corthel,gas_inert_culsion,gas_inert_dioxis,gas_reactive_eleton,crystalline_gallinorian,crystalline_green_diamond,gas_inert_hurlothrombic,gas_inert_hydron3,gas_reactive_irolunn,gas_inert_kaylon,crystalline_kerol_firegem,gas_inert_korfaise,crystalline_laboi_mineral_crystal,gas_inert_malium,gas_inert_methanagen,gas_reactive_methane,gas_inert_mirth,gas_inert_obah,gas_reactive_orveth,armophous_plexite,armophous_regvis,gas_inert_rethin,armophous_rudic,armophous_ryll,crystalline_seafah_jewel,armophous_sedrellium,gas_reactive_sig,gas_reactive_skevon,crystalline_sormahil_firegem,armophous_stygium,gas_reactive_tolium,metal_ferrous_unknown,ore_igneous_unknown,metal_nonferrous_unknown,ore_sedimentary_unknown,armophous_vendusii,crystalline_vertex,petrochem_fuel_liquid_unknown,petrochem_fuel_solid_unknown,radioactive_unknown,aluminum_titanium,aluminum_agrinium,aluminum_chromium,aluminum_duralumin,aluminum_linksteel,aluminum_phrik,copper_desh,copper_thallium,copper_beyrllius,copper_codoan,copper_diatium,copper_kelsh,copper_mythra,copper_platinite,copper_polysteel,ore_extrusive_bene,ore_extrusive_chronamite,ore_extrusive_ilimium,ore_extrusive_kalonterium,ore_extrusive_keschel,ore_extrusive_lidium,ore_extrusive_maranium,ore_extrusive_pholokite,ore_extrusive_quadrenium,ore_extrusive_vintrium,ore_intrusive_berubium,ore_intrusive_chanlon,ore_intrusive_corintium,ore_intrusive_derillium,ore_intrusive_oridium,ore_intrusive_dylinium,ore_intrusive_hollinium,ore_intrusive_ionite,ore_intrusive_katrium,ore_carbonate_alantium,ore_carbonate_barthierium,ore_carbonate_chromite,ore_carbonate_frasium,ore_carbonate_lommite,ore_carbonate_ostrine,ore_carbonate_varium,ore_carbonate_zinsiam,ore_siliclastic_ardanium,ore_siliclastic_cortosis,ore_siliclastic_crism,ore_siliclastic_malab,ore_siliclastic_robindun,ore_siliclastic_tertian,gemstone_unknown,gas_reactive_unknown,gas_inert_unknown,energy_renewable_site_limited_tidal_corellia,energy_renewable_site_limited_tidal_dathomir,energy_renewable_site_limited_tidal_dantooine,energy_renewable_site_limited_tidal_endor,energy_renewable_site_limited_tidal_lok,energy_renewable_site_limited_tidal_naboo,energy_renewable_site_limited_tidal_rori,energy_renewable_site_limited_tidal_talus,energy_renewable_site_limited_tidal_tatooine,energy_renewable_site_limited_tidal_yavin4,energy_renewable_site_limited_hydron3_corellia,energy_renewable_site_limited_hydron3_dantooine,energy_renewable_site_limited_hydron3_dathomir,energy_renewable_site_limited_hydron3_endor,energy_renewable_site_limited_hydron3_lok,energy_renewable_site_limited_hydron3_naboo,energy_renewable_site_limited_hydron3_rori,energy_renewable_site_limited_hydron3_talus,energy_renewable_site_limited_hydron3_tatooine,energy_renewable_site_limited_hydron3_yavin4,energy_renewable_site_limited_geothermal_corellia,energy_renewable_site_limited_geothermal_dantooine,energy_renewable_site_limited_geothermal_dathomir,energy_renewable_site_limited_geothermal_endor,energy_renewable_site_limited_geothermal_lok,energy_renewable_site_limited_geothermal_naboo,energy_renewable_site_limited_geothermal_rori,energy_renewable_site_limited_geothermal_talus,energy_renewable_site_limited_geothermal_tatooine,energy_renewable_site_limited_geothermal_yavin4,radioactive_known,fuel_petrochem_liquid_known,petrochem_inert_lubricating_oil,petrochem_inert_polymer,water_vapor_corellia,water_vapor_dantooine,water_vapor_dathomir,water_vapor_endor,water_vapor_lok,water_vapor_naboo,water_vapor_rori,water_vapor_talus,water_vapor_tatooine,water_vapor_yavin4,steel_rhodium,steel_kiirium,steel_cubirian,steel_thoranium,steel_neutronium,steel_duranium,steel_ditanium,steel_quadranium,steel_carbonite,steel_duralloy,iron_plumbum,iron_polonium,iron_axidite,iron_bronzium,iron_colat,iron_dolovite,iron_doonium,iron_kammris,fuel_petrochem_solid_known"
miniinitializemumpoolexcludes = jtlresources

  -- The random pool must have one of each of the items listed above spawned at all times.
  -- The random pool must never include the items in the excludes
randompoolincludes = "mineral,gas,chemical,water"
randompoolexcludes = jtlresources..",iron,fiberplast"
randompoolsize = 27
  
  -- The fixed pool must have one of each of the items listed above spawned at all times.
fixedpoolincludes = jtlresources..",iron,iron,iron,iron,iron,iron,iron,iron,iron,iron,iron,iron,iron,iron"
fixedpoolexcludes = ""

  -- The native pool must have one of each of the items listed above spawned at all times, but planet restricted.
nativepoolincludes = "milk_domesticated,milk_wild,meat_domesticated,meat_wild,meat_herbivore,meat_carnivore,meat_reptilian,meat_avian,meat_egg,meat_insect,seafood_fish,seafood_crustacean,seafood_mollusk,bone_mammal,bone_avian,bone_horn,hide_wooly,hide_bristley,hide_leathery,hide_scaley,corn_domesticated,corn_wild,rice_domesticated,rice_wild,oats_domesticated,oats_wild,wheat_domesticated,wheat_wild,vegetable_greens,vegetable_beans,vegetable_tubers,vegetable_fungi,fruit_fruits,fruit_berries,fruit_flowers,wood_deciduous,softwood_conifer,softwood_evergreen,energy_renewable_unlimited_solar,energy_renewable_unlimited_wind,fiberplast"
nativepoolexcludes = ""

