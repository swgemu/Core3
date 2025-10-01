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

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f37012cf", -- Golly! That didn't work out the way we planned it.
	animation = "rub_belly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d33d4e93", "every_move"}, -- No kidding.
		{"@conversation/corellia_privateer_tier3:s_f89feda0", "pirates_had_intel"}, -- You THINK?!!?
		{"@conversation/corellia_privateer_tier3:s_f50b28e8", "comlink_hole"}, -- I don't want to talk about it. I just want to accomplish something, for a change.
	}
}
ramna_convo_template:addScreen(third_mission);

every_move = ConvoScreen:new {
	id = "every_move",
	leftDialog = "@conversation/corellia_privateer_tier3:s_2a37df4a", -- The problem is that the pirates know about our every move.
	animation = "rub_chin_thoughtful",
	playerAnimation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_44d57431", "remember_dead_ship"}, -- How can that be?
		{"@conversation/corellia_privateer_tier3:s_1001fca4", "oh_right_forgot"}, -- Of course they do! We've already discussed the problem.
	}
}
ramna_convo_template:addScreen(every_move);

remember_dead_ship = ConvoScreen:new {
	id = "remember_dead_ship",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9aac04b2", -- Remember that pirate ship, the one that was floating dead over Corellia?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_52917b0d", "computer_virus"}, -- Of course.
	}
}
ramna_convo_template:addScreen(remember_dead_ship);

oh_right_forgot = ConvoScreen:new {
	id = "oh_right_forgot",
	leftDialog = "@conversation/corellia_privateer_tier3:s_bc0a2234", -- Oh! Right. I forgot.
	animation = "slump_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_52917b0d", "oops_forgot"}, -- I just want a freaking solution!
	}
}
ramna_convo_template:addScreen(oh_right_forgot);

computer_virus = ConvoScreen:new {
	id = "computer_virus",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9c4357e6", -- Well, apparently the ship was carrying some kind of computer virus. It infected your ship's communication system, basically creating an open channel. The pirates can listen in to all of our communications.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_8fcc3b5a", "engineers_working"}, -- Oh for crying out loud.
	}
}
ramna_convo_template:addScreen(computer_virus);

engineers_working = ConvoScreen:new {
	id = "engineers_working",
	leftDialog = "@conversation/corellia_privateer_tier3:s_74f40f1d", -- We've got engineers working on the problem as we speak.
	animation = "",
	playerAnimation = "smack_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d5206411", "engineers_not_done"}, -- It's not fixed?
	}
}
ramna_convo_template:addScreen(engineers_working);

engineers_not_done = ConvoScreen:new {
	id = "engineers_not_done",
	leftDialog = "@conversation/corellia_privateer_tier3:s_727409be", -- Not yet.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d2ab8937", "need_be_smart"}, -- Then we're out of luck.
	}
}
ramna_convo_template:addScreen(engineers_not_done);

need_be_smart = ConvoScreen:new {
	id = "need_be_smart",
	leftDialog = "@conversation/corellia_privateer_tier3:s_1fc81cc9", -- Or telepathic.
	animation = "tap_head",
	playerAnimation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_355b403f", "more_low_tech"}, -- Then we're out of luck.
	}
}
ramna_convo_template:addScreen(need_be_smart);

more_low_tech = ConvoScreen:new {
	id = "more_low_tech",
	leftDialog = "@conversation/corellia_privateer_tier3:s_5f3b7a4", -- Nah! Something much more low-tech.
	animation = "laugh_titter",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_33360d50", "face_the_facts"}, -- What have you got in mind?.
	}
}
ramna_convo_template:addScreen(more_low_tech);

face_the_facts = ConvoScreen:new {
	id = "face_the_facts",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9d1e1c8d", -- As long as they can hear us, they've got the upper hand. So let's face facts and give up.
	animation = "shrug_hands",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d590d63c", "flip_the_script"}, -- WHAT?!
	}
}
ramna_convo_template:addScreen(face_the_facts);

