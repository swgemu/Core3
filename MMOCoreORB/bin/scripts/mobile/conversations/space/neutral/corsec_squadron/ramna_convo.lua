ramna_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ramnaConvoHandler",
	screens = {}
}

pilot_not_corsec = ConvoScreen:new {
	id = "pilot_not_corsec",
	leftDialog = "@conversation/corellia_privateer_tier3:s_ccf2f65c", --  You lost, buddy?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d30b5c72", "get_moving"}, -- Nah.
		{"@conversation/corellia_privateer_tier3:s_af22b9b2", "see_ya"}, -- I guess so.
	}
}
ramna_convo_template:addScreen(pilot_not_corsec);

completed_ramna = ConvoScreen:new {
	id = "completed_ramna",
	leftDialog = "@conversation/corellia_privateer_tier3:s_15be2c5c", -- Well %NU, it's time for you to go.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_87f3112e", "my_pleasure"}, -- Thanks for everything.
		{"@conversation/corellia_privateer_tier3:s_705da14d", "sorry_to_hear"}, -- Sorry to hear that.
	}
}
ramna_convo_template:addScreen(completed_ramna);

--[[

	Quest Line Missions

]]

-- Mission 1

first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_61e91afa", -- %TU. Good to meet you. I'm Commander Ramna. How are you liking Lok so far?
	animation = "greet",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_cc4b75d1", "no_place_like_home"}, -- Not bad.
		{"@conversation/corellia_privateer_tier3:s_8335bee5", "oh_yeah"}, -- I'd like it more if I had something to do.
	}
}
ramna_convo_template:addScreen(first_mission);

no_place_like_home = ConvoScreen:new {
	id = "no_place_like_home",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9f123cf0", -- I like it, though there's no place like Corellia.  So listen. You're reporting to me now. Let's get you up to speed.
	animation = "stretch",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_5e2a2bb1", "up_to_speed"}, -- Sounds good.
	}
}
ramna_convo_template:addScreen(no_place_like_home);

oh_yeah = ConvoScreen:new {
	id = "oh_yeah",
	leftDialog = "@conversation/corellia_privateer_tier3:s_d4f6cbf2", -- Oh yeah? Well maybe I can help you with your problem. We've got a disabled pirate ship, floating dead above the planet.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_212383c4", "something_like"}, -- Engine malfunction?
	}
}
ramna_convo_template:addScreen(oh_yeah);

up_to_speed = ConvoScreen:new {
	id = "up_to_speed",
	leftDialog = "@conversation/corellia_privateer_tier3:s_73d80fb", -- The Black Suns have been on our backs for a while, but they're finally starting to back off and things are back to normal. But I do have an assignment for you.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b2e340f6", "dead_ship"}, -- What's that?
	}
}
ramna_convo_template:addScreen(up_to_speed);

dead_ship = ConvoScreen:new {
	id = "dead_ship",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3675602", -- We've got a disabled pirate ship, floating dead above the planet.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_212383c4", "something_like"}, -- Engine malfunction?
	}
}
ramna_convo_template:addScreen(dead_ship);

something_like = ConvoScreen:new {
	id = "something_like",
	leftDialog = "@conversation/corellia_privateer_tier3:s_aeb32a6f", -- Something like that. The life-support systems are failing; they're desperate. They've asked us to reel them in.
	animation = "survey",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_ad728136", "not_so_bad"}, -- They MUST be desperate, to ask for our help.
		{"@conversation/corellia_privateer_tier3:s_9143af03", "cant_believe"}, -- You're sure they're pirates?
	}
}
ramna_convo_template:addScreen(something_like);

not_so_bad = ConvoScreen:new {
	id = "not_so_bad",
	leftDialog = "@conversation/corellia_privateer_tier3:s_1df277de", -- Maybe they've realized we're not so bad after all.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_2f9db7a", "still_criminals"}, -- Maybe.
	}
}
ramna_convo_template:addScreen(not_so_bad);

