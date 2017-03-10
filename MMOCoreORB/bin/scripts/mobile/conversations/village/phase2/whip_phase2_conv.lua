villageWhipPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageWhipPhase2ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/village_whip:s_4d59f240", -- It seems like it's one thing after another around here.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_77e48d5b", "attacking_supply_transports"}, -- What do you mean?
	}
}
villageWhipPhase2ConvoTemplate:addScreen(intro);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/village_whip:s_bfdaca25", -- Say, could you... oh, it looks like you're already pretty busy. On your way then.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_has_other_quest);

intro_completed_other_quest = ConvoScreen:new {
	id = "intro_completed_other_quest",
	leftDialog = "@conversation/village_whip:s_de007d6", -- Hey there. I heard you've been a big help around here. Great work!
	stopConversation = "false",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_completed_other_quest);

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/village_whip:s_b8360516", -- I don't mean to be rude, but you're getting in my way.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_not_eligible);

intro_quest_completed = ConvoScreen:new {
	id = "intro_quest_completed",
	leftDialog = "@conversation/village_whip:s_a984d976", -- You got all the supplies! That's just great. You have no idea how badly they were needed. You have my eternal thanks.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_quest_completed);

intro_quest_aborted = ConvoScreen:new {
	id = "intro_quest_aborted",
	leftDialog = "@conversation/village_whip:s_bfc5a85d", -- Uh oh... it looks like something happened during the transmission of the emergency beacon location. Here, let me try again...
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_quest_aborted);

intro_quest_failed = ConvoScreen:new {
	id = "intro_quest_failed",
	leftDialog = "@conversation/village_whip:s_af518049", -- You lost the supplies? Those supplies are vital to the survival of the village, now more than ever. Here, we've located another lost transport. Try to be more careful this time.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_quest_failed);

intro_quest_continue = ConvoScreen:new {
	id = "intro_quest_continue",
	leftDialog = "@conversation/village_whip:s_cc5225b7", -- Excellent work! Supplies! Hey, we've got supplies over here! This is great, but there are still %DI more shipments that we were expecting. We've located another lost transport. Good luck, friend.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_quest_continue);

intro_quest_inprogress = ConvoScreen:new {
	id = "intro_quest_inprogress",
	leftDialog = "@conversation/village_whip:s_ed25aceb", -- Go on now! You've got to go find the missing supplies!
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_dcf4498e", "beacons_not_reliable"}, -- I need a new beacon location.
		{"@conversation/village_whip:s_24aab8ee", "good_luck"}, -- Right! I'll get back to it!
	}
}
villageWhipPhase2ConvoTemplate:addScreen(intro_quest_inprogress);

beacons_not_reliable = ConvoScreen:new {
	id = "beacons_not_reliable",
	leftDialog = "@conversation/village_whip:s_e780d201", -- I understand. Those emergency beacons aren't as reliable as they probably should be. And those Sith Shadows are probably salvaging the last transport as we speak. There, I've loaded a new beacon location for you. Now hurry to Endor before it's too late!
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(beacons_not_reliable);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/village_whip:s_a80d9308", -- Good luck!
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(good_luck);

attacking_supply_transports = ConvoScreen:new {
	id = "attacking_supply_transports",
	leftDialog = "@conversation/village_whip:s_5d4ac8af", -- The Sith Shadows have been raiding our village for some time now. And now they've taken to attacking our supply transports from Endor.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_dc446bf8", "dire_need"}, -- How does that affect the village?
	}
}
villageWhipPhase2ConvoTemplate:addScreen(attacking_supply_transports);

dire_need = ConvoScreen:new {
	id = "dire_need",
	leftDialog = "@conversation/village_whip:s_550396aa", -- Well, we haven't received a shipment in some time, and we are in dire need of supplies.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_a767cb3c", "someone_to_go"}, -- Is there anything that I can do to help?
	}
}
villageWhipPhase2ConvoTemplate:addScreen(dire_need);

someone_to_go = ConvoScreen:new {
	id = "someone_to_go",
	leftDialog = "@conversation/village_whip:s_6fb14c74", -- There is, in fact. We are low on manpower and we need someone to go get those supplies for us. We are tracking the emergency beacons from the transports, we just need someone to go there and try to salvage some supplies.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_22d4c864", "help_us"}, -- I think that I can help with that.
		{"@conversation/village_whip:s_d29a29d0", "i_understand"}, -- That doesn't sound like something I can do.
	}
}
villageWhipPhase2ConvoTemplate:addScreen(someone_to_go);

i_understand = ConvoScreen:new {
	id = "i_understand",
	leftDialog = "@conversation/village_whip:s_106cd909", -- I understand. Just come back if you change your mind.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(i_understand);

help_us = ConvoScreen:new {
	id = "help_us",
	leftDialog = "@conversation/village_whip:s_e591b8a3", -- That's great! If you help us get those supplies, I will help you learn to use the Force to enhance your vehicle control skills.
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_d9ea288b", "not_taken_lightly"}, -- Yes, I will go find the missing supplies.
		{"@conversation/village_whip:s_2fdb8fbd", "i_understand"}, -- On second thought, I don't think I can help right now.
	}
}
villageWhipPhase2ConvoTemplate:addScreen(help_us);

not_taken_lightly = ConvoScreen:new {
	id = "not_taken_lightly",
	leftDialog = "@conversation/village_whip:s_eefb2830", -- You must realize that this is not a task to be taken lightly. If you help me with this, you will not be able to assist anyone else for a while. Do you understand?
	stopConversation = "false",
	options = {
		{"@conversation/village_whip:s_34ea67b6", "here_is_location"}, -- Yes, that is fine.
		{"@conversation/village_whip:s_d7ce4a0d", "i_understand"}, -- Oh, in that case I'd rather not.
	}
}
villageWhipPhase2ConvoTemplate:addScreen(not_taken_lightly);

here_is_location = ConvoScreen:new {
	id = "here_is_location",
	leftDialog = "@conversation/village_whip:s_edfab808", -- OK. Here is the location of one of the emergency beacons from a supply transport. Go there, see what you can find, and try to salvage some supplies. But be careful, there are likely to be some Sith Shadows still hanging around.
	stopConversation = "true",
	options = {}
}
villageWhipPhase2ConvoTemplate:addScreen(here_is_location);

addConversationTemplate("villageWhipPhase2ConvoTemplate", villageWhipPhase2ConvoTemplate);