pirates_had_intel = ConvoScreen:new {
	id = "pirates_had_intel",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a8412b0", -- Those pirates knew right where to find you...
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_671470cf", "had_the_intel"}, -- It's almost like they KNEW I was going to be there.
		{"@conversation/corellia_privateer_tier3:s_6b7c6e79", "oops_forgot"}, -- Of course they did! We've already discussed the problem.
	}
}
ramna_convo_template:addScreen(pirates_had_intel);

had_the_intel = ConvoScreen:new {
	id = "had_the_intel",
	leftDialog = "@conversation/corellia_privateer_tier3:s_956853f", -- Yes. It's like they had classified information or something.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_43feb101", "stop_shouting"}, -- I THINK THEY DID!!
	}
}
ramna_convo_template:addScreen(had_the_intel);

stop_shouting = ConvoScreen:new {
	id = "stop_shouting",
	leftDialog = "@conversation/corellia_privateer_tier3:s_aa4936a9", -- All right! No need to shout!
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_24f6863f", "please_stop"}, -- I'm the one getting shot at! I think I have a right to shout!
	}
}
ramna_convo_template:addScreen(stop_shouting);

please_stop = ConvoScreen:new {
	id = "please_stop",
	leftDialog = "@conversation/corellia_privateer_tier3:s_8e67895a", -- Please. You're upsetting me.
	animation = "cover_mouth",
	playerAnimation = "pound_fist_chest",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d8ec7fac", "can_be_angry"}, -- I DON'T CARE!!
	}
}
ramna_convo_template:addScreen(please_stop);

can_be_angry = ConvoScreen:new {
	id = "can_be_angry",
	leftDialog = "@conversation/corellia_privateer_tier3:s_81e58210", -- OK, OK. You've got a right to be angry. Give me a chance to speak, will ya?.
	animation = "implore",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_1d231c8f", "the_pirates_knew"}, -- You better have something good to say.
	}
}
ramna_convo_template:addScreen(can_be_angry);

the_pirates_knew = ConvoScreen:new {
	id = "the_pirates_knew",
	leftDialog = "@conversation/corellia_privateer_tier3:s_6dc79733", -- As a matter of fact, I do. OK. First of all, we know for a fact that the pirates DID know about your movements.
	animation = "cough_polite",
	playerAnimation = "tap_foot",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_fcf4d778", "remeber_ship"}, -- How?
	}
}
ramna_convo_template:addScreen(the_pirates_knew);

remeber_ship = ConvoScreen:new {
	id = "remeber_ship",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9af2e537", -- Remember the pirate ship you rescued?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_8dd36524", "going_to_love"}, -- Sure.
	}
}
ramna_convo_template:addScreen(remeber_ship);

going_to_love = ConvoScreen:new {
	id = "going_to_love",
	leftDialog = "@conversation/corellia_privateer_tier3:s_4cd655f5", -- You're going to love this.
	animation = "shake_head_disgust",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b8b1e69c", "ship_virus"}, -- Hit me.
	}
}
ramna_convo_template:addScreen(going_to_love);

ship_virus = ConvoScreen:new {
	id = "ship_virus",
	leftDialog = "@conversation/corellia_privateer_tier3:s_66691f62", -- The ship was carrying a virus that infected your ship's computer system. It gave the pirates a window into all CorSec communications.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_38e3a35a", "pretty_annoying"}, -- That explains it.
	}
}
ramna_convo_template:addScreen(ship_virus);

pretty_annoying = ConvoScreen:new {
	id = "pretty_annoying",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7b3d8608", -- Pretty annoying, eh?
	animation = "whisper",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_c4d60644", "blame_engineer"}, -- I'll say.
	}
}
ramna_convo_template:addScreen(pretty_annoying);

blame_engineer = ConvoScreen:new {
	id = "blame_engineer",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f9b4dab6", -- The engineer you brought back? He's the guy who designed the original virus. I figure, he broke it, he can fix it too.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_ddb75eb1", "not_fixed"}, -- HAS he fixed it yet?
	}
}
ramna_convo_template:addScreen(blame_engineer);