still_criminals = ConvoScreen:new {
	id = "still_criminals",
	leftDialog = "@conversation/corellia_privateer_tier3:s_2b85ccf3", -- Now just because we're rescuing them, that doesn't mean we're off the clock. These guys are still criminals. And now that the Black Suns are out of the picture, our arrangement with them is null and void.
	animation = "explain",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_8e42f486", "cuff_up"}, -- So I should arrest them?
	}
}
ramna_convo_template:addScreen(still_criminals);

cuff_up = ConvoScreen:new {
	id = "cuff_up",
	leftDialog = "@conversation/corellia_privateer_tier3:s_6c251948", -- You got it.
	animation = "point_forward",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_287bd3e4", "dont_care"}, -- Think they'll be surprised?
	}
}
ramna_convo_template:addScreen(cuff_up);

dont_care = ConvoScreen:new {
	id = "dont_care",
	leftDialog = "@conversation/corellia_privateer_tier3:s_dde9d959", -- Don't really care if they are. I'll see you when you get back.
	animation = "yawn",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(dont_care);

cant_believe = ConvoScreen:new {
	id = "cant_believe",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3dda8c36", -- They told us so themselves. And I know these guys. They've been around for a long time.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_5bf2f9e5", "out_to_lunch"}, -- I can't believe they're asking US for help.
	}
}
ramna_convo_template:addScreen(cant_believe);

out_to_lunch = ConvoScreen:new {
	id = "out_to_lunch",
	leftDialog = "@conversation/corellia_privateer_tier3:s_4831750e", -- I guess all the other pirates are out to lunch.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_7afb0972", "no_pirate_code"}, -- Whatever happened to the pirate code?
	}
}
ramna_convo_template:addScreen(out_to_lunch);

no_pirate_code = ConvoScreen:new {
	id = "no_pirate_code",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3d3852ed", -- Went bye-bye. How should I know? Look, the bottom line is, there are guys up there who are sucking air through a straw. They won't last much longer.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_cc93ce57", "still_criminals2"}, -- OK. I'll get them.
	}
}
ramna_convo_template:addScreen(no_pirate_code);

still_criminals2 = ConvoScreen:new {
	id = "still_criminals2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_2b85ccf3", -- Now just because we're rescuing them, that doesn't mean we're off the clock. These guys are still criminals. And now that the Black Suns are out of the picture, our arrangement with them is null and void.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_8e42f486", "cuff_up2"}, -- So I should arrest them?
	}
}
ramna_convo_template:addScreen(still_criminals2);

cuff_up2 = ConvoScreen:new {
	id = "cuff_up2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_6c251948", -- You got it.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_287bd3e4", "dont_care"}, -- Think they'll be surprised?
	}
}
ramna_convo_template:addScreen(cuff_up2);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_62241cb7", -- What's going on?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_dcc126b1", "keep_going"}, -- Just doing my job.
		{"@conversation/corellia_privateer_tier3:s_657871b9", "you_sure_did"}, -- Ran into a little bit of trouble up there.
	}
}
ramna_convo_template:addScreen(failed_first_mission);

keep_going = ConvoScreen:new {
	id = "keep_going",
	leftDialog = "@conversation/corellia_privateer_tier3:s_aca5b8fe", -- OK. Just keep doing it until it's done.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(keep_going);

you_sure_did = ConvoScreen:new {
	id = "you_sure_did",
	leftDialog = "@conversation/corellia_privateer_tier3:s_5ec3d0ab", -- You sure did. But you know what to do, right?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_13ad0318", "exactly1"}, -- I just need to finish what I started.
	}
}
ramna_convo_template:addScreen(you_sure_did);

