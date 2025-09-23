rikkh_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rikkhConvoHandler",
	screens = {}
}

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(no_jtl);

not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5d3166b9", -- Everything is fine here. Nothing wrong at all.
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(not_pilot);

pilot_not_corsec = ConvoScreen:new {
	id = "pilot_not_corsec",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_87bedbc6", -- "Well, if it isn't %TU. I've heard your name around the pilot's lounge a few times. What can I do for you?"
	animation = "wave2",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_b978843d", "non_corsec_missions"}, --  I'm looking for a mission. Do you have anything I can do?
	}
}
rikkh_convo_template:addScreen(pilot_not_corsec);

finished_tier = ConvoScreen:new {
	id = "finished_tier",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_447b4291", -- %TU!  Long time no see.  I've heard Commander Ramna was quite pleased with your performance.
	animation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6adec6b0", "cocky_pilot"}, -- Of course!
		{"@conversation/corellia_privateer_trainer:s_b6b1c40a", "mild_pilot"}, -- Not really
	}
}
rikkh_convo_template:addScreen(finished_tier);

cocky_pilot = ConvoScreen:new {
	id = "cocky_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_fc079db2", -- Still the cocky one, aren't you?  Anyway, what brings you back to Corellia?
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8125b624", "find_adwan"}, -- Looking for Adwan Turoldine
		{"@conversation/corellia_privateer_trainer:s_74f806bd", "just_visit"}, -- Just visiting
	}
}
rikkh_convo_template:addScreen(cocky_pilot);

mild_pilot = ConvoScreen:new {
	id = "mild_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b9fa1db9", -- She can be a tough one to work with, but she's a good officer.  Anyway, what brings you back to Corellia?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8125b624", "find_adwan"}, -- Looking for Adwan Turoldine
		{"@conversation/corellia_privateer_trainer:s_74f806bd", "just_visit"}, -- Just visiting
	}
}
rikkh_convo_template:addScreen(mild_pilot);

find_adwan = ConvoScreen:new {
	id = "find_adwan",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a635c8aa", -- Turoldine?  Why... he's stationed on Dantooine, I think.  Not Corellia!  Look for him in the Mining outpost.
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_3b2fdc7f", "will_thanks"}, -- Will do!  Thanks!
	}
}
rikkh_convo_template:addScreen(find_adwan);

just_visit = ConvoScreen:new {
	id = "just_visit",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7282cf08", -- Oh yes, I know what you mean... there's no place like Corellia.
	animation = "nod_head_multiple",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_ea178ddb", "like_corellia"}, -- Talus is like Corellia
		{"@conversation/corellia_privateer_trainer:s_264b3207", "start_joke"}, -- You said it!
	}
}
rikkh_convo_template:addScreen(just_visit);

like_corellia = ConvoScreen:new {
	id = "like_corellia",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_530a5a44", -- Are you insane?  The weather there is terrible, the food tastes awful and the locals are all rude.  Talus is practically a backwater compared to Corellia.
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8e2edcbe", "start_joke"}, -- If you say so.
	}
}
rikkh_convo_template:addScreen(like_corellia);

start_joke = ConvoScreen:new {
	id = "start_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_aba61e8d", -- Hey, stop me if you've heard this one.  Three Corellians see an Imperial at the starport.
	animation = "slow_down",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_ec084dd3", "continue_joke"}, -- Go on
		{"@conversation/corellia_privateer_trainer:s_30350c6", "heard_it"}, -- I've heard it.
	}
}
rikkh_convo_template:addScreen(start_joke);

heard_it = ConvoScreen:new {
	id = "heard_it",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4e6f47aa", -- Oh.  Ok... heh, guess I'm getting to be old, telling the same old jokes over and over.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9f5f269", "back_to_work"}, -- No problem
	}
}
rikkh_convo_template:addScreen(heard_it);

