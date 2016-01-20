seanTrenwellConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "sean_trenwell_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/sean_trenwell:s_52a14d49", --All this talk about the Tuskens, I can't-Oh! I didn't notice that you had entered my office. Welcome! It definitely is a horrible day outside, unbearably hot indeed. How may I help you?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d","proposed_changes"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_1ee4d2a","about_tuskins"}, --You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(convo_start);

proposed_changes = ConvoScreen:new {
	id = "proposed_changes",
	leftDialog = "@conversation/sean_trenwell:s_928992d9", --I am humbled by your request. Currently, Bestine's markets are inadequate. I have already completed the construction of one market place. If I win this election, I'll put my efforts into attracting new merchants to these areas to help Bestine's economy. Perhaps it will bring about new schematics for our crafters.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_540ac7e9","proposed_changes2"}, -- Continue.
		{"@conversation/sean_trenwell:s_1ee4d2a","about_tuskins"}, --You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(proposed_changes);

proposed_changes2 = ConvoScreen:new {
	id = "proposed_changes2",
	leftDialog = "@conversation/sean_trenwell:s_91135631", --I plan to feature the culture of this area. I intend to hire historians to uncover the history of Bestine. I would also like to see more funding for the museum so that we can bring more artwork to our city. This would give artisans a chance to place their creations on display and share them with a larger audience.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_540ac7e9","proposed_changes3"}, -- Continue.
		{"@conversation/sean_trenwell:s_1ee4d2a","about_tuskins"}, --You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(proposed_changes2);

proposed_changes3 = ConvoScreen:new {
	id = "proposed_changes3",
	leftDialog = "@conversation/sean_trenwell:s_8bdcb5a3", --Additionally, I plan to hire historians to uncover the history of Bestine. Artisans will definitely appreciate the new renovations done to the museum. It will give them a chance to place their creations on display.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"}, --I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"}, --I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(proposed_changes3);


about_tuskins = ConvoScreen:new {
	id = "about_tuskins",
	leftDialog = "@conversation/sean_trenwell:s_df1ac18d", --The Tuskens... My rival is centered on the slight possibility that they might launch an attack against Bestine. I find that highly doubtful. We have enough Troopers walking around as it is and they can easily defend us if needed. The Tuskens aren't brave or stupid enough to come near Bestine. We need to concentrate on the economy by introducing more markets!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d","proposed_changes"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(about_tuskins);

here_to_vote = ConvoScreen:new {
	id = "here_to_vote",
	leftDialog = "@conversation/sean_trenwell:s_d15b93e5", --Excellent news! How does the process go - Oh! You should let the governor, Tour Aryon, know of any evidence of a good deed I have done for the people of Bestine. Take it to her! I have done much for the people of Bestine, so I have confidence that our governor will be impressed. Of course, if you decide I am not the right candidate to represent you, you can always join my rival's campaign instead. Though I can't imagine how that would be possible.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_540ac7e9","here_to_vote2"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(here_to_vote);


here_to_vote2 = ConvoScreen:new {
	id = "here_to_vote2",
	leftDialog = "@conversation/sean_trenwell:s_30eb7833", --After which, if you discover his twisted ideas aren't for you... and I won't be surprised when you do... you'll need to bring back some sort of negative tidbit about him in order for you to be let back into my campaign. Do you get it? I'll just give you a disk to further explain the details.
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(here_to_vote2);

returned_noroom = ConvoScreen:new {
	id = "returned_noroom",
	leftDialog = "@conversation/sean_trenwell:s_17a8ddce", --You were here before, weren't you? About joining my campaign?
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(returned_noroom);

ask_voted = ConvoScreen:new {
	id = "ask_voted",
	leftDialog = "@conversation/sean_trenwell:s_47a2ec4d", --It's nice to see you again! How did the voting go?
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(ask_voted);


checkForVote_true = ConvoScreen:new {
	id = "checkForVote_true",
	leftDialog = "@conversation/sean_trenwell:s_7fa991c4", --Excellent! I appreciate your support. And to take that further, if I win come back and talk to me. I like to reward those who contribute to my success.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(checkForVote_true);


checkForVote_false = ConvoScreen:new {
	id = "checkForVote_false",
	leftDialog = "@conversation/sean_trenwell:s_70b3691e", --Hmm... you did? Really? Hmm... well, thanks. I think.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(checkForVote_false);


get_going = ConvoScreen:new {
	id = "get_going",
	leftDialog = "@conversation/sean_trenwell:s_a17fdb9a", --Oh? So soon? Okay. I should get back to work anyway!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(get_going);


returned_noroom_nojoin = ConvoScreen:new {
	id = "returned_noroom_nojoin",
	leftDialog = "@conversation/sean_trenwell:s_ee8c0e93", --I see. Well, I suppose these things happen. I'm disappointed, but you're free to make whatever mistakes you wish.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(returned_noroom_nojoin);


join_campaign = ConvoScreen:new {
	id = "join_campaign",
	leftDialog = "@conversation/sean_trenwell:s_51c418fd", --I knew you would! You seem like the sensible type. If you have questions, you can refer to the disk I just gave you. You'll need to find evidence. I can't think of anyone right now off the top of my head. I'm sure my secretary would know. Be sure to ask her on your way out.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(join_campaign);

no_inventory_space = ConvoScreen:new {
	id = "no_inventory_space",
	leftDialog = "@conversation/sean_trenwell:s_9adf6cf2", --Thanks for the interest! I guess you don't have enough room to receive the disk, though. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(no_inventory_space);

returned_noroom_still = ConvoScreen:new {
	id = "returned_noroom_still",
	leftDialog = "@conversation/sean_trenwell:s_8784f1db", --Thanks for the interest, but it looks like you still don't have enough room to receive the disk. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(returned_noroom_still);

cant_find_evidence = ConvoScreen:new {
	id = "cant_find_evidence",
	leftDialog = "@conversation/sean_trenwell:s_bb6b1f4b", --Really? I thought my secretary knew how to get it for sure. I really think you should speak with her again.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(cant_find_evidence);

rival_player = ConvoScreen:new {
	id = "rival_player",
	leftDialog = "@conversation/sean_trenwell:s_68788cf5", --I'm sorry to see that another one of Bestine's citizens prefers Defense over Commerce. I'm sure he tricked you into joining his campaign.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b826b85a","prove_yourself"}, -- I want to join your campaign.
		{"@conversation/sean_trenwell:s_82e87c1c","good_bye_then"},--I gotta go.
	}
}
seanTrenwellConvoTemplate:addScreen(rival_player);

voted_sean_this_election = ConvoScreen:new {
	id = "voted_sean_this_election",
	leftDialog = "@conversation/sean_trenwell:s_64c62370", --I hear you spoke to the governor and voted for me. I appreciate that! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(voted_sean_this_election);

voted_victor_this_election = ConvoScreen:new {
	id = "voted_sean_this_election",
	leftDialog = "@conversation/sean_trenwell:s_4c2afce6", --So, you voted for my rival, did you? I see. I guess that's the point of having an open election. I'm disappointed, but that's really all I can say.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(voted_sean_this_election);

prove_yourself = ConvoScreen:new {
	id = "prove_yourself",
	leftDialog = "@conversation/sean_trenwell:s_67295aa1", --It's not so easy. You can't just join my campaign with the drop of a hat. To prove yourself, you'll need to dig up some dirt on that no-good Victor. Speak with my secretary for all the details. What do you think?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_a8b339fd","action_nquest"}, --I'll do it!
		{"@conversation/sean_trenwell:s_1e5ba263","decline_nquest"}, -- --No, I don't think so.
	}
}
seanTrenwellConvoTemplate:addScreen(prove_yourself);

action_nquest = ConvoScreen:new {
	id = "action_nquest",
	leftDialog = "@conversation/sean_trenwell:s_2bc6a2f8", --Excellent! Now, run along... remember to speak with my secretary.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(action_nquest);

decline_nquest = ConvoScreen:new {
	id = "decline_nquest",
	leftDialog = "@conversation/sean_trenwell:s_82b273a8", --Suit yourself.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(decline_nquest);

nquest_return = ConvoScreen:new {
	id = "nquest_return",
	leftDialog = "@conversation/sean_trenwell:s_181e49f6", --Ahh, welcome. I remember sending you out to find dirt on that no-good Victor. Well, did you find any?
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(nquest_return);


nquest_found = ConvoScreen:new {
	id = "nquest_found",
	leftDialog = "@conversation/sean_trenwell:s_a0d033e3", --This is excellent! I can't believe he would be so daft to do such things! You can now join my campaign. That is what you wanted... right?
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(nquest_found);

nquest_notfound = ConvoScreen:new {
	id = "nquest_notfound",
	leftDialog = "@conversation/sean_trenwell:s_aa0406b",  --Ah, well return when you do.  You'll need to go and talk to my secretary if you need more information.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(nquest_notfound);

nquest_nojoin = ConvoScreen:new {
	id = "nquest_nojoin",
	leftDialog = "@conversation/sean_trenwell:s_a4a25b0f", -- Oh. Well, come back if you discover the error of your ways.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(nquest_nojoin);

changed_my_mind = ConvoScreen:new {
	id = "changed_my_mind",
	leftDialog = "@conversation/sean_trenwell:s_483c9216", --I'm sorry to hear that. However, if you do decide that you'd rather join my campaign, please come by again. We could always use your vote.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(changed_my_mind);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@conversation/sean_trenwell:s_bad1d1bb", -- Good bye, then.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(good_bye);

notInOffice_noElection = ConvoScreen:new {
	id = "notInOffice_noElection",
	leftDialog = "@conversation/sean_trenwell:s_6718926b", --Well, I lost the election, but there's always next time. I still have many good ideas for Bestine. You should come back when the next election starts. In fact, the townsfolk usually talk about things like this when they happen. Be sure to talk to them.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(notInOffice_noElection);

disk_to_hutt = ConvoScreen:new {
	id = "disk_to_hutt",
	leftDialog = "@conversation/sean_trenwell:s_2810bcdc", --How could you give that disk to someone working for Jabba the Hutt??!! My career is in serious jeopardy because of you! I knew I couldn't trust you. Get out of here!!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(disk_to_hutt);

have_to_go = ConvoScreen:new {
	id = "have_to_go",
	leftDialog = "@conversation/sean_trenwell:s_91cc7d0", --I wish you well. Come back soon!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(have_to_go);


addConversationTemplate("seanTrenwellConvoTemplate", seanTrenwellConvoTemplate);
