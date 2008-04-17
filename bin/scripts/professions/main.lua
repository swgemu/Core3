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

itemMap = { }

function addToItemMap(class, itemcontainer)
	itemMap[class] = itemcontainer
end

function createItems(Name, Profession, Species, Sex)
	local ic = itemMap[Profession]
	local gen = itemMap["general"]

	createItemsInList(ic.global_class_items, Name)
	createItemsInList(gen.global_class_items, Name)

	if Species == "ithorian" then
		if Sex == "male" then
			createItemsInList(ic.itho_male_items, Name)
			createItemsInList(gen.itho_male_items, Name)
		else
			createItemsInList(ic.itho_female_items, Name)
			createItemsInList(gen.itho_female_items, Name)
		end
	elseif Species == "wookiee" then
		if Sex == "male" then
			createItemsInList(ic.wook_male_items, Name)
			createItemsInList(gen.wook_male_items, Name)
		else
			createItemsInList(ic.wook_female_items, Name)
			createItemsInList(gen.wook_female_items, Name)
		end
	elseif Species == "trandoshan" then
		if Sex == "male" then
			createItemsInList(ic.tran_male_items, Name)
			createItemsInList(gen.tran_male_items, Name)
		else
			createItemsInList(ic.tran_female_items, Name)
			createItemsInList(gen.tran_female_items, Name)
		end
	else
		if Sex == "male" then
			createItemsInList(ic.humanoid_male_items, Name)
			createItemsInList(gen.humanoid_male_items, Name)
		else
			createItemsInList(ic.humanoid_female_items, Name)
			createItemsInList(gen.humanoid_female_items, Name)
		end
	end
end

function createItemsInList(List, Name)
	for element in list_iter(List) do
		element.owner = Name
		AddPlayerItem(element)
	end
end

function list_iter (t)
      local i = 0
      local n = table.getn(t)
      return function ()
               i = i + 1
               if i <= n then return t[i] end
             end
end

RunProfessionFile("marksman.lua");
RunProfessionFile("brawler.lua");
RunProfessionFile("medic.lua");
RunProfessionFile("scout.lua");
RunProfessionFile("artisan.lua");
RunProfessionFile("entertainer.lua");
RunProfessionFile("general.lua");