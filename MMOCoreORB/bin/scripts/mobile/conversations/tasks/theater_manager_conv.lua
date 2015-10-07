theaterManagerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "TheaterManagerConvoHandler",
	screens = {}
}

init_not_entertainer = ConvoScreen:new {
	id = "init_not_entertainer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_2a8b6bf", -- Only entertainers and crew should be backstage. What are you doing here?
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_not_entertainer);

init_completed_both = ConvoScreen:new {
	id = "init_completed_both",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_e5438cc6", -- Welcome back! I still can't tell you how impressed I am with your performances. You truly are a credit to the entertainment professions. Best of luck to you in the future, friend!
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_completed_both);

init_failed_audition_timer = ConvoScreen:new {
	id = "init_failed_audition_timer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_3936bc63", -- Oh, you didn't pass the audition? That's too bad. We can set you up with another audition, but not until twenty-four hours have passed since your last audition. Come back then and we'll talk.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_failed_audition_timer);

init_failed_performance_timer = ConvoScreen:new {
	id = "init_failed_performance_timer",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_aa18ac6", -- It looks like your previous show didn't go over so well. That's too bad. You can try the performance again, but not until twenty-four hours have passed since your last one. Come back then and we'll talk.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_failed_performance_timer);

init_event_in_progress = ConvoScreen:new {
	id = "init_event_in_progress",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_d66dc712", -- Too busy to talk right now. I'm very busy, sorry.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_event_in_progress);

init_completed_one = ConvoScreen:new {
	id = "init_completed_one",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_95037778", -- Oh, hello! Welcome back, friend. Are you looking to participate in another performance?
	stopConversation = "false",
	options = {
	-- Handled by convo handler
	--{"@conversation/quest_crowd_pleaser_manager:s_dda95847", "full_on_dance or full_on_music"}, -- Is that possible?
	--{"@conversation/quest_crowd_pleaser_manager:s_c5a66e82", "come_see_me"}, -- No, not really.
	}
}
theaterManagerConvoTemplate:addScreen(init_completed_one);

come_see_me = ConvoScreen:new {
	id = "come_see_me",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_67e4d556", -- OK... Well, if you ever need any more work, just come see me.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_see_me);

full_on_dance = ConvoScreen:new {
	id = "full_on_dance",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_919f9d5a", -- Well, I'll be honest with you. Ever since your show, every hack that thinks he can dance a step has come here to perform. So we're all full on dance shows, but we still have a few spots open for a musical show if you're interested.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_39aa9593", "still_must_audition_music"}, -- Sure, I can give it a try.
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "ill_be_here"}, -- No, that's not really something I want to do.
	}
}
theaterManagerConvoTemplate:addScreen(full_on_dance);

full_on_music = ConvoScreen:new {
	id = "full_on_music",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_a84a3743", -- Well, I'll be honest with you. Ever since your show, every hack that thinks he can play a note has come here to perform. So we're all full on musical shows, but we still have a few spots open for a dance show if you're interested.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_39aa9593", "still_must_audition_dance"}, -- Sure, I can give it a try.
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "ill_be_here"}, -- No, that's not really something I want to do.
	}
}
theaterManagerConvoTemplate:addScreen(full_on_music);

ill_be_here = ConvoScreen:new {
	id = "ill_be_here",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1b58131a", -- Alright. If you change your mind, I'll be here.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(ill_be_here);

still_must_audition_dance = ConvoScreen:new {
	id = "still_must_audition_dance",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_70da1c6a", -- OK. You'll still need to audition though. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_9739cb4c", "prep_second_audition_dance"}, -- Yes, that's fine.
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "i_understand"}, -- No way. I don't want to go through that again.
	}
}
theaterManagerConvoTemplate:addScreen(still_must_audition_dance);

