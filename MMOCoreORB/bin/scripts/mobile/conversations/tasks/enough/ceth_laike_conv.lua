ceth_laike_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "CethLaikeConvoHandler",
	screens = {}
}

neutral_greeting = ConvoScreen:new {
	id = "neutral_greeting",
	leftDialog = "@conversation/c_sink_imp:s_1334", -- Hello citizen, nice day isn't it?  I'm sorry, but I don't have anything that you can help me with.  I really need a member of the Imperial Armed Forces.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(neutral_greeting)

rebel_greeting = ConvoScreen:new {
	id = "rebel_greeting",
	leftDialog = "@conversation/c_sink_imp:s_1332", -- What makes you think I will talk to you, insurgent?
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(rebel_greeting)

imperial_greeting = ConvoScreen:new {
	id = "imperial_greeting",
	leftDialog = "@conversation/c_sink_imp:s_1336", -- I have a simple mission for you, soldier.  A good friend of mine from the academy needs an escort back here from an accident.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1338", "response_1"}, -- Escort from where?  What happened?
	}
}
ceth_laike_conv:addScreen(imperial_greeting)


response_1 = ConvoScreen:new {
	id = "response_1",
	leftDialog = "@conversation/c_sink_imp:s_1340", -- During a battle, those Rebels shot his ship down.  He's good enough, and lucky enough to have crash-landed instead of blowing up. But, outside of a ship, he's just terrible.  He needs someone to bring him back here.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1342", "response_start"}, -- It would be a privilege to escort a friend of yours, sir.
		{"@conversation/c_sink_imp:s_1346", "response_deny"}, -- I think the pilot can make it back on his own. Isn't that what he was trained for?
	}
}
ceth_laike_conv:addScreen(response_1)

response_start = ConvoScreen:new {
	id = "response_start",
	leftDialog = "@conversation/c_sink_imp:s_1344", -- Good show.  Let me give you the location.  You can't miss it; look for the crashed Tie Fighter.  My friend is probably out of sight.  I'll radio and let him know that you are coming, so just go to the coordinates that I give you and bring him back.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(response_start)

response_deny = ConvoScreen:new {
	id = "response_deny",
	leftDialog = "@conversation/c_sink_imp:s_1348", -- I see.  You are right of course.  I'll remember to mention that to the dispatcher if you ever need a lift back to base.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(response_deny)

where_friend = ConvoScreen:new {
	id = "where_friend",
	leftDialog = "@conversation/c_sink_imp:s_1380", -- I don't see my friend with you.  I guess you should be heading out to get him.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1382", "new_waypoint"}, -- I need the location again.
	}
}
ceth_laike_conv:addScreen(where_friend)

new_waypoint = ConvoScreen:new {
	id = "new_waypoint",
	leftDialog = "@conversation/c_sink_imp:s_1168", -- Go north and look for the crashed Escape Pod.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(new_waypoint)

no_pilot = ConvoScreen:new {
	id = "no_pilot",
	leftDialog = "@conversation/c_sink_imp:s_1350", -- Welcome back.  Tell me what happened.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1352", "time_for_action"}, -- I found a corpse at the crash site and a bunch of Binayre attacked me.
	}
}
ceth_laike_conv:addScreen(no_pilot)

time_for_action = ConvoScreen:new {
	id = "time_for_action",
	leftDialog = "@conversation/c_sink_imp:s_1354", -- My friend must be dead.  The good news is that they finally stepped over the line.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1356", "explain_more"}, -- I beg your pardon, sir?  There is good news in this?
	}
}
ceth_laike_conv:addScreen(time_for_action)

explain_more = ConvoScreen:new {
	id = "explain_more",
	leftDialog = "@conversation/c_sink_imp:s_1358", -- Yes and no.  I have just received orders that if those thugs attack Imperial personnel, I am authorized to take whatever actions I deem necessary.
	stopConversation = "false",
	options = {
		{"@conversation/c_sink_imp:s_1360", "just_gangs1"}, -- What, exactly do you deem necessary?
		{"@conversation/c_sink_imp:s_1372", "help_accept"}, -- I want to help! I hate those gangs. Thugs and criminals, all of them.  Tell me what I can do.
		{"@conversation/c_sink_imp:s_1376", "help_decline"}, -- Respectfully, sir, I want no part of this. Even if you asked me to do something, I will not.
	}
}
ceth_laike_conv:addScreen(explain_more)

