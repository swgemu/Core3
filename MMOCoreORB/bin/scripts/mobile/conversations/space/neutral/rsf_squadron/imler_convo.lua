imler_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imlerConvoHandler",
	screens = {}
}

pilot_not_rsf = ConvoScreen:new {
	id = "pilot_not_rsf",
	leftDialog = "@conversation/naboo_privateer_tier4:s_aa1834ec", -- I don't think I've seen you before. Maybe you took a wrong turn somewhere.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(pilot_not_rsf);

not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/naboo_privateer_tier4:s_35a5b893", -- Won't find any here. See ya.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(not_pilot);

not_proper_tier = ConvoScreen:new {
	id = "not_proper_tier",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9686f892", -- Tsk. Better get back to Commander Delios. He hates it when people don't finish what they started.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(not_proper_tier);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_67b2bdc1", -- Hurry up. It's time to get back to work.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(on_mission);

--[[
	Training Screens
]]

ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/naboo_privateer_tier4:s_24231574", -- That's a nice attitude for a pilot to have. Actually, I do have some duty missions to assign.
	stopConversation = "false",
	options = {}
}
imler_convo_template:addScreen(ready_train_pilot);

initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/naboo_privateer_tier4:s_42d6c3ee", -- Go on. Your ship is waiting.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(initial_train_fighters);

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/naboo_privateer_tier4:s_42d6c3ee", -- Go on. Your ship is waiting.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(initial_train_components);

initial_train_techniques = ConvoScreen:new {
	id = "initial_train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier4:s_42d6c3ee", -- Go on. Your ship is waiting.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(initial_train_techniques);

initial_train_algorithms = ConvoScreen:new {
	id = "initial_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_tier4:s_42d6c3ee", -- Go on. Your ship is waiting.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(initial_train_algorithms);

mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/naboo_privateer_tier4:s_41799e3b", -- You did good. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission2_train_fighters);

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/naboo_privateer_tier4:s_41799e3b", -- You did good. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission2_train_components);

mission2_train_techniques = ConvoScreen:new {
	id = "mission2_train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier4:s_41799e3b", -- You did good. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission2_train_techniques);

mission2_train_algorithms = ConvoScreen:new {
	id = "mission2_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_tier4:s_41799e3b", -- You did good. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission2_train_algorithms);

mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/naboo_privateer_tier4:s_720204b2", -- Let me worry about the Black Suns. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission3_train_fighters);

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/naboo_privateer_tier4:s_720204b2", -- Let me worry about the Black Suns. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission3_train_components);

mission3_train_techniques = ConvoScreen:new {
	id = "mission3_train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier4:s_720204b2", -- Let me worry about the Black Suns. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission3_train_techniques);

mission3_train_algorithms = ConvoScreen:new {
	id = "mission3_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_tier4:s_720204b2", -- Let me worry about the Black Suns. I have a new mission for you.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission3_train_algorithms);

mission4_train_fighters = ConvoScreen:new {
	id = "mission4_train_fighters",
	leftDialog = "@conversation/naboo_privateer_tier4:s_76701ff2", -- You're about to get your wish. But this time, you're not going alone.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission4_train_fighters);

mission4_train_components = ConvoScreen:new {
	id = "mission4_train_components",
	leftDialog = "@conversation/naboo_privateer_tier4:s_76701ff2", -- You're about to get your wish. But this time, you're not going alone.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission4_train_components);

mission4_train_techniques = ConvoScreen:new {
	id = "mission4_train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier4:s_76701ff2", -- You're about to get your wish. But this time, you're not going alone.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission4_train_techniques);

mission4_train_algorithms = ConvoScreen:new {
	id = "mission4_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_tier4:s_76701ff2", -- You're about to get your wish. But this time, you're not going alone.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(mission4_train_algorithms);

final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/naboo_privateer_tier4:s_92fa7352", -- I have just been informed that Grand Admiral Nial Declann has ordered that you be transferred...
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(final_train_fighters);

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/naboo_privateer_tier4:s_92fa7352", -- I have just been informed that Grand Admiral Nial Declann has ordered that you be transferred...
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(final_train_components);

final_train_techniques = ConvoScreen:new {
	id = "final_train_techniques",
	leftDialog = "@conversation/naboo_privateer_tier4:s_92fa7352", -- I have just been informed that Grand Admiral Nial Declann has ordered that you be transferred...
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(final_train_techniques);

final_train_algorithms = ConvoScreen:new {
	id = "final_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_tier4:s_92fa7352", -- I have just been informed that Grand Admiral Nial Declann has ordered that you be transferred...
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(final_train_algorithms);

--[[
	Initial Briefing
]]

initial_briefing = ConvoScreen:new {
	id = "initial_briefing",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9312a850", -- So. How was life with Commander Delios?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_68441a06", "action_packed"}, -- Action packed.
		{"@conversation/naboo_privateer_tier4:s_a404eb10", "done_with_him"}, -- I'm done with him!
	}
}
imler_convo_template:addScreen(initial_briefing);

action_packed = ConvoScreen:new {
	id = "action_packed",
	leftDialog = "@conversation/naboo_privateer_tier4:s_3d333deb", -- Well, you'll get more of the same here, if you're lucky. Are you a good pilot?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_2271ff14", "judge_of_that"}, -- I think so. But you can be the judge of that.
		{"@conversation/naboo_privateer_tier4:s_55dae7d2", "for_the_money"}, -- Not by a long shot. And yes, I AM doing it for the money.
	}
}
imler_convo_template:addScreen(action_packed);

done_with_him = ConvoScreen:new {
	id = "done_with_him",
	leftDialog = "@conversation/naboo_privateer_tier4:s_25cf4e47", -- I don't think he's done with YOU, though.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_1f2b0388", "not_any_more"}, -- Not any more.
	}
}
imler_convo_template:addScreen(done_with_him);

not_any_more = ConvoScreen:new {
	id = "not_any_more",
	leftDialog = "@conversation/naboo_privateer_tier4:s_3d333deb", -- Well, you'll get more of the same here, if you're lucky. Are you a good pilot?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_2271ff14", "judge_of_that"}, -- I think so. But you can be the judge of that.
		{"@conversation/naboo_privateer_tier4:s_55dae7d2", "for_the_money"}, -- Not by a long shot. And yes, I AM doing it for the money.
	}
}
imler_convo_template:addScreen(not_any_more);

judge_of_that = ConvoScreen:new {
	id = "judge_of_that",
	leftDialog = "@conversation/naboo_privateer_tier4:s_ab0e62", -- Mm! Good answer, %TU. I should warn you, though. I don't like telling people what I'm thinking.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_85a73c8b", "first_mission"}, -- So do you have a mission for me?
	}
}
imler_convo_template:addScreen(judge_of_that);