not_fixed = ConvoScreen:new {
	id = "not_fixed",
	leftDialog = "@conversation/corellia_privateer_tier3:s_b5f15b19", --  Not yet.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_faab88c", "just_give_up"}, -- So what are we going to do?
	}
}
ramna_convo_template:addScreen(not_fixed);

just_give_up = ConvoScreen:new {
	id = "just_give_up",
	leftDialog = "@conversation/corellia_privateer_tier3:s_8af6aa3e", -- Give up, I guess
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d590d63c", "flip_the_script"}, -- WHAT?!
	}
}
ramna_convo_template:addScreen(just_give_up);

flip_the_script = ConvoScreen:new {
	id = "flip_the_script",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f61487ff", -- What do you think?
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_442e44f0", "maybe_theyll_think"}, -- I think you're an idiot!
	}
}
ramna_convo_template:addScreen(flip_the_script);

maybe_theyll_think = ConvoScreen:new {
	id = "maybe_theyll_think",
	leftDialog = "@conversation/corellia_privateer_tier3:s_f61487ff", -- Hopefully THEY'LL think I'm an idiot too.
	animation = "listen",
	playerAnimation = "smack_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_2313ac9e", "false_win"}, -- What are you talking about?
	}
}
ramna_convo_template:addScreen(maybe_theyll_think);

false_win = ConvoScreen:new {
	id = "false_win",
	leftDialog = "@conversation/corellia_privateer_tier3:s_e26f7766", -- If the Black Suns think we're giving up, they'll relax. Feel like they've won. And a relaxed enemy is easy to beat.
	animation = "shrug_hands",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_af180142", "lay_low_now"}, -- Tricky!
	}
}
ramna_convo_template:addScreen(false_win);

lay_low_now = ConvoScreen:new {
	id = "lay_low_now",
	leftDialog = "@conversation/corellia_privateer_tier3:s_fc05d09", -- Tricky if it works, stupid if it doesn't. We'll see. Listen, for now, we're going to just lay low. We've got a CorSec ship out there. We want to transfer all those weapons and personnel to a ship that hangs lower in the planet's ozone layer.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_9a672aca", "act_normal_on_comms"}, -- They'll think it's a sign of a retreat
	}
}
ramna_convo_template:addScreen(lay_low_now);

act_normal_on_comms = ConvoScreen:new {
	id = "act_normal_on_comms",
	leftDialog = "@conversation/corellia_privateer_tier3:s_75bc266c", -- They sure will. But listen to me. The only way this plan can work is if they think we're not on to them. So act normal - especially over coms.
	animation = "wave_finger_warning",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_67e6df55", "get_into_position"}, -- Okay.
	}
}
ramna_convo_template:addScreen(act_normal_on_comms);

get_into_position = ConvoScreen:new {
	id = "get_into_position",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3aef69fa", -- Once we've got our problem solved, we're going to move into position. Here's the sign. Ready?
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_a5e6e5e7", "go_on_patrol"}, -- Yep.
	}
}
ramna_convo_template:addScreen(get_into_position);

go_on_patrol = ConvoScreen:new {
	id = "go_on_patrol",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9ff4de20", -- When I tell you to take patrol, that's your cue. Take the patrol as ordered, but at the end of it, you'll be in position for a massive attack.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_bc375f79", "got_it_100"}, -- Got it.
	}
}
ramna_convo_template:addScreen(go_on_patrol);

got_it_100 = ConvoScreen:new {
	id = "got_it_100",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a8806358", -- So we understand each other?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_5904df36", "dant_operations"}, -- 100%.
	}
}
ramna_convo_template:addScreen(got_it_100);

dant_operations = ConvoScreen:new {
	id = "dant_operations",
	leftDialog = "@conversation/corellia_privateer_tier3:s_423a90e7", -- Get out to the Dantooine System, we will have an operative up there to set up the operation.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(dant_operations);

oops_forgot = ConvoScreen:new {
	id = "oops_forgot",
	leftDialog = "@conversation/corellia_privateer_tier3:s_53213682", -- I think we've got one. But we're going to have to be tricky.
	animation = "rub_chin_thoughtful",
	playerAnimation = "stamp_feet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_c261cfae", "no_moves_until_patch"}, -- No problem.
	}
}
ramna_convo_template:addScreen(oops_forgot);

