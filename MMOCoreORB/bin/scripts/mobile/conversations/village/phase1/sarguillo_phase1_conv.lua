villageSarguilloPhase1ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "villageSarguilloPhase1ConvoHandler",
	screens = {}
}

intro_hasotherquest = ConvoScreen:new {
	id = "intro_hasotherquest",
	leftDialog = "@conversation/fs_patrol_quest_start:s_37871f01", -- As I understand it you already have some assignments from some of the other villagers.  Come back when you don't have so much on your plate.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_hasotherquest);

intro_noteligible = ConvoScreen:new {
	id = "intro_noteligible",
	leftDialog = "@conversation/fs_patrol_quest_start:s_ebd8c749", -- I wish I could talk to you right now, but I just don't have the time.  Come see me later, though, I may have something for you then.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_noteligible);

intro_didallpatrols = ConvoScreen:new {
	id = "intro_didallpatrols",
	leftDialog = "@conversation/fs_patrol_quest_start:s_5f2a0dac", -- You've been a lot of help to me, but our patrols are filled.  We don't need the help just yet.  Use this time for some R&R, or maybe see if someone else needs some help.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_didallpatrols);

intro_completedfirstset = ConvoScreen:new {
	id = "intro_completedfirstset",
	leftDialog = "@conversation/fs_patrol_quest_start:s_7d744b43", -- I hear your patrols are top of the line.  Good to have someone like you around.  I guess you're starting to get a sense of how powerful you really are.  Keep up the good work.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_completedfirstset);

intro_completedsecondset = ConvoScreen:new {
	id = "intro_completedsecondset",
	leftDialog = "@conversation/fs_patrol_quest_start:s_13f339fe", -- Your information gathering is first rate.  We should be able to start rebuilding.  I have something for you, it's not much, but it's what I've got.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_completedsecondset);

intro_secondsetinprogress = ConvoScreen:new {
	id = "intro_secondsetinprogress",
	leftDialog = "@conversation/fs_patrol_quest_start:s_4b5df4f5", -- Are you back already?  You finish that last patrol?
	stopConversation = "false",
	options = {
		--{"@conversation/fs_patrol_quest_start:s_b6101821", "get_to_it or data_is_incomplete"}, -- Yes.
		--{"@conversation/fs_patrol_quest_start:s_b6101821", "are_you_sure"}, -- No, I need to restart the patrol.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_secondsetinprogress);

get_to_it = ConvoScreen:new {
	id = "get_to_it",
	leftDialog = "@conversation/fs_patrol_quest_start:s_1f1e059", -- Ok, then here's another one for you.  Get to it soldier.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(get_to_it);

data_is_incomplete = ConvoScreen:new {
	id = "data_is_incomplete",
	leftDialog = "@conversation/fs_patrol_quest_start:s_67427da4", -- Actually, it doesn't look like you did.  Your data is incomplete.  I'm gonna have to ask you to start over.  And soldier?  Do it right this time.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(data_is_incomplete);

intro_firstsetinprogress = ConvoScreen:new {
	id = "intro_firstsetinprogress",
	leftDialog = "@conversation/fs_patrol_quest_start:s_9e38953b", -- Did you finish that patrol?  I see you're back, but I don't think that necessarily means you finished...
	stopConversation = "false",
	options = {
		--{"@conversation/fs_patrol_quest_start:s_6d3ed33b", "worried_about_performance or you_know_routine"}, -- Yes, and I'm ready for more.
		--{"@conversation/fs_patrol_quest_start:s_d33566f3", "are_you_sure"}, -- No, I need to restart the patrol.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_firstsetinprogress);

worried_about_performance = ConvoScreen:new {
	id = "worried_about_performance",
	leftDialog = "@conversation/fs_patrol_quest_start:s_491ce1ad", -- I'm starting to worry about your performance soldier.  This data isn't complete.  Get back out there and start over, I don't have time for incomplete reports.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(worried_about_performance);

you_know_routine = ConvoScreen:new {
	id = "you_know_routine",
	leftDialog = "@conversation/fs_patrol_quest_start:s_1b5216d5", -- Perfect.  We can put this information to some good use.  Ok, here's your next patrol route.  You know the routine.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(you_know_routine);

are_you_sure = ConvoScreen:new {
	id = "are_you_sure",
	leftDialog = "@conversation/fs_patrol_quest_start:s_cbbe47bb", -- Are you sure you want to start over?
	stopConversation = "false",
	options = {
		{"@conversation/fs_patrol_quest_start:s_d70dba34", "need_data_asap"}, -- Yes.
		{"@conversation/fs_patrol_quest_start:s_4c695dbd", "get_job_done"}, -- No.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(are_you_sure);

need_data_asap = ConvoScreen:new {
	id = "need_data_asap",
	leftDialog = "@conversation/fs_patrol_quest_start:s_649f5207", -- I need the recon data ASAP.  I don't have time to wait, and neither do you.  Get back to work.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(need_data_asap);

get_job_done = ConvoScreen:new {
	id = "get_job_done",
	leftDialog = "@conversation/fs_patrol_quest_start:s_30c694db", -- Well then, get out there and get the job done, soldier!
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(get_job_done);

intro_startsecondset = ConvoScreen:new {
	id = "intro_startsecondset",
	leftDialog = "@conversation/fs_patrol_quest_start:s_fb116507", -- I need more help on the patrol routes.  You're proving to be quite valuable to this little operation.  Are you up for some more?
	stopConversation = "false",
	options = {
		{"@conversation/fs_patrol_quest_start:s_ec2d9d88", "you_know_the_drill"}, -- Whatever I can do to help!
		{"@conversation/fs_patrol_quest_start:s_60a74f25", "sorry_to_hear_that"}, -- No thanks, Once was enough.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro_startsecondset);

you_know_the_drill = ConvoScreen:new {
	id = "you_know_the_drill",
	leftDialog = "@conversation/fs_patrol_quest_start:s_2872b835", -- Good. Ok, you know the drill.  Here's the next route.  Let's get it going.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(you_know_the_drill);

sorry_to_hear_that = ConvoScreen:new {
	id = "sorry_to_hear_that",
	leftDialog = "@conversation/fs_patrol_quest_start:s_1485495", -- Sorry to hear that.  Let me know if you change your mind.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(sorry_to_hear_that);

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_patrol_quest_start:s_b76cc5ed", -- How are you, soldier?  I understand you're looking for something to do?  Great.  I have some patrol routes I need covered.  You interested?
	stopConversation = "false",
	options = {
		{"@conversation/fs_patrol_quest_start:s_240c8c9d", "heres_the_drill"}, -- Yes, I'm interested.
		{"@conversation/fs_patrol_quest_start:s_d6695e83", "if_change_mind"}, -- No thanks.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(intro);

if_change_mind = ConvoScreen:new {
	id = "if_change_mind",
	leftDialog = "@conversation/fs_patrol_quest_start:s_fa12949a", -- Ok, but I'm gonna need to find someone to do these patrol routes.  I need to make sure the village isn't in any immediate danger.  Come back if you change your mind, I could use someone like you.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(if_change_mind);

heres_the_drill = ConvoScreen:new {
	id = "heres_the_drill",
	leftDialog = "@conversation/fs_patrol_quest_start:s_2248d7ad", -- All right, but here's the drill.  Once you start working for me, I can't have you taking jobs from anyone else.  I demand complete focus from all my soldiers. One other thing.  If you finish this, I'll let Noldan know you will be ready for some ranged accuracy training.
	stopConversation = "false",
	options = {
		{"@conversation/fs_patrol_quest_start:s_199a175c", "all_eight_points"}, -- Yes, let's get started.
		{"@conversation/fs_patrol_quest_start:s_764478e7", "everyone_needs_help"}, -- No, there are others I need to help.
	}
}
villageSarguilloPhase1ConvoTemplate:addScreen(heres_the_drill);

everyone_needs_help = ConvoScreen:new {
	id = "everyone_needs_help",
	leftDialog = "@conversation/fs_patrol_quest_start:s_e0c9cc07", -- That's all right, everyone around here needs a little help.  Come back and see me when you've got more time on your hands.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(everyone_needs_help);

all_eight_points = ConvoScreen:new {
	id = "all_eight_points",
	leftDialog = "@conversation/fs_patrol_quest_start:s_9ec72704", -- Good, here is your first assignment.  I need you to hit all eight points on this patrol, and then report back every time you finish so I can give you the next. I have ten total I need you to do.
	stopConversation = "true",
	options = {}
}
villageSarguilloPhase1ConvoTemplate:addScreen(all_eight_points);

addConversationTemplate("villageSarguilloPhase1ConvoTemplate", villageSarguilloPhase1ConvoTemplate);
