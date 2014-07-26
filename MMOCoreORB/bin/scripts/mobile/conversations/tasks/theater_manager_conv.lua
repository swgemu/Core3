theaterManagerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theater_manager_conv_handler",
	screens = {}
}

init_notentertainer = ConvoScreen:new {
	id = "init_notentertainer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_2a8b6bf", -- Only entertainers and crew should be backstage. What are you doing here?
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_notentertainer);

init_entertainer = ConvoScreen:new {
	id = "init_entertainer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_37b822c1", -- Hello there! You're a member of the entertainment industry are you not? I've got an offer for you if you're interested.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_499afb89", "explain_offer"}, -- What is your offer?
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "if_change_mind"}, -- Not right now, thanks.
	}
}
theaterManagerConvoTemplate:addScreen(init_entertainer);

if_change_mind = ConvoScreen:new {
	id = "if_change_mind",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1b58131a", -- Alright. If you change your mind, I'll be here.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(if_change_mind);

explain_offer = ConvoScreen:new {
	id = "explain_offer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_c08ff946", -- I'm looking for some new solo acts to perform here at the theater. I've been scouring the city trying to find fresh new talent to put on some live shows. Would you possibly be interested in doing a performance series?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_a2fae368", "must_audition"}, -- Sure, that sounds like a lot of fun.
		{"@conversation/quest_crowd_pleaser_manager:s_388438a6", "how_much_paid"}, -- How much will I get paid?
		{"@conversation/quest_crowd_pleaser_manager:s_1343b0ab", "if_change_mind"}, -- Nah, doesn't really sound like something I want to do.
	}
}
theaterManagerConvoTemplate:addScreen(explain_offer);

must_audition = ConvoScreen:new {
	id = "must_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_7b9543aa", -- Let's not get ahead of ourselves. First, you must pass an audition. We can't just have anyone getting up on the stage now, can we?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_34bf7b50", "prepare_audition"}, -- I see. Just tell me what I need to do.
		{"@conversation/quest_crowd_pleaser_manager:s_64d20f97", "understand_come_back"}, -- Audition? Uh, I'd rather not be judged.
	}
}
theaterManagerConvoTemplate:addScreen(must_audition);

prepare_audition = ConvoScreen:new {
	id = "prepare_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_705ff1a9", -- Excellent. Make whatever preparations you feel are necessary, and then come back to me when you are ready to start the audition.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(prepare_audition);

understand_come_back = ConvoScreen:new {
	id = "understand_come_back",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_56d2a81f", -- I understand. Come back if you change your mind.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(understand_come_back);

how_much_paid = ConvoScreen:new {
	id = "how_much_paid",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_a2ce6dd9", -- That's all you youngsters are worried about these days, isn't it? Don't worry, you'll be compensated for your time.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_39aa9593", "need_to_audition"}, -- Sure, I can give it a try.
		{"@conversation/quest_crowd_pleaser_manager:s_1343b0ab", "if_change_mind"}, -- Nah, doesn't really sound like something I want to do.
	}
}
theaterManagerConvoTemplate:addScreen(how_much_paid);

need_to_audition = ConvoScreen:new {
	id = "need_to_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_70da1c6a", -- OK. You'll still need to audition though. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_7943785d", "prepare_audition"}, -- Sure, no time like the present.
		{"@conversation/quest_crowd_pleaser_manager:s_64d20f97", "understand_come_back"}, -- Audition? Uh, I'd rather not be judged.
	}
}
theaterManagerConvoTemplate:addScreen(need_to_audition);

here_for_audition = ConvoScreen:new {
	id = "here_for_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_472f2a5e", -- You're here for an audition, yes? Are you ready to get started now?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_59a59142", "musician_or_dancer"}, -- As ready as I'll ever be.
		{"@conversation/quest_crowd_pleaser_manager:s_414898b2", "understand_come_back"}, -- I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(here_for_audition);

musician_or_dancer = ConvoScreen:new {
	id = "musician_or_dancer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1204a0c6", -- I see. Now, do you want to audition as a musician or a dancer?
	stopConversation = "false",
	options = {
	}
}
theaterManagerConvoTemplate:addScreen(musician_or_dancer);

not_skilled_enough = ConvoScreen:new {
	id = "not_skilled_enough",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1c296980", -- It doesn't look like you're skilled enough to perform yet. Go practice a little more and come back when you're ready to try again.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(not_skilled_enough);

come_back_ready = ConvoScreen:new {
	id = "come_back_ready",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_303aa95e", -- Alright. Come back when you're ready.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_ready);

audition_in_30_music = ConvoScreen:new {
	id = "audition_in_30_music",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_in_30_music);

audition_in_30_dance = ConvoScreen:new {
	id = "audition_in_30_dance",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_in_30_dance);

audition_in_30 = ConvoScreen:new {
	id = "audition_in_30",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_in_30);

show_running = ConvoScreen:new {
	id = "show_running",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_57f90c0e", -- Hm... it looks like someone else is on stage right now. Try back again in a little while and we'll see if we can get you set up.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(show_running);

audition_successful = ConvoScreen:new {
	id = "audition_successful",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_857ede28", -- Hey! I hear that you passed the audition! That's fantastic. Here, let me give you a payment in advance for your up-coming performances. You deserve a break now, though. Come back later and we'll discuss what needs to be done next.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_successful);

addConversationTemplate("theaterManagerConvoTemplate", theaterManagerConvoTemplate);