continue_joke = ConvoScreen:new {
	id = "continue_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_76c3352e", -- So, one of the Corellians walked over to the Imperial, taps him on the shoulder, and says, 'Hey, I hear your Darth Vader is a spice-fiend.'
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_ba11bd82", "continue_joke2"}, -- And?.
	}
}
rikkh_convo_template:addScreen(continue_joke);

continue_joke2 = ConvoScreen:new {
	id = "continue_joke2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_47fde4be", -- The Imperial just shrugs and says, 'Oh really, I didn't know that.'  So the Corellian goes back to his buddies and tells them, 'I insulted Darth Vader and he didn't even care'.
	animation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_b3c84ab4", "continue_joke3"}, -- Then what happened?
	}
}
rikkh_convo_template:addScreen(continue_joke2);

continue_joke3 = ConvoScreen:new {
	id = "continue_joke3",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a5293421", -- One of his buddies says, 'You just don't know how to get to him.  Watch this.' and he goes over to the Imperial and says, 'Hey, I hear your Darth Vader was a lying, cheating, idiotic, low-life scum!'  But the Imperial still just shrugs and says, 'Oh, really?  I didn't know that.'
	animation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_ec084dd3", "continue_joke4"}, -- Go on
	}
}
rikkh_convo_template:addScreen(continue_joke3);

continue_joke4 = ConvoScreen:new {
	id = "continue_joke4",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f8842e94", -- So he goes back to his Corellian buddies and says, 'You're right!  That guy is unshakable!'  And the third Corellian says, 'I'll get him.  Watch this.'  And he goes over to the Imperial, taps him on the shoulder and says, 'Hey, I heard Darth Vader was a Corellian!'
	animation = "point_to_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_b3c84ab4", "continue_joke5"}, -- Then what happened?
	}
}
rikkh_convo_template:addScreen(continue_joke4);

continue_joke5 = ConvoScreen:new {
	id = "continue_joke5",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f8842e94", -- The Imperial just shrugged and said, 'Yeah, that's what your buddies were trying to tell me.'
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_99251349", "done_goofing"}, -- (Laugh)
		{"@conversation/corellia_privateer_trainer:s_8ed520f1", "terrible_joke"}, -- That was terrible
	}
}
rikkh_convo_template:addScreen(continue_joke5);

completed_rikkh = ConvoScreen:new {
	id = "completed_rikkh",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a87fc3e8", -- I want you to travel to Lok and see Commander Ramna.  She'll probably be holed-up in Nym's cantina...
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_d24a2285", "good_luck"}, -- Will do.
		{"@conversation/corellia_privateer_trainer:s_84be4b94", "why_lok"}, -- Why Lok?
	}
}
rikkh_convo_template:addScreen(completed_rikkh);

why_lok = ConvoScreen:new {
	id = "why_lok",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_19104bb", -- I don't have all the details.  Suffice to say that sometimes CorSec needs to be a little more proactive.  We can't always wait for trouble to come to us.
	animation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_bcdf778f", "good_luck2"}, -- Ok, see ya.
		{"@conversation/corellia_privateer_trainer:s_9b99e4ac", "more_duty"}, -- Can't I just do some duty missions for you?
	}
}
rikkh_convo_template:addScreen(why_lok);

more_duty = ConvoScreen:new {
	id = "more_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1d843b61", -- You're much too good a pilot to waste on the trivial tasks that I could assign you.  We need you in Lok.  Now!
	animation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e576266", "git_gone"}, -- OK, ok!
	}
}
rikkh_convo_template:addScreen(more_duty);

initial_training = ConvoScreen:new {
	id = "initial_training",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_584a90f8", -- You've done an excellent job for me, %NU.  I can see that you are ready for some training.
	animation = "",
	stopConversation = "false",
	options = {
		-- Added via handler
	}
}
rikkh_convo_template:addScreen(initial_training);









--[[

	Quest Line Missions

]]








failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e00ac98e", -- What happened up there?
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_d21a7a71", "fail_first_terrible"}, -- I failed
	}
}
rikkh_convo_template:addScreen(failed_first_mission);

fail_first_terrible = ConvoScreen:new {
	id = "fail_first_terrible",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_baddec82", -- Oh that's terrible.  You've got to get back to Lok and destroy that ship!
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_40e66be3", "try_first_mission"}, -- I'll try
		{"@conversation/corellia_privateer_trainer:s_32e9d36a", "cant_wait_first"}, -- Can't it wait?
	}
}
rikkh_convo_template:addScreen(fail_first_terrible)












--[[

	Duty Missions

]]

here_for_work = ConvoScreen:new {
	id = "here_for_work",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5d262b71", -- You are here for work now, yes?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_e107077e", "good_duty"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer_2:s_c545bb40", "no_duty"}, -- No I am not
		{"@conversation/corellia_privateer_trainer_2:s_98dba2b6", "better_ship"}, -- I need a better ship
	}
}
rikkh_convo_template:addScreen(here_for_work)

good_duty = ConvoScreen:new {
	id = "good_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_178d46a1", -- Good.  Choose an assignment.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty1"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_56e162f2", "escort_duty"}, -- Escort Duty
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty2"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_28ea80d", "recovery_duty"}, -- Recovery Duty
	}
}
rikkh_convo_template:addScreen(good_duty)

no_duty = ConvoScreen:new {
	id = "no_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9e85f6f2", -- Why not?  We've got bad guys to catch, stolen cargo to recover, Imperial oppression to resist... you think Corellia is just going to magically secure itself?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f613ccdb", "lots_to_do"}, -- Ok, what can I do?
		{"@conversation/corellia_privateer_trainer_2:s_82d13497", "too_busy"}, -- I'm busy
	}
}
rikkh_convo_template:addScreen(no_duty)

lots_to_do = ConvoScreen:new {
	id = "lots_to_do",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5715d65c", -- Lots.  What do you WANT to do?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty1"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_56e162f2", "escort_duty"}, -- Escort Duty
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty2"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_28ea80d", "recovery_duty"}, -- Recovery Duty
	}
}
rikkh_convo_template:addScreen(lots_to_do)

better_ship = ConvoScreen:new {
	id = "better_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_6d4db3b5", -- What's wrong with the one you've got?
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_bc99a4d2", "weak_ship"}, -- It's weak!
		{"@conversation/corellia_privateer_trainer_2:s_3880d2bf", "buy_ship"}, -- I need a hyperdrive
	}
}
rikkh_convo_template:addScreen(better_ship)

weak_ship = ConvoScreen:new {
	id = "weak_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_aad866ad", -- You'll just have to learn to deal with it... or buy a better ship.  Now are you ready for work or not?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_e107077e", "good_duty"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer_2:s_c545bb40", "no_duty"}, -- No I am not
		{"@conversation/corellia_privateer_trainer_2:s_98dba2b6", "better_ship"}, -- I need a better ship
	}
}
rikkh_convo_template:addScreen(weak_ship)

destroy_duty1 = ConvoScreen:new {
	id = "destroy_duty1",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_346ddf", -- You know Corellia's officially neutral in the civil war, right?  Well the Imperials seem to have a hard time remembering that.  Go out there and 'remind' them they aren't welcome as a military power in the Corellia system.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_d24a2285", "accept_destroy1"}, -- Will do.
	}
}
rikkh_convo_template:addScreen(destroy_duty1)

accept_destroy1 = ConvoScreen:new {
	id = "accept_destroy1",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f43089c2", -- Excellent!  Good luck, %NU.  And remember, Experience is something you don't get until after you need it.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_destroy1)

escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_13b10809", -- Travel to Lok Space and protect a transport that has gotten between some Imperial and Rebels.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_3b83352c", "accept_escort"}, -- On my way
	}
}
rikkh_convo_template:addScreen(escort_duty)

