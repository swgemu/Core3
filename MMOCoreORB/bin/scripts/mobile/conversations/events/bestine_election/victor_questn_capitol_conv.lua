victorQuestnCapitolConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victorQuestnCapitolConvoHandler",
	screens = {}
}

init_on_rival_quest = ConvoScreen:new {
	id = "init_on_rival_quest",
	leftDialog = "@conversation/victor_questn_capitol:s_4d313a", -- You're not supposed to be hanging around here, citizen. Move along.
	stopConversation = "false",
	options = {
		{"@conversation/victor_questn_capitol:s_496168b6", "looking_for_evidence"}, -- I need your help...
	}
}
victorQuestnCapitolConvoTemplate:addScreen(init_on_rival_quest);

looking_for_evidence = ConvoScreen:new {
	id = "looking_for_evidence",
	leftDialog = "@conversation/victor_questn_capitol:s_ce8d51fb", -- Look-oh? Looking for evidence, are you? I may be able to help with that. It would be a perfect opportunity to get even with that Victor fellow. Never mind the details. Here, you might find this... 'list' entertaining. Be sure to say that you 'found' it.
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questn_capitol:s_b9b27823", ""}, -- Thank you.
	}
}
victorQuestnCapitolConvoTemplate:addScreen(looking_for_evidence);

give_evidence = ConvoScreen:new {
	id = "give_evidence",
	leftDialog = "@conversation/victor_questn_capitol:s_d638d2ec", -- Move along.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(give_evidence);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/victor_questn_capitol:s_d2df4599", -- I could help you... if you had enough room. Come back when you do and we'll talk.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(inv_full);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/victor_questn_capitol:s_c1bf1629", -- You'd be wise to join the Empire. The Rebel Alliance and its members have spiraled out of control. We're going to stomp them out of existence.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(init_office_phase);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/victor_questn_capitol:s_7dcdb445", -- There is an election going on at the capitol. You should participate. Otherwise... move along, citizen.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(init_election_phase);

init_already_has_evidence = ConvoScreen:new {
	id = "init_already_has_evidence",
	leftDialog = "@conversation/victor_questn_capitol:s_f688af52", -- Move along... oh, it's you again. Why haven't you used that list I gave... er... I mean, that you found... against Victor? Arrrgh! I was in a good mood after giving that to you, but now I'm upset again. Just go take care of it already.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(init_already_has_evidence);

init_inv_was_full = ConvoScreen:new {
	id = "init_inv_was_full",
	leftDialog = "@conversation/victor_questn_capitol:s_f62e5a7d", -- Ah, you're back. Do you have enough room this time to get your precious evidence?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_questn_capitol:s_90ec63e0", "great_man"}, -- Yes, I do.
	--{"@conversation/victor_questn_capitol:s_da9a29e9", "wasting_my_time"}, -- No, not yet.
	}
}
victorQuestnCapitolConvoTemplate:addScreen(init_inv_was_full);

was_full_give_evidence = ConvoScreen:new {
	id = "was_full_give_evidence",
	leftDialog = "@conversation/victor_questn_capitol:s_6ddb06b2", -- And here you are. Now... get lost.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(was_full_give_evidence);

inv_still_full = ConvoScreen:new {
	id = "inv_still_full",
	leftDialog = "@conversation/victor_questn_capitol:s_99ef56dc", -- No, you don't. Again, come back when you do. And next time, you'd better not waste my time.
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(inv_still_full);

wasting_my_time = ConvoScreen:new {
	id = "wasting_my_time",
	leftDialog = "@conversation/victor_questn_capitol:s_42deb08e", -- Wasting my time is not a smart idea...
	stopConversation = "true",
	options = {}
}
victorQuestnCapitolConvoTemplate:addScreen(wasting_my_time);

addConversationTemplate("victorQuestnCapitolConvoTemplate", victorQuestnCapitolConvoTemplate);
