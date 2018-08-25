seanTrenwellConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanTrenwellConvoHandler",
	screens = {}
}

init_not_in_office_current_election = ConvoScreen:new {
	id = "init_not_in_office_current_election",
	leftDialog = "@conversation/sean_trenwell:s_52a14d49", -- All this talk about the Tuskens, I can't-Oh! I didn't notice that you had entered my office. Welcome! It definitely is a horrible day outside, unbearably hot indeed. How may I help you?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d", "humbled_by_request"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_1ee4d2a", "might_launch_attack"}, -- You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d", "let_governor_know"}, -- I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a", "come_back_soon"}, -- I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(init_not_in_office_current_election);

init_not_in_office_no_election = ConvoScreen:new {
	id = "init_not_in_office_no_election",
	leftDialog = "@conversation/sean_trenwell:s_6718926b", -- Well, I lost the election, but there's always next time. I still have many good ideas for Bestine. You should come back when the next election starts. In fact, the townsfolk usually talk about things like this when they happen. Be sure to talk to them.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(init_not_in_office_no_election);

init_voted_for_victor = ConvoScreen:new {
	id = "init_voted_for_victor",
	leftDialog = "@conversation/sean_trenwell:s_4c2afce6", -- So, you voted for my rival, did you? I see. I guess that's the point of having an open election. I'm disappointed, but that's really all I can say.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(init_voted_for_victor);

init_voted_for_sean = ConvoScreen:new {
	id = "init_voted_for_sean",
	leftDialog = "@conversation/sean_trenwell:s_64c62370", -- I hear you spoke to the governor and voted for me. I appreciate that! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(init_voted_for_sean);

init_sean_in_office = ConvoScreen:new {
	id = "init_sean_in_office",
	leftDialog = "@conversation/sean_trenwell:s_7f70fe38", -- Now that I'm in office, I can finally set some of my ideas into action. The marketplace could definitely use some attention, and I should make sure everything at the museum is going well.
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_338ea1e3", ""}, -- You said to return for a reward. For destroying that disk.
	--{"@conversation/sean_trenwell:s_a3734170", "disk_dealt_with"} -- I spoke to your contact about the disk from the crash site.
	--{"@conversation/sean_trenwell:s_49368633", "take_it_to_contact"} -- What was I supposed to do with this disk from the crash site?
	--{"@conversation/sean_trenwell:s_238ef4f6", "did_you_find_anything"} -- I've searched the crash site.
	--{"@conversation/sean_trenwell:s_a068d8f2", "seek_historian"} -- Who do I let screen anything I find at the crash site?
	--{"@conversation/sean_trenwell:s_35bc21ba", "find_anything_of_value"} -- What did you want me to do at the crash site?
	--{"@conversation/sean_trenwell:s_6a0bba8c", "indeed_i_do"} -- Do you have any special plans for while you're in office?
	--{"@conversation/sean_trenwell:s_811e4ed1", "greatly_appreciate_it"} -- I voted for you in this election.
	--{"@conversation/sean_trenwell:s_3ab76f84", "efforts_going_well"} -- I hear you're up for re-election. How's the campaign going?
	--{"@conversation/sean_trenwell:s_7eabd120", ""} -- Now that you're in office, I've come to ask about the reward you promised.
	--{"@conversation/sean_trenwell:s_81f9db80", "taking_an_interest"} -- Just thought I'd see what the local government was up to.
	}
}
seanTrenwellConvoTemplate:addScreen(init_sean_in_office);

taking_an_interest = ConvoScreen:new {
	id = "taking_an_interest",
	leftDialog = "@conversation/sean_trenwell:s_c1c018c3", -- Good for you. I always like to see people taking an interest in politics.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(taking_an_interest);

main_reward_already_given = ConvoScreen:new {
	id = "main_reward_already_given",
	leftDialog = "@conversation/sean_trenwell:s_c27445f0", -- Reward? I think not. You already received one.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(main_reward_already_given);

give_main_reward = ConvoScreen:new {
	id = "give_main_reward",
	leftDialog = "@conversation/sean_trenwell:s_f81b7edd", -- Oh yeah! Again I thank you for the help and for your support, I've prepared a little gift for you.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(give_main_reward);

main_reward_inv_full = ConvoScreen:new {
	id = "main_reward_inv_full",
	leftDialog = "@conversation/sean_trenwell:s_88b2f5bd", -- I have a nice reward for you, but you don't seem to have room to take it. Please return after making some room in your inventory.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(main_reward_inv_full);

efforts_going_well = ConvoScreen:new {
	id = "efforts_going_well",
	leftDialog = "@conversation/sean_trenwell:s_c6d1b21", -- That's correct and so far our efforts seem to be going well.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d", "humbled_by_request"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_1ee4d2a", "might_launch_attack"}, -- You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d", "let_governor_know"}, -- I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a", "come_back_soon"}, -- I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(efforts_going_well);

humbled_by_request = ConvoScreen:new {
	id = "humbled_by_request",
	leftDialog = "@conversation/sean_trenwell:s_3a06f79e", -- I am humbled by your request. Currently, Bestine's markets are inadequate. I have already completed the construction of one market place. If I win this election, I'll put my efforts into attracting new merchants to these areas to help Bestine's economy.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_540ac7e9", "hire_historians"}, -- Continue.
	}
}
seanTrenwellConvoTemplate:addScreen(humbled_by_request);

hire_historians = ConvoScreen:new {
	id = "hire_historians",
	leftDialog = "@conversation/sean_trenwell:s_8bdcb5a3", -- Additionally, I plan to hire historians to uncover the history of Bestine. Artisans will definitely appreciate the new renovations done to the museum. It will give them a chance to place their creations on display.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_1ee4d2a", "might_launch_attack"}, -- You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d", "let_governor_know"}, -- I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a", "come_back_soon"}, -- I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(hire_historians);

might_launch_attack = ConvoScreen:new {
	id = "might_launch_attack",
	leftDialog = "@conversation/sean_trenwell:s_df1ac18d", -- The Tuskens... My rival is centered on the slight possibility that they might launch an attack against Bestine. I find that highly doubtful. We have enough Troopers walking around as it is and they can easily defend us if needed. The Tuskens aren't brave or stupid enough to come near Bestine. We need to concentrate on the economy by introducing more markets!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d", "humbled_by_request"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_d6a9a15d", "let_governor_know"}, -- I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a", "come_back_soon"}, -- I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(might_launch_attack);

let_governor_know = ConvoScreen:new {
	id = "let_governor_know",
	leftDialog = "@conversation/sean_trenwell:s_a7627a7", -- Excellent news! How does the process go... Oh! You should let the governor, Tour Aryon, know of any evidence of a good deed I have done for the people of Bestine. Take it to her! I have done much for the people of Bestine, so I have confidence that our governor will be impressed. Of course, if you decide I am not the right candidate to represent you, you can always join my rival's campaign instead. Though I can't imagine how that would be possible.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_540ac7e9", "negative_tidbit"}, -- Continue.
	}
}
seanTrenwellConvoTemplate:addScreen(let_governor_know);

negative_tidbit = ConvoScreen:new {
	id = "negative_tidbit",
	leftDialog = "@conversation/sean_trenwell:s_30eb7833", -- After which, if you discover his twisted ideas aren't for you... and I won't be surprised when you do... you'll need to bring back some sort of negative tidbit about him in order for you to be let back into my campaign. Do you get it? I'll just give you a disk to further explain the details.
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_ef067f71", ""}, -- Alright. I want to join your campaign.
	--{"@conversation/sean_trenwell:s_5c46daeb", "always_use_vote"}, -- I've changed my mind.
	--{"@conversation/sean_trenwell:s_dea56128", "come_back_soon"}, -- I have to go.
	}
}
seanTrenwellConvoTemplate:addScreen(negative_tidbit);

always_use_vote = ConvoScreen:new {
	id = "always_use_vote",
	leftDialog = "@conversation/sean_trenwell:s_483c9216", -- I'm sorry to hear that. However, if you do decide that you'd rather join my campaign, please come by again. We could always use your vote.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(always_use_vote);

come_back_soon = ConvoScreen:new {
	id = "come_back_soon",
	leftDialog = "@conversation/sean_trenwell:s_91cc7d0", -- I wish you well. Come back soon!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(come_back_soon);

greatly_appreciate_it = ConvoScreen:new {
	id = "greatly_appreciate_it",
	leftDialog = "@conversation/sean_trenwell:s_f1b007b2", -- I heard and greatly appreciate it! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(greatly_appreciate_it);

indeed_i_do = ConvoScreen:new {
	id = "indeed_i_do",
	leftDialog = "@conversation/sean_trenwell:s_dab387e8", -- Indeed I do! History is a passion of mine, especially since my ancestors were among the original settlers of Bestine. I've gotten enough funding to hire a historian. We made an exciting new discovery just last week! A terrible desert storm came through and kicked up loose sand and beneath was a wrecked ship. We think it may be the Red-Sin Valon, the vessel used to transport the early settlers to Tatooine. It's so exciting!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_4ff8cd88", "brutal_attacks"}, -- I suppose.
	}
}
seanTrenwellConvoTemplate:addScreen(indeed_i_do);

brutal_attacks = ConvoScreen:new {
	id = "brutal_attacks",
	leftDialog = "@conversation/sean_trenwell:s_d485fca4", -- Yes. Anyway, lately we've experienced brutal attacks from the Sand People. My historian is having a hard time of it, and I'm not sure her efforts can continue. She doesn't possess a brawler's spirit or the skill of a marksman. She's just a scholar. It's depressing to think that our attempts to restore the Red-Sin Valon have been fruitless. Do you think you can help? You seem like an adventurer. Or am I wrong?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_1e35bbba", "just_my_luck"}, -- I am an adventurer!
		{"@conversation/sean_trenwell:s_3ba540c", "thats_unfortunate"} -- You're wrong.
	}
}
seanTrenwellConvoTemplate:addScreen(brutal_attacks);

just_my_luck = ConvoScreen:new {
	id = "just_my_luck",
	leftDialog = "@conversation/sean_trenwell:s_a5cd533e", -- Just my luck! I could really use your help. The Red-Sin Valon find is phenomenal in of itself, but what if there's more? I want you to bring back any information you can. There must be some sort of log of the events surrounding the early settlement attempts. I'd really like for you to find it. Do you think you can do that?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b45b3794", "punch_in_location"}, -- Sounds like fun. I'll do it!
		{"@conversation/sean_trenwell:s_2ac8d04c", "maybe_later_then"} -- No, I can't.
	}
}
seanTrenwellConvoTemplate:addScreen(just_my_luck);

punch_in_location = ConvoScreen:new {
	id = "punch_in_location",
	leftDialog = "@conversation/sean_trenwell:s_78b31931", -- Let me see your datapad for a second. I'll punch in the location for you. Return to me if you find anything. Be sure to speak with my historian at the site. Oh, and beware of the Tuskens!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(punch_in_location);

maybe_later_then = ConvoScreen:new {
	id = "maybe_later_then",
	leftDialog = "@conversation/sean_trenwell:s_dc13d9c7", -- I understand. Maybe later, then.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(maybe_later_then);

thats_unfortunate = ConvoScreen:new {
	id = "thats_unfortunate",
	leftDialog = "@conversation/sean_trenwell:s_61503fc8", -- Oh. That's unfortunate. If you know of an adventurer, please send him or her my way. It would really help me. Thank you.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(thats_unfortunate);

find_anything_of_value = ConvoScreen:new {
	id = "find_anything_of_value",
	leftDialog = "@conversation/sean_trenwell:s_d349c913", -- See if you can find anything of value. Did you speak to my historian? Speak to her when you get to the site.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_1059c36e", "let_historian_screen"}, -- Okay, I'll do that.
		{"@conversation/sean_trenwell:s_3ba540c", "disappointed_but_understand"} -- No thanks, I'd rather not. I'm done with this.
	}
}
seanTrenwellConvoTemplate:addScreen(find_anything_of_value);

disappointed_but_understand = ConvoScreen:new {
	id = "disappointed_but_understand",
	leftDialog = "@conversation/sean_trenwell:s_75491d63", -- As you wish. I'm disappointed, but I understand how these things are.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(disappointed_but_understand);

let_historian_screen = ConvoScreen:new {
	id = "let_historian_screen",
	leftDialog = "@conversation/sean_trenwell:s_f47244aa", -- Excellent. If you find anything, be sure to let my historian screen it. Then report back to me.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(let_historian_screen);

seek_historian = ConvoScreen:new {
	id = "seek_historian",
	leftDialog = "@conversation/sean_trenwell:s_ca646df4", -- My historian, who's out at the crash site. She needs to screen and catalog whatever you find. Go and speak with her.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(seek_historian);

did_you_find_anything = ConvoScreen:new {
	id = "did_you_find_anything",
	leftDialog = "@conversation/sean_trenwell:s_2e38174d", -- Well returned! Did you find anything?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b30bd73c", "can_i_see_it"}, -- Yes, I did.
		{"@conversation/sean_trenwell:s_c8a36ac7", "something_out_there"} -- No, unfortunately. Nothing of use.
	}
}
seanTrenwellConvoTemplate:addScreen(did_you_find_anything);

can_i_see_it = ConvoScreen:new {
	id = "can_i_see_it",
	leftDialog = "@conversation/sean_trenwell:s_9d0c2f9e", -- What did you find? Can I see it? Does it mention my ancestor? Let me have it, please.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_81a382e3", "this_isnt_good"}, -- Here you are.
	}
}
seanTrenwellConvoTemplate:addScreen(can_i_see_it);

this_isnt_good = ConvoScreen:new {
	id = "this_isnt_good",
	leftDialog = "@conversation/sean_trenwell:s_8dc34668", -- Oh no. This isn't good. If the governor finds out that I'm related to such a person, she may just kick me out of office. Here, take it back. Tell you what. If you find some way to destroy it, I'll give you something. Just... get rid of it!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_fcf4d778", "seek_out_contact"}, -- How?
	}
}
seanTrenwellConvoTemplate:addScreen(this_isnt_good);

seek_out_contact = ConvoScreen:new {
	id = "seek_out_contact",
	leftDialog = "@conversation/sean_trenwell:s_5caf6cfd", -- I have a contact with whom you can meet. He has ways of destroying information. Please seek him out. And whatever you do, do not give it to anyone else! This is my career we're talking about here. You'll know where to find him.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(seek_out_contact);

something_out_there = ConvoScreen:new {
	id = "something_out_there",
	leftDialog = "@conversation/sean_trenwell:s_2d1057e6", -- Will you try again? I know there's something out there! Look more closely. I'll be waiting anxiously.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(something_out_there);

take_it_to_contact = ConvoScreen:new {
	id = "take_it_to_contact",
	leftDialog = "@conversation/sean_trenwell:s_5ae436c2", -- Please! Take the disk out of here! Take it to my contact. Here, I'll give you the location again. Get rid of it quickly.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(take_it_to_contact);

disk_dealt_with = ConvoScreen:new {
	id = "disk_dealt_with",
	leftDialog = "@conversation/sean_trenwell:s_a907268e", -- And has the disk been dealt with?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_338ea1e3", ""}, -- Yes, the disk has been taken care of.
	}
}
seanTrenwellConvoTemplate:addScreen(disk_dealt_with);

history_quest_inv_full = ConvoScreen:new {
	id = "history_quest_inv_full",
	leftDialog = "@conversation/sean_trenwell:s_2e05a27f", -- I'm grateful to you and would like to reward you, but you have no room in your inventory. Please, speak to me again when you've made some room.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(history_quest_inv_full);

history_quest_reward = ConvoScreen:new {
	id = "history_quest_reward",
	leftDialog = "@conversation/sean_trenwell:s_bc42a527", -- Finally! I'm so grateful to you. Please, take this as my token of eternal gratitude.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(history_quest_reward);

history_quest_inv_still_full = ConvoScreen:new {
	id = "history_inv_still_full",
	leftDialog = "@conversation/sean_trenwell:s_64f4dd40", -- I'm glad you're back, but you still don't have room. You need to have space in your inventory. Please come speak to me when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(history_inv_still_full);

history_quest_was_full_reward = ConvoScreen:new {
	id = "history_quest_was_full_reward",
	leftDialog = "@conversation/sean_trenwell:s_b893398e", -- Ah good to see you again. Please, take this as a token of my gratitude.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(history_quest_was_full_reward);

init_joined_victor = ConvoScreen:new {
	id = "init_joined_victor",
	leftDialog = "@conversation/sean_trenwell:s_68788cf5", -- I'm sorry to see that another one of Bestine's citizens prefers Defense over Commerce. I'm sure he tricked you into joining his campaign.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b826b85a", "dig_up_some_dirt"}, -- I want to join your campaign.
		{"@conversation/sean_trenwell:s_82e87c1c", "good_bye_then"} -- I gotta go.
	}
}
seanTrenwellConvoTemplate:addScreen(init_joined_victor);

dig_up_some_dirt = ConvoScreen:new {
	id = "dig_up_some_dirt",
	leftDialog = "@conversation/sean_trenwell:s_67295aa1", -- It's not so easy. You can't just join my campaign with the drop of a hat. To prove yourself, you'll need to dig up some dirt on that no-good Victor. Speak with my secretary for all the details. What do you think?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_a8b339fd", "speak_with_secretary"}, -- I'll do it!
		{"@conversation/sean_trenwell:s_1e5ba263", "suit_yourself"} -- No, I don't think so.
	}
}
seanTrenwellConvoTemplate:addScreen(dig_up_some_dirt);

speak_with_secretary = ConvoScreen:new {
	id = "speak_with_secretary",
	leftDialog = "@conversation/sean_trenwell:s_2bc6a2f8", -- Excellent! Now, run along... remember to speak with my secretary.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(speak_with_secretary);

suit_yourself = ConvoScreen:new {
	id = "suit_yourself",
	leftDialog = "@conversation/sean_trenwell:s_82b273a8", -- Suit yourself.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(suit_yourself);

good_bye_then = ConvoScreen:new {
	id = "good_bye_then",
	leftDialog = "@conversation/sean_trenwell:s_bad1d1bb", -- Good bye, then.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(good_bye_then);

init_on_dirt_quest = ConvoScreen:new {
	id = "init_on_dirt_quest",
	leftDialog = "@conversation/sean_trenwell:s_181e49f6", -- Ahh, welcome. I remember sending you out to find dirt on that no-good Victor. Well, did you find any?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_338ea1e3", "so_daft"}, -- Yes, I did. Here you are.
	--{"@conversation/sean_trenwell:s_da9a29e9", "return_when_you_do"} -- No, not yet.
	}
}
seanTrenwellConvoTemplate:addScreen(init_on_dirt_quest);

so_daft = ConvoScreen:new {
	id = "so_daft",
	leftDialog = "@conversation/sean_trenwell:s_a0d033e3", -- This is excellent! I can't believe he would be so daft to do such things! You can now join my campaign. That is what you wanted... right?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_641d98d5", ""}, -- Yes, of course!
	--{"@conversation/sean_trenwell:s_fe8dd35a", "error_of_ways"} -- No, I changed my mind.
	}
}
seanTrenwellConvoTemplate:addScreen(so_daft);

error_of_ways = ConvoScreen:new {
	id = "error_of_ways",
	leftDialog = "@conversation/sean_trenwell:s_a4a25b0f", -- Oh. Well, come back if you discover the error of your ways.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(error_of_ways);

return_when_you_do = ConvoScreen:new {
	id = "return_when_you_do",
	leftDialog = "@conversation/sean_trenwell:s_da9a29e9", -- Ah, well return when you do.  You'll need to go and talk to my secretary if you need more information.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(return_when_you_do);

init_joined_campaign = ConvoScreen:new {
	id = "init_joined_campaign",
	leftDialog = "@conversation/sean_trenwell:s_47a2ec4d", -- It's nice to see you again! How did the voting go?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_d1f385de", ""}, -- It went well. I voted for you.
	--{"@conversation/sean_trenwell:s_e7ffff2", "oh_so_soon"} -- I think I'm going to get going.
	--{"@conversation/sean_trenwell:s_8b63bfe1", "speak_to_secretary"} -- I can't find evidence.
	}
}
seanTrenwellConvoTemplate:addScreen(init_joined_campaign);

init_had_full_inventory = ConvoScreen:new {
	id = "init_had_full_inventory",
	leftDialog = "@conversation/sean_trenwell:s_17a8ddce", -- You were here before, weren't you? About joining my campaign?
	stopConversation = "false",
	options = {
	--{"@conversation/sean_trenwell:s_ff7aeed7", ""}, -- Yes, that was me.
	--{"@conversation/sean_trenwell:s_5ef87080", "oh_so_soon"} -- I've thought about it and no longer want to join your campaign.
	}
}
seanTrenwellConvoTemplate:addScreen(init_had_full_inventory);

speak_to_secretary = ConvoScreen:new {
	id = "speak_to_secretary",
	leftDialog = "@conversation/sean_trenwell:s_bb6b1f4b", -- Really? I thought my secretary knew how to get it for sure. I really think you should speak with her again.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(speak_to_secretary);

oh_so_soon = ConvoScreen:new {
	id = "oh_so_soon",
	leftDialog = "@conversation/sean_trenwell:s_a17fdb9a", -- Oh? So soon? Okay. I should get back to work anyway!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(oh_so_soon);

appreciate_support = ConvoScreen:new {
	id = "appreciate_support",
	leftDialog = "@conversation/sean_trenwell:s_7fa991c4", -- Excellent! I appreciate your support. And to take that further, if I win come back and talk to me. I like to reward those who contribute to my success.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(appreciate_support);

thanks_i_think = ConvoScreen:new {
	id = "thanks_i_think",
	leftDialog = "@conversation/sean_trenwell:s_70b3691e", -- Hmm... you did? Really? Hmm... well, thanks. I think.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(thanks_i_think);

these_things_happen = ConvoScreen:new {
	id = "these_things_happen",
	leftDialog = "@conversation/sean_trenwell:s_ee8c0e93", -- I see. Well, I suppose these things happen. I'm disappointed, but you're free to make whatever mistakes you wish.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(these_things_happen);

sensible_type_rival = ConvoScreen:new {
	id = "sensible_type_rival",
	leftDialog = "@conversation/sean_trenwell:s_51c418fd", -- I knew you would! You seem like the sensible type. If you have questions, you can refer to the disk I just gave you. You'll need to find evidence. I can't think of anyone right now off the top of my head. I'm sure my secretary would know. Be sure to ask her on your way out.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(sensible_type_rival);

disk_inv_full_rival = ConvoScreen:new {
	id = "disk_inv_full_rival",
	leftDialog = "@conversation/sean_trenwell:s_9adf6cf2", -- Thanks for the interest! I guess you don't have enough room to receive the disk, though. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(disk_inv_full_rival);

sensible_type = ConvoScreen:new {
	id = "sensible_type",
	leftDialog = "@conversation/sean_trenwell:s_51c418fd", -- I knew you would! You seem like the sensible type. If you have questions, you can refer to the disk I just gave you. You'll need to find evidence. I can't think of anyone right now off the top of my head. I'm sure my secretary would know. Be sure to ask her on your way out.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(sensible_type);

disk_inv_full = ConvoScreen:new {
	id = "disk_inv_full",
	leftDialog = "@conversation/sean_trenwell:s_9adf6cf2", -- Thanks for the interest! I guess you don't have enough room to receive the disk, though. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(disk_inv_full);

still_full_inventory = ConvoScreen:new {
	id = "still_full_inventory",
	leftDialog = "@conversation/sean_trenwell:s_8784f1db", -- Thanks for the interest, but it looks like you still don't have enough room to receive the disk. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(still_full_inventory);

init_gave_intel_to_hutt = ConvoScreen:new {
	id = "init_gave_intel_to_hutt",
	leftDialog = "@conversation/sean_trenwell:s_2810bcdc", -- How could you give that disk to someone working for Jabba the Hutt??!! My career is in serious jeopardy because of you! I knew I couldn't trust you. Get out of here!!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(init_gave_intel_to_hutt);

addConversationTemplate("seanTrenwellConvoTemplate", seanTrenwellConvoTemplate);
