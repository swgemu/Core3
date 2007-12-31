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
RunCreatureFile("objects/lair.lua") -- Lair Object

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

function spawnCreature(creature, Planet, PositionX, PositionY)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionY = PositionY }
	AddCreatureToServer(newCreature)
end

function spawnCreature(creature, Planet, PositionX, PositionY, respawnTime)
	newCreature = creature:new { planet = Planet, positionX = PositionX, positionY = PositionY, respawnTimer = respawnTime }
	AddCreatureToServer(newCreature)
end

function spawnCreatures(creature, Planet, PositionX, PositionY, radius, number)
	for i=1,number do
		angle = math.random(359)
		dist = math.random(radius)
	
		x = math.cos(angle) * dist + PositionX
		y = math.sin(angle) * dist + PositionY
		
		spawnCreature(creature, Planet, x, y)
	end	
end

function spawnCreatures(creature, Planet, PositionX, PositionY, radius, number, respawnTime)
	for i=0,number do
		angle = math.random(359)
		dist = math.random(radius)
	
		x = math.cos(angle) * dist + PositionX
		y = math.sin(angle) * dist + PositionY
		
		spawnCreature(creature, Planet, x, y, respawnTime)
	end	
end

function spawnLair(creatures, lair, posX, posY, posZ)
end

-- Creature objects
RunCreatureFile("objects/creatures/canyonKraytDragon.lua")
RunCreatureFile("objects/creatures/darthVader.lua")
RunCreatureFile("objects/creatures/wompRat.lua")
RunCreatureFile("objects/creatures/scyk.lua")
RunCreatureFile("objects/creatures/worrt.lua")
RunCreatureFile("objects/creatures/rill.lua")
RunCreatureFile("objects/creatures/juviCanyonKraytDragon.lua")
RunCreatureFile("objects/creatures/derangedSquill.lua")
RunCreatureFile("objects/creatures/squill.lua")
RunCreatureFile("objects/creatures/dewback.lua")

RunCreatureFile("objects/creatures/nightsisterElder.lua")
RunCreatureFile("objects/creatures/nightsisterProtector.lua")
RunCreatureFile("objects/creatures/nightsisterSpellweaver.lua")
RunCreatureFile("objects/creatures/nightsisterSentinel.lua")
RunCreatureFile("objects/creatures/nightsisterStalker.lua")
RunCreatureFile("objects/creatures/nightsisterOutcast.lua")
RunCreatureFile("objects/creatures/nightsisterRanger.lua")
RunCreatureFile("objects/creatures/nightsisterRancorTamer.lua")
RunCreatureFile("objects/creatures/nightsisterSentry.lua")
RunCreatureFile("objects/creatures/nightsisterInitiate.lua")

RunCreatureFile("objects/creatures/singingMountainClanSlave.lua")
RunCreatureFile("objects/creatures/singingMountainClanRancorTamer.lua")
RunCreatureFile("objects/creatures/singingMountainClanArchWitch.lua")
RunCreatureFile("objects/creatures/singingMountainClanHuntress.lua")
RunCreatureFile("objects/creatures/singingMountainClanScout.lua")
RunCreatureFile("objects/creatures/singingMountainClanInitiate.lua")
RunCreatureFile("objects/creatures/singingMountainClanSentry.lua")
RunCreatureFile("objects/creatures/singingMountainClanCouncilwoman.lua")
RunCreatureFile("objects/creatures/singingMountainClanWitch.lua")
RunCreatureFile("objects/creatures/singingMountainClanGuardian.lua")

RunCreatureFile("objects/creatures/bazNitch.lua")
RunCreatureFile("objects/creatures/kwi.lua")
RunCreatureFile("objects/creatures/reptilianFlier.lua")
RunCreatureFile("objects/creatures/malkloc.lua")
RunCreatureFile("objects/creatures/purbole.lua")
RunCreatureFile("objects/creatures/verne.lua")
RunCreatureFile("objects/creatures/bullRancor.lua")
RunCreatureFile("objects/creatures/mutantRancor.lua")
RunCreatureFile("objects/creatures/rancor.lua")
RunCreatureFile("objects/creatures/gapingSpider.lua")
RunCreatureFile("objects/creatures/gapingSpiderRecluse.lua")

RunCreatureFile("objects/creatures/bageraset.lua")
RunCreatureFile("objects/creatures/carrionSpat.lua")
RunCreatureFile("objects/creatures/corellianButterfly.lua")
RunCreatureFile("objects/creatures/dalyrake.lua")
RunCreatureFile("objects/creatures/direCat.lua")
RunCreatureFile("objects/creatures/durni.lua")
RunCreatureFile("objects/creatures/gronda.lua")
RunCreatureFile("objects/creatures/gubbur.lua")
RunCreatureFile("objects/creatures/gulginaw.lua")
RunCreatureFile("objects/creatures/gurrcat.lua")
RunCreatureFile("objects/creatures/humbaba.lua")
RunCreatureFile("objects/creatures/lordNyax.lua")
RunCreatureFile("objects/creatures/nyaxThug.lua")
RunCreatureFile("objects/creatures/murra.lua")
RunCreatureFile("objects/creatures/paralope.lua")
RunCreatureFile("objects/creatures/plumedRasp.lua")
RunCreatureFile("objects/creatures/sharnaff.lua")
RunCreatureFile("objects/creatures/sliceHound.lua")

RunCreatureFile("objects/creatures/stormTrooper.lua")
RunCreatureFile("objects/creatures/atSt.lua")
RunCreatureFile("objects/creatures/atAt.lua")
RunCreatureFile("objects/creatures/superBattleDroid.lua")

RunCreatureFile("objects/creatures/rebelGeneral.lua")
RunCreatureFile("objects/creatures/rebelSurfaceMarshal.lua")

-- Spawns
RunCreatureFile("tatooine/staticSpawns.lua")
RunCreatureFile("dathomir/staticSpawns.lua")
RunCreatureFile("corellia/staticSpawns.lua")
