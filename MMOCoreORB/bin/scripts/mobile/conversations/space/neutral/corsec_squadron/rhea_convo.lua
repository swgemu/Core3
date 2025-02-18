rhea_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rheaConvoHandler",
	screens = {}
}

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_jtl);

rebel_pilot = ConvoScreen:new {
	id = "rebel_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	animation = "wave_on_dismissing",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(rebel_pilot);

imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	animation = "standing_placate",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(imperial_pilot);

-- Player is a Neutral Pilot but a different squadron

non_corsec_pilot = ConvoScreen:new {
	id = "non_corsec_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	animation = "point_accusingly",
	options = {
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "not_corsec_duty_missions"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(non_corsec_pilot);

-- Player has no pilot skills

recruitment = ConvoScreen:new {
	id = "recruitment",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	animation = "greet",
	options = {
		{"@conversation/corellia_privateer_trainer:s_370822d1", "yes_join"}, -- Yes
		{"@conversation/corellia_privateer_trainer:s_457a7010", "no_join"}, -- No
		{"@conversation/corellia_privateer_trainer:s_4906b993", "what_is_corsec"}, -- What is CorSec?
	}
}
rhea_convo_template:addScreen(recruitment);

yes_join = ConvoScreen:new {
	id = "yes_join",
	leftDialog = "@conversation/corellia_privateer_trainer:s_63a61222", -- We don't let just anyone join.  There'll be a background check of course.
	stopConversation = "false",
	animation = "slow_down",
	options = {
		-- Replies added via handler
	}
}
rhea_convo_template:addScreen(yes_join);

-- Negative Corsec faction, deny player

of_course_no_good = ConvoScreen:new {
	id = "of_course_no_good",
	leftDialog = "@conversation/corellia_privateer_trainer:s_be5a7539", -- This will only take a moment... Ah... Well according to this you've run into a problem with the law.  Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_e107077e", "yes_denied"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_360d8728", "no_denied"}, -- No thanks
	}
}
rhea_convo_template:addScreen(of_course_no_good);

ridiculous_no_good = ConvoScreen:new {
	id = "ridiculous_no_good",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d72a0d47", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Ah... Well according to this you've run into a problem with the law.  Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_2f9db7a", "maybe_no_good"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_f42d051f", "maybe_not_no_good"}, -- Maybe not.
	}
}
rhea_convo_template:addScreen(ridiculous_no_good);

-- Corsec faction standing is over 200

of_course_great = ConvoScreen:new {
	id = "of_course_great",
	leftDialog = "@conversation/corellia_privateer_trainer:s_7df39542", -- This will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_e107077e", "yes_i_am"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_360d8728", "no_thanks"}, -- No thanks
	}
}
rhea_convo_template:addScreen(of_course_great);

ridiculous_great = ConvoScreen:new {
	id = "ridiculous_great",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cec02f8", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_2f9db7a", "maybe_great"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_f42d051f", "goodbye"}, -- Maybe not.
	}
}
rhea_convo_template:addScreen(ridiculous_great);

maybe_great = ConvoScreen:new {
	id = "maybe__42",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e0dfe067", -- Very well.  I'll go ahead and sign you up.  Do you have your own ship?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_5091cb8e", "no_ship"}, -- Ah... no I don't.
		{"@conversation/corellia_privateer_trainer:s_90ec63e0", "yes_ship"}, -- Yes, I do.
	}
}
rhea_convo_template:addScreen(maybe__42);

of_course = ConvoScreen:new {
	id = "of_course",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ee2895df", -- This will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it will improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_e107077e", "yes_i_am"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_360d8728", "no_thanks"}, -- No thanks
	}
}
rhea_convo_template:addScreen(of_course);

ridiculous = ConvoScreen:new {
	id = "ridiculous",
	leftDialog = "@conversation/corellia_privateer_trainer:s_7396ebcf", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it'd improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_2f9db7a", "maybe_great"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_f42d051f", "goodbye"}, -- Maybe not.
	}
}
rhea_convo_template:addScreen(ridiculous);

