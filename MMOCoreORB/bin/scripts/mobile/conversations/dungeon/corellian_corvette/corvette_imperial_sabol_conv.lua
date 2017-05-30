corvetteSabolConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverSabolConvoHandler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_69693bca", --Must you interrupt me? I cannot make time for those unwilling to declare allegiance to the Empire. Please leave me be until your loyalties become clearer.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_74947555", --Typical... I actually need some assistance, and they send me someone who can't help me. You're already busy. What was the point. Come back when you've finished your current task and maybe, assuming it's not too late, you could still be of use.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_145e07df", --Idiots! Complete and utter idiots! How can I complete my tasks when my commanding officers are nothing but fools! I... Excuse me. I didn't see you standing there. Well... what do you want? I'm very busy as you can see.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_3098b584	","convo_start_2"}, --You said something about tasks.
		{"@conversation/corvette_sabol_imperial1:s_4c16d4f","convo_exit"} --Ah, nothing. My apologies for disturbing you.
	}
}
corvetteSabolConvoTemplate:addScreen(convo_start);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_229f193e", -- Indeed. And please do not make a habit of doing so. I have responsibilities to the Empire that must not be delayed.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(convo_exit);

convo_start_2 = ConvoScreen:new {
	id = "convo_start_2",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_1e7ac1df", --So? Are you looking for work? Are you that desperate? I suppose I might be thankful but, as a lieutenant of the Empire, I am more suspicious than grateful. Oh fine! I'll tell you but only because I need someone to help me with some... field work. Do you wish to hear me out?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_683de974	","convo_start_3"}, --Yes, I'll hear your story.
		{"@conversation/corvette_sabol_imperial1:s_d143f357","convo_exit_2"} --No thanks. I'm going now. Good-bye.
	}
}
corvetteSabolConvoTemplate:addScreen(convo_start_2);

convo_exit_2 = ConvoScreen:new {
	id = "convo_exit_2",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_fdcee9b7", --The standard for those allowed into our Imperial ranks has obviously declined. Greatly. I regret the day someone like you was called to server. Leave now.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(convo_exit_2);

convo_start_3 = ConvoScreen:new {
	id = "convo_start_3",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_f7d97fec", --My superiors have instructed me to eliminate a high-ranking Rebel officer. To do so, I must find an important document belonging to the Rebel Alliance that tells me where to find this officer. As an Imperial lieutenant, I will not participate in such menial tasks. But I am also a woman of great ambition, so I'll not ignore such orders. Instead I prefer to find others who will do my bidding. Are you interested in the task? Mind you, I will not tolerate failure.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_1f9dab05	","convo_start_4"}, --I'll gladly help eliminate a Rebel officer. Where can I find this document?
		{"@conversation/corvette_sabol_imperial1:s_df8ea53","convo_exit_3"} --Not interested.
	}
}
corvetteSabolConvoTemplate:addScreen(convo_start_3);

convo_exit_3 = ConvoScreen:new {
	id = "convo_exit_3",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_1dcd7b46", -- Disgusting peon. Breathing your air makes my intelligence dwindle into nothingness. Be gone!
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(convo_exit_3);

convo_start_4 = ConvoScreen:new {
	id = "convo_start_4",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_963fc82f", --I have some data on where this document might be found. Let me check my datapad. Hmm... Only three locations. Unfortunately I have nothing that gives us a hint about which might be the one with the document we seek. It could be at any of these places. Are you still interested in assisting me?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_b9bb7669	","quest_start"}, --Yes, of course. I'll check all three if need be.
		{"@conversation/corvette_sabol_imperial1:s_a11b6dbf","convo_exit_4"} --No, that would be a little too hard.
	}
}
corvetteSabolConvoTemplate:addScreen(convo_start_4);

