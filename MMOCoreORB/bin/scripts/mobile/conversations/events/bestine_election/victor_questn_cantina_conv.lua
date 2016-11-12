victorQuestnCantinaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_questn_conv_handler",
	screens = {}
}

convo_start_give = ConvoScreen:new {
	id = "convo_start_give",
	leftDialog = "@conversation/victor_questn_cantina:s_dcb68f7c", -- Yeh, I 'ave what y'need. Y'lookin' fer some sort o'evidence against that Victor Vis'ilis? Wh'evah his name is. He'a been ignorin' our 'illegal' activites fer some time now. He even made'a agreement wit' us, wrote it on'a paper even! Daft, I says. I'll give it to ya iffin' ye pay me... two hunnerd credits.
	stopConversation = "false",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(convo_start_give);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/victor_questn_cantina:s_6307f85c", -- Can' ya'see I'm busy? Get ya' lost!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(no_business);

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/victor_questn_cantina:s_3665cc86", -- Can' ya'see I'm busy? Get ya' lost!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(no_election);

give_item = ConvoScreen:new {
	id = "give_item",
	leftDialog = "@conversation/victor_questn_cantina:s_ac84b134", -- An' here is yer paper. Now, go 'way.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(give_item);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/victor_questn_cantina:s_c70282a3", -- What, yer back? I already gave ya what y'need. If ya ain't gonna put it ta use, don't come cryin' ta me.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(already_has_evidence);

no_room = ConvoScreen:new {
	id = "no_room",
	leftDialog = "@conversation/victor_questn_cantina:s_8a0cf969", -- An' here is yer paper--Uh... ye don' 'ave enough room. Get rid o'yer junk first an' come back fer yer paper.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(no_room);

noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/victor_questn_cantina:s_89278f85", -- Bah, yer back. Ye 'ave enough room yet?
	stopConversation = "false",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(noroom_returned);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/victor_questn_cantina:s_f7347f40", -- Ye still don't 'ave enough room. Stop wastin' ma'time!
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(noroom_returned_noroom);

noroom_returned_reply = ConvoScreen:new {
	id = "noroom_returned_reply",
	leftDialog = "@conversation/victor_questn_cantina:s_36fef8c1", -- Go away then. I've got things to do.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(noroom_returned_reply);

no_money = ConvoScreen:new {
	id = "no_money",
	leftDialog = "@conversation/victor_questn_cantina:s_ff29a83c", -- Yer a cheapskate. Get ya' lost.
	stopConversation = "true",
	options = {}
}
victorQuestnCantinaConvoTemplate:addScreen(no_money);

addConversationTemplate("victorQuestnCantinaConvoTemplate", victorQuestnCantinaConvoTemplate);
