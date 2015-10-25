trialsPadawanOldMusician01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanOldMusician01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_01:s_dbc1ba26", -- Well hello there! It's always nice to see new faces at this age. Reminds me of years past. Humor and old man for a bit, and listen up eh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_52917b0d", "curious"}, -- Of course.
		{"@conversation/padawan_old_musician_01:s_4f05c224", "not_curious"} -- I don't have time for your dusty old stories.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(intro);

not_curious = ConvoScreen:new {
	id = "not_curious",
	leftDialog = "@conversation/padawan_old_musician_01:s_189e6456", -- As I thought. I didn't much expect you to.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(not_curious);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_old_musician_01:s_d27dbab", -- In my younger years I was in a traveling band. We played all over this here planet. We were not the best band around, but people seemed to enjoy our music enough. Over the years the band drifted and we all went our separate ways. I haven't kept in touch with any of the three other members, and have regretted it to this day.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_150fa11a", "continue"} -- My guess is you want me to help you with that.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(curious);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_old_musician_01:s_6aa99fbc", -- You are a quick one. All I want is for you to try to find them. If you could of course.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_c2f4a95c", "continue_more"} -- Any reason you cannot look for them yourself?
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_old_musician_01:s_6b726d18", -- Truthfully, I don't have much time left. I think it would be a surprise to both my doctors and myself if I made it to the end of this week.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_2c577f48", "continue_accept"}, -- Where should I start?
		{"@conversation/padawan_old_musician_01:s_d23b54d0", "continue_decline"} -- You're not even gonna live long enough for this to be worth it. I'm out.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_more);

continue_accept = ConvoScreen:new {
	id = "continue_accept",
	leftDialog = "@conversation/padawan_old_musician_01:s_5027198", -- That's a good question. I think there's a man I used to know... he's a booking agent for musical acts. Name's Marco Vahn. Last I heard, he was in Mos Eisley on Tatooine trying to convince some band at the cantina there to go on tour for him. He might know where my old band mates are.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_accept);

continue_decline = ConvoScreen:new {
	id = "continue_decline",
	leftDialog = "@conversation/padawan_old_musician_01:s_6386bdac", -- What's that? Speak up a bit. Where ya going...
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_decline);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_old_musician_01:s_f6fe45ba", -- Well hello... oh you're back. Did you find any of my old friends?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_c4a1af2c", "notdone_yet"} -- Not yet, but I'm still looking. I'll be back when I find them.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(back_notdone);

notdone_yet = ConvoScreen:new {
	id = "notdone_yet",
	leftDialog = "@conversation/padawan_old_musician_01:s_a80877a1", -- I look forward to hearing from you.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(notdone_yet);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_old_musician_01:s_73519ce0", -- Are they on their way?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_c53fc924", "continue_more_too"}, -- No, but I found a good lead. One of your friends moved to Lok.
		{"@conversation/padawan_old_musician_01:s_d7278b9f", "continue_done"} -- Sort of, but there's no way I'm travelling all the way to Lok
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(back_done);

continue_more_too = ConvoScreen:new {
	id = "continue_more_too",
	leftDialog = "@conversation/padawan_old_musician_01:s_9fe9d850", -- Oh, that is very good news. Please go and find out if he's still there.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_more_too);

continue_done = ConvoScreen:new {
	id = "continue_done",
	leftDialog = "@conversation/padawan_old_musician_01:s_42d4547", -- Lok? Why would you go there? Oh never mind. I'm surprised you've done as much as you have, to be honest.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_done);

back_again = ConvoScreen:new {
	id = "back_again",
	leftDialog = "@conversation/padawan_old_musician_01:s_f2a197da", -- Have you found my old friends?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_431c1c58", "continue_again"}, -- I've got some bad news Grizzlo.
		{"@conversation/padawan_old_musician_01:s_e4475a83", "continue_done_too"}, -- Looks like you are out of luck old man.
		{"@conversation/padawan_old_musician_01:s_64234023", "continue_ring"} -- This was given to me... to give to you.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(back_again);

continue_again = ConvoScreen:new {
	id = "continue_again",
	leftDialog = "@conversation/padawan_old_musician_01:s_d6d1e61d", -- You don't even have to say it friend, I can see from the look in your eyes. They are all dead. You can go on now, thanks again for your help.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_again);

continue_done_too = ConvoScreen:new {
	id = "continue_done_too",
	leftDialog = "@conversation/padawan_old_musician_01:s_246ed1c7", -- Don't much have to tell me that. Lady luck left me many years ago. Thanks for your time.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_d7ea1106", "continue_done_bye"} -- Also there's a rin... er... I mean... yeah, I'll be going.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_done_too);

continue_done_bye = ConvoScreen:new {
	id = "continue_done_bye",
	leftDialog = "@conversation/padawan_old_musician_01:s_2d9fa396", -- If only you'd found at least one of them alive. I would have gone to my rest a happier man.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_done_bye);

continue_ring = ConvoScreen:new {
	id = "continue_ring",
	leftDialog = "@conversation/padawan_old_musician_01:s_2d855cc6", -- Samston always did like to rub it in. We would fight for days over Selestina, she was the sole reason 'The Blue Mead', broke up. This ring means a whole lot to me, and I appreciate the trouble you went through to get it. I wish I hadn't been so stubborn in my life and I hope you can learn from my poor example.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_52917b0d", "continue_ring_more"} -- Of course.
	}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_ring);

continue_ring_more = ConvoScreen:new {
	id = "continue_ring_more",
	leftDialog = "@conversation/padawan_old_musician_01:s_ef7a7d43", -- My friends may all have passed on, but this ring will help me remember. Thank you.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(continue_ring_more);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_old_musician_01:s_6386bdac", -- What's that? Speak up a bit. Where ya going...
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(noquest_player_talks);

player_already_completed = ConvoScreen:new {
	id = "player_already_completed",
	leftDialog = "@conversation/padawan_old_musician_01:s_7a8dee0a", -- Back when I used to play my music, I wore a blumfruit on my lapel because it was the style at the time.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician01ConvoTemplate:addScreen(player_already_completed);

addConversationTemplate("trialsPadawanOldMusician01ConvoTemplate", trialsPadawanOldMusician01ConvoTemplate);
