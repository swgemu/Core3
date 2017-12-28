bestineRumor12ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_rumor12:s_9a4ad400", -- There's something more to Sean Trenwell than meets the eye. I'm looking into his past to see what skeletons he's hiding. He's running as the Director of Commerce in the upcoming election. Hopefully, he won't win. But then again, I'm not too fond of Victor Visalis either. You need to vote and find out for yourself. Talk with the governor at the capitol.
	stopConversation = "true",
	options = {}
}
bestineRumor12ConvoTemplate:addScreen(init_election_phase);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_rumor12:s_5028a3e0", -- 	Have you ever seen a Jedi before? I did the other day. He seemed kinda... odd. He was an apprentice, I think, and he was showing off his light saber to someone else. You wouldn't believe it but, out of nowhere he was attacked by bounty hunters... troopers even! He got away, thankfully. I bet he'll be more careful next time.
	stopConversation = "true",
	options = {}
}
bestineRumor12ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineRumor12ConvoTemplate", bestineRumor12ConvoTemplate);
