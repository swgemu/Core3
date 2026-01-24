ufwol_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ufwolConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
ufwol_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_4a4a0211", -- I don't think that you belong here.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_no_jtl)

-- Imperial/Not Rebel Pilot
ufwol_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_4", -- I don't think that you belong here, soldier.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_imperial_pilot)

-- Neutral Pilot
ufwol_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_4", -- I don't think that you belong here, soldier.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_neutral_pilot)

-- Non-Crimson Phoenix Rebel Pilot (not on track)
ufwol_convo_non_crimson_phoenix_pilot = ConvoScreen:new {
	id = "non_crimson_phoenix_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_b9b83ec5", -- Eh? You don't fly for the Crimson Phoenix. What are you doing here?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_d157e1de", "non_track_explain"}, -- I'm looking for missions.
	}
}
ufwol_convo:addScreen(ufwol_convo_non_crimson_phoenix_pilot)

-- Non Track Explain
ufwol_convo_non_track_explain = ConvoScreen:new {
	id = "non_track_explain",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_b9b83ec5", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_non_track_explain)

-- Not Rebel Pilot
ufwol_convo_not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_4", -- I don't think that you belong here, soldier.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_not_rebel_pilot)

-- Not Ready (hasn't completed Tier 3)
ufwol_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_46ccc483", -- I think you've got work to do for Ulvaw'op, soldier.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_not_ready)

-- Has Active Mission
ufwol_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_a86d6540", -- You've already got a mission. I suggest you do it.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_has_mission)

-- Introduction (hasn't met)
ufwol_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_1ec8846c", -- Hello, pilot. Welcome to Rori. First time here?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_340", "quest1_brief"}, -- Yes sir.
	}
}
ufwol_convo:addScreen(ufwol_convo_introduction)

-- Quest 1 Brief
ufwol_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_1ec8846c", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_quest1_brief)

-- Grant Quest 1 (ready for mission 1)
ufwol_convo_grant_quest1 = ConvoScreen:new {
	id = "grant_quest1",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_37df0fba", -- You're up. Let's see if you can keep up with my squadron.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_5bc07030", "accept_mission1"}, -- What's the mission, sir?
		{"@conversation/tatooine_rebel_tier4:s_321", "accept_mission1"}, -- I'm ready to go.
	}
}
ufwol_convo:addScreen(ufwol_convo_grant_quest1)

-- Accept Mission 1
ufwol_convo_accept_mission1 = ConvoScreen:new {
	id = "accept_mission1",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_37df0fba", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_accept_mission1)

-- Failed Quest 1
ufwol_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_8d9faecf", -- That's mission failure, soldier.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_a95ef734", "retry_quest1"}, -- Requesting redeployment!
		{"@conversation/tatooine_rebel_tier4:s_9fc24a78", "retry_quest1"}, -- Are you transferring me out of this unit?
	}
}
ufwol_convo:addScreen(ufwol_convo_failed_quest1)

-- Retry Quest 1
ufwol_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_37df0fba", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete)
ufwol_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_831e2b3a", -- All soldiers receive duty pay at the end of each mission.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_987445c9", "grant_quest2"}, -- Thank you, sir.
		{"@conversation/tatooine_rebel_tier4:s_f69a2921", "grant_quest2"}, -- Glad to hear it.
	}
}
ufwol_convo:addScreen(ufwol_convo_excellent_work)

-- Grant Quest 2 (ready for mission 2)
ufwol_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_7b03d343", -- My men tell me you weren't too bad up there.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_d059f8aa", "quest2_brief"}, -- Those TIE fighters are tough!
		{"@conversation/tatooine_rebel_tier4:s_24f29c02", "quest2_brief"}, -- I held my own.
	}
}
ufwol_convo:addScreen(ufwol_convo_grant_quest2)

-- Quest 2 Brief
ufwol_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_7b03d343", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_quest2_brief)