no_moves_until_patch = ConvoScreen:new {
	id = "no_moves_until_patch",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a1fbb23f", -- We don't want to make any aggressive moves - not until the comlink's patched.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_c261cfae", "better_believe"}, -- Is that engineer working on it?
	}
}
ramna_convo_template:addScreen(no_moves_until_patch);

better_believe = ConvoScreen:new {
	id = "better_believe",
	leftDialog = "@conversation/corellia_privateer_tier3:s_8e888943", -- You better believe he is.
	animation = "pound_fist_palm",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_5dc82348", "play_possum"}, -- Good.
	}
}
ramna_convo_template:addScreen(better_believe);

play_possum = ConvoScreen:new {
	id = "play_possum",
	leftDialog = "@conversation/corellia_privateer_tier3:s_b4ebb4b3", -- In the meantime, what we're going to do is lay low. Play possum.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_42880861", "low_atmo_ship"}, -- Okay...
	}
}
ramna_convo_template:addScreen(play_possum);

low_atmo_ship = ConvoScreen:new {
	id = "low_atmo_ship",
	leftDialog = "@conversation/corellia_privateer_tier3:s_71b6239a", -- We've got a CorSec ship out there. We want to transfer all those weapons and personnel to a ship that hangs lower in the planet's atmosphere.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_9a672aca", "act_normal_on_comms"}, -- They'll think it's a sign of a retreat.
	}
}
ramna_convo_template:addScreen(low_atmo_ship);

comlink_hole = ConvoScreen:new {
	id = "comlink_hole",
	leftDialog = "@conversation/corellia_privateer_tier3:s_956853f", -- OK. Well you're up to speed on everything that's happened so far, right? The hole in our comlink system, all that?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_ad973bd9", "non_aggressive"}, -- Yeah.
	}
}
ramna_convo_template:addScreen(comlink_hole);

non_aggressive = ConvoScreen:new {
	id = "non_aggressive",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9089ef38", -- So, we don't want to make any aggressive moves - not until we have some semblance of privacy.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_202eca31", "play_possum2"}, -- Makes sense.
	}
}
ramna_convo_template:addScreen(non_aggressive);

play_possum2 = ConvoScreen:new {
	id = "play_possum2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_3dd7f9c6", -- So what we're going to do it lay low. Play possum.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_42880861", "transfer_weapons_ship"}, -- Okay...
	}
}
ramna_convo_template:addScreen(play_possum2);

transfer_weapons_ship = ConvoScreen:new {
	id = "transfer_weapons_ship",
	leftDialog = "@conversation/corellia_privateer_tier3:s_19b25af3", -- We've got a CorSec ship out there. We want to transfer all those weapons and personnel to a ship that hangs lower in the planet's ozone layer.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_9a672aca", "act_normal_on_comms"}, -- They'll think it's a sign of a retreat.
	}
}
ramna_convo_template:addScreen(transfer_weapons_ship);

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_9d1ce696", -- Hey %NU! What gives? I thought we had a plan.
	animation = "greet",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_bf7ad2b4", "blew_it"}, -- I blew it.
		{"@conversation/corellia_privateer_tier3:s_5d9d0e58", "on_the_job"}, -- I'm still on the job.
	}
}
ramna_convo_template:addScreen(failed_third_mission);

blew_it = ConvoScreen:new {
	id = "blew_it",
	leftDialog = "@conversation/corellia_privateer_tier3:s_cfd01162", -- Don't say that! You just had a setback. It's nothing to worry about. The REAL mistake would be giving up.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_25d2c630", "go_back_get_some"}, -- You sound like my mom.
	}
}
ramna_convo_template:addScreen(blew_it);

