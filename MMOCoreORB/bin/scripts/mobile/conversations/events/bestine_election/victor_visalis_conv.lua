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
		{"@conversation/victor_visalis:s_bae6b22d","proposed_changes"}, --What are your proposed changes for Bestine?
		{"@conversation/victor_visalis:s_d6a9a15d","here_to_vote"}, --I'm here to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3","about_tuskens"}, --Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc","need_to_go"}, --I need to go. I'm sorry.
	}
}
victorVisalisConvoTemplate:addScreen(convo_start);

proposed_changes = ConvoScreen:new {
	id = "proposed_changes",
	leftDialog = "@conversation/victor_visalis:s_70973a58", --The city of Bestine is severly lacking when it comes to defense. It is my main concern. The Tusken Raiders have become more daring and have constantly tried to launch attacks against the outer walls of the city. Several people have died. The Empire has kept it quiet, preventing it from reaching the common folk of Bestine. I fear the Tuskens will launch a more devastating attack in the days to come. Several of my sources have confirmed my suspicions.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9","proposed_changes2"}, --Continue.
		{"@conversation/victor_visalis:s_d6a9a15d","here_to_vote"}, --I'm here to vote for you.		
		{"@conversation/victor_visalis:s_1a50f0d3","about_tuskens"}, --Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc","need_to_go"}, --I need to go. I'm sorry.
	}
}
victorVisalisConvoTemplate:addScreen(proposed_changes);

proposed_changes2 = ConvoScreen:new {
	id = "proposed_changes2",
	leftDialog = "@conversation/victor_visalis:s_486664dd", --To make it short and clear, my proposed changes for Bestine would be to increase the number of Storm Troopers within Bestine. I plan to establish a special force of Troopers to eradicate the more... dangerous of scum from the city.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_1285849e","here_to_vote"}, --I've decided to vote for you.
		{"@conversation/victor_visalis:s_87b97dc","need_to_go"}, --I need to go. I'm sorry.
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
			{"@conversation/victor_visalis:s_6cf7afee","need_to_go"}, --I should go.
	}
}
victorVisalisConvoTemplate:addScreen(about_tuskens2);

noOffice_noElection = ConvoScreen:new {
	id = "noOffice_noElection",
	leftDialog = "@conversation/victor_visalis:s_57218e96", --I am much too occupied at the moment. You may return when the election begins again. Speak with Bestine's citizens. They usually speak of it.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(noOffice_noElection);

rival_player = ConvoScreen:new {
	id = "rival_player",
	leftDialog = "@conversation/victor_visalis:s_26e91e91", --I see that you have joined the campaign of my opponent. I am disappointed.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_b826b85a","action_nquest"}, --I want to join your campaign.
		{"@conversation/victor_visalis:s_67dbab18","have_to_go"}, --Sorry, I have to go.
	}
}
victorVisalisConvoTemplate:addScreen(rival_player);

votedVictorCurrentElection = ConvoScreen:new {
	id = "votedVictorCurrentElection",
	leftDialog = "@conversation/victor_visalis:s_82dcbdca", --Ah, thanks for voting for me in this election. I really appreciate it. If I win, come back and speak to me so that I can reward your loyalty.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(votedVictorCurrentElection);

votedSeanCurrentElection = ConvoScreen:new {
	id = "votedSeanCurrentElection",
	leftDialog = "@conversation/victor_visalis:s_66e44ee", --I'm surprised you voted for Sean Trenwell in this election. I don't see how anyone could justify doing that, but apparently you found his ideas palatable. I can't imagine what had to happen to make that possible, and frankly, I don't want to know.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(votedSeanCurrentElection);

nquest_joincampaign = ConvoScreen:new {
	id = "nquest_joincampaign",
	leftDialog = "@conversation/victor_visalis:s_572eae57", --Good. You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(nquest_joincampaign);

returned_noroom = ConvoScreen:new {
	id = "returned_noroom",
	leftDialog = "@conversation/victor_visalis:s_ca4e3819", --I see you have returned. Last we spoke, you didn't have room for the diskette. Would you like it now?
	stopConversation = "false",
	options = {}
}
victorVisalisConvoTemplate:addScreen(returned_noroom);

returned_maderoom = ConvoScreen:new {
	id = "returned_maderoom",
	leftDialog = "@conversation/victor_visalis:s_1b6edbfe", --Here you are. You'll need evidence in order for your vote to be registered. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(returned_maderoom);

returned_stillnoroom = ConvoScreen:new {
	id = "returned_stillnoroom",
	leftDialog = "@conversation/victor_visalis:s_a58217e0", --You'll need to come back when you have more room.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(returned_stillnoroom);

joincampaign_noroom = ConvoScreen:new {
	id = "joincampaign_noroom",
	leftDialog = "@conversation/victor_visalis:s_eafac099", --I'm glad you have agreed to join my campaign. However, in order to receive the diskette, you'll need more room. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(joincampaign_noroom);

cant_find_evidence = ConvoScreen:new {
	id = "cant_find_evidence",
	leftDialog = "@conversation/victor_visalis:s_41012fd2", --You can speak with my secretary on the subject. She will know all the details for what you seek.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(cant_find_evidence);

still_no_room = ConvoScreen:new {
	id = "still_no_room",
	leftDialog = "@conversation/victor_visalis:s_a58217e0", --You'll need to come back when you have more room.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(still_no_room);

decided_no_vote = ConvoScreen:new {
	id = "decided_no_vote",
	leftDialog = "@conversation/victor_visalis:s_cf6147b3", --That is a pity. And to think I thought you were the intelligent sort... Very well. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(decided_no_vote);

need_to_go = ConvoScreen:new {
	id = "need_to_go",
	leftDialog = "@conversation/victor_visalis:s_28586fd5", --Very well
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(need_to_go);

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

givedisk_joincampaign = ConvoScreen:new {
	id = "givedisk_joincampaign",
	leftDialog = "@conversation/victor_visalis:s_b0c249bb", --You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(givedisk_joincampaign);

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

neg_quests_changed_mind = ConvoScreen:new {
	id = "neg_quests_changed_mind",
	leftDialog = "@conversation/victor_visalis:s_d987b9fe", --Very well, then. Be sure to return when you've seen that our views are the right path.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(neg_quests_changed_mind);

ask_voted = ConvoScreen:new {
	id = "ask_voted",
	leftDialog = "@conversation/victor_visalis:s_c2b746c2", --You have returned. Did you find the proper evidence the governor requires?
	stopConversation = "false",
	options = { }
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

addConversationTemplate("victorVisalisConvoTemplate", victorVisalisConvoTemplate);
