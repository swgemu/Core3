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

-- utils
-- creatures lua files
RunCreatureFile("objects/object.lua") -- basic object
RunCreatureFile("objects/creature.lua") -- Creature Object

local sin, cos = math.sin, math.cos
local deg, rad = math.deg, math.rad
math.sin = function (x) return sin(rad(x)) end
math.cos = function (x) return cos(rad(x)) end

-- Global creature table
Creatures = { }

function Creatures:addCreature(obj, crc)
	self[crc] = obj
end

function getCreature(crc)
	return Creatures[crc]
end

-- Standard Creature Spawning
function spawnCreature(creature, Planet, PositionX, PositionY)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionY = PositionY }
	AddCreatureToServer(newCreature)
end

-- Spawning with Respawn Time
function spawnCreature(creature, Planet, PositionX, PositionY, respawnTime)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionY = PositionY, respawnTimer = respawnTime }
	AddCreatureToServer(newCreature)
end

-- Spawning With Direction
function spawnCreature(creature, Planet, PositionX, PositionY, DirectionX, DirectionZ, DirectionY, DirectionW)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionY = PositionY, directionX = DirectionX, directionZ = DirectionZ, directionY = DirectionY, directionW = DirectionW }
	AddCreatureToServer(newCreature)
end

-- Spawning Inside Cells
function spawnCreatureInCell(creature, Planet, PositionX, PositionZ, PositionY, cellid)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionZ = PositionZ, positionY = PositionY, cellID = cellid }
	AddCreatureToServer(newCreature)
end

-- Spawning Inside Cells With Direction
function spawnCreatureInCell(creature, Planet, PositionX, PositionZ, PositionY, DirectionX, DirectionZ, DirectionY, DirectionW, cellid)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionZ = PositionZ, positionY = PositionY, directionX = DirectionX, directionZ = DirectionZ, directionY = DirectionY, directionW = DirectionW, cellID = cellid }
	AddCreatureToServer(newCreature)
end

function spawnBlueFrog(x, y, oy, ow, bftype, cellid)
	bluefrog = { X = x, Y = y, oY = oy, oW = ow, bfType = bftype, cellId = cellid }
	AddBlueFrogToServer(bluefrog)
end

-- Spawning Mutiple Creatures with Radius
function spawnCreatures(creature, Planet, PositionX, PositionY, radius, number)
	for i=1,number do
		angle = math.random(359)
		dist = math.random(radius)
	
		x = math.cos(angle) * dist + PositionX
		y = math.sin(angle) * dist + PositionY
		
		spawnCreature(creature, Planet, x, y)
	end	
end

-- Spawning Mutiple Creatures with Radius and Respawn time
function spawnCreatures(creature, Planet, PositionX, PositionY, radius, number, respawnTime)
	for i=1,number do
		angle = math.random(359)
		dist = math.random(radius)
	
		x = math.cos(angle) * dist + PositionX
		y = math.sin(angle) * dist + PositionY
		
		spawnCreature(creature, Planet, x, y, respawnTime)
	end	
end

-- Creature objects
RunCreatureFile("creatureObjects.lua")

-- Spawns
RunCreatureFile("spawns.lua")
