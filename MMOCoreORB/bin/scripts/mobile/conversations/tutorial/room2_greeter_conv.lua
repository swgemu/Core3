tutorialRoomTwoGreeterConvoTemplate = ConvoTemplate:new {
	initialScreen = "intro",
	templateType = "Lua",
	luaClassHandler = "tutorialRoomTwoGreeterConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_start", -- That's more like it. Well, I'm your supply disbursement officer. I don't see why we should waste good supplies on refugees like you.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_1", "all_the_same"}, -- What happened?
		{"@newbie_tutorial/newbie_convo:convo_1_reply_2", "in_the_drum"}, -- What supplies?
	}
}

tutorialRoomTwoGreeterConvoTemplate:addScreen(intro);

all_the_same = ConvoScreen:new {
	id = "all_the_same",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_more", -- You people, you're all the same. Look, you were on a ship with dubious credentials. The Star Destroyer hailed you, and you didn't stop fast enough. So they boarded, and brought the survivors over here.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_1_reply_3", "they_were_dissidents"}, -- The survivors? You mean the Empire killed civilian passengers?
	}
}

tutorialRoomTwoGreeterConvoTemplate:addScreen(all_the_same);

in_the_drum = ConvoScreen:new {
	id = "in_the_drum",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_stuff", -- There's some stuff left that the other refugees didn't take. Not much though. In the drum right here.
	stopConversation = "true",
	options = {}
}

tutorialRoomTwoGreeterConvoTemplate:addScreen(in_the_drum);

they_were_dissidents = ConvoScreen:new {
	id = "they_were_dissidents",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_1_explain", -- They weren't civilians. They were dissidents. Officially, anyway. Now, go get your free supplies from this drum right here, courtesy of the generosity of the Empire.
	stopConversation = "true",
	options = {}
}

tutorialRoomTwoGreeterConvoTemplate:addScreen(they_were_dissidents);

addConversationTemplate("tutorialRoomTwoGreeterConvoTemplate", tutorialRoomTwoGreeterConvoTemplate);
