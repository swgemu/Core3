raceDroidConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "raceDroidConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/event_perk_racing:s_ac51e630", -- Greetings, I'm the coordinator for this course. If you'd like to race the track, just let me know. How may I serve you today?
	stopConversation = "false",
	options = {
		{"@conversation/event_perk_racing:s_e460e3d3", "series_of_waypoints"}, -- How do I race?
		{"@conversation/event_perk_racing:s_2492930f", "displaying_data"}, -- I'd like to see who holds the current record for this track.
		{"@conversation/event_perk_racing:s_dffdee4b", "start_the_timer"}, -- I'd like to give this track a try.
	}
}
raceDroidConvoTemplate:addScreen(intro);

series_of_waypoints = ConvoScreen:new {
	id = "series_of_waypoints",
	leftDialog = "@conversation/event_perk_racing:s_4b4fb2b7", -- A series of waypoints will appear one after the other. Head to each waypoint as quickly as possible. When you arrive back here, talk to me again and I'll register your last time for this track.
	stopConversation = "false",
	options = {
		{"@conversation/event_perk_racing:s_2492930f", "displaying_data"}, -- I'd like to see who holds the current record for this track.
		{"@conversation/event_perk_racing:s_dffdee4b", "start_the_timer"}, -- I'd like to give this track a try.
	}
}
raceDroidConvoTemplate:addScreen(series_of_waypoints);

displaying_data = ConvoScreen:new {
	id = "displaying_data",
	leftDialog = "@conversation/event_perk_racing:s_371b3f4", -- Displaying current data...
	stopConversation = "true",
	options = {}
}
raceDroidConvoTemplate:addScreen(displaying_data);

start_the_timer = ConvoScreen:new {
	id = "start_the_timer",
	leftDialog = "@conversation/event_perk_racing:s_1cd82216", -- Get ready... I'll start the timer when you say go!
	stopConversation = "false",
	options = {
		{"@conversation/event_perk_racing:s_2528fad7", "start_race"}, -- GO!!!
		{"@conversation/event_perk_racing:s_262e8687", "no_hurry"}, -- Uhh, wait a minute.
	}
}
raceDroidConvoTemplate:addScreen(start_the_timer);

start_race = ConvoScreen:new {
	id = "start_race",
	leftDialog = "@conversation/event_perk_racing:s_b2acc217", -- And they're off!
	stopConversation = "true",
	options = {}
}
raceDroidConvoTemplate:addScreen(start_race);

no_hurry = ConvoScreen:new {
	id = "no_hurry",
	leftDialog = "@conversation/event_perk_racing:s_c0918d6", -- No hurry. Let me know when you're ready.
	stopConversation = "false",
	options = {
		{"@conversation/event_perk_racing:s_e460e3d3", "series_of_waypoints"}, -- How do I race?
		{"@conversation/event_perk_racing:s_2492930f", "displaying_data"}, -- I'd like to see who holds the current record for this track.
		{"@conversation/event_perk_racing:s_dffdee4b", "start_the_timer"}, -- I'd like to give this track a try.
	}
}
raceDroidConvoTemplate:addScreen(no_hurry);

intro_current_racer = ConvoScreen:new {
	id = "intro_current_racer",
	leftDialog = "@conversation/event_perk_racing:s_6a5b9858", -- The clock is ticking, get moving!
	stopConversation = "false",
	options = {
		{"@conversation/event_perk_racing:s_d900d1be", "as_you_wish"}, -- I need to abort this race.
	}
}
raceDroidConvoTemplate:addScreen(intro_current_racer);

as_you_wish = ConvoScreen:new {
	id = "as_you_wish",
	leftDialog = "@conversation/event_perk_racing:s_6441a2a6", -- As you wish.
	stopConversation = "true",
	options = {}
}
raceDroidConvoTemplate:addScreen(as_you_wish);

addConversationTemplate("raceDroidConvoTemplate", raceDroidConvoTemplate);
