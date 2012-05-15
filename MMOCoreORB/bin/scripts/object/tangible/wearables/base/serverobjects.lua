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

-- Server Objects
includeFile("tangible/wearables/base/armor_base.lua")
includeFile("tangible/wearables/base/base_back.lua")
includeFile("tangible/wearables/base/base_backpack.lua")
includeFile("tangible/wearables/base/base_bandolier.lua")
includeFile("tangible/wearables/base/base_belt.lua")
includeFile("tangible/wearables/base/base_bicep_both.lua")
includeFile("tangible/wearables/base/base_bicep_l.lua")
includeFile("tangible/wearables/base/base_bicep_r.lua")
includeFile("tangible/wearables/base/base_bracer_both.lua")
includeFile("tangible/wearables/base/base_bracer_l.lua")
includeFile("tangible/wearables/base/base_bracer_r.lua")
includeFile("tangible/wearables/base/base_bracer_upper_both.lua")
includeFile("tangible/wearables/base/base_bracer_upper_l.lua")
includeFile("tangible/wearables/base/base_bracer_upper_r.lua")
includeFile("tangible/wearables/base/base_cape.lua")
includeFile("tangible/wearables/base/base_cloak.lua")
includeFile("tangible/wearables/base/base_cloak_hooded.lua")
includeFile("tangible/wearables/base/base_cloak_noback.lua")
includeFile("tangible/wearables/base/base_costume_allow_jewelry.lua")
includeFile("tangible/wearables/base/base_costume_full.lua")
includeFile("tangible/wearables/base/base_dress.lua")
includeFile("tangible/wearables/base/base_dress_formal.lua")
includeFile("tangible/wearables/base/base_dress_formal_gloved.lua")
includeFile("tangible/wearables/base/base_dress_formal_hooded.lua")
includeFile("tangible/wearables/base/base_dress_poofysleeve_allow_gauntlets.lua")
includeFile("tangible/wearables/base/base_dress_poofysleeve_full.lua")
includeFile("tangible/wearables/base/base_dress_poofysleeve_lower.lua")
includeFile("tangible/wearables/base/base_dress_poofysleeve_upper.lua")
includeFile("tangible/wearables/base/base_ear_both.lua")
includeFile("tangible/wearables/base/base_ear_either.lua")
includeFile("tangible/wearables/base/base_ear_l.lua")
includeFile("tangible/wearables/base/base_ear_r.lua")
includeFile("tangible/wearables/base/base_eyes.lua")
includeFile("tangible/wearables/base/base_gauntlets.lua")
includeFile("tangible/wearables/base/base_gauntlets_long.lua")
includeFile("tangible/wearables/base/base_gloves.lua")
includeFile("tangible/wearables/base/base_gloves_long.lua")
includeFile("tangible/wearables/base/base_hat.lua")
includeFile("tangible/wearables/base/base_held_both.lua")
includeFile("tangible/wearables/base/base_held_l.lua")
includeFile("tangible/wearables/base/base_held_r.lua")
includeFile("tangible/wearables/base/base_helmet_closed_eyes.lua")
includeFile("tangible/wearables/base/base_helmet_closed_full.lua")
includeFile("tangible/wearables/base/base_helmet_closed_full_ventilated.lua")
includeFile("tangible/wearables/base/base_helmet_closed_mouth.lua")
includeFile("tangible/wearables/base/base_helmet_open.lua")
includeFile("tangible/wearables/base/base_jacket_halfsleeve.lua")
includeFile("tangible/wearables/base/base_jacket_longsleeve.lua")
includeFile("tangible/wearables/base/base_jacket_shortsleeve.lua")
includeFile("tangible/wearables/base/base_jewelry_set.lua")
includeFile("tangible/wearables/base/base_jumpsuit.lua")
includeFile("tangible/wearables/base/base_jumpsuit_gloved.lua")
includeFile("tangible/wearables/base/base_jumpsuit_longsleeve.lua")
includeFile("tangible/wearables/base/base_jumpsuit_shortsleeve.lua")
includeFile("tangible/wearables/base/base_mask_face.lua")
includeFile("tangible/wearables/base/base_mouth.lua")
includeFile("tangible/wearables/base/base_neck.lua")
includeFile("tangible/wearables/base/base_pants.lua")
includeFile("tangible/wearables/base/base_pauldron_both.lua")
includeFile("tangible/wearables/base/base_pauldron_l.lua")
includeFile("tangible/wearables/base/base_pauldron_r.lua")
includeFile("tangible/wearables/base/base_ring_both.lua")
includeFile("tangible/wearables/base/base_ring_either.lua")
includeFile("tangible/wearables/base/base_ring_l.lua")
includeFile("tangible/wearables/base/base_ring_r.lua")
includeFile("tangible/wearables/base/base_robe_longsleeve.lua")
includeFile("tangible/wearables/base/base_robe_longsleeve_hooded.lua")
includeFile("tangible/wearables/base/base_robe_shortsleeve.lua")
includeFile("tangible/wearables/base/base_robe_shortsleeve_hooded.lua")
includeFile("tangible/wearables/base/base_shirt.lua")
includeFile("tangible/wearables/base/base_shirt_poofysleeve_full.lua")
includeFile("tangible/wearables/base/base_shirt_poofysleeve_lower.lua")
includeFile("tangible/wearables/base/base_shirt_poofysleeve_upper.lua")
includeFile("tangible/wearables/base/base_shoes.lua")
includeFile("tangible/wearables/base/base_skirt.lua")
includeFile("tangible/wearables/base/base_sleeve_both.lua")
includeFile("tangible/wearables/base/base_sleeve_l.lua")
includeFile("tangible/wearables/base/base_sleeve_r.lua")
includeFile("tangible/wearables/base/base_vest.lua")
includeFile("tangible/wearables/base/base_wrist_both.lua")
includeFile("tangible/wearables/base/base_wrist_either.lua")
includeFile("tangible/wearables/base/base_wrist_l.lua")
includeFile("tangible/wearables/base/base_wrist_r.lua")
includeFile("tangible/wearables/base/wearables_base.lua")
