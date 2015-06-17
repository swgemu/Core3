fsVillageConvo6MaleTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "fsVillageConvo6MaleHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/fs_village_convo6_m:s_98f1d36", -- Hey, you a trader? I got an artifact here.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_564850b4", "ancient_jedi_artifact" }, -- What kind of artifact? I might be interested.
		{ "@conversation/fs_village_convo6_m:s_8ce975f3", "trader_came_through" }, -- How would a dirt farmer out in the middle of nowhere get an artifact?
		{ "@conversation/fs_village_convo6_m:s_f39a113e", "artifacts_explode" }, -- Artifact, eh? Try not to blow up anyone I know.
	}
}
fsVillageConvo6MaleTemplate:addScreen(intro);

ancient_jedi_artifact = ConvoScreen:new {
	id = "ancient_jedi_artifact",
	leftDialog = "@conversation/fs_village_convo6_m:s_af4a93c0", -- It's an ancient Jedi artifact, used in their rituals.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_bf977dc7", "activated_by_force" }, -- Jedi don't have rituals. Let's see this artifact.
		{ "@conversation/fs_village_convo6_m:s_223add4d", "great_temples" }, -- I didn't know Jedi had rituals. What more can you tell me?
	}
}
fsVillageConvo6MaleTemplate:addScreen(ancient_jedi_artifact);

activated_by_force = ConvoScreen:new {
	id = "activated_by_force",
	leftDialog = "@conversation/fs_village_convo6_m:s_2d2307c4", -- See here! It's an artifact. it glows when you hold it. I think it's activated by the Force.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_cd1f47c5", "what_do_you_know" }, -- That's not an artifact friend. It's a glowcrystal. You can buy them for 10 credits.
	}
}
fsVillageConvo6MaleTemplate:addScreen(activated_by_force);

what_do_you_know = ConvoScreen:new {
	id = "what_do_you_know",
	leftDialog = "@conversation/fs_village_convo6_m:s_9173b56f", -- What do you know? Are you a Jedi? I think I'll hold on to this until I find someone that can appreciate its rarity.
	stopConversation = "true",
	options = {}
}
fsVillageConvo6MaleTemplate:addScreen(what_do_you_know);

great_temples = ConvoScreen:new {
	id = "great_temples",
	leftDialog = "@conversation/fs_village_convo6_m:s_2370af8f", -- Well, I know they have great temples. They are the most powerful people in the galaxy!
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_a3809553", "would_you_help" }, -- Well where are they now? We could sure use their help.
	}
}
fsVillageConvo6MaleTemplate:addScreen(great_temples);

would_you_help = ConvoScreen:new {
	id = "would_you_help",
	leftDialog = "@conversation/fs_village_convo6_m:s_fd4a5d92", -- If you were them would you help? In the war I mean.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_34f24948", "speak_with_elder" }, -- Yes, I would.
		{ "@conversation/fs_village_convo6_m:s_9d65b97c", "answered_own_question" }, -- No, I don't think I would.
	}
}
fsVillageConvo6MaleTemplate:addScreen(would_you_help);

speak_with_elder = ConvoScreen:new {
	id = "speak_with_elder",
	leftDialog = "@conversation/fs_village_convo6_m:s_7e6f0d3e", -- Perhaps you should speak with the village elder. He's in the center of the village near his hut.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_abaeae10", "just_a_glowcrystal" }, -- What about the artifact?
	}
}
fsVillageConvo6MaleTemplate:addScreen(speak_with_elder);

just_a_glowcrystal = ConvoScreen:new {
	id = "just_a_glowcrystal",
	leftDialog = "@conversation/fs_village_convo6_m:s_c743096f", -- What? Oh, yea. That's just a glowcrystal after all. I was mistaken. Make sure you speak to the village elder. He's a very wise man.
	stopConversation = "true",
	options = {}
}
fsVillageConvo6MaleTemplate:addScreen(just_a_glowcrystal);

answered_own_question = ConvoScreen:new {
	id = "answered_own_question",
	leftDialog = "@conversation/fs_village_convo6_m:s_1a53608", -- Then it looks like you have answered your own question.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_abaeae10", "just_a_glowcrystal" }, -- What about the artifact?
	}
}
fsVillageConvo6MaleTemplate:addScreen(answered_own_question);

trader_came_through = ConvoScreen:new {
	id = "trader_came_through",
	leftDialog = "@conversation/fs_village_convo6_m:s_d59bf8d6", -- A trader that came through here a few years ago traded it to me for a case of Maroj melons.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_60109f4d", "yup" }, -- A case of melons? For an artifact?
	}
}
fsVillageConvo6MaleTemplate:addScreen(trader_came_through);

yup = ConvoScreen:new {
	id = "yup",
	leftDialog = "@conversation/fs_village_convo6_m:s_b86c2d97", -- Yup.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_9cb8cd84", "artifact_alright" }, -- Listen friend. I really doubt that is an artifact.
	}
}
fsVillageConvo6MaleTemplate:addScreen(yup);

artifact_alright = ConvoScreen:new {
	id = "artifact_alright",
	leftDialog = "@conversation/fs_village_convo6_m:s_b1b21b87", -- It's an artifact alright! It glows when you hold it. I think it's activated by the Force.
	stopConversation = "false",
	options = {
		{ "@conversation/fs_village_convo6_m:s_cd1f47c5", "what_do_you_know" }, -- That's not an artifact friend. It's a glowcrystal. You can buy them for 10 credits.
	}
}
fsVillageConvo6MaleTemplate:addScreen(artifact_alright);

artifacts_explode = ConvoScreen:new {
	id = "artifacts_explode",
	leftDialog = "@conversation/fs_village_convo6_m:s_6e0cc829", -- What? Artifacts explode!?
	stopConversation = "true",
	options = {}
}
fsVillageConvo6MaleTemplate:addScreen(artifacts_explode);

addConversationTemplate("fsVillageConvo6MaleTemplate", fsVillageConvo6MaleTemplate);