exactly1 = ConvoScreen:new {
	id = "exactly1",
	leftDialog = "@conversation/corellia_privateer_tier3:s_d4866d33", -- Exactly.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(exactly1);

complete_mission1 = ConvoScreen:new {
	id = "complete_mission1",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7c722941", -- Oh boy. We have really got a problem on our hands now! I need skilled pilots. Let's continue your training. What's next for you?
	animation = "smack_self",
	playerAnimation = "",
	stopConversation = "false",
	options = {}
}
ramna_convo_template:addScreen(complete_mission1);

-- Mission 2

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_55c00fb4", -- Well how about THEM apples?!
	animation = "gesticulate_wildly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_eeb1457d", "were_black_suns"}, -- What HAPPENED up there?! Those guys handed me my hat!
		{"@conversation/corellia_privateer_tier3:s_7bec018d", "planned_all_along"}, -- That's what we get for trying to help out a bunch of grubby pirates!
	}
}
ramna_convo_template:addScreen(second_mission);

planned_all_along = ConvoScreen:new {
	id = "planned_all_along",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f436768c", -- They must have been planning this all along.
	animation = "",
	playerAnimation = "standing_raise_fist",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_a6b16355", "pretended_to_leave"}, -- Planning what? I'm still confused about what just happened.
	}
}
ramna_convo_template:addScreen(planned_all_along);

were_black_suns = ConvoScreen:new {
	id = "were_black_suns",
	leftDialog = "@conversation/corellia_privateer_tier3:s_55c00fb4", -- I noticed! Those were the Black Suns. They didn't leave after all!
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b427b7ce", "interest_underestimated"}, -- I thought we took care of that problem!
	}
}
ramna_convo_template:addScreen(were_black_suns);

interest_underestimated = ConvoScreen:new {
	id = "interest_underestimated",
	leftDialog = "@conversation/corellia_privateer_tier3:s_e1260dbe", -- Yeah. Well, we underestimated their interest in this area.
	animation = "shiver",
	playerAnimation = "stamp_feet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_4ec92de8", "dead_in_the_water"}, -- What happened to our arrangement with the other pirates?
	}
}
ramna_convo_template:addScreen(interest_underestimated);

dead_in_the_water = ConvoScreen:new {
	id = "dead_in_the_water",
	leftDialog = "@conversation/corellia_privateer_tier3:s_ef2c1d07", -- Dead in the water!
	animation = "gesticulate_wildly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b754dde0", "poor_guards"}, -- Obviously! Did you see how fast those prisoners took control of that ship?
	}
}
ramna_convo_template:addScreen(dead_in_the_water);

poor_guards = ConvoScreen:new {
	id = "poor_guards",
	leftDialog = "@conversation/corellia_privateer_tier3:s_36069595", -- Sure did. Those poor guards.
	animation = "sigh_deeply",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_1f325741", "we_were_idiots"}, -- Pfft.
	}
}
ramna_convo_template:addScreen(poor_guards);

we_were_idiots = ConvoScreen:new {
	id = "we_were_idiots",
	leftDialog = "@conversation/corellia_privateer_tier3:s_8f418b3a", -- We were IDIOTS to trust those pirates.
	animation = "sigh_deeply",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_7600e908", "our_problem_now"}, -- Well it wasn't exactly our idea!
	}
}
ramna_convo_template:addScreen(we_were_idiots);

our_problem_now = ConvoScreen:new {
	id = "our_problem_now",
	leftDialog = "@conversation/corellia_privateer_tier3:s_d714b5a0", -- Nope. Sure wasn't. But it's our problem now. The Black Suns must have brokered some kind of deal with the pirates.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_ca158be9", "stronger_than_ever"}, -- Or vice versa.
	}
}
ramna_convo_template:addScreen(our_problem_now);

stronger_than_ever = ConvoScreen:new {
	id = "stronger_than_ever",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f798d511", -- Sheesh. Who knows? Doesn't matter now. All of a sudden we're looking at an enemy who's stronger than ever.
	animation = "shake_head_disgust",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_f0b69eb", "break_the_alliance"}, -- Any ideas about what to do next?
	}
}
ramna_convo_template:addScreen(stronger_than_ever);

