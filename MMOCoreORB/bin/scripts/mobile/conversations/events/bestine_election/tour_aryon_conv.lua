tourAryonConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tourAryonConvoHandler",
	screens = {}
}

init_not_election_phase = ConvoScreen:new {
	id = "init_not_election_phase",
	leftDialog = "@conversation/tour_aryon:s_57d5a9c4", -- It's good to know that the citizens of Bestine care about the city. A fact much in evidence when so many people voted during the last election. And they chose wisely... I am quite satisfied with the winning candidate. You should come back in the next months. Listen to the people of Bestine. They usually talk about the events surrounding the city.
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_5d2e1112", ""}, -- Who was the winning candidate?
	--{"@conversation/tour_aryon:s_68d96c4a", ""} -- When does the next election begin?
	}
}
tourAryonConvoTemplate:addScreen(init_not_election_phase);

sean_won = ConvoScreen:new {
	id = "sean_won",
	leftDialog = "@conversation/tour_aryon:s_1797f2fb", -- Sean Trenwell won the election. Sean seems quite interested in the  financial and cultural health of Bestine. I'm sure he'll do a very good job.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(sean_won);

victor_won = ConvoScreen:new {
	id = "victor_won",
	leftDialog = "@conversation/tour_aryon:s_7420991b", -- Victor Visalis won the election. Victor is very concerned with the welfare of those living in and visiting Bestine. He has strong ideas for increasing security and for providing better protection from the bands of Sand People that have been assaulting the city recently.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(victor_won);

no_one_won = ConvoScreen:new {
	id = "no_one_won",
	leftDialog = "@conversation/tour_aryon:s_f9c0d87f", -- I seem to be confused and don't know who won. Maybe I should cut back on the Corellian ale.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(no_one_won);

init_election_phase = ConvoScreen:new {
	id = "init_election_phase",
	leftDialog = "@conversation/tour_aryon:s_c1091f5a", -- It's always good to speak with one of our citizens. Are you here to speak about the little election I'm staging?
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_fad1aba", "proper_evidence"}, -- I have some evidence I'd like to show you. It's for the election.
	--{"@conversation/tour_aryon:s_ca478f48", ""} -- Yes, I'd like to get involved.
	--{"@conversation/tour_aryon:s_3001dad0", "enjoy_your_time"} -- No, not really. Just wandering through Bestine.
	}
}
tourAryonConvoTemplate:addScreen(init_election_phase);

proper_evidence = ConvoScreen:new {
	id = "proper_evidence",
	leftDialog = "@conversation/tour_aryon:s_2a9eedba", -- I am glad you're taking a part in this election. So many people have voted already and there will be tons more by night's end. I'll only register your vote if you have the proper evidence. Are you ready to vote?
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_1a74caee", "glad_youre_taking_part"}, -- I am ready to vote.
	--{"@conversation/tour_aryon:s_3829680a", "completely_understand"}, -- On second thought, I think I'm not quite ready.
	}
}
tourAryonConvoTemplate:addScreen(proper_evidence);

get_involved_hasnt_voted = ConvoScreen:new {
	id = "get_involved_hasnt_voted",
	leftDialog = "@conversation/tour_aryon:s_b1c70765", -- The capitol has been very active recently with the news of the new election. I have a new project that I'm heading and have chosen two eligible candidates to work with me. However, to avoid the show of unfair favoritism, I have left it to the people of Bestine to select the politician who best represents them. I've been taking votes all day. It's been a long and tedious process, but it's been interesting. Are you here to vote?
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_bb225c00", "two_candidates"}, -- I need more information.
	--{"@conversation/tour_aryon:s_65a4282", "glad_youre_taking_part"} -- I'd like to vote, yes.
	--{"@conversation/tour_aryon:s_fb124268", "completely_understand"} -- No, I really need to go.
	}
}
tourAryonConvoTemplate:addScreen(get_involved_hasnt_voted);

two_candidates = ConvoScreen:new {
	id = "two_candidates",
	leftDialog = "@conversation/tour_aryon:s_5ff564e3", -- The two candidates are Victor Visalis, Officer of Defense and Sean Trenwell, Director of Commerce. You'll need to speak with either of the two and join their campaign. They'll most likely tell you what they propose for Bestine and the changes that will take hold if they win. After speaking with the politician of your choice, you'll need to decide if you wish to vote for him.
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_540ac7e9", "select_right_man"}, -- Continue.
	}
}
tourAryonConvoTemplate:addScreen(two_candidates);

select_right_man = ConvoScreen:new {
	id = "select_right_man",
	leftDialog = "@conversation/tour_aryon:s_fbf7f817", -- It is imperative that I select the right man for the job. Just giving me a name won't do. You'll need to bring me evidence of a good deed in order for your vote to be registered. For example, if you wish to vote for Victor, you'll need to bring me evidence of a good deed he has done for the people of Bestine. The same goes for Sean. You'll want to speak with the various people around the capitol. I'm sure they will have ideas for evidence.
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_e547fd1e", "only_positive_things"}, -- Yeah?
	}
}
tourAryonConvoTemplate:addScreen(select_right_man);