-- Failed Quest 2
ufwol_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_9b578280", -- Where's that Imperial ship?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_1678be5a", "retry_quest2"}, -- I haven't brought one down yet.
		{"@conversation/tatooine_rebel_tier4:s_6912a453", "retry_quest2"}, -- We're trying, sir.
	}
}
ufwol_convo:addScreen(ufwol_convo_failed_quest2)

-- Retry Quest 2
ufwol_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_7b03d343", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_retry_quest2)

-- Excellent Work 2 (Quest 2 Complete)
ufwol_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_6c524e01", -- Nice work, %TU. Our engineers are examining that TIE fighter now. Here's your duty pay.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_9c236354", "grant_quest3"}, -- Excellent.
		{"@conversation/tatooine_rebel_tier4:s_987445c9", "grant_quest3"}, -- Thank you, sir.
	}
}
ufwol_convo:addScreen(ufwol_convo_excellent_work2)

-- Grant Quest 3 (ready for mission 3)
ufwol_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_49bf2ccb", -- We've been taking a close look at that TIE fighter. Quite a piece of machinery.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_c8a0830d", "quest3_brief"}, -- Especially those guns.
		{"@conversation/tatooine_rebel_tier4:s_c01ad90e", "quest3_brief"}, -- They're going to give us a problem, sir.
	}
}
ufwol_convo:addScreen(ufwol_convo_grant_quest3)

-- Quest 3 Brief
ufwol_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_49bf2ccb", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_quest3_brief)

-- Failed Quest 3
ufwol_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_6d4fe1fb", -- Unacceptable, soldier.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_8c5f29f4", "retry_quest3"}, -- I want to be a part of the Crimson Phoenix, sir.
		{"@conversation/tatooine_rebel_tier4:s_63740522", "retry_quest3"}, -- Requesting redeployment, sir!
	}
}
ufwol_convo:addScreen(ufwol_convo_failed_quest3)

-- Retry Quest 3
ufwol_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_49bf2ccb", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_retry_quest3)

-- Excellent Work 3 (Quest 3 Complete)
ufwol_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_d5a98554", -- I have your duty pay.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_acef64cd", "grant_quest4"}, -- I did a good job out there.
		{"@conversation/tatooine_rebel_tier4:s_d0fd857b", "grant_quest4"}, -- I'll take it.
	}
}
ufwol_convo:addScreen(ufwol_convo_excellent_work3)

-- Grant Quest 4 (ready for mission 4 - official Crimson Phoenix)
ufwol_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_d30b6d26", -- Congratulations, soldier. You're officially a part of the Crimson Phoenix.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_87f091b9", "quest4_brief"}, -- Thank you, sir. I'm happy to be a part of the team.
		{"@conversation/tatooine_rebel_tier4:s_90", "quest4_brief"}, -- Excellent.
	}
}
ufwol_convo:addScreen(ufwol_convo_grant_quest4)

-- Quest 4 Brief
ufwol_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_d30b6d26", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_quest4_brief)

-- Failed Quest 4
ufwol_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_eb925c97", -- I thought you said you WANTED to be a part of the Crimson Phoenix.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_4479e343", "retry_quest4"}, -- I do, sir!
		{"@conversation/tatooine_rebel_tier4:s_2022581b", "retry_quest4"}, -- Sir, it won't happen again.
	}
}
ufwol_convo:addScreen(ufwol_convo_failed_quest4)

-- Retry Quest 4
ufwol_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_d30b6d26", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_retry_quest4)

-- All Missions Complete (Quest 4 Complete)
ufwol_convo_all_missions_complete = ConvoScreen:new {
	id = "all_missions_complete",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_bf1cdb65", -- Here's a little something.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_a58b9067", "training_menu"}, -- Duty pay?
		{"@conversation/tatooine_rebel_tier4:s_987445c9", "training_menu"}, -- Thank you, sir.
	}
}
ufwol_convo:addScreen(ufwol_convo_all_missions_complete)

-- Training Menu (dynamic options added by handler)
ufwol_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_cb594529", -- Well soldier, you've earned the right to upgrade to a new skill. I expect all my pilots to continue their training, at all times!
	stopConversation = "false",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_training_menu)

