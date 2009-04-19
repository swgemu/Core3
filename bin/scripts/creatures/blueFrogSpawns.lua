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

-------------------------------------------------------------------------------------------
--Tatooine
if (PLANET_ID == 8) then
 spawnBlueFrog(45, -5352, -.11083, .993839, JAWA, 0);
 spawnBlueFrog(59, -5336, 1, 0, JAWA, 0);
 spawnBlueFrog(119, -5354, .723221, -.690617, JAWA, 0);
 spawnBlueFrog(-87, -5332, -.0339502, .999424, JAWA, 0);
end

--Naboo
if (PLANET_ID == 5) then
 spawnBlueFrog(-4834, 4148, .723221, -.690617, GUNGAN, 0);
 spawnBlueFrog(-4879, 4185, 1, 0, GUNGAN, 0);
 spawnBlueFrog(17.6233, 11.2728, 1, 0, GUNGAN, 1697360);
 spawnBlueFrog(2.2, -2.5, 1, 0, BARTENDER, 91);
 spawnBlueFrog(-4933, 4234, 1, .1, GUNGAN, 0);
end

--Endor
if (PLANET_ID == 3) then
 spawnBlueFrog(3221, -3451, .99154, 0.04113, EWOK, 0);
end

--Corellia
if (PLANET_ID == 0) then
 spawnBlueFrog(39.7053, 2.76636, 0.908367, 0.418174, BARTENDER, 8105494);
 spawnBlueFrog(-136.522, -4729.71, .707743, -0.70647, BARTENDER, 0);
end

