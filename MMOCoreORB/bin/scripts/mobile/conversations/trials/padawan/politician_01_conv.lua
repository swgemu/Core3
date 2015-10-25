trialsPadawanPolitician01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanPolitician01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_politician_01:s_e16a4410", -- Hello there, you are a perfect match for a quick and dirty job I need done to help the citizens of this fair city. Not to mention help boost my image in the next election.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_60ba5013", "more"}, -- What kind of quick and dirty job are we talking about?
		{"@conversation/padawan_politician_01:s_82367ff2", "not_more"} -- Keep your problems to yourself. What makes you think I'd care.
	}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(intro);

more = ConvoScreen:new {
	id = "more",
	leftDialog = "@conversation/padawan_politician_01:s_10204c5e", -- As folks in these parts know, more than our fair share of predators roam the area outside of the city limits. What I need you to do my bright eyed adventuring friend is head out into this untamed region and destroy a bloodseeker mite that has been causing no end of trouble. Think you're capable?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_6299309e", "continue"}, -- Of course. Give me the location, and consider it done.
		{"@conversation/padawan_politician_01:s_de8ec7cf", "not_more"} -- Fight your own battles. And find someone who cares.
	}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(more);

not_more = ConvoScreen:new {
	id = "not_more",
	leftDialog = "@conversation/padawan_politician_01:s_c61129a3", -- That's a real shame.
	stopConversation = "true",
	options = {}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(not_more);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_politician_01:s_e01d17e1", -- Ahh, just as stup.. err. brave as I suspected. I have uploaded a waypoint to your datapad with the location of a known hunting ground of this creature. Return to me when the bloodseeker mite has been eliminated.
	stopConversation = "true",
	options = {}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(continue);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_politician_01:s_4eb51131", -- That was quick... did you make the countryside a safer place?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_d30e03d9", "continue_on"}, -- Not yet, but believe me they will.
		{"@conversation/padawan_politician_01:s_99bdf01", "not_more"} -- I decided to make myself a safer place. Go deal with it yourself.
	}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(back_notdone);

continue_on = ConvoScreen:new {
	id = "continue_on",
	leftDialog = "@conversation/padawan_politician_01:s_e6b7fdc0", -- Excellent. Such enthusiasm in one's work is always a pleasure to behold.
	stopConversation = "true",
	options = {}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(continue_on);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_politician_01:s_59b6aab3", -- Has the bloodseeker mite been taken care of?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_politician_01:s_dc3b8fc5", "back_done_more"} -- Yes, it has.
	}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(back_done);

back_done_more = ConvoScreen:new {
	id = "back_done_more",
	leftDialog = "@conversation/padawan_politician_01:s_4fc89968", -- Excellent, thank you for your services friend.
	stopConversation = "true",
	options = {}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(back_done_more);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_politician_01:s_badba8f2", -- Greetings and be welcome. Remember my motto: voting once is nice; voting often is better.
	stopConversation = "true",
	options = {}
}
trialsPadawanPolitician01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanPolitician01ConvoTemplate", trialsPadawanPolitician01ConvoTemplate);
