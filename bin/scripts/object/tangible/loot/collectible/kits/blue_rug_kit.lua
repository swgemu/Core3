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


object_tangible_loot_collectible_kits_blue_rug_kit = object_tangible_loot_collectible_kits_shared_blue_rug_kit:new {

	templateType = LOOTKIT,

	gameObjectType = 8233,
	
	--These are used to determine which components are necessary in the loot kit to finish the item
	collectibleComponents = {"object/tangible/loot/collectible/collectible_parts/blue_rug_adhesive.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_dye.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_patches.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_01.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_02.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_03.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_04.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_05.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_06.iff", "object/tangible/loot/collectible/collectible_parts/blue_rug_thread_07.iff"},
	
	collectibleReward = {"object/tangible/loot/collectible/collectible_rewards/blue_rug.iff"},

	deleteComponents = 1,

	--These are used to display to the player which components he already added. Same order as above is used
	attributes = {"blue_rug_adhesive","blue_rug_dye","blue_rug_cloth_patches","blue_rug_thread_01","blue_rug_thread_02","blue_rug_thread_03","blue_rug_thread_04","blue_rug_thread_05","blue_rug_thread_06","blue_rug_thread_07"}
}

ObjectTemplates:addTemplate(object_tangible_loot_collectible_kits_blue_rug_kit, "object/tangible/loot/collectible/kits/blue_rug_kit.iff")