still_must_audition_music = ConvoScreen:new {
	id = "still_must_audition_music",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_70da1c6a", -- OK. You'll still need to audition though. Is that acceptable?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_9739cb4c", "prep_second_audition_music"}, -- Yes, that's fine.
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "i_understand"}, -- No way. I don't want to go through that again.
	}
}
theaterManagerConvoTemplate:addScreen(still_must_audition_music);

prep_second_audition_dance = ConvoScreen:new {
	id = "prep_second_audition_dance",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_14556b51", -- OK. Go ahead and make your preparations. You know the drill. Just come back and talk with me when you're ready to audition.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(prep_second_audition_dance);

prep_second_audition_music = ConvoScreen:new {
	id = "prep_second_audition_music",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_14556b51", -- OK. Go ahead and make your preparations. You know the drill. Just come back and talk with me when you're ready to audition.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(prep_second_audition_music);

i_understand = ConvoScreen:new {
	id = "i_understand",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_56d2a81f", -- I understand. Come back if you change your mind.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(i_understand);

init_start_second_audition = ConvoScreen:new {
	id = "init_start_second_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_472f2a5e", -- You're here for an audition, yes? Are you ready to get started now?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_4a1d2431", "second_audition_starts_in_30"}, -- Yes, I'm ready.
		{"@conversation/quest_crowd_pleaser_manager:s_f3d46f0b", "come_back_when_ready"}, -- No, not quite yet.
	}
}
theaterManagerConvoTemplate:addScreen(init_start_second_audition);

second_audition_starts_in_30 = ConvoScreen:new {
	id = "second_audition_starts_in_30",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(second_audition_starts_in_30);

init_first_time = ConvoScreen:new {
	id = "init_first_time",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_37b822c1", -- Hello there! You're a member of the entertainment industry are you not? I've got an offer for you if you're interested.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_499afb89", "looking_for_acts"}, -- What is your offer?
		{"@conversation/quest_crowd_pleaser_manager:s_2883b989", "suit_yourself"}, -- Not right now, thanks.
	}
}
theaterManagerConvoTemplate:addScreen(init_first_time);

suit_yourself = ConvoScreen:new {
	id = "suit_yourself",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_82b273a8", -- Suit yourself.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(suit_yourself);

looking_for_acts = ConvoScreen:new {
	id = "looking_for_acts",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_c08ff946", -- I'm looking for some new solo acts to perform here at the theater. I've been scouring the city trying to find fresh new talent to put on some live shows. Would you possibly be interested in doing a performance series?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_a2fae368", "first_must_pass_audition"}, -- Sure, that sounds like a lot of fun.
		{"@conversation/quest_crowd_pleaser_manager:s_388438a6", "youll_be_compensated"}, -- How much will I get paid?
		{"@conversation/quest_crowd_pleaser_manager:s_1343b0ab", "suit_yourself"}, -- Nah, doesn't really sound like something I want to do.
	}
}
theaterManagerConvoTemplate:addScreen(looking_for_acts);

first_must_pass_audition = ConvoScreen:new {
	id = "first_must_pass_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_7b9543aa", -- Let's not get ahead of ourselves. First, you must pass an audition. We can't just have anyone getting up on the stage now, can we?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_9288900f", "make_audition_preperations"}, -- I understand.
		{"@conversation/quest_crowd_pleaser_manager:s_64d20f97", "suit_yourself"}, -- Audition? Uh, I'd rather not be judged.
	}
}
theaterManagerConvoTemplate:addScreen(first_must_pass_audition);

make_audition_preperations = ConvoScreen:new {
	id = "make_audition_preperations",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_705ff1a9", -- Excellent. Make whatever preparations you feel are necessary, and then come back to me when you are ready to start the audition.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(make_audition_preperations);

youll_be_compensated = ConvoScreen:new {
	id = "youll_be_compensated",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_a2ce6dd9", -- That's all you youngsters are worried about these days, isn't it? Don't worry, you'll be compensated for your time.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_8e4955d6", "first_must_pass_audition"}, -- OK, count me in.
		{"@conversation/quest_crowd_pleaser_manager:s_64d20f97", "suit_yourself"}, -- Nah, it's not for me.
	}
}
theaterManagerConvoTemplate:addScreen(youll_be_compensated);

