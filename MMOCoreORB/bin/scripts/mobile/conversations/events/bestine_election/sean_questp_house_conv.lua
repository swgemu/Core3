seanQuestpHouseConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questp_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/sean_questp_house:s_f6effab8", -- Oh my! I didn't expect visitors today! This place is a complete mess! Please forgive me. The last of the tragedy victims left. They all found new homes. I'm just cleaning up. Why are you here?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_house:s_34f710c5","convo_start2"}, -- What victims?
		{"@conversation/sean_questp_house:s_51c40792","questp_end"}, -- I'm in the wrong house. Sorry!
	}
}
seanQuestpHouseConvoTemplate:addScreen(convo_start);

convo_start2 = ConvoScreen:new {
	id = "convo_start2",
	leftDialog = "@conversation/sean_questp_house:s_8a9c6889", -- Oh, you didn't hear? The Empire went on a rampage and destroyed one of the newer, smaller cities assumed to harbor Rebel operatives. Those poor people. Sean Trenwell opened his homes for the survivors. He's such a kind man.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_house:s_ab4c4ff8","convo_start_give"} -- Really? Can you help me with something?
	}
}
seanQuestpHouseConvoTemplate:addScreen(convo_start2);

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/sean_questp_house:s_43e36f6f", -- Sure, I can try. What do you need? Write a testimony? Of course, I will! Anything to help him with this election. I really hope he wins. He deserves it. Let me write it up..
	stopConversation = "false",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(convo_start_give);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/sean_questp_house:s_d066eb10", -- Hello! Are you here to discuss the election? You haven't heard about it? You should really go to the capitol. The governor is taking votes.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(no_business);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/sean_questp_house:s_2267c63c", -- I'm so busy. Sean is planning to run for the new election that will happen soon. He's going to have tons of people over for dinner in hopes of impressing them. I really must get back to work. I'm sorry.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(no_election);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/sean_questp_house:s_47e61b76", -- Here you are. Please let me know if you'd like to come over for dinner sometime. I'm a great cook! Have a great day!
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(give_item);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/sean_questp_house:s_41f6594d", -- Oh hello! I'm surprised to see you again so soon. Please be sure to sure to show the governor the testimony I wrote for you. I want her to know what a kind and generous person Sean is.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(already_has_evidence);

no_room = ConvoScreen:new {
	id = "no_room",
	leftDialog = "@conversation/sean_questp_house:s_198905a5", -- Here you are--Oh no! You don't have enough room. I'm sorry. Please come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(no_room);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog =  "@conversation/sean_questp_house:s_20b8d563", -- I'm glad you're back. Do you have enough room now?
	stopConversation = "false",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(noroom_returned);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/sean_questp_house:s_9e4a0794", -- Here you are, then. I hope you have a wonderful day.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(noroom_returned_giveitem);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/sean_questp_house:s_bd542a54", -- You still don't have enough room. Come back when you do. I'd be happy to give it to you then.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(noroom_returned_noroom);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/sean_questp_house:s_d6d23166", -- Well, return when you do. I'll be happy to give it to you then.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(noroom_returned_reply);

questp_end = ConvoScreen:new {
	id = "questp_end",
	leftDialog = "@conversation/sean_questp_house:s_d5702a3b", -- Come back any time. You're always welcome in the Trenwell house.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(questp_end);

addConversationTemplate("seanQuestpHouseConvoTemplate", seanQuestpHouseConvoTemplate);
