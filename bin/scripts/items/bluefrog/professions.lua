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

addBFGroup("Combat Professions", "root");
  addBFGroup("Melee Professions", "Combat Professions");
    addBFProfession("Master Brawler", "Melee Professions", "combat_brawler_master");
    addBFProfession("Master Teras Kasi Artist", "Melee Professions", "combat_unarmed_master");
    addBFProfession("Master Fencer", "Melee Professions", "combat_1hsword_master");
    addBFProfession("Master Pikeman", "Melee Professions", "combat_polearm_master");
    addBFProfession("Master Swordsman", "Melee Professions", "combat_2hsword_master");
  addBFGroup("Ranged Professions", "Combat Professions");
    addBFProfession("Master Marksman", "Ranged Professions", "combat_marksman_master");
    addBFProfession("Master Rifleman", "Ranged Professions", "combat_rifleman_master");
    addBFProfession("Master Pistoleer", "Ranged Professions", "combat_pistol_master");
    addBFProfession("Master Carbineer", "Ranged Professions", "combat_carbine_master");
    addBFProfession("Master Bounty Hunter", "Ranged Professions", "combat_bountyhunter_master");
    addBFProfession("Master Commando", "Ranged Professions", "combat_commando_master");
    addBFProfession("Master Smuggler", "Ranged Professions", "combat_smuggler_master");

addBFGroup("Non-Combatant Professions", "root");
  addBFGroup("Healing Professions", "Non-Combatant Professions");
    addBFProfession("Master Doctor", "Healing Professions", "science_doctor_master");
    addBFProfession("Master Medic", "Healing Professions", "science_medic_master");
  addBFGroup("Crafting Professions", "Non-Combatant Professions");
    addBFProfession("Master Artisan", "Crafting Professions", "crafting_artisan_master");
  addBFGroup("Social Professions", "Non-Combatant Professions"); 
    addBFProfession("Master Entertainer", "Social Professions", "social_entertainer_master");
    addBFProfession("Master Musician", "Social Professions", "social_musician_master");
    addBFProfession("Master Dancer", "Social Professions", "social_dancer_master");
    addBFProfession("Master Image Designer", "Social Professions", "social_imagedesigner_master");
  addBFGroup("Outdoor Professions", "Non-Combatant Professions");
    addBFProfession("Exploration 2", "Outdoor Professions", "outdoors_scout_movement_02");
    addBFProfession("Exploration 4", "Outdoor Professions", "outdoors_scout_movement_04");
    addBFProfession("Master Scout", "Outdoor Professions", "outdoors_scout_master");
    addBFProfession("Master Ranger", "Outdoor Professions", "outdoors_ranger_master");
    addBFProfession("Master Squad Leader", "Outdoor Professions", "outdoors_squadleader_master");
        
