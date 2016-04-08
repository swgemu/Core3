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

inOffice_newElection = ConvoScreen:new {
	id = "inOffice_newElection",
	leftDialog = "@conversation/sean_trenwell:s_c6d1b21", --That's correct and so far our efforts seem to be going well.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_6ba0df1d","proposed_changes"}, -- I want to hear about your proposed changes.
		{"@conversation/sean_trenwell:s_1ee4d2a","about_tuskins"}, --You mentioned something about the Tuskens...
		{"@conversation/sean_trenwell:s_d6a9a15d","here_to_vote"},--I'm here to vote for you.
		{"@conversation/sean_trenwell:s_bab1f93a","have_to_go"},--I have to go. Sorry!
	}
}
seanTrenwellConvoTemplate:addScreen(inOffice_newElection);

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
	options = { }
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

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/sean_trenwell:s_8784f1db", --Thanks for the interest, but it looks like you still don't have enough room to receive the disk. You'll need to come back when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(noroom_returned_noroom);

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
		{"@conversation/sean_trenwell:s_82e87c1c","good_bye"},--I gotta go.
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

sean_inOffice = ConvoScreen:new {
	id = "sean_inOffice",
	leftDialog = "@conversation/sean_trenwell:s_7f70fe38", --Now that I'm in office, I can finally set some of my ideas into action. The marketplace could definitely use some attention, and I should make sure everything at the museum is going well.
	stopConversation = "false",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(sean_inOffice);

inOffice_alreadyReceivedReward = ConvoScreen:new {
	id = "inOffice_alreadyReceivedReward",
	leftDialog = "@conversation/sean_trenwell:s_c27445f0", --Reward? I think not. You already received one.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_alreadyReceivedReward);

inOffice_giveReward = ConvoScreen:new {
	id = "inOffice_giveReward",
	leftDialog = "@conversation/sean_trenwell:s_f81b7edd", --Oh yeah! Again I thank you for the help and for your support, I've prepared a little gift for you.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_giveReward);

inOffice_giveReward_noroom = ConvoScreen:new {
	id = "inOffice_giveReward_noroom",
	leftDialog = "@conversation/sean_trenwell:s_88b2f5bd", --I have a nice reward for you, but you don't seem to have room to take it. Please return after making some room in your inventory.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_giveReward_noroom);

inOffice_giveHistoryReward_noroom_returned = ConvoScreen:new {
	id = "inOffice_giveHistoryReward_noroom_returned",
	leftDialog = "@conversation/sean_trenwell:s_64f4dd40", -- I'm glad you're back, but you still don't have room. You need to have space in your inventory. Please come speak to me when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_giveHistoryReward_noroom_returned);

inOffice_giveHistoryReward = ConvoScreen:new {
	id = "inOffice_giveHistoryReward",
	leftDialog = "@conversation/sean_trenwell:s_b893398e", --Ah good to see you again. Please, take this as a token of my gratitude.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_giveHistoryReward);

inOffice_HowsWork = ConvoScreen:new {
	id = "inOffice_HowsWork",
	leftDialog = "@conversation/sean_trenwell:s_c1c018c3", --Good for you. I always like to see people taking an interest in politics.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_HowsWork);

inOffice_playerVoted = ConvoScreen:new {
	id = "inOffice_playerVoted",
	leftDialog = "@conversation/sean_trenwell:s_f1b007b2", --I heard and greatly appreciate it! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_playerVoted);

inOffice_yourPlans = ConvoScreen:new {
	id = "inOffice_yourPlans",
	leftDialog = "@conversation/sean_trenwell:s_dab387e8", --Indeed I do! History is a passion of mine, especially since my ancestors were among the original settlers of Bestine. I've gotten enough funding to hire a historian. We made an exciting new discovery just last week! A terrible desert storm came through and kicked up loose sand and beneath was a wrecked ship. We think it may be the Red-Sin Valon, the vessel used to transport the early settlers to Tatooine. It's so exciting!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_4ff8cd88","inOffice_yourPlans_2"}, --I suppose	
	}
}
seanTrenwellConvoTemplate:addScreen(inOffice_yourPlans);

inOffice_yourPlans_2 = ConvoScreen:new {
	id = "inOffice_yourPlans_2",
	leftDialog = "@conversation/sean_trenwell:s_d485fca4", --Yes. Anyway, lately we've experienced brutal attacks from the Sand People. My historian is having a hard time of it, and I'm not sure her efforts can continue. She doesn't possess a brawler's spirit or the skill of a marksman. She's just a scholar. It's depressing to think that our attempts to restore the Red-Sin Valon have been fruitless. Do you think you can help? You seem like an adventurer. Or am I wrong?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_9a679e7f","inOffice_youre_wrong"}, --You're wrong.
		{"@conversation/sean_trenwell:s_1e35bbba","inOffice_adventurer"}, --I am an adventurer!
	}
}
seanTrenwellConvoTemplate:addScreen(inOffice_yourPlans_2);

inOffice_youre_wrong = ConvoScreen:new {
	id = "inOffice_youre_wrong",
	leftDialog = "@conversation/sean_trenwell:s_61503fc8",--Oh. That's unfortunate. If you know of an adventurer, please send him or her my way. It would really help me. Thank you.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_youre_wrong);

inOffice_adventurer = ConvoScreen:new {
	id = "inOffice_adventurer",
	leftDialog = "@conversation/sean_trenwell:s_a5cd533e",--Just my luck! I could really use your help. The Red-Sin Valon find is phenomenal in of itself, but what if there's more? I want you to bring back any information you can. There must be some sort of log of the events surrounding the early settlement attempts. I'd really like for you to find it. Do you think you can do that?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b45b3794","inOffice_accept_HQuest"},	--Sounds like fun. I'll do it!
		{"@conversation/sean_trenwell:s_2ac8d04c","inOffice_decline_HQuest"},	--No, I can't.
	}
}
seanTrenwellConvoTemplate:addScreen(inOffice_adventurer);

inOffice_accept_HQuest = ConvoScreen:new {
	id = "inOffice_accept_HQuest",
	leftDialog = "@conversation/sean_trenwell:s_78b31931",  --Let me see your datapad for a second. I'll punch in the location for you. Return to me if you find anything. Be sure to speak with my historian at the site. Oh, and beware of the Tuskens!
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_accept_HQuest);

inOffice_decline_HQuest = ConvoScreen:new {
	id = "inOffice_decline_HQuest",
	leftDialog = "@conversation/sean_trenwell:s_dc13d9c7",  --I understand. Maybe later, then.
	stopConversation = "true",
	options = {}
}
seanTrenwellConvoTemplate:addScreen(inOffice_decline_HQuest);

historyQuest_SpokeToContact = ConvoScreen:new {
  id = "historyQuest_SpokeToContact",
  leftDialog = "@conversation/sean_trenwell:s_7fc36aab",  -- And has the disk been dealt with?
  stopConversation = "false",
  options = { }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_SpokeToContact);

historyQuest_HasDisk = ConvoScreen:new {
  id = "historyQuest_HasDisk",
  leftDialog = "@conversation/sean_trenwell:s_5ae436c2",  -- Please! Take the disk out of here! Take it to my contact. Here, I'll give you the location again. Get rid of it quickly.
  stopConversation = "true",
  options = {  }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_HasDisk);

historyQuest_DestroyedDisk_noroom = ConvoScreen:new {
  id = "historyQuest_DestroyedDisk_noroom",
  leftDialog = "@conversation/sean_trenwell:s_2e05a27f",  --I'm grateful to you and would like to reward you, but you have no room in your inventory. Please, speak to me again when you've made some room.
  stopConversation = "true",
  options = {  }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_DestroyedDisk_noroom);

historyQuest_DestroyedDisk = ConvoScreen:new {
  id = "historyQuest_DestroyedDisk",
  leftDialog = "@conversation/sean_trenwell:s_bc42a527",  --Finally! I'm so grateful to you. Please, take this as my token of eternal gratitude.
  stopConversation = "true",
  options = { }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_DestroyedDisk);

historyQuest_SearchedCrashSite = ConvoScreen:new {
  id = "historyQuest_SearchedCrashSite",
  leftDialog = "@conversation/sean_trenwell:s_2e38174d",  --Well returned! Did you find anything?
  stopConversation = "false",
  options = { 
   --{"@conversation/sean_trenwell:s_b30bd73c","SearchedCrashSite_Found"},  --Yes, I did.
  }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_SearchedCrashSite);

SearchedCrashSite_Found = ConvoScreen:new {
  id = "SearchedCrashSite_Found",
  leftDialog = "@conversation/sean_trenwell:s_9d0c2f9e",  --What did you find? Can I see it? Does it mention my ancestor? Let me have it, please.
  stopConversation = "false",
  options = {
  {"@conversation/sean_trenwell:s_81a382e3","HistoryQuest_ShowDisk"},  --Here you are.
  }
}
seanTrenwellConvoTemplate:addScreen(SearchedCrashSite_Found);

HistoryQuest_ShowDisk = ConvoScreen:new {
  id = "HistoryQuest_ShowDisk",
  leftDialog = "@conversation/sean_trenwell:s_8dc34668",  -- Oh no. This isn't good. If the governor finds out that I'm related to such a person, she may just kick me out of office. Here, take it back. Tell you what. If you find some way to destroy it, I'll give you something. Just... get rid of it!
  stopConversation = "false",
  options = {
     {"@conversation/sean_trenwell:s_fcf4d778","HistoryQuest_SeansContact"}, --How?
  }
}
seanTrenwellConvoTemplate:addScreen(HistoryQuest_ShowDisk);


HistoryQuest_SeansContact = ConvoScreen:new {
  id = "HistoryQuest_SeansContact",
  leftDialog = "@conversation/sean_trenwell:s_5caf6cfd",  -- I have a contact with whom you can meet. He has ways of destroying information. Please seek him out. And whatever you do, do not give it to anyone else! This is my career we're talking about here. You'll know where to find him.
  stopConversation = "true",
  options = {
  }
}
seanTrenwellConvoTemplate:addScreen(HistoryQuest_SeansContact);

SearchedCrashSite_NotFound = ConvoScreen:new {
  id = "SearchedCrashSite_NotFound",
  leftDialog = "@conversation/sean_trenwell:s_2d1057e6",  --Will you try again? I know there's something out there! Look more closely. I'll be waiting anxiously.
  stopConversation = "true",
  options = {
  }
}
seanTrenwellConvoTemplate:addScreen(SearchedCrashSite_NotFound);

historyQuest_SeanHistorian = ConvoScreen:new {
  id = "historyQuest_SeanHistorian",
  leftDialog = "@conversation/sean_trenwell:s_ca646df4",  --My historian, who's out at the crash site. She needs to screen and catalog whatever you find. Go and speak with her.
  stopConversation = "true",
  options = { }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_SeanHistorian);

historyQuest_CrashSite = ConvoScreen:new {
  id = "historyQuest_CrashSite",
  leftDialog = "@conversation/sean_trenwell:s_d349c913",  --See if you can find anything of value. Did you speak to my historian? Speak to her when you get to the site.
  stopConversation = "false",
  options = {
      {"@conversation/sean_trenwell:s_1059c36e","historyQuest_CrashSite_dothat"}, --Okay, I'll do that.
      {"@conversation/sean_trenwell:s_3ba540c","historyQuest_CrashSite_quit"}, --No thanks, I'd rather not. I'm done with this.
   }
}
seanTrenwellConvoTemplate:addScreen(historyQuest_CrashSite);

historyQuest_CrashSite_dothat = ConvoScreen:new {
  id = "historyQuest_CrashSite_dothat",
  leftDialog = "@conversation/sean_trenwell:s_f47244aa",  --Excellent. If you find anything, be sure to let my historian screen it. Then report back to me.
  stopConversation = "true",
  options = {}
}
seanTrenwellConvoTemplate:addScreen(historyQuest_CrashSite_dothat);

historyQuest_CrashSite_quit = ConvoScreen:new {
  id = "historyQuest_CrashSite_quit",
  leftDialog = "@conversation/sean_trenwell:s_75491d63",  --As you wish. I'm disappointed, but I understand how these things are.
  stopConversation = "true",
  options = {}
}
seanTrenwellConvoTemplate:addScreen(historyQuest_CrashSite_quit);

addConversationTemplate("seanTrenwellConvoTemplate", seanTrenwellConvoTemplate);
