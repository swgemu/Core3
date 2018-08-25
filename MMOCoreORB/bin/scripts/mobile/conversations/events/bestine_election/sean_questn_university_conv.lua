seanQuestnUniversityConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanQuestnUniversityConvoHandler",
	screens = {}
}

init_on_rival_quest = ConvoScreen:new {
	id = "init_on_rival_quest",
	leftDialog = "@conversation/sean_questn_university:s_5788afea", -- I'm in the middle of grading papers. Did you need help with something?
	stopConversation = "false",
	options = {
		{"@conversation/sean_questn_university:s_36904010", "bad_student"}, -- I was told to talk to you about Sean Trenwell.
	}
}
seanQuestnUniversityConvoTemplate:addScreen(init_on_rival_quest);

bad_student = ConvoScreen:new {
	id = "bad_student",
	leftDialog = "@conversation/sean_questn_university:s_7c259594", -- Sean Trenwell... oh yes! I remember him. Unfortunately, he was a particularly bad student. I would always catch him trying to cheat during exams. He barely graduated from the University. In fact, he could even be considered a fake. I really don't want him representing our people in this election.
	stopConversation = "false",
	options = {
		{"@conversation/sean_questn_university:s_5ec23736", "use_as_evidence"}, -- Oh? I could really use your help...
	}
}
seanQuestnUniversityConvoTemplate:addScreen(bad_student);

use_as_evidence = ConvoScreen:new {
	id = "use_as_evidence",
	leftDialog = "@conversation/sean_questn_university:s_799ad811", -- Mmhmm--Oh really? I actually have something that might help you. I think you could use it as evidence. Yes! Here it is. I always keep the grades of my students. Here you are.
	stopConversation = "false",
	options = {
	--{"@conversation/sean_questn_university:s_b9b27823", "good_day"}, -- Thank you.
	}
}
seanQuestnUniversityConvoTemplate:addScreen(use_as_evidence);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/sean_questn_university:s_dac635d2", -- I see that you don't have enough room to get the evidence you seek. Please come back when you have room.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(inv_full);

good_day = ConvoScreen:new {
	id = "good_day",
	leftDialog = "@conversation/sean_questn_university:s_e656ba0c", -- Good day.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(good_day);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/sean_questn_university:s_3c4a2f4", -- I'm too busy to talk right now. I'm grading papers. You seem like you'd be interested in voting at the capitol. They're holding an election.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/sean_questn_university:s_9c880546", -- I hope you've gone to school. We could really use more... educated folks nowadays.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(init_office_phase);

init_has_evidence = ConvoScreen:new {
	id = "init_has_evidence",
	leftDialog = "@conversation/sean_questn_university:s_70145cf1", -- You again. I'm still quite busy, and I see you still have those papers I gave you from Mr. Trenwell's school days. How's this... you leave me to my work, and I won't ask for those back?
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(init_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/sean_questn_university:s_656e8f97", -- I see that you've returned. Do you have enough room now?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_questn_university:s_7e78bf8f", "here_you_are_then"}, -- Yes, can I have the evidence, please?
	--{"@conversation/sean_questn_university:s_7291fe2e", "theres_no_hurry"}, -- Not yet. I still need to make room.
	}
}
seanQuestnUniversityConvoTemplate:addScreen(init_inv_was_full);

theres_no_hurry = ConvoScreen:new {
	id = "theres_no_hurry",
	leftDialog = "@conversation/sean_questn_university:s_b8a92f09", -- I see. I guess there's no hurry... just come back you have more space.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(theres_no_hurry);

was_full_give_evidence = ConvoScreen:new {
	id = "was_full_give_evidence",
	leftDialog = "@conversation/sean_questn_university:s_dcf7aa7a", -- Of course. Here you are.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(was_full_give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/sean_questn_university:s_99711fbf", -- Again, you still don't have enough room. Come back when you do.
	stopConversation = "true",
	options = {}
}
seanQuestnUniversityConvoTemplate:addScreen(inv_still_full);

addConversationTemplate("seanQuestnUniversityConvoTemplate", seanQuestnUniversityConvoTemplate);
