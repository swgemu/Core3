seanQuestpMarketConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questp_conv_handler",
	screens = {}
}

default_reply = ConvoScreen:new {
	id = "default_reply",
	leftDialog = "@conversation/sean_questp_market:s_7ffa475", -- Are you here to collect these influx capacitors? *pauses listening to the Jawa next to her* Oh... sorry, you're not the right person. While I've got your ear, I should let you know there's an election going on at the capitol. I encourage you to support Sean Trenwell if you get involved.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(default_reply);

no_office = ConvoScreen:new {
	id = "no_office",
	leftDialog = "@conversation/sean_questp_market:s_f319b246", --Our little market is tucked away in the city, but provides wonderful rewards for brave acts. I think some of the merchants here are looking for rare bones. Not sure where you'd get them from. But someone mentioned Sand People. Does that mean anything to you?
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(no_office);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/sean_questp_market:s_c8e9e99a", --Hi again. Good to see you... and oh, since you still have that disk I gave you, my friend thinks he can use something like that in an invention of his. But I guess you still need it, don't you. Nevermind.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(already_has_evidence);

noroom = ConvoScreen:new {
	id = "noroom",
	leftDialog = "@conversation/sean_questp_market:s_a1a4c8c9", --Oh yeah? We'd love to help! Of course, we'll give it to you--Wait a second. Unfortunately, you don't have enough room. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom);


quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/sean_questp_market:s_faf0f6d6", --We've recently established ourselves in this new marketplace . Isn't it great? Sean Trenwell used his own money to help build it.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_cb056ffb","quest_start2"}, --Do you have record of that?
		{"@conversation/sean_questp_market:s_de2e386f","good_bye"}, --That's nice. I have to go.
	}
}
seanQuestpMarketConvoTemplate:addScreen(quest_start);

quest_start2 = ConvoScreen:new {
	id = "quest_start2",
	leftDialog = "@conversation/sean_questp_market:s_e61c91fe", --Actually, my Jawa friend may have something like that. Wait here a second while I discuss it with him.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_67e6df55","quest_start3"} --Okay.
	}
}
seanQuestpMarketConvoTemplate:addScreen(quest_start2);

quest_start3 = ConvoScreen:new {
	id = "quest_start3",
	leftDialog = "@conversation/sean_questp_market:s_9e71b2ab", --In fact, he does. You're lucky you came today. He was going to take the disk apart and recycle it to make one of his new, crazy inventions. Why do you need it?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_market:s_a4149441","quest_start4"} --Let me tell you the situation...
	}
}
seanQuestpMarketConvoTemplate:addScreen(quest_start3);

quest_start4 = ConvoScreen:new {
	id = "quest_start4",
	leftDialog = "@conversation/sean_questp_market:s_b4164d7b", --Oh yeah? We'd love to help! Of course, we'll give it to you for the sake of helping Sean Trenwell win the election. Here you are. Good luck!
	stopConversation = "false",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(quest_start4);



noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/sean_questp_market:s_40977666", --Welcome! Oh, I remember you. Do you have enough room now to receive the evidence?
	stopConversation = "false",
	options = { }
	--Haven't had a chance yet.s_6cd9792d
	--Yes, please.s_c82e9a2f}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/sean_questp_market:s_14d1042bs", --Here you are. Good luck on the voting!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_giveitem);

noroom_returned_nochance = ConvoScreen:new {
	id = "noroom_returned_nochance",
	leftDialog = "@conversation/sean_questp_market:s_c1035c83", --Ah, well return when you've done so.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_nochance);

noroom_returned_stillfull = ConvoScreen:new {
	id = "noroom_returned_stillfull",
	leftDialog = "@conversation/sean_questp_market:s_1b885620", --You didn't have enough room again. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_stillfull);

noroom_returned_no = ConvoScreen:new {
	id = "noroom_returned_no",
	leftDialog = "@conversation/sean_questp_market:s_b8a92f09", --I see. I guess there's no hurry... just come back you have more space.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(noroom_returned_no);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/sean_questp_market:s_60613aaf", --Bye!
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(give_item);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@conversation/sean_questp_market:s_ce0e0612", --Nice doing... well, we didn't exactly do business, did we. Thanks for coming by, I suppose.
	stopConversation = "true",
	options = {}
}
seanQuestpMarketConvoTemplate:addScreen(good_bye);


addConversationTemplate("seanQuestpMarketConvoTemplate", seanQuestpMarketConvoTemplate);
