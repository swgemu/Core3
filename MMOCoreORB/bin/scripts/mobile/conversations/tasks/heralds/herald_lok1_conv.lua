heraldLok1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldlok:s_599fe081", -- You do not seem to be apart of the Empire. Ha! As if I care what affiliation you belong to. I left the Alliance years ago, but... I left with a bit of information regarding the location of certain points of interest. Are you interested in what I have to say?
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok:s_36a4e374", "yes"}, -- Yes, I am.
		{"@conversation/heraldlok:s_c5a66e82", "no"}, -- No, not really.
	}
}
heraldLok1ConvoTemplate:addScreen(init);

yes = ConvoScreen:new {
	id = "yes",
	leftDialog = "@conversation/heraldlok:s_ff7f26e1", -- I knew you were hungry for information. Which location do you want to hear about? I have information regarding the 'Kimogila Town', and 'Canyon Corsair Stronghold'. They are all interesting places, I assure you.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok:s_95bfd0f3", "loc1"}, -- Kimogila Town.
		{"@conversation/heraldlok:s_434a59e6", "loc2"}, -- Canyon Corsair Stronghold.
		{"@conversation/heraldlok:s_5e804346", "why"}, -- Why are you telling me this information?
	}
}
heraldLok1ConvoTemplate:addScreen(yes);

no = ConvoScreen:new {
	id = "no",
	leftDialog = "@conversation/heraldlok:s_6336e957", -- Suit yourself. I'll wait for someone else. My information is worth alot of credits to many people.
	stopConversation = "true",
	options = {}
}
heraldLok1ConvoTemplate:addScreen(no);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldlok:s_a5343515", -- You'd be daft if you wanted to go there. Nonetheless, it's your life, not mine. I can give you the general location of the place, but the exact location was corrupted in my database. I'll download the information into your datapad, but that's all I can do.
	stopConversation = "true",
	options = {}
}
heraldLok1ConvoTemplate:addScreen(loc1);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldlok:s_be60eda6", -- I hope you have several friends with you. Now, granted, I haven't really been to any of these places, but... I've heard things. Enough of my babble. I'll download the general location into your datapad. It's not exact, but close enough.
	stopConversation = "true",
	options = {}
}
heraldLok1ConvoTemplate:addScreen(loc2);

why = ConvoScreen:new {
	id = "why",
	leftDialog = "@conversation/heraldlok:s_e933930f", -- I used to be apart of the Rebel Alliance Spy Network, but I decided that my skills were needed elsewhere. I collected information for them regarding the activity on Lok. Obviously, they didn't like the fact that their systems were easy to hack. I left on the account of 'unresolved differances'. Err--why am I telling you this?
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok:s_a8387526", "bye"}, -- I, uh, really need to go.
		{"@conversation/heraldlok:s_119ff40f", "locs"}, -- How about those locations again?
	}
}
heraldLok1ConvoTemplate:addScreen(why);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/heraldlok:s_7117043f", -- Okay. Good bye!
	stopConversation = "true",
	options = {}
}
heraldLok1ConvoTemplate:addScreen(bye);

locs = ConvoScreen:new {
	id = "locs",
	leftDialog = "@conversation/heraldlok:s_57d2d366", -- Oh, so now you want to hear about them. Fine. Which do you want to hear about? I have information regarding the 'Kimogila Town', and 'Canyon Corsair Stronghold'.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok:s_95bfd0f3", "loc1"}, -- Kimogila Town.
		{"@conversation/heraldlok:s_434a59e6", "loc2"}, -- Canyon Corsair Stronghold.
	}
}
heraldLok1ConvoTemplate:addScreen(locs);

addConversationTemplate("heraldLok1ConvoTemplate", heraldLok1ConvoTemplate);
