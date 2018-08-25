victorVisalisConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "victorVisalisConvoHandler",
	screens = {}
}

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/victor_visalis:s_aa1a9de6", -- Can you feel that? The Sand People are getting restless. I can sense it from here. Bestine will not be safe unless we recruit more Imperial Troopers to defend the city. If my... opponent wins the election, I am afraid of what may happen to the people of Bestine. But enough of this. How may I help you?
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_bae6b22d", "lacking_defense"}, -- What are your proposed changes for Bestine?
		{"@conversation/victor_visalis:s_d6a9a15d", "makes_or_breaks"}, -- I'm here to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3", "more_and_more_restless"}, -- Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc", "very_well"}, -- I need to go. I'm sorry.
	}
}
victorVisalisConvoTemplate:addScreen(init_election_phase);

init_not_in_office_election_voted_sean = ConvoScreen:new {
	id = "init_not_in_office_election_voted_sean",
	leftDialog = "@conversation/victor_visalis:s_66e44ee", -- I'm surprised you voted for Sean Trenwell in this election. I don't see how anyone could justify doing that, but apparently you found his ideas palatable. I can't imagine what had to happen to make that possible, and frankly, I don't want to know.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(init_not_in_office_election_voted_sean);

init_not_in_office_election_voted_victor = ConvoScreen:new {
	id = "init_not_in_office_election_voted_victor",
	leftDialog = "@conversation/victor_visalis:s_82dcbdca", -- Ah, thanks for voting for me in this election. I really appreciate it. If I win, come back and speak to me so that I can reward your loyalty.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(init_not_in_office_election_voted_victor);

init_not_in_office_no_election = ConvoScreen:new {
	id = "init_not_in_office_no_election",
	leftDialog = "@conversation/victor_visalis:s_57218e96", -- I am much too occupied at the moment. You may return when the election begins again. Speak with Bestine's citizens. They usually speak of it.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(init_not_in_office_no_election);

init_victor_in_office = ConvoScreen:new {
	id = "init_victor_in_office",
	leftDialog = "@conversation/victor_visalis:s_a19e3981", -- I am now in office, this much is true. However, I have matters on my mind to which I must attend. Is there something you need?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_edafb11b", ""}, -- How goes your work now that you're in office?
	--{"@conversation/victor_visalis:s_6641e79e", ""}, -- I have destroyed the intended target.
	--{"@conversation/victor_visalis:s_42c394e0", "sand_people_fortress"}, -- I'm lost. What do I need to do?
	--{"@conversation/victor_visalis:s_cbb4f307", "target_in_fortress"}, -- I'm still looking for our target.
	--{"@conversation/victor_visalis:s_f70821a3", "released_from_mission"}, -- I quit!
	--{"@conversation/victor_visalis:s_380817dd", "never_seen_before"}, -- I found these weird stones.
	--{"@conversation/victor_visalis:s_82af0027", ""}, -- Hey wait! What about my reward for voting for you?
	--{"@conversation/victor_visalis:s_de1eacb3", ""}, -- Now that another election has begun, are you planning to get re-elected?
	}
}
victorVisalisConvoTemplate:addScreen(init_victor_in_office);

in_office_hasnt_voted = ConvoScreen:new {
	id = "in_office_hasnt_voted",
	leftDialog = "@conversation/victor_visalis:s_e8aff3cd", -- Absolutely. I fully intend to win over Mr.Trenwell once again. We need to keep his meddlesome ideas out of Bestine. Bestine needs more defense and it is defense that I shall give them! Keep me in office and vote in the next election with the governor.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_bae6b22d", "lacking_defense"}, -- What are your proposed changes for Bestine?
		{"@conversation/victor_visalis:s_d6a9a15d", "makes_or_breaks"}, -- I'm here to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3", "more_and_more_restless"}, -- Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_87b97dc", "very_well"}, -- I need to go. I'm sorry.
	}
}
victorVisalisConvoTemplate:addScreen(in_office_hasnt_voted);

lacking_defense = ConvoScreen:new {
	id = "lacking_defense",
	leftDialog = "@conversation/victor_visalis:s_70973a58", -- The city of Bestine is severly lacking when it comes to defense. It is my main concern. The Tusken Raiders have become more daring and have constantly tried to launch attacks against the outer walls of the city. Several people have died. The Empire has kept it quiet, preventing it from reaching the common folk of Bestine. I fear the Tuskens will launch a more devastating attack in the days to come. Several of my sources have confirmed my suspicions.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9", "short_and_clear"}, -- Continue.
	}
}
victorVisalisConvoTemplate:addScreen(lacking_defense);

