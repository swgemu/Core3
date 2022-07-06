imperialCoordinatorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialCoordinatorConvoHandler",
	screens = {}
}

--[[

	Start CoA3 - Imperial Coordinator does not have winning Options

]]

coa3_init = ConvoScreen:new {
	id = "coa3_init",
	leftDialog = "@conversation/coa3lcoordinator:s_20ad68cd", -- It's a pleasure seeing you again, thank you for coming! Actually, I'm not surprised considering you have been in the middle of this whole Dead-Eye situation from the beginning. Your work so far has been top-notch and you haven't failed us yet. Would you be willing to accept another mission?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_c4ae7e31", "coa3_a_lot_has_happened"}, -- I'd love to help out again.
		{"@conversation/coa3lcoordinator:s_20eec74a", "coa3_must_be_very_busy"}, -- I need to do something else right now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init);

coa3_a_lot_has_happened = ConvoScreen:new {
	id = "coa3_a_lot_has_happened",
	leftDialog = "@conversation/coa3lcoordinator:s_976a6f0", -- Great! A lot has happened since we last spoke. I don't have time to go over all of the details with you right now. Go and speak with our Information Officer and listen to what he has to say. You can find him in the Commerce Guild Hall in this city.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_f595b0cb", "coa3_get_filled_in"}, -- Ok, I'll go see what he has to say.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_a_lot_has_happened);

coa3_must_be_very_busy = ConvoScreen:new {
	id = "coa3_must_be_very_busy",
	leftDialog = "@conversation/coa3lcoordinator:s_4e122a6b", -- I understand. You must be a very busy person. We haven't forgotten about what you did for us last time and we don't want to put you out. We really could use your help though, so if you change your mind come back and see me. I could use a person who can get results.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_must_be_very_busy);

coa3_get_filled_in = ConvoScreen:new {
	id = "coa3_get_filled_in",
	leftDialog = "@conversation/coa3lcoordinator:s_223c5db", -- Great, once you get all filled in on the details feel free to come back and see me. I'm not quite finished with what I'm working on but I think I may need to call upon your top notch talents once again.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_get_filled_in);


-- Player sent to Information Officer, but has not spoken to them yet


