victorQuestpHospitalConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questp_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/victor_questp_hospital:s_f2a042d2", -- Are you here to make a donation to the orphanage? We received a huge donation just the other week from a respectable politician. It is truly exciting. Our children can finally get the care they need because of him.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_hospital:s_67a10ef6", "convo_start2"}, -- Who was the politician?
		{"@conversation/victor_questp_hospital:s_58411386", "noDonation"} -- No, I'm not. Good bye.
	}
}
victorQuestpHospitalConvoTemplate:addScreen(convo_start);

noDonation = ConvoScreen:new {
	id = "noDonation",
	leftDialog = "@conversation/victor_questp_hospital:s_2dc62c40", -- Uh... bye! Come back soon! And be sure to make a donation next time!
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(noDonation);

convo_start2 = ConvoScreen:new {
	id = "convo_start2",
	leftDialog = "@conversation/victor_questp_hospital:s_23ac5f59",-- Victor Visalis. He's truly a great man. I wish I could help him in some way for being so generous.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_hospital:s_ad2e138", "convo_start_give"}, -- I know how you can.
		{"@conversation/victor_questp_hospital:s_dafadce6", "questp_end"}, -- Yeah. Anyway, I have to go.
	}
}
victorQuestpHospitalConvoTemplate:addScreen(convo_start2);

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/victor_questp_hospital:s_e0a4222c", -- You do? I'm all ears. Hmm... really? I have just the perfect thing for your evidence. I always keep a sort of personal receipt system for all the donations I've received just so no one will wonder where I keep getting all this money from. Let me make a copy. Hold on a second, will you?
	stopConversation = "false",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(convo_start_give);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/victor_questp_hospital:s_23306eeb", -- With the help from Victor Visalis, the orphanage is safe from the constant Sand People attacks. You should help by defending the people of Bestine.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(no_election);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/victor_questp_hospital:s_4c7aa64d", -- Are you here to make a donation to the orphanage? No? I hear there's an election going on at the capitol. You should go and vote. I know I did.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(no_business);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/victor_questp_hospital:s_34c66631", -- Okay. Here you are. Complete registry and everything. I really hope this helps you in voting for Victor. I wish you well! Tell him I said 'thank you' again.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(give_item);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/victor_questp_hospital:s_7651d151", -- Are you here to make a donation to... oh, I remember you. I gave you a copy of my list of all the donations we've received. Please be sure to let the governor see that... I want her to know about Victor's generosity.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(already_has_evidence);

noroom = ConvoScreen:new {
	id = "noroom",
	leftDialog = "@conversation/victor_questp_hospital:s_b06dcd05", -- Here you are--Oops! Looks like you don't have enough room for this. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(noroom);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/victor_questp_hospital:s_e4d6a9f4", -- Oh, you're back! Do you have enough room to receive your evidence now?
	stopConversation = "false",
	options = {-- PLAYER: Yes, I do."s_90ec63e0"
		-- PLAYER: No, not yet."s_da9a29e9"}
	}
}
victorQuestpHospitalConvoTemplate:addScreen(noroom_returned);

noroom_returned_giveitem = ConvoScreen:new {
	id = "noroom_returned_giveitem",
	leftDialog = "@conversation/victor_questp_hospital:s_90c73952", -- Excellent! Here you are. Be sure to thank Victor for me. Good day!
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(noroom_returned_giveitem);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/victor_questp_hospital:s_46462c3d", -- No, unfortunately, you do not. Please come back when you have enough room to receive the evidence.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(noroom_returned_noroom);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/victor_questp_hospital:s_abdf450b", -- Oh, okay. Come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(noroom_returned_reply);

questp_end = ConvoScreen:new {
	id = "questp_end",
	leftDialog = "@conversation/victor_questp_hospital:s_705d8e7c", -- I wish you well, then.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(questp_end);

addConversationTemplate("victorQuestpHospitalConvoTemplate", victorQuestpHospitalConvoTemplate);
