padawan_politician_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_politician_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_politician_01:s_e16a4410", -- Hello there, you are a perfect match for a quick and dirty job I need done to help the citizens of this fair city. Not to mention help boost my image in the next election.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_60ba5013", "predators_in_area"}, -- What kind of quick and dirty job are we talking about?
		{"@conversation/padawan_politician_01:s_82367ff2", "real_shame"} -- Keep your problems to yourself. What makes you think I'd care.
	}
}
padawan_politician_01_convo_template:addScreen(intro);

predators_in_area = ConvoScreen:new {
	id = "predators_in_area",
	leftDialog = "@conversation/padawan_politician_01:s_10204c5e", -- As folks in these parts know, more than our fair share of predators roam the area outside of the city limits.  What I need you to do my bright eyed adventuring friend is head out into this untamed region and destroy a bloodseeker mite that has been causing no end of trouble.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_6299309e", "uploaded_waypoint"}, -- Of course.  Give me the location, and consider it done.
		{"@conversation/padawan_politician_01:s_de8ec7cf", "real_shame"} -- Fight your own battles. And find someone who cares.
	}
}
padawan_politician_01_convo_template:addScreen(predators_in_area);

uploaded_waypoint = ConvoScreen:new {
	id = "uploaded_waypoint",
	leftDialog = "@conversation/padawan_politician_01:s_e01d17e1", -- Ahh, just as stup.. err. brave as I suspected. I have uploaded a waypoint to your datapad with the location of a known hunting ground of this creature. Return to me when the bloodseeker mite has been eliminated.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(uploaded_waypoint);

real_shame = ConvoScreen:new {
	id = "real_shame",
	leftDialog = "@conversation/padawan_politician_01:s_c61129a3", -- That's a real shame.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(real_shame);

intro_killed_target = ConvoScreen:new {
	id = "intro_killed_target",
	leftDialog = "@conversation/padawan_politician_01:s_59b6aab3", -- Has the bloodseeker mite been taken care of?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_dc3b8fc5", "thank_you"}, -- Yes, it has.
	}
}
padawan_politician_01_convo_template:addScreen(intro_killed_target);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/padawan_politician_01:s_4fc89968", -- Excellent, thank you for your services friend.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(thank_you);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_politician_01:s_4eb51131", -- That was quick... did you make the countryside a safer place?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_d30e03d9", "such_enthusiasm"}, -- "Not yet, but believe me they will."
		{"@conversation/padawan_politician_01:s_99bdf01", "real_shame"} -- I decided to make myself a safer place. Go deal with it yourself.
	}
}
padawan_politician_01_convo_template:addScreen(intro_in_progress);

such_enthusiasm = ConvoScreen:new {
	id = "such_enthusiasm",
	leftDialog = "@conversation/padawan_politician_01:s_e6b7fdc0", -- Excellent. Such enthusiasm in one's work is always a pleasure to behold.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(such_enthusiasm);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_politician_01:s_dbf5765a", -- Ah good. My election into office is almost certainly assured once I take credit for... er... I mean, let the people know about the service you've provided.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_politician_01:s_badba8f2", -- Greetings and be welcome. Remember my motto: voting once is nice; voting often is better.
	stopConversation = "true",
	options = {}
}
padawan_politician_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_politician_01_convo_template", padawan_politician_01_convo_template);

