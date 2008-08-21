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

-----------------------------------------------------------------------------------------------------------------------

--Tatooine
if (PLANET_ID == 8) then
 RunCreatureFile("objects/tatooine/creatures/kraytDragonAncient.lua")
 RunCreatureFile("objects/tatooine/creatures/canyonKraytDragon.lua")
 RunCreatureFile("objects/tatooine/creatures/wompRat.lua")
 RunCreatureFile("objects/tatooine/creatures/scyk.lua")
 RunCreatureFile("objects/tatooine/creatures/worrt.lua")
 RunCreatureFile("objects/tatooine/creatures/rill.lua")
 RunCreatureFile("objects/tatooine/creatures/juvenileCanyonKrayt.lua")
 -- RunCreatureFile("objects/tatooine/creatures/derangedSquill.lua")
 RunCreatureFile("objects/tatooine/creatures/squill.lua")
 RunCreatureFile("objects/tatooine/creatures/dewback.lua")

 --Fort Tusken / Tusken Bunker
 RunCreatureFile("objects/tatooine/npcs/tuskenCaptain.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenEliteGuard.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenExecutioner.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenKing.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenObserver.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenRaider.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenSniper.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenWarlord.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenWarMaster.lua")
 RunCreatureFile("objects/tatooine/npcs/tuskenWitchDoctor.lua") 

 --Squill Cave
 RunCreatureFile("objects/tatooine/creatures/malignantSquill.lua")
 RunCreatureFile("objects/tatooine/creatures/femaleMountainSquill.lua")
 RunCreatureFile("objects/tatooine/creatures/youngMountainSquill.lua")
 RunCreatureFile("objects/tatooine/creatures/mountainSquillGuardian.lua")

 --Hutt Hideout
 RunCreatureFile("objects/tatooine/npcs/jabbaEnforcer.lua")
 RunCreatureFile("objects/tatooine/npcs/jabbasSwooper.lua")
 RunCreatureFile("objects/tatooine/npcs/jabbaCompoundGuard.lua") 


 --Sennex Cave
 RunCreatureFile("objects/tatooine/npcs/sennexHunter.lua")
 RunCreatureFile("objects/tatooine/npcs/sennexSlavemaster.lua")
 RunCreatureFile("objects/tatooine/npcs/sennexLookout.lua")
 RunCreatureFile("objects/tatooine/npcs/sennexSlaver.lua")
 RunCreatureFile("objects/tatooine/npcs/sennexGuard.lua")
 RunCreatureFile("objects/tatooine/npcs/sennexWarder.lua")
 RunCreatureFile("objects/tatooine/creatures/caveBeetle.lua")
 RunCreatureFile("objects/tatooine/creatures/duneBeetle.lua")
end
--------------------------------------------------------

--Dathomir
if (PLANET_ID == 2) then
 RunCreatureFile("objects/dathomir/npcs/nightsisterElder.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterInitiate.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterOutcast.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterProtector.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterRancorTamer.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterRanger.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterSentinal.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterSentry.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterSpellWeaver.lua")
 RunCreatureFile("objects/dathomir/npcs/nightsisterStalker.lua")

 RunCreatureFile("objects/dathomir/npcs/singingMountainClanSentry.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanArchWitch.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanCouncilwoman.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanGuardian.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanHuntress.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanInitiate.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanOutcast.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanRancorTamer.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanScout.lua")
 RunCreatureFile("objects/dathomir/npcs/singingMtnClanSlave.lua")

 RunCreatureFile("objects/dathomir/creatures/bazNitch.lua")
 RunCreatureFile("objects/dathomir/creatures/kwi.lua")
 RunCreatureFile("objects/dathomir/creatures/reptilianFlier.lua")
 RunCreatureFile("objects/dathomir/creatures/malkloc.lua")
 RunCreatureFile("objects/dathomir/creatures/purbole.lua")
 RunCreatureFile("objects/dathomir/creatures/verne.lua")
 RunCreatureFile("objects/dathomir/creatures/bullRancor.lua")
 RunCreatureFile("objects/dathomir/creatures/mutantRancor.lua")
 RunCreatureFile("objects/dathomir/creatures/rancor.lua")
 RunCreatureFile("objects/dathomir/creatures/gapingSpider.lua")
 RunCreatureFile("objects/dathomir/creatures/gapingSpiderRecluse.lua")
end
-------------------------------------------------------------

