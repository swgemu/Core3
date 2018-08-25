victorQuestpHospitalConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victorQuestpHospitalConvoHandler",
	screens = {}
}

init_joined_victor = ConvoScreen:new {
	id = "init_joined_victor",
	leftDialog = "@conversation/victor_questp_hospital:s_f2a042d2", -- Are you here to make a donation to the orphanage? We received a huge donation just the other week from a respectable politician. It is truly exciting. Our children can finally get the care they need because of him.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_hospital:s_67a10ef6", "great_man"}, -- Who was the politician?
	}
}
victorQuestpHospitalConvoTemplate:addScreen(init_joined_victor);

great_man = ConvoScreen:new {
	id = "great_man",
	leftDialog = "@conversation/victor_questp_hospital:s_23ac5f59", -- Victor Visalis. He's truly a great man. I wish I could help him in some way for being so generous.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questp_hospital:s_ad2e138", "perfect_thing"}, -- I know how you can.
	}
}
victorQuestpHospitalConvoTemplate:addScreen(great_man);

perfect_thing = ConvoScreen:new {
	id = "perfect_thing",
	leftDialog = "@conversation/victor_questp_hospital:s_e0a4222c", -- You do? I'm all ears. Hmm... really? I have just the perfect thing for your evidence. I always keep a sort of personal receipt system for all the donations I've received just so no one will wonder where I keep getting all this money from. Let me make a copy. Hold on a second, will you?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questp_hospital:s_67e6df55", "give_evidence"}, -- Okay.
	}
}
victorQuestpHospitalConvoTemplate:addScreen(perfect_thing);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/victor_questp_hospital:s_b06dcd05", -- Here you are--Oops! Looks like you don't have enough room for this. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(inv_full);

give_evidence = ConvoScreen:new {
	id = "give_evidence",
	leftDialog = "@conversation/victor_questp_hospital:s_34c66631", -- Okay. Here you are. Complete registry and everything. I really hope this helps you in voting for Victor. I wish you well! Tell him I said 'thank you' again.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(give_evidence);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/victor_questp_hospital:s_4c7aa64d", -- Are you here to make a donation to the orphanage? No? I hear there's an election going on at the capitol. You should go and vote. I know I did.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/victor_questp_hospital:s_23306eeb", -- With the help from Victor Visalis, the orphanage is safe from the constant Sand People attacks. You should help by defending the people of Bestine.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(init_office_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/victor_questp_hospital:s_7651d151", -- Are you here to make a donation to... oh, I remember you. I gave you a copy of my list of all the donations we've received. Please be sure to let the governor see that... I want her to know about Victor's generosity.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(init_already_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/victor_questp_hospital:s_e4d6a9f4", -- Oh, you're back! Do you have enough room to receive your evidence now?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questp_hospital:s_90ec63e0", ""}, -- Yes, I do.
	--{"@conversation/victor_questp_hospital:s_da9a29e9", "come_back"}, -- No, not yet.
	}
}
victorQuestpHospitalConvoTemplate:addScreen(init_inv_was_full);

was_full_give_evidence = ConvoScreen:new {
	id = "was_full_give_evidence",
	leftDialog = "@conversation/victor_questp_hospital:s_90c73952", -- Excellent! Here you are. Be sure to thank Victor for me. Good day!
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(was_full_give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/victor_questp_hospital:s_46462c3d", -- No, unfortunately, you do not. Please come back when you have enough room to receive the evidence.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(inv_still_full);

come_back = ConvoScreen:new {
	id = "come_back",
	leftDialog = "@conversation/victor_questp_hospital:s_abdf450b", -- Oh, okay. Come back when you do.
	stopConversation = "true",
	options = {}
}
victorQuestpHospitalConvoTemplate:addScreen(come_back);

addConversationTemplate("victorQuestpHospitalConvoTemplate", victorQuestpHospitalConvoTemplate);
