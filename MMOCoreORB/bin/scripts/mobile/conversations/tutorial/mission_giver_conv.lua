tutorialMissionGiverConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialMissionGiverConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_start", -- What took you so long to get here? The shuttle's ready to leave! Take these release documents to the Quartermaster and get yourself off my space station.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:mission_1_reply_1", "get_moving" }, -- Where is the Quartermaster?
		{ "@newbie_tutorial/newbie_convo:mission_1_reply_2", "get_moving" }, -- Will do!
	}
}
tutorialMissionGiverConvoTemplate:addScreen(intro);

get_moving = ConvoScreen:new {
	id = "get_moving",
	leftDialog = "@newbie_tutorial/newbie_convo:mission_1_waypoint", -- Here are your release documents. Now get moving! The Quartermaster is just down the hall, there.
	stopConversation = "true",
	options = {}
}
tutorialMissionGiverConvoTemplate:addScreen(get_moving);

addConversationTemplate("tutorialMissionGiverConvoTemplate", tutorialMissionGiverConvoTemplate);
