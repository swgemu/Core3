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

-----------------------------------------------------------------------------------------------------------
exceptionalLiquidSuspension = {

	objectName = "\\#ffff00Advanced Liquid Suspension (Exceptional)",

	templateName = "object/tangible/component/chemistry/shared_liquid_delivery_suspension_advanced.iff",

	objectCRC = "1862978449",

	objectType = COMPONENT,

	power = 240,

        forageGroup = 6 -- exceptional components
}

CreateForageItemFromLua(exceptionalLiquidSuspension);
-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
exceptionalChemicalReleaseDurationMechanism = {

	objectName = "\\#ffff00Advanced Chemical Release Duration Mechanism (Exceptional)",

	templateName = "object/tangible/component/chemistry/shared_release_mechanism_duration_advanced.iff",

	objectCRC = "282084455",

	objectType = COMPONENT,

	power = 90, 

        forageGroup = 6 -- exceptional components
}

CreateForageItemFromLua(exceptionalChemicalReleaseDurationMechanism);
-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
exceptionalSolidDeliveryShell = {

	objectName = "\\#ffff00Advanced Solid Delivery Shell (Exceptional)",

	templateName = "object/tangible/component/chemistry/shared_solid_delivery_shell_advanced.iff",

	objectCRC = "2952575979",

	objectType = COMPONENT,

	power = 90, 

        forageGroup = 6 -- exceptional components
}

CreateForageItemFromLua(exceptionalSolidDeliveryShell);
-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
exceptionalBiologicalEffectController = {

	objectName = "\\#ffff00Advanced Biological Effect Controller (Exceptional)",

	templateName = "object/tangible/component/chemistry/shared_biologic_effect_controller_advanced.iff",

	objectCRC = "2300334388",

	objectType = COMPONENT,

        charges = 40,

	power = 40, 

        forageGroup = 6 -- exceptional components
}

CreateForageItemFromLua(exceptionalBiologicalEffectController);
-----------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------
