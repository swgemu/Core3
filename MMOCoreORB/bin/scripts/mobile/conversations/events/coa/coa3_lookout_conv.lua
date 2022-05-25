coa3LookoutConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "coa3LookoutConvoHandler",
	screens = {}
}


-- First Contact After Coordinator

init_first_round = ConvoScreen:new {
	id = "init_first_round",
	leftDialog = "@conversation/coa3sharedlookout:s_74f0143a", -- Ya talkin' to me? Who sent ya?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_70614d9f", "response_valerian"}, -- I come on behalf of Valerian.
		{"@conversation/coa3sharedlookout:s_f9883674", "response_jabba"}, -- I work for Jabba.
		{"@conversation/coa3sharedlookout:s_dbe291a4", "response_alkhara"}, -- Alkhara sent me.
		{"@conversation/coa3sharedlookout:s_b1f8b064", "darn_right"}, -- I'm sorry I thought you were someone else.
	}
}
coa3LookoutConvoTemplate:addScreen(init_first_round);

response_valerian = ConvoScreen:new {
	id = "response_valerian",
	leftDialog = "@conversation/coa3sharedlookout:s_8c75fac0", -- What!? I mean... I hope she's doing ok and all... Uh... Never mind.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(response_valerian);

response_jabba = ConvoScreen:new {
	id = "response_jabba",
	leftDialog = "@conversation/coa3sharedlookout:s_c6ca8aca", -- Ya do? I can't give ya anything, what I have is mine. But take a rest if ya need it. So what sort of work do you do do?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_e1e1e0ac", "do_this_do_that"}, -- Whatever Jabba asks me to do.
		{"@conversation/coa3sharedlookout:s_90b36308", "good_philosophy"}, -- Whatever makes me the most money.
		{"@conversation/coa3sharedlookout:s_bb54f6cc", "response_fine"}, -- None of your business.
	}
}
coa3LookoutConvoTemplate:addScreen(response_jabba);

