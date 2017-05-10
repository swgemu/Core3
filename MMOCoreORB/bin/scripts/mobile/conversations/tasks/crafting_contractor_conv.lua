craftingContractorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "craftingContractorConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/crafting_contractor:s_14e7249", -- Hello there. I contract manufacturing jobs to crafters that are looking for work. The pay is not great, but it's good practice for those that are interested in learning the art of crafting. Are you interested?
	stopConversation = "false",
	options = {
		{"@conversation/crafting_contractor:s_eb7fcc27", "what_sort_of_job"}, -- Yes, I am interested.
		{"@conversation/crafting_contractor:s_b9dc4832", "come_back_for_work"}, -- No, not right now.
	}
}
craftingContractorConvoTemplate:addScreen(init);

what_sort_of_job = ConvoScreen:new {
	id = "what_sort_of_job",
	leftDialog = "@conversation/crafting_contractor:s_404252ce", -- What sort of crafting job are you interested in?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(what_sort_of_job);

job_architect = ConvoScreen:new {
	id = "job_architect",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_architect);

job_armorsmith = ConvoScreen:new {
	id = "job_armorsmith",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_armorsmith);

job_artisan = ConvoScreen:new {
	id = "job_artisan",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_artisan);

job_chef = ConvoScreen:new {
	id = "job_chef",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_chef);

job_droidengineer = ConvoScreen:new {
	id = "job_droidengineer",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_droidengineer);

job_tailor = ConvoScreen:new {
	id = "job_tailor",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_tailor);

job_weaponsmith = ConvoScreen:new {
	id = "job_weaponsmith",
	leftDialog = "@conversation/crafting_contractor:s_8cadb7f", -- How challenging of a task would you like?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(job_weaponsmith);

diff_easy = ConvoScreen:new {
	id = "diff_easy",
	leftDialog = "@conversation/crafting_contractor:s_f58f323c", -- I've got just the job for you. You'll need to craft %DI %TO. Does that sound alright?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(diff_easy);

diff_medium = ConvoScreen:new {
	id = "diff_medium",
	leftDialog = "@conversation/crafting_contractor:s_f58f323c", -- I've got just the job for you. You'll need to craft %DI %TO. Does that sound alright?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(diff_medium);

diff_hard = ConvoScreen:new {
	id = "diff_hard",
	leftDialog = "@conversation/crafting_contractor:s_f58f323c", -- I've got just the job for you. You'll need to craft %DI %TO. Does that sound alright?
	stopConversation = "false",
	options = {
		-- Handled in convo handler
	}
}
craftingContractorConvoTemplate:addScreen(diff_hard);

come_back_for_work = ConvoScreen:new {
	id = "come_back_for_work",
	leftDialog = "@conversation/crafting_contractor:s_73c628e8", -- Alright. Come back if you need the work.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(come_back_for_work);

init_no_artisan = ConvoScreen:new {
	id = "init_no_artisan",
	leftDialog = "@conversation/crafting_contractor:s_e3aab67f", -- I don't think that we have any business to discuss. Good day.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(init_no_artisan);

init_completed_job = ConvoScreen:new {
	id = "init_completed_job",
	leftDialog = "@conversation/crafting_contractor:s_a62477a9", -- You're done with the job? Excellent! I'll just take the crate then. Yes, and here is your payment. I'll bet that was good practice for you, eh?
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(init_completed_job);

init_on_timer = ConvoScreen:new {
	id = "init_on_timer",
	leftDialog = "@conversation/crafting_contractor:s_b3d0de8", -- I'm sorry. I don't have any jobs available right now. Try back again in a minute or two.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(init_on_timer);

init_incomplete_job = ConvoScreen:new {
	id = "init_incomplete_job",
	leftDialog = "@conversation/crafting_contractor:s_d5a1b00c", -- I see that you're back, but it doesn't look like you've finished the job.
	stopConversation = "false",
	options = {
		{"@conversation/crafting_contractor:s_9c7d6f79", "back_when_finished"}, -- I'll get back to work.
		{"@conversation/crafting_contractor:s_bdac2f18", "take_back_crate"}, -- I've changed my mind. I don't want to do this job.
	}
}
craftingContractorConvoTemplate:addScreen(init_incomplete_job);

back_when_finished = ConvoScreen:new {
	id = "back_when_finished",
	leftDialog = "@conversation/crafting_contractor:s_51b72d61", -- OK. Just come back here whenever you're finished.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(back_when_finished);

take_back_crate = ConvoScreen:new {
	id = "take_back_crate",
	leftDialog = "@conversation/crafting_contractor:s_436186dd", -- Alright. I'll take back your crafting crate then. Come back again if you ever need the work.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(take_back_crate);

inv_full = ConvoScreen:new {
	id = "inv_full",
	leftDialog = "@conversation/crafting_contractor:s_82c3e20a", -- It looks like your inventory is full. Talk to me again when you free up some space.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(inv_full);

accept_quest = ConvoScreen:new {
	id = "accept_quest",
	leftDialog = "@conversation/crafting_contractor:s_62092c04", -- Excellent. Here is a crate for you. Simply put the crafted items into it and bring it back to me when it is full. Then I will give you your pay.
	stopConversation = "true",
	options = {}
}
craftingContractorConvoTemplate:addScreen(accept_quest);

addConversationTemplate("craftingContractorConvoTemplate", craftingContractorConvoTemplate);
