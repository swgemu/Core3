--Copyright (C) 2010 <SWGEmu>


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



--Children folder includes
includeFile("draft_schematic/chemistry/component/serverobjects.lua")

-- Server Objects
includeFile("draft_schematic/chemistry/antidote_sm_s1.lua")
includeFile("draft_schematic/chemistry/dye_kit_clothing.lua")
includeFile("draft_schematic/chemistry/dye_kit_hair.lua")
includeFile("draft_schematic/chemistry/med_fire_blanket.lua")
includeFile("draft_schematic/chemistry/med_stimpack_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_area_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_area_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_area_c.lua")
includeFile("draft_schematic/chemistry/med_stimpack_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_c.lua")
includeFile("draft_schematic/chemistry/med_stimpack_d.lua")
includeFile("draft_schematic/chemistry/med_stimpack_e.lua")
includeFile("draft_schematic/chemistry/med_stimpack_range_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_range_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_range_c.lua")
includeFile("draft_schematic/chemistry/med_stimpack_range_d.lua")
includeFile("draft_schematic/chemistry/med_stimpack_range_e.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_blinded_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_blinded_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_dizzy_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_dizzy_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_intimidated_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_intimidated_b.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_stunned_a.lua")
includeFile("draft_schematic/chemistry/med_stimpack_state_stunned_b.lua")
includeFile("draft_schematic/chemistry/medic_damage.lua")
includeFile("draft_schematic/chemistry/medikit_advanced.lua")
includeFile("draft_schematic/chemistry/medikit_basic.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_a.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_area_a.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_area_b.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_area_c.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_b.lua")
includeFile("draft_schematic/chemistry/medpack_cure_disease_c.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_a.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_area_a.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_area_b.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_area_c.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_b.lua")
includeFile("draft_schematic/chemistry/medpack_cure_poison_c.lua")
includeFile("draft_schematic/chemistry/medpack_damage.lua")
includeFile("draft_schematic/chemistry/medpack_disease_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_constitution_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_constitution_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_constitution_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_focus_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_focus_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_focus_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_mind_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_mind_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_mind_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_quickness_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_quickness_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_quickness_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_stamina_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_stamina_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_stamina_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_strength_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_strength_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_strength_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_willpower_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_willpower_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_area_willpower_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_constitution_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_constitution_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_constitution_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_focus_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_focus_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_focus_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_mind_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_mind_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_mind_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_quickness_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_quickness_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_quickness_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_stamina_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_stamina_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_stamina_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_strength_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_strength_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_strength_c.lua")
includeFile("draft_schematic/chemistry/medpack_disease_willpower_a.lua")
includeFile("draft_schematic/chemistry/medpack_disease_willpower_b.lua")
includeFile("draft_schematic/chemistry/medpack_disease_willpower_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_action_d.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_constitution_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_constitution_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_constitution_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_constitution_d.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_disease_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_disease_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_disease_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_health_d.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_poison_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_poison_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_poison_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_quickness_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_quickness_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_quickness_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_quickness_d.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_stamina_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_stamina_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_stamina_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_stamina_d.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_strength_a.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_strength_b.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_strength_c.lua")
includeFile("draft_schematic/chemistry/medpack_enhance_strength_d.lua")
includeFile("draft_schematic/chemistry/medpack_poison_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_mind_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_mind_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_area_mind_c.lua")
includeFile("draft_schematic/chemistry/medpack_poison_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_poison_mind_a.lua")
includeFile("draft_schematic/chemistry/medpack_poison_mind_b.lua")
includeFile("draft_schematic/chemistry/medpack_poison_mind_c.lua")
includeFile("draft_schematic/chemistry/medpack_revive.lua")
includeFile("draft_schematic/chemistry/medpack_sm_s1.lua")
includeFile("draft_schematic/chemistry/medpack_wound.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_action_e.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_constitution_e.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_health_e.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_quickness_e.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_stamina_e.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength_a.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength_b.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength_c.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength_d.lua")
includeFile("draft_schematic/chemistry/medpack_wound_strength_e.lua")
includeFile("draft_schematic/chemistry/quest_stimpack_a.lua")
includeFile("draft_schematic/chemistry/stimpack_sm_s1.lua")