only_positive_things = ConvoScreen:new {
	id = "only_positive_things",
	leftDialog = "@conversation/tour_aryon:s_1ec9d0f0", -- I only want to hear positive things about the candidates. There has been too many scandals and ill-spoken words thrown about during this thing. I'm really tired of it. I need to get back to work. I have a lot of things I need to get done. Go speak with either Victor Visalis or Sean Trenwell.
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_e547fd1e", "glad_youre_taking_part"}, -- Okay. I'd like to vote.
	--{"@conversation/tour_aryon:s_3829680a", "completely_understand"}, -- I'm... uh, gonna go. Bye!
	}
}
tourAryonConvoTemplate:addScreen(only_positive_things);

glad_youre_taking_part = ConvoScreen:new {
	id = "glad_youre_taking_part",
	leftDialog = "@conversation/tour_aryon:s_9bf39028", -- I am glad you're taking a part in this election. So many people have voted already and there will be tons more by night's end. I'll only register your vote if you have the proper evidence. Do you need more information? Or are you ready to vote?
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_1a74caee", ""}, -- I am ready to vote.
	--{"@conversation/tour_aryon:s_23b3506c", "two_eligible_candidates"}, -- I need more information, please.
	--{"@conversation/tour_aryon:s_a44272b4", "without_proper_evidence"}, -- What evidence?
	}
}
tourAryonConvoTemplate:addScreen(glad_youre_taking_part);

without_proper_evidence = ConvoScreen:new {
	id = "without_proper_evidence",
	leftDialog = "@conversation/tour_aryon:s_9b77406a", -- Unfortunately, without the proper evidence, I cannot register your vote. Evidence can be anywhere from a written testimony from someone in the city, to a data disk containing valuable information. The evidence needs to be tied to a good deed. Do you have such evidence?
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_90ec63e0", "are_you_ready"}, -- Yes, I do.
	--{"@conversation/tour_aryon:s_1f2450ea", "will_be_here"}, -- No, I need to go get it.
	}
}
tourAryonConvoTemplate:addScreen(without_proper_evidence);

are_you_ready = ConvoScreen:new {
	id = "are_you_ready",
	leftDialog = "@conversation/tour_aryon:s_23877744", -- Are you ready to vote?
	stopConversation = "false",
	options = {
	--{"@conversation/tour_aryon:s_1a74caee", "has_victor_evidence"}, -- I am ready to vote.
	--{"@conversation/tour_aryon:s_1a74caee", "has_sean_evidence"}, -- I am ready to vote.
	--{"@conversation/tour_aryon:s_1a74caee", "has_no_evidence"}, -- I am ready to vote.
	}
}
tourAryonConvoTemplate:addScreen(are_you_ready);

has_sean_evidence = ConvoScreen:new {
	id = "has_sean_evidence",
	leftDialog = "@conversation/tour_aryon:s_f3d3efe5", -- Excellent! I see that you have positive evidence to support Sean Trenwell's campaign. Do you wish to vote for him?
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_b51737ff", "vote_for_sean"}, -- Yes, I wish to vote for him.
		{"@conversation/tour_aryon:s_91852029", "be_sure_to_return"}, -- I've changed my mind and would like to think about this a bit more.
	}
}
tourAryonConvoTemplate:addScreen(has_sean_evidence);

vote_for_sean = ConvoScreen:new {
	id = "vote_for_sean",
	leftDialog = "@conversation/tour_aryon:s_b1e3db3e", -- Thank you for your vote. I will keep the tally in my database for when the election has been drawn to a close.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(vote_for_sean);

has_victor_evidence = ConvoScreen:new {
	id = "has_victor_evidence",
	leftDialog = "@conversation/tour_aryon:s_bf3641cd", -- Excellent! I see that you have positive evidence to support Victor Visalis' campaign. Do you wish to vote for him?
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_b51737ff", "vote_for_victor"}, -- Yes, I wish to vote for him.
		{"@conversation/tour_aryon:s_91852029", "be_sure_to_return"}, -- I've changed my mind and would like to think about this a bit more.
	}
}
tourAryonConvoTemplate:addScreen(has_victor_evidence);

