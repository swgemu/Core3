heraldCorellia1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldcorellia1:s_62db6450", -- AHH! Stay away from me! I didn't mean to--oh. You're not a part of Lord Nyax's Clan. What a relief! You scared me there. I am right, aren't I? You're not a spy, are you? ... are you?!
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_7634b077", "no"}, -- No, I'm not.
		{"@conversation/heraldcorellia1:s_fd0eff19", "yes"}, -- I am a part of Lord Nyax's Clan, actually.
	}
}
heraldCorellia1ConvoTemplate:addScreen(init);

no = ConvoScreen:new {
	id = "no",
	leftDialog = "@conversation/heraldcorellia1:s_94914b83", -- I'm glad to hear that. You had me scared there for a little bit.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_4f78edca", "one_of_them"}, -- Why are you so scared of them?
		{"@conversation/heraldcorellia1:s_92abbb2d", "bye"}, -- Yeah, well. Bye.
	}
}
heraldCorellia1ConvoTemplate:addScreen(no);

one_of_them = ConvoScreen:new {
	id = "one_of_them",
	leftDialog = "@conversation/heraldcorellia1:s_2dc5fa6c", -- I was one of them. They don't like the fact that I left just to cash in on their location by providing others with their whereabouts. Say, would you like to know? Free of charge! I also know a little bit about other activities on this planet.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_bb636d95", "loc1"}, -- Sure. Where is Nyax?
		{"@conversation/heraldcorellia1:s_f20cf001", "other_activities"}, -- What other activities?
	}
}
heraldCorellia1ConvoTemplate:addScreen(one_of_them);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldcorellia1:s_15b3396c", -- It's too hard to explain. Besides, someone else could be listening. I don't want them getting the information for free. I downloaded the information into your datapad.
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(loc1);

other_activities = ConvoScreen:new {
	id = "other_activities",
	leftDialog = "@conversation/heraldcorellia1:s_5933dda", -- Well, there's the Afarathu Cave and the Imperial Strong hold. What are you interested in?
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_d004968e", "loc1a"}, -- Uh. Lord Nyax, actually.
		{"@conversation/heraldcorellia1:s_4e268ec", "loc2"}, -- Afarathu Cave.
		{"@conversation/heraldcorellia1:s_ce93e2a4", "loc3"}, -- Imperial Stronghold.
	}
}
heraldCorellia1ConvoTemplate:addScreen(other_activities);

loc1a = ConvoScreen:new {
	id = "loc1a",
	leftDialog = "@conversation/heraldcorellia1:s_1350775c", -- I'm not going to tell you the location outloud. Downloading it into your datapad would be much easier. I hope you find the place with ease.
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(loc1a);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldcorellia1:s_a7c04702", -- I actually don't know the location offhand. Let me see. Hmmm--Ahh! There, downloaded into your datapad. It may or may not be exact. I hope you won't get lost.
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(loc2);

loc3 = ConvoScreen:new {
	id = "loc3",
	leftDialog = "@conversation/heraldcorellia1:s_5bd24f96", -- Be careful there. They don't like visitors unless you're an Imperial. Better than being a Nyax follower! Eh. May as well be the same thing. Oh well! The location has been downloaded into your datapad.
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(loc3);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/heraldcorellia1:s_60613aaf", -- Bye!
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(bye);

yes = ConvoScreen:new {
	id = "yes",
	leftDialog = "@conversation/heraldcorellia1:s_b24dbaa5", -- Hmm... I'm suspicious. You don't look like someone Lord Nyax would recruit. Fine. If you are a part of the clan, then where is the hideout?
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_302a0829", "thought"}, -- Okay, you got me. I'm not a part of the Clan.
		{"@conversation/heraldcorellia1:s_16ef1618", "lies"}, -- Um... West of here!
	}
}
heraldCorellia1ConvoTemplate:addScreen(yes);

thought = ConvoScreen:new {
	id = "thought",
	leftDialog = "@conversation/heraldcorellia1:s_a343f6b2", -- That's what I thought. I knew you weren't. I should know. I was a part of the clan myself. They don't like the fact that I left just to cash in on their location by providing others with their whereabouts. Say, would you like to know? Free of charge! I also know a little bit about other activities on this planet.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_bb636d95", "loc1"}, -- Sure. Where is Nyax?
		{"@conversation/heraldcorellia1:s_f20cf001", "other_activities"}, -- What other activities?
	}
}
heraldCorellia1ConvoTemplate:addScreen(thought);

lies = ConvoScreen:new {
	id = "lies",
	leftDialog = "@conversation/heraldcorellia1:s_43ff531e", -- Lies! I knew you weren't a part of the clan. I should know. I was one of them! I left because I didn't agree with what they were doing.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_14db17db", "not_tell"}, -- What were they doing?
		{"@conversation/heraldcorellia1:s_8487276", "fine"}, -- I don't want to hear your life story.
	}
}
heraldCorellia1ConvoTemplate:addScreen(lies);

not_tell = ConvoScreen:new {
	id = "not_tell",
	leftDialog = "@conversation/heraldcorellia1:s_1abf1335", -- Uhh.. I'm not going to tell you. You'd probably hurt me if I did. I did some of those things, you know. Why don't you go there yourself and find out. Unless, you'd rather do something else on this planet.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_b5cd3612", "loc1a"}, -- I'll check out Nyax's Clan.
		{"@conversation/heraldcorellia1:s_eff34704", "other_activities"}, -- What else is there to do on this planet?
	}
}
heraldCorellia1ConvoTemplate:addScreen(not_tell);

fine = ConvoScreen:new {
	id = "fine",
	leftDialog = "@conversation/heraldcorellia1:s_508d181c", -- Hrmph! Fine! I was going to give you information, but now I'm not going to!
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_7170206c", "hrmph"}, -- Fine! Good bye!
		{"@conversation/heraldcorellia1:s_f4a2753b", "lucky"}, -- Look, I'm sorry.
	}
}
heraldCorellia1ConvoTemplate:addScreen(fine);

hrmph = ConvoScreen:new {
	id = "hrmph",
	leftDialog = "@conversation/heraldcorellia1:s_9d54ab3b", -- Hrmph!
	stopConversation = "true",
	options = {}
}
heraldCorellia1ConvoTemplate:addScreen(hrmph);

lucky = ConvoScreen:new {
	id = "lucky",
	leftDialog = "@conversation/heraldcorellia1:s_abab52df", -- You're lucky I'm desperate for help. I have some information regarding the Nyax Clan and their whereabouts. I also have information about other activities as well.
	stopConversation = "false",
	options = {
		{"@conversation/heraldcorellia1:s_f20cf001", "other_activities"}, -- What other activities?
		{"@conversation/heraldcorellia1:s_8aeb5275", "loc1a"}, -- Where's the Nyax Clan?
	}
}
heraldCorellia1ConvoTemplate:addScreen(lucky);

addConversationTemplate("heraldCorellia1ConvoTemplate", heraldCorellia1ConvoTemplate);