convo_exit_4 = ConvoScreen:new {
	id = "convo_exit_4",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_f60e408a", -- I see now that you are a coward. Such a pity.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(convo_exit_4);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_3e470c42", --Excellent. The document we seek can be found at any one of these locations: at the Rebel base on Dantooine, in the Afarathu cave on Corellia, and on a cruise liner... the Star Tours Tzarina.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(quest_start);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_29dd35da", -- Ugh! This is turning out to be a disaster. About which location do you need more information?
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_b687be9",--An old Rebel base can be found in the northwest corner of Dantooine. It was supposedly abandoned when the traitors making up the Rebel Alliance opted for a new and, one would assume, better base of operations. My belief is that there are still Rebels making use of the base. Maybe not many, but some. Look there for the information we need.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_ba8810ed", --We have reports that in the recent past some Rebels were fighting warriors from the Afarathu Sect on Corellia. Further intelligence hinted that the Afarathu made off with some important Rebel documents... possibly including the one we need. The Afarathu are slime though. You won't be able to enter their cave without a fight. Regardless, search it well and find the document.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_c23e3bbe", --The Star Tours Tzarina was a cruise liner. It was struck by an unidentified object while in flight and crashed on Dathomir. Word is that a Rebel spy was on this cruise liner and among his cargo could be the document we seek. You'll have to search for it among the wreckage of the starship. Try the northwestern area of Dathomir. It might be difficult to find, but then this mission isn't for the faint of heart. Find it.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_7fdf3bed", --Good. I am satisfied to know you are not a coward and are willing to risk your life for the greater good of the Empire. Now, leave.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_6289b734", --Leave here before you anger me further. Do not waste my time again!
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_214dc2b7", --I see that you've returned. I do not tolerate failure. Please tell me you've succeeded. I do not wish to terminate another Imperial soldier this day. Did you find my documents?
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_1bb4597", --I will gladly clear the records of your progress and confiscate all documents pertaining to this mission. I will also immediately report this to my superiors. Run, run far away or I will have my troopers arrest you for treason.
	stopConversation = "true",
	options = { }
}
corvetteSabolConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_e139d89b", --The only document I'm interested in is the one I commanded you to find! Now where is it?! Fine--I'll humor you. What did you find on your travels?
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_63bcc509", --No, no, no! This is not the right document! Damn those Rebels! I will record your findings in case I can use this data in future operations, and I suppose a small reward is in order. But find the information we need!
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_63bcc509", --No, no, no! This is not the right document! Damn those Rebels! I will record your findings in case I can use this data in future operations, and I suppose a small reward is in order. But find the information we need!
	stopConversation = "false",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_424889c8", --Yes and you're wasting my time just standing there. Find those documents!
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_a33382c5", --Let me see them.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_60956d9a", --Perfect! This is the correct document. It provides information location of the high-ranking Rebel officer that the Empire wants assassinated. And for once, I agree... all Rebel officers should be put to death. Here, take this. It authorizes you for transportation that will intercept your target on the corvette. Go to the Emperor's private retreat on Naboo and speak to the shuttle pilot there. If you succeed in eliminating that officer, return to me for a reward. Go now.
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_9caa2380", --And what is keeping you? Go away. I have other important tasks to complete. Go to the Emperor's private retreat on Naboo and speak to the shuttle pilot there. If you somehow manage to succeed in this mission, return to me for your reward. Now go. Hurry.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_eeb7ec64", --You're back?
	stopConversation = "false",
	options = {	}
}
corvetteSabolConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_4142af45", --Oh? You realize if you quit I must eradicate all records of your progress, confiscate all remaining mission documents, and revoke the travel authorization. You do realize that, correct?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_c8e527a1","decline_quest_reset"}, --That's fine. I still want to quit.
		{"@conversation/corvette_sabol_imperial1:s_c36f888","changed_mind"}, --Oh. Nevermind. I'll continue.
	}
}
corvetteSabolConvoTemplate:addScreen(still_here_decline);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_e24b66e7", --I was tired of seeing your face, anyway. I will find someone else who possesses more direction in life.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(decline_quest_reset);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_a7150449", --That's what I thought.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(changed_mind);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_550eac58", -- It is not that hard to understand. You need to travel to the Emperor's Retreat and contact the shuttle pilot there. He will then provide you transportation on a starship that will intercept the Alliance Corellian corvette in flight. If you somehow manage to succeed in this mission, return to me for your reward. Now go.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(launch_location);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_afa2913f", -- You've actually succeeded? Unprecedented. This will truly make me look good. What's that? Oh, yes I suppose it makes you look good as well. Maybe a little anyway. I imagine you want your reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_sabol_imperial1:s_6f43c8f7","give_reward"}, --That's right, I do.
		{"@conversation/corvette_sabol_imperial1:s_be293abc","reward_notyet"} -- No, not yet. I'll return.
	}
}
corvetteSabolConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_1accfb99", --Whatever. Makes no difference to me. Just let me know when you're ready.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_ed80aff5", --Take it. I'll... um... I'll be sure my commanders know your part in this. Don't you worry about that. Now go away.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_sabol_imperial1:s_759b9766", -- As much as I'd like to conclude our business, I'm afraid I cannot. You do not have room to carry this reward. Make room and then speak with me again.
	stopConversation = "true",
	options = {}
}
corvetteSabolConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteSabolConvoTemplate", corvetteSabolConvoTemplate);

