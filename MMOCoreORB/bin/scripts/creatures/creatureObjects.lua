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

--Corellia
if (PLANET_ID == 0) then
RunCreatureFile("objects/corellia/creatures.lua") 
RunCreatureFile("objects/corellia/npcs.lua") 
end

----------------------------------------------------

--Dantooine
if (PLANET_ID == 1) then
RunCreatureFile("objects/dantooine/creatures.lua") 
RunCreatureFile("objects/dantooine/npcs.lua")
end

-------------------------------------------------------

--Dathomir
if (PLANET_ID == 2) then
RunCreatureFile("objects/dathomir/creatures.lua") 
RunCreatureFile("objects/dathomir/npcs.lua")
end
-------------------------------------------------------------

--Endor
if (PLANET_ID == 3) then
RunCreatureFile("objects/endor/creatures.lua") 
RunCreatureFile("objects/endor/npcs.lua")
end

--------------------------------------------------------------

-- Rori
if (PLANET_ID == 4) then
RunCreatureFile("objects/rori/creatures.lua") 
RunCreatureFile("objects/rori/npcs.lua")
end

---------------------------------------------------------------

-- Naboo
if (PLANET_ID == 5) then
RunCreatureFile("objects/naboo/creatures.lua") 
RunCreatureFile("objects/naboo/npcs.lua") 
end

--------------------------------------------------------------------

-- Rori
if (PLANET_ID == 6) then
RunCreatureFile("objects/rori/creatures.lua") 
RunCreatureFile("objects/rori/npcs.lua") 
end

--------------------------------------------------------------------

-- Talus
if (PLANET_ID == 7) then
RunCreatureFile("objects/talus/creatures.lua") 
RunCreatureFile("objects/talus/npcs.lua") 
end

--------------------------------------------------------------------

--Tatooine
if (PLANET_ID == 8) then
RunCreatureFile("objects/tatooine/creatures.lua") 
RunCreatureFile("objects/tatooine/npcs.lua")
end
--------------------------------------------------------



-- yavin 4
if (PLANET_ID == 9) then
RunCreatureFile("objects/yavin4/creatures.lua") 
RunCreatureFile("objects/yavin4/npcs.lua")
end

--------------------------------------------------------------------

--Faction Spawns (All Planets) 

--Imperial
RunCreatureFile("objects/npcs/atSt.lua")
RunCreatureFile("objects/npcs/atAt.lua")

RunCreatureFile("objects/npcs/darkTrooper.lua")
RunCreatureFile("objects/npcs/imperialColonel.lua")
RunCreatureFile("objects/npcs/imperialMajor.lua")
RunCreatureFile("objects/npcs/imperialMajorGeneral.lua")
RunCreatureFile("objects/npcs/imperialSurfaceMarshal.lua")
RunCreatureFile("objects/npcs/stormTrooper.lua")

--Rebel
RunCreatureFile("objects/npcs/rebelGeneral.lua")
RunCreatureFile("objects/npcs/rebelSurfaceMarshal.lua")

--Misc
RunCreatureFile("objects/npcs/palpatine.lua")
RunCreatureFile("objects/npcs/darthVader.lua")
RunCreatureFile("objects/npcs/mellichae.lua")
RunCreatureFile("objects/npcs/moJediMaster.lua")
RunCreatureFile("objects/npcs/jediMaster.lua")
RunCreatureFile("objects/npcs/jediKnight.lua")

RunCreatureFile("objects/npcs/oldMan.lua")
RunCreatureFile("objects/npcs/luke.lua")
RunCreatureFile("objects/npcs/hanSolo.lua")
RunCreatureFile("objects/npcs/chewbacca.lua")
RunCreatureFile("objects/npcs/bobaFett.lua")
RunCreatureFile("objects/npcs/jabbaHutt.lua")

----------------------------------------------------------------------------------------------------
