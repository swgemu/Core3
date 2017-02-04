heraldCorellia2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldcorellia2:s_17f4a48e", -- You seem a bit too simple-minded to be a politician. Therefore, you wouldn't be in league with my rival in office. Though... something about you suggests you are an adventurer. You hunger for information. Today is your lucky day for I have such information.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia2:s_34578735", "not_so_fast"}, -- What information?
		{"@conversation/heraldcorellia2:s_365cae75", "run_along"}, -- I... have to go. Good bye!
	}
}
heraldCorellia2ConvoTemplate:addScreen(init);

run_along = ConvoScreen:new {
	id = "run_along",
	leftDialog = "@conversation/heraldcorellia2:s_e8e88020", -- Yes, run along. I have more important things to do.
	stopConversation = "true",
	options = {}
}
heraldCorellia2ConvoTemplate:addScreen(run_along);

not_so_fast = ConvoScreen:new {
	id = "not_so_fast",
	leftDialog = "@conversation/heraldcorellia2:s_9e3a2d26", -- Ahh, I was correct. Not so fast, my friend. I shall not just hand over the information to just anyone. You must promise me something. Promise to have you and your minions, friends, whatever, vote for me in the next election. If you promise and do not fullfill, you will be hunted down, I assure you.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia2:s_e8ba751", "promised"}, -- I promise.
		{"@conversation/heraldcorellia2:s_ae8d99dc", "no_info"}, -- I can't promise anything.
	}
}
heraldCorellia2ConvoTemplate:addScreen(not_so_fast);

no_info = ConvoScreen:new {
	id = "no_info",
	leftDialog = "@conversation/heraldcorellia2:s_cd3a7aff", -- Then, I give you no information. It is as simple as that. Now, run along and go play with your little toy weapons.
	stopConversation = "true",
	options = {}
}
heraldCorellia2ConvoTemplate:addScreen(no_info);

promised = ConvoScreen:new {
	id = "promised",
	leftDialog = "@conversation/heraldcorellia2:s_467e5760", -- You promised too easily and readily. I do not really trust you. Nor, I suppose, can a politician be trusted. You'll have to take this information lightly. I may give you a location that doesn't exist. We're both on even ground now. If forced, I'll wrap you into some elaborate story that will hurt the integrity of my rival. That should do the trick.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia2:s_5f670c9a", "certain_info"}, -- Yeah, yeah. What information do you have?
		{"@conversation/heraldcorellia2:s_fd53304", "bye"}, -- I think I'm going to get out of here.
	}
}
heraldCorellia2ConvoTemplate:addScreen(promised);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/heraldcorellia2:s_b21d503f", -- Ugh. So simple-minded. Breathing your air even dumbs my mind somewhat.
	stopConversation = "true",
	options = {}
}
heraldCorellia2ConvoTemplate:addScreen(bye);

certain_info = ConvoScreen:new {
	id = "certain_info",
	leftDialog = "@conversation/heraldcorellia2:s_7ef6e01", -- I have certain information regarding a meddling band of Rogue Corsec and an insignificant Drall Patriots Hideout.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia2:s_6152d272", "loc1"}, -- Where is the Drall Patriots Hideout?
		{"@conversation/heraldcorellia2:s_6fe071a8", "loc2"}, -- Where is the Rogue Corsec band?
	}
}
heraldCorellia2ConvoTemplate:addScreen(certain_info);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldcorellia2:s_1540303f", -- Over there somewhere. I'm much too busy to tell you straight out. I don't even know why I stopped to talk to you in the first place. You'll find the location has been downloaded into your datapad.
	stopConversation = "true",
	options = {}
}
heraldCorellia2ConvoTemplate:addScreen(loc1);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldcorellia2:s_47d10547", -- I have no clue, really. While campaigning across this forsaken planet, my people came across it. I suppose I can download it into your silly datapad. Now, go. I have an election to win.
	stopConversation = "true",
	options = {}
}
heraldCorellia2ConvoTemplate:addScreen(loc2);

addConversationTemplate("heraldCorellia2ConvoTemplate", heraldCorellia2ConvoTemplate);
