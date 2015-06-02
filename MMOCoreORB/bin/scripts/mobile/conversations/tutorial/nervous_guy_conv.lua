tutorialNervousGuyConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialNervousGuyConvoHandler",
	screens = {}
}

intro1 = ConvoScreen:new {
	id = "intro1",
	leftDialog = "@newbie_tutorial/newbie_convo:nervous_guy1", -- You couldn't PAY me to go down that hallway!
	stopConversation = "true",
	options = {
	}
}
tutorialNervousGuyConvoTemplate:addScreen(intro1);

intro2 = ConvoScreen:new {
	id = "intro2",
	leftDialog = "@newbie_tutorial/newbie_convo:nervous_guy2", -- That pirate is crazy! He blocked up the hallway and threatens anyone that goes near him!
	stopConversation = "true",
	options = {
	}
}
tutorialNervousGuyConvoTemplate:addScreen(intro2);

intro3 = ConvoScreen:new {
	id = "intro3",
	leftDialog = "@newbie_tutorial/newbie_convo:nervous_guy3", -- I bet the Empire will send him to the spice mines on Kessel
	stopConversation = "true",
	options = {
	}
}
tutorialNervousGuyConvoTemplate:addScreen(intro3);

intro4 = ConvoScreen:new {
	id = "intro4",
	leftDialog = "@newbie_tutorial/newbie_convo:nervous_guy4", -- You can't be thinking of going down that hallway?! Didn't you hear? CRAZY PIRATE ON THE LOOSE!
	stopConversation = "true",
	options = {
	}
}
tutorialNervousGuyConvoTemplate:addScreen(intro4);

intro5 = ConvoScreen:new {
	id = "intro5",
	leftDialog = "@newbie_tutorial/newbie_convo:nervous_guy5", -- I wish I could go home...
	stopConversation = "true",
	options = {
	}
}
tutorialNervousGuyConvoTemplate:addScreen(intro5);

addConversationTemplate("tutorialNervousGuyConvoTemplate", tutorialNervousGuyConvoTemplate);