for_the_money = ConvoScreen:new {
	id = "for_the_money",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9192ecb", -- Don't be. I'm being sarcastic.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_85a73c8b", "first_mission"}, -- So do you have a mission for me?
	}
}
imler_convo_template:addScreen(for_the_money);

--[[
	Mission 1: Escort RSF Scanner (Endor)
]]

first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_a82676b8", -- Royal Security Forces are using a deep space scan vessel in Endor space.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_25f8ac14", "whats_it_carrying"}, -- What's it carrying?
		{"@conversation/naboo_privateer_tier4:s_9525d65c", "blacksun_up_to"}, -- Any idea what the Black Suns are up to?
	}
}
imler_convo_template:addScreen(first_mission);

whats_it_carrying = ConvoScreen:new {
	id = "whats_it_carrying",
	leftDialog = "@conversation/naboo_privateer_tier4:s_b47b0542", -- I don't know, and right now, I don't care. The only thing that matters right now is that deep space scan. It's an expensive piece of equipment. We'd hate to lose it.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_63e5cad0", "accept_first_mission"}, -- Send me out there.
	}
}
imler_convo_template:addScreen(whats_it_carrying);

blacksun_up_to = ConvoScreen:new {
	id = "blacksun_up_to",
	leftDialog = "@conversation/naboo_privateer_tier4:s_7cc97d1a", -- Well, apparently there are some Black Suns in the area, and they'd prefer to keep their activities private. So they're launching an attack against our vessel.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_63e5cad0", "accept_first_mission"}, -- Send me out there.
	}
}
imler_convo_template:addScreen(blacksun_up_to);

