tutorialCelebrityConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialCelebrityConvoHandler",
	screens = {}
}

intro1 = ConvoScreen:new {
	id = "intro1",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy1", -- I can't believe that crazy pirate is dead.
	stopConversation = "true",
	options = {
	}
}
tutorialCelebrityConvoTemplate:addScreen(intro1);

intro2 = ConvoScreen:new {
	id = "intro2",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy2", -- That must have been a tough battle.
	stopConversation = "true",
	options = {
	}
}
tutorialCelebrityConvoTemplate:addScreen(intro2);

intro3 = ConvoScreen:new {
	id = "intro3",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy3", -- I'm sure glad that's over with.
	stopConversation = "true",
	options = {
	}
}
tutorialCelebrityConvoTemplate:addScreen(intro3);

intro4 = ConvoScreen:new {
	id = "intro4",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy4", -- Good thing someone came along to kill that pirate. We'd have been trapped in here forever.
	stopConversation = "true",
	options = {
	}
}
tutorialCelebrityConvoTemplate:addScreen(intro4);

intro5 = ConvoScreen:new {
	id = "intro5",
	leftDialog = "@newbie_tutorial/newbie_convo:celeb_guy5", -- I hate pirates.
	stopConversation = "true",
	options = {
	}
}
tutorialCelebrityConvoTemplate:addScreen(intro5);

addConversationTemplate("tutorialCelebrityConvoTemplate", tutorialCelebrityConvoTemplate);