just_gangs1 = ConvoScreen:new {
	id = "just_gangs1",
	leftDialog = "@conversation/c_sink_imp:s_1362", -- I want to cripple them. They hurt and kill our citizens and they must be executed. I want them rendered ineffective and then wiped out.
	options = {
		{"@conversation/c_sink_imp:s_1364", "help_accept"}, -- Sounds like a rough job.  I like it!
		{"@conversation/c_sink_imp:s_1368", "help_decline2"}, -- No way.  I don't get involved in minor disputes.  That is what the Planetary Security Forces are for.
	}
}
ceth_laike_conv:addScreen(just_gangs1)

help_accept = ConvoScreen:new {
	id = "help_accept",
	leftDialog = "@conversation/c_sink_imp:s_1366", -- That's the spirit!  I want you to target two of the groups, one here and one on Corellia. I'll transmit the information to your journal and datapad.  Good luck, soldier!
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(help_accept)

help_decline = ConvoScreen:new {
	id = "help_decline",
	leftDialog = "@conversation/c_sink_imp:s_1378", -- Know that you are turning your back on the law-abiding citizens that you are supposed to be defending.  Sleep well on that... soldier.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(help_decline)

help_decline2 = ConvoScreen:new {
	id = "help_decline2",
	leftDialog = "@conversation/c_sink_imp:s_1370", -- Well they are obviously not nearly as effective as they should be, are they?  If you stand aside, it's your business, just get the hell out of the way while I do something about it.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(help_decline2)

ground_kill = ConvoScreen:new {
	id = "ground_kill",
	leftDialog = "@conversation/c_sink_imp:s_1386", -- How did it go?
	stopConversation = "false",
	options = {
		--{"@conversation/c_sink_imp:s_1388", "ground_failing"}, -- I haven't started yet, sir.
		--{"@conversation/c_sink_imp:s_1392", "ground_progress"}, -- I'm still working my way through the bad guys.
		--{"@conversation/c_sink_imp:s_1396", "ground_finished"}, -- I have the Flail symbols and you have heard about the Binayre, I believe, sir.
	}
}
ceth_laike_conv:addScreen(ground_kill)

ground_failing = ConvoScreen:new {
	id = "ground_failing",
	leftDialog = "@conversation/c_sink_imp:s_1390", -- Then I suggest you start now.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(ground_failing)

ground_progress = ConvoScreen:new {
	id = "ground_progress",
	leftDialog = "@conversation/c_sink_imp:s_1394", -- I have nothing else to offer you now.  Get going!
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(ground_progress)

ground_finished = ConvoScreen:new {
	id = "ground_finished",
	leftDialog = "@conversation/c_sink_imp:s_1396", -- I have the Flail symbols and you have heard about the Binayre, I believe, sir.
	stopConversation = "false",
	options = {
		--{"@conversation/c_sink_imp:s_1400", "space_start"}, -- These thugs aren't only on the ground, sir.
		--{"@conversation/c_sink_imp:s_1404", "ground_done"}, -- I am happy to do my part.
	}
}
ceth_laike_conv:addScreen(ground_finished)

ground_done = ConvoScreen:new {
	id = "ground_done",
	leftDialog = "@conversation/c_sink_imp:s_1406", -- Let me give you your reward for a job well done.  It looks like this little problem isn't so little.  I need to do some research.  I'll probably have more for you at a later time.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(ground_done)

space_start = ConvoScreen:new {
	id = "space_start",
	leftDialog = "@conversation/c_sink_imp:s_1402", -- Very true.  In fact, that's something that I was going to talk to you about.  Binyare fly this sector and I want you to cripple their fleet, a few ships at a time.  Once you are in space, I'll transfer coordinates to you.
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(space_start)

space_wait = ConvoScreen:new {
	id = "space_wait",
	customDialogText = "It seems that you are not a pilot of the Imperial Navy... you better change that before you speak to me again.",
	stopConversation = "true",
	options = {}
}
ceth_laike_conv:addScreen(space_wait)

addConversationTemplate("ceth_laike_conv", ceth_laike_conv)