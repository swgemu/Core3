imperial_retreat_governor_grayed_wintozzen_convotemplate = ConvoTemplate:new {
	initialScreen = "gov_initial",
	templateType = "Normal",
	--luaClassHandler = "imperial_retreat_governor_grayed_wintozzen_convo_handler",
	screens = {}
}


gov_initial = ConvoScreen:new {
	id = "gov_initial",
	leftDialog = "@kaja_newbie_quest_1:gov1", --Excuse me?
	stopConversation = "false",
	options = {
		{"@kaja_newbie_quest_1:gov1_reply1","gov_escort_1"} --Kaja sent me to escort you to your ship.
	}
}


imperial_retreat_governor_grayed_wintozzen_convotemplate:addScreen(gov_initial);


gov_escort_1 = ConvoScreen:new {
	id = "gov_escort_1",
	leftDialog = "@kaja_newbie_quest_1:gov2", --Let's get going then.  Lead the way.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_governor_grayed_wintozzen_convotemplate:addScreen(gov_escort_1);


addConversationTemplate("imperial_retreat_governor_grayed_wintozzen_convotemplate",imperial_retreat_governor_grayed_wintozzen_convotemplate);
