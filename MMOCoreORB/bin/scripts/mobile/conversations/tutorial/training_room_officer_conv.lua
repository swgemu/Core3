tutorialTrainingRoomOfficerConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "tutorialTrainingRoomOfficerConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_start", -- Good show, in there. You're quite resourceful.
	stopConversation = "false",
	options = {
		{ "@newbie_tutorial/newbie_convo:off_1_reply_1", "go_train_1" }, -- I'd be even better with a little training.
		{ "@newbie_tutorial/newbie_convo:off_1_reply_2", "go_train_2" }, -- Combat isn't really my thing.
	}
}
tutorialTrainingRoomOfficerConvoTemplate:addScreen(intro);

go_train_1 = ConvoScreen:new {
	id = "go_train_1",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_gotrain", -- Well there's someone you should talk to right over there.
	stopConversation = "true",
	options = {}
}
tutorialTrainingRoomOfficerConvoTemplate:addScreen(go_train_1);

go_train_2 = ConvoScreen:new {
	id = "go_train_2",
	leftDialog = "@newbie_tutorial/newbie_convo:off_1_gotrain2", -- Ha ha ha! I suppose not. Hey, there's someone right here you should talk to about that. I bet you could learn something.
	stopConversation = "true",
	options = {}
}
tutorialTrainingRoomOfficerConvoTemplate:addScreen(go_train_2);

addConversationTemplate("tutorialTrainingRoomOfficerConvoTemplate", tutorialTrainingRoomOfficerConvoTemplate);
