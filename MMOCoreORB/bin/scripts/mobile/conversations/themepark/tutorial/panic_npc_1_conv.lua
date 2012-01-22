panic_npc_1_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Normal",
	screens = {}
}

panic_npc_1_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:shout_panic4",
	stopConversation = "true",
	options = {
	}
}

panic_npc_1_convotemplate:addScreen(panic_npc_1_convoscreen1);

addConversationTemplate("panic_npc_1_convotemplate", panic_npc_1_convotemplate);
