ramna_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ramnaConvoHandler",
	screens = {}
}

pilot_not_corsec = ConvoScreen:new {
	id = "pilot_not_corsec",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_ccf2f65c", --  You lost, buddy?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_d30b5c72", "get_moving"}, -- Nah.
		{"@conversation/corellia_privateer_trainer_2:s_af22b9b2", "see_ya"}, -- I guess so.
	}
}
rikkh_convo_template:addScreen(pilot_not_corsec);
























--[[

	Quest Line Missions

]]















--[[

	Conversation Enders

]]

get_moving = ConvoScreen:new {
	id = "get_moving",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b26e36ad", -- If you're not a privateer, you sure as heck ARE lost. Get moving.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(get_moving);

see_ya = ConvoScreen:new {
	id = "see_ya",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9e0c4569", -- That's what I thought. See ya around.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(see_ya);

not_tier3 = ConvoScreen:new {
	id = "not_tier3",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_61b78d18", -- Psst! I think you took a wrong turn somewhere. Your boss is waiting for you.
	animation = "whisper",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(not_tier3);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c816ccac", -- Hey listen, we've ALL got work to do.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(on_mission);











addConversationTemplate("ramna_convo_template", ramna_convo_template);
