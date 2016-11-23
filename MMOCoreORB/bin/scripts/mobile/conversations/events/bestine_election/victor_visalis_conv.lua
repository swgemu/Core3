victorVisalisConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victor_visalis_conv_handler",
	screens = {}
}

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/victor_visalis:s_aa1a9de6", --Can you feel that? The Sand People are getting restless. I can sense it from here. Bestine will not be safe unless we recruit more Imperial Troopers to defend the city. If my... opponent wins the election, I am afraid of what may happen to the people of Bestine. But enough of this. How may I help you?
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_bae6b22d","proposed_changes"}, --What are your proposed changes for Bestine?.
		{"@conversation/victor_visalis:s_d6a9a15d","here_to_vote"}, --I'm here to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3","about_tuskens"}, --Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc","endconvo_verywell"}, --I need to go. I'm sorry.
	}
}
victorVisalisConvoTemplate:addScreen(convo_start);

proposed_changes = ConvoScreen:new {
	id = "proposed_changes",
	leftDialog = "@conversation/victor_visalis:s_70973a58", --The city of Bestine is severly lacking when it comes to defense. It is my main concern. The Tusken Raiders have become more daring and have constantly tried to launch attacks against the outer walls of the city. Several people have died. The Empire has kept it quiet, preventing it from reaching the common folk of Bestine. I fear the Tuskens will launch a more devastating attack in the days to come. Several of my sources have confirmed my suspicions.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9","proposed_changes2"}, --Continue.
	}
}
victorVisalisConvoTemplate:addScreen(proposed_changes);

proposed_changes2 = ConvoScreen:new {
	id = "proposed_changes2",
	leftDialog = "@conversation/victor_visalis:s_486664dd", --To make it short and clear, my proposed changes for Bestine would be to increase the number of Storm Troopers within Bestine. I plan to establish a special force of Troopers to eradicate the more... dangerous of scum from the city.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_1285849e","here_to_vote"}, --I've decided to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3","about_tuskens"}, --Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc","endconvo_verywell"}, --I should go.
	}
}
victorVisalisConvoTemplate:addScreen(proposed_changes2);

here_to_vote = ConvoScreen:new {
	id = "here_to_vote",
	leftDialog = "@conversation/victor_visalis:s_c34a7f30", --A wise choice. However, I know that words do not weigh much in this life. It is action that makes or breaks a nation. The governor has ridiculous restrictions on the voting process. By her words, you will need evidence in order to vote; evidence of a good deed I have done. Childish.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9","here_to_vote2"}, --Continue.
	}
}
victorVisalisConvoTemplate:addScreen(here_to_vote);

here_to_vote2 = ConvoScreen:new {
	id = "here_to_vote2",
	leftDialog = "@conversation/victor_visalis:s_6c1a2811", --Regardless... if you are serious about the whole ordeal, I suggest you speak with others within the capitol and throughout the city. I am sure I have touched a few lives in my passing, but I do not remember such frivolous things. Should you decide to join my opponent's campaign and uncover the dirt that's bound to be in his past, bring it to me. It is the only way I'll let you back into my campaign if you decide to help him instead.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9","here_to_vote3"}, --Continue.
	}
}
victorVisalisConvoTemplate:addScreen(here_to_vote2);

here_to_vote3 = ConvoScreen:new {
	id = "here_to_vote3",
	leftDialog = "@conversation/victor_visalis:s_59c941ec", --Time is running out and I have too much to do to explain the intricacies of politics with you. If you decide to join my campaign, I will offer you a diskette that will further explain the process.
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(here_to_vote3);

about_tuskens = ConvoScreen:new {
	id = "about_tuskens",
	leftDialog = "@conversation/victor_visalis:s_dcd4d8d5", --What is there to tell... The Tuskens have become more and more restless with each passing day. New cities have sprung up from the sand literally overnight, backing the Sand People into a small corner of the planet. I fear Bestine is next on the chopping board, so to speak. I have sent several scouts to keep an eye on them.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9","about_tuskens2"}, --Continue.
	}
}
victorVisalisConvoTemplate:addScreen(about_tuskens);

about_tuskens2 = ConvoScreen:new {
	id = "about_tuskens2",
	leftDialog = "@conversation/victor_visalis:s_fc5485d3", --My opponent will put the city's money into worthless things --markets, hiring historians, a museum --which will severely reduce our defenses. I cannot have that happen. We need to increase the defense... or many will die.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_a76ad142","here_to_vote"}, --I'm going to vote for you.
		{"@conversation/victor_visalis:s_6cf7afee","endconvo_verywell"}, --I should go.
	}
}
victorVisalisConvoTemplate:addScreen(about_tuskens2);