-- What Do you mean? - responses

what_no_good = ConvoScreen:new {
	id = "what_no_good",
	leftDialog = "@conversation/corellia_privateer_trainer:s_b06e1df9", -- Don't worry, this will only take a moment.  We do need to ensure you're not some sort of criminal... Ah... Well according to this you haven't exactly been the most law abiding citizen on Corellia... Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_af22b9b2", "join_denied"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_984b22b", "i_dont_think_clean"}, -- I don't think so
	}
}
rhea_convo_template:addScreen(what_no_good);

what_great = ConvoScreen:new {
	id = "what_great",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ea3dcf32", -- Don't worry, this will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_af22b9b2", "i_guess_so"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_984b22b", "i_dont_think_so"}, -- I don't think so
	}
}
rhea_convo_template:addScreen(what_great);

what_do_you_mean = ConvoScreen:new {
	id = "what_do_you_mean",
	leftDialog = "@conversation/corellia_privateer_trainer:s_898027d6", -- Don't worry, this will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it will improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_af22b9b2", "i_guess_so"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_984b22b", "i_dont_think_so"}, -- I don't think so
	}
}
rhea_convo_template:addScreen(what_do_you_mean);

no_thanks = ConvoScreen:new {
	id = "no_thanks",
	leftDialog = "@conversation/corellia_privateer_trainer:s_36adcd36", -- What?  Are you sure?  You'd make an excellent candidate.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8acaf405", "positive_reject"}, -- Positive.  I don't want to join CorSec
		{"@conversation/corellia_privateer_trainer:s_e258dc9b", "yes_i_am"}, -- You're right.  Sign me up!
	}
}
rhea_convo_template:addScreen(no_thanks);

-- Joining

i_guess_so = ConvoScreen:new {
	id = "i_guess_so",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f3fdecfc", -- Then I will add you to the roster.  Do you have your own ship?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_5091cb8e", "no_ship"}, -- Ah... no I don't.
		{"@conversation/corellia_privateer_trainer:s_90ec63e0", "yes_ship"}, -- Yes, I do.
	}
}
rhea_convo_template:addScreen(i_guess_so);

yes_i_am = ConvoScreen:new {
	id = "yes_i_am",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40617d3", -- Indeed.  Do you have your own ship?
	stopConversation = "false",
	options = {
		--Responses added in convo handler
	}
}
rhea_convo_template:addScreen(yes_i_am);

what_is_corsec = ConvoScreen:new {
	id = "what_is_corsec",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40061f60", -- CorSec is Corellia's local Security force.  As you know, Corellia is officially neutral in the Galactic Civil War... or at least as neutral as a world can be in this day and age.  We provide defense and law enforcement for the entire Corellian system.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_deaabd84", "oh_no"}, -- Oh.  No thanks
		{"@conversation/corellia_privateer_trainer:s_614b71f0", "i_see"}, -- I see...
	}
}
rhea_convo_template:addScreen(what_is_corsec);

i_see = ConvoScreen:new {
	id = "i_see",
	leftDialog = "@conversation/corellia_privateer_trainer:s_63a61222", -- We don't let just anyone join.  There'll be a background check of course.
	stopConversation = "false",
	animation = "slow_down",
	options = {} -- Replies added via handler
}
rhea_convo_template:addScreen(i_see);

-- Grant Ship

no_ship = ConvoScreen:new {
	id = "no_ship",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4e95069b", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_privateer_trainer:s_b9b27823", "thank_you"}, -- Thank you.
	}
}
rhea_convo_template:addScreen(no_ship);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/corellia_privateer_trainer:s_80a724aa", -- Well now, I think that does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_4a1d2431", "yes_im_ready"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_68660d24", "i_need_to"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(thank_you);