short_and_clear = ConvoScreen:new {
	id = "short_and_clear",
	leftDialog = "@conversation/victor_visalis:s_486664dd", -- To make it short and clear, my proposed changes for Bestine would be to increase the number of Storm Troopers within Bestine. I plan to establish a special force of Troopers to eradicate the more... dangerous of scum from the city.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_1285849e", "makes_or_breaks"}, -- I've decided to vote for you.
		{"@conversation/victor_visalis:s_1a50f0d3", "more_and_more_restless"}, -- Tell me more about the Tuskens.
		{"@conversation/victor_visalis:s_6cf7afee", "very_well"}, -- I should go.
	}
}
victorVisalisConvoTemplate:addScreen(short_and_clear);

makes_or_breaks = ConvoScreen:new {
	id = "makes_or_breaks",
	leftDialog = "@conversation/victor_visalis:s_c34a7f30", -- A wise choice. However, I know that words do not weigh much in this life. It is action that makes or breaks a nation. The governor has ridiculous restrictions on the voting process. By her words, you will need evidence in order to vote; evidence of a good deed I have done. Childish.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9", "speak_with_others"}, -- Continue.
	}
}
victorVisalisConvoTemplate:addScreen(makes_or_breaks);

speak_with_others = ConvoScreen:new {
	id = "speak_with_others",
	leftDialog = "@conversation/victor_visalis:s_6c1a2811", -- Regardless... if you are serious about the whole ordeal, I suggest you speak with others within the capitol and throughout the city. I am sure I have touched a few lives in my passing, but I do not remember such frivolous things. Should you decide to join my opponent's campaign and uncover the dirt that's bound to be in his past, bring it to me. It is the only way I'll let you back into my campaign if you decide to help him instead.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9", "time_running_out"}, -- Continue.
	}
}
victorVisalisConvoTemplate:addScreen(speak_with_others);

time_running_out = ConvoScreen:new {
	id = "time_running_out",
	leftDialog = "@conversation/victor_visalis:s_59c941ec", -- Time is running out and I have too much to do to explain the intricacies of politics with you. If you decide to join my campaign, I will offer you a diskette that will further explain the process.
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_540ac7e9", "wise_to_agree"}, -- I wish to join your campaign.
	--{"@conversation/victor_visalis:s_540ac7e9", "more_about_museums"}, -- I don't want to join your campaign.
	--{"@conversation/victor_visalis:s_9201d81b", "very_well"}, -- I have to go. Bye!
	}
}
victorVisalisConvoTemplate:addScreen(time_running_out);

