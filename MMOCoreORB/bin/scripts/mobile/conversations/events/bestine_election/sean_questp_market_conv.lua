seanQuestpMarketConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanQuestpMarketConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/sean_questp_market:s_7ffa475", -- Are you here to collect these influx capacitors? *pauses listening to the Jawa next to her* Oh... sorry, you're not the right person. While I've got your ear, I should let you know there's an election going on at the capitol. I encourage you to support Sean Trenwell if you get involved.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(init_election_phase);

init_joined_sean = ConvoScreen:new {
	id = "init_joined_sean",
	leftDialog = "@conversation/sean_questp_market:s_faf0f6d6", -- We've recently established ourselves in this new marketplace . Isn't it great? Sean Trenwell used his own money to help build it.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_cb056ffb", "jawa_might_have"}, -- Do you have record of that?
	}
}
seanQuestpMarketConvoTemplate:addScreen(init_joined_sean);

jawa_might_have = ConvoScreen:new {
	id = "jawa_might_have",
	leftDialog = "@conversation/sean_questp_market:s_e61c91fe", -- Actually, my Jawa friend may have something like that. Wait here a second while I discuss it with him.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_67e6df55", "lucky_you_came"}, -- Okay.
	}
}
seanQuestpMarketConvoTemplate:addScreen(jawa_might_have);

lucky_you_came = ConvoScreen:new {
	id = "lucky_you_came",
	leftDialog = "@conversation/sean_questp_market:s_9e71b2ab", -- In fact, he does. You're lucky you came today. He was going to take the disk apart and recycle it to make one of his new, crazy inventions. Why do you need it?
	stopConversation = "false",
	options = {
		--{"@conversation/sean_questp_market:s_a4149441", "love_to_help"}, -- Let me tell you the situation...
	}
}
seanQuestpMarketConvoTemplate:addScreen(lucky_you_came);

love_to_help = ConvoScreen:new {
	id = "love_to_help",
	leftDialog = "@conversation/sean_questp_market:s_b4164d7b", -- Oh yeah? We'd love to help! Of course, we'll give it to you for the sake of helping Sean Trenwell win the election. Here you are. Good luck!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(love_to_help);

help_but_inv_full = ConvoScreen:new {
	id = "help_but_inv_full",
	leftDialog = "@conversation/sean_questp_market:s_a1a4c8c9", -- Oh yeah? We'd love to help! Of course, we'll give it to you--Wait a second. Unfortunately, you don't have enough room. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(help_but_inv_full);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/sean_questp_market:s_40977666", -- Welcome! Oh, I remember you. Do you have enough room now to receive the evidence?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_questp_market:s_c82e9a2f", "i_feel_bad"}, -- Yes, please.
	--{"@conversation/sean_questp_market:s_6cd9792d", "return_when_done"}, -- Haven't had a chance yet.
	}
}
seanQuestpMarketConvoTemplate:addScreen(init_inv_was_full);

give_evidence = ConvoScreen:new {
	id = "give_evidence",
	leftDialog = "@conversation/sean_questp_market:s_14d1042b", -- Here you are. Good luck on the voting!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/sean_questp_market:s_1b885620", -- You didn't have enough room again. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(inv_still_full);

return_when_done = ConvoScreen:new {
	id = "return_when_done",
	leftDialog = "@conversation/sean_questp_market:s_c1035c83", -- Ah, well return when you've done so.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(return_when_done);

init_not_election_phase = ConvoScreen:new {
	id = "init_not_election_phase",
	leftDialog = "@conversation/sean_questp_market:s_f319b246", -- Our little market is tucked away in the city, but provides wonderful rewards for brave acts. I think some of the merchants here are looking for rare bones. Not sure where you'd get them from. But someone mentioned Sand People. Does that mean anything to you?
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(init_not_election_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/sean_questp_market:s_c8e9e99a", -- Hi again. Good to see you... and oh, since you still have that disk I gave you, my friend thinks he can use something like that in an invention of his. But I guess you still need it, don't you. Nevermind.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(init_already_has_evidence);

addConversationTemplate("seanQuestpMarketConvoTemplate", seanQuestpMarketConvoTemplate);
