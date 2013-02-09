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


object_draft_schematic_bio_engineer_dna_template_dna_template_generic = object_draft_schematic_bio_engineer_dna_template_shared_dna_template_generic:new {

   templateType = DRAFTSCHEMATIC,

   customObjectName = "Generic DNA Template",

   craftingToolTab = 8192, -- (See DraftSchemticImplementation.h)
   complexity = 18, 
   size = 1, 

   xpType = "crafting_bio_engineer_creature", 
   xp = 50, 

   assemblySkill = "bio_engineer_assembly", 
   experimentingSkill = "bio_engineer_experimentation", 
   customizationSkill = "bio_customization", 

   customizationOptions = {},
   customizationStringNames = {},
   customizationDefaults = {},

   ingredientTemplateNames = {"craft_creature_ingredients_n", "craft_creature_ingredients_n", "craft_creature_ingredients_n", "craft_creature_ingredients_n", "craft_creature_ingredients_n"},
   ingredientTitleNames = {"physique_profile", "prowess_profile", "mental_profile", "psychological_profile", "aggression_profile"},
   ingredientSlotType = {2, 2, 2, 2, 2},
   resourceTypes = {"object/tangible/component/base/shared_base_dna_sample.iff", "object/tangible/component/base/shared_base_dna_sample.iff", "object/tangible/component/base/shared_base_dna_sample.iff", "object/tangible/component/base/shared_base_dna_sample.iff", "object/tangible/component/base/shared_base_dna_sample.iff"},
   resourceQuantities = {1, 1, 1, 1, 1},
   contribution = {100, 100, 100, 100, 100},


   targetTemplate = "object/tangible/component/dna/dna_template_generic.iff",

   additionalTemplates = {
             }

}
ObjectTemplates:addTemplate(object_draft_schematic_bio_engineer_dna_template_dna_template_generic, "object/draft_schematic/bio_engineer/dna_template/dna_template_generic.iff")
