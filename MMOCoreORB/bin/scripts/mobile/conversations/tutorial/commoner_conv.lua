commoner_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "commoner_handler",
	screens = {}
}

commoner_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@newbie_tutorial/newbie_convo:leave_me_alone",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen1);

commoner_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy1",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen2);

commoner_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy4",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen3);

commoner_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy3",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen4);

commoner_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy2",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen5);

commoner_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy5",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen6);

commoner_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	--someone knows what he's actually supposed to say, please fix it
	leftDialog = "@npc_reaction/stormtrooper:hi_mid_14",
	stopConversation = "true",
	options = {
	}
}

commoner_convotemplate:addScreen(commoner_convoscreen7);

addConversationTemplate("commoner_convotemplate", commoner_convotemplate);