yes_ship = ConvoScreen:new {
	id = "yes_ship",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ddfbd948", -- Well then. I think that about does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_4a1d2431", "yes_im_ready"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_68660d24", "i_need_to"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(yes_ship);

more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.  Now tell me, what area of knowledge are you most interested in?
	stopConversation = "false",
	animation = "salute1",
	options = {
		--{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "train_player_fighters_free"}, -- I'm interested in basic fighters.
		--{"@conversation/corellia_privateer_trainer:s_d1431f95", "train_player_component_free"}, -- I'm interested in basic starship component use.
		--{"@conversation/corellia_privateer_trainer:s_8523e1fc", "train_player_droid_free"}, -- I'm interested in basic training.
		--{"@conversation/corellia_privateer_trainer:s_b7fc5e5d", "train_player_basics_free"}, -- I'm interested in droid interface basics.
	}
}
rhea_convo_template:addScreen(more_training);

--[[

	Quest Line Missions

]]

yes_im_ready = ConvoScreen:new {
	id = "yes_im_ready",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cc53ba8f", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	animation = "dismiss",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "slow_down"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(yes_im_ready);

first_assignment = ConvoScreen:new {
	id = "first_assignment",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	animation = "point_away",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_exp"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_to_go"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "when_done"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(first_assignment);

an_assignment_exp = ConvoScreen:new {
	id = "an_assignment_exp",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	animation = "point_away",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_exp"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_to_go"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "when_done"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment_exp);

what_ship = ConvoScreen:new {
	id = "what_ship",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_exp"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_to_go"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "when_done"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship);

where_to_go = ConvoScreen:new {
	id = "where_to_go",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	animation = "point_away",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_exp"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_to_go"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "when_done"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_to_go);

when_done = ConvoScreen:new {
	id = "when_done",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_exp"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_to_go"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "when_done"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(when_done);

excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	animation = "applause_polite",
	options = {
		{"@conversation/corellia_privateer_trainer:s_1c76874e", "i_was_attacked"}, -- I was attacked!
		{"@conversation/corellia_privateer_trainer:s_3557fc9f", "nothing_to_it"}, -- Nothing to it.
	}
}
rhea_convo_template:addScreen(excellent_work);

i_was_attacked = ConvoScreen:new {
	id = "i_was_attacked",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "train_me2"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked);

nothing_to_it = ConvoScreen:new {
	id = "nothing_to_it",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "train_me2"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it);

excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	animation = "salute1",
	options = {
		{"@conversation/corellia_privateer_trainer:s_a927c891", "whats_next"}, -- What's next?
		{"@conversation/corellia_privateer_trainer:s_257f178d", "was_a_snap"}, -- It was a snap.
	}
}
rhea_convo_template:addScreen(excellent_work2);

whats_next = ConvoScreen:new {
	id = "whats_next",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "train_me3"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next);

was_a_snap = ConvoScreen:new {
	id = "was_a_snap",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.-
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "train_me3"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(was_a_snap);

excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	animation = "bow",
	options = {
		{"@conversation/corellia_privateer_trainer:s_a927c891", "enough_of_this"}, -- What's next?
		{"@conversation/corellia_privateer_trainer:s_ebb99364", "enough_of_this"}, -- There are too many pirates in this system!
	}
}
rhea_convo_template:addScreen(excellent_work3);

enough_of_this = ConvoScreen:new {
	id = "enough_of_this",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "train_me4"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(enough_of_this);

missions_complete = ConvoScreen:new {
	id = "missions_complete",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- "Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already."
	stopConversation = "false",
	animation = "point_forward",
	options = {
		{"@conversation/corellia_privateer_trainer:s_a78a4ac3", "what_now"}, -- What do I do now?
		{"@conversation/corellia_privateer_trainer:s_af264a19", "what_now"}, -- I love being a starfighter pilot.
	}
}
rhea_convo_template:addScreen(missions_complete);

what_now = ConvoScreen:new {
	id = "what_now",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So tell me, what area interests you the most?
	animation = "nod_head_multiple",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "train_player_fighters_free"}, -- I'm interested in basic fighters.
		{"@conversation/corellia_privateer_trainer:s_d1431f95", "train_player_component_free"}, -- I'm interested in basic starship component use.
		{"@conversation/corellia_privateer_trainer:s_8523e1fc", "train_player_basics_free"}, -- I'm interested in basic training.
		{"@conversation/corellia_privateer_trainer:s_b7fc5e5d", "train_player_droid_free"}, -- I'm interested in droid interface basics.
	}
}
rhea_convo_template:addScreen(what_now);

