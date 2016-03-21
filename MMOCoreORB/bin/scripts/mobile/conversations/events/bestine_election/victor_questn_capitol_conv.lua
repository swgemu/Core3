victorQuestnCapitolConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victor_questn_capitol_conv_handler",
	screens = {}
}

no_election = ConvoScreen:new {
	id = "no_election",
	leftDialog = "@conversation/victor_questn_capitol:s_c1bf1629", -- You'd be wise to join the Empire. The Rebel Alliance and its members have spiraled out of control. We're going to stomp them out of existence.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(no_election);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/victor_questn_capitol:s_7dcdb445", -- There is an election going on at the capitol. You should participate. Otherwise... move along, citizen.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(no_business);

already_has_evidence = ConvoScreen:new {
	id = "already_has_evidence",
	leftDialog = "@conversation/victor_questn_capitol:s_f688af52", --Move along... oh, it's you again. Why haven't you used that list I gave... er... I mean, that you found... against Victor? Arrrgh! I was in a good mood after giving that to you, but now I'm upset again. Just go take care of it already.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(already_has_evidence);


no_room = ConvoScreen:new {
	id = "no_room",
	leftDialog = "@conversation/victor_questn_capitol:s_d2df4599", --I could help you... if you had enough room. Come back when you do and we'll talk.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(no_room);


noroom_returned = ConvoScreen:new {
	id = "noroom_returned",
	leftDialog = "@conversation/victor_questn_capitol:s_f62e5a7d", -- Ah, you're back. Do you have enough room this time to get your precious evidence?
	stopConversation = "false",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(noroom_returned);

noroom_returned_notyet = ConvoScreen:new {
	id = "noroom_returned_notyet",
	leftDialog = "@conversation/victor_questn_capitol:s_42deb08e", --Wasting my time is not a smart idea...
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(noroom_returned_notyet);

noroom_returned_fullinv = ConvoScreen:new {
	id = "noroom_returned_fullinv",
	leftDialog = "@conversation/victor_questn_capitol:s_99ef56dc", --No, you don't. Again, come back when you do. And next time, you'd better not waste my time.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(noroom_returned_fullinv);


convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/victor_questn_capitol:s_4d313a", -- You're not supposed to be hanging around here, citizen. Move along.
	stopConversation = "false",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(convo_start);

im_leaving = ConvoScreen:new {
	id = "im_leaving",
	leftDialog = "@conversation/victor_questn_capitol:s_11cdd7b1", --And it would be best, for your health, not to come back.
	stopConversation = "true",
	options = { }
}
victorQuestnCapitolConvoTemplate:addScreen(im_leaving);

give_list = ConvoScreen:new {
	id = "give_list",
	leftDialog = "@conversation/victor_questn_capitol:s_ce8d51fb", --Look-oh? Looking for evidence, are you? I may be able to help with that. It would be a perfect opportunity to get even with that Victor fellow. Never mind the details. Here, you might find this... 'list' entertaining. Be sure to say that you 'found' it.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questn_capitol:s_b9b27823","givelist_end"}, --Thank you.
	}
}
victorQuestnCapitolConvoTemplate:addScreen(give_list);

givelist_end = ConvoScreen:new {
	id = "givelist_end",
	leftDialog = "@conversation/victor_questn_capitol:s_d638d2ec", --Move along.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(givelist_end);

noroom_returned_givelist = ConvoScreen:new {
	id = "noroom_returned_givelist",
	leftDialog = "@conversation/victor_questn_capitol:s_6ddb06b2", -- And here you are. Now... get lost.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(noroom_returned_givelist);


addConversationTemplate("victorQuestnCapitolConvoTemplate", victorQuestnCapitolConvoTemplate);