go_back_get_some = ConvoScreen:new {
	id = "go_back_get_some",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7d83809c", -- Well I'm SOMEBODY'S mom! Go on, get back out there!
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(go_back_get_some);

on_the_job = ConvoScreen:new {
	id = "on_the_job",
	leftDialog = "@conversation/corellia_privateer_tier3:s_1cab7ef2", -- Need anything from me? Can I help?
	animation = "offer_affection",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_77b0e9f8", "go_back_get_some"}, -- No. I can do it.
	}
}
ramna_convo_template:addScreen(on_the_job);

go_back_get_some = ConvoScreen:new {
	id = "go_back_get_some",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a26f4215", -- OK. I'm counting on you.
	animation = "rub_chin_thoughtful",
	playerAnimation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(go_back_get_some);

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

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_44d4901e", -- I think things are going our way.
	animation = "greet",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_dfe0e1a2", "scrambling_black_suns"}, -- What's going on up there?
		{"@conversation/corellia_privateer_tier3:s_b95fcaf8", "sure_did_work"}, -- Your plan worked.
	}
}
ramna_convo_template:addScreen(fourth_mission);

scrambling_black_suns = ConvoScreen:new {
	id = "scrambling_black_suns",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7546ce62", -- The Black Suns are scrambling. They don't know what hit them!
	animation = "laugh_cackle",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_6ddb0d47", "messed_up_plans"}, -- I hit them.
	}
}
ramna_convo_template:addScreen(scrambling_black_suns);

messed_up_plans = ConvoScreen:new {
	id = "messed_up_plans",
	leftDialog = "@conversation/corellia_privateer_tier3:s_cc075a69", -- You sure did. We've messed up their plans, but good. And now we're going to press our advantage.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_a6198527", "send_message"}, -- Sounds like you've got a mission for me.
	}
}
ramna_convo_template:addScreen(messed_up_plans);

send_message = ConvoScreen:new {
	id = "send_message",
	leftDialog = "@conversation/corellia_privateer_tier3:s_36f54748", -- You sure did. We've messed up their plans, but good. And now we're going to press our advantage.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b52f3018", "double_crossers"}, -- To who?
	}
}
ramna_convo_template:addScreen(send_message);

double_crossers = ConvoScreen:new {
	id = "double_crossers",
	leftDialog = "@conversation/corellia_privateer_tier3:s_467f5524", -- To those double-crossing pirates, that's who..
	animation = "pound_fist_palm",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_cd445db2", "payback_time"}, -- I like the sound of that.
	}
}
ramna_convo_template:addScreen(double_crossers);

payback_time = ConvoScreen:new {
	id = "payback_time",
	leftDialog = "@conversation/corellia_privateer_tier3:s_537e4c85", -- This would never have happened, if they hadn't taken advantage of our trusting nature. So it's payback time. I want you to go after the captain who radioed in for help. He's the guy who started this whole thing.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_43aecff6", "no_trial_death"}, -- What do I do when I get him?
	}
}
ramna_convo_template:addScreen(payback_time);

no_trial_death = ConvoScreen:new {
	id = "no_trial_death",
	leftDialog = "@conversation/corellia_privateer_tier3:s_1ca5111b", -- I'm not interested in any long, drawn-out trial.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_53faf560", "yes_kill"}, -- You want me to kill him.
	}
}
ramna_convo_template:addScreen(no_trial_death);

yes_kill = ConvoScreen:new {
	id = "yes_kill",
	leftDialog = "@conversation/corellia_privateer_tier3:s_a5e6e5e7", -- Yep.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d4c80032", "intercept_in_endor"}, -- My pleasure. Where can I find this guy?
	}
}
ramna_convo_template:addScreen(yes_kill);

intercept_in_endor = ConvoScreen:new {
	id = "intercept_in_endor",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7aa63d3c", -- You can intercept him in the Endor system. Good luck.
	animation = "dismiss",
	playerAnimation = "flex_biceps",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(intercept_in_endor);

sure_did_work = ConvoScreen:new {
	id = "sure_did_work",
	leftDialog = "@conversation/corellia_privateer_tier3:s_626f9f67", -- Sure did! Surprise!
	animation = "pose_proudly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_785dc9dc", "was_unexpected"}, -- It felt good to turn around and kick those Black Suns where it counts.
	}
}
ramna_convo_template:addScreen(sure_did_work);