--[[

	Duty Missions

]]

duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", --What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	animation = "salute1",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_duty"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "what_missions"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "about_training"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(duty_missions);

what_is_duty = ConvoScreen:new {
	id = "what_is_duty",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d43b2932", -- Duty missions are a good way for you to get experience as a pilot. Only experienced pilots can receive the proper training to learn new skills and abilities.There's no real final objective so you can end the mission whenever you want. So, would you like to take a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_duty"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "what_missions"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "about_training"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_is_duty);

about_training = ConvoScreen:new {
	id = "about_training",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e5c453e0", -- You're not ready for more training yet. But duty missions are a good way of getting good experience so that you'll be ready for training soon. What do you say? Are you ready to try a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_duty"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "what_missions"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "about_training"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(about_training);

what_missions = ConvoScreen:new {
	id = "what_missions",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d6a6a9fc", -- Well, merchant freighters are always in need of escorts, or if you like you can help in the fight against the pirate leaders. What interests you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e417b37", "destroy_duty"}, -- The Pirate Leaders
		{"@conversation/corellia_privateer_trainer:s_221daf73", "escort_duty"}, -- Escorting Merchants
		{"@conversation/corellia_privateer_trainer:s_c35e70d2", "not_right_now"}, -- Nothing right now.
	}
}
rhea_convo_template:addScreen(what_missions);