coa3_init_go_to_info = ConvoScreen:new {
	id = "coa3_init_go_to_info",
	leftDialog = "@conversation/coa3lcoordinator:s_6837ec87", -- Oh it's you again! I didn't expect to see you so soon. Unfortunately, I'm still crunching some data right now. Why don't you go and speak with our Information Officer. You can find him in the Commerce Guild in this city. Get all details from him about our current situation and by the time you're done with that, I should be done analyzing this data.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_go_to_info);


-- Player has spoken with Information Officer


coa3_init_completed_info = ConvoScreen:new {
	id = "coa3_init_completed_info",
	leftDialog = "@conversation/coa3lcoordinator:s_4ba81cc8", -- Ah good, you're back! I've finished analyzing the data from our most recent intelligence and it looks pretty promising. I think we are ready to proceed with our plan. I'll need you to go undercover. If you're successful you probably won't need to fire a single shot. If you fail, that's a different story and we're back to square one. Do you have any questions?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_b4f92479", "coa3_cornered_market"}, -- What are the details of this mission?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them"}, -- Enough details, I'm ready to go.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_completed_info);

coa3_cornered_market = ConvoScreen:new {
	id = "coa3_cornered_market",
	leftDialog = "@conversation/coa3lcoordinator:s_ad11a99b", -- As I'm sure you know various underworld organizations have all but cornered the market on this Alderaanian Flora. As to be expected, Jabba the Hutt has come out ahead in this game and he seems to be the one doing the most business. This flora is enormously valuable so obviously Jabba's rivals are taking every opportunity to hijack any shipments they come across. Knowing this, Jabba is using a decentralized system of storage and transport to cut down on losses.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_efdb954e", "coa3_traffic_flora"}, -- Ok, go on.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them"}, -- Enough details, I'm ready to go.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_cornered_market);

coa3_pose_as_them = ConvoScreen:new {
	id = "coa3_pose_as_them",
	leftDialog = "@conversation/coa3lcoordinator:s_26b400f9", -- Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_pose_as_them);

coa3_traffic_flora = ConvoScreen:new {
	id = "coa3_traffic_flora",
	leftDialog = "@conversation/coa3lcoordinator:s_4724fd7d", -- He's using land vehicles to traffic the flora to and from the storehouses with a complex system of lookouts scattered along the routes. If any trouble is spotted, the caravans are alerted and they use a different route. It's all very organized. The intelligence I just analyzed reveals the location of all the lookouts on the planet and it indicates a caravan is to make a delivery today. Predicting the caravan's destination is simply impossible. This is where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_19d2e135", "coa3_gather_information"}, -- Interesting. Please continue.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them"}, -- Enough details, I'm ready to go.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_traffic_flora);

coa3_gather_information = ConvoScreen:new {
	id = "coa3_gather_information",
	leftDialog = "@conversation/coa3lcoordinator:s_1fd11fc5", -- They are so cautious that caravans have been known to zig zag and circle for hours before finally heading to their destination unless things are completely safe. Simple observation won't tell us anything, so we need you to pose as a member of their organization and try to gather information about where that caravan is headed. We need hard information; disks, papers, whatever you can find. As you can imagine, this will be dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_4ca03ddb", "coa3_incredibly_suspicious"}, -- How so?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them"}, -- Enough details, I'm ready to go.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_gather_information);

coa3_incredibly_suspicious = ConvoScreen:new {
	id = "coa3_incredibly_suspicious",
	leftDialog = "@conversation/coa3lcoordinator:s_1f81bc3c", -- These people are incredibly suspicious so you'll need to be very convincing. If they suspect you they won't hesitate to attack. If that happens, then I'm afraid we'll have to start over and try it again. Are you prepared to take on this task?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_d55f2579", "coa3_uploaded_lookout_location"}, -- I'm ready to go.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_incredibly_suspicious);

coa3_uploaded_lookout_location = ConvoScreen:new {
	id = "coa3_uploaded_lookout_location",
	leftDialog = "@conversation/coa3lcoordinator:s_eae61031", -- Great! I've uploaded the location of one of their lookouts to your datapad. Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_uploaded_lookout_location);


-- Player has been sent on lookout mission

-- Player does not have disk yet
coa3_init_has_lookout = ConvoScreen:new {
	id = "coa3_init_has_lookout",
	leftDialog = "@conversation/coa3lcoordinator:s_882bc6e0", -- Well, how did things go?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_a6f2327f", "coa3_cornered_market_reminder"}, -- What were the details of the mission again?
		{"@conversation/coa3lcoordinator:s_7b9e2f5e", "coa3_ran_into_trouble"}, -- Can I have another waypoint?
		{"@conversation/coa3lcoordinator:s_80af7773", "coa3_friendly_first"}, -- Got any advice for me?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_later"}, -- I can't do this right now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_has_lookout);

coa3_cornered_market_reminder = ConvoScreen:new {
	id = "coa3_cornered_market_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_ad11a99b", -- As I'm sure you know various underworld organizations have all but cornered the market on this Alderaanian Flora. As to be expected, Jabba the Hutt has come out ahead in this game and he seems to be the one doing the most business. This flora is enormously valuable so obviously Jabba's rivals are taking every opportunity to hijack any shipments they come across. Knowing this, Jabba is using a decentralized system of storage and transport to cut down on losses.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_efdb954e", "coa3_traffic_flora_reminder"}, -- Ok, go on.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_cornered_market_reminder);

coa3_traffic_flora_reminder = ConvoScreen:new {
	id = "coa3_traffic_flora_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_4724fd7d", -- He's using land vehicles to traffic the flora to and from the storehouses with a complex system of lookouts scattered along the routes. If any trouble is spotted, the caravans are alerted and they use a different route. It's all very organized. The intelligence I just analyzed reveals the location of all the lookouts on the planet and it indicates a caravan is to make a delivery today. Predicting the caravan's destination is simply impossible. This is where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_19d2e135", "coa3_gather_information_reminder"}, -- Interesting. Please continue.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_traffic_flora_reminder);

coa3_gather_information_reminder = ConvoScreen:new {
	id = "coa3_gather_information_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_1fd11fc5", -- They are so cautious that caravans have been known to zig zag and circle for hours before finally heading to their destination unless things are completely safe. Simple observation won't tell us anything, so we need you to pose as a member of their organization and try to gather information about where that caravan is headed. We need hard information; disks, papers, whatever you can find. As you can imagine, this will be dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_4ca03ddb", "coa3_incredibly_suspicious_reminder"}, -- How so?
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_gather_information_reminder);

coa3_incredibly_suspicious_reminder = ConvoScreen:new {
	id = "coa3_incredibly_suspicious_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_1f81bc3c", -- These people are incredibly suspicious so you'll need to be very convincing. If they suspect you they won't hesitate to attack. If that happens, then I'm afraid we'll have to start over and try it again. Are you prepared to take on this task?
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_incredibly_suspicious_reminder);

-- Player has disk

coa3_init_has_disk = ConvoScreen:new {
	id = "coa3_init_has_disk",
	leftDialog = "@conversation/coa3lcoordinator:s_fec795", -- Excellent work! To be honest, I didn't think you could pull it off. You must have done some real smooth talking! I'll start analyzing the disk right away but it is going to take some time. Why don't you go and speak with the Tactical Officer, I believe he has something for you to do. You can find him in the Combat Guild of this city.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_has_disk);

-- Player has been sent to tactical officer but not spoken to them yet

coa3_init_go_to_tact = ConvoScreen:new {
	id = "coa3_init_go_to_tact",
	leftDialog = "@conversation/coa3lcoordinator:s_19d54dc3", -- Back so soon? I'm still trying to break the encryption on this disk. It's going to take me some time. In the mean time, go and speak with the Tactical Officer. You can find him in the Combat Guild in this city. I'm sure he has plenty that needs to be done.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_go_to_tact);

-- Player has gone to the tactical officer and spoken to him

coa3_init_completed_tact = ConvoScreen:new {
	id = "coa3_init_completed_tact",
	leftDialog = "@conversation/coa3lcoordinator:s_fa0fdb09", -- Great to see you again. Those disks you acquired have been of great help to our Tactical Officer. He'll be able to assign as many assault missions as you can take, but there is something of more importance if you're up for it.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_f35aaa26", "coa3_big_impression"}, -- I'm up for anything.
		{"@conversation/coa3lcoordinator:s_d819b34e", "coa3_count_on_support"}, -- I'm not able to do this now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_completed_tact);

coa3_big_impression = ConvoScreen:new {
	id = "coa3_big_impression",
	leftDialog = "@conversation/coa3lcoordinator:s_70df24d2", -- I thought you'd say that. You've made a big impression and Colonel Veers himself has flown into our headquarters there to oversee the operation. He said he wanted to speak with you personally about it. I've added a waypoint to your datapad with the location of the off-world headquarters. I'd head there at once so you don't keep him waiting.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_4148ae14", "coa3_heavy_action"}, -- I look forward to meeting the Colonel.
		{"@conversation/coa3lcoordinator:s_d819b34e", "coa3_count_on_support"}, -- I'm not able to do this now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_big_impression);

coa3_heavy_action = ConvoScreen:new {
	id = "coa3_heavy_action",
	leftDialog = "@conversation/coa3lcoordinator:s_458473c9", -- Good. I'm sure there will be some heavy action when you get there, so you may want to bring some loyal friends if you're not much of a fighter.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_heavy_action);

coa3_count_on_support = ConvoScreen:new {
	id = "coa3_count_on_support",
	leftDialog = "@conversation/coa3lcoordinator:s_740fcda6", -- That's too bad, I was hoping I could count on your support with this. The offer still stands if you change your mind.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_count_on_support);

-- Player has been sent to see Colonel Veers but not completed the final mission

coa3_init_go_to_veers = ConvoScreen:new {
	id = "coa3_init_go_to_veers",
	leftDialog = "@conversation/coa3lcoordinator:s_448b1792", -- Have you been to see Colonel Veers yet? You probably don't want to keep him waiting. Anyway, was there something I can help you with right now?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_bc0e9972", "coa3_leave_soon"}, -- Nothing for right now, thanks.
		{"@conversation/coa3lcoordinator:s_52cc7bda", "coa3_thought_was_correct"}, -- Are you sure that waypoint was correct?
		{"@conversation/coa3lcoordinator:s_315ff574", "coa3_thats_a_shame"}, -- I can't make it there right now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_go_to_veers);

coa3_leave_soon = ConvoScreen:new {
	id = "coa3_leave_soon",
	leftDialog = "@conversation/coa3lcoordinator:s_ecae16e7", -- Ok, carry on. You should probably leave soon though.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_leave_soon);

coa3_thought_was_correct = ConvoScreen:new {
	id = "coa3_thought_was_correct",
	leftDialog = "@conversation/coa3lcoordinator:s_cd603241", -- I thought that it was correct. I'll update your datapad again just to be safe.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_thought_was_correct);

coa3_thats_a_shame = ConvoScreen:new {
	id = "coa3_thats_a_shame",
	leftDialog = "@conversation/coa3lcoordinator:s_45cbfb7d", -- Well that's a shame. If you change your mind, please let me know.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_thats_a_shame);

coa3_init_complete = ConvoScreen:new {
	id = "coa3_init_complete",
	leftDialog = "@conversation/coa3lcoordinator:s_e08167af", -- Well, it's always a pleasure to see you! We've made some progress in putting a stop to Dead Eye thanks to you. You are to be commended. I don't have anything else I need from you right now. You might ask our Tactical Officer at the Combat Guild if he still needs helping tracking down and destroying those warehouses.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_init_complete);

-- Generica CoA3 responses

coa3_ran_into_trouble = ConvoScreen:new {
	id = "coa3_ran_into_trouble",
	leftDialog = "@conversation/coa3lcoordinator:s_8ee9343e", -- Ran into trouble did you? Well there are plenty of lookouts out there still. Here is the location of another one. Come back as soon as you find any sort of hard data about that caravan and maybe we can determine where it was heading. Good luck to you!
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_ran_into_trouble);

coa3_friendly_first = ConvoScreen:new {
	id = "coa3_friendly_first",
	leftDialog = "@conversation/coa3lcoordinator:s_cf35e3d5", -- A direct approach might get you killed. You'll need to get friendly with them first and then maybe they will trust you and open up. Think like a thug. Thugs are generally greedy, selfish, out for themselves. They like things like drinking, gambling, cheating, carousing; that sort of thing.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_friendly_first);

coa3_come_back_later = ConvoScreen:new {
	id = "coa3_come_back_later",
	leftDialog = "@conversation/coa3lcoordinator:s_a3ea7bf6", -- I'm sorry to hear that. Come back later if you change your mind.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_come_back_later);

coa3_come_back_when_ready = ConvoScreen:new {
	id = "coa3_come_back_when_ready",
	leftDialog = "@conversation/coa3lcoordinator:s_37281366", -- I understand. I wouldn't want you to take on this mission unless you are completely prepared. Come back when you are ready.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa3_come_back_when_ready);

generic_response = ConvoScreen:new {
	id = "generic_response",
	leftDialog = "@recruiting/imperial_recruit:ir13", -- Good day, and what can I do for you?
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(generic_response);

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:coordinator_rebel_response", -- I have nothing to say to those who have dealings with rebel scum. I suggest you move along before you find yourself in a hail of blaster fire!
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(begin_wrong_faction);

--[[



	========== CoA2 Conversation Options =========



]]

coa2_m1_begin = ConvoScreen:new {
	id = "coa2_m1_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin", -- A rebel agent stole some very important documents concerning the Dead Eye project. We would like to stop this information from falling into the wrong hands. Would you like to help?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info1", "coa2_m1_begin_info1"}, -- Who is this agent?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info2", "coa2_m1_begin_info2"}, -- What is the Dead Eye Project?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "coa2_m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "coa2_m1_begin_no"}, -- No thanks.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_begin);

coa2_m1_begin_info1 = ConvoScreen:new {
	id = "coa2_m1_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_info1_response", -- Her codename is Skimmer. Her whereabouts are unknown. She joined the rebellion after both her father and brother were killed during earlier campaigns waged against the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info2", "coa2_m1_begin_info2"}, -- What is the Dead Eye Project?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "coa2_m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "coa2_m1_begin_no"}, -- No thanks.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_begin_info1);

coa2_m1_begin_info2 = ConvoScreen:new {
	id = "coa2_m1_begin_info2",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_info2_response", -- That information is need-to-know only and you don't need to know. Be assured that success of project Dead Eye is extremely important to the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_info1", "coa2_m1_begin_info1"}, -- Who is this agent?
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_yes", "coa2_m1_begin_yes"}, -- I would like to help.
		{"@theme_park/alderaan/act2/imperial_missions:m1_begin_no", "coa2_m1_begin_no"}, -- No thanks.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_begin_info2);

coa2_m1_begin_yes = ConvoScreen:new {
	id = "coa2_m1_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_yes_response", -- We have an informant that has intercepted a rebel communication outlining their next move. Speak with the informant and return to me. I have added a waypoint to your data pad.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_begin_yes);

coa2_m1_begin_no = ConvoScreen:new {
	id = "coa2_m1_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_begin_no_response", -- Very well. If you change your mind, come back and we'll talk.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_begin_no);

coa2_m1_active = ConvoScreen:new {
	id = "coa2_m1_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active", -- Have you spoken with the informant yet? This information is vital to the Empire.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_working", "coa2_m1_active_working"}, -- I'll speak with the informant immediately.
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_restart", "coa2_m1_active_restart"}, -- Are you sure those coordinates were correct?
		{"@theme_park/alderaan/act2/imperial_missions:m1_active_abort", "coa2_m1_active_abort"}, -- I don't have time for this right now.
	}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_active);

coa2_m1_active_working = ConvoScreen:new {
	id = "coa2_m1_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_working_response", -- Good. Carry on.
	stopConversation = "true",
	options = {}
}
imperialCoordinatorConvoTemplate:addScreen(coa2_m1_active_working);

coa2_m1_active_restart = ConvoScreen:new {
	id = "coa2_m1_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_restart_response", -- It looks as though the informant has moved. Here, I've updated his current location into your datapad.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m1_active_restart);

coa2_m1_active_abort = ConvoScreen:new {
	id = "coa2_m1_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m1_active_abort_response", -- I'm sorry to hear that. Perhaps we can find someone else for the job.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m1_active_abort);

coa2_m2_begin = ConvoScreen:new {
	id = "coa2_m2_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin", -- We need to prevent that encoded message from being transmitted and retrieve it. Are you ready to get your hands dirty?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_info1", "coa2_m2_begin_info1"}, -- Get my hands dirty?
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_yes", "coa2_m2_begin_yes"}, -- I'll do what is necessary.
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_no", "coa2_m2_begin_no"}, -- I'm not so sure I'm up to this.
	}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_begin);

coa2_m2_begin_info1 = ConvoScreen:new {
	id = "coa2_m2_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_info1_response", -- That's just an expression. Lethal force is authorized considering the sensitive nature of this case. You don't need to worry about any legal repercussions.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_yes", "coa2_m2_begin_yes"}, -- I'll do what is necessary.
		{"@theme_park/alderaan/act2/imperial_missions:m2_begin_no", "coa2_m2_begin_no"}, -- I'm not so sure I'm up to this.
	}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_begin_info1);

coa2_m2_begin_yes = ConvoScreen:new {
	id = "coa2_m2_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_yes_response", -- Go to the slicer's location and recover the encoded message using any means. If you're not skilled in combat, bring some help. Return when you've retrieved the encoded message.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_begin_yes);

coa2_m2_begin_no = ConvoScreen:new {
	id = "coa2_m2_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_begin_no_response", -- That's alright. This sort of work is not for everyone. Come on back if you change your mind though.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_begin_no);

coa2_m2_active = ConvoScreen:new {
	id = "coa2_m2_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active", -- Back again? Don't tell me you're getting cold feet. We have to stop that slicer and intercept that message before he's able to transmit it.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_working", "coa2_m2_active_working"}, -- I'll stop the slicer and get the encoded message.
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_restart", "coa2_m2_active_restart"}, -- I was unable to locate the slicer.
		{"@theme_park/alderaan/act2/imperial_missions:m2_active_abort", "coa2_m2_active_abort"}, -- I can't do this right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_active);

coa2_m2_active_working = ConvoScreen:new {
	id = "coa2_m2_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_working_response", -- That's the spirit. Now get moving!
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_active_working);

coa2_m2_active_restart = ConvoScreen:new {
	id = "coa2_m2_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_restart_response", -- We received intelligence that the slicer was on the move after you had left. We have his new location and I've updated the new location to your datapad.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_active_restart);

coa2_m2_active_abort = ConvoScreen:new {
	id = "coa2_m2_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m2_active_abort_response", -- That's too bad. If you change your mind, please feel free to come back later.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m2_active_abort);

coa2_m3_begin = ConvoScreen:new {
	id = "coa2_m3_begin",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin", -- We need to get that encoded message to the commander. Would you be willing to make the delivery?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m3_begin_yes", "coa2_m3_begin_yes"}, -- I will make the delivery.
		{"@theme_park/alderaan/act2/imperial_missions:m3_begin_no", "coa2_m3_begin_no"}, -- I don't have time for this right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_begin);

coa2_m3_begin_yes = ConvoScreen:new {
	id = "coa2_m3_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin_yes_response", -- Excellent! The commander is currently off world. I've uploaded his location to your datapad. Deliver the encoded message to him at once.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_begin_yes);

coa2_m3_begin_no = ConvoScreen:new {
	id = "coa2_m3_begin_no",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_begin_no_response", -- In that case, come back whenever your busy schedule allows.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_begin_no);

coa2_m3_active = ConvoScreen:new {
	id = "coa2_m3_active",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active", -- You're still here? I've already contacted the Commander so he's expecting you. He's not the type of man you want to keep waiting.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_working", "coa2_m3_active_working"}, -- I'm leaving on the next flight out.
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_restart", "coa2_m3_active_restart"}, -- I seem to have lost the Commander's location.
		{"@theme_park/alderaan/act2/imperial_missions:m3_active_abort", "coa2_m3_active_abort"}, -- I need to do something else right now.
	}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_active);

coa2_m3_active_working = ConvoScreen:new {
	id = "coa2_m3_active_working",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_working_response", -- Glad to hear it. I'm sure he will be very pleased.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_active_working);

coa2_m3_active_restart = ConvoScreen:new {
	id = "coa2_m3_active_restart",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_restart_response", -- These missions are not to be taken lightly! Please be more careful next time. Here, I've uploaded the waypoint to your datapad once again.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_active_restart);

coa2_m3_active_abort = ConvoScreen:new {
	id = "coa2_m3_active_abort",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_active_abort_response", -- How unfortunate. If you have time later on, please see me again. I hope the commander understands for both of our sakes.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_active_abort);

coa2_m3_finish = ConvoScreen:new {
	id = "coa2_m3_finish",
	leftDialog = "@theme_park/alderaan/act2/imperial_missions:m3_finish", -- You've done well and I commend you for your admirable service to the Empire. There is nothing more I need of you at this time.
	stopConversation = "true",
	options = {}
}

imperialCoordinatorConvoTemplate:addScreen(coa2_m3_finish);

addConversationTemplate("imperialCoordinatorConvoTemplate", imperialCoordinatorConvoTemplate);
