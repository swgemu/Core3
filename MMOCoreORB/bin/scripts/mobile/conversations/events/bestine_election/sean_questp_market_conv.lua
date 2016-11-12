seanQuestpMarketConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questp_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/sean_questp_market:s_faf0f6d6", -- We've recently established ourselves in this new marketplace . Isn't it great? Sean Trenwell used his own money to help build it.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_cb056ffb", "convo_start2"}, -- Do you have record of that?
		{"@conversation/sean_questp_market:s_de2e386f", "questp_end"}, -- That's nice. I have to go.
	}
}
seanQuestpMarketConvoTemplate:addScreen(convo_start);

convo_start2 = ConvoScreen:new {
	id = "convo_start2",
	leftDialog = "@conversation/sean_questp_market:s_e61c91fe", -- Actually, my Jawa friend may have something like that. Wait here a second while I discuss it with him.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_67e6df55", "convo_start3"} -- Okay.
	}
}
seanQuestpMarketConvoTemplate:addScreen(convo_start2);

convo_start3 = ConvoScreen:new {
	id = "convo_start3",
	leftDialog = "@conversation/sean_questp_market:s_9e71b2ab", -- In fact, he does. You're lucky you came today. He was going to take the disk apart and recycle it to make one of his new, crazy inventions. Why do you need it?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_a4149441","convo_start_give"} -- Let me tell you the situation...
	}
}
seanQuestpMarketConvoTemplate:addScreen(convo_start3);

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/sean_questp_market:s_b4164d7b", -- Oh yeah? We'd love to help! Of course, we'll give it to you for the sake of helping Sean Trenwell win the election. Here you are. Good luck!
	stopConversation = "false",
}
seanQuestpMarketConvoTemplate:addScreen(convo_start_give);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/sean_questp_market:s_7ffa475", -- Are you here to collect these influx capacitors? *pauses listening to the Jawa next to her* Oh... sorry, you're not the right person. While I've got your ear, I should let you know there's an election going on at the capitol. I encourage you to support Sean Trenwell if you get involved.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(no_business);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/sean_questp_market:s_f319b246", -- Our little market is tucked away in the city, but provides wonderful rewards for brave acts. I think some of the merchants here are looking for rare bones. Not sure where you'd get them from. But someone mentioned Sand People. Does that mean anything to you?
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(no_election);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/sean_questp_market:s_60613aaf", -- Bye!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(give_item);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/sean_questp_market:s_c8e9e99a", -- Hi again. Good to see you... and oh, since you still have that disk I gave you, my friend thinks he can use something like that in an invention of his. But I guess you still need it, don't you. Nevermind.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(already_has_evidence);

no_room = ConvoScreen:new {
	id = "no_room",
	leftDialog = "@conversation/sean_questp_market:s_a1a4c8c9", -- Oh yeah? We'd love to help! Of course, we'll give it to you--Wait a second. Unfortunately, you don't have enough room. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(no_room);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/sean_questp_market:s_40977666", -- Welcome! Oh, I remember you. Do you have enough room now to receive the evidence?
	stopConversation = "false",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/sean_questp_market:s_14d1042bs", -- Here you are. Good luck on the voting!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_giveitem);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/sean_questp_market:s_c1035c83", -- Ah, well return when you've done so.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_reply);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/sean_questp_market:s_1b885620", -- You didn't have enough room again. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_noroom);

questp_end = ConvoScreen:new {
	id = "questp_end",
	leftDialog = "@conversation/sean_questp_market:s_ce0e0612", -- Nice doing... well, we didn't exactly do business, did we. Thanks for coming by, I suppose.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(questp_end);


addConversationTemplate("seanQuestpMarketConvoTemplate", seanQuestpMarketConvoTemplate);
