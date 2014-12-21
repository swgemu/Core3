deathWatchMedicalDroidConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchMedicalDroidConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_medical_droid:s_22f2cc9b", -- Welcome. I am medical droid designation G12-4J. How may I be of service to you?
	stopConversation = "false",
	options = {
		-- Adjust if full inventory
		--{"@conversation/death_watch_medical_droid:s_ab36bcfc", "cure_issued"}, -- I need some medicine to cure alum sickness.
		--{"@conversation/death_watch_medical_droid:s_ab36bcfc", "inventory_full"}, -- I need some medicine to cure alum sickness.
		--{"@conversation/death_watch_medical_droid:s_82d3782a", "please_return"}, -- I don't think there is anything that I need.
	}
}
deathWatchMedicalDroidConvoTemplate:addScreen(intro);

please_return = ConvoScreen:new {
	id = "please_return",
	leftDialog = "@conversation/death_watch_medical_droid:s_52a263b9", -- Please return if there is anything that I can be of service to you for. Thank you.
	stopConversation = "true",
	options = {
	}
}
deathWatchMedicalDroidConvoTemplate:addScreen(please_return);

cure_issued = ConvoScreen:new {
	id = "cure_issued",
	leftDialog = "@conversation/death_watch_medical_droid:s_6a6a070d", -- Alum sickness cure has been issued. Please administer to the subject directly and allow for medicine to take effect. Resume normal, unpolluted breathing or alum sickness may return. Thank you.
	stopConversation = "true",
	options = {
	}
}
deathWatchMedicalDroidConvoTemplate:addScreen(cure_issued);

inventory_full = ConvoScreen:new {
	id = "inventory_full",
	leftDialog = "@conversation/death_watch_medical_droid:s_46d286cc", -- I would like to issue you the alum sickness cure medication but you do not have any room in your inventory. Please speak to me again once you have cleared up some space.
	stopConversation = "true",
	options = {
	}
}
deathWatchMedicalDroidConvoTemplate:addScreen(inventory_full);

addConversationTemplate("deathWatchMedicalDroidConvoTemplate", deathWatchMedicalDroidConvoTemplate);