-- Ready for Training
ufwol_convo_ready_for_training = ConvoScreen:new {
	id = "ready_for_training",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_cb594529", -- Well soldier, you've earned the right to upgrade to a new skill. I expect all my pilots to continue their training, at all times!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_411", "training_menu"}, -- What is on the training schedule today?
	}
}
ufwol_convo:addScreen(ufwol_convo_ready_for_training)

-- Duty Missions Menu (not completed tier 4)
ufwol_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- Well? Are you ready for a duty assignment? Or would you like to hear the briefing again?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_89951606", "duty_destroy"}, -- Let me at those Imperial patrols.
		{"@conversation/tatooine_rebel_tier4:s_91502216", "duty_escort"}, -- I'll fly escort for those Rebel spies.
		{"@conversation/tatooine_rebel_tier4:s_67ee2a0", "duty_rescue"}, -- I want to help those prisoners.
		{"@conversation/tatooine_rebel_tier4:s_c1c9b365", "duty_recovery"}, -- I'll do whatever I can to help those disabled freighters.
		{"@conversation/tatooine_rebel_tier4:s_49805f81", "duty_briefing"}, -- Can I hear the briefing again?
	}
}
ufwol_convo:addScreen(ufwol_convo_duty_missions)

-- Duty Destroy
ufwol_convo_duty_destroy = ConvoScreen:new {
	id = "duty_destroy",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_duty_destroy)

-- Duty Escort
ufwol_convo_duty_escort = ConvoScreen:new {
	id = "duty_escort",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_duty_escort)

-- Duty Rescue
ufwol_convo_duty_rescue = ConvoScreen:new {
	id = "duty_rescue",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_duty_rescue)

-- Duty Recovery
ufwol_convo_duty_recovery = ConvoScreen:new {
	id = "duty_recovery",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_duty_recovery)

-- Duty Briefing
ufwol_convo_duty_briefing = ConvoScreen:new {
	id = "duty_briefing",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_39a10eac", -- dynamic
	stopConversation = "false",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_duty_briefing)

-- Completed Tier 4 (send to Admiral Burke for master skill)
ufwol_convo_completed_tier4 = ConvoScreen:new {
	id = "completed_tier4",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_30a32651", -- Good, you're here. I have your orders. Seems that somebody has taken an interest in your piloting abilities. You're being transferred.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_1d23eb6a", "go_to_burke"}, -- Where to?
		{"@conversation/tatooine_rebel_tier4:s_3cc21469", "go_to_burke"}, -- I always knew I was destined for greatness.
	}
}
ufwol_convo:addScreen(ufwol_convo_completed_tier4)

-- Go to Admiral Burke
ufwol_convo_go_to_burke = ConvoScreen:new {
	id = "go_to_burke",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_30a32651", -- dynamic
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_go_to_burke)

-- Master Pilot (completed Admiral Burke)
ufwol_convo_master_pilot = ConvoScreen:new {
	id = "master_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_233489bc", -- Glad to see that you made it back from your assignment with Admiral Burke. Are you looking for work?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier4:s_89951606", "duty_destroy"}, -- Let me at those Imperial patrols.
		{"@conversation/tatooine_rebel_tier4:s_91502216", "duty_escort"}, -- I'll fly escort for those Rebel spies.
		{"@conversation/tatooine_rebel_tier4:s_67ee2a0", "duty_rescue"}, -- I want to help those prisoners.
		{"@conversation/tatooine_rebel_tier4:s_c1c9b365", "duty_recovery"}, -- I'll do whatever I can to help those disabled freighters.
		{"@conversation/tatooine_rebel_tier4:s_49805f81", "duty_briefing"}, -- Can I hear the briefing again?
	}
}
ufwol_convo:addScreen(ufwol_convo_master_pilot)

-- Goodbye
ufwol_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/tatooine_rebel_tier4:s_a86d6540", -- You've already got a mission. I suggest you do it.
	stopConversation = "true",
	options = {}
}
ufwol_convo:addScreen(ufwol_convo_goodbye)

addConversationTemplate("ufwol_convo", ufwol_convo)