vote_for_victor = ConvoScreen:new {
	id = "vote_for_victor",
	leftDialog = "@conversation/tour_aryon:s_b1e3db3e", -- Thank you for your vote. I will keep the tally in my database for when the election has been drawn to a close.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(vote_for_victor);

be_sure_to_return = ConvoScreen:new {
	id = "be_sure_to_return",
	leftDialog = "@conversation/tour_aryon:s_de483def", -- I understand. Please take what time you need, but be sure to return before the election ends.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(be_sure_to_return);

has_no_evidence = ConvoScreen:new {
	id = "has_no_evidence",
	leftDialog = "@conversation/tour_aryon:s_7603d7cd", -- Unfortunately, without the proper evidence, I cannot register your vote. Evidence can be anywhere from a written testimony from someone in the city, to a data disk containing valuable information. The evidence needs to be tied to a good deed. Return when you have such data.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(has_no_evidence);

will_be_here = ConvoScreen:new {
	id = "will_be_here",
	leftDialog = "@conversation/tour_aryon:s_567d69e1", -- I will be here when you return. I am looking forward to collecting your vote for the election!
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(will_be_here);

two_eligible_candidates = ConvoScreen:new {
	id = "two_eligible_candidates",
	leftDialog = "@conversation/tour_aryon:s_16d541d2", -- There are two candidates eligible to work with me on a new project. The candidates are Victor Visalis, Officer of Defense and Sean Trenwell, Director of Commerce. You'll need to speak with either of the two and join their campaign. They'll most likely tell you what they propose for Bestine and the changes that will take hold if they win.
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_540ac7e9", "need_to_decide"}, -- Continue.
	}
}
tourAryonConvoTemplate:addScreen(two_eligible_candidates);

need_to_decide = ConvoScreen:new {
	id = "need_to_decide",
	leftDialog = "@conversation/tour_aryon:s_3c509be9", -- After speaking with the politician of your choice, you'll need to decide if you wish to vote for him. It is imperative that I select the right man for the job. Just giving me a name won't do. You'll need to bring me evidence of a good deed in order for your vote to be registered. For example, if you wish to vote for Victor, you'll need to bring me evidence of a good deed he has done for the people of Bestine. The same goes for Sean.
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_e547fd1e", "speak_with_people"}, -- Yeah?
	}
}
tourAryonConvoTemplate:addScreen(need_to_decide);

speak_with_people = ConvoScreen:new {
	id = "speak_with_people",
	leftDialog = "@conversation/tour_aryon:s_6ff89ddc", -- You'll want to speak with the various people around the capitol. I'm sure they will have ideas for evidence. I only want to hear positive things about the candidates. There has been too many scandals and ill-spoken words thrown about during this thing. I'm really tired of it. I need to get back to work. I have a lot of things I need to get done. Go speak with either Victor Visalis or Sean Trenwell.
	stopConversation = "false",
	options = {
		{"@conversation/tour_aryon:s_eea34749", "wish_you_well"}, -- Okay. Thank you!
	}
}
tourAryonConvoTemplate:addScreen(speak_with_people);

wish_you_well = ConvoScreen:new {
	id = "wish_you_well",
	leftDialog = "@conversation/tour_aryon:s_ab50056b", -- I wish you well!
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(wish_you_well);

completely_understand = ConvoScreen:new {
	id = "completely_understand",
	leftDialog = "@conversation/tour_aryon:s_dfebee34", -- I completely understand. I too have to complete a lot of work before the election. Feel free to come by when you have time and vote.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(completely_understand);

get_involved_already_voted = ConvoScreen:new {
	id = "get_involved_already_voted",
	leftDialog = "@conversation/tour_aryon:s_2230b5b1", -- I see you've already voted. Unfortunately, you can only vote once per election. Be sure to come back during the next election and participate then!
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(get_involved_already_voted);

enjoy_your_time = ConvoScreen:new {
	id = "enjoy_your_time",
	leftDialog = "@conversation/tour_aryon:s_6beb48d3", -- I hope you enjoy your time here.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(enjoy_your_time);

within_the_hour = ConvoScreen:new {
	id = "within_the_hour",
	leftDialog = "@conversation/tour_aryon:s_a87968a2", -- The next election starts within the hour.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(within_the_hour);

in_a_few_hours = ConvoScreen:new {
	id = "in_a_few_hours",
	leftDialog = "@conversation/tour_aryon:s_ae946995", -- The next election starts in just a few hours.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_a_few_hours);

in_less_than_a_day = ConvoScreen:new {
	id = "in_less_than_a_day",
	leftDialog = "@conversation/tour_aryon:s_bc2f5e3d",  -- In less than a day the next election will begin.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_less_than_a_day);

in_more_than_a_day = ConvoScreen:new {
	id = "in_more_than_a_day",
	leftDialog = "@conversation/tour_aryon:s_9fadb4cd", -- The election won't begin for more than a day.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_more_than_a_day);

just_a_few_days = ConvoScreen:new {
	id = "just_a_few_days",
	leftDialog = "@conversation/tour_aryon:s_9e562b00", -- It's just a few days until the next election begins.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(just_a_few_days);

in_less_than_a_week = ConvoScreen:new {
	id = "in_less_than_a_week",
	leftDialog = "@conversation/tour_aryon:s_9b704e1e", -- The next election will start in less than a week.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_less_than_a_week);

in_more_than_a_week = ConvoScreen:new {
	id = "in_more_than_a_week",
	leftDialog = "@conversation/tour_aryon:s_3dcd5980", -- The next election won't start for well over a week.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_more_than_a_week);

in_more_than_two_weeks = ConvoScreen:new {
	id = "in_more_than_two_weeks",
	leftDialog = "@conversation/tour_aryon:s_45511d66", -- It will be more than two weeks before the next election begins.
	stopConversation = "true",
	options = {}
}
tourAryonConvoTemplate:addScreen(in_more_than_two_weeks);

addConversationTemplate("tourAryonConvoTemplate", tourAryonConvoTemplate);
