victorQuestnCantinaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victorQuestnCantinaConvoHandler",
	screens = {}
}

init_on_rival_quest = ConvoScreen:new {
	id = "init_on_rival_quest",
	leftDialog = "@conversation/victor_questn_cantina:s_dcb68f7c", -- Yeh, I 'ave what y'need. Y'lookin' fer some sort o'evidence against that Victor Vis'ilis? Wh'evah his name is. He'a been ignorin' our 'illegal' activites fer some time now. He even made'a agreement wit' us, wrote it on'a paper even! Daft, I says. I'll give it to ya iffin' ye pay me... two hunnerd credits.
	stopConversation = "false",
	options = {
		--{"@conversation/victor_questn_cantina:s_51ac4991", "great_man"}, -- Hmm. Here you go.
		--{"@conversation/victor_questn_cantina:s_19d90991", "cheapskate"}, -- I don't have that kind of money.
	}
}
victorQuestnCantinaConvoTemplate:addScreen(init_on_rival_quest);

give_evidence = ConvoScreen:new {
	id = "give_evidence",
	leftDialog = "@conversation/victor_questn_cantina:s_ac84b134", -- An' here is yer paper. Now, go 'way.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(give_evidence);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/victor_questn_cantina:s_8a0cf969", -- An' here is yer paper--Uh... ye don' 'ave enough room. Get rid o'yer junk first an' come back fer yer paper.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(inv_full);

cheapskate = ConvoScreen:new {
	id = "cheapskate",
	leftDialog = "@conversation/victor_questn_cantina:s_ff29a83c", -- Yer a cheapskate. Get ya' lost.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(cheapskate);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/victor_questn_cantina:s_6307f85c", -- Can y'see I'm busy? Get ya' lost!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(init_office_phase);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/victor_questn_cantina:s_3665cc86", -- Can' ya'see I'm busy? Get ya' lost!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(init_election_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/victor_questn_cantina:s_c70282a3", -- What, yer back? I already gave ya what y'need. If ya ain't gonna put it ta use, don't come cryin' ta me.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(init_already_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/victor_questn_cantina:s_89278f85", -- Bah, yer back. Ye 'ave enough room yet?
	stopConversation = "false",
	options = {
		--{"@conversation/victor_questn_cantina:s_67a10ef6", ""}, -- Yes, I do.
		--{"@conversation/victor_questn_cantina:s_62bf3631", "go_away_then"}, -- No, I haven't made room yet.
	}
}
victorQuestnCantinaConvoTemplate:addScreen(init_inv_was_full);

was_full_give_evidence = ConvoScreen:new {
	id = "was_full_give_evidence",
	leftDialog = "@conversation/victor_questn_cantina:s_ac84b134", -- An' here is yer paper. Now, go 'way.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(was_full_give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/victor_questn_cantina:s_f7347f40", -- Ye still don't 'ave enough room. Stop wastin' ma'time!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(inv_still_full);

go_away_then = ConvoScreen:new {
	id = "go_away_then",
	leftDialog = "@conversation/victor_questn_cantina:s_36fef8c1", -- Go away then. I've got things to do.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(go_away_then);

addConversationTemplate("victorQuestnCantinaConvoTemplate", victorQuestnCantinaConvoTemplate);