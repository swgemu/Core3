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
 RunCreatureFile("spawns/corellia/staticSpawns.lua")
 RunCreatureFile("spawns/corellia/afarathuCave.lua")
 RunCreatureFile("spawns/corellia/drallCave.lua")
 RunCreatureFile("spawns/corellia/lordNyaxCult.lua")
 RunCreatureFile("spawns/corellia/rogueCorsec.lua")
end

--Dantooine
if (PLANET_ID == 1) then
 RunCreatureFile("spawns/dantooine/staticSpawns.lua")
 RunCreatureFile("spawns/dantooine/forceCrystalHuntersCave.lua")
 RunCreatureFile("spawns/dantooine/jantaCave.lua")
 RunCreatureFile("spawns/dantooine/kungaCave.lua")
 RunCreatureFile("spawns/dantooine/MokkCave.lua")
end

--Dathomir
if (PLANET_ID == 2) then
 RunCreatureFile("spawns/dathomir/staticSpawns.lua")
 RunCreatureFile("spawns/dathomir/nightsisters.lua")
 RunCreatureFile("spawns/dathomir/singingmtnclan.lua")
 RunCreatureFile("spawns/dathomir/rancorCave.lua")
 RunCreatureFile("spawns/dathomir/nightsisterCave.lua")
end


--Endor
if (PLANET_ID == 3) then
RunCreatureFile("spawns/endor/staticSpawns.lua")
RunCreatureFile("spawns/endor/jindaCave.lua")
RunCreatureFile("spawns/endor/korgaCave.lua")
RunCreatureFile("spawns/endor/marauderStronghold.lua")
-- RunCreatureFile("spawns/endor/deathWatchBunker.lua")
end

--Lok
if (PLANET_ID == 4) then
end

--Naboo
if (PLANET_ID == 5) then
 RunCreatureFile("spawns/naboo/staticSpawns.lua")
end

--Rori
if (PLANET_ID == 6) then
end

--Talus
if (PLANET_ID == 7) then
end

--Tatooine
if (PLANET_ID == 8) then
 RunCreatureFile("spawns/tatooine/staticSpawns.lua")
 RunCreatureFile("spawns/tatooine/forttusken.lua")
 RunCreatureFile("spawns/tatooine/squillcavern.lua")
 RunCreatureFile("spawns/tatooine/hutthideout.lua")
 RunCreatureFile("spawns/tatooine/tuskenBunker.lua")
 RunCreatureFile("spawns/tatooine/beetlecave.lua")
end

--Yavin 4
if (PLANET_ID == 9) then
RunCreatureFile("spawns/yavin4/staticSpawns.lua")
end