was_unexpected = ConvoScreen:new {
	id = "was_unexpected",
	leftDialog = "@conversation/corellia_privateer_tier3:s_191e8e9e", -- Especially since they weren't expecting it! They thought they owned us. Boy were they wrong!
	animation = "laugh_titter",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_27244a5b", "press_advantage"}, -- Ha.
		{"@conversation/corellia_privateer_tier3:s_f313dc31", "he_made_it"}, -- They didn't exactly roll over and die. They went after that CorSec officer, after all.
	}
}
ramna_convo_template:addScreen(was_unexpected);

press_advantage = ConvoScreen:new {
	id = "press_advantage",
	leftDialog = "@conversation/corellia_privateer_tier3:s_80c0a2c4", -- Ha is right. And now we're going to press our advantage.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_80c0a2c4", "got_a_mission"}, -- Sounds like you've got a mission for me.
	}
}
ramna_convo_template:addScreen(press_advantage)

got_a_mission = ConvoScreen:new {
	id = "got_a_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_36f54748", -- I sure do. Listen, you're good. And I put my good pilots to work. I think it's time for us to send a message.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_b52f3018", "double_crossing_pirates"}, -- To who?
	}
}
ramna_convo_template:addScreen(got_a_mission)

double_crossing_pirates = ConvoScreen:new {
	id = "double_crossing_pirates",
	leftDialog = "@conversation/corellia_privateer_tier3:s_467f5524", -- To those double-crossing pirates, that's who.
	animation = "pound_fist_palm",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_cd445db2", "payback_time"}, -- I like the sound of that.
	}
}
ramna_convo_template:addScreen(double_crossing_pirates)

he_made_it = ConvoScreen:new {
	id = "he_made_it",
	leftDialog = "@conversation/corellia_privateer_tier3:s_45e3cf78", -- They TRIED to. He made it, thanks to you.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_67d280da", "press_advantage2"}, -- He would have done the same for me.
	}
}
ramna_convo_template:addScreen(he_made_it)

press_advantage2 = ConvoScreen:new {
	id = "press_advantage2",
	leftDialog = "@conversation/corellia_privateer_tier3:s_c2675d2d", -- We need to press our advantage.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_a6198527", "got_a_mission"}, -- Sounds like you've got a mission for me.
	}
}
ramna_convo_template:addScreen(press_advantage2)

failed_fourth_mission = ConvoScreen:new {
	id = "failed_fourth_mission",
	leftDialog = "@conversation/corellia_privateer_tier3:s_7d0ca743", -- Absolutely.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_d9cced1f", "get_back_out"}, -- Absolutely.
		{"@conversation/corellia_privateer_tier3:s_7d4eaca7", "cant_get_out"}, -- I don't know.
	}
}
ramna_convo_template:addScreen(failed_fourth_mission)

get_back_out = ConvoScreen:new {
	id = "get_back_out",
	leftDialog = "@conversation/corellia_privateer_tier3:s_5141a2c2", -- Good. Get back out there.
	animation = "",
	playerAnimation = "pound_fist_palm",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(get_back_out)

cant_get_out = ConvoScreen:new {
	id = "cant_get_out",
	leftDialog = "@conversation/corellia_privateer_tier3:s_51db29e8", -- We can't get out of this without you.
	animation = "",
	playerAnimation = "slump_head",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_2f9db7a", "go_on"}, -- Maybe.
	}
}
ramna_convo_template:addScreen(cant_get_out)

go_on = ConvoScreen:new {
	id = "go_on",
	leftDialog = "@conversation/corellia_privateer_tier3:s_edb238bc", -- Go on.
	animation = "offer_affection",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier3:s_2836e6b5", ""}, -- OK.
	}
}
ramna_convo_template:addScreen(go_on)

see_you_soon = ConvoScreen:new {
	id = "see_you_soon",
	leftDialog = "@conversation/corellia_privateer_tier3:s_c402784e", -- See you soon.
	animation = "wave1",
	playerAnimation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
ramna_convo_template:addScreen(see_you_soon)

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