break_the_alliance = ConvoScreen:new {
	id = "break_the_alliance",
	leftDialog = "@conversation/corellia_privateer_tier3:s_68f733fc", -- As long as they're working together, they're unstoppable. We need to break this alliance, quick.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_10d3e04", "the_weaker_group"}, -- Yeah, but how?
	}
}
ramna_convo_template:addScreen(break_the_alliance);

the_weaker_group = ConvoScreen:new {
	id = "the_weaker_group",
	leftDialog = "@conversation/corellia_privateer_tier3:s_416e437c", -- Our best bet is to hit the weaker group.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_148bc3dc", "yes_pirate"}, -- You mean the pirates.
	}
}
ramna_convo_template:addScreen(the_weaker_group);

yes_pirate = ConvoScreen:new {
	id = "yes_pirate",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a5e6e5e7", -- Yep.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_de4a941c", "what_they_need"}, -- OK, but how?
	}
}
ramna_convo_template:addScreen(yes_pirate);

what_they_need = ConvoScreen:new {
	id = "what_they_need",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3ca5a892", -- Well, what do pirates need to do their jobs?
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d7bf7b44", "different_pirates"}, -- A pegleg and a parrot?
	}
}
ramna_convo_template:addScreen(what_they_need);

different_pirates = ConvoScreen:new {
	id = "different_pirates",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9b2b6284", -- They're not THAT kind of pirates, smart guy.
	animation = "laugh_titter",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_798f8f83", "weapons_shipment"}, -- They need weapons.
	}
}
ramna_convo_template:addScreen(different_pirates);

weapons_shipment = ConvoScreen:new {
	id = "weapons_shipment",
	leftDialog = "@conversation/corellia_privateer_tier3:s_5991827d", -- Bingo. Word is, they're expecting a weapons shipment in the Dathomir System. I'd like you to find the freighter ship and confiscate their cargo.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d24a2285", "good_luck_mission2"}, -- Will do.
	}
}
ramna_convo_template:addScreen(weapons_shipment);

good_luck_mission2 = ConvoScreen:new {
	id = "good_luck_mission2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_90422eb5", -- Good luck.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(good_luck_mission2);

pretended_to_leave = ConvoScreen:new {
	id = "pretended_to_leave",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3ca83562", -- The Black Suns only pretended to leave. They were just waiting for the right time to strike!
	animation = "",
	playerAnimation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_c69ddd08", "took_advantage"}, -- And that prison ship?
	}
}
ramna_convo_template:addScreen(pretended_to_leave);

took_advantage = ConvoScreen:new {
	id = "took_advantage",
	leftDialog = "@conversation/corellia_privateer_tier3:s_1fa985de", --  Well, either they took advantage of the situation, and decided to commandeer the vehicle, or they were in on the Black Suns' plans.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_545738f9", "bet_the_latter"}, -- I bet it's the latter.
	}
}
ramna_convo_template:addScreen(took_advantage);

bet_the_latter = ConvoScreen:new {
	id = "bet_the_latter",
	leftDialog = "@conversation/corellia_privateer_tier3:s_868a3d1c", -- I bet you're right.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_9f8d6da8", "shouldnt_surprise"}, -- So it's true! The pirates and Black Suns ARE working together.
	}
}
ramna_convo_template:addScreen(bet_the_latter)

shouldnt_surprise = ConvoScreen:new {
	id = "shouldnt_surprise",
	leftDialog = "@conversation/corellia_privateer_tier3:s_868a3d1c", -- Yep. Surprised?
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_3269c6d", "the_only_surprise"}, -- Not really.
		{"@conversation/corellia_privateer_tier3:s_e48d5a", "why_bail"}, -- I need to transfer out of this unit.
	}
}
ramna_convo_template:addScreen(shouldnt_surprise)

the_only_surprise = ConvoScreen:new {
	id = "the_only_surprise",
	leftDialog = "@conversation/corellia_privateer_tier3:s_b08d0506", -- The only surprising thing is that it took them this long to join forces. If we're going to beat these guys, we're going to have to think smart.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_f0b69eb", "break_the_alliance"}, -- Any ideas about what to do next?
	}
}
ramna_convo_template:addScreen(the_only_surprise)