init_start_audition = ConvoScreen:new {
	id = "init_start_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_472f2a5e", -- You're here for an audition, yes? Are you ready to get started now?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_4a1d2431", "what_type_of_audition"}, -- Yes, I'm ready.
		{"@conversation/quest_crowd_pleaser_manager:s_f3d46f0b", "come_back_when_ready"}, -- No, not quite yet.
	}
}
theaterManagerConvoTemplate:addScreen(init_start_audition);

come_back_when_ready = ConvoScreen:new {
	id = "come_back_when_ready",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_303aa95e", -- Alright. Come back when you're ready.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_when_ready);

what_type_of_audition = ConvoScreen:new {
	id = "what_type_of_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1204a0c6", -- I see. Now, do you want to audition as a musician or a dancer?
	stopConversation = "false",
	options = {
		-- Handled in convo handler, checks to see if player has skills needed
		--{"@conversation/quest_crowd_pleaser_manager:s_183e8ee4", ""}, -- As a musician.
		--{"@conversation/quest_crowd_pleaser_manager:s_9172f29c", ""}, -- As a dancer.
		--{"@conversation/quest_crowd_pleaser_manager:s_c73756f7", "come_back_when_ready"}, -- On second thought, I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(what_type_of_audition);

not_skilled_enough = ConvoScreen:new {
	id = "not_skilled_enough",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1c296980", -- It doesn't look like you're skilled enough to perform yet. Go practice a little more and come back when you're ready to try again.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(not_skilled_enough);

someone_on_stage = ConvoScreen:new {
	id = "someone_on_stage",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_57f90c0e", -- Hm... it looks like someone else is on stage right now. Try back again in a little while and we'll see if we can get you set up.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(someone_on_stage);

audition_starts_in_30_music = ConvoScreen:new {
	id = "audition_starts_in_30_music",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_starts_in_30_music);

audition_starts_in_30_dance = ConvoScreen:new {
	id = "audition_starts_in_30_dance",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_274a8930", -- Alright, I'll go ahead and get things set up. You'd better hurry up and get onstage. The audition will start in thirty seconds.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(audition_starts_in_30_dance);

init_passed_audition = ConvoScreen:new {
	id = "init_passed_audition",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_857ede28", -- Hey! I hear that you passed the audition! That's fantastic. Here, let me give you a payment in advance for your up-coming performances. You deserve a break now, though. Come back later and we'll discuss what needs to be done next.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_passed_audition);

init_first_advertising = ConvoScreen:new {
	id = "init_first_advertising",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_937f2001", -- Back already, huh? I don't blame you for wanting to get started.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_694f2644", "first_show_advertising"}, -- OK, so what do we do next?
		{"@conversation/quest_crowd_pleaser_manager:s_414898b2", "come_back_when_you_are"}, -- I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(init_first_advertising);

come_back_when_you_are = ConvoScreen:new {
	id = "come_back_when_you_are",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_fa31756f", -- OK, come back when you are.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_when_you_are);

first_show_advertising = ConvoScreen:new {
	id = "first_show_advertising",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_353af024", -- Well, before you put on your first show, we need to do some advertising. You know, what good is a show if nobody comes to see it?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_8ddf8010", "go_out_and_promote"}, -- How do we do that?
		{"@conversation/quest_crowd_pleaser_manager:s_e8276d66", "come_back_whenever"}, -- That sounds pretty hard, maybe I'll come back later.
	}
}
theaterManagerConvoTemplate:addScreen(first_show_advertising);

come_back_whenever = ConvoScreen:new {
	id = "come_back_whenever",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_f72be127", -- Alright. Come back whenever you're ready.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_whenever);

go_out_and_promote = ConvoScreen:new {
	id = "go_out_and_promote",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_4dbb8ff6", -- I'll take care of all the promotions on this end, but you need to go out and promote yourself, if you know what I'm saying. Get your name out there on the streets... get people talking.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_34bf7b50", "should_be_simple"}, -- I see. Just tell me what I need to do.
		{"@conversation/quest_crowd_pleaser_manager:s_e8276d66", "come_back_when_more_time"}, -- I don't really have time for that right now.
	}
}
theaterManagerConvoTemplate:addScreen(go_out_and_promote);

come_back_when_more_time = ConvoScreen:new {
	id = "come_back_when_more_time",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_b1522710", -- I see. Well, come back when you have more time and we'll get started.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_when_more_time);

should_be_simple = ConvoScreen:new {
	id = "should_be_simple",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_2224e2b8", -- It should be quite simple. Just go out there and do a little performance routine for some people. I think that if you were to entertain ten people, that would be enough. Are you ready to do this now?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_7943785d", "go_entertain_ten"}, -- Sure, no time like the present.
		{"@conversation/quest_crowd_pleaser_manager:s_350a3257", "come_back_when_more_time"}, -- Not right now, I've got some stuff to do first.
	}
}
theaterManagerConvoTemplate:addScreen(should_be_simple);

go_entertain_ten = ConvoScreen:new {
	id = "go_entertain_ten",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_8b00fbc4", -- OK, I'll get the promotions started, you just go out and entertain ten people. Then come back here and we'll talk about getting the concert started.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(go_entertain_ten);

init_hasnt_entertained_ten = ConvoScreen:new {
	id = "init_hasnt_entertained_ten",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_810fffd0", -- Oh, you're back. But I don't think you've finished your promotional campaign have you? Come back when you're done and we'll talk about your show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_hasnt_entertained_ten);

init_entertained_ten = ConvoScreen:new {
	id = "init_entertained_ten",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_2b8d253d", -- Excellent work. I'm starting to hear the buzz about your performance! We should be able to put on the show whenever you're ready. Go make your preparations, then come speak with me again when you want to begin.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_entertained_ten);

init_first_show = ConvoScreen:new {
	id = "init_first_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_b5131941", -- Ready to start the show, are you? Don't worry if you're nervous. Everybody gets like that the first time they're on stage.
	stopConversation = "false",
	options = {
		-- Handled by convo handler in case someone is on stage
		--{"@conversation/quest_crowd_pleaser_manager:s_1377703a", "starts_in_two_min"}, -- Yes, I'm ready. Let's get this show on the road.
		--{"@conversation/quest_crowd_pleaser_manager:s_4365b273", "stomach_of_steel"}, -- I'm not nervous.
		--{"@conversation/quest_crowd_pleaser_manager:s_d730c5dd", "take_your_time"}, -- No, I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(init_first_show);

take_your_time = ConvoScreen:new {
	id = "take_your_time",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_ab1c9c5f", -- That's fine. Take your time. Just come back when you're ready.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(take_your_time);

stomach_of_steel = ConvoScreen:new {
	id = "stomach_of_steel",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_85b97ed7", -- Sure, sure. You've got a stomach of pure steel. So, are you ready to get started?
	stopConversation = "false",
	options = {
		-- Handled by convo handler in case someone is on stage
		--{"@conversation/quest_crowd_pleaser_manager:s_1377703a", "starts_in_two_min"}, -- Yes, I'm ready. Let's get this show on the road.
		--{"@conversation/quest_crowd_pleaser_manager:s_d730c5dd", "take_your_time"}, -- No, I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(stomach_of_steel);

starts_in_two_min = ConvoScreen:new {
	id = "starts_in_two_min",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_db3a3e40", -- Good. I'll let the crew know so that they can start setting up. The performance will start in two minutes. You may speak with the audience beforehand if you like, but you must be on the stage when the show starts, alright?
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(starts_in_two_min);

init_completed_first_show = ConvoScreen:new {
	id = "init_completed_first_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_cad51774", -- You've completed your first show! Congratulations, the audience loved you. Let me give you another advance for your next performance. Come back and see me again when you're ready to talk about your next show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_completed_first_show);

init_second_advertising = ConvoScreen:new {
	id = "init_second_advertising",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_ed9c9f8d", -- Oh yes. You're ready to get going for your next show. Let's not get too ahead of ourselves, though. You need to go out and do some more promotion before the next performance.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_847c3be4", "show_will_be_bigger"}, -- More promotion?
		{"@conversation/quest_crowd_pleaser_manager:s_6b02387e", "ok_come_back"}, -- I see. I'm not ready for that yet.
	}
}
theaterManagerConvoTemplate:addScreen(init_second_advertising);

ok_come_back = ConvoScreen:new {
	id = "ok_come_back",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_fa31756f", -- OK, come back when you are.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(ok_come_back);

show_will_be_bigger = ConvoScreen:new {
	id = "show_will_be_bigger",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_58ea419", -- Indeed! This show will be even bigger than the last one! If the next show is as good as the last, you'll be on your way to the top!
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_3e04f6f", "performance_for_twenty"}, -- Alright. What do I need to do this time?
		{"@conversation/quest_crowd_pleaser_manager:s_11a3b43", "come_back_whenever"}, -- I'll have to come back later.
	}
}
theaterManagerConvoTemplate:addScreen(show_will_be_bigger);

performance_for_twenty = ConvoScreen:new {
	id = "performance_for_twenty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_c9770db7", -- I would think that if you were to go out and do a performance routine for at least twenty people, that would be sufficient. Remember, the more people that get a taste of your act, the more tickets we'll sell!
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_b6dac7cf", "go_entertain_twenty"}, -- OK, I'll get started on that now.
		{"@conversation/quest_crowd_pleaser_manager:s_a820a6d1", "come_back_when_more_time"}, -- I'll have to come back later.
	}
}
theaterManagerConvoTemplate:addScreen(performance_for_twenty);

come_back_when_more_time = ConvoScreen:new {
	id = "come_back_when_more_time",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_b1522710", -- I see. Well, come back when you have more time and we'll get started.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(come_back_when_more_time);

go_entertain_twenty = ConvoScreen:new {
	id = "go_entertain_twenty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_f66a7b69", -- Just go out and entertain twenty people. That should be enough. Then come back and we'll talk about your next show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(go_entertain_twenty);

init_hasnt_entertained_twenty = ConvoScreen:new {
	id = "init_hasnt_entertained_twenty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_3d244a46", -- You haven't completed your promotional assignment have you? Come back when you're done and we'll talk about your next performance.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_hasnt_entertained_twenty);

init_entertained_twenty = ConvoScreen:new {
	id = "init_entertained_twenty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_f29e46b6", -- Great work! Really great work! I'm starting to hear a lot of people talk about you! I've got a feeling that this show is going to be fantastic.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_7b58a334", "whenever_you_like"}, -- When can we get started with the next show?
	}
}
theaterManagerConvoTemplate:addScreen(init_entertained_twenty);

whenever_you_like = ConvoScreen:new {
	id = "whenever_you_like",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1e0d968c", -- Whenever you like. Just go make yourself ready and speak to me again when you want to start.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(whenever_you_like);

init_second_show = ConvoScreen:new {
	id = "init_second_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_3cdabd0e", -- What? Oh, hello there. I'm sorry, it's recently become rather busy. What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_1dc24a1", "open_slot_coming_up"}, -- I'm here to talk about my next performance.
		{"@conversation/quest_crowd_pleaser_manager:s_3ef23ade", "ok_thats_fine"}, -- Sorry. I'll come back later.
	}
}
theaterManagerConvoTemplate:addScreen(init_second_show);

ok_thats_fine = ConvoScreen:new {
	id = "ok_thats_fine",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_a19891a9", -- OK, that's fine.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(ok_thats_fine);

open_slot_coming_up = ConvoScreen:new {
	id = "open_slot_coming_up",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_250ebca6", -- Oh yes, I see, I see. Yes, we do have an open slot coming up here very shortly. Are you ready to get started with your show now?
	stopConversation = "false",
	options = {
		-- Handled by convo handler in case someone is on stage
		--{"@conversation/quest_crowd_pleaser_manager:s_59a59142", ""}, -- As ready as I'll ever be.
		--{"@conversation/quest_crowd_pleaser_manager:s_fb55e1c0", "nervous_come_back"}, -- Actually I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(open_slot_coming_up);

nervous_come_back = ConvoScreen:new {
	id = "nervous_come_back",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_38a3b1e2", -- Nervous? I understand. Just come back when you're ready and we'll get you up on stage.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(nervous_come_back);

starts_in_two_and_a_half = ConvoScreen:new {
	id = "starts_in_two_and_a_half",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_e66da464", -- Good. I'll let the crew know so that they can start setting up. The performance will start in two and a half minutes. You may speak with the audience beforehand if you like, but you must be on the stage when the show starts, alright?
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(starts_in_two_and_a_half);

init_completed_second_show = ConvoScreen:new {
	id = "init_completed_second_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_1a0fba4e", -- Wow, that was a great act! Really! Here, I'm supposed to give you an advance for your next performance. Go get some rest, and come see me whenever you want to talk about your next show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_completed_second_show);

init_third_advertising = ConvoScreen:new {
	id = "init_third_advertising",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_ffa16d1d", -- You're here about your next show aren't you? Sure, sure, I understand. You'll need to go out and do some more promotion before you get started with the next performance, though. Is that alright?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_1dc24a1", "biggest_performance_ever"}, -- That's fine. I don't mind doing the promotions.
		{"@conversation/quest_crowd_pleaser_manager:s_2f3d57d6", "part_of_the_business"}, -- I don't really like doing the promotions.
		{"@conversation/quest_crowd_pleaser_manager:s_1fe0d27c", "alright_come_back_when_time"}, -- I don't have time for that stuff now.
	}
}
theaterManagerConvoTemplate:addScreen(init_third_advertising);

alright_come_back_when_time = ConvoScreen:new {
	id = "alright_come_back_when_time",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_942ddb10", -- Alright, come back when you have the time.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(alright_come_back_when_time);

part_of_the_business = ConvoScreen:new {
	id = "part_of_the_business",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_fe82f47f", -- Advertising and promotion is part of the business kid. Now are you ready to go out there and spread the word, or not?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_a99397a", "biggest_performance_ever"}, -- Yeah, I guess so.
		{"@conversation/quest_crowd_pleaser_manager:s_da9a29e9", "alright_come_back_when_ready"}, -- No, not yet.
	}
}
theaterManagerConvoTemplate:addScreen(part_of_the_business);

alright_come_back_when_ready = ConvoScreen:new {
	id = "alright_come_back_when_ready",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_f72be127", -- Alright. Come back whenever you're ready.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(alright_come_back_when_ready);

biggest_performance_ever = ConvoScreen:new {
	id = "biggest_performance_ever",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_668b00bf", -- That's fantastic. This is going to be your biggest performance ever! I can feel it!
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_57c8489e", "performance_for_thirty"}, -- What should I do?
		{"@conversation/quest_crowd_pleaser_manager:s_ad679858", "alright_come_back_when_ready"}, -- I changed my mind. I'm not ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(biggest_performance_ever);

performance_for_thirty = ConvoScreen:new {
	id = "performance_for_thirty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_7cef0609", -- Here's what you do. Go out and do a small performance routine for thirty people. Soon, everybody should be talking about you, and if the word is good, we might even have a sell out show!
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_c6403b16", "go_entertain_thirty"}, -- OK, I'll go get started.
		{"@conversation/quest_crowd_pleaser_manager:s_d0fc43d", "alright_come_back_when_time"}, -- Hm. I don't have time for that right now.
	}
}
theaterManagerConvoTemplate:addScreen(performance_for_thirty);

go_entertain_thirty = ConvoScreen:new {
	id = "go_entertain_thirty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_bba5f6f2", -- Excellent. Just go out and entertain thirty people. After that, no more promotional work, I promise. Then come back and we'll talk about your next show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(go_entertain_thirty);

init_hasnt_entertained_thirty = ConvoScreen:new {
	id = "init_hasnt_entertained_thirty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_664ead2a", -- I'm hearing people talk about your upcoming show, but it's not enough. Go finish your promotional job, and then we'll discuss your performance.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_hasnt_entertained_thirty);

init_entertained_thirty = ConvoScreen:new {
	id = "init_entertained_thirty",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_b5c6a62d", -- Wow... this is fantastic! Everybody in town is talking about you! We'll have a sold out show for sure! Go make your preparations and come back whenever you're ready to start the performance!
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_entertained_thirty);

init_third_show = ConvoScreen:new {
	id = "init_third_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_16e98373", -- Ah, you're here about your last show?
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_36a4e374", "set_up_if_ready"}, -- Yes, I am.
		{"@conversation/quest_crowd_pleaser_manager:s_55e428e8", "last_of_series"}, -- Last show?
		{"@conversation/quest_crowd_pleaser_manager:s_3ef23ade", "ok_thats_fine"}, -- Sorry, I'll come back later.
	}
}
theaterManagerConvoTemplate:addScreen(init_third_show);

last_of_series = ConvoScreen:new {
	id = "last_of_series",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_2cf69669", -- That's right. This is the last show scheduled for your concert series. But don't worry, for an entertainer such as yourself, I'm sure that there will be many opportunities for you in the future.
	stopConversation = "false",
	options = {
		{"@conversation/quest_crowd_pleaser_manager:s_61657d0f", "set_up_if_ready"}, -- I see.
		{"@conversation/quest_crowd_pleaser_manager:s_fd047f06", "alright_come_back_when_ready"}, -- I'd better come back later then.
	}
}
theaterManagerConvoTemplate:addScreen(last_of_series);

set_up_if_ready = ConvoScreen:new {
	id = "set_up_if_ready",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_b751f222", -- If you're ready now, I'll go ahead and start getting things set up. What do you say?
	stopConversation = "false",
	options = {
		-- Handled by convo handler in case someone is on stage
		--{"@conversation/quest_crowd_pleaser_manager:s_dd4bb16d", "starts_in_three"}, -- Let's do it!
		--{"@conversation/quest_crowd_pleaser_manager:s_d730c5dd", "take_your_time"}, -- No, I'm not quite ready yet.
	}
}
theaterManagerConvoTemplate:addScreen(set_up_if_ready);

starts_in_three = ConvoScreen:new {
	id = "starts_in_three",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_86731ce6", -- Good. I'll let the crew know so that they can start setting up. The performance will start in three minutes. You may speak with the audience beforehand if you like, but you must be on the stage when the show starts, alright?
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(starts_in_three);

init_completed_third_show = ConvoScreen:new {
	id = "init_completed_third_show",
	leftDialog = "@conversation/quest_crowd_pleaser_manager:s_7223d3c0", -- Amazing. Simply amazing. You truly are one of the best performers I've seen in a long time. Here's a bonus for doing so well. Also, one of our regular performers has offered to teach you a new act. Maybe you can use it at your next show.
	stopConversation = "true",
	options = {}
}
theaterManagerConvoTemplate:addScreen(init_completed_third_show);

addConversationTemplate("theaterManagerConvoTemplate", theaterManagerConvoTemplate);