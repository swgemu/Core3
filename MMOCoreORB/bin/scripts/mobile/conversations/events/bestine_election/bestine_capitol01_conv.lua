bestineCapitol01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestineRumorConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/bestine_capitol01:s_f9dda042", -- 	You look a little lost. Or have you come to the capitol to vote in the upcoming election? Confused? You haven't heard of the changes to Bestine? I thought everyone had heard of it! Must be an outsider. Oh well! Do you want to hear about it?
	stopConversation = "false",
	options = {
		{"@conversation/bestine_capitol01:s_f660c800", "appointing_someone"}, -- Yes, please.
		{"@conversation/bestine_capitol01:s_90ce1297", "a_pity"}, -- No, thank you.
	}
}
bestineCapitol01ConvoTemplate:addScreen(init_election_phase);

appointing_someone = ConvoScreen:new {
	id = "appointing_someone",
	leftDialog = "@conversation/bestine_capitol01:s_8819f19f", -- The governor is appointing someone to work closely with her on a new project. Currently, the only two candidates eligible are Victor Visalis, Officer of Defense and Sean Trenwell, Director of Commerce. You'll probably have to speak with the governor for more information about the voting process and further details. Unfortunately, I have to get back to work.
	stopConversation = "true",
	options = {}
}
bestineCapitol01ConvoTemplate:addScreen(appointing_someone);

a_pity = ConvoScreen:new {
	id = "a_pity",
	leftDialog = "@conversation/bestine_capitol01:s_edaf838a", -- That's a pity. Okay, then. Have a good day!
	stopConversation = "true",
	options = {}
}
bestineCapitol01ConvoTemplate:addScreen(a_pity);

init_office_phase = ConvoScreen:new {
	id = "init_office_phase",
	leftDialog = "@conversation/bestine_capitol01:s_da5842cb", -- Another election should be coming up in the following months. I wonder who will win and what effects it will have on the city of Bestine. You should probably keep an eye out for upcoming announcements.
	stopConversation = "true",
	options = {}
}
bestineCapitol01ConvoTemplate:addScreen(init_office_phase);

addConversationTemplate("bestineCapitol01ConvoTemplate", bestineCapitol01ConvoTemplate);