--Corellia
if (PLANET_ID == 0) then
 RunCreatureFile("objects/corellia/creatures/bageraset.lua")
 RunCreatureFile("objects/corellia/creatures/carrionSpat.lua")
 RunCreatureFile("objects/corellia/creatures/corellianButterfly.lua")
 RunCreatureFile("objects/corellia/creatures/dalyrake.lua")
 RunCreatureFile("objects/corellia/creatures/direCat.lua")
 RunCreatureFile("objects/corellia/creatures/durni.lua")
 RunCreatureFile("objects/corellia/creatures/gronda.lua")
 RunCreatureFile("objects/corellia/creatures/gubbur.lua")
 RunCreatureFile("objects/corellia/creatures/gulginaw.lua")
 RunCreatureFile("objects/corellia/creatures/gurrcat.lua")
 RunCreatureFile("objects/corellia/creatures/humbaba.lua")
 RunCreatureFile("objects/corellia/creatures/murra.lua")
 RunCreatureFile("objects/corellia/creatures/paralope.lua")
 RunCreatureFile("objects/corellia/creatures/plumedRasp.lua")
 RunCreatureFile("objects/corellia/creatures/sharnaff.lua")
 RunCreatureFile("objects/corellia/creatures/sliceHound.lua")

 RunCreatureFile("objects/corellia/npcs/afarathuCultBrute.lua")
 RunCreatureFile("objects/corellia/npcs/afarathuCultFollower.lua")
 RunCreatureFile("objects/corellia/npcs/afarathuCultLeader.lua")
 RunCreatureFile("objects/corellia/npcs/afarathuCultRuffian.lua")
 RunCreatureFile("objects/corellia/npcs/afarathuCultSavage.lua")

 RunCreatureFile("objects/corellia/npcs/drallAbbot.lua")
 RunCreatureFile("objects/corellia/npcs/drallChieftain.lua")
 RunCreatureFile("objects/corellia/npcs/drallPatriotConqueror.lua")
 RunCreatureFile("objects/corellia/npcs/drallPatriotFootsoldier.lua")
 RunCreatureFile("objects/corellia/npcs/drallPatriotLegionnare.lua")

 RunCreatureFile("objects/corellia/npcs/lordNyax.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxDisciple.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxFanatic.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxFiend.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxMinion.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxServant.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxVisionary.lua")
 RunCreatureFile("objects/corellia/npcs/lordNyaxZealot.lua")

 RunCreatureFile("objects/corellia/npcs/corsecComissioner1.lua")
 RunCreatureFile("objects/corellia/npcs/corsecComissioner.lua")
 RunCreatureFile("objects/corellia/npcs/corsecDeserter.lua")
 RunCreatureFile("objects/corellia/npcs/corsecRogue.lua")
 RunCreatureFile("objects/corellia/npcs/corsecTraitor.lua")
 RunCreatureFile("objects/corellia/npcs/corsecTrooper1.lua")
 RunCreatureFile("objects/corellia/npcs/corsecTrooper.lua")
end

----------------------------------------------------

--Faction Spawns (All Planets)
 
--Imperial
--RunCreatureFile("objects/npcs/atSt.lua")
--RunCreatureFile("objects/npcs/atAt.lua")
RunCreatureFile("objects/npcs/darkTrooper.lua")
RunCreatureFile("objects/npcs/darthVader.lua")
RunCreatureFile("objects/npcs/imperialColonel.lua")
RunCreatureFile("objects/npcs/imperialMajor.lua")
RunCreatureFile("objects/npcs/imperialMajorGeneral.lua")
RunCreatureFile("objects/npcs/imperialSurfaceMarshal.lua")
RunCreatureFile("objects/npcs/darthVader.lua")
RunCreatureFile("objects/npcs/stormTrooper.lua")

--Rebel
RunCreatureFile("objects/npcs/rebelGeneral.lua")
RunCreatureFile("objects/npcs/rebelSurfaceMarshal.lua")

----------------------------------------------------------------------------------------------------

--Dantooine
if (PLANET_ID == 1) then
 --Force Crystal Cave Mob
 RunCreatureFile("objects/dantooine/npcs/darkForceCrystalHunter.lua") 
 RunCreatureFile("objects/dantooine/npcs/untrainedWielderOfTheDarkSide.lua")

 --Jantas
 RunCreatureFile("objects/dantooine/npcs/jantaClanLeader.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaHarvester.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaHerbalist.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaHunter.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaLoreweaver.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaPrimalist.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaRockshaper.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaScout.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaShaman.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaSoothsayer.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaTribesman.lua")
 RunCreatureFile("objects/dantooine/npcs/jantaWarrior.lua")

 --Kungas
 RunCreatureFile("objects/dantooine/npcs/kungaClanLeader.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaHarvester.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaHerbalist.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaHunter.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaLoreweaver.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaRockshaper.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaScout.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaShaman.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaSoothsayer.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaTribesman.lua")
 RunCreatureFile("objects/dantooine/npcs/kungaWarrior.lua")
end
-------------------------------------------------------------------------------------------------------------------------------------

--Endor
-- Death Watch Bunker
-- RunCreatureFile("objects/endor/npcs/battleDroidDWB.lua")
-- RunCreatureFile("objects/endor/npcs/blackSunThugDWB.lua")
-- RunCreatureFile("objects/endor/npcs/blackSunHenchmanDWB.lua")
-- RunCreatureFile("objects/endor/npcs/blackSunAssassinDWB.lua")
-- RunCreatureFile("objects/endor/npcs/deathWatchGhostDWB.lua")
-- RunCreatureFile("objects/endor/npcs/deathWatchBloodguardDWB.lua")
-- RunCreatureFile("objects/endor/npcs/deathWatchWraithDWB.lua")
-- RunCreatureFile("objects/endor/npcs/superBattleDroidDWB.lua")
-- RunCreatureFile("objects/endor/npcs/mineRatDWB.lua")
-- RunCreatureFile("objects/endor/npcs/technicianDWB.lua")
-- RunCreatureFile("objects/endor/npcs/minerDWB.lua")
-- RunCreatureFile("objects/endor/npcs/engineerDWB.lua")
-- RunCreatureFile("objects/endor/npcs/deathWatchOverlordDWB.lua")
-- RunCreatureFile("objects/endor/npcs/twilekSlave.lua")

------------------------------------------------------------------------------------------------------------------------------

-- Naboo
if (PLANET_ID == 5) then
 RunCreatureFile("objects/npcs/naboostormTrooper.lua")
 RunCreatureFile("objects/endor/creatures/gorax.lua")
 RunCreatureFile("objects/naboo/creatures/capperSpineflap.lua")
 RunCreatureFile("objects/naboo/creatures/diseasedNuna.lua")
 RunCreatureFile("objects/naboo/creatures/fleshEatingChuba.lua")
 RunCreatureFile("objects/naboo/creatures/nightspider.lua")
 RunCreatureFile("objects/naboo/creatures/shaupaut.lua")
end
-- Event