response_alkhara = ConvoScreen:new {
	id = "response_alkhara",
	leftDialog = "@conversation/coa3sharedlookout:s_fac80094", -- Really? That's mighty... fine...
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(response_alkhara);

darn_right = ConvoScreen:new {
	id = "darn_right",
	leftDialog = "@conversation/coa3sharedlookout:s_b6a2f31", -- You're darn right you're sorry and I am someone else. In fact, lets just say ya never saw me okay? That would be better for both of us. Got it? Now get out of here before you wind up with a nice blaster hole in your head!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(darn_right);

do_this_do_that = ConvoScreen:new {
	id = "do_this_do_that",
	leftDialog = "@conversation/coa3sharedlookout:s_74476a3d", -- Yeah I hear you there. Do this, do that, go here, blah blah blah. It all gets old, ya know?
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(do_this_do_that);

good_philosophy = ConvoScreen:new {
	id = "good_philosophy",
	leftDialog = "@conversation/coa3sharedlookout:s_4ae032b9", -- Now we're talkin'! That's a good philosophy to stick too. The pay's not bad but the kick-backs you get from making Jabba happy, that's what makes it all worth it.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(good_philosophy);

response_fine = ConvoScreen:new {
	id = "response_fine",
	leftDialog = "@conversation/coa3sharedlookout:s_7eb4d42", -- Fine.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(response_fine);

-- player already conversed one time

init_second_round = ConvoScreen:new {
	id = "init_second_round",
	leftDialog = "@conversation/coa3sharedlookout:s_6273debb", -- You're a chatty one. Then again, it gets a little lonely bein' out here so it's nice to have someone to chat with. But let's just keep it to small talk okay?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_8aa225b4", "who_said_anything"}, -- Did you hear anything about the caravan in this area?
		{"@conversation/coa3sharedlookout:s_bcb9ba12", "better_not_to_ask"}, -- What do you know about Alderaanian flora?
		{"@conversation/coa3sharedlookout:s_43af83df", "i_like_gamblin"}, -- What do you do for fun?
	}
}
coa3LookoutConvoTemplate:addScreen(init_second_round);

who_said_anything = ConvoScreen:new {
	id = "who_said_anything",
	leftDialog = "@conversation/coa3sharedlookout:s_8dccb521", -- Who said anythin' about a caravan? I'm starting to think maybe you're not on the up and up here asking things like that.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(who_said_anything);

better_not_to_ask = ConvoScreen:new {
	id = "better_not_to_ask",
	leftDialog = "@conversation/coa3sharedlookout:s_33d80544", -- Anyone workin' for the big guy would know the answer to that or would know better not to ask!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(better_not_to_ask);

i_like_gamblin = ConvoScreen:new {
	id = "i_like_gamblin",
	leftDialog = "@conversation/coa3sharedlookout:s_efba54e2", -- I like gamblin'. Mostly Sabacc, ya know? I stay away from those Lugjack machines. Ya may as well be throwin' credits into the Sarlacc Pit playin' that game. That's a game for old women and clueless nobles who can't appreciate the subtleties of a real man's game. You like Sabacc?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_4957d505", "not_game_for_me"}, -- I'm more of a Lugjack person.
		{"@conversation/coa3sharedlookout:s_f33a89f5", "lighten_up"}, -- Games are a foolish waste of time.
		{"@conversation/coa3sharedlookout:s_5b9f69a4", "less_risky"}, -- Yes, lots of money to be made at that game.
	}
}
coa3LookoutConvoTemplate:addScreen(i_like_gamblin);

not_game_for_me = ConvoScreen:new {
	id = "not_game_for_me",
	leftDialog = "@conversation/coa3sharedlookout:s_93295f8c", -- One of them huh? Well that's not game for me.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(not_game_for_me);

lighten_up = ConvoScreen:new {
	id = "lighten_up",
	leftDialog = "@conversation/coa3sharedlookout:s_24813e89", -- Well, a little fun never hurt no one. It ain't right stayin' so focused on work all the time. You need to learn to lighten up.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(lighten_up);

less_risky = ConvoScreen:new {
	id = "less_risky",
	leftDialog = "@conversation/coa3sharedlookout:s_48a4f87f", -- Don't you know it! If I had better luck, I'd play it for a livin'. It would probably less risky then this line of work.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(less_risky);

-- Player Has gone through Round 1 and 2 of Conversation

init_third_round = ConvoScreen:new {
	id = "init_third_round",
	leftDialog = "@conversation/coa3sharedlookout:s_e6e3a9f7", -- So... What do you like to do for fun?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_5d8182f2", "too_rich"}, -- I collect weapons. The bigger the better.
		{"@conversation/coa3sharedlookout:s_fcb2a3f3", "response_oh"}, -- I like dancing and reading poetry.
		{"@conversation/coa3sharedlookout:s_46c66c6d", "something_in_common"}, -- I love playing Sabacc.
		{"@conversation/coa3sharedlookout:s_b3049ce7", "watch_your_step"}, -- Enough chit chat. What do you know about the caravan?
	}
}
coa3LookoutConvoTemplate:addScreen(init_third_round);

too_rich = ConvoScreen:new {
	id = "too_rich",
	leftDialog = "@conversation/coa3sharedlookout:s_68196cce", -- Weapon collector huh? That's too rich a hobby for someone like me. Nah, a reliable blaster is really all I need.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(too_rich);

response_oh = ConvoScreen:new {
	id = "response_oh",
	leftDialog = "@conversation/coa3sharedlookout:s_1cace673", -- Oh...
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(response_oh);

something_in_common = ConvoScreen:new {
	id = "something_in_common",
	leftDialog = "@conversation/coa3sharedlookout:s_1d45a1b2", -- You too huh? Well it's great we have something in common! Too bad we don't have cards or we could have us a game. Say, what's your favorite Sabacc variant?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_a31bb6a5", "rule_changin"}, -- Random Sabacc.
		{"@conversation/coa3sharedlookout:s_ab11e3a9", "regular_kind_huh"}, -- The regular kind of Sabacc.
		{"@conversation/coa3sharedlookout:s_789d30e1", "easy_money"}, -- There's more then one way to play?
	}
}
coa3LookoutConvoTemplate:addScreen(something_in_common);

watch_your_step = ConvoScreen:new {
	id = "watch_your_step",
	leftDialog = "@conversation/coa3sharedlookout:s_c8af5b42", -- You better watch your step kiddo.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(watch_your_step);

rule_changin = ConvoScreen:new {
	id = "rule_changin",
	leftDialog = "@conversation/coa3sharedlookout:s_4fe0cc64", -- Wow, you must be good! I can't keep up with all that constant rule changin'.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(rule_changin);

regular_kind_huh = ConvoScreen:new {
	id = "regular_kind_huh",
	leftDialog = "@conversation/coa3sharedlookout:s_e0ec2153", -- The "regular kind" huh? Hehe, alright then.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(regular_kind_huh);

easy_money = ConvoScreen:new {
	id = "easy_money",
	leftDialog = "@conversation/coa3sharedlookout:s_be39516b", -- Yeah, there's lots of different rule variations used throughout the galaxy. You don't know as much about the game as I thought. Now I really wish we had some cards, you sound like easy money to me.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(easy_money);

init_passed_trial = ConvoScreen:new {
	id = "init_passed_trial",
	leftDialog = "@conversation/coa3sharedlookout:s_eff5d25", -- Say. There's something I need to ask you.
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_1c8bddbb", "in_a_jam"}, -- What is it?
	}
}
coa3LookoutConvoTemplate:addScreen(init_passed_trial);

-- Player Answered poorly, gets attacked

gotta_kill_ya = ConvoScreen:new {
	id = "gotta_kill_ya",
	leftDialog = "@conversation/coa3sharedlookout:s_8591381a", -- Why do you think you can fool me into thinkin' you're someone you ain't? Now I have no choice but to kill ya!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(gotta_kill_ya);

-- Player passed trial, has to accept mission

in_a_jam = ConvoScreen:new {
	id = "in_a_jam",
	leftDialog = "@conversation/coa3sharedlookout:s_e9a05b92", -- I'm in sort of a jam right now. You wouldn't happen to be good at fixin' things would ya? One of the speeders in our caravan has a busted 100-GU anti-gravity unit and it ain't goin' no where until it gets repaired. Jabba's got a lot of money tied up in this shipment so I'm sure he'd pay ya well for your trouble!
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_39c1d4f4", "take_repair_kit"}, -- Err... Yeah I'm great at fixing things.
		{"@conversation/coa3sharedlookout:s_2c2f4605", "cant_leave_camp"}, -- I'm feeling lazy. Why can't you do it?
		{"@conversation/coa3sharedlookout:s_2b3ee988", "help_us_out"}, -- Sorry. I'm not good at that sort of thing
	}
}
coa3LookoutConvoTemplate:addScreen(in_a_jam);

take_repair_kit = ConvoScreen:new {
	id = "take_repair_kit",
	leftDialog = "@conversation/coa3sharedlookout:s_f513f012", -- You're a real sport. This is a really important shipment and if it's lost, Jabba will have all our heads. Take this repair kit and get that part fixed. They'll give you an encoded disk that explains their status. Just deliver that disk and I'm sure you'll be paid well. Just don't lose it! Even though it is encoded, I'd hate to be you if you let it fall into the wrong hands.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(take_repair_kit);

cant_leave_camp = ConvoScreen:new {
	id = "cant_leave_camp",
	leftDialog = "@conversation/coa3sharedlookout:s_4e7b2666", -- I can't leave this camp! Jabba wants me planted here to keep an eye on our over-land shipping routes. The last thing we need is to lose a valuable shipment to the likes of Valerian or the Alkharans. But if that part isn't fixed, that's just what's going to happen! Those guys are stranded out there and its only a matter of time before someone sees them. Lots of people want to get their hands on that cargo.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(cant_leave_camp);

help_us_out = ConvoScreen:new {
	id = "help_us_out",
	leftDialog = "@conversation/coa3sharedlookout:s_41d587bc", -- Oh come on! It won't take ya any time to do and with that repair kit it will be so easy a Wookiee could do it! You need to help us out here; we'll all end up as rancor kibble if something happens to this shipment, don't make me beg!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(help_us_out);

-- Pending missiong acceptance

init_passed_prior_refuse = ConvoScreen:new {
	id = "init_passed_prior_refuse",
	leftDialog = "@conversation/coa3sharedlookout:s_82fdf085", -- So, can ya go and make those repairs then?
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_69fbc643", "important_shipment"}, -- Sure, sounds easy enough.
		{"@conversation/coa3sharedlookout:s_da6c5185", "twin_suns"}, -- I told you, I'm not mechanically inclined.
	}
}
coa3LookoutConvoTemplate:addScreen(init_passed_prior_refuse);

important_shipment = ConvoScreen:new {
	id = "important_shipment",
	leftDialog = "@conversation/coa3sharedlookout:s_7d2ae36c", -- You're a real sport. That caravan's deliverin' an important shipment but one of our speeders had a breakdown and lost one of its anti-gravity units. Take this repair kit and get that speeder up and running. They'll give you a disk explainin' their status and their new ETA. Just be careful you don't lose it! Even though it is encoded, it contains a lot of sensitive information. If you lose the disk, not getting paid would be the least of your worries.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(important_shipment);

twin_suns = ConvoScreen:new {
	id = "twin_suns",
	leftDialog = "@conversation/coa3sharedlookout:s_fdb57c0", -- The twin suns take ya, you're exasperating! Listen, I trust you and you look smart enough to figure out what is supposed to go where on a simple part. Aside from the shipment, there are lives on the line here and some of the guys in that caravan owe me a lot of money. Are ya sure ya won't reconsider, I'm beggin' ya here?
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(twin_suns);

init_already_accepted = ConvoScreen:new {
	id = "init_already_accepted",
	leftDialog = "@conversation/coa3sharedlookout:s_8cf78df2", -- Hey, shouldn't you be out making those repairs? We have to get that caravan moving pronto!
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_869a3fda", "get_on_it"}, -- Yeah, I'm on my way there right now.
		{"@conversation/coa3sharedlookout:s_b4e5d3ef", "always_getting_lost"}, -- I wasn't able to find the caravan.
	}
}
coa3LookoutConvoTemplate:addScreen(init_already_accepted);

get_on_it = ConvoScreen:new {
	id = "get_on_it",
	leftDialog = "@conversation/coa3sharedlookout:s_e9f1af41", -- Well get on it already!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(get_on_it);

always_getting_lost = ConvoScreen:new {
	id = "always_getting_lost",
	leftDialog = "@conversation/coa3sharedlookout:s_2fe8f4b5", -- Those guys are always getting lost. I'll upload their last known location to your datapad again.
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(always_getting_lost);

init_failed_trial = ConvoScreen:new {
	id = "init_failed_trial",
	leftDialog = "@conversation/coa3sharedlookout:s_eff5d25", -- Say. There's something I need to ask you.
	stopConversation = "false",
	options = {
		{"@conversation/coa3sharedlookout:s_1c8bddbb", "gotta_kill_ya"}, -- What is it?
	}
}
coa3LookoutConvoTemplate:addScreen(init_failed_trial);

init_no_mission = ConvoScreen:new {
	id = "init_no_mission",
	leftDialog = "@conversation/coa3sharedlookout:s_3029f004", -- Listen pal, I don't know who you are but you better get lost. Strangers make me nervous and when I get nervous, it makes me want to start shootin' if ya know what I mean. Now beat it!
	stopConversation = "true",
	options = {}
}
coa3LookoutConvoTemplate:addScreen(init_no_mission);

addConversationTemplate("coa3LookoutConvoTemplate", coa3LookoutConvoTemplate);
