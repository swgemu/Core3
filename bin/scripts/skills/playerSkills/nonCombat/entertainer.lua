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


-- Core Commands

imagedesignSkill = {
	skillname = "imagedesign",
        invalidStateMask = 3894542336, --frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
--AddEntertainSkill(imagedesignSkill)

startdanceSkill = {
	skillname = "startdance",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceSkill)

startmusicSkill = {
	skillname = "startmusic",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicSkill)

stopdanceSkill = {
	skillname = "stopdance",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(stopdanceSkill)

stopmusicSkill = {
	skillname = "stopmusic",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(stopmusicSkill)
-- Effects

spotlightSkill = {
	skillname = "spotlight",
	effect_prefix = "clienteffect/entertainer_spot_light_level_",
        invalidStateMask = 3894934635, --cover, combat, aiming, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainEffectSkill(spotlightSkill)

dazzleSkill = {
	skillname = "dazzle",
	effect_prefix = "clienteffect/entertainer_dazzle_level_",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainEffectSkill(dazzleSkill)


colorlightsSkill = {
	skillname = "colorlights",
	effect_prefix = "clienteffect/entertainer_color_lights_level_",
        invalidStateMask = 3894934635, --cover, combat, aiming, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainEffectSkill(colorlightsSkill)

-- Flourishes

bandflourishSkill = {
	skillname = "bandflourish",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddBandFlourishSkill(bandflourishSkill) 

flourishSkill = {
	skillname = "flourish",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourishSkill)

flourish1Skill = {
	skillname = "flourish+1",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish1Skill)

flourish2Skill = {
	skillname = "flourish+2",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish2Skill)

flourish3Skill = {
	skillname = "flourish+3",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish3Skill)

flourish4Skill = {
	skillname = "flourish+4",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish4Skill)

flourish5Skill = {
	skillname = "flourish+5",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish5Skill)

flourish6Skill = {
	skillname = "flourish+6",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish6Skill)

flourish7Skill = {
	skillname = "flourish+7",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish7Skill)

flourish8Skill = {
	skillname = "flourish+8",
        invalidStateMask = 3760193552, --alert, glowingJedi, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "",
	instant = 0
}
AddEntertainSkill(flourish8Skill)


-- Dances

startdanceBasicSkill = {
	skillname = "startdance+basic",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceBasicSkill)

startdanceRhythmicSkill = {
	skillname = "startdance+rhythmic",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceRhythmicSkill)

startdanceBasic2Skill = {
	skillname = "startdance+basic2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceBasic2Skill)

startdanceRhythmic2Skill = {
	skillname = "startdance+rhythmic2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceRhythmic2Skill)

startdanceFootlooseSkill = {
	skillname = "startdance+footloose",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceFootlooseSkill)

startdanceFormalSkill = {
	skillname = "startdance+formal",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceFormalSkill)

startdanceFootloose2Skill = {
	skillname = "startdance+footloose2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceFootloose2Skill)

startdanceFormal2Skill = {
	skillname = "startdance+formal2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceFormal2Skill)

startdancePopularSkill = {
	skillname = "startdance+popular",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdancePopularSkill)

startdancePoplockSkill = {
	skillname = "startdance+poplock",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdancePoplockSkill)

startdancePopular2Skill = {
	skillname = "startdance+popular2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdancePopular2Skill)

startdancePoplock2Skill = {
	skillname = "startdance+poplock2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdancePoplock2Skill)

startdanceLyricalSkill = {
	skillname = "startdance+lyrical",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceLyricalSkill)

startdanceBreakdanceSkill = {
	skillname = "startdance+breakdance",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceBreakdanceSkill)

startdanceBreakdance2Skill = {
	skillname = "startdance+breakdance2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceBreakdance2Skill)

startdanceExoticSkill = {
	skillname = "startdance+exotic",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceExoticSkill)

startdanceExotic2Skill = {
	skillname = "startdance+exotic2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceExotic2Skill)

startdanceLyrical2Skill = {
	skillname = "startdance+lyrical2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceLyrical2Skill)

startdanceExotic3Skill = {
	skillname = "startdance+exotic3",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceExotic3Skill)

startdanceExotic4Skill = {
	skillname = "startdance+exotic4",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceExotic4Skill)

startdanceTheatricalSkill = {
	skillname = "startdance+theatrical",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceTheatricalSkill)

startdanceTheatrical2Skill = {
	skillname = "startdance+theatrical2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceTheatrical2Skill)

startdanceTumbleSkill = {
    skillname = "startdance+tumble",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceTumbleSkill)

startdanceTumble2Skill = {
    skillname = "startdance+tumble2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startdanceTumble2Skill)

-- Music Songs

startmusicStarwars1Skill = {
	skillname = "startmusic+starwars1",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicStarwars1Skill)

startmusicRockSkill = {
	skillname = "startmusic+rock",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicRockSkill)

startmusicStarwars2Skill = {
	skillname = "startmusic+starwars2",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicStarwars2Skill)

startmusicFolkSkill = {
	skillname = "startmusic+folk",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicFolkSkill)

startmusicStarwars3Skill = {
	skillname = "startmusic+starwars3",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicStarwars3Skill)

startmusicCeremonialSkill = {
	skillname = "startmusic+ceremonial",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicCeremonialSkill)

startmusicStarwars4Skill = {
	skillname = "startmusic+starwars4",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicStarwars4Skill)

startmusicBalladSkill = {
	skillname = "startmusic+ballad",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicBalladSkill)

startmusicFunkSkill = {
	skillname = "startmusic+funk",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicFunkSkill)

startmusicWaltzSkill = {
	skillname = "startmusic+waltz",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicWaltzSkill)

startmusicJazzSkill = {
	skillname = "startmusic+jazz",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicJazzSkill)

startmusicVirtuosoSkill = {
	skillname = "startmusic+virtuoso",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicVirtuosoSkill)

startmusicWesternSkill = {
	skillname = "startmusic+western",
        invalidStateMask = 3894934651, --cover, combat, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
AddEntertainSkill(startmusicWesternSkill)

