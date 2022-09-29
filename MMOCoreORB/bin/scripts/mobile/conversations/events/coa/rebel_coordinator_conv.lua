rebelCoordinatorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rebelCoordinatorConvoHandler",
	screens = {}
}

--[[


	========== CoA3 -- WINNING --  Conversation Options =========


]]

coa3_init_w = ConvoScreen:new {
	id = "coa3_init_w",
	leftDialog = "@conversation/coa3wcoordinator:s_8d99c71a", -- I see you're back. Good job. Everyone's talking about how you were able to break into that relay station and send the Princess' message. Quite a feat. I haven't been fully briefed yet, but I hear Vacca's made his decision. Whichever side he picks, things are going to get interesting. You want to stick around and help? We could use you.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_afc313e6", "coa3_come_out_on_top_w"}, -- I'll do what I can to help.
		{"@conversation/coa3wcoordinator:s_20eec74a", "coa3_must_be_very_busy"}, -- I need to do something else right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_w);

coa3_come_out_on_top_w = ConvoScreen:new {
	id = "coa3_come_out_on_top_w",
	leftDialog = "@conversation/coa3wcoordinator:s_e0227bd9", -- Excellent! If you do as well as last time, we will definitely come out on top. I haven't been briefed on the details so you'll have to go speak with the Information Officer, he'll fill you in. You can find him in the Commerce Guild Hall in this city.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_f595b0cb", "coa3_give_you_report_w"}, -- Ok, I'll go see what he has to say.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_come_out_on_top_w);