why_bail = ConvoScreen:new {
	id = "why_bail",
	leftDialog = "@conversation/corellia_privateer_tier3:s_841d27db", -- Why?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_529d94c9", "what_kind_soldier"}, -- Because there is no way we're going to be able to beat the Black Suns!
	}
}
ramna_convo_template:addScreen(why_bail)

what_kind_soldier = ConvoScreen:new {
	id = "what_kind_soldier",
	leftDialog = "@conversation/corellia_privateer_tier3:s_4aa060bb", -- Buck up! What kind of soldier are you?
	animation = "pound_fist_palm",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_199af81e", "just_do_better"}, -- Hey, I've seen those guys at work! They're good!
	}
}
ramna_convo_template:addScreen(what_kind_soldier)

just_do_better = ConvoScreen:new {
	id = "just_do_better",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a0e7bdff", -- Well then we just have to be better. Are you going to calm down, or do I have to give you a smack?
	animation = "stamp_feet",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_587cb454", "change_equation"}, -- I'm OK.
	}
}
ramna_convo_template:addScreen(just_do_better)

change_equation = ConvoScreen:new {
	id = "change_equation",
	leftDialog = "@conversation/corellia_privateer_tier3:s_28670323", -- All right then! Now let's FOCUS. Black Suns + pirates > us. We need to change that equation.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_fcf4d778", "the_weaker_group2"}, -- How?
	}
}
ramna_convo_template:addScreen(change_equation)

the_weaker_group2 = ConvoScreen:new {
	id = "the_weaker_group2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_416e437c", -- Our best bet is to hit the weaker group.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_148bc3dc", "yes_pirate2"}, -- You mean the pirates.
	}
}
ramna_convo_template:addScreen(the_weaker_group2);

yes_pirate2 = ConvoScreen:new {
	id = "yes_pirate2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a5e6e5e7", -- Yep.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_de4a941c", "what_they_need2"}, -- OK, but how?
	}
}
ramna_convo_template:addScreen(yes_pirate2);

what_they_need2 = ConvoScreen:new {
	id = "what_they_need2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3ca5a892", -- Well, what do pirates need to do their jobs?
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_798f8f83", "weapons_shipment2"}, -- They need weapons.
	}
}
ramna_convo_template:addScreen(what_they_need2);

weapons_shipment2 = ConvoScreen:new {
	id = "weapons_shipment2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_5991827d", -- Bingo. Word is, they're expecting a weapons shipment in the Dathomir System. I'd like you to find the freighter ship and confiscate their cargo.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d24a2285", "good_luck_mission2_2"}, -- Will do.
	}
}
ramna_convo_template:addScreen(weapons_shipment2);

good_luck_mission2_2 = ConvoScreen:new {
	id = "good_luck_mission2_2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_90422eb5", -- Good luck.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(good_luck_mission2_2);

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_b53ef7a5", -- What is this? What are you doing here?
	animation = "gesticulate_wildly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_192771db", "need_good_news"}, -- It's OK! Just ran into a few problems.
		{"@conversation/corellia_privateer_tier3:s_c8ea3e2b", "working_with_pirates"}, -- They cleaned my clock.
	}
}
ramna_convo_template:addScreen(failed_second_mission);

need_good_news = ConvoScreen:new {
	id = "need_good_news",
	leftDialog = "@conversation/corellia_privateer_tier3:s_359bb23b", -- Every report I get these days is a bad one. Do me a favor and bring me some GOOD news, would ya? Get back to work!
	animation = "smack_self",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(need_good_news);

working_with_pirates = ConvoScreen:new {
	id = "working_with_pirates",
	leftDialog = "@conversation/corellia_privateer_tier3:s_d11614d5", -- Are you working with the pirates or something?
	animation = "point_accusingly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_7426e000", "then_go_fight"}, -- No!
	}
}
ramna_convo_template:addScreen(working_with_pirates);

