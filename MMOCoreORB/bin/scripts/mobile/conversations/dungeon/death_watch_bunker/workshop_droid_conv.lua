deathWatchWorkshopDroidConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "deathWatchWorkshopDroidConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d", -- ...
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_treadwell:s_4fcd015f", "clean_battery"}, -- Yes you can help me. I was sent to get this battery cleaned.
		{"@conversation/death_watch_treadwell:s_8e9e4ef9", "end_convo"}, -- No thank you. I am not need of any assistance.
	}
}

deathWatchWorkshopDroidConvoTemplate:addScreen(intro);

clean_battery = ConvoScreen:new {
	id = "clean_battery",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d", -- ...
	stopConversation = "true",
	options = {
	}
}
deathWatchWorkshopDroidConvoTemplate:addScreen(clean_battery);

end_convo = ConvoScreen:new {
	id = "end_convo",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d", -- ...
	stopConversation = "true",
	options = {
	}
}
deathWatchWorkshopDroidConvoTemplate:addScreen(end_convo);

no_battery_intro = ConvoScreen:new {
	id = "no_battery_intro",
	leftDialog = "@conversation/death_watch_treadwell:s_9208410d",
	stopConversation = "true",
	options = {
	}
}
deathWatchWorkshopDroidConvoTemplate:addScreen(no_battery_intro);

addConversationTemplate("deathWatchWorkshopDroidConvoTemplate", deathWatchWorkshopDroidConvoTemplate);