notInOffice_noElection = ConvoScreen:new {
	id = "notInOffice_noElection",
	leftDialog = "@conversation/victor_visalis:s_57218e96", --I am much too occupied at the moment. You may return when the election begins again. Speak with Bestine's citizens. They usually speak of it.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(notInOffice_noElection);

rival_player = ConvoScreen:new {
	id = "rival_player",
	leftDialog = "@conversation/victor_visalis:s_26e91e91", --I see that you have joined the campaign of my opponent. I am disappointed.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_b826b85a","action_nquest"}, --I want to join your campaign.
		{"@conversation/victor_visalis:s_67dbab18","endconvo_verywell"}, --Sorry, I have to go.
	}
}
victorVisalisConvoTemplate:addScreen(rival_player);

voted_victor_this_election = ConvoScreen:new {
	id = "voted_victor_this_election",
	leftDialog = "@conversation/victor_visalis:s_82dcbdca", --Ah, thanks for voting for me in this election. I really appreciate it. If I win, come back and speak to me so that I can reward your loyalty.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(voted_victor_this_election);

voted_sean_this_election = ConvoScreen:new {
	id = "voted_sean_this_election",
	leftDialog = "@conversation/victor_visalis:s_66e44ee", --I'm surprised you voted for Sean Trenwell in this election. I don't see how anyone could justify doing that, but apparently you found his ideas palatable. I can't imagine what had to happen to make that possible, and frankly, I don't want to know.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(voted_sean_this_election);

nquest_joincampaign = ConvoScreen:new {
	id = "nquest_joincampaign",
	leftDialog = "@conversation/victor_visalis:s_572eae57", --Good. You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_joincampaign);

joincampaign_noroom = ConvoScreen:new {
	id = "joincampaign_noroom",
	leftDialog = "@conversation/victor_visalis:s_eafac099", --I'm glad you have agreed to join my campaign. However, in order to receive the diskette, you'll need more room. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(joincampaign_noroom);

returned_noroom = ConvoScreen:new {
	id = "returned_noroom",
	leftDialog = "@conversation/victor_visalis:s_ca4e3819", --I see you have returned. Last we spoke, you didn't have room for the diskette. Would you like it now?
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(returned_noroom);

noroom_returned_noroom = ConvoScreen:new {
	id = "noroom_returned_noroom",
	leftDialog = "@conversation/victor_visalis:s_a58217e0", --You'll need to come back when you have more room.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(noroom_returned_noroom);

noroom_returned_joincampaign = ConvoScreen:new {
	id = "noroom_returned_joincampaign",
	leftDialog = "@conversation/victor_visalis:s_1b6edbfe", --Here you are. You'll need evidence in order for your vote to be registered. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(noroom_returned_joincampaign);

cant_find_evidence = ConvoScreen:new {
	id = "cant_find_evidence",
	leftDialog = "@conversation/victor_visalis:s_41012fd2", --You can speak with my secretary on the subject. She will know all the details for what you seek.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(cant_find_evidence);

decided_no_vote = ConvoScreen:new {
	id = "decided_no_vote",
	leftDialog = "@conversation/victor_visalis:s_cf6147b3", --That is a pity. And to think I thought you were the intelligent sort... Very well. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(decided_no_vote);

endconvo_friendly = ConvoScreen:new {
	id = "endconvo_friendly",
	leftDialog = "@conversation/victor_visalis:s_26684a50", --Very well. Be safe, my friend.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(endconvo_friendly);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/victor_visalis:s_c135d871", --That's unfortunate. I suppose you care more of museums, historians and new market places than the lives of others. Very well.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(changed_mind);

action_nquest = ConvoScreen:new {
	id = "action_nquest",
	leftDialog = "@conversation/victor_visalis:s_e6a20ca5", --Unfortunately, you cannot just change your mind when the time is only convenient for you. To prove yourself, you'll need to find evidence that will prove my rival is as ruthless as I think he is. Again, talk with my secretary. I have too much to do at the moment to explain it to you.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(action_nquest);

joinCampaign_giveDisk = ConvoScreen:new {
	id = "joinCampaign_giveDisk",
	leftDialog = "@conversation/victor_visalis:s_b0c249bb", --You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(joinCampaign_giveDisk);

nquest_return = ConvoScreen:new {
	id = "nquest_return",
	leftDialog = "@conversation/victor_visalis:s_4e29a0ab", --I see that you are eager to join my campaign. Do you have the proper evidence against Sean Trenwell? Without it, you'll not be able to join my campaign.
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_return);

nquest_found = ConvoScreen:new {
	id = "nquest_found",
	leftDialog = "@conversation/victor_visalis:s_7c4e7b68", --Ahh, excellent. I am satisfied. You have proven your worth and want to join my campaign. Are you sure you want to join us?
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_found);

nquest_notfound = ConvoScreen:new {
	id = "nquest_notfound",
	leftDialog = "@conversation/victor_visalis:s_52a836a3",  --If you're serious about joining my campaign, you'll stop wasting my time and go find the evidence I seek. Again, talk with my secretary for more details.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_notfound);

nquest_nojoin = ConvoScreen:new {
	id = "nquest_nojoin",
	leftDialog = "@conversation/victor_visalis:s_d987b9fe", --Very well, then. Be sure to return when you've seen that our views are the right path.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_nojoin);

ask_voted = ConvoScreen:new {
	id = "ask_voted",
	leftDialog = "@conversation/victor_visalis:s_c2b746c2", --You have returned. Did you find the proper evidence the governor requires?
	stopConversation = "false",
	options = {	}
}
victorVisalisConvoTemplate:addScreen(ask_voted);

checkForVote_true = ConvoScreen:new {
	id = "checkForVote_true",
	leftDialog = "@conversation/victor_visalis:s_73f65b89", --Thank you. Soon, Bestine will be safe again. I thank you for your support. If I win the election, return to me and you will be greatly rewarded.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(checkForVote_true);

checkForVote_false = ConvoScreen:new {
	id = "checkForVote_false",
	leftDialog = "@conversation/victor_visalis:s_c74fd908", --I am a bit suspicious... Thank you, then, for your vote. I must get back to work. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(checkForVote_false);

victor_inOffice = ConvoScreen:new {
	id = "victor_inOffice",
	leftDialog = "@conversation/victor_visalis:s_a19e3981", -- I am now in office, this much is true. However, I have matters on my mind to which I must attend. Is there something you need?
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(victor_inOffice);

inOffice_votedvictor = ConvoScreen:new {
	id = "inOffice_votedvictor",
	leftDialog = "@conversation/victor_visalis:s_578e3372", --Of course, and I thank you for voting for me. I greatly appreciate it. If I win, come back and speak to me so that I can reward your loyalty.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(inOffice_votedvictor);

inOffice_votedsean = ConvoScreen:new {
	id = "inOffice_votedsean",
	leftDialog = "@conversation/victor_visalis:s_5bccff58", --That is my intention, though I'm surprised to discover that you already voted for Sean Trenwell. I don't see how anyone could justify doing that, but apparently you found his ideas palatable. I can't imagine what had to happen to make that possible, and frankly, I don't want to know.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(inOffice_votedsean);

inOffice_newElection = ConvoScreen:new {
	id = "inOffice_newElection",
	leftDialog = "@conversation/victor_visalis:s_e8aff3cd", --Absolutely. I fully intend to win over Mr.Trenwell once again. We need to keep his meddlesome ideas out of Bestine. Bestine needs more defense and it is defense that I shall give them! Keep me in office and vote in the next election with the governor.
	stopConversation = "false",
	options = {	}
}
victorVisalisConvoTemplate:addScreen(inOffice_newElection);

endconvo_verywell = ConvoScreen:new {
	id = "endconvo_verywell",
	leftDialog = "@conversation/victor_visalis:s_28586fd5", --Very well
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(endconvo_verywell);

tuskenquest_complete = ConvoScreen:new {
	id = "tuskenquest_complete",
	leftDialog = "@conversation/victor_visalis:s_ce06af62", --Things are going extremely well. Thank you for your help earlier. Bestine is now a safer place. Is there anything I can help you with?
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_complete);

tuskenquest_foundstones = ConvoScreen:new {
	id = "tuskenquest_foundstones",
	leftDialog = "@conversation/victor_visalis:s_1c1db559", --Stones? Hmm... They seem to be valuable. Rare, you say? I heard that there are merchants looking for such things over in the city's new market place. However, I hear that those particular merchants are rare. You may have to keep an eye out for them. That is all I know, really.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_foundstones);

inOffice_onTuskenQuest = ConvoScreen:new {
	id = "inOffice_onTuskenQuest",
	leftDialog = "@conversation/victor_visalis:s_f594d753", -- Everything's going well. I am awaiting word from Fort Tusken. Excuse me. I must return to my work.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(inOffice_onTuskenQuest);

destroyed_target = ConvoScreen:new {
	id = "destroyed_target",
	leftDialog = "@conversation/victor_visalis:s_df711673", -- Ah yes! Indeed you have. Perhaps now the Sand People will leave the people of Bestine alone. I am grateful. Here is your reward.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(destroyed_target);

tusken_reward_given = ConvoScreen:new {
	id = "tusken_reward_given",
	leftDialog = "@conversation/victor_visalis:s_81eb46c0", --I see that I have already given you your reward for this particular task. Unfortunately, I cannot give you another. I wish you well. Please continue to serve Bestine. Our city is already in debt to you.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(tusken_reward_given);

retell_tusken_quest = ConvoScreen:new {
	id = "retell_tusken_quest",
	leftDialog = "@conversation/victor_visalis:s_269510f1", --You must travel to the site of the Sand People Fortress and search it for a very powerful Tusken Raider. The Sand People place significance on this particular leader. It has never been seen before, has never been mentioned in any book. We can only assume that, with its destruction, the Sand People will leave the people of Bestine alone for good. My contacts have mentioned an extensive cave system below the Fortress. Search there first.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(retell_tusken_quest);

still_looking = ConvoScreen:new {
	id = "still_looking",
	leftDialog = "@conversation/victor_visalis:s_e955e18", --Our 'target' is in the Fortress. I am unsure of the direct location of where it may be hiding. Most likely,  it could be within the cave system beneath the actual Fortress. Return to me when you have succeeded in your task. Remember, I need proof you have eliminated the target.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(still_looking);

quit_tusken_quest = ConvoScreen:new {
	id = "quit_tusken_quest",
	leftDialog = "@conversation/victor_visalis:s_7ce36b97", --I am disappointed. Very well. You have been released from your mission.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(quit_tusken_quest);

found_stones = ConvoScreen:new {
	id = "found_stones",
	leftDialog = "@conversation/victor_visalis:s_8d1a9cd2", --Odd. I've never seen objects like these before. However, they do seem to be very valuable. You may be able to find more information regarding these stones in the new market place. A merchant may know what to do with them. I hear that many of the merchants come and go regularly so you may not be able to find this particular merchant immediately. Keep your eye out though. Merchants can be fickle about their business hours.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(found_stones);

already_received_election_reward = ConvoScreen:new {
	id = "already_received_election_reward",
	leftDialog = "@conversation/victor_visalis:s_24f8534b", --Greedy, are you? You already received a 'reward' from me. I must return to my duties. Now, be gone.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(already_received_election_reward);

give_election_reward = ConvoScreen:new {
	id = "give_election_reward",
	leftDialog = "@conversation/victor_visalis:s_cc9cab18", --Oh yes! It almost slipped my mind. Here you are.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(give_election_reward);

election_reward_noroom = ConvoScreen:new {
	id = "election_reward_noroom",
	leftDialog = "@conversation/victor_visalis:s_adc1f0dc", --Return when you have more room. I must return to my duties.
	stopConversation = "true",
	options = { }
}
victorVisalisConvoTemplate:addScreen(election_reward_noroom);

tuskenquest_intro = ConvoScreen:new {
	id = "tuskenquest_intro",
	leftDialog = "@conversation/victor_visalis:s_6775ddea", --Stressful.  I will use my place in office to my advantage during this dangerous time. We must strike at the heart of the Sand People resistance. I have sent some of Bestine's toughest soldiers to the Tusken Fortress. Unfortunately, they have not returned to us. I fear for the worst. For the first time in my life, I am at a loss...
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_390b2857","tuskenquest_letmehelp"}, --Let me help!
		{"@conversation/victor_visalis:s_e9a49e3","tuskenquest_toughdeal"}, --Sounds like a tough deal.
	}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_intro);

tuskenquest_letmehelp = ConvoScreen:new {
	id = "tuskenquest_letmehelp",
	leftDialog = "@conversation/victor_visalis:s_113169f8", --You? What could you do? I-ugh. Very well. You may help us. I need for you to go to the Fortress. Our spies have witnessed a power never seen before and it lurks there. A 'brand' of Sand People never mentioned in any book. We think it may be the leading power in the Tusken community, if one could call it that. Kill it. Bring back some significant proof that you've killed it, yes?
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_23e4ded2","tuskenquest_decline"}, --Um.. no.
		{"@conversation/victor_visalis:s_177e9cb7","tuskenquest_accept"}, --Yes! I will help you!
	}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_letmehelp);

tuskenquest_decline = ConvoScreen:new {
	id = "tuskenquest_decline",
	leftDialog = "@conversation/victor_visalis:s_3516c87", --I see that you're a coward. Very well.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_decline);

tuskenquest_accept = ConvoScreen:new {
	id = "tuskenquest_accept",
	leftDialog = "@conversation/victor_visalis:s_72a766a9", --Good. Leave with haste. Our target may leave for a more... safe place soon. We must strike when it least expects it and when it is most vulnerable. Travel to Fort Tusken and search there. I wish you luck.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_accept);

tuskenquest_toughdeal = ConvoScreen:new {
	id = "tuskenquest_toughdeal",
	leftDialog = "@conversation/victor_visalis:s_e52ed44", -- It is my hope that my soldiers will return. I must return to my duties. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(tuskenquest_toughdeal);

addConversationTemplate("victorVisalisConvoTemplate", victorVisalisConvoTemplate);
