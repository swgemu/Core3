seanQuestnUniversityConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questn_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/sean_questn_university:s_5788afea", --  I'm in the middle of grading papers. Did you need help with something?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questn_university:s_36904010", "convo_start_give"} -- I was told to talk to you about Sean Trenwell.
	}
}
seanQuestnUniversityConvoTemplate:addScreen(convo_start);

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/sean_questn_university:s_7c259594", -- Sean Trenwell... oh yes! I remember him. Unfortunately, he was a particularly bad student. I would always catch him trying to cheat during exams. He barely graduated from the University. In fact, he could even be considered a fake. I really don't want him representing our people in this election.
	stopConversation = "false",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(convo_start_give);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/sean_questn_university:s_3c4a2f4", -- I'm too busy to talk right now. I'm grading papers. You seem like you'd be interested in voting at the capitol. They're holding an election.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(no_business);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/sean_questn_university:s_9c880546", -- I hope you've gone to school. We could really use more... educated folks nowadays.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(no_election);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/sean_questn_university:s_799ad811", -- Mmhmm--Oh really? I actually have something that might help you. I think you could use it as evidence. Yes! Here it is. I always keep the grades of my students. Here you are.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questn_university:s_b9b27823", "questn_end"} -- Thank you.
	}
}
seanQuestnUniversityConvoTemplate:addScreen(give_item);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/sean_questn_university:s_70145cf1", -- You again. I'm still quite busy, and I see you still have those papers I gave you from Mr. Trenwell's school days. How's this... you leave me to my work, and I won't ask for those back?
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(already_has_evidence);

no_room = ConvoScreen:new {
	id = "no_room",
	leftDialog = "@conversation/sean_questn_university:s_dac635d2", -- I see that you don't have enough room to get the evidence you seek. Please come back when you have room.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(no_room);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/sean_questn_university:s_656e8f97", -- I see that you've returned. Do you have enough room now?
	stopConversation = "false",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(noroom_returned);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/sean_questn_university:s_99711fbf", -- Again, you still don't have enough room. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(noroom_returned_noroom);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/sean_questn_university:s_b8a92f09", -- I see. I guess there's no hurry... just come back you have more space.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(noroom_returned_reply);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/sean_questn_university:s_dcf7aa7a", -- Of course. Here you are.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(noroom_returned_giveitem);

questn_end = ConvoScreen:new {
	id = "questn_end",
	leftDialog = "@conversation/sean_questn_university:s_e656ba0c", -- Good day.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(questn_end);

addConversationTemplate("seanQuestnUniversityConvoTemplate", seanQuestnUniversityConvoTemplate);
