corvetteVelsoConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverVelsoConvoHandler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_cc45dddf", --I do not have time to chat, citizen. Please move along.
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_3d6658e8",--Soldier, I appreciate your enthusiasm, but I can see that you're already busy. Come back when you've finished your current task, and I'll get you back into the action.
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_477d6952",--Just in time soldier! I have an urgent mission that requires your assistance.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_757e4a85","quest_start"},-- Yes Sir, what are the details?
		{"@conversation/corvette_velso_imperial_destroy:s_823dca3f","convo_exit"} --Sorry, too busy right now.
	}
}
corvetteVelsoConvoTemplate:addScreen(convo_start);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_36c480be",--A payload of weapons is being smuggled to a group of Rebels waiting to slaughter some outnumbered Imperial... er.. I mean to slaughter some innocent civilians. Yes. They're on a Corellian corvette, but it's marked as a medical transport so we don't want to attack it directly. I need you to find the destruction sequences for the corvette and blow it up from the inside. I have three leads on where the sequences could be located.
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(quest_start);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_27825c70", -- What?! That wasn't a question! Fine, I can't let this mission be handled by someone like you anyway, get out of here!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(convo_exit);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_524ad772",--Were you not listening soldier?! If I weren't desperate I would put you on kitchen duty for a month! Now which location do I have to repeat myself about?
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_e5e44e1d",--The traitor Erran Sif is leading a small group of warriors on Talus. She betrayed the Empire in the past and is considered an enemy, so don't expect a friendly reception. I hear she's also no friend to the Rebel Alliance for whatever that's worth. Regardless, I believe she may have the codes for this corvette as she may have used it once herself. Infiltrate her base and report back with whatever you find.
	stopConversation = "false",
	options = { }
}
corvetteVelsoConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_32084dfe", --The city of Anchorhead is in southern Tatooine. Rebels are known to congregate in Anchorhead, so I feel there is a good chance the sequences we seek could be there. They might be in an abandoned building or in the back room of a cantina. I really have no idea. It is your job to uncover those sequences and return them to me.
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_b68e2c66", --The Rebels are rumored to have hidden among the Dantari on Dantooine. Specifically with a tribe called the Janta. We believe that when the Rebels evacuated the area, this ship was among those used. There may be information at the Janta Stronghold... retrieve it.
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_160e282",--Excellent, don't disappoint me soldier! Time is of the essence here. You can choose to return whenever you find something so that we can check the information as you find it. Or get them all at once, that's fine as well. Just make it quick. Dismissed!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_d521e0c0", --Tea?! Get out of here soldier, you're lucky I'm not incarcerating you! Wait... first give me 50, now!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_ce1a4a29", --Speak soldier, what are you doing here?!
	stopConversation = "false",
	options = {	}
}
corvetteVelsoConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_640dac0a", -- What?! You are a disgrace soldier! I will have your name sent to the inquisition for this! You will be relieved of all mission data and any documents you've gathered. You disgust me. Get out of my sight!
	stopConversation = "true",
	options = { }
}
corvetteVelsoConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_52d6b1d", --Show it to me.
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_29a2b68d",--Are you kidding me soldier? Can you even read? This is useless! But I'll keep it anyway, just in case...
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_988cb045", --Who let you in to the Empire soldier?! This is rubbish! No, you can't have it back!
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_9ddd4bc7", --Why are you still here?! Go, go, go!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_65cd8f5e", --Fine, let me have a look.
	stopConversation = "false",
	options = { }
}
corvetteVelsoConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_95397df3",--It sure is soldier, good work! Now take this travel authorization to the Imperial pilot out by the shuttle, and he will arrange deep space transportation for you that will intercept that corvette. If you succeed in destroying that corvette and in escaping it, return to me for a reward.
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_9e916cc9", --Yes soldier, you are a lot brighter than you look! And after doing that and successfully escaping, return to me for a reward. Now hurry, hurry, hurry!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_105e0ec6",--Why are you still here soldier?! Did you forget your weapon or are you just trying to upset me?!
	stopConversation = "false",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_5b578f0d", --What?! You are a disgrace soldier! I will have your name sent to the inquisition for this! This will mean having to revoke your travel authorization and relieving you of all mission data and any documents you've gathered. And that means paperwork. I hate paperwork. So instead, you'll stay on this mission. Now get on that shuttle!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_31c5707e","decline_quest_reset"},--I..I'm sorry Sir, I can't do it.
		{"@conversation/corvette_velso_imperial_destroy:s_b99cf73b","changed_mind"},--Okay, okay Sir. I'll do it.
	}
}
corvetteVelsoConvoTemplate:addScreen(still_here_decline);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_f0bafd8b", --You will wish our paths never crossed when I'm done with you. Now get out of my sight!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(decline_quest_reset);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_8d72ccd0", -- You better! Now get on that shuttle and do your duty soldier!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(changed_mind);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_c159261e", --You will be the death of me... take it to the pilot outside by the Lambda shuttle. If by some miracle you don't fail in this mission, return to me for a reward. Now go!
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(launch_location);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_446ba9d",--Nothing left of that corvette but space dust. I knew I could whip you into shape. That's exactly what the Empire needs... more soldiers like me. Like you? Ha. I guess you did earn a reward, though.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_velso_imperial_destroy:s_b384a269","give_reward"}, --At least you'll admit that much. Can I have my reward?
		{"@conversation/corvette_velso_imperial_destroy:s_5aca4872","reward_notyet"} --Um... I think I'll come back later.
	}
}
corvetteVelsoConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_fc34951f", --Later? You should take what you can get. Might not be a later.Guess that's when you'll be a good soldier too. Later. Or more likely never.
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_2b546273", --Here's your reward, soldier. Take it. You earned it... I won't deny that.
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_velso_imperial_destroy:s_131222b8", --Are you not aware of the fact that you cannot carry anything else? What kind of soldier are you? You must be aware of these things at all times. Otherwise the Alliance will kill you in your sleep. Don't return until you've made some room to carry this reward.
	stopConversation = "true",
	options = {}
}
corvetteVelsoConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteVelsoConvoTemplate", corvetteVelsoConvoTemplate);