then_go_fight = ConvoScreen:new {
	id = "then_go_fight",
	leftDialog = "@conversation/corellia_privateer_tier3:s_215042ad", -- Then get back out there and fight!
	animation = "point_away",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(then_go_fight);

complete_mission2 = ConvoScreen:new {
	id = "complete_mission2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_97c1c260", -- Nice work up there. That engineer's going to be a big help to us. He may not WANT to help us, but that's too bad. He'll be busy for a while. Meanwhile, let's get you back to your studies.
	animation = "applause_excited",
	playerAnimation = "",
	stopConversation = "false",
	options = {}
}
ramna_convo_template:addScreen(complete_mission2);

-- Mission 3















































complete_mission3 = ConvoScreen:new {
	id = "complete_mission3",
	leftDialog = "@conversation/corellia_privateer_tier3:s_c0786e56", -- Ha! Well DONE, %NU! We showed those Black Suns who's boss, didn't we? I wish I could have seen the look on their faces when you blasted them! Come on; it's time for another lesson.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {}
}
ramna_convo_template:addScreen(complete_mission3);

-- Mission 4

complete_mission4 = ConvoScreen:new {
	id = "complete_mission4",
	leftDialog = "@conversation/corellia_privateer_tier3:s_191d4365", -- "How about that? I guess those pirates aren't so tough after all.  Come on, let's get you a new skill.
	animation = "stretch",
	playerAnimation = "",
	stopConversation = "false",
	options = {}
}
ramna_convo_template:addScreen(complete_mission4);




--[[

	Conversation Enders

]]

get_moving = ConvoScreen:new {
	id = "get_moving",
	leftDialog = "@conversation/corellia_privateer_tier3:s_b26e36ad", -- If you're not a privateer, you sure as heck ARE lost. Get moving.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(get_moving);

see_ya = ConvoScreen:new {
	id = "see_ya",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9e0c4569", -- That's what I thought. See ya around.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(see_ya);

not_tier3 = ConvoScreen:new {
	id = "not_tier3",
	leftDialog = "@conversation/corellia_privateer_tier3:s_61b78d18", -- Psst! I think you took a wrong turn somewhere. Your boss is waiting for you.
	animation = "whisper",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(not_tier3);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_c816ccac", -- Hey listen, we've ALL got work to do.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(on_mission);

train_warships = ConvoScreen:new {
	id = "train_warships",
	leftDialog = "@conversation/corellia_privateer_tier3:s_fc33d4d3", -- Done! See me when you're ready. We've got work to do.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(train_warships);

train_components = ConvoScreen:new {
	id = "train_components",
	leftDialog = "@conversation/corellia_privateer_tier3:s_fc33d4d3", -- Done! See me when you're ready. We've got work to do.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(train_components);

train_techniques = ConvoScreen:new {
	id = "train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier3:s_fc33d4d3", -- Done! See me when you're ready. We've got work to do.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(train_techniques);

train_programming = ConvoScreen:new {
	id = "train_programming",
	leftDialog = "@conversation/corellia_privateer_tier3:s_fc33d4d3", -- Done! See me when you're ready. We've got work to do.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(train_programming);

my_pleasure = ConvoScreen:new {
	id = "my_pleasure",
	leftDialog = "@conversation/corellia_privateer_tier3:s_57bdf799", -- My pleasure. From now on you'll  be reporting to Adwan Turoldine. You'll like him, I think. Currently he's working undercover in the cantina at the Mining Outpost of Dantooine.  Take care not to blow his cover!
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(my_pleasure);

sorry_to_hear = ConvoScreen:new {
	id = "sorry_to_hear",
	leftDialog = "@conversation/corellia_privateer_tier3:s_4d0823a4", -- Me too. We work well together, I think. But now you'll be reporting to Adwan Turoldine, and he's one of the best. Currently he's working undercover in the cantina at the Mining Outpost of Dantooine.  Take care not to blow his cover!  See you around, %NU.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(sorry_to_hear);



addConversationTemplate("ramna_convo_template", ramna_convo_template);
