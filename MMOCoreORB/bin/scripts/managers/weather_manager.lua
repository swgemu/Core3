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

-- defaultWeather: This determines which weather is in place when the server starts.
-- Acceptable values: 0, 1, 2, 3, 4, 5
-- A value of 5 will cause a random weather ID from 0-2 at startup.
-- Default: 5

-- weatherStability: This determines volitility in most factors for weather.
-- Acceptable values: 0-100
-- A value of 95 will have the following effect:
--  Base Weather:
--	0: 96%
--	1: 2.5%
--	2: 1.25%
--	3: < 1 so 0%
--	4: < 1 so 0%
--   Storm Patterns: 95% of storms will be mild, 5% medium to extreme
-- A value of 60 will have the following effect:
--  Base Weather:
--	0: 68%
--	1: 20%
--	2: 6.66%
--	3: 3.33%
--	4: 2%
--   Storm Patterns: 60% of storms will be mild, 40% medium to extreme

-----------------------------------------------------------

-- ***Optional Sandstorm Hindrance Feature***

-- This feature is only in effect (ticks) when weather ID = 4 (severe)

-- hasDamagingSandstorms: Determines whether the optional sandstorm hindrance feature is enabled.
-- Acceptable values: 0 or 1
-- Default value: 0


-- sandstormDamage: Determines how many wounds a player can receive to his primary HAM bars per sandstorm "tick".
-- Acceptable range: 0 to 500
-- Default: 70 (Tatooine), 50 (Lok)

-----------------------------------------------------------

-----------------
--   Corellia
-----------------
corellia = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 90, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--   Tatooine 
-----------------
tatooine = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 70, -- Range 0 - 100, Higher = Less weather changes, Overall better weather

	hasDamagingSandstorms = 0,

	sandstormDamage = 70, -- 40 = Annoying, 100 = deadly
}


-----------------
--   Dantooine
-----------------
dantooine = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 85, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--   Dathomir
-----------------
dathomir = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 50, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--    Endor
-----------------
endor = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 90, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--     Lok
-----------------
lok = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 60, -- Range 0 - 100, Higher = Less weather changes, Overall better weather

	hasDamagingSandstorms = 0,

	sandstormDamage = 50, -- 30 = Annoying, 50 = deadly
}

-----------------
--    Naboo
-----------------
naboo = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 90, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--     Rori
-----------------
rori = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 80, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--    Talus
-----------------
talus = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 80, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}

-----------------
--    Yavin4
-----------------
yavin4 = {

	defaultWeather = 0, -- Sunny

	averageWeatherDuration = 3600, -- In seconds

	weatherStability = 70, -- Range 0 - 100, Higher = Less weather changes, Overall better weather
}






