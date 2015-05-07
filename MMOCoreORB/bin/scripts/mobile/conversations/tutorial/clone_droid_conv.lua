tutorialCloneDroidConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "tutorialCloneDroidConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_start", -- I'm here to explain Cloning and Insurance. Where would you like to begin?
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_1", "explain_cloning"}, -- Cloning.
		{"@newbie_tutorial/newbie_convo:convo_2_reply_2", "explain_insurance"}, -- Insurance.
	}
}

tutorialCloneDroidConvoTemplate:addScreen(intro);

explain_cloning = ConvoScreen:new {
	id = "explain_cloning",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning", -- If something should happen to you, your clone will take over with all the skills you had at the time you died. Though you always have the option to respawn at the nearest cloning facility, unless you've cloned there you will emerge with many, many wounds.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_3", "when_to_clone"}, -- How often should I clone?
	}
}

tutorialCloneDroidConvoTemplate:addScreen(explain_cloning);

when_to_clone = ConvoScreen:new {
	id = "when_to_clone",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning_2", -- You should clone yourself whenever you want the option to emerge from that particular location. Otherwise you will appear at the closest cloning facility from where you died, with many wounds. You will also need to set a new cloning location when you travel to a new planet, because there is no interplanetary cloning.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_5", "only_to_change_loc"}, -- Do I need to clone again every time I die?
	}
}

tutorialCloneDroidConvoTemplate:addScreen(when_to_clone);

only_to_change_loc = ConvoScreen:new {
	id = "only_to_change_loc",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_cloning_3", -- No. Only when you want to have the option of appearing at a particular location without a lot of wounds, regardless of where you died.
	stopConversation = "true",
	options = {}
}

tutorialCloneDroidConvoTemplate:addScreen(only_to_change_loc);

explain_insurance = ConvoScreen:new {
	id = "explain_insurance",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance", -- Insurance is a way of better preserving the condition of your belongings in the event of your untimely demise. The return of nominally damaged, insured items to a cloning facility fetches a much higher price with the facility at which you choose to clone since you subsidize their item retrieval programs by purchasing insurance.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_4", "increased_decay"}, -- What happens to uninsured items?
	}
}

tutorialCloneDroidConvoTemplate:addScreen(explain_insurance);

increased_decay = ConvoScreen:new {
	id = "increased_decay",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance_2", -- Your items will suffer a significantly increased decay rate when transported back to your clone. People like to be paid, and cloning facilities don't pay much for recovery of uninsured items; so it stands to reason that uninsured items tend to not be cared for as well as their insured counterparts.
	stopConversation = "false",
	options = {
		{"@newbie_tutorial/newbie_convo:convo_2_reply_8", "insure_every_time"}, -- Do I have to insure my items every time I die?
	}
}

tutorialCloneDroidConvoTemplate:addScreen(increased_decay);

insure_every_time = ConvoScreen:new {
	id = "insure_every_time",
	leftDialog = "@newbie_tutorial/newbie_convo:convo_2_insurance_5", -- Yes! Insurance is only valid one time. If you want your items returned to you in a condition similar to last you saw them, you'll have to insure the item again!
	stopConversation = "true",
	options = {}
}

tutorialCloneDroidConvoTemplate:addScreen(insure_every_time);

addConversationTemplate("tutorialCloneDroidConvoTemplate", tutorialCloneDroidConvoTemplate);