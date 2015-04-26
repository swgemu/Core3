tutorialQuartermasterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialQuartermasterConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_1_start", -- Ah! I see you have the proper documents there. I'll just take those from you.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:quarter_1_reply_1", "you_may_leave" }, -- Can I leave now?
		{ "@newbie_tutorial/newbie_convo:quarter_1_reply_2", "you_may_leave" }, -- Where are you sending me?
	}
}
tutorialQuartermasterConvoTemplate:addScreen(intro);

intro_nodocs = ConvoScreen:new {
	id = "intro_nodocs",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_nodocs", -- You don't have your release papers? Well you'd better go get them from the Corporal. Make it snappy! Hup! Hup!
	stopConversation = "true",
	options = {}
}
tutorialQuartermasterConvoTemplate:addScreen(intro_nodocs)

you_may_leave = ConvoScreen:new {
	id = "you_may_leave",
	leftDialog = "@newbie_tutorial/newbie_convo:quarter_1_go_nochoice", -- You may use the travel terminal here and be on your way. And don't worry about the cost of transportation, the Empire will be picking up the tab on this one.
	stopConversation = "true",
	options = {}
}
tutorialQuartermasterConvoTemplate:addScreen(you_may_leave);

addConversationTemplate("tutorialQuartermasterConvoTemplate", tutorialQuartermasterConvoTemplate);