accept_escort = ConvoScreen:new {
	id = "accept_escort",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7f5b2aa", -- Fantastic!  And remember, if you lose contact with the enemy, look behind you.
	animation = "laugh_titter",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_escort)

destroy_duty2 = ConvoScreen:new {
	id = "destroy_duty2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e5e96bc7", -- Head up to Corellia Space and destroy some Hidden Daggers.  Those pirates have been getting a little too bold lately.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_52467dab", "accept_destroy2"}, -- I'll destroy them
	}
}
rikkh_convo_template:addScreen(destroy_duty2)

accept_destroy2 = ConvoScreen:new {
	id = "accept_destroy2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f1e77b0c", -- Good!  But just remember, no plan ever survives contact with the enemy.
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_destroy2)

recovery_duty = ConvoScreen:new {
	id = "recovery_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8cd19baf", -- Nym's ships have been expanding their operations all the way out to Yavin 4.  We want to put a stop to that, but more importantly we want to recover the cargo he's been swiping from Corellian freighters!  Go recover that cargo in the Yavin system!
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_9f5f269", "accept_recovery"}, -- No problem
	}
}
rikkh_convo_template:addScreen(recovery_duty)

accept_recovery = ConvoScreen:new {
	id = "accept_recovery",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7f5b2aa", -- Fantastic.  Don't forget:  If the enemy is within range, so are you.
	animation = "applause_polite",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_recovery)














--[[

	Conversation Enders

]]

will_thanks = ConvoScreen:new {
	id = "will_thanks",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c261cfae", -- No problem.
	animation = "wave2",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(will_thanks);

back_to_work = ConvoScreen:new {
	id = "back_to_work",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a34ecd3", -- Alright.  Well, I better get back to work.  Don't be a stranger!
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(back_to_work);

done_goofing = ConvoScreen:new {
	id = "done_goofing",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_53b9240e", -- Ha ha!  Ok, enough goofing off.  I better get back to work.  Enjoy your visit to Corellia.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(done_goofing);

terrible_joke = ConvoScreen:new {
	id = "terrible_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_12da4881", -- Yeah, well, they can't all be gems.  Anyway I'd better get back to work.  Take care, %NU.
	animation = "shrug_hands",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(terrible_joke);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_658107f", -- I can see you're busy.  Come talk to me when you've got some time.  I can always use your services
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(on_mission);

try_first_mission = ConvoScreen:new {
	id = "try_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f7394720", -- That's the spirit!  Good luck!  And don't worry, some day we'll look back on this, laugh nervously and change the subject.
	animation = "laugh_titter",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(try_first_mission);

cant_wait_first = ConvoScreen:new {
	id = "cant_wait_first",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7b2e95f6", -- I will always cherish the initial misconceptions I had about you.  No it can't 'wait'!  You think they're just going to cruise around waiting for you to go blow 'em up.  Get out there!
	animation = "pound_fist_palm",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(cant_wait_first);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a80d9308", -- Good luck!
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(good_luck);

good_luck2 = ConvoScreen:new {
	id = "good_luck2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a80d9308", -- Good luck!
	animation = "wave2",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(good_luck2);

git_gone = ConvoScreen:new {
	id = "git_gone",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1f3b7ea2", -- Git!
	animation = "point_away",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(git_gone);

buy_ship = ConvoScreen:new {
	id = "buy_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8694eb3f", -- You're right about that!  Unfortunately I don't have any better ships to spare.  You'll just have to buy a better ship yourself.
	animation = "nod_head_multiple",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(buy_ship)

too_busy = ConvoScreen:new {
	id = "too_busy",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4e3437a8", -- Oh, YOU'RE busy.  You think I don't work here?  Come talk to me when you're ready for an assignment.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(too_busy)













addConversationTemplate("rikkh_convo_template", rikkh_convo_template);