need_more_room = ConvoScreen:new {
	id = "need_more_room",
	leftDialog = "@conversation/victor_visalis:s_eafac099", -- I'm glad you have agreed to join my campaign. However, in order to receive the diskette, you'll need more room. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(need_more_room);

wise_to_agree = ConvoScreen:new {
	id = "wise_to_agree",
	leftDialog = "@conversation/victor_visalis:s_b0c249bb", -- You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(wise_to_agree);

more_about_museums = ConvoScreen:new {
	id = "more_about_museums",
	leftDialog = "@conversation/victor_visalis:s_c135d871", -- That's unfortunate. I suppose you care more of museums, historians and new market places than the lives of others. Very well.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(more_about_museums);

more_and_more_restless = ConvoScreen:new {
	id = "more_and_more_restless",
	leftDialog = "@conversation/victor_visalis:s_dcd4d8d5", -- What is there to tell... The Tuskens have become more and more restless with each passing day. New cities have sprung up from the sand literally overnight, backing the Sand People into a small corner of the planet. I fear Bestine is next on the chopping board, so to speak. I have sent several scouts to keep an eye on them.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_540ac7e9", "worthless_things"}, -- Continue.
	}
}
victorVisalisConvoTemplate:addScreen(more_and_more_restless);

worthless_things = ConvoScreen:new {
	id = "worthless_things",
	leftDialog = "@conversation/victor_visalis:s_fc5485d3", -- My opponent will put the city's money into worthless things--markets, hiring historians, a museum--which will severely reduce our defenses. I cannot have that happen. We need to increase the defense... or many will die.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_a76ad142", "makes_or_breaks"}, -- I'm going to vote for you.
		{"@conversation/victor_visalis:s_6cf7afee", "very_well"}, -- I should go.
	}
}
victorVisalisConvoTemplate:addScreen(worthless_things);

in_office_voted_current_election = ConvoScreen:new {
	id = "in_office_voted_current_election",
	leftDialog = "@conversation/victor_visalis:s_578e3372", -- Of course, and I thank you for voting for me. I greatly appreciate it. If I win, come back and speak to me so that I can reward your loyalty.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(in_office_voted_current_election);

in_office_voted_sean_current_election = ConvoScreen:new {
	id = "in_office_voted_sean_current_election",
	leftDialog = "@conversation/victor_visalis:s_5bccff58", -- That is my intention, though I'm surprised to discover that you already voted for Sean Trenwell. I don't see how anyone could justify doing that, but apparently you found his ideas palatable. I can't imagine what had to happen to make that possible, and frankly, I don't want to know.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(in_office_voted_sean_current_election);

main_reward_give = ConvoScreen:new {
	id = "main_reward_give",
	leftDialog = "@conversation/victor_visalis:s_cc9cab18", -- Oh yes! It almost slipped my mind. Here you are.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(main_reward_give);

main_reward_inv_full = ConvoScreen:new {
	id = "main_reward_inv_full",
	leftDialog = "@conversation/victor_visalis:s_adc1f0dc", -- Return when you have more room. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(main_reward_inv_full);

main_reward_already_claimed = ConvoScreen:new {
	id = "main_reward_already_claimed",
	leftDialog = "@conversation/victor_visalis:s_24f8534b", -- Greedy, are you? You already received a 'reward' from me. I must return to my duties. Now, be gone.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(main_reward_already_claimed);

never_seen_before = ConvoScreen:new {
	id = "never_seen_before",
	leftDialog = "@conversation/victor_visalis:s_8d1a9cd2", -- Odd. I've never seen objects like these before. However, they do seem to be very valuable. You may be able to find more information regarding these stones in the new market place. A merchant may know what to do with them. I hear that many of the merchants come and go regularly so you may not be able to find this particular merchant immediately. Keep your eye out though. Merchants can be fickle about their business hours.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(never_seen_before);

released_from_mission = ConvoScreen:new {
	id = "released_from_mission",
	leftDialog = "@conversation/victor_visalis:s_7ce36b97", -- I am disappointed. Very well. You have been released from your mission.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(released_from_mission);

target_in_fortress = ConvoScreen:new {
	id = "target_in_fortress",
	leftDialog = "@conversation/victor_visalis:s_e955e18", -- Our 'target' is in the Fortress. I am unsure of the direct location of where it may be hiding. Most likely,  it could be within the cave system beneath the actual Fortress. Return to me when you have succeeded in your task. Remember, I need proof you have eliminated the target.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(target_in_fortress);

sand_people_fortress = ConvoScreen:new {
	id = "sand_people_fortress",
	leftDialog = "@conversation/victor_visalis:s_269510f1", -- You must travel to the site of the Sand People Fortress and search it for a very powerful Tusken Raider. The Sand People place significance on this particular leader. It has never been seen before, has never been mentioned in any book. We can only assume that, with its destruction, the Sand People will leave the people of Bestine alone for good. My contacts have mentioned an extensive cave system below the Fortress. Search there first.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(sand_people_fortress);

continue_to_serve = ConvoScreen:new {
	id = "continue_to_serve",
	leftDialog = "@conversation/victor_visalis:s_81eb46c0", -- I see that I have already given you your reward for this particular task. Unfortunately, I cannot give you another. I wish you well. Please continue to serve Bestine. Our city is already in debt to you.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(continue_to_serve);

sand_people_will_leave = ConvoScreen:new {
	id = "sand_people_will_leave",
	leftDialog = "@conversation/victor_visalis:s_df711673", -- Ah yes! Indeed you have. Perhaps now the Sand People will leave the people of Bestine alone. I am grateful. Here is your reward.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(sand_people_will_leave);

strike_at_heart = ConvoScreen:new {
	id = "strike_at_heart",
	leftDialog = "@conversation/victor_visalis:s_6775ddea", -- Stressful.  I will use my place in office to my advantage during this dangerous time. We must strike at the heart of the Sand People resistance. I have sent some of Bestine's toughest soldiers to the Tusken Fortress. Unfortunately, they have not returned to us. I fear for the worst. For the first time in my life, I am at a loss...
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_390b2857", "what_could_you_do"}, -- Let me help!
		{"@conversation/victor_visalis:s_e9a49e3", "soldiers_will_return"}, -- Sounds like a tough deal.
	}
}
victorVisalisConvoTemplate:addScreen(strike_at_heart);

soldiers_will_return = ConvoScreen:new {
	id = "soldiers_will_return",
	leftDialog = "@conversation/victor_visalis:s_e52ed44", -- It is my hope that my soldiers will return. I must return to my duties. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(soldiers_will_return);

what_could_you_do = ConvoScreen:new {
	id = "what_could_you_do",
	leftDialog = "@conversation/victor_visalis:s_113169f8", -- You? What could you do? I-ugh. Very well. You may help us. I need for you to go to the Fortress. Our spies have witnessed a power never seen before and it lurks there. A 'brand' of Sand People never mentioned in any book. We think it may be the leading power in the Tusken community, if one could call it that. Kill it. Bring back some significant proof that you've killed it, yes?
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_23e4ded2", "youre_a_coward"}, -- Um.. no.
		{"@conversation/victor_visalis:s_177e9cb7", "leave_with_haste"}, -- Yes! I will help you!
	}
}
victorVisalisConvoTemplate:addScreen(what_could_you_do);

leave_with_haste = ConvoScreen:new {
	id = "leave_with_haste",
	leftDialog = "@conversation/victor_visalis:s_72a766a9", -- Good. Leave with haste. Our target may leave for a more... safe place soon. We must strike when it least expects it and when it is most vulnerable. Travel to Fort Tusken and search there. I wish you luck.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(leave_with_haste);

youre_a_coward = ConvoScreen:new {
	id = "youre_a_coward",
	leftDialog = "@conversation/victor_visalis:s_3516c87", -- I see that you're a coward. Very well.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(youre_a_coward);

bestine_is_safer_place = ConvoScreen:new {
	id = "bestine_is_safer_place",
	leftDialog = "@conversation/victor_visalis:s_ce06af62", -- Things are going extremely well. Thank you for your help earlier. Bestine is now a safer place. Is there anything I can help you with?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_30e8118", "be_safe_my_friend"}, -- Just checking up on things. Bye!
	--{"@conversation/victor_visalis:s_380817dd", "seem_to_be_valuable"}, -- I found these weird stones.
	}
}
victorVisalisConvoTemplate:addScreen(bestine_is_safer_place);

seem_to_be_valuable = ConvoScreen:new {
	id = "seem_to_be_valuable",
	leftDialog = "@conversation/victor_visalis:s_1c1db559", -- Stones? Hmm... They seem to be valuable. Rare, you say? I heard that there are merchants looking for such things over in the city's new market place. However, I hear that those particular merchants are rare. You may have to keep an eye out for them. That is all I know, really.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(seem_to_be_valuable);

be_safe_my_friend = ConvoScreen:new {
	id = "be_safe_my_friend",
	leftDialog = "@conversation/victor_visalis:s_26684a50", -- Very well. Be safe, my friend.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(be_safe_my_friend);

awaiting_word = ConvoScreen:new {
	id = "awaiting_word",
	leftDialog = "@conversation/victor_visalis:s_f594d753", -- Everything's going well. I am awaiting word from Fort Tusken. Excuse me. I must return to my work.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(awaiting_word);

init_on_rival_quest = ConvoScreen:new {
	id = "init_on_rival_quest",
	leftDialog = "@conversation/victor_visalis:s_4e29a0ab", -- I see that you are eager to join my campaign. Do you have the proper evidence against Sean Trenwell? Without it, you'll not be able to join my campaign.
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_6ac98e49", "proven_your_worth"}, -- I have it, yes.
	--{"@conversation/victor_visalis:s_da9a29e9", "stop_wasting_my_time"}, -- No, not yet.
	}
}
victorVisalisConvoTemplate:addScreen(init_on_rival_quest);

proven_your_worth = ConvoScreen:new {
	id = "proven_your_worth",
	leftDialog = "@conversation/victor_visalis:s_7c4e7b68", -- Ahh, excellent. I am satisfied. You have proven your worth and want to join my campaign. Are you sure you want to join us?
	stopConversation = "false",
	options = {
		--{"@conversation/victor_visalis:s_798f58f7", "rival_complete_join_campaign"}, -- Yes, I am sure.
		--{"@conversation/victor_visalis:s_5c46daeb", "be_sure_to_return"}, -- I've changed my mind.
	}
}
victorVisalisConvoTemplate:addScreen(proven_your_worth);

rival_complete_join_campaign = ConvoScreen:new {
	id = "rival_complete_join_campaign",
	leftDialog = "@conversation/victor_visalis:s_572eae57", -- Good. You are wise to agree with my views regarding Bestine and its state of defense. As I may have mentioned, I will give you a diskette to explain anything you may have missed. As for evidence, you will need to speak with several others. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(rival_complete_join_campaign);

rival_complete_inv_full = ConvoScreen:new {
	id = "rival_complete_inv_full",
	leftDialog = "@conversation/victor_visalis:s_eafac099", -- I'm glad you have agreed to join my campaign. However, in order to receive the diskette, you'll need more room. Please come back when you do.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(rival_complete_inv_full);

be_sure_to_return = ConvoScreen:new {
	id = "be_sure_to_return",
	leftDialog = "@conversation/victor_visalis:s_d987b9fe", -- Very well, then. Be sure to return when you've seen that our views are the right path.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(be_sure_to_return);

stop_wasting_my_time = ConvoScreen:new {
	id = "stop_wasting_my_time",
	leftDialog = "@conversation/victor_visalis:s_52a836a3", -- If you're serious about joining my campaign, you'll stop wasting my time and go find the evidence I seek. Again, talk with my secretary for more details.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(stop_wasting_my_time);

init_joined_sean = ConvoScreen:new {
	id = "init_joined_sean",
	leftDialog = "@conversation/victor_visalis:s_26e91e91", -- I see that you have joined the campaign of my opponent. I am disappointed.
	stopConversation = "false",
	options = {
		{"@conversation/victor_visalis:s_b826b85a", "prove_yourself"}, -- I want to join your campaign.
		{"@conversation/victor_visalis:s_67dbab18", "s_67dbab18"}, -- Sorry, I have to go.
	}
}
victorVisalisConvoTemplate:addScreen(init_joined_sean);

prove_yourself = ConvoScreen:new {
	id = "prove_yourself",
	leftDialog = "@conversation/victor_visalis:s_e6a20ca5", -- Unfortunately, you cannot just change your mind when the time is only convenient for you. To prove yourself, you'll need to find evidence that will prove my rival is as ruthless as I think he is. Again, talk with my secretary. I have too much to do at the moment to explain it to you.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(prove_yourself);

init_joined_campaign = ConvoScreen:new {
	id = "init_joined_campaign",
	leftDialog = "@conversation/victor_visalis:s_c2b746c2", -- You have returned. Did you find the proper evidence the governor requires?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_798f58f7", ""}, -- Yes and I voted for you.
	--{"@conversation/victor_visalis:s_700330a5", "speak_with_secretary"}, -- I can't find any evidence.
	--{"@conversation/victor_visalis:s_8999ec9b", "thats_a_pity"}, -- I decided not to vote for you.
	--{"@conversation/victor_visalis:s_dea56128", "very_well"}, -- I have to go.
	}
}
victorVisalisConvoTemplate:addScreen(init_joined_campaign);

bestine_will_be_safe = ConvoScreen:new {
	id = "bestine_will_be_safe",
	leftDialog = "@conversation/victor_visalis:s_73f65b89", -- Thank you. Soon, Bestine will be safe again. I thank you for your support. If I win the election, return to me and you will be greatly rewarded.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(bestine_will_be_safe);

bit_suspicious = ConvoScreen:new {
	id = "bit_suspicious",
	leftDialog = "@conversation/victor_visalis:s_c74fd908", -- I am a bit suspicious... Thank you, then, for your vote. I must get back to work. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(bit_suspicious);

speak_with_secretary = ConvoScreen:new {
	id = "speak_with_secretary",
	leftDialog = "@conversation/victor_visalis:s_41012fd2", -- You can speak with my secretary on the subject. She will know all the details for what you seek.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(speak_with_secretary);

thats_a_pity = ConvoScreen:new {
	id = "thats_a_pity",
	leftDialog = "@conversation/victor_visalis:s_cf6147b3", -- That is a pity. And to think I thought you were the intelligent sort... Very well. Good day.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(thats_a_pity);

init_had_no_room_to_join_campaign = ConvoScreen:new {
	id = "init_had_no_room_to_join_campaign",
	leftDialog = "@conversation/victor_visalis:s_ca4e3819", -- I see you have returned. Last we spoke, you didn't have room for the diskette. Would you like it now?
	stopConversation = "false",
	options = {
	--{"@conversation/victor_visalis:s_c82e9a2f", "humbled_by_request"}, -- Yes, please.
	--{"@conversation/victor_visalis:s_ee26e33e", "very_well"}, -- No thanks!
	}
}
victorVisalisConvoTemplate:addScreen(init_had_no_room_to_join_campaign);

still_no_room_to_join_campaign = ConvoScreen:new {
	id = "still_no_room_to_join_campaign",
	leftDialog = "@conversation/victor_visalis:s_a58217e0", -- You'll need to come back when you have more room.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(still_no_room_to_join_campaign);

youll_need_evidence = ConvoScreen:new {
	id = "youll_need_evidence",
	leftDialog = "@conversation/victor_visalis:s_1b6edbfe", -- Here you are. You'll need evidence in order for your vote to be registered. It is my understanding that my secretary receives letters from the people of Bestine, thanking me for my assistance. She may know the information you seek. I must return to my duties.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(youll_need_evidence);

very_well = ConvoScreen:new {
	id = "very_well",
	leftDialog = "@conversation/victor_visalis:s_28586fd5", -- Very well.
	stopConversation = "true",
	options = {}
}
victorVisalisConvoTemplate:addScreen(very_well);

addConversationTemplate("victorVisalisConvoTemplate", victorVisalisConvoTemplate);
