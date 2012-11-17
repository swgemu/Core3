--[[
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
--]]



--[[
	GLOBAL CITY SETTINGS
	--------------------
--]]
--The amount of time in minutes before the city specialization may be changed again.
CitySpecializationCooldown = 604800

--The amount of time in minutes before another withdrawal from the city treasury may be made.
TreasuryWithdrawalCooldown = 86400

--The number of city update cycles that must pass before mayoral voting process is complete.
CityVotingCycles = 3

--The number of city update cyles after which to lock the mayoral voting race registration.
CityVotingCyclesUntilLocked = 2

--The amount of time in minutes before the city performs an update.
CityUpdateInterval = 10080

--The amount of time in minutes a new city has to gain enough citizens to remain a city.
NewCityGracePeriod = 2

--The amount of time in minutes an old city has to regain enough citizens to remain a city.
OldCityGracePeriod = 30240

--Whether or not to allow the use of the command, /cityWarn to give players a TEF while in the city limits.
EnableCityWarn = false

--The number of citizens required to achieve each city rank. (Outpost, Village, Township, City, Metropolis)
CitizensPerRank = {2, 3, 4, 5, 6}
--CitizensPerRank = {10, 20, 35, 55, 85}

--The radius in meters of the city at each city rank. (Outpost, Village, Township, City, Metropolis)
RadiusPerRank = {150, 200, 300, 400, 450}



--[[
	CITIES ALLOWED PER PLANET
	-------------------------
	
	This is the number of cities allowed per planet, per rank. (Outpost, Village, Township, City, Metropolis)
	The maximum amount of cities per rank is 255.
--]]
CitiesAllowed = {
	{"corellia", {20, 20, 15, 10, 10}},
	{"dantooine", {50, 50, 30, 20, 20}},
	{"dathomir", {0, 0, 0, 0, 0}},
	{"endor", {0, 0, 0, 0, 0}},
	{"lok", {50, 50, 30, 20, 20}},
	{"naboo", {20, 20, 15, 10, 10}},
	{"rori", {50, 50, 30, 20, 20}},
	{"talus", {50, 50, 30, 20, 20}},
	{"tatooine", {20, 20, 15, 10, 10}},
	{"yavin4", {0, 0, 0, 0, 0}}
}



--[[
	CITY TAX SETTINGS
	-----------------
	
	WARNING: Do not change the number or order of tax entries below. You may only safely modify the entries.
	min: The minimum value of the tax.
	max: The maximum value of the tax.
	menuText: The text that appears on the 'Adjust Taxes' selection menu.
	inputTitle: The title of the set tax window.
	inputText: The text description of the set tax window.
	statusPrompt: The text that appears in the 'Status Report' window. Leave this blank to omit the tax from the report.
	systemMessage: The system message that is displayed to the mayor when settings this tax.
	emailSubject: The subject of the email that is sent to citizens when this tax changes.
	emailBody: The body of the email that is sent to citizens when this tax changes. %DI = Amount of new tax; %TO = Name of the city.
--]]
CityTaxes = {
	{--Property Tax
		min = 0, max = 50,
		menuText = "@city/city:property_tax_prompt",
		inputTitle = "@city/city:set_tax_t_property",
		inputText = "@city/city:set_tax_d_property",
		statusPrompt = "@city/city:promperty_tax_prompt",
		systemMessage = "@city/city:set_property_tax",
		emailSubject = "@city/city:tax_property_subject",
		emailBody = "@city/city:tax_property_body"
	},
	{--Income Tax
		min = 0, max = 2000,
		menuText = "@city/city:income_tax",
		inputTitle = "@city/city:set_tax_t_income",
		inputText = "@city/city:set_tax_d_income",
		statusPrompt = "@city/city:income_tax_prompt",
		systemMessage = "@city/city:set_income_tax",
		emailSubject = "@city/city:tax_income_subject",
		emailBody = "@city/city:tax_income_body"
	},
	{--Sales Tax
		min = 0, max = 20,
		menuText = "@city/city:sales_tax",
		inputTitle = "@city/city:set_tax_t_sales",
		inputText = "@city/city:set_tax_d_sales",
		statusPrompt = "@city/city:sales_tax_prompt",
		systemMessage = "@city/city:set_sales_tax",
		emailSubject = "@city/city:tax_sales_subject",
		emailBody = "@city/city:tax_sales_body"
	},
	{--Travel Tax
		min = 0, max = 500,
		menuText = "@city/city:travel_tax",
		inputTitle = "@city/city:set_tax_t_travel",
		inputText = "@city/city:set_tax_d_travel",
		statusPrompt = "@city/city:travel_cost_prompt",
		systemMessage = "@city/city:set_travel_fee",
		emailSubject = "@city/city:tax_travel_subject",
		emailBody = "@city/city:tax_travel_body"
	},
	{--Garage Tax
		min = 0, max = 30,
		menuText = "@city/city:garage_tax",
		inputTitle = "@city/city:set_tax_t_garage",
		inputText = "@city/city:set_tax_d_garage",
		statusPrompt = "",
		systemMessage = "@city/city:set_garage_tax",
		emailSubject = "@city/city:garage_fee_subject",
		emailBody = "@city/city:garage_fee_body"
	}
}



--[[
	CITY SPECIALIZATIONS
	====================
--]]
CitySpecializations = {
	{--Sample Rich
		name = "@city/city:city_spec_sample_rich",
		cost = 70000,
		skillMods = {
			{"private_spec_samplesize", 20},
			{"private_spec_samplerate", 10}
		}
	},
	{--Manufacturing Center
		name = "@city/city:city_spec_industry",
		cost = 50000,
		skillMods = {
			{"private_spec_assembly", 10}
		}
	},
	{--Medical Center
		name = "@city/city:city_spec_doctor",
		cost = 80000,
		skillMods = {
			{"private_medical_rating", 10}
		}
	},
	{--Clone Lab
		name = "@city/city:city_spec_clone",
		cost = 80000,
		skillMods = {
			{"private_spec_cloning", 20}
		}
	},
	{--Research Center
		name = "@city/city:city_spec_research",
		cost = 125000,
		skillMods = {
			{"private_spec_experimentation", 15}
		}
	},
	{--Improved Job Market
		name = "@city/city:city_spec_missions",
		cost = 80000,
		skillMods = {
			{"private_spec_missions", 20}
		}
	},
	{--Entertainment District
		name = "@city/city:city_spec_entertainer",
		cost = 80000,
		skillMods = {
			{"private_spec_entertainer", 10}
		}
	},
	{--Stronghold
		name = "@city/city:city_spec_stronghold",
		cost = 150000,
		skillMods = {
			{"private_defense", 50}
		}
	},
}
