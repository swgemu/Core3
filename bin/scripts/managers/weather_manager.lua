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



--------------------------
-- Weather System Notes
--------------------------
-- Weather ID's are: 0-4 (0 being sunny and calm)
-- When a new weather ID is chosen (delayed by newWeatherTime), the server will slowly 
-- change to that value one ID at a time (delayed by transitionTime).



----------------------------
-- Desciption of Variables
----------------------------
-- weatherEnabled: This determines if the weather will change over time.
-- Acceptable values: 0 or 1
-- Default: 1

-- startingWeatherID: This determines which weather is in place when the server starts.
-- Acceptable values: 0, 1, 2, 3, 4, 5
-- A value of 5 will cause a random weather ID from 0-2 at startup.
-- Default: 5

-- levelZeroChance (percent)
-- levelOneChance (percent)
-- levelTwoChance (percent)
-- levelThreeChance (percent)
-- levelFourChance (percent)
-- These determine the chance each weather ID will be selected when new weather is chosen.
-- Acceptable range: 0-100. These values must combine to equal 100.
-- Default: 70, 14, 9, 5, 2

-- windChangeChance (percent): Determines the chance of the wind direction changing when the weather ID transitions between 3-4. 
-- Acceptable range: 0 to 100
-- Default: 50

-- newWeatherTimeMin (seconds): Determines the minimum amount of time until new weather is chosen after the previously selected weather is reached.
-- Acceptable Range: 0 to less than or equal to newWeatherTimeMax
-- Default: 600 (10 minutes)


-- newWeatherTimeMax (seconds): Determines the maximum amount of time until new weather is chosen after the previously selected weather is reached.
-- Acceptable Range: 0 to 100000
-- Default: 1800 (30 minutes)


-- transitionTimeMin (seconds): Determines the minimum amount of time until the weather transitions toward the selected weather again.
-- Acceptable Range: 0 to less than or equal to transitionTimeMax
-- Default: 120 (2 minutes)


-- transitionTimeMax (seconds): Determines the maximum amount of time until the weather transitions toward the selected weather again.
-- Acceptable Range: 0 to 100000
-- Default: 600 (10 minutes)

-----------------------------------------------------------

-- ***Optional Sandstorm Hindrance Feature***

-- This feature is only in effect (ticks) when weather ID = 4 (severe) on Tatooine and Lok.

-- sandstormEffectsEnabled: Determines whether the optional sandstorm hindrance feature is enabled.
-- Acceptable values: 0 or 1
-- Default value: 0


-- sandstormWounds: Determines how many wounds a player can receive to his primary HAM bars per sandstorm "tick".
-- Acceptable range: 0 to 500
-- Default: 15 (Tatooine), 10 (Lok)

-- sandstormWoundsMitigation: Determines how many wounds to subtract per protective item the player is wearing (5 items max).
-- Acceptable range: 0 to 500
-- Default: 3 (Tatooine), 2 (Lok)


-- sandstormKnockdownChance: Determines the percent chance that a player will be knocked down per sandstorm "tick".
-- Acceptable range: 0 to 100
-- Default: 40 (Tatooine), 30 (Lok)


-- sandstormKnockdownModifier: Determines how much knockdown chance will be added (armour) or subtracted (protective
-- clothing) per item the player is wearing (5 items max).
-- Acceptable range: 0 to 100
-- Default: 4 (Tatooine), 4 (Lok)


-- sandstormTickTime (seconds): Determines how often the sandstorm hindrances will be applied to players not in a structure or camp.
-- Acceptable range: 5 to 60 
-- Default: 10

-----------------------------------------------------------

-----------------
--   Corellia
-----------------
corellia_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--   Dantooine
-----------------
dantooine_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--   Dathomir
-----------------
dathomir_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--    Endor
-----------------
endor_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--     Lok
-----------------
lok_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
	sandstormEffectsEnabled = 1,
	sandstormWounds = 10,
	sandstormWoundsMitigation = 2,
	sandstormKnockdownChance = 30,
	sandstormKnockdownModifier = 4,
	sandstormTickTime = 10,
}

-----------------
--    Naboo
-----------------
naboo_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--     Rori
-----------------
rori_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--    Talus
-----------------
talus_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}

-----------------
--   Tatooine 
-----------------
tatooine_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
	sandstormEffectsEnabled = 1,
	sandstormWounds = 15,
	sandstormWoundsMitigation = 3,
	sandstormKnockdownChance = 40,
	sandstormKnockdownModifier = 4,
	sandstormTickTime = 10,
}

-----------------
--    Yavin4
-----------------
yavin4_weather = {
	weatherEnabled = 1,
	startingWeatherID = 5,
	levelZeroChance = 70,
	levelOneChance = 14,
	levelTwoChance = 9,
	levelThreeChance = 5,
	levelFourChance = 2,
	windChangeChance = 50,
	newWeatherTimeMin = 600,
	newWeatherTimeMax = 1800,
	transitionTimeMin = 120,
	transitionTimeMax = 600,
}






