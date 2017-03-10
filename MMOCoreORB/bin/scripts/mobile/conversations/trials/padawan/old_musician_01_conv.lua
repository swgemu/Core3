padawan_old_musician_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_old_musician_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_01:s_dbc1ba26", -- Well hello there! It's always nice to see new faces at this age. Reminds me of years past. Humor and old man for a bit, and listen up eh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_52917b0d", "traveling_band"}, -- Of course.
	}
}
padawan_old_musician_01_convo_template:addScreen(intro);

traveling_band = ConvoScreen:new {
	id = "traveling_band",
	leftDialog = "@conversation/padawan_old_musician_01:s_d27dbab", --	In my younger years I was in a traveling band. We played all over this here planet. We were not the best band around, but people seemed to enjoy our music enough. Over the years the band drifted and we all went our separate ways. I haven't kept in touch with any of the three other members, and have regretted it to this day.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_150fa11a", "try_to_find_them"}, -- My guess is you want me to help you with that.
		{"@conversation/padawan_old_musician_01:s_4f05c224", "as_i_thought"}, -- I don't have time for your dusty old stories.
	}
}
padawan_old_musician_01_convo_template:addScreen(traveling_band);

try_to_find_them = ConvoScreen:new {
	id = "try_to_find_them",
	leftDialog = "@conversation/padawan_old_musician_01:s_6aa99fbc", --	You are a quick one.  All I want is for you to try to find them.  If you could of course.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_2c577f48", "booking_agent"}, -- Where should I start?
		{"@conversation/padawan_old_musician_01:s_c2f4a95c", "as_i_thought"}, -- Any reason you cannot look for them yourself?
	}
}
padawan_old_musician_01_convo_template:addScreen(try_to_find_them);

try_to_find_them = ConvoScreen:new {
	id = "try_to_find_them",
	leftDialog = "@conversation/padawan_old_musician_01:s_6aa99fbc", --	You are a quick one.  All I want is for you to try to find them.  If you could of course.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_2c577f48", "traveling_band"}, -- Where should I start?
		{"@conversation/padawan_old_musician_01:s_c2f4a95c", "not_much_time"}, -- Any reason you cannot look for them yourself?
	}
}
padawan_old_musician_01_convo_template:addScreen(try_to_find_them);

not_much_time = ConvoScreen:new {
	id = "not_much_time",
	leftDialog = "@conversation/padawan_old_musician_01:s_6b726d18", -- Truthfully, I don't have much time left. I think it would be a surprise to both my doctors and myself if I made it to the end of this week.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_2c577f48", "traveling_band"}, -- Where should I start?
		{"@conversation/padawan_old_musician_01:s_e4475a83", "lady_luck_left_me"}, -- Looks like you are out of luck old man.
	}
}
padawan_old_musician_01_convo_template:addScreen(not_much_time);

