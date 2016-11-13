villageSarguilloPhase3ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSarguilloPhase3ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/combat_quest_p3:s_822aed71", -- We've gained some critical information about the enemy, thanks to the efforts of you and your friends. The time for our attack has come.
	stopConversation = "false",
	options = {
	--{"@conversation/combat_quest_p3:s_43c7c81c", "crucial_information"}, -- What information do you have?
	--{"@conversation/combat_quest_p3:s_ab0e6060", "if_still_interested"}, -- Attack? Well, I have this appointment, you see...
	--{"@conversation/combat_quest_p3:s_d403b674", "here_is_remote"}, -- I want to turn in these frequency codes...
	--{"@conversation/combat_quest_p3:s_5d6c3f37", "simple_encryption"}, -- I want to turn in this waypoint datadisk...
	--{"@conversation/combat_quest_p3:s_f3864fa4", "work_with_friend"}, -- Tell me what I need to do again...
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(intro);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/combat_quest_p3:s_476f5295", -- It looks like you're already helping someone else in the village.  See me again later when you're ready to give me your undivided attention.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(intro_has_other_quest);

intro_completed_other_quest = ConvoScreen:new {
	id = "intro_completed_other_quest",
	leftDialog = "@conversation/combat_quest_p3:s_5ee8eee8", -- You've already helped the village out enough for now.  Come see me again when we're ready to get on with our preparations.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(intro_completed_other_quest);

intro_not_available = ConvoScreen:new {
	id = "intro_not_available",
	leftDialog = "@conversation/combat_quest_p3:s_2c9f72e9", -- I have nothing for you to do right now.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(intro_not_available);

crucial_information = ConvoScreen:new {
	id = "crucial_information",
	leftDialog = "@conversation/combat_quest_p3:s_1b62f30b", -- Our scouting missions have revealed some very crucial information about possible enemy encampments right here on Dathomir!  We are not certain of the exact locations and our intelligence tells us that the enemy is constantly on the move attempting to elude detection.
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_a48b66a0", "will_you_assist"}, -- I will fight for you!
		{"@conversation/combat_quest_p3:s_5604a3fb", "very_well"}, -- I'm afraid I don't have the time right now.  Good luck though.
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(crucial_information);

will_you_assist = ConvoScreen:new {
	id = "will_you_assist",
	leftDialog = "@conversation/combat_quest_p3:s_b8a984d3", -- I'm afraid I can't offer much in return, but I can put in a good word with Noldan, so that he might allow you to train Melee Accuracy.  Will you still assist me?  Keep in mind that if you're helping me, you won't be able to do any other work here in the village until later.
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_52917b0d", "excellent"}, -- Of course.
		{"@conversation/combat_quest_p3:s_6c565018", "i_understand"}, -- Sorry, I'm not interested in learning more about Melee Accuracy.
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(will_you_assist);

excellent = ConvoScreen:new {
	id = "excellent",
	leftDialog = "@conversation/combat_quest_p3:s_e4a148f5", -- Excellent!
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_527934ce", "exact_frequency"}, -- It's that easy, huh?
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(excellent);

exact_frequency = ConvoScreen:new {
	id = "exact_frequency",
	leftDialog = "@conversation/combat_quest_p3:s_7481097c", -- Well, not really.  First of all we need to know the exact frequency code for the specific shield you wish to power down in order to configure the remote control device.   Each shield has its own frequency code.
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_dd3cd5d7", "return_data_disk"}, -- And I guess I'm supposed to find these datadisks?
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(exact_frequency);

return_data_disk = ConvoScreen:new {
	id = "return_data_disk",
	leftDialog = "@conversation/combat_quest_p3:s_ae1194d7", -- If you return such a data disk to me, I will give you a remote control device configured with the proper frequency to power down the shield.
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_8767a129", "work_with_friend"}, -- What about my reward, if I work with someone else?
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(return_data_disk);

work_with_friend = ConvoScreen:new {
	id = "work_with_friend",
	leftDialog = "@conversation/combat_quest_p3:s_2a5da4e9", -- If you and a friend decide to take this task on together, I will make sure that both of you receive your training as long as you both participate.
	stopConversation = "false",
	options = {
		{"@conversation/combat_quest_p3:s_de9f3fb3", "power_down_generator"}, -- Tell me about powering down the shield generator...
		{"@conversation/combat_quest_p3:s_9bd673a6", "join_a_group"}, -- Tell me about capturing the camp's commander...
	}
}
villageSarguilloPhase3ConvoTemplate:addScreen(work_with_friend);

power_down_generator = ConvoScreen:new {
	id = "power_down_generator",
	leftDialog = "@conversation/combat_quest_p3:s_3804b036", -- Then you must power down the shield generator and eliminate at least 5 of the enemy's troops afterwards.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(power_down_generator);

join_a_group = ConvoScreen:new {
	id = "join_a_group",
	leftDialog = "@conversation/combat_quest_p3:s_97bc1b9", -- Then you must join a group with someone who powered down the shield generator, and eliminate at least 5 of the enemy's troops after the shield comes down.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(join_a_group);

i_understand = ConvoScreen:new {
	id = "i_understand",
	leftDialog = "@conversation/combat_quest_p3:s_206a4b9b", -- I understand.  Farewell.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(i_understand);

very_well = ConvoScreen:new {
	id = "very_well",
	leftDialog = "@conversation/combat_quest_p3:s_54db1a8e", -- Very well.  Goodbye.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(very_well);

if_still_interested = ConvoScreen:new {
	id = "if_still_interested",
	leftDialog = "@conversation/combat_quest_p3:s_50cdfefd", -- Very well.  Come back to see me if you're still interested in helping us to bring a swift end to this evil that has befallen our village.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(if_still_interested);

here_is_remote = ConvoScreen:new {
	id = "here_is_remote",
	leftDialog = "@conversation/combat_quest_p3:s_c012ae2b", -- Very well.  Here is a remote control configured with the frequency code on the datapad.   Good luck
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(here_is_remote);

simple_encryption = ConvoScreen:new {
	id = "simple_encryption",
	leftDialog = "@conversation/combat_quest_p3:s_51775d2e", -- A yes.  This encryption is rather simple.  I have added the waypoint information to your datapad.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase3ConvoTemplate:addScreen(simple_encryption);

addConversationTemplate("villageSarguilloPhase3ConvoTemplate", villageSarguilloPhase3ConvoTemplate);