accept_first_mission = ConvoScreen:new {
	id = "accept_first_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_90422eb5", -- Good luck.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_first_mission);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_2035fbe6", -- You're lucky you made it back in one piece.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_c17d2691", "accept_first_mission"}, -- I can do it.
	}
}
imler_convo_template:addScreen(failed_first_mission);

first_mission_success = ConvoScreen:new {
	id = "first_mission_success",
	leftDialog = "@conversation/naboo_privateer_tier4:s_bdc28bb4", -- You did a nice job protecting that scan vessel. We took a look at the tapes.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8289ab5b", "ready_train_pilot"}, -- I'm ready for my next mission.
	}
}
imler_convo_template:addScreen(first_mission_success);

--[[
	Mission 2: Inspect Freighter (Endor)
]]

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9145ef83", -- Listen. There's a heavy mining freighter passing through Endor space.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_79387096", "inspect_mission"}, -- An inspect mission?
		{"@conversation/naboo_privateer_tier4:s_89aa28bd", "any_idea_looking_for"}, -- Any idea what I should be looking for?
	}
}
imler_convo_template:addScreen(second_mission);

inspect_mission = ConvoScreen:new {
	id = "inspect_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_4d02fd15", -- That's what they SAY they're carrying. But I'm not so sure. I'd like you to take a closer look.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8462774c", "accept_second_mission"}, -- So I should inspect the ship.
	}
}
imler_convo_template:addScreen(inspect_mission);

any_idea_looking_for = ConvoScreen:new {
	id = "any_idea_looking_for",
	leftDialog = "@conversation/naboo_privateer_tier4:s_aa07a17b", -- Spice? Sliced weapons? Who knows. Anything's possible. And I mean ANYTHING. So keep your eyes open and your blasters primed.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8462774c", "accept_second_mission"}, -- So I should inspect the ship.
	}
}
imler_convo_template:addScreen(any_idea_looking_for);

accept_second_mission = ConvoScreen:new {
	id = "accept_second_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_87246f3e", -- You got it. Go check it out. And I don't mean one quick pass, either. Take a GOOD look.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_second_mission);

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_b59b9d3e", -- Well THAT didn't go as planned.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8bbbb2ce", "accept_second_mission"}, -- Things don't always go as planned.
	}
}
imler_convo_template:addScreen(failed_second_mission);

second_mission_success = ConvoScreen:new {
	id = "second_mission_success",
	leftDialog = "@conversation/naboo_privateer_tier4:s_39500c68", -- What did you find?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_27e6d728", "they_were_packed"}, -- You were right. They were packed to the gills with contraband.
	}
}
imler_convo_template:addScreen(second_mission_success);

they_were_packed = ConvoScreen:new {
	id = "they_were_packed",
	leftDialog = "@conversation/naboo_privateer_tier4:s_840f4ebe", -- What can I say? I've got a nose for these kinds of things.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8289ab5b", "ready_train_pilot"}, -- I'm ready for my next mission.
	}
}
imler_convo_template:addScreen(they_were_packed);

--[[
	Mission 3: Deliver Imperial Goods (Yavin)
]]

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_b5ee61ed", -- A pair of Imperial freighters have entered Yavin space. They need a go-between for a supply transfer. And that go-between would be you.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_95fbf5d7", "relationship_imperials"}, -- Our relationship with the Imperials is an important one.
		{"@conversation/naboo_privateer_tier4:s_bbd611b4", "what_about_imperials"}, -- What about the Imperials?
	}
}
imler_convo_template:addScreen(third_mission);

