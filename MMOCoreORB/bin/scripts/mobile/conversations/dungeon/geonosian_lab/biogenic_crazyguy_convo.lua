biogenicCrazyGuyConvoTemplate = ConvoTemplate:new {
	initialScreen = "are_you_here",
	templateType = "Lua",
	luaClassHandler = "conv_handler",
	screens = {}
}

are_you_here = ConvoScreen:new {
	id = "are_you_here",
	leftDialog = "@conversation/biogenic_crazyguy:s_eb2f9960", -- HELP! HELP! Are you here?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_5d16248c", "you_are_the_truth"}, -- Yes, I'm here. Now what is going on?
		{"@conversation/biogenic_crazyguy:s_e34d6272", "no_who_is_not_here"}, -- Is who here? Start making sense!
		{"@conversation/biogenic_crazyguy:s_564ba87", "not_going_on_going_in"}, -- I swear, if you don't tell me what's going on...
		{"@conversation/biogenic_crazyguy:s_e5f4a149", "there_is_no_leaving"} -- Please don't hurt me. I was just leaving.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(are_you_here);

go_no_leave = ConvoScreen:new {
	id = "go_no_leave",
	leftDialog = "@conversation/biogenic_crazyguy:s_d166b780", -- Go? No, I want you to leave... in there!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_e1fbb5ed", "yes_keep_going"}, -- In where? Into that opening back there?
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "thats_what_i_say"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(go_no_leave);

no_who_is_not_here = ConvoScreen:new {
	id = "no_who_is_not_here",
	leftDialog = "@conversation/biogenic_crazyguy:s_1c4a552c", -- No, who is not here. That is... the problem. I think? Are you ...who?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_7d4e91e1", "yes_you_are_now_must_go"}, -- Yes, I am. I think.
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "thats_what_i_say"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(no_who_is_not_here);

arent_who_you_are = ConvoScreen:new {
	id = "arent_who_you_are",
	leftDialog = "@conversation/biogenic_crazyguy:s_51edfa93", -- Then maybe you aren't... who you are. So long then.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(arent_who_you_are);

youre_here = ConvoScreen:new {
	id = "youre_here",
	leftDialog = "@conversation/biogenic_crazyguy:s_80c190c3", -- *gurk* Why... you're here? Did they send you? I see that you're here.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_f6dd63d", "are_you_here"}, -- Did who send me? What's going on here?
		{"@conversation/biogenic_crazyguy:s_e7953fb5", "do_you_see_it"}, -- What is the matter with you?
		{"@conversation/biogenic_crazyguy:s_daa5a74d", "never_alone"} -- Ok, you seem distracted. I'll leave you alone.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(youre_here);

remember_never_seen = ConvoScreen:new {
	id = "remember_never_seen",
	leftDialog = "@conversation/biogenic_crazyguy:s_4e52ced2", -- Hey, I remember you... but I've never seen you before.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_9499432", "how_many_monsters"}, -- Still crazy as ever I see.
		{"@conversation/biogenic_crazyguy:s_a64c5d9e", "arent_who_you_are"}, -- Of course you have, I was here just a bit ago.
		{"@conversation/biogenic_crazyguy:s_70a572af", "all_i_have_is_time"} -- I don't have time for this. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(remember_never_seen);

keep_what_in_mind = ConvoScreen:new {
	id = "keep_what_in_mind",
	leftDialog = "@conversation/biogenic_crazyguy:s_68d073fe", -- Keep what in mind? Was it something important? Oh well.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_564ba87", "not_going_on_going_in"}, -- I swear, if you don't tell me what's going on...
		{"@conversation/biogenic_crazyguy:s_3157939", "some_think_that"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(keep_what_in_mind);

do_you_see_it = ConvoScreen:new {
	id = "do_you_see_it",
	leftDialog = "@conversation/biogenic_crazyguy:s_74fbbad2", -- Look around... do you see it? That's, uh... what is?
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_9c653067", "no_one_does_anymore"}, -- See what? I don't...
		{"@conversation/biogenic_crazyguy:s_564ba87", "not_going_on_going_in"} -- I swear, if you don't tell me what's going on...
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(do_you_see_it);

you_are_the_truth = ConvoScreen:new {
	id = "you_are_the_truth",
	leftDialog = "@conversation/biogenic_crazyguy:s_14b63e24", -- Yes! I see you are... the truth. When you leave... we all can go. But I must tell you...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_1c8bddbb", "not_all_about_rhyming"}, -- What is it?
		{"@conversation/biogenic_crazyguy:s_f0a82cfa", "not_all_about_rhyming"}, -- I think you've told me enough already.
		{"@conversation/biogenic_crazyguy:s_70a572af", "all_i_have_is_time"} -- I don't have time for this. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(you_are_the_truth);

not_all_about_rhyming = ConvoScreen:new {
	id = "not_all_about_rhyming",
	leftDialog = "@conversation/biogenic_crazyguy:s_5d995d79", -- Life is not all about... rhyming. And soon it will be over.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_fd7a670e", "keep_what_in_mind"}, -- Right... I'll try to, um... keep that in mind.
		{"@conversation/biogenic_crazyguy:s_20413fbf", "we_all_get_it"} -- I'm sorry, I guess I just don't get it. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(not_all_about_rhyming);

no_one_does_anymore = ConvoScreen:new {
	id = "no_one_does_anymore",
	leftDialog = "@conversation/biogenic_crazyguy:s_3e250a", -- No... no one. No one does. No one anymore.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(no_one_does_anymore);

yes_you_are_now_must_go = ConvoScreen:new {
	id = "yes_you_are_now_must_go",
	leftDialog = "@conversation/biogenic_crazyguy:s_524005c4", -- Yes! Yes you are! I see you... now you must go!
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_64bc92a0", "what_isnt_happening"}, -- Go where? Tell me what's happening!
		{"@conversation/biogenic_crazyguy:s_cc90aebb", "go_no_leave5"} -- Good idea. I can't take any more of this.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(yes_you_are_now_must_go);

what_isnt_happening = ConvoScreen:new {
	id = "what_isnt_happening",
	leftDialog = "@conversation/biogenic_crazyguy:s_b18aca61", -- What isn't happening? You, that's what... why? Go now.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_be321a24", "how_many_monsters"}, -- Ok, ok. I'm going.
		{"@conversation/biogenic_crazyguy:s_a9f69fb7", "yes_keep_going"}, -- Go? You want me to leave?
		{"@conversation/biogenic_crazyguy:s_3157939", "some_think_that"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(what_isnt_happening);

yes_keep_going = ConvoScreen:new {
	id = "yes_keep_going",
	leftDialog = "@conversation/biogenic_crazyguy:s_7d4f8520", -- Yes, yes. Keep going. That way. No, wait. That way.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_be321a24", "for_the_monsters"}, -- Ok, ok. I'm going.
		{"@conversation/biogenic_crazyguy:s_3157939", "some_think_that"} -- You're loony as a peko bird. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(yes_keep_going);

how_many_monsters = ConvoScreen:new {
	id = "how_many_monsters",
	leftDialog = "@conversation/biogenic_crazyguy:s_3a0e3163", -- How many? 32281... monsters... 32281... monsters.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(how_many_monsters);

not_going_on_going_in = ConvoScreen:new {
	id = "not_going_on_going_in",
	leftDialog = "@conversation/biogenic_crazyguy:s_469eaf3a", -- No, not going on... going in, and when you've done that... we all go out.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_crazyguy:s_d87072f3", "go_no_leave"}, -- Go in? Go out? What are you talking about?
		{"@conversation/biogenic_crazyguy:s_c182d8fb", "thats_what_i_say"} -- Sorry, I don't talk with crazy people. Good-bye.
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(not_going_on_going_in);

for_the_monsters = ConvoScreen:new {
	id = "for_the_monsters",
	leftDialog = "@conversation/biogenic_crazyguy:s_91c86ae2", -- For the monsters... 32281 is it. You see, 32281... monsters. There are 32281 monsters.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(for_the_monsters);

never_alone = ConvoScreen:new {
	id = "never_alone",
	leftDialog = "@conversation/biogenic_crazyguy:s_23bcaf58", -- Never alone... never alone...
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(never_alone);

some_think_that = ConvoScreen:new {
	id = "some_think_that",
	leftDialog = "@conversation/biogenic_crazyguy:s_28eb431a", -- There are some that think that... namely you.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(some_think_that);

there_is_no_leaving = ConvoScreen:new {
	id = "there_is_no_leaving",
	leftDialog = "@conversation/biogenic_crazyguy:s_d3b52482", -- There is no leaving. Not now since... oh, you're here?
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(there_is_no_leaving);

all_i_have_is_time = ConvoScreen:new {
	id = "all_i_have_is_time",
	leftDialog = "@conversation/biogenic_crazyguy:s_bc3d132b", -- No, no. All I have is time, until it ends.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(all_i_have_is_time);

thats_what_i_say = ConvoScreen:new {
	id = "thats_what_i_say",
	leftDialog = "@conversation/biogenic_crazyguy:s_40626e0f", -- That's what I say too. Except I'm... staying here.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(thats_what_i_say);

we_all_get_it = ConvoScreen:new {
	id = "we_all_get_it",
	leftDialog = "@conversation/biogenic_crazyguy:s_72870486", -- Unfortunately... we all get it. Very soon.
	stopConversation = "true",
	options = {
	}
}

biogenicCrazyGuyConvoTemplate:addScreen(we_all_get_it);

addConversationTemplate("biogenicCrazyGuyConvoTemplate", biogenicCrazyGuyConvoTemplate);
