ezkiel_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ezkielConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
ezkiel_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_8ea054c0", -- Please leave. This is private property.
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_no_jtl)

-- Imperial Pilot
ezkiel_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_6e50b681", -- What do you want? We're running a legal scientific expedition here.
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_imperial_pilot)

-- Neutral Pilot
ezkiel_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_b6efe97d", -- Please leave. This is private property!
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_neutral_pilot)

-- Non-Vortex Rebel Pilot (not on track)
ezkiel_convo_non_vortex_pilot = ConvoScreen:new {
	id = "non_vortex_pilot",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_14c2f902", -- You don't look like a Vortex pilot. What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_c23a0a19", "non_track_explain"}, -- Do you have any missions that I can fly?
	}
}
ezkiel_convo:addScreen(ezkiel_convo_non_vortex_pilot)

-- Non Track Explain
ezkiel_convo_non_track_explain = ConvoScreen:new {
	id = "non_track_explain",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_14c2f902", -- dynamic
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_non_track_explain)

-- Rebel Non-Member (different squadron)
ezkiel_convo_rebel_non_member = ConvoScreen:new {
	id = "rebel_non_member",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_be0843f2", -- Greetings %TU. Too bad you're already working for a different part of the Alliance Navy. We are short a few pilots at the moment.
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_rebel_non_member)

-- Negative Faction
ezkiel_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_b9e38f83", -- Woah, there, %TU. Just what do you think you're doing?
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_900f01d1", "faction_explain"}, -- What?
	}
}
ezkiel_convo:addScreen(ezkiel_convo_negative_faction)

-- Faction Explain
ezkiel_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_b9e38f83", -- dynamic
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_faction_explain)

-- Has Active Mission
ezkiel_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_d69a6474", -- What are you still doing here %TU? Time is of the essence!
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_has_mission)

-- On Another Mission
ezkiel_convo_on_another_mission = ConvoScreen:new {
	id = "on_another_mission",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_d0f52630", -- What's your name again? Oh yes, I see you on the duty roster. But it looks like you already have an assignment. Wrap that up, and then we can talk.
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_on_another_mission)

-- Ready for Tier 3 (send to Ezkiel)
ezkiel_convo_ready_for_tier3 = ConvoScreen:new {
	id = "ready_for_tier3",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_319cfac4", -- Good to see you, %NU. I've really enjoyed our time together. But now I'm placing you under the command of Brother Ezkiel. You can find him right over there. He will continue your guidance in the Vortex. Stay in touch, my friend!
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_ready_for_tier3)

-- Failed Mission 4
ezkiel_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_59d7264c", -- Quick! We have another chance to catch that officer before he reaches the Imperial fleet. Here are the new coordinates. Suit up and get going!
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_1d85385d", "retry_quest4"}, -- I can't do it. He's too heavily guarded.
		{"@conversation/dantooine_rebel_trainer_2:s_6a35a7eb", "retry_quest4"}, -- Great! I hate failure!
	}
}
ezkiel_convo:addScreen(ezkiel_convo_failed_quest4)

-- Retry Quest 4
ezkiel_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_59d7264c", -- dynamic
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_retry_quest4)

-- Won Mission 4
ezkiel_convo_excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_74e55e9e", -- We have it within our grasp, thanks to you, %NU. Outstanding job up there. Rest up and get ready for the final step. It's time to shut this Imperial operation down for good!
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_f931eb62", "training_menu"}, -- Thank you, sir. It was a close call.
		{"@conversation/dantooine_rebel_trainer_2:s_7363d4a2", "training_menu"}, -- I have to admit, I impressed even myself.
	}
}
ezkiel_convo:addScreen(ezkiel_convo_excellent_work4)

-- Ready for Mission 4
ezkiel_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_985bcff1", -- Perfect timing, %NU. We are ready for the next phase of our mission. We have finally learned what this project is all about - AND we've figured out a way to stop it.
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_1807105", "quest4_brief"}, -- Give me the short version; I'm ready for action.
		{"@conversation/dantooine_rebel_trainer_2:s_2ca477ff", "goodbye"}, -- I can't right now, Vrovel. I have things to do.
		{"@conversation/dantooine_rebel_trainer_2:s_9793aadf", "quest4_brief"}, -- Finally! What is it all about?
	}
}
ezkiel_convo:addScreen(ezkiel_convo_grant_quest4)

-- Quest 4 Brief
ezkiel_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_985bcff1", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_quest4_brief)

-- Won Mission 3
ezkiel_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_e6de2bcb", -- I understand that the smuggler arrived safely at Lok. Very well done, %NU. I'm glad we didn't have to take any extreme measures. Here's your completion bonus. Get some rest. You deserve it.
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_4d99132b", "training_menu"}, -- Thank you, sir. I'll be back shortly.
		{"@conversation/dantooine_rebel_trainer_2:s_93f5b2e2", "training_menu"}, -- Rest? Bah! I'm ready for action!
	}
}
ezkiel_convo:addScreen(ezkiel_convo_excellent_work3)

-- Failed Mission 3
ezkiel_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_e8baa9a9", -- I heard of your misfortune, %TU. I have some good news, though. The clever smuggler managed to avoid capture. He escaped in a pod. Now we will get a second chance. Are you ready %NU?
	stopConversation = "false",
	options = {
		{"@conversation/dantooine_rebel_trainer_2:s_e3516195", "retry_quest3"}, -- Excellent. Payback time!
		{"@conversation/dantooine_rebel_trainer_2:s_5d243499", "retry_quest3"}, -- I'm not going back into that death trap!
	}
}
ezkiel_convo:addScreen(ezkiel_convo_failed_quest3)

-- Retry Quest 3
ezkiel_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_e8baa9a9", -- dynamic
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_retry_quest3)

-- Training Menu (dynamic options added by handler)
ezkiel_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_319cfac4", -- dynamic
	stopConversation = "false",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_training_menu)

-- Goodbye
ezkiel_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/dantooine_rebel_trainer_2:s_8ea054c0", -- dynamic
	stopConversation = "true",
	options = {}
}
ezkiel_convo:addScreen(ezkiel_convo_goodbye)

addConversationTemplate("ezkiel_convo", ezkiel_convo)
