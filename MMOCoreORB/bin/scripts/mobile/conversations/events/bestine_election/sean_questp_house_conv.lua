seanQuestpHouseConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanQuestpHouseConvoHandler",
	screens = {}
}

init_not_election_phase = ConvoScreen:new {
	id = "init_not_election_phase",
	leftDialog = "@conversation/sean_questp_house:s_2267c63c", -- I'm so busy. Sean is planning to run for the new election that will happen soon. He's going to have tons of people over for dinner in hopes of impressing them. I really must get back to work. I'm sorry.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(init_not_election_phase);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/sean_questp_house:s_d066eb10", -- Hello! Are you here to discuss the election? You haven't heard about it? You should really go to the capitol. The governor is taking votes.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(init_election_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/sean_questp_house:s_41f6594d", -- Oh hello! I'm surprised to see you again so soon. Please be sure to sure to show the governor the testimony I wrote for you. I want her to know what a kind and generous person Sean is.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(init_already_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/sean_questp_house:s_20b8d563", -- I'm glad you're back. Do you have enough room now?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_questp_house:s_e69937da", "here_you_are_then"}, -- Yes. Thank you.
	--{"@conversation/sean_questp_house:s_48b343d3", "return_when_done"}, -- Actually, no I don't.
	}
}
seanQuestpHouseConvoTemplate:addScreen(init_inv_was_full);

return_when_done = ConvoScreen:new {
	id = "return_when_done",
	leftDialog = "@conversation/sean_questp_house:s_d6d23166", -- Well, return when you do. I'll be happy to give it to you then.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(return_when_done);

here_you_are_then = ConvoScreen:new {
	id = "here_you_are_then",
	leftDialog = "@conversation/sean_questp_house:s_9e4a0794", -- Here you are, then. I hope you have a wonderful day.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(here_you_are_then);

still_no_room = ConvoScreen:new {
	id = "still_no_room",
	leftDialog = "@conversation/sean_questp_house:s_bd542a54", -- You still don't have enough room. Come back when you do. I'd be happy to give it to you then.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(still_no_room);

init_joined_sean = ConvoScreen:new {
	id = "init_joined_sean",
	leftDialog = "@conversation/sean_questp_house:s_f6effab8", -- Oh my! I didn't expect visitors today! This place is a complete mess! Please forgive me. The last of the tragedy victims left. They all found new homes. I'm just cleaning up. Why are you here?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_house:s_34f710c5", "empire_rampage"}, -- What victims?
		{"@conversation/sean_questp_house:s_51c40792", "always_welcome"}, -- I'm in the wrong house. Sorry!
	}
}
seanQuestpHouseConvoTemplate:addScreen(init_joined_sean);

empire_rampage = ConvoScreen:new {
	id = "empire_rampage",
	leftDialog = "@conversation/sean_questp_house:s_8a9c6889", -- Oh, you didn't hear? The Empire went on a rampage and destroyed one of the newer, smaller cities assumed to harbor Rebel operatives. Those poor people. Sean Trenwell opened his homes for the survivors. He's such a kind man.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questp_house:s_ab4c4ff8", "write_a_testimony"}, -- Really? Can you help me with something?
	}
}
seanQuestpHouseConvoTemplate:addScreen(empire_rampage);

write_a_testimony = ConvoScreen:new {
	id = "write_a_testimony",
	leftDialog = "@conversation/sean_questp_house:s_43e36f6f", -- Sure, I can try. What do you need? Write a testimony? Of course, I will! Anything to help him with this election. I really hope he wins. He deserves it. Let me write it up..
	stopConversation = "false",
	options = {
	--{"@conversation/sean_questp_house:s_67e6df55", ""}, -- Okay.
	}
}
seanQuestpHouseConvoTemplate:addScreen(write_a_testimony);

come_for_dinner = ConvoScreen:new {
	id = "come_for_dinner",
	leftDialog = "@conversation/sean_questp_house:s_47e61b76", -- Here you are. Please let me know if you'd like to come over for dinner sometime. I'm a great cook! Have a great day!
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(come_for_dinner);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/sean_questp_house:s_198905a5", -- Here you are--Oh no! You don't have enough room. I'm sorry. Please come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(inv_full);

always_welcome = ConvoScreen:new {
	id = "always_welcome",
	leftDialog = "@conversation/sean_questp_house:s_d5702a3b", -- Come back any time. You're always welcome in the Trenwell house.
	stopConversation = "true",
	options = {}
}
seanQuestpHouseConvoTemplate:addScreen(always_welcome);

addConversationTemplate("seanQuestpHouseConvoTemplate", seanQuestpHouseConvoTemplate);