relationship_imperials = ConvoScreen:new {
	id = "relationship_imperials",
	leftDialog = "@conversation/naboo_privateer_tier4:s_7378bc13", -- You know how testy Imperial freighter captains can be. They think they own the universe.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_c4fcfcf7", "accept_third_mission"}, -- I guess I should just...go and do it, then.
	}
}
imler_convo_template:addScreen(relationship_imperials);

what_about_imperials = ConvoScreen:new {
	id = "what_about_imperials",
	leftDialog = "@conversation/naboo_privateer_tier4:s_48621561", -- What about them? Look, they don't bother us, we don't bother them.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_c4fcfcf7", "accept_third_mission"}, -- I guess I should just...go and do it, then.
	}
}
imler_convo_template:addScreen(what_about_imperials);

accept_third_mission = ConvoScreen:new {
	id = "accept_third_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_8a0c5ce7", -- I'll talk to you when you get back.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_third_mission);

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_c93f357b", -- I thought you said you were a good pilot.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_5e1ad1a2", "accept_third_mission"}, -- I am. I'm just having a bad day.
	}
}
imler_convo_template:addScreen(failed_third_mission);

third_mission_success = ConvoScreen:new {
	id = "third_mission_success",
	leftDialog = "@conversation/naboo_privateer_tier4:s_8180cd8a", -- So. You did it.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_9121b74a", "it_was_easy"}, -- It was easy.
	}
}
imler_convo_template:addScreen(third_mission_success);

it_was_easy = ConvoScreen:new {
	id = "it_was_easy",
	leftDialog = "@conversation/naboo_privateer_tier4:s_76cd7167", -- No. I'm not. Although...I'll admit that I didn't think you'd pull it off.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8289ab5b", "ready_train_pilot"}, -- I'm ready for my next mission.
	}
}
imler_convo_template:addScreen(it_was_easy);

--[[
	Mission 4: Assist RSF Forces (Yavin)
]]

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_1cf9a0f6", -- I've saved the best for last. I need a pilot willing to fly sorties against Black Sun pirates. Dangerous, but fun. Especially for a big strong pilot like you.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_62c8be58", "handle_blacksuns"}, -- I can handle those Black Suns.
		{"@conversation/naboo_privateer_tier4:s_9299cabe", "whats_going_on_blacksuns"}, -- What's going on with the Black Suns?
	}
}
imler_convo_template:addScreen(fourth_mission);

handle_blacksuns = ConvoScreen:new {
	id = "handle_blacksuns",
	leftDialog = "@conversation/naboo_privateer_tier4:s_221582e4", -- Oh, you can, can you? I guess we'll see. Bye bye.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_1adbadc4", "accept_fourth_mission"}, -- I'm ready.
	}
}
imler_convo_template:addScreen(handle_blacksuns);

whats_going_on_blacksuns = ConvoScreen:new {
	id = "whats_going_on_blacksuns",
	leftDialog = "@conversation/naboo_privateer_tier4:s_16106529", -- Well, this is a new problem in Yavin. We'll just have to deal with it. I'm not going to wait for them to come to us.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_1adbadc4", "accept_fourth_mission"}, -- I'm ready.
	}
}
imler_convo_template:addScreen(whats_going_on_blacksuns);

accept_fourth_mission = ConvoScreen:new {
	id = "accept_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9281abbb", -- Go get 'em, tiger.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_fourth_mission);

failed_fourth_mission = ConvoScreen:new {
	id = "failed_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_87f301d7", -- Really? Because it looks pretty easy. Maybe you could give it another shot. Please?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_8fe73508", "accept_fourth_mission"}, -- Nobody replaces me.
	}
}
imler_convo_template:addScreen(failed_fourth_mission);

fourth_mission_success = ConvoScreen:new {
	id = "fourth_mission_success",
	leftDialog = "@conversation/naboo_privateer_tier4:s_96b5ddf3", -- Some firefight.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_3c9a53fb", "ready_train_pilot"}, -- I've noticed.
	}
}
imler_convo_template:addScreen(fourth_mission_success);

