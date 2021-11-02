neutralTylaJinnConvoTemplate = ConvoTemplate:new {
	initialScreen = "s_382",
	templateType = "Lua",
	luaClassHandler = "neutralTylaJinnConvoHandler",
	screens = {}
}

s_382 = ConvoScreen:new {
	id = "s_382",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_382", -- Can you help me?  Please help me!  My friend's ship is missing and I haven't heard from him.  I'm really worried.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_384", "s_386"} -- What can you tell me about it?
	}
}

neutralTylaJinnConvoTemplate:addScreen(s_382);

s_386 = ConvoScreen:new {
	id = "s_386",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_386", -- He is a merchant and on one of this runs, he disappeared!  I can't imagine what happened!  He's a very good pilot. I don't think that Rori was one of his stops, but that's where his last coordinates say he was.  I'm very worried.
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_neu_quest:s_388", "s_390"} -- I will help you find your friend.
	}
}

neutralTylaJinnConvoTemplate:addScreen(s_386);

s_390 = ConvoScreen:new {
	id = "s_390",
	leftDialog = "@conversation/c_story1_1_neu_quest:s_390", -- Thank you!  I have the coordinates here.  Please bring me back any information you find. I'm so worried about him!
	stopConversation = "true",
	options = {}
}

neutralTylaJinnConvoTemplate:addScreen(s_390);

addConversationTemplate("neutralTylaJinnConvoTemplate", neutralTylaJinnConvoTemplate);
