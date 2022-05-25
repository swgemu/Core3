coa3VeersConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3VeersConvoHandler",
	screens = {}
}

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3lgeneralveers:s_4d8cedd4", -- I don't have time to talk right now, I'm waiting for someone.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(init_default);

init_sent_by_coordinator = ConvoScreen:new {
	id = "init_sent_by_coordinator",
	leftDialog = "@conversation/coa3lgeneralveers:s_1cfbefd4", -- So you're the one we've been hearing so much about. I wanted to personally thank you for doing such a commendable job. The Empire needs more Soldiers like you. Thanks to your efforts we were able to find one of their research facilities. Destroying this facility would strike a serious blow against them and could significantly hamper their efforts. We need that facility destroyed and I think you're just the person for the job. Can I count on you?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lgeneralveers:s_fdba7430", "location_of_facility"}, -- You can count on me.
		{"@conversation/coa3lgeneralveers:s_2977a9a3", "not_acceptable"}, -- I'm not able to do this now
	}
}
coa3VeersConvoTemplate:addScreen(init_sent_by_coordinator);

not_acceptable = ConvoScreen:new {
	id = "not_acceptable",
	leftDialog = "@conversation/coa3lgeneralveers:s_efae2d69", -- What? This is not acceptable! Perhaps you are not as good as the stories I've been hearing about you. Get out of my sight.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(not_acceptable);

location_of_facility = ConvoScreen:new {
	id = "location_of_facility",
	leftDialog = "@conversation/coa3lgeneralveers:s_1a6ba35a", -- Good. Here's the location of the facility. Reduce it to rubble and destroy any traitors there you find. The destruction of this facility will seriously hamper their efforts to find an Alderaanian Flora alternative. This is not an easy mission, so you may want to recruit some help to destroy it.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(location_of_facility);

init_in_progress = ConvoScreen:new {
	id = "init_in_progress",
	leftDialog = "@conversation/coa3lgeneralveers:s_370a3d89", -- What's the matter, don't know how to follow orders? Why haven't you destroyed the facility yet?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lgeneralveers:s_92d64a93", "get_to_it"}, -- I'll get on it right now.
		{"@conversation/coa3lgeneralveers:s_6be1cd6b", "faulty_data"}, -- I wasn't able to located the facility
		{"@conversation/coa3lgeneralveers:s_2cdb5dd0", "overlook_failure"}, -- I can not do this right now
	}
}
coa3VeersConvoTemplate:addScreen(init_in_progress);

get_to_it = ConvoScreen:new {
	id = "get_to_it",
	leftDialog = "@conversation/coa3lgeneralveers:s_a486253d", -- Get to it and don't leave anything standing!
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(get_to_it);

faulty_data = ConvoScreen:new {
	id = "faulty_data",
	leftDialog = "@conversation/coa3lgeneralveers:s_b02864c6", -- Perhaps our data was faulty. I've uploaded some fresh intel to your datapad.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(faulty_data);

overlook_failure = ConvoScreen:new {
	id = "overlook_failure",
	leftDialog = "@conversation/coa3lgeneralveers:s_4461239", -- I hope you realize that we don't take look kindly on failure. I'll overlook it this one time. If you wish to try it again some time in the future, you let me know.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(overlook_failure);

init_completed_everything = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3lgeneralveers:s_bea4597", -- Great work taking out that research facility that really hit them where it counts! If you continue your service to the Empire in this manner, I see great things in your future.
	stopConversation = "true",
	options = {}
}
coa3VeersConvoTemplate:addScreen(init_default);

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	customDialogText =  "You must declare your allegiance. You cannot be on leave, and must at lease be a Combatant.",
	stopConversation = "false",
	options = {}
}
coa3VeersConvoTemplate:addScreen(wrong_faction);

addConversationTemplate("coa3VeersConvoTemplate", coa3VeersConvoTemplate);