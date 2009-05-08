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
HealSelfSkill = {
	skillname = "healdamage",
	effect = "clienteffect/healing_healdamage.cef",
	animation = "heal_self",
 
	mindCost = -50,
	range = 6.0,

        invalidStateMask = 3894805544, --aiming, berzerk, tumbling, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,5,6,9,10,11,13,14,",
	instant = 0
}
 
AddHealDamageTargetSkill(HealSelfSkill);
 
HealSelfSkill = {
	skillname = "healwound",
	effect = "clienteffect/healing_healwound.cef",
	animation = "heal_self",
 
	mindCost = -50,
	range = 6.0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddHealWoundTargetSkill(HealSelfSkill);
 
FirstAidSkill = {
	skillname = "firstaid",
	effect = "clienteffect/healing_healdamage.cef",
	animation = "heal_self",
 
	speed = 5.0,
	range = 6.0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddFirstAidTargetSkill(FirstAidSkill);
 
TendDamageSkill = {
	skillname = "tenddamage",
	effect = "clienteffect/healing_healdamage.cef",
	animation = "heal_self",
 
	mindCost = 30,
	mindWoundCost = 5,
 
	healthHealed = 50,
	actionHealed = 50,
 
	tendDamage = 1,
 
	speed = 5.0,
	range = 6.0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddTendHealTargetSkill(TendDamageSkill);
 
QuickHealSkill = {
	skillname = "quickheal",
	effect = "clienteffect/healing_healdamage.cef",
	animation = "heal_self",
 
	mindCost = 175,
	mindWoundCost = 10,
 
	speed = 3.5,
	range = 6.0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddQuickHealTargetSkill(QuickHealSkill);

TendWoundSkill = {
	skillname = "tendwound",
	effect = "clienteffect/healing_healwound.cef",
	animation = "heal_self",
 
	mindCost = 30,
	mindWoundCost = 10,
 
	woundPool = 1,
	woundHealed = 25,
 
	tendWound = 1,
 
	speed = 5.0,
	range = 6.0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddTendHealTargetSkill(TendWoundSkill);
 
DiagnoseTargetSkill = {
	skillname = "diagnose",
	effect = "clienteffect/healing_healenhance.cef",
	animation = "heal_self",
 
	mindCost = 0,
	range = 6.0,
	speed = 0,

        invalidStateMask = 3894542352, --alert, frozen, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "2,5,7,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddDiagnoseTargetSkill(DiagnoseTargetSkill);

DragTargetSkill = {
	skillname = "dragincapacitatedplayer",
	effect = "",
	maxRange = 20.0,
	maxMovement = 5.0,
	speed = 0.0,
	needsConsent = 1,

        invalidStateMask = 3894934649, --cover, aiming, alert, berzerk, feigndeath, tumbling, rallied, stunned, blinded, dizzy, intimidated, immobilized, frozen, swimming, glowingJedi, ridingMount, pilotingShip, shipOperations, shipGunner, 
        invalidPostures = "3,1,2,5,6,7,8,9,10,11,12,13,14,4,",
	instant = 0
}
 
AddDragTargetSkill(DragTargetSkill);
