function createPetConversationTemplate(personality, templatename)
	pet_convotemplate = ConvoTemplate:new {
		initialScreen = "convoscreenpetinfo",
		templateType = "Personality",
		screens = {}
	}
	pet_convoscreenpetinfo = ConvoScreen:new {
		id = "convoscreenpetinfo",
		leftDialog = "@hireling/"..personality..":start_convo_1",
		stopConversation = "false",
		options = { 
			{"@hireling/"..personality..":command_reply_1", "pet_start_convo_2" },
			{"@hireling/"..personality..":command_group_1", "pet_group_command" }, -- as seen in screen shots
			{"@hireling/"..personality..":command_release", "pet_release_command" }, --as seen in screenshots			
			--{"@hireling/"..personality..":command_group_2", "pet_leave_group_command" },
			-- if needed we add menu_repair_other
		}
	}
	pet_convotemplate:addScreen(pet_convoscreenpetinfo);
	pet_group_command = ConvoScreen:new {
		id = "pet_group_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_group_command)	
	
--[[
	pet_leave_group_command = ConvoScreen:new {
		id = "pet_leve_group_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_leave_group_command)	
--]]
	pet_release_command = ConvoScreen:new {
		id = "pet_release_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_release_command)	
	
	pet_start_conv_2 = ConvoScreen:new {
		id = "pet_start_convo_2",
		leftDialog = "@hireling/"..personality..":start_convo_2",
		stopConversation = "false",
		options= {
			{"@hireling/"..personality..":move_commands",       "pet_move_commands"},
			{"@hireling/"..personality..":patrolling_commands", "pet_patrolling_commands"},
			{"@hireling/"..personality..":formation_commands",  "pet_formation_commands"},
			{"@hireling/"..personality..":friendship_commands", "pet_friendship_commands"},
			{"@hireling/"..personality..":combat_commands",     "pet_combat_commands"},
		}
	}	
	pet_convotemplate:addScreen(pet_start_conv_2)
	pet_repair_command = ConvoScreen:new {
		id = "pet_repair_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_repair_command)	
	
	-- formation commands
	pet_formation_commands = ConvoScreen:new {
		id = 'pet_formation_commands',
		leftDialog = "@hireling/"..personality..":which_command",
		stopConversation = "false",
		options = {
			{"@hireling/"..personality..":command_assume_formation_1","pet_formation_1_command"}, -- wait for player to say something.
			{"@hireling/"..personality..":command_assume_formation_2","pet_formation_2_command"},
		}		
	}
	pet_convotemplate:addScreen(pet_formation_commands)
	pet_formation_1_command = ConvoScreen:new {
		id = "pet_formation_1_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_formation_1_command)	
	pet_formation_2_command = ConvoScreen:new {
		id = "pet_formation_2_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_formation_2_command)	

	-- combat commands
	pet_combat_commands = ConvoScreen:new {
		id = 'pet_combat_commands',
		leftDialog = "@hireling/"..personality..":which_command",
		stopConversation = "false",
		options = {
			{"@hireling/"..personality..":command_attack","pet_attack_command"}, -- wait for player to say something.
			{"@hireling/"..personality..":command_guard","pet_guard_command"},
		}		
	}
	pet_convotemplate:addScreen(pet_combat_commands)
	pet_attack_command = ConvoScreen:new {
		id = "pet_attack_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_attack_command)	
	
	pet_guard_command = ConvoScreen:new {
		id = "pet_guard_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_guard_command)	
	
	-- friendship commands
	pet_friendship_commands = ConvoScreen:new {
		id = 'pet_friendship_commands',
		leftDialog = "@hireling/"..personality..":which_command",
		stopConversation = "false",
		options = {
			{"@hireling/"..personality..":command_friend","pet_friend_command"}, -- wait for player to say something.
			{"@hireling/"..personality..":command_transfer","pet_transfer_command"},
		}		
	}
	pet_convotemplate:addScreen(pet_friendship_commands)
	pet_friend_command = ConvoScreen:new {
		id = "pet_friend_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_friend_command)	
	pet_transfer_command = ConvoScreen:new {
		id = "pet_transfer_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_transfer_command)	

	-- patrolling commands
	pet_patrolling_commands = ConvoScreen:new {
		id = 'pet_patrolling_commands',
		leftDialog = "@hireling/"..personality..":which_command",
		stopConversation = "false",
		options = {
			{"@hireling/"..personality..":command_clear_patrol_points","pet_clear_patrol_points_command"}, -- wait for player to say something.
			{"@hireling/"..personality..":command_get_patrol_point","pet_get_patrol_point_command"},
			{"@hireling/"..personality..":command_patrol","pet_patrol_command"},
		}		
	}
	pet_convotemplate:addScreen(pet_patrolling_commands)
	-- Add 3 pet patrol commands here
	pet_clear_patrol_command = ConvoScreen:new {
		id = "pet_clear_patrol_points_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_clear_patrol_command)	
	pet_get_patrol_command = ConvoScreen:new {
		id = "pet_get_patrol_point_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_get_patrol_command)	
	pet_patrol_command = ConvoScreen:new {
		id = "pet_patrol_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_patrol_command)	
	
	-- movemen commands	
	pet_move_commands = ConvoScreen:new {
		id ="pet_move_commands",
		leftDialog = "@hireling/"..personality..":which_command",
		stopConversation = "false",
		options = {
			{"@hireling/"..personality..":command_stay","pet_stay_command"}, -- wait for player to say something.
			{"@hireling/"..personality..":command_follow","pet_follow_command"},
			{"@hireling/"..personality..":command_follow_other","pet_follow_other_command"},
		}
	}	
	pet_convotemplate:addScreen(pet_move_commands)
	
	pet_stay_command = ConvoScreen:new {
		id = "pet_stay_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_stay_command)	

	pet_follow_command = ConvoScreen:new {
		id = "pet_follow_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_follow_command)

	pet_follow_other_command = ConvoScreen:new {
		id = "pet_follow_other_command",
		leftDialog = "", --"@hireling/"..personality..":start_convo_4",
		stopConversation = "true",
		options = {}
	}
	pet_convotemplate:addScreen(pet_follow_other_command)	
		
	addConversationTemplate(templatename, pet_convotemplate);
end

-- ****** Create personaloty templates with the function above ******
createPetConversationTemplate("hireling_droid_geek", "pet_geek_convotemplate")
createPetConversationTemplate("hireling_droid_prissy", "pet_prissy_convotemplate")
createPetConversationTemplate("hireling_droid_worshipful", "pet_worshipful_convotemplate")
createPetConversationTemplate("hireling_droid_slang", "pet_slang_convotemplate")
createPetConversationTemplate("hireling_droid_stupid", "pet_stupid_convotemplate")
createPetConversationTemplate("hireling_droid_sarcastic", "pet_sarcastic_convotemplate")
createPetConversationTemplate("hireling_military", "pet_militry_convotemplate")
createPetConversationTemplate("hireling_stormtrooper", "pet_stormtrooper_convotemplate")
createPetConversationTemplate("hireling_slang", "pet_nondroid_slang_convotemplate")
createPetConversationTemplate("hireling_fancy", "pet_fancy_convotemplate")
createPetConversationTemplate("", "pet_base_convotemplate")




