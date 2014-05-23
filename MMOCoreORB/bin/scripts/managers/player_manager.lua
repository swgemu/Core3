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

-----------------------------------
--GENERAL PLAYER SETTINGS
-----------------------------------

--Blue frog / GM buff values
performanceBuff = 1000
medicalBuff = 1900
performanceDuration = 7200 -- in seconds
medicalDuration = 7200 -- in seconds

--Sets the experience multiplier while grouped
groupExpMultiplier = 1.2

--Sets a global experience multiplier
globalExpMultiplier = 1.0

--Sets the base number of control devices of each type that a player can have in their datapad at once
--For creature pets, A Creature Handler will have the base number + their stored pets skill mod as limit
baseStoredCreaturePets = 2
baseStoredFactionPets = 3
baseStoredDroids = 5
baseStoredVehicles = 3
baseStoredShips = 3

-----------------------------------
--VETERAN REWARDS CONFIG
-----------------------------------
-- TODO: CHANGE TO 90, 180, 270, 360 AFTER TESTING
veteranRewardMilestones = {3, 6, 9, 12} --days, must be sorted low to high

veteranRewards = {

	-- 90 Day Rewards
	-- TODO: CHANGE TO 90 AFTER TESTING
	-- Disabled until harvester is functional {templateFile = "object/tangible/veteran_reward/harvester.iff", milestone=90, oneTime=true, description="@veteran_new:poweredharvester"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s1.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal1"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s2.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal2"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s3.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal3"},
	{templateFile = "object/tangible/veteran_reward/data_terminal_s4.iff", milestone=3, oneTime=false, description="@veteran_new:dataterminal4"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_protocol_droid_toy.iff", milestone=3, oneTime=false, description="@veteran_new:mini_protocoldroid"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_r2_toy.iff", milestone=3, oneTime=false, description="@veteran_new:mini_r2"},

	-- 180 Day Rewards
	-- TODO: CHANGE TO 180 AFTER TESTING
	{templateFile = "object/tangible/veteran_reward/resource.iff", milestone=6, oneTime=true, description="@veteran_new:resourcecrate"},
	{templateFile = "object/tangible/veteran_reward/frn_couch_falcon_corner_s01.iff", milestone=6, oneTime=false, description="@veteran_new:falconcouch"},
	{templateFile = "object/tangible/veteran_reward/frn_couch_falcon_section_s01.iff", milestone=6, oneTime=false, description="@veteran_new:falconchair"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_tie_fighter_toy.iff", milestone=6, oneTime=false, description="@veteran_new:mini_tiefighter"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_x_wing_toy.iff", milestone=6, oneTime=false, description="@veteran_new:mini_xwing"},

	-- 270 Day Rewards
	-- TODO: CHANGE TO 270 AFTER TESTING
	{templateFile = "object/tangible/deed/vehicle_deed/speederbike_flash_deed.iff", milestone=9, oneTime=false},
	{templateFile = "object/tangible/wearables/goggles/goggles_s01.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 1"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s02.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 2"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s03.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 3"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s04.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 4"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s05.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 5"},
	{templateFile = "object/tangible/wearables/goggles/goggles_s06.iff", milestone=9, oneTime=false, description="Special Edition Goggles Style 6"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_darth_vader_toy.iff", milestone=9, oneTime=false, description="@veteran_new:mini_darthvader"},

	-- 360 Day Rewards
	-- TODO: CHANGE TO 360 AFTER TESTING
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_a.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_a"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_b.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_b"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_c.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_c"},
	{templateFile = "object/tangible/veteran_reward/frn_tech_console_sectional_d.iff", milestone=12, oneTime=false, description="@veteran_new:techconsole_d"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_jabba_toy.iff", milestone=12, oneTime=false, description="@veteran_new:mini_jabba"},
	{templateFile = "object/tangible/veteran_reward/frn_vet_stormtrooper_toy.iff", milestone=12, oneTime=false, description="@veteran_new:mini_stormtrooper"},
	--Disabled until kits are functional {templateFile = "object/tangible/veteran_reward/antidecay.iff", milestone=12, oneTime=true, description="@veteran_new:antidecay"},
	
}