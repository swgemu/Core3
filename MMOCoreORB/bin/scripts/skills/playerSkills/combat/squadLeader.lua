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

------------------------------------------------------------------------
SystemGroupMessageSkill = {
	skillname = "serversysgroup"	
}

AddSystemGroupMessageSkill(SystemGroupMessageSkill);
------------------------------------------------------------------------

------------------------------------------------------------------------
BoostMoraleGroupSkill = {
	skillname = "boostmorale",
	combatspam = "boostmorale_buff",
	cooldowntime = 120,
	healthcost = 100,
	actioncost = 100,
	mindcost = 100
}

AddBoostMoraleGroupSkill(BoostMoraleGroupSkill);
------------------------------------------------------------------------

------------------------------------------------------------------------
VolleyFireGroupSkill = {
	skillname = "volleyfire",
	
	combatspam = "volley_success_single",
	
	defaultattack = "attack",
	
	cooldowntime = 30,
	healthcost = 100,
	actioncost = 100,
	mindcost = 50
}

AddVolleyFireGroupSkill(VolleyFireGroupSkill);
------------------------------------------------------------------------

------------------------------------------------------------------------
FormupGroupSkill = {
	skillname = "formup",
	combatspam = "formup_buff",
	cooldowntime = 5,
	healthcost = 50,
	actioncost = 50,
	mindcost = 50,
	healdizzychance = 25, -- a value of 50 means a 50% chance to heal, 100 = 100%, 0 = 0%
	healstunchance = 25,
	healblindchance = 25,
	healintimidatechance = 25,
}

AddFormupGroupSkill(FormupGroupSkill);
------------------------------------------------------------------------

------------------------------------------------------------------------
RallyGroupSkill = {
	skillname = "rally",
	combatspam = "rally_success_group_msg",
	cooldowntime = 70,
	healthcost = 100,
	actioncost = 200,
	mindcost = 100,
	rallyduration = 45,
	accuracybonus = 15
}

AddRallyGroupSkill(RallyGroupSkill);
------------------------------------------------------------------------
------------------------------------------------------------------------
RetreatSkill = {
	skillname = "retreat",
	combatspam = "retreat_buff",
	cooldowntime = 30,

	healthcost = 0,
	actioncost = 600,                 
	mindcost = 600,   

	effect = "", --applied to all group members that receive the buff.
	buffSL = 0 --determines if Squad Leader also receives the buff. 	                   
}

AddRetreatGroupSkill(RetreatSkill);

------------------------------------------------------------------------

