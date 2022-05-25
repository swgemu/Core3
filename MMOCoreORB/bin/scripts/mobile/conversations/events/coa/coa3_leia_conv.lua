coa3LeiaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3LeiaConvoHandler",
	screens = {}
}

-- Sent from coordinator

init_sent_by_coordinator = ConvoScreen:new {
	id = "init_sent_by_coordinator",
	leftDialog = "@conversation/coa3wcoolguy:s_a85b1da", -- It is so nice to meet you. Your bravery so far has generated quite a bit of conversation in the ranks. Are you ready to do more for the Alliance?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoolguy:s_62241cb7", "find_alternative"}, -- What's going on?
		{"@conversation/coa3wcoolguy:s_4c3cd444", "research_stations"}, -- I'd like to finish what I started.
		{"@conversation/coa3wcoolguy:s_d1ae6871", "sorry_to_hear"}, -- I don't have time for this now.
	}
}
coa3LeiaConvoTemplate:addScreen(init_sent_by_coordinator);

find_alternative = ConvoScreen:new {
	id = "find_alternative",
	leftDialog = "@conversation/coa3wcoolguy:s_9ebad40b", -- We're trying to find an alternative to Alderaanian Flora for the Dead Eye process and have a number of research stations working on the problem. If we succeed we will be able to continue to make Dead Eye. If we can't, Dead Eye will be useless once the current stores of Alderaanian Flora are exhausted.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoolguy:s_d768eb98", "discovered_stations"}, -- What is the enemy doing?
		{"@conversation/coa3wcoolguy:s_4c3cd444", "research_stations"}, -- I'd like to finish what I started.
		{"@conversation/coa3wcoolguy:s_d1ae6871", "sorry_to_hear"}, -- I don't have time for this now.
	}
}
coa3LeiaConvoTemplate:addScreen(find_alternative);

discovered_stations = ConvoScreen:new {
	id = "discovered_stations",
	leftDialog = "@conversation/coa3wcoolguy:s_f3080e5", -- They have discovered our research stations and have been launching constant attacks against them. They are hoping to hinder our research to the point that Dead Eye will fail.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoolguy:s_4c3cd444", "research_stations"}, -- I'd like to finish what I started.
		{"@conversation/coa3wcoolguy:s_d1ae6871", "sorry_to_hear"}, -- I don't have time for this now.
	}
}
coa3LeiaConvoTemplate:addScreen(discovered_stations);

research_stations = ConvoScreen:new {
	id = "research_stations",
	leftDialog = "@conversation/coa3wcoolguy:s_c0e4cb7a", -- Excellent. We have a number of research stations that are coming under attack from the Empire. I've uploaded a waypoint to your datapad. Head out there and stop the attackers. It will be a hard fight. You might need help.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(research_stations);

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	customDialogText =  "For this task you must become one of us. Please speak to one of our recruiters and come back to me. You cannot be on leave, and must at lease be a Combatant.",
	stopConversation = "false",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(wrong_faction);

-- Accepted Mission to go to Facility

init_in_progress = ConvoScreen:new {
	id = "init_in_progress",
	leftDialog = "@conversation/coa3wcoolguy:s_a4053724", -- Did you complete the mission yet?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoolguy:s_83b68081", "good_luck_then"}, -- Not yet. I'm working on it.
		{"@conversation/coa3wcoolguy:s_dc616180", "datapad_troubles"}, -- I need to get a new assignment, that last one had a bad waypoint.
		{"@conversation/coa3wcoolguy:s_6428dedb", "sorry_to_hear"}, -- I can't complete this mission right now.
	}
}
coa3LeiaConvoTemplate:addScreen(init_in_progress);

good_luck_then = ConvoScreen:new {
	id = "good_luck_then",
	leftDialog = "@conversation/coa3wcoolguy:s_cf3aed9b", -- Good luck then. Come back when you're done.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(good_luck_then);

datapad_troubles = ConvoScreen:new {
	id = "datapad_troubles",
	leftDialog = "@conversation/coa3wcoolguy:s_bb33eb73", -- Datapad troubles? That happens. I'll upload a new waypoint to your pad. Good luck.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(datapad_troubles);

-- Finished CoA3 Story Line

init_completed_everything = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3wcoolguy:s_c500ae34", -- The Rebellion owes you a debt of thanks. If we are able to finish this research, we will be able to replace the Alderaanian Flora with a suitable alternative and bring Dead Eye to our troops. While the Tactical Officers might have more missions to collect flora, we have asked all of you that we can. You have my personal thanks. May the Force be with you.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(init_default);

-- Generic Response

init_default = ConvoScreen:new {
	id = "init_default",
	leftDialog = "@conversation/coa3wcoolguy:s_a3621ded", -- I'm sorry, but we are very busy right now. If you want to help, you should go find one of our Coordinators.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(init_default);

sorry_to_hear = ConvoScreen:new {
	id = "sorry_to_hear",
	leftDialog = "@conversation/coa3wcoolguy:s_cc92be25", -- I'm sorry to hear that. These stations are constantly coming under attack, so come back if you change your mind.
	stopConversation = "true",
	options = {}
}
coa3LeiaConvoTemplate:addScreen(sorry_to_hear);

addConversationTemplate("coa3LeiaConvoTemplate", coa3LeiaConvoTemplate);