coa3_give_you_report_w = ConvoScreen:new {
	id = "coa3_give_you_report_w",
	leftDialog = "@conversation/coa3wcoordinator:s_4f6ac618", -- Good. He'll give you a status report. By the time you return from the Commerce Guild Hall I should have updated intel on our next move. See you soon.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_give_you_report_w);


-- Player sent to information officer, but has not spoken to them yet


coa3_init_go_to_info_w = ConvoScreen:new {
	id = "coa3_init_go_to_info_w",
	leftDialog = "@conversation/coa3wcoordinator:s_6837ec87", -- Oh it's you again! I didn't expect to see you so soon. Unfortunately, I'm still crunching some data right now. Why don't you go and speak with our Information Officer. You can find him in the Commerce Guild in this city. Get all details from him about our current situation and by the time you're done with that, I should be done analyzing this data.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_go_to_info_w);


-- Player has spoken to Information Officer


coa3_init_completed_info_w = ConvoScreen:new {
	id = "coa3_init_completed_info_w",
	leftDialog = "@conversation/coa3wcoordinator:s_4ba81cc8", -- Ah good, you're back! I've finished analyzing the data from our most recent intelligence and it looks pretty promising. I think we are ready to proceed with our plan. I'll need you to go undercover. If you're successful you probably won't need to fire a single shot. If you fail, that's a different story and we're back to square one. Do you have any questions?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_b4f92479", "coa3_cornered_market_w"}, -- What are the details of this mission?
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3wcoordinator:s_28de3a91", "coa3_pose_as_them_w"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_completed_info_w);

coa3_pose_as_them_w = ConvoScreen:new {
	id = "coa3_pose_as_them_w",
	leftDialog = "@conversation/coa3wcoordinator:s_26b400f9", -- Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_pose_as_them_w);

coa3_cornered_market_w = ConvoScreen:new {
	id = "coa3_cornered_market_w",
	leftDialog = "@conversation/coa3wcoordinator:s_ad11a99b", -- As I'm sure you know various underworld organizations have all but cornered the market on this Alderaanian Flora. As to be expected, Jabba the Hutt has come out ahead in this game and he seems to be the one doing the most business. This flora is enormously valuable so obviously Jabba's rivals are taking every opportunity to hijack any shipments they come across. Knowing this, Jabba is using a decentralized system of storage and transport to cut down on losses.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_efdb954e", "coa3_traffic_flora_w"}, -- Ok, go on.
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3wcoordinator:s_28de3a91", "coa3_pose_as_them_w"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_cornered_market_w);

coa3_traffic_flora_w = ConvoScreen:new {
	id = "coa3_traffic_flora_w",
	leftDialog = "@conversation/coa3wcoordinator:s_4724fd7d", -- He's using land vehicles to traffic the flora to and from the storehouses with a complex system of lookouts scattered along the routes. If any trouble is spotted, the caravans are alerted and they use a different route. It's all very organized. The intelligence I just analyzed reveals the location of all the lookouts on the planet and it indicates a caravan is to make a delivery today. Predicting the caravan's destination is simply impossible. This is where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_19d2e135", "coa3_gather_information_w"}, -- Interesting. Please continue.
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3wcoordinator:s_28de3a91", "coa3_pose_as_them_w"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_traffic_flora_w);

coa3_gather_information_w = ConvoScreen:new {
	id = "coa3_gather_information_w",
	leftDialog = "@conversation/coa3wcoordinator:s_1fd11fc5", -- They are so cautious that caravans have been known to zig zag and circle for hours before finally heading to their destination unless things are completely safe. Simple observation won't tell us anything, so we need you to pose as a member of their organization and try to gather information about where that caravan is headed. We need hard information; disks, papers, whatever you can find. As you can imagine, this will be dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_4ca03ddb", "coa3_incredibly_suspicious_w"}, -- How so?
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3wcoordinator:s_28de3a91", "coa3_pose_as_them_w"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_gather_information_w);

coa3_incredibly_suspicious_w = ConvoScreen:new {
	id = "coa3_incredibly_suspicious_w",
	leftDialog = "@conversation/coa3wcoordinator:s_1f81bc3c", -- These people are incredibly suspicious so you'll need to be very convincing. If they suspect you they won't hesitate to attack. If that happens, then I'm afraid we'll have to start over and try it again. Are you prepared to take on this task?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_d55f2579", "coa3_uploaded_lookout_location_w"}, -- I'm ready to go.
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_incredibly_suspicious_w);

coa3_uploaded_lookout_location_w = ConvoScreen:new {
	id = "coa3_uploaded_lookout_location_w",
	leftDialog = "@conversation/coa3wcoordinator:s_eae61031", -- Great! I've uploaded the location of one of their lookouts to your datapad. Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_uploaded_lookout_location_w);


-- Player has been sent on lookout mission

-- Player does not have disk yet
coa3_init_has_lookout_w = ConvoScreen:new {
	id = "coa3_init_has_lookout_w",
	leftDialog = "@conversation/coa3wcoordinator:s_882bc6e0", -- Well, how did things go?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_a6f2327f", "coa3_cornered_market_reminder"}, -- What were the details of the mission again?
		{"@conversation/coa3wcoordinator:s_7b9e2f5e", "coa3_ran_into_trouble"}, -- Can I have another waypoint?
		{"@conversation/coa3wcoordinator:s_75565d5a", "coa3_friendly_first"}, -- Any hints?
		{"@conversation/coa3wcoordinator:s_36142d2b", "coa3_come_back_later"}, -- I can't do this right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_has_lookout_w);

-- Player has disk, given coa3_init_has_disk. Sent to tactical Officer.

-- Player has complete the Tactical officers missions

coa3_init_go_to_princess_w = ConvoScreen:new {
	id = "coa3_init_go_to_princess_w",
	leftDialog = "@conversation/coa3wcoordinator:s_c9282e23", -- Have you been to see the Princess yet? You probably don't want to keep her waiting. Anyway, was there something I can help you with right now?
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_bc0e9972", "coa3_leave_soon"}, -- Nothing for right now, thanks.
		{"@conversation/coa3wcoordinator:s_52cc7bda", "coa3_thought_was_correct"}, -- Are you sure that waypoint was correct?
		{"@conversation/coa3wcoordinator:s_315ff574", "coa3_thats_a_shame"}, -- I can't make it there right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_go_to_princess_w);

coa3_init_complete_w = ConvoScreen:new {
	id = "coa3_init_complete_w",
	leftDialog = "@conversation/coa3wcoordinator:s_e2c3d142", -- Good to see you again. Thanks to your efforts we stand a good chance of finding an alternative source of flora for Dead Eye. You're to be commended. I don't have anything else I need from you right now, but you might ask our Tactical Officer at the Combat Guild if he still needs helping tracking down and destroying those warehouses.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_complete_w);

--[[


	========== CoA3 -- LOSING --  Conversation Options =========


]]

-- Pre-Informant
coa3_init_l = ConvoScreen:new {
	id = "coa3_init_l",
	leftDialog = "@conversation/coa3lcoordinator:s_20ad68cd", -- It's a pleasure seeing you again, thank you for coming! Actually, I'm not surprised considering you have been in the middle of this whole Dead-Eye situation from the beginning. Your work so far has been top-notch and you haven't failed us yet. Would you be willing to accept another mission?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_c4ae7e31", "coa3_come_out_on_top_l"}, -- I'd love to help out again.
		{"@conversation/coa3lcoordinator:s_20eec74a", "coa3_must_be_very_busy"}, -- I need to do something else right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_l);

coa3_come_out_on_top_l = ConvoScreen:new {
	id = "coa3_come_out_on_top_l",
	leftDialog = "@conversation/coa3lcoordinator:s_976a6f0", -- Great! A lot has happened since we last spoke. I don't have time to go over all of the details with you right now. Go and speak with our Information Officer and listen to what he has to say. You can find him in the Commerce Guild Hall in this city.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_f595b0cb", "coa3_give_you_report_l"}, -- Ok, I'll go see what he has to say.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_come_out_on_top_l);

coa3_give_you_report_l = ConvoScreen:new {
	id = "coa3_give_you_report_l",
	leftDialog = "@conversation/coa3lcoordinator:s_223c5db", -- Great, once you get all filled in on the details feel free to come back and see me. I'm not quite finished with what I'm working on but I think I may need to call upon your top notch talents once again.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_give_you_report_l);


-- Player sent to informant, but has not spoken to them yet


coa3_init_go_to_info_l = ConvoScreen:new {
	id = "coa3_init_go_to_info_l",
	leftDialog = "@conversation/coa3lcoordinator:s_6837ec87", -- Oh it's you again! I didn't expect to see you so soon. Unfortunately, I'm still crunching some data right now. Why don't you go and speak with our Information Officer. You can find him in the Commerce Guild in this city. Get all details from him about our current situation and by the time you're done with that, I should be done analyzing this data.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_go_to_info_l);


-- Player Goes to Informant


coa3_init_completed_info_l = ConvoScreen:new {
	id = "coa3_init_completed_info_l",
	leftDialog = "@conversation/coa3lcoordinator:s_4ba81cc8", --  Ah good, you're back! I've finished analyzing the data from our most recent intelligence and it looks pretty promising. I think we are ready to proceed with our plan. I'll need you to go undercover. If you're successful you probably won't need to fire a single shot. If you fail, that's a different story and we're back to square one. Do you have any questions?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_b4f92479", "coa3_cornered_market_l"}, -- What are the details of this mission?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them_l"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_completed_info_l);

coa3_pose_as_them_l = ConvoScreen:new {
	id = "coa3_pose_as_them_l",
	leftDialog = "@conversation/coa3lcoordinator:s_26b400f9", -- Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_pose_as_them_l);

coa3_cornered_market_l = ConvoScreen:new {
	id = "coa3_cornered_market_l",
	leftDialog = "@conversation/coa3lcoordinator:s_ad11a99b", -- As I'm sure you know various underworld organizations have all but cornered the market on this Alderaanian Flora. As to be expected, Jabba the Hutt has come out ahead in this game and he seems to be the one doing the most business. This flora is enormously valuable so obviously Jabba's rivals are taking every opportunity to hijack any shipments they come across. Knowing this, Jabba is using a decentralized system of storage and transport to cut down on losses.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_efdb954e", "coa3_traffic_flora_l"}, -- Ok, go on.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them_l"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_cornered_market_l);

coa3_traffic_flora_l = ConvoScreen:new {
	id = "coa3_traffic_flora_l",
	leftDialog = "@conversation/coa3lcoordinator:s_4724fd7d", -- He's using land vehicles to traffic the flora to and from the storehouses with a complex system of lookouts scattered along the routes. If any trouble is spotted, the caravans are alerted and they use a different route. It's all very organized. The intelligence I just analyzed reveals the location of all the lookouts on the planet and it indicates a caravan is to make a delivery today. Predicting the caravan's destination is simply impossible. This is where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_19d2e135", "coa3_gather_information_l"}, -- Interesting. Please continue.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them_l"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_traffic_flora_l);

coa3_gather_information_l = ConvoScreen:new {
	id = "coa3_gather_information_l",
	leftDialog = "@conversation/coa3lcoordinator:s_1fd11fc5", -- They are so cautious that caravans have been known to zig zag and circle for hours before finally heading to their destination unless things are completely safe. Simple observation won't tell us anything, so we need you to pose as a member of their organization and try to gather information about where that caravan is headed. We need hard information; disks, papers, whatever you can find. As you can imagine, this will be dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_4ca03ddb", "coa3_incredibly_suspicious_l"}, -- How so?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
		{"@conversation/coa3lcoordinator:s_28de3a91", "coa3_pose_as_them"}, -- Enough details, I'm ready to go.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_gather_information_l);

coa3_incredibly_suspicious_l = ConvoScreen:new {
	id = "coa3_incredibly_suspicious_l",
	leftDialog = "@conversation/coa3lcoordinator:s_1f81bc3c", -- These people are incredibly suspicious so you'll need to be very convincing. If they suspect you they won't hesitate to attack. If that happens, then I'm afraid we'll have to start over and try it again. Are you prepared to take on this task?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_d55f2579", "coa3_uploaded_lookout_location"}, -- I'm ready to go.
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_when_ready"}, -- I can't do this right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_incredibly_suspicious_l);

coa3_uploaded_lookout_location_l = ConvoScreen:new {
	id = "coa3_uploaded_lookout_location_l",
	leftDialog = "@conversation/coa3lcoordinator:s_26b400f9", -- Pose as one of them and do whatever you can to get your hands on some hard data about that caravan. Things like papers, manifests or disks. Come back as soon as you find something. Be careful and remember to think like a thug. If things go bad, you'll have no choice but to fight. Should that happen, come back and we can try it again.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_uploaded_lookout_location_l);

-- Player has been sent on lookout mission

-- Player does not have disk yet
coa3_init_has_lookout_l = ConvoScreen:new {
	id = "coa3_init_has_lookout_l",
	leftDialog = "@conversation/coa3lcoordinator:s_882bc6e0", -- Well, how did things go?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_a6f2327f", "coa3_cornered_market_reminder"}, -- What were the details of the mission again?
		{"@conversation/coa3lcoordinator:s_7b9e2f5e", "coa3_ran_into_trouble"}, -- Can I have another waypoint?
		{"@conversation/coa3lcoordinator:s_80af7773", "coa3_friendly_first"}, -- Got any advice for me?
		{"@conversation/coa3lcoordinator:s_36142d2b", "coa3_come_back_later"}, -- I can't do this right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_has_lookout_l);

-- Player has disk, given coa3_init_has_disk. Sent to tactical Officer.
-- Player has complete the Tactical officers missions

coa3_init_go_to_princess_l = ConvoScreen:new {
	id = "coa3_init_go_to_princess_l",
	leftDialog = "@conversation/coa3lcoordinator:s_c9282e23", -- Have you been to see the Princess yet? You probably don't want to keep her waiting. Anyway, was there something I can help you with right now?
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_bc0e9972", "coa3_leave_soon"}, -- Nothing for right now, thanks.
		{"@conversation/coa3lcoordinator:s_52cc7bda", "coa3_thought_was_correct"}, -- Are you sure that waypoint was correct?
		{"@conversation/coa3lcoordinator:s_315ff574", "coa3_thats_a_shame"}, -- I can't make it there right now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_go_to_princess_l);

coa3_init_complete_l = ConvoScreen:new {
	id = "coa3_init_complete_l",
	leftDialog = "@conversation/coa3lcoordinator:s_e2c3d142", -- Good to see you again. Thanks to your efforts we stand a good chance of finding an alternative source of flora for Dead Eye. You're to be commended. I don't have anything else I need from you right now, but you might ask our Tactical Officer at the Combat Guild if he still needs helping tracking down and destroying those warehouses.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_complete_l);










--[[


	========== Generic and Multi-Use Responses =========


]]

coa3_come_back_when_ready = ConvoScreen:new {
	id = "coa3_come_back_when_ready",
	leftDialog = "@conversation/coa3wcoordinator:s_37281366", -- I understand. I wouldn't want you to take on this mission unless you are completely prepared. Come back when you are ready.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_come_back_when_ready);

coa3_init_has_disk = ConvoScreen:new {
	id = "coa3_init_has_disk",
	leftDialog = "@conversation/coa3wcoordinator:s_fec795", -- Excellent work! To be honest, I didn't think you could pull it off. You must have done some real smooth talking! I'll start analyzing the disk right away but it is going to take some time. Why don't you go and speak with the Tactical Officer, I believe he has something for you to do. You can find him in the Combat Guild of this city.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_has_disk);

coa3_come_back_later = ConvoScreen:new {
	id = "coa3_come_back_later",
	leftDialog = "@conversation/coa3wcoordinator:s_a3ea7bf6", -- I'm sorry to hear that. Come back later if you change your mind.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_come_back_later);

coa3_leave_soon = ConvoScreen:new {
	id = "coa3_leave_soon",
	leftDialog = "@conversation/coa3wcoordinator:s_ecae16e7", -- Ok, carry on. You should probably leave soon though.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_leave_soon);

coa3_thought_was_correct = ConvoScreen:new {
	id = "coa3_thought_was_correct",
	leftDialog = "@conversation/coa3wcoordinator:s_cd603241", -- I thought that it was correct. I'll update your datapad again just to be safe.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_thought_was_correct);

coa3_thats_a_shame = ConvoScreen:new {
	id = "coa3_thats_a_shame",
	leftDialog = "@conversation/coa3wcoordinator:s_45cbfb7d", -- Well that's a shame. If you change your mind, please let me know.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_thats_a_shame);

coa3_ran_into_trouble = ConvoScreen:new {
	id = "coa3_ran_into_trouble",
	leftDialog = "@conversation/coa3wcoordinator:s_8ee9343e", -- Ran into trouble did you? Well there are plenty of lookouts out there still. Here is the location of another one. Come back as soon as you find any sort of hard data about that caravan and maybe we can determine where it was heading. Good luck to you!
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_ran_into_trouble);

coa3_friendly_first = ConvoScreen:new {
	id = "coa3_friendly_first",
	leftDialog = "@conversation/coa3wcoordinator:s_cf35e3d5", -- A direct approach might get you killed. You'll need to get friendly with them first and then maybe they will trust you and open up. Think like a thug. Thugs are generally greedy, selfish, out for themselves. They like things like drinking, gambling, cheating, carousing; that sort of thing.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_friendly_first);

coa3_must_be_very_busy = ConvoScreen:new {
	id = "coa3_must_be_very_busy",
	leftDialog = "@conversation/coa3wcoordinator:s_fb75278f", -- I understand. You must be a very busy person. We haven't forgotten about what you did for us last time and we don't want to put you out. We really could use your help though. Come back if you change your mind and see me. I'm sure we can use your talents.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_must_be_very_busy);

coa3_cornered_market_reminder = ConvoScreen:new {
	id = "coa3_cornered_market_reminder",
	leftDialog = "@conversation/coa3wcoordinator:s_ad11a99b", -- As I'm sure you know various underworld organizations have all but cornered the market on this Alderaanian Flora. As to be expected, Jabba the Hutt has come out ahead in this game and he seems to be the one doing the most business. This flora is enormously valuable so obviously Jabba's rivals are taking every opportunity to hijack any shipments they come across. Knowing this, Jabba is using a decentralized system of storage and transport to cut down on losses.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_efdb954e", "coa3_traffic_flora_reminder"}, -- Ok, go on.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_cornered_market_reminder);

coa3_traffic_flora_reminder = ConvoScreen:new {
	id = "coa3_traffic_flora_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_4724fd7d", -- He's using land vehicles to traffic the flora to and from the storehouses with a complex system of lookouts scattered along the routes. If any trouble is spotted, the caravans are alerted and they use a different route. It's all very organized. The intelligence I just analyzed reveals the location of all the lookouts on the planet and it indicates a caravan is to make a delivery today. Predicting the caravan's destination is simply impossible. This is where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_19d2e135", "coa3_gather_information_reminder"}, -- Interesting. Please continue.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_traffic_flora_reminder);

coa3_gather_information_reminder = ConvoScreen:new {
	id = "coa3_gather_information_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_1fd11fc5", -- They are so cautious that caravans have been known to zig zag and circle for hours before finally heading to their destination unless things are completely safe. Simple observation won't tell us anything, so we need you to pose as a member of their organization and try to gather information about where that caravan is headed. We need hard information; disks, papers, whatever you can find. As you can imagine, this will be dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/coa3lcoordinator:s_4ca03ddb", "coa3_incredibly_suspicious_reminder"}, -- How so?
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_gather_information_reminder);

coa3_incredibly_suspicious_reminder = ConvoScreen:new {
	id = "coa3_incredibly_suspicious_reminder",
	leftDialog = "@conversation/coa3lcoordinator:s_1f81bc3c", -- These people are incredibly suspicious so you'll need to be very convincing. If they suspect you they won't hesitate to attack. If that happens, then I'm afraid we'll have to start over and try it again. Are you prepared to take on this task?
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_incredibly_suspicious_reminder);

coa3_init_go_to_tact = ConvoScreen:new {
	id = "coa3_init_go_to_tact",
	leftDialog = "@conversation/coa3wcoordinator:s_19d54dc3", -- Back so soon? I'm still trying to break the encryption on this disk. It's going to take me some time. In the mean time, go and speak with the Tactical Officer. You can find him in the Combat Guild in this city. I'm sure he has plenty that needs to be done.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_go_to_tact);

coa3_init_completed_tact = ConvoScreen:new {
	id = "coa3_init_completed_tact",
	leftDialog = "@conversation/coa3wcoordinator:s_fa0fdb09", -- Great to see you again. Those disks you acquired have been of great help to our Tactical Officer. He'll be able to assign as many assault missions as you can take, but there is something of more importance if you're up for it.
	stopConversation = "false",
	options = {
		{"@conversation/coa3wcoordinator:s_f35aaa26", "coa3_big_impression"}, -- I'm up for anything.
		{"@conversation/coa3wcoordinator:s_d819b34e", "coa3_count_on_support"}, -- I'm not able to do this now.
	}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_init_completed_tact);

coa3_big_impression = ConvoScreen:new {
	id = "coa3_big_impression",
	leftDialog = "@conversation/coa3wcoordinator:s_a97e415d", -- I thought you'd say that. You've made a big impression and the Princess has decided to oversee the operation herself. She said she wanted to speak with you personally about it. I've added a waypoint to your datapad with the location of the off-world headquarters. I'd head there at once so you don't keep her waiting.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_big_impression);

coa3_count_on_support = ConvoScreen:new {
	id = "coa3_count_on_support",
	leftDialog = "@conversation/coa3wcoordinator:s_740fcda6", -- That's too bad, I was hoping I could count on your support with this. The offer still stands if you change your mind.
	stopConversation = "true",
	options = {}
}
rebelCoordinatorConvoTemplate:addScreen(coa3_count_on_support);

generic_response = ConvoScreen:new {
	id = "generic_response",
	leftDialog = "@recruiting/rebel_recruit:rr13", -- Hello friend. What can I do for you?
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(generic_response);

begin_wrong_faction = ConvoScreen:new {
	id = "begin_wrong_faction",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:coordinator_imperial_response", -- You seem to be more interested in helping the Empire. Why don't you come back when you've come to your senses.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(begin_wrong_faction);

--[[



	========== CoA2 Conversation Options =========



]]

coa2_m1_begin = ConvoScreen:new {
	id = "coa2_m1_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin", -- I hope you're here to help. We're stretched thin looking for Skimmer.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_info1", "coa2_m1_begin_info1"}, -- What's going on?
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_yes", "coa2_m1_begin_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_no", "coa2_m1_begin_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_begin);

coa2_m1_begin_info1 = ConvoScreen:new {
	id = "coa2_m1_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_info1_response", -- We're trying to locate one of our operatives code named Skimmer and we have a lot of tips to follow up. It has to do with this Dead Eye project we've been hearing about.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_yes", "coa2_m1_begin_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_begin_no", "coa2_m1_begin_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_begin_info1);

coa2_m1_begin_yes = ConvoScreen:new {
	id = "coa2_m1_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_yes_response", -- Great! We think Skimmer may have recently contacted one of her close friends. Go to these coordinates and see of Skimmer has been in touch and report back here with any information you uncover.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_begin_yes);

coa2_m1_begin_no = ConvoScreen:new {
	id = "coa2_m1_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_begin_no_response", -- I'm sorry to hear that. Skimmer's stumbled onto something big. If you change your mind, let me know.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_begin_no);

coa2_m1_refused = ConvoScreen:new {
	id = "coa2_m1_refused",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused", -- I hope you've changed your mind and can help us out. We need every loyal operative we can find right now.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_info1", "coa2_m1_refused_info1"}, -- What's going on?
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_yes", "coa2_m1_refused_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_no", "coa2_m1_refused_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_refused);

coa2_m1_refused_info1 = ConvoScreen:new {
	id = "coa2_m1_refused_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_info1_response", -- We're trying to locate one of our operatives code named Skimmer and we have a lot of tips to follow up. It has to do with this Dead Eye project we've been hearing about.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_yes", "coa2_m1_refused_yes"}, -- I'd like to help.
		{"@theme_park/alderaan/act2/rebel_missions:m1_refused_no", "coa2_m1_refused_no"}, -- I'm not ready to help yet.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_refused_info1);

coa2_m1_refused_yes = ConvoScreen:new {
	id = "coa2_m1_refused_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_yes_response", -- Great! We think Skimmer may have recently contacted one of her close friends. Go to these coordinates and see of Skimmer has been in touch and report back here with any information you uncover.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_refused_yes);

coa2_m1_refused_no = ConvoScreen:new {
	id = "coa2_m1_refused_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_refused_no_response", -- I'm sorry to hear that. Skimmer's stumbled onto something big. If you change your mind, let me know.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_refused_no);

coa2_m1_active = ConvoScreen:new {
	id = "coa2_m1_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active", -- Have you talked to Skimmer's friend yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_working", "coa2_m1_active_working"}, -- I'm still looking for her.
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_abort", "coa2_m1_active_abort"}, -- I'm not going to be able to finish the mission.
		{"@theme_park/alderaan/act2/rebel_missions:m1_active_restart", "coa2_m1_active_restart"}, -- I need my mission profile updated.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_active);

coa2_m1_active_working = ConvoScreen:new {
	id = "coa2_m1_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_working_response", -- Time's of the essence here, so do your best.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_active_working);

coa2_m1_active_abort = ConvoScreen:new {
	id = "coa2_m1_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_abort_response", -- I understand. Come find me if you change your mind. We need a lot of help on this one.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_active_abort);

coa2_m1_active_restart = ConvoScreen:new {
	id = "coa2_m1_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_active_restart_response", -- Very well. I've uploaded our latest intel to your datapad. You should be able to continue your mission now. May the Force be with you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_active_restart);

coa2_m1_finish_encoded = ConvoScreen:new {
	id = "coa2_m1_finish_encoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_finish_encoded", -- Good Work! Wait a pulse, this disk has been locked with an old Imperial code! We have schematics for this model of coder, but the parts are obsolete. I bet only local gangs or scavengers would have some of this stuff. I'll give you the schematics, but you'll have to locate the parts and put a decoder together before we can read this intel. Report back to me when you have the disk decoded.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_finish_encoded);

coa2_m1_finish_decoded = ConvoScreen:new {
	id = "coa2_m1_finish_decoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m1_finish_decoded", -- Good work. We'll analyze this information and decide on a plan. Come back in a little while and we'll have more information for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m1_finish_decoded);

coa2_m2_begin_encoded = ConvoScreen:new {
	id = "coa2_m2_begin_encoded",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_encoded", -- I'm very busy coordinating missions. Unless you have a decoded Dead Eye data disk for me, there's not much to discuss. Come back when you've decoded it.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin_encoded);

coa2_m2_begin = ConvoScreen:new {
	id = "coa2_m2_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin", -- Excellent. This message is from Skimmer. She's hiding outside the city and says she has information on Dead Eye. Can you head to these coordinates and make sure she's still there? We don't want to send a team to a place she left twelve cycles ago.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "coa2_m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info1", "coa2_m2_begin_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info2", "coa2_m2_begin_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "coa2_m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin);

coa2_m2_begin_info1 = ConvoScreen:new {
	id = "coa2_m2_begin_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_info1_response", -- Not much. She's related to two Alliance pilots who died flying for us. Her brother was on Alderaan when it was destroyed by the Empire. Later her father was killed during the assault on the Death Star. I just hope he got a chance to know it was destroyed before his Y-wing was blown up.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "coa2_m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info2", "coa2_m2_begin_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "coa2_m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin_info1);

coa2_m2_begin_info2 = ConvoScreen:new {
	id = "coa2_m2_begin_info2",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_info2_response", -- Don't know. Not much data on it yet. All I know is that I don't want the Imperials to be any more accurate than they already are. I'd like to get Dr. Vacca on our side if we could.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_yes", "coa2_m2_begin_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_info1", "coa2_m2_begin_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_begin_no", "coa2_m2_begin_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin_info2);

coa2_m2_begin_yes = ConvoScreen:new {
	id = "coa2_m2_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_yes_response", -- Excellent. Make sure she's still there and then report back to me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin_yes);

coa2_m2_begin_no = ConvoScreen:new {
	id = "coa2_m2_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_begin_no_response", -- I understand. If you change your mind, come find me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_begin_no);

coa2_m2_refused = ConvoScreen:new {
	id = "coa2_m2_refused",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused", -- I hope you've changed your mind about helping us find Skimmer. She's still out there somewhere and we need to find her before the Imperials do. Are you willing to help?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "coa2_m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info1", "coa2_m2_refused_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info2", "coa2_m2_refused_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "coa2_m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_refused);

coa2_m2_refused_info1 = ConvoScreen:new {
	id = "coa2_m2_refused_info1",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_info1_response", -- Not much. She's related to two Alliance pilots who died flying for us. Her brother was on Alderaan when it was destroyed by the Empire. Later her father was killed during the assault on the Death Star. I just hope he got a chance to know it was destroyed before his B-wing was blown up.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "coa2_m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info2", "coa2_m2_refused_info2"}, -- What do you think of this Dead Eye project?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "coa2_m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_refused_info1);

coa2_m2_refused_info2 = ConvoScreen:new {
	id = "coa2_m2_refused_info2",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_info2_response", -- Don't know. Not much data on it yet. All I know is that I don't want the Imperials to be any more accurate than they already are. I'd like to get Dr. Vacca on our side if we could.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_yes", "coa2_m2_refused_yes"}, -- I'll go find her.
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_info1", "coa2_m2_refused_info1"}, -- What do you know about Skimmer?
		{"@theme_park/alderaan/act2/rebel_missions:m2_refused_no", "coa2_m2_refused_no"}, -- I don't have the time to do that now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_refused_info2);

coa2_m2_refused_yes = ConvoScreen:new {
	id = "coa2_m2_refused_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_yes_response", -- Excellent. Make sure she's still there and then report back to me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_refused_yes);

coa2_m2_refused_no = ConvoScreen:new {
	id = "coa2_m2_refused_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_refused_no_response", -- I understand. If you change your mind, come find me.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_refused_no);

coa2_m2_active = ConvoScreen:new {
	id = "coa2_m2_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active", -- Have you found skimmer yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_working", "coa2_m2_active_working"}, -- Not yet. I'm working on it.
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_abort", "coa2_m2_active_abort"}, -- I'm not going to be able to finish the mission.
		{"@theme_park/alderaan/act2/rebel_missions:m2_active_restart", "coa2_m2_active_restart"}, -- I think I need updated intel.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_active);

coa2_m2_active_working = ConvoScreen:new {
	id = "coa2_m2_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_working_response", -- The imperials are after her, so don't waste any time.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_active_working);

coa2_m2_active_abort = ConvoScreen:new {
	id = "coa2_m2_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_abort_response", -- I understand. Come find me if you change your mind. We need a lot of help on this one.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_active_abort);

coa2_m2_active_restart = ConvoScreen:new {
	id = "coa2_m2_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_active_restart_response", -- Things change out in the field. I'll upload our latest information to your datapad. Done. You've got our latest information. Good luck.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_active_restart);

coa2_m2_finish = ConvoScreen:new {
	id = "coa2_m2_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish", -- Lyda's alive? Thank the stars. We'll send out a team to get her right away. You do good work. If you're up for it we need someone to deliver this disk and report to one of our Rebel Commanders about Lyda and project Dead Eye.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m2_finish_yes", "coa2_m2_finish_yes"}, -- I'm up for anything
		{"@theme_park/alderaan/act2/rebel_missions:m2_finish_no", "coa2_m2_finish_no"}, -- I can't help you right now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_finish);

coa2_m2_finish_yes = ConvoScreen:new {
	id = "coa2_m2_finish_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish_yes_response", -- Good. I'll give you the coordinates of the Commander's current location. Bring him the disk and he'll take over from there.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_finish_yes);

coa2_m2_finish_no = ConvoScreen:new {
	id = "coa2_m2_finish_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m2_finish_no_response", -- I'm sorry to hear that. If you change your mind, come back. I'll have something for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m2_finish_no);

coa2_m3_begin = ConvoScreen:new {
	id = "coa2_m3_begin",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin", -- If you're available we still need someone to bring this information about Lyda and Dead Eye to our commander. He may have another mission for you if you're willing to do some traveling.
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m3_begin_yes", "coa2_m3_begin_yes"}, -- I'm up for anything.
		{"@theme_park/alderaan/act2/rebel_missions:m3_begin_no", "coa2_m3_begin_no"}, -- I can't help you right now.
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_begin);

coa2_m3_begin_yes = ConvoScreen:new {
	id = "coa2_m3_begin_yes",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin_yes_response", -- Good. I'll give you the coordinates of the Commander's current location. Bring him the disk and he'll take over from there.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_begin_yes);

coa2_m3_begin_no = ConvoScreen:new {
	id = "coa2_m3_begin_no",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_begin_no_response", -- I'm sorry to hear that. If you change your mind, come back. I'll have something for you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_begin_no);

coa2_m3_active = ConvoScreen:new {
	id = "coa2_m3_active",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active", -- Have you finished the mission yet?
	stopConversation = "false",
	options = {
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_working", "coa2_m3_active_working"}, -- Not yet. I'm working on it.
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_abort", "coa2_m3_active_abort"}, -- I'm not able to do this mission now.
		{"@theme_park/alderaan/act2/rebel_missions:m3_active_restart", "coa2_m3_active_restart"}, -- I need the location of the Commander again
	}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_active);

coa2_m3_active_working = ConvoScreen:new {
	id = "coa2_m3_active_working",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_working_response", -- Keep up the good work. We're counting on you.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_active_working);

coa2_m3_active_abort = ConvoScreen:new {
	id = "coa2_m3_active_abort",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_abort_response", -- I'm not able to do this mission now.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_active_abort);

coa2_m3_active_restart = ConvoScreen:new {
	id = "coa2_m3_active_restart",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_active_restart_response", -- Data pad troubles? That happens I suppose. I'll give you updated coordinates, but don't lose it again.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_active_restart);

coa2_m3_finish = ConvoScreen:new {
	id = "coa2_m3_finish",
	leftDialog = "@theme_park/alderaan/act2/rebel_missions:m3_finish", -- I heard from the Commander that you were able to find him. I hope the mission went well. We could use some good news around here.
	stopConversation = "true",
	options = {}
}

rebelCoordinatorConvoTemplate:addScreen(coa2_m3_finish);

addConversationTemplate("rebelCoordinatorConvoTemplate", rebelCoordinatorConvoTemplate);