--[[
	Master Mission and Completion
]]

master_mission = ConvoScreen:new {
	id = "master_mission",
	leftDialog = "@conversation/naboo_privateer_tier4:s_92fa7352", -- I have just been informed that Grand Admiral Nial Declann has ordered that you be transferred to his squadron, effective immediately. This is a very rare honor!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_57f232d6", "become_imperial"}, -- I am going to become an Imperial?
		{"@conversation/naboo_privateer_tier4:s_7177c3f2", "who_is_declann"}, -- Who is Grand Admiral Nial Declann?
	}
}
imler_convo_template:addScreen(master_mission);

become_imperial = ConvoScreen:new {
	id = "become_imperial",
	leftDialog = "@conversation/naboo_privateer_tier4:s_5d72fdfa", -- Well, not officially. But this is a big opportunity for you. You will be working under them until they no longer are in need of your services.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(become_imperial);

who_is_declann = ConvoScreen:new {
	id = "who_is_declann",
	leftDialog = "@conversation/naboo_privateer_tier4:s_75f5450f", -- That's classified, my dear. You can ask the Grand Admiral yourself. Now let me give you some free advice.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(who_is_declann);

--[[
	Duty Missions and Work
]]

here_for_work = ConvoScreen:new {
	id = "here_for_work",
	leftDialog = "@conversation/naboo_privateer_tier4:s_3f76a413", -- I like it when my pilots stay busy. Why don't you volunteer for something? Or I can give you the briefing again, if you like.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_c82e9a2f", "duty_briefing"}, -- Yes, please.
		{"@conversation/naboo_privateer_tier4:s_953c410e", "bye_cantina"}, -- Are you kidding? I'm going to the cantina.
	}
}
imler_convo_template:addScreen(here_for_work);

duty_briefing = ConvoScreen:new {
	id = "duty_briefing",
	leftDialog = "@conversation/naboo_privateer_tier4:s_5603b2a1", -- Now listen up and pay attention. I hate repeating myself. I need a pilot to escort a Naboo mining transport through Endor space.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_tier4:s_619658af", "accept_duty2"}, -- I'll escort that mining transport.
		{"@conversation/naboo_privateer_tier4:s_413ac49a", "accept_duty3"}, -- I want to help that mining craft.
		{"@conversation/naboo_privateer_tier4:s_62c8be58", "accept_duty1"}, -- I can handle those Black Suns.
		{"@conversation/naboo_privateer_tier4:s_7869de8a", "accept_duty4"}, -- What's wrong with that Ay'Nat ship?
	}
}
imler_convo_template:addScreen(duty_briefing);

accept_duty1 = ConvoScreen:new {
	id = "accept_duty1",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9281abbb", -- Go get 'em, tiger.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_duty1);

accept_duty2 = ConvoScreen:new {
	id = "accept_duty2",
	leftDialog = "@conversation/naboo_privateer_tier4:s_9750cd6f", -- Lucky miners! Have fun.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_duty2);

accept_duty3 = ConvoScreen:new {
	id = "accept_duty3",
	leftDialog = "@conversation/naboo_privateer_tier4:s_552b15d", -- Right now, the only problem is that it's not here, in my custody. But you could solve that problem. Get going.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_duty3);

accept_duty4 = ConvoScreen:new {
	id = "accept_duty4",
	leftDialog = "@conversation/naboo_privateer_tier4:s_8ca0b65b", -- If you have a thing against the Ay'Nat, you could help me out by capturing one of their private vessels.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(accept_duty4);

bye_cantina = ConvoScreen:new {
	id = "bye_cantina",
	leftDialog = "@conversation/naboo_privateer_tier4:s_27cad067", -- Don't think I can help you there.
	stopConversation = "true",
	options = {}
}
imler_convo_template:addScreen(bye_cantina);

addConversationTemplate("imler_convo_template", imler_convo_template);