booking_agent = ConvoScreen:new {
	id = "booking_agent",
	leftDialog = "@conversation/padawan_old_musician_01:s_5027198", -- That's a good question. I think there's a man I used to know... he's a booking agent for musical acts. Name's Marco Vahn. Last I heard, he was in Mos Eisley on Tatooine trying to convince some band at the cantina there to go on tour for him. He might know where my old band mates are.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(booking_agent);

lady_luck_left_me = ConvoScreen:new {
	id = "lady_luck_left_me",
	leftDialog = "@conversation/padawan_old_musician_01:s_246ed1c7", -- Don't much have to tell me that.  Lady luck left me many years ago.  
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(lady_luck_left_me);

as_i_thought = ConvoScreen:new {
	id = "as_i_thought",
	leftDialog = "@conversation/padawan_old_musician_01:s_189e6456", -- As I thought.  I didn't much expect you to.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(as_i_thought);

intro_spoke_to_second_npc = ConvoScreen:new {
	id = "intro_spoke_to_second_npc",
	leftDialog = "@conversation/padawan_old_musician_01:s_73519ce0", -- Are they on their way?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_431c1c58", "look_in_your_eyes"}, -- I've got some bad news Grizzlo.
	}
}
padawan_old_musician_01_convo_template:addScreen(intro_spoke_to_second_npc);

look_in_your_eyes = ConvoScreen:new {
	id = "look_in_your_eyes",
	leftDialog = "@conversation/padawan_old_musician_01:s_d6d1e61d", -- You don't even have to say it friend, I can see from the look in your eyes.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_64234023", "rub_it_in"}, -- This was given to me... to give to you.
		{"@conversation/padawan_old_musician_01:s_d7ea1106", "gone_to_rest"}, -- Also there's a rin... er... I mean... yeah, I'll be going.
	}
}
padawan_old_musician_01_convo_template:addScreen(look_in_your_eyes);

rub_it_in = ConvoScreen:new {
	id = "rub_it_in",
	leftDialog = "@conversation/padawan_old_musician_01:s_2d855cc6", -- Samston always did like to rub it in. We would fight for days over Selestina, she was the sole reason 'The Blue Mead', broke up. This ring means a whole lot to me, and I appreciate the trouble you went through to get it. I wish I hadn't been so stubborn in my life and I hope you can learn from my poor example.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(rub_it_in);

gone_to_rest = ConvoScreen:new {
	id = "gone_to_rest",
	leftDialog = "@conversation/padawan_old_musician_01:s_2d9fa396", -- If only you'd found at least one of them alive. I would have gone to my rest a happier man.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(gone_to_rest);

intro_spoke_to_first_npc = ConvoScreen:new {
	id = "intro_spoke_to_first_npc",
	leftDialog = "@conversation/padawan_old_musician_01:s_f2a197da", -- Have you found my old friends?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_c53fc924", "very_good_news"}, -- No, but I found a good lead. One of your friends moved to Lok.
		{"@conversation/padawan_old_musician_01:s_d7278b9f", "to_be_honest"}, -- Sort of, but there's no way I'm travelling all the way to Lok
	}
}
padawan_old_musician_01_convo_template:addScreen(intro_spoke_to_first_npc);

very_good_news = ConvoScreen:new {
	id = "very_good_news",
	leftDialog = "@conversation/padawan_old_musician_01:s_9fe9d850", -- Oh, that is very good news. Please go and find out if he's still there.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(very_good_news);

to_be_honest = ConvoScreen:new {
	id = "to_be_honest",
	leftDialog = "@conversation/padawan_old_musician_01:s_42d4547", -- Lok? Why would you go there? Oh never mind. I'm surprised you've done as much as you have, to be honest.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(to_be_honest);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_old_musician_01:s_f6fe45ba", -- Well hello... oh you're back. Did you find any of my old friends?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_01:s_c4a1af2c", "look_forward_to_it"}, -- Not yet, but I'm still looking. I'll be back when I find them.
		{"@conversation/padawan_old_musician_01:s_d23b54d0", "where_ya_going"}, -- You're not even gonna live long enough for this to be worth it. I'm out.
	}
}
padawan_old_musician_01_convo_template:addScreen(intro_in_progress);

look_forward_to_it = ConvoScreen:new {
	id = "look_forward_to_it",
	leftDialog = "@conversation/padawan_old_musician_01:s_a80877a1", -- I look forward to hearing from you.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(look_forward_to_it);

where_ya_going = ConvoScreen:new {
	id = "where_ya_going",
	leftDialog = "@conversation/padawan_old_musician_01:s_6386bdac", -- What's that? Speak up a bit. Where ya going...
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(where_ya_going);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_old_musician_01:s_ef7a7d43", -- My friends may all have passed on, but this ring will help me remember. Thank you.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_old_musician_01:s_7a8dee0a", -- Back when I used to play my music, I wore a blumfruit on my lapel because it was the style at the time.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_old_musician_01_convo_template", padawan_old_musician_01_convo_template);
