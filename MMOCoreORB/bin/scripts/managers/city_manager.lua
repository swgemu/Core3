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


------------------------------
--  Global City Settings
------------------------------
CitySpecializationCooldown = 604800000 --Milliseconds: 1 Week = 604800000
TreasuryWithdrawalCooldown = 86400000 --Milliseconds: 1 Day = 86400000
CityVotingDuration = 45 --Minutes until the next vote occurs. (60 = 1 hour, 1440 = 1 day, 10080 = 1 week)
CityUpdateInterval = 15 --Minutes between city rank updates (60 = 1 hour, 1440 = 1 day, 10080 = 1 week)
NewCityGracePeriod = 15 --Minutes before a new city has to reach rank 1 citizens before it decays.

CitizensPerRank = {1, 2, 4, 7, 11}
--CitizensPerRank = {10, 20, 35, 55, 85}
RadiusPerRank = {150, 200, 300, 400, 450}

------------------------------
--  City Tax Settings
------------------------------
--[[
	Notes on modifying existing taxes:
	WARNING: DO NOT CHANGE THE ORDER OR ADD NEW TAXES TO THE LIST BELOW WITHOUT MODIFYING THE CORE FIRST TO HANDLE IT.
	Each Tax table in the CityTaxes table below corresponds to a tax. They depend upon their position to be referenced in the core.
	They have the properties below:
	min: The minimum value the tax can have.
	max: the maximum value the tax can have.
	menuText: The string key corresponding to their menu text in the "Adjust Taxes" selection menu. Must come from city/city.stf.
	inputTitle: The string key corresponding to the title of the input box for the tax. Must come from city/city.stf.
	inputText: The string key corresponding to the body of the input box for the tax. Must come from city/city.stf.
	statusPrompt: The text displayed in the status report, showing the amount of tax. Leave this blank to omit this tax from the status report. Must come from city/city.stf
	systemMessage: The system message shown to the mayor upon success. Must come from city/city.stf.
	emailSubject: The subject of the email that is sent out to players when tax changes. Must come from city/city.stf.
	emailBody: The body of the email that is sent out to players when tax changes. Must come from city/city.stf.
--]]
CityTaxes = {
	{
		--Property Tax
		min = 0, max = 50,
		menuText = "property_tax_prompt",
		inputTitle = "set_tax_t_property",
		inputText = "set_tax_d_property",
		statusPrompt = "promperty_tax_prompt",
		systemMessage = "set_property_tax",
		emailSubject = "tax_property_subject",
		emailBody = "tax_property_body"
	},
	{
		--Income Tax
		min = 0, max = 2000,
		menuText = "income_tax",
		inputTitle = "set_tax_t_income",
		inputText = "set_tax_d_income",
		statusPrompt = "income_tax_prompt",
		systemMessage = "set_income_tax",
		emailSubject = "tax_income_subject",
		emailBody = "tax_income_body"
	},
	{
		--Sales Tax
		min = 0, max = 20,
		menuText = "sales_tax",
		inputTitle = "set_tax_t_sales",
		inputText = "set_tax_d_sales",
		statusPrompt = "sales_tax_prompt",
		systemMessage = "set_sales_tax",
		emailSubject = "tax_sales_subject",
		emailBody = "tax_sales_body"
	},
	{
		--Travel Tax
		min = 0, max = 500,
		menuText = "travel_tax",
		inputTitle = "set_tax_t_travel",
		inputText = "set_tax_d_travel",
		statusPrompt = "travel_cost_prompt",
		systemMessage = "set_travel_fee",
		emailSubject = "tax_travel_subject",
		emailBody = "tax_travel_body"
	},
	{
		--Garage Tax
		min = 0, max = 30,
		menuText = "garage_tax",
		inputTitle = "set_tax_t_garage",
		inputText = "set_tax_d_garage",
		statusPrompt = "",
		systemMessage = "set_garage_tax",
		emailSubject = "garage_fee_subject",
		emailBody = "garage_fee_body"
	}
}

------------------------------
--  Cities Per Planet
------------------------------
--{rank1, rank2, rank3, rank4, rank5}
-- -1 = 255 cities which is the max amount
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

CitySpecializations = {
	{
		name = "@city/city:city_spec_sample_rich",
		cost = 70000,
		skillMods = {
			{"private_spec_samplesize", 20},
			{"private_spec_samplerate", 10}
		}
	},
	{
		name = "@city/city:city_spec_industry",
		cost = 50000,
		skillMods = {
			{"private_spec_assembly", 10}
		}
	},
	{
		name = "@city/city:city_spec_doctor",
		cost = 80000,
		skillMods = {
			{"private_medical_rating", 10}
		}
	},
	{
		name = "@city/city:city_spec_clone",
		cost = 80000,
		skillMods = {
			{"private_spec_cloning", 20}
		}
	},
	{
		name = "@city/city:city_spec_research",
		cost = 125000,
		skillMods = {
			{"private_spec_experimentation", 15}
		}
	},
	{
		name = "@city/city:city_spec_missions",
		cost = 80000,
		skillMods = {
			{"private_spec_missions", 20}
		}
	},
	{
		name = "@city/city:city_spec_entertainer",
		cost = 80000,
		skillMods = {
			{"private_spec_entertainer", 10}
		}
	},
	{
		name = "@city/city:city_spec_stronghold",
		cost = 150000,
		skillMods = { --Stronghold
			{"private_defense", 50}
		}
	},
}
