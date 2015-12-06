villageDageerinPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageDageerinPhase2ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_quests_sad_conv:s_b3f0b662", -- Greetings.  I am eager for your assistance.  In return, I offer to train you to use the Force to quicken you in melee.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_b84b366c", "bases_spotted"}, -- How can I help?
		{"@conversation/fs_quests_sad_conv:s_e1175f92", "always_welcome"}, -- I'm sorry -- I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro);

always_welcome = ConvoScreen:new {
	id = "always_welcome",
	leftDialog = "@conversation/fs_quests_sad_conv:s_52917b0d", -- All right -- if that is your wish.  You are always welcome here.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(always_welcome);

bases_spotted = ConvoScreen:new {
	id = "bases_spotted",
	leftDialog = "@conversation/fs_quests_sad_conv:s_bc39cbe0", -- A variety of Shadow bases have been spotted in the surrounding countryside.  We suspect they are marshalling their forces for some sort of large-scale raid unlike anything we've seen.  If they were to strike now, we would be horribly unprepared.  We must convince them that we are much stronger than we, in fact, are.  Village agents are scouring the countryside as we speak, looking for likely targets for dynamic raids.  We can use your help.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_52917b0d", "make_something_clear"}, -- Of course.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(bases_spotted);

make_something_clear = ConvoScreen:new {
	id = "make_something_clear",
	leftDialog = "@conversation/fs_quests_sad_conv:s_14c652fd", -- Now, I want to make something clear.  This mission is going to carry you out into the field as an operative for our militia.  It's going to be impossible to do anything else for our village for quite a while - possibly as much as 3 weeks.  You can back out now, but once I give you our intelligence data, you're committed.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_faedbf19", "tracking_device"}, -- No, I understand.  I'm committed.
		{"@conversation/fs_quests_sad_conv:s_8909d6f9", "always_welcome"}, -- Ok, I'm glad you told me.  I've got other things to do before I commit.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(make_something_clear);

tracking_device = ConvoScreen:new {
	id = "tracking_device",
	leftDialog = "@conversation/fs_quests_sad_conv:s_f163f1df", -- Great.  So, one of our men managed to attach a tracking device to one of the Shadow during their last confrontation, a small radioactive beacon that we can track using this radiation sensor. I'm going to give you a control device that can sit in your datapad.  Activate it to get a reading.  As the reading goes up, you're getting close to the target.  Based on the strength of the readings, the device is about 1000 meters from here. Good luck.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(tracking_device);

intro_not_eligible = ConvoScreen:new {
	id = "intro_not_eligible",
	leftDialog = "@conversation/fs_quests_sad_conv:s_a4ab4cd7", -- Greetings, stranger.  Focus on clearing your mind.  It is still cloudy.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_not_eligible);

intro_completed_other_quest = ConvoScreen:new {
	id = "intro_completed_other_quest",
	leftDialog = "@conversation/fs_quests_sad_conv:s_ad5c1b56", -- You've helped enough for now, and we thank you.  I have nothing for you right now - rest a while.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_other_quest);

intro_has_other_quest = ConvoScreen:new {
	id = "intro_has_other_quest",
	leftDialog = "@conversation/fs_quests_sad_conv:s_be2a8162", -- I thank you for helping our village.  I've heard of the good work you're doing.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_has_other_quest);

intro_completed_quest = ConvoScreen:new {
	id = "intro_completed_quest",
	leftDialog = "@conversation/fs_quests_sad_conv:s_ce50d249", -- I thank you for the services you have rendered our village.  Our home is safe because of your skill and bravery.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_quest);

intro_full_inventory = ConvoScreen:new {
	id = "intro_full_inventory",
	leftDialog = "@conversation/fs_quests_sad_conv:s_e874c8c5", -- You are so burdened - I'd like to reward you but I need you to free up space.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_full_inventory);

intro_reward = ConvoScreen:new {
	id = "intro_reward",
	leftDialog = "@conversation/fs_quests_sad_conv:s_21cb22af", -- I cannot thank you enough.  Your vigilance, speed, and bravery have undoubtedly saved many lives.  Please take this as a token of my respect -- it's been sitting in my shop far too long.  You'll find it will help you make your melee weapons faster, but extremely durable.  The whole village is in your debt.  I believe you will find that you have also learned the secret to increased melee speed through the Force.  May the Force be with you.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_reward);

intro_max_tasks_for_day = ConvoScreen:new {
	id = "intro_max_tasks_for_day",
	leftDialog = "@conversation/fs_quests_sad_conv:s_45e3060a", -- Unfortunately, the Shadow has managed to evade our patrols.  We can't find them.  It's only a matter of time before we catch up with them, though - check back tommorrow.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_max_tasks_for_day);

intro_need_new_sensor = ConvoScreen:new {
	id = "intro_need_new_sensor",
	leftDialog = "@conversation/fs_quests_sad_conv:s_86aa30ad", -- I see you've misplaced your radiation sensor.  I'm going to give you another one.  Good luck taking care of that Shadow camp.  Our people are counting on you.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_need_new_sensor);

intro_on_task = ConvoScreen:new {
	id = "intro_on_task",
	leftDialog = "@conversation/fs_quests_sad_conv:s_8903f2e3", -- Good luck taking care of that Shadow camp.  Our soldiers are counting on you.  I'm not sure if my lieutenants were able to update your datapad with a waypoint, but if not you've got your radiation sensor, right?  Good enough.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_on_task);

come_back_when_eliminated = ConvoScreen:new {
	id = "come_back_when_eliminated",
	leftDialog = "@conversation/fs_quests_sad_conv:s_71c49afd", -- Please come back when you've eliminated them -- and be careful.  My lieutenants are coordinating the attacks, so they may be able to send you waypoints if one of the patrols has found a Shadow base.  Otherwise, remember to use the radiation sensor in your datapad.
	stopConversation = "true",
	options = {}
}
villageDageerinPhase2ConvoTemplate:addScreen(come_back_when_eliminated);

intro_completed_one = ConvoScreen:new {
	id = "intro_completed_one",
	leftDialog = "@conversation/fs_quests_sad_conv:s_511b214d", -- You did us a great service with your last raid on the Shadow, but there are more out there.  Can you help us again?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_one);

intro_completed_two = ConvoScreen:new {
	id = "intro_completed_two",
	leftDialog = "@conversation/fs_quests_sad_conv:s_ceb13feb", -- I think your attacks are beginning to get their attention.  I'd watch your back.  Here's your next target, if you're up for it...
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_two);

intro_completed_three = ConvoScreen:new {
	id = "intro_completed_three",
	leftDialog = "@conversation/fs_quests_sad_conv:s_e549bc85", -- They've started moving their bases around in response to our attacks.  We've tracked them into a new area that we'd like to investigate.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_three);

intro_completed_four = ConvoScreen:new {
	id = "intro_completed_four",
	leftDialog = "@conversation/fs_quests_sad_conv:s_ae82a454", -- Unfortunately, one of our field soldiers was caught and killed.  But he managed to get us a message with the coordinates of an enemy base.  Can you avenge him for us?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_four);

intro_completed_five = ConvoScreen:new {
	id = "intro_completed_five",
	leftDialog = "@conversation/fs_quests_sad_conv:s_b1cf9ec4", -- We may have turned the corner on this thing.  It feels great to finally take the battle to our enemy instead of waiting for them to attack.  Ready for another one?
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_five);

intro_completed_six = ConvoScreen:new {
	id = "intro_completed_six",
	leftDialog = "@conversation/fs_quests_sad_conv:s_ace5dd74", -- All of the reports coming in are promising -- we definitely have them on the run now.  I think we're getting to their more elite troops -- please be careful.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_six);

intro_completed_seven = ConvoScreen:new {
	id = "intro_completed_seven",
	leftDialog = "@conversation/fs_quests_sad_conv:s_744e165e", -- Exciting news!  We've finally tracked down one of their high-ranking officers.  Our efforts have flushed him out, and our agent caught a glimpse of him just a while back.  I think...well, better not say anything.  Be careful -- a cornered rat fights hard.
	stopConversation = "false",
	options = {
		{"@conversation/fs_quests_sad_conv:s_1adbadc4", "come_back_when_eliminated"}, -- I'm ready.
		{"@conversation/fs_quests_sad_conv:s_45d6d31e", "always_welcome"}, -- I'm sorry - I can't help you right now.
	}
}
villageDageerinPhase2ConvoTemplate:addScreen(intro_completed_seven);

addConversationTemplate("villageDageerinPhase2ConvoTemplate", villageDageerinPhase2ConvoTemplate);
