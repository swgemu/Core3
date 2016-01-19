villageDageerinPhase3ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageDageerinPhase3ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_ec95030", -- You look like you know your way around a weapon.  We need able bodied men to fill out our auxiliaries.  Are you prepared for the challenge?  I can teach you how to defend yourself from attacks at a distance by channelling the Force.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_b84b366c", "taking_fight_to_enemy"}, -- How can I help?
		{"@conversation/fs_quests_sad2_conv:s_e1175f92", "if_that_is_wish"}, -- I'm sorry -- I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro);

taking_fight_to_enemy = ConvoScreen:new {
	id = "taking_fight_to_enemy",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_1d03bd79", -- We're taking the fight to the enemy while we prepare our invincible shield defense.  Because of the preparations, and the scale of the conflict, our normal militia is overworked.  We're recruiting auxiliaries to be frontline combat troops.  We know the location of a number of Shadow bases that we want taken out to keep them on the run.  
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_4ae25b38", "understand_this"}, -- I would be honored to serve you and the Force.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(taking_fight_to_enemy);

understand_this = ConvoScreen:new {
	id = "understand_this",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_b39e716", -- Understand this, my friend.  This mission is going to carry you out into the field as an operative for our militia.  You're going to be too busy to help us in any other way for a while -- possibly as much as 3 weeks.  This is your chance to back out. 
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_faedbf19", "good_luck"}, -- No, I understand.  I'm committed.
		{"@conversation/fs_quests_sad2_conv:s_8909d6f9", "if_that_is_wish"}, -- Ok, I'm glad you told me.  I've got other things to do before I commit.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(understand_this);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_eabbdaa6", -- Glad to hear it.  Our militia uses a small tracking device called a radiation sensor to track the enemy out in the field. I'm going to give you a control device that can sit in your datapad.  Activate it to get a reading.  As the reading goes up, you're getting close to the target.  Based on the strength of the readings, I think the nearest Shadow base is about 1000 meters from here.  Good luck, soldier.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(good_luck);

if_that_is_wish = ConvoScreen:new {
	id = "if_that_is_wish",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_bf7dd33f", -- All right -- if that is your wish.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(if_that_is_wish);

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_e188a139", -- Greetings, stranger.  Your mind is clouded, you must clear it first.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_not_eligible);

intro_completed_other_quest = ConvoScreen:new {
	id = "intro_completed_other_quest",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_ad5c1b56", -- You've helped enough for now, and we thank you.  I have nothing for you right now - rest a while.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_other_quest);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_be2a8162", -- I thank you for helping our village.  I've heard of the good work you're doing.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_has_other_quest);

intro_completed_quest = ConvoScreen:new {
	id = "intro_completed_quest",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_ce50d249", -- I thank you for the services you have rendered our village.  Our home is safe because of your skill and bravery.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_quest);

intro_full_inventory = ConvoScreen:new {
	id = "intro_full_inventory",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_e874c8c5", -- You are so burdened - I'd like to reward you but I need you to free up space.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_full_inventory);

intro_reward = ConvoScreen:new {
	id = "intro_reward",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_47d40828", -- I cannot thank you enough.  Your vigilance, speed and bravery have undoubtedly saved many lives.  Please take this as a token of my respect - it's been sitting in my shop far too long. You'll find it makes you more nimble, better able to defend against ranged attacks.  You will also find that you've achieved an understanding of how to increase your ranged defense through the Force.  May the Force be with you.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_reward);

intro_max_tasks_for_day = ConvoScreen:new {
	id = "intro_max_tasks_for_day",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_45e3060a", -- Unfortunately, the Shadow has managed to evade our patrols.  We can't find them.  It's only a matter of time before we catch up with them, though - check back tommorrow.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_max_tasks_for_day);

intro_need_new_sensor = ConvoScreen:new {
	id = "intro_need_new_sensor",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_86aa30ad", -- I see you've misplaced your radiation sensor.  I'm going to give you another one.  Good luck taking care of that Shadow camp.  Our people are counting on you.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_need_new_sensor);

intro_on_task = ConvoScreen:new {
	id = "intro_on_task",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_1bb0236f", -- Good luck taking care of that Shadow camp.  Our soldiers are counting on you.  Follow your waypoint or use your radiation sensor if you don't have one.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_on_task);

intro_completed_one = ConvoScreen:new {
	id = "intro_completed_one",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_6649d643", -- Someone is feeding them supplies, but we don't know who.  We've located a base that's supplying a large area outside the village.  Can you track it down and destroy it for us?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_one);

intro_completed_two = ConvoScreen:new {
	id = "intro_completed_two",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_f1ccb161", -- We'll bring this Shadow out into the open if it's the last thing we do.  I'm redoubling our patrols, which places great strain on the auxiliaries.  Think you can handle it?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_two);

intro_completed_three = ConvoScreen:new {
	id = "intro_completed_three",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_f62934bc", -- TThey've started moving their bases around in response to our attacks.  With the help of the Force, I hope we can find their new camps quickly.  Can you help?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_three);

intro_completed_four = ConvoScreen:new {
	id = "intro_completed_four",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_b1cf9ec4", -- We may have turned the corner on this thing.  It feels great to finally take the battle to our enemy instead of waiting for them to attack.  Ready for another one?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_four);

intro_completed_five = ConvoScreen:new {
	id = "intro_completed_five",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_f88c54a", -- Our spies have netted us another camp.  But you'll have to act quickly.  They look like they're ready to move.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_five);

intro_completed_six = ConvoScreen:new {
	id = "intro_completed_six",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_873e5003", -- All of the reports coming in are promising -- we definitely have them on the run now.  I think we're getting to their more elite troops - please be careful.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_six);

intro_completed_seven = ConvoScreen:new {
	id = "intro_completed_seven",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_f4afc95c", -- All right, we're getting somewhere, finally.  Reports are coming in that a high-ranking officer of the Shadow is holed up nearby.  Take him out, now.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad2_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad2_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase3ConvoTemplate:addScreen(intro_completed_seven);

come_back_when_eliminated = ConvoScreen:new {
	id = "come_back_when_eliminated",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_5a1fb6b3", -- Please come back when you've eliminated them - and be careful.  If we have waypoint data, we've provided it to you, otherwise, remember to use your radiation sensor in your datapad.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(come_back_when_eliminated);

always_welcome = ConvoScreen:new {
	id = "always_welcome",
	leftDialog = "@conversation/fs_quests_sad2_conv:s_253d75eb", -- All right -- if that is your wish.  You are always welcome here.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase3ConvoTemplate:addScreen(always_welcome);

addConversationTemplate("villageDageerinPhase3ConvoTemplate", villageDageerinPhase3ConvoTemplate);