destroy_duty = ConvoScreen:new {
	id = "destroy_duty",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cebaf0db", -- You're right.  No sooner do we eliminate one leader than another shows up.  Take out the Corellian Space Pirates!
	animation = "pound_fist_palm",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(destroy_duty);

escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/corellia_privateer_trainer:s_3f62bf0", -- Right, those merchants rely on us to provide them with safe passage through the Corellia system.  Just keep escorting them through.
	animation = "nod_head_multiple",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(escort_duty);






not_corsec_duty_missions = ConvoScreen:new {
	id = "not_corsec_duty_missions",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dadaabf", -- As a matter of fact, I do have some duty missions that you could perform. Who knows, maybe if you do well, you might be invited to join the CorSec. Are you ready for a duty mission?
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_corsec_duty_missions);




--[[

	Conversation Enders

]]

no_missions = ConvoScreen:new {
	id = "no_missions",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5b8a384b", -- I'm sorry, unless you are a member of the CorSec, there's very little that I can do for you. You may want to try speaking to your own contacts if you're looking for a mission.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_missions);

no_join = ConvoScreen:new {
	id = "no_join",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c8c21783", -- In that case, move along.  We're very busy here.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_join);

yes_denied = ConvoScreen:new {
	id = "yes_denied",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2c6a1c50", -- I'm sorry, but I'm afraid it's completely out of the question with your history.  You're going to have to clean up your act before you can join CorSec.
	stopConversation = "true",
	animation = "shake_head_no",
	options = {}
}
rhea_convo_template:addScreen(yes_denied);

no_denied = ConvoScreen:new {
	id = "no_denied",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2b418533", -- Perhaps you'll turn your life around, decide to be a part of the solution instead of a part of the problem.  When you're ready to help enforce the law instead of breaking it, come see me.
	stopConversation = "true",
	animation = "shake_head_no",
	options = {}
}
rhea_convo_template:addScreen(no_denied);

oh_no = ConvoScreen:new {
	id = "oh_no",
	leftDialog = "@conversation/corellia_privateer_trainer:s_580337ba", -- Very well, then please move along.  I am very busy.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(oh_no);

-- Same response with different animations in the handler
maybe_no_good = ConvoScreen:new {
	id = "maybe_no_good",
	leftDialog = "@conversation/corellia_privateer_trainer:s_342d1bdf", -- It's completely out of the question with your history.  If you want to work for CorSec then you're going to have to clean up your act.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_no_good);

maybe_not_no_good = ConvoScreen:new {
	id = "maybe_not_no_good",
	leftDialog = "@conversation/corellia_privateer_trainer:s_342d1bdf", -- It's completely out of the question with your history.  If you want to work for CorSec then you're going to have to clean up your act.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_not_no_good);

join_denied = ConvoScreen:new {
	id = "join_denied",
	leftDialog = "@conversation/corellia_privateer_trainer:s_1a1a36a3", -- Completely out of the question with your history.  You're going to have to clean up your act before you can join CorSec.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(join_denied);

i_dont_think_clean = ConvoScreen:new {
	id = "i_dont_think_clean",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b451c3f", -- All right.  But you'd better clean up your act if you ever change your mind.  We can't have CorSec members with your kind of history.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_dont_think_clean);

i_dont_think_so = ConvoScreen:new {
	id = "i_dont_think_so",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8358aeb7", -- Very well.  Let me know if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_dont_think_so);

positive_reject = ConvoScreen:new {
	id = "positive_reject",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f176d13", -- Oh?  Well.  Ok.  Come see me if you change your mind.  We could really use you.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(positive_reject);

goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corellia_privateer_trainer:s_746a1bed", -- Ok.  Bye.  Come see me if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(goodbye);

has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(has_mission);

slow_down = ConvoScreen:new {
	id = "slow_down",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e5b619a", -- Oh no, not quite so fast, %NU.  You complete a few more assignments and then we'll see about getting you some training!
	stopConversation = "true",
	animation = "slow_down",
	options = {}
}
rhea_convo_template:addScreen(slow_down);

train_me2 = ConvoScreen:new {
	id = "train_me2",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c91ba06e", -- Not just yet, %NU.  I have just a few more things for you to do before you get any training from me.
	stopConversation = "true",
	animation = "shake_head_no",
	options = {}
}
rhea_convo_template:addScreen(train_me2);

train_me3 = ConvoScreen:new {
	id = "train_me3",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e926d5f0", -- Almost, %NU.  I have just a couple more things for you to take care of before you can be trained further.  Starting with that patrol...
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_me3);

train_me4 = ConvoScreen:new {
	id = "train_me4",
	leftDialog = "@conversation/corellia_privateer_trainer:s_28435d2", -- Tell you what, %NU.  Kill that pirate leader and YES, I will train you.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_me4);

completed_rhea = ConvoScreen:new {
	id = "completed_rhea",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	animation = "beckon",
	options = {}
}
rhea_convo_template:addScreen(completed_rhea);

train_player_droid = ConvoScreen:new {
	id = "train_player_droid",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_droid);

train_player_basics = ConvoScreen:new {
	id = "train_player_basics",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_basics);

train_player_fighters = ConvoScreen:new {
	id = "train_player_fighters",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_fighters);

train_player_component = ConvoScreen:new {
	id = "train_player_component",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_component);

train_player_droid_free = ConvoScreen:new {
	id = "train_player_droid_free",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_droid_free);

train_player_basics_free = ConvoScreen:new {
	id = "train_player_basics_free",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_basics_free);

train_player_fighters_free = ConvoScreen:new {
	id = "train_player_fighters_free",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_fighters_free);

train_player_component_free = ConvoScreen:new {
	id = "train_player_component_free",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(train_player_component_free);

not_right_now = ConvoScreen:new {
	id = "not_right_now",
	leftDialog = "@conversation/corellia_privateer_trainer:s_27d40413", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_right_now);

addConversationTemplate("rhea_convo_template", rhea_convo_template);
