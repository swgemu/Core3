heraldLok2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldlok2:s_66d367c9", -- I recognize that swagger in your steps. You're an outcast like me. And, like me, you should know that opposition to your aims and goals are grounds for 'removal'.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_63fbc0e4", "yes"}, -- I agree!
		{"@conversation/heraldlok2:s_7bf56007", "no"}, -- I don't agree with you.
	}
}
heraldLok2ConvoTemplate:addScreen(init);

yes = ConvoScreen:new {
	id = "yes",
	leftDialog = "@conversation/heraldlok2:s_471ddd18", -- Then help me! Help me rid Lok of my opposition so that I may become leader of my own little band of outcasts. I must earn their trust...
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_48566ef9", "why"}, -- What's in it for me?
		{"@conversation/heraldlok2:s_a66ef7ad", "yes2"}, -- I'll help you.
		{"@conversation/heraldlok2:s_d17c998e", "no2"}, -- I don't want to help you.
	}
}
heraldLok2ConvoTemplate:addScreen(yes);

no = ConvoScreen:new {
	id = "no",
	leftDialog = "@conversation/heraldlok2:s_391e8a36", -- I was wrong about you. You're nothing but a commoner. I don't deal with commoners. Go away!
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(no);

no2 = ConvoScreen:new {
	id = "no2",
	leftDialog = "@conversation/heraldlok2:s_657533b5", -- Then leave! I have too many things to do than to waste my time.
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(no2);

yes2 = ConvoScreen:new {
	id = "yes2",
	leftDialog = "@conversation/heraldlok2:s_a9eda6c", -- Excellent! You can start by either plundering the Droid Engineer's Cave or the Smuggler's Ship. Which will it be?
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_4db27a02", "loc1"}, -- Droid Engineer's Cave.
		{"@conversation/heraldlok2:s_7884d24e", "loc2"}, -- Smuggler's Ship.
	}
}
heraldLok2ConvoTemplate:addScreen(yes2);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldlok2:s_f8224468", -- Completely insane, the droid engineer creates minions for his own personal design. We cannot compete with insanity and must find means of removing him from Lok. I wish you luck in the endeavor. It won't be easy.
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(loc1);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldlok2:s_fc5dc465", -- Ahh, the smugglers. They have been a thorn in our side for awhile. Their ground operatives have stolen too many of our missions and goals. For some reason, their ship has been shot down by forces unknown. Looks as if they have more enemies than we thought.
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(loc2);

why = ConvoScreen:new {
	id = "why",
	leftDialog = "@conversation/heraldlok2:s_6cfa2fa7", -- The bounty and riches of my--our!--enemy's strongholds! Just think of it; all the treasure you can fill your deep pockets with! All yours! Just destroy them.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_3f395897", "locs"}, -- Where are these enemies?
		{"@conversation/heraldlok2:s_9be34260", "bye"}, -- It sounds fishy to me. No.
	}
}
heraldLok2ConvoTemplate:addScreen(why);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/heraldlok2:s_46236858", -- I will offer the opportunity to someone else. Unfortunately, it will be your loss.
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(bye);

locs = ConvoScreen:new {
	id = "locs",
	leftDialog = "@conversation/heraldlok2:s_2f559d1", -- It depends. There's the Smuggler's Ship and the Droid Engineer's cave. Which do you prefer to plunder first?
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_7884d24e", "loc2"}, -- Smuggler's Ship.
		{"@conversation/heraldlok2:s_4db27a02", "loc1"}, -- Droid Engineer's Cave.
		{"@conversation/heraldlok2:s_326fcc61", "reason"}, -- What is your reasoning behind this?
	}
}
heraldLok2ConvoTemplate:addScreen(locs);

reason = ConvoScreen:new {
	id = "reason",
	leftDialog = "@conversation/heraldlok2:s_4487b6cf", -- What business is it of yours? Do not question me! Had you the opportunity to become leader of your underground gand of pirates, you too would try to gain your people's trust and rid yourself of the troubles your opposition caused.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_248becfc", "bye2"}, -- I don't like your reasoning.
		{"@conversation/heraldlok2:s_372fb7c1", "locs2"}, -- Okay, okay. What were those places again?
	}
}
heraldLok2ConvoTemplate:addScreen(reason);

bye2 = ConvoScreen:new {
	id = "bye2",
	leftDialog = "@conversation/heraldlok2:s_e4e08f1f", -- Ugh! I have no time for this..
	stopConversation = "true",
	options = {}
}
heraldLok2ConvoTemplate:addScreen(bye2);

locs2 = ConvoScreen:new {
	id = "locs2",
	leftDialog = "@conversation/heraldlok2:s_8247a8b0", -- Smuggler's Ship and the Droid Engineer's Cave.
	stopConversation = "false",
	options = {
		{"@conversation/heraldlok2:s_7884d24e", "loc2"}, -- Smuggler's Ship.
		{"@conversation/heraldlok2:s_4db27a02", "loc1"}, -- Droid Engineer's Cave.
	}
}
heraldLok2ConvoTemplate:addScreen(locs2);

addConversationTemplate("heraldLok2ConvoTemplate", heraldLok2ConvoTemplate);
