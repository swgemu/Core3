villageSarguilloPhase4ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSarguilloPhase4ConvoHandler",
	screens = {}
}

intro_has_otherquest = ConvoScreen:new {
	id = "intro_has_otherquest",
	leftDialog = "@conversation/defend_the_village:s_41ea5583", -- "As I understand it you already have some assignments from some of the other villagers.  Come back when you don't have so much on your plate."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(intro_has_otherquest);

quest_in_progress = ConvoScreen:new {
	id = "quest_in_progress",
	leftDialog = "@conversation/defend_the_village:s_c9be571d", -- "I know you've been working on that problem of ours...you know, with the mercs and the pirates? But I'm going to need you to work a little harder. Now get back out there soldier!"
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(quest_in_progress);

intro_begin = ConvoScreen:new {
	id = "intro_begin",
	leftDialog = "@conversation/defend_the_village:s_d2fe23af", -- "Easy there recruit. I have an assignment for you whenever you're ready. I can give you training after you complete this mission. Would you be more interested in learning how to fire ranged weapons more quickly, or defending yourself in melee combat?"
	stopConversation = "false",
	options = {
		-- See convo handler
		--{"@conversation/defend_the_village:s_6e8bed18", "choose_ranged"}, -- "Definitely increasing my ranged speed."
		--{"@conversation/defend_the_village:s_95fe56b2", "choose_melee"}, -- "Melee defense. No question."
		--{"@conversation/defend_the_village:s_64cad97c", "choose_neither"}, -- "I'm not ready to work right now."
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(intro_begin);

choose_neither = ConvoScreen:new {
	id = "choose_neither",
	leftDialog = "@conversation/defend_the_village:s_918a48b8", -- "Right then. Speak with me when you're ready."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(choose_neither);

choose_ranged = ConvoScreen:new {
	id = "choose_ranged",
	leftDialog = "@conversation/defend_the_village:s_cb3652f", -- "Here's what I have. Outlaws and pirates are swarming this area like Jawas over a speeder engine. The village's safety is going to rely on reducing the number of hostiles we have in this area. I'm counting on you to do that."
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_c382b2d0", "explain_quest_ranged"}, -- "You want me to take out ALL of them?!?"
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(choose_ranged);

choose_melee = ConvoScreen:new {
	id = "choose_melee",
	leftDialog = "@conversation/defend_the_village:s_cb3652f", -- "Here's what I have. Outlaws and pirates are swarming this area like Jawas over a speeder engine. The village's safety is going to rely on reducing the number of hostiles we have in this area. I'm counting on you to do that."
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_c382b2d0", "explain_quest_melee"}, -- "You want me to take out ALL of them?!?"
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(choose_melee);

explain_quest_ranged = ConvoScreen:new {
	id = "explain_quest_ranged",
	leftDialog = "@conversation/defend_the_village:s_ee72ef65", -- "No. In fact, I just want you to take out a few. Well, more than a few. Let's say 50 outlaws. I think if you can handle that, the rest of them will get the message that this isn't a safe spot for them to hang around. The pirates, well, there's less of them, so let's say 25 of the pirates. Can you handle that?"
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_a30c1a53", "accept_quest_ranged"}, -- "Yes sir!"
		{"@conversation/defend_the_village:s_ed6ed8a4", "right_person_ranged"}, -- "Sounds like a lot..."
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(explain_quest_ranged);

explain_quest_melee = ConvoScreen:new {
	id = "explain_quest_melee",
	leftDialog = "@conversation/defend_the_village:s_ee72ef65", -- "No. In fact, I just want you to take out a few. Well, more than a few. Let's say 50 outlaws. I think if you can handle that, the rest of them will get the message that this isn't a safe spot for them to hang around. The pirates, well, there's less of them, so let's say 25 of the pirates. Can you handle that?"
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_a30c1a53", "accept_quest_melee"}, -- "Yes sir!"
		{"@conversation/defend_the_village:s_ed6ed8a4", "right_person_melee"}, -- "Sounds like a lot..."
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(explain_quest_melee);

right_person_ranged = ConvoScreen:new {
	id = "right_person_ranged",
	leftDialog = "@conversation/defend_the_village:s_2647addd", -- "Maybe, but I think you're the right person for the job. Can you do it?"
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_f9a0517", "fantastic_accept_ranged"}, -- "Um...sure."
		{"@conversation/defend_the_village:s_2b2d70cd", "choose_continue_decline"}, -- "No, I think it's too much for me."
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(right_person_ranged);

right_person_melee = ConvoScreen:new {
	id = "right_person_melee",
	leftDialog = "@conversation/defend_the_village:s_2647addd", -- "Maybe, but I think you're the right person for the job. Can you do it?"
	stopConversation = "false",
	options = {
		{"@conversation/defend_the_village:s_f9a0517", "fantastic_accept_melee"}, -- "Um...sure."
		{"@conversation/defend_the_village:s_2b2d70cd", "choose_continue_decline"}, -- "No, I think it's too much for me."
	}
}
villageSarguilloPhase4ConvoTemplate:addScreen(right_person_melee);

choose_continue_decline = ConvoScreen:new {
  id = "choose_continue_decline",
  leftDialog = "@conversation/defend_the_village:s_982a066f", -- "That's too bad. I was hoping you'd be more helpful. Come back if you ever toughen up."
  stopConversation = "true",
  options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(choose_continue_decline);

fantastic_accept_ranged = ConvoScreen:new {
	id = "fantastic_accept_ranged",
	leftDialog = "@conversation/defend_the_village:s_212d92b3", -- "Fantastic!  I knew I could count on you."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(fantastic_accept_ranged);

fantastic_accept_melee = ConvoScreen:new {
	id = "fantastic_accept_melee",
	leftDialog = "@conversation/defend_the_village:s_212d92b3", -- "Fantastic!  I knew I could count on you."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(fantastic_accept_melee);

accept_quest_ranged = ConvoScreen:new {
	id = "accept_quest_ranged",
	leftDialog = "@conversation/defend_the_village:s_db99c818", -- "Good. Come back and see me while you're working on this problem and I'll let you know how things are going."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(accept_quest_ranged);

accept_quest_melee = ConvoScreen:new {
	id = "accept_quest_melee",
	leftDialog = "@conversation/defend_the_village:s_db99c818", -- "Good. Come back and see me while you're working on this problem and I'll let you know how things are going."
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase4ConvoTemplate:addScreen(accept_quest_melee);

update_back_for_more = ConvoScreen:new {
	id = "update_back_for_more",
	leftDialog = "@conversation/defend_the_village:s_1a9b1371", -- "I knew I picked the right person for this, I just knew it. The mercenaries and the pirates are cursing your name this very minute. You've almost finished what I asked you to do. All you have to do is get out there and complete this mission. Good luck, soldier!"
	stopConversation = "true",
	options = {}
}

villageSarguilloPhase4ConvoTemplate:addScreen(update_back_for_more);

update_all_done = ConvoScreen:new {
	id = "update_all_done",
	leftDialog = "@conversation/defend_the_village:s_a2665c7f", -- "I'd like to thank you for all the hard work you did. Get some rest, I'm sure at some point in the future we'll need some more help from you, but for now you've earned some R&R."
	stopConversation = "true",
	options = {}
}

villageSarguilloPhase4ConvoTemplate:addScreen(update_all_done);

addConversationTemplate("villageSarguilloPhase4ConvoTemplate", villageSarguilloPhase4ConvoTemplate);
