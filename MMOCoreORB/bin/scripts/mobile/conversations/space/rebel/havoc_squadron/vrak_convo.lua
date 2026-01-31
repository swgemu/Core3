vrak_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "vrakConvoHandler",
	screens = {}
}

-- ============================================================================
-- Default (Not the right player)
-- ============================================================================

vrak_convo_not_right_player = ConvoScreen:new {
	id = "not_right_player",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_b02a22c2", -- What do you want? I'm busy!
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
vrak_convo:addScreen(vrak_convo_not_right_player)

-- ============================================================================
-- First Meeting Flow (viopaSmuggler == 1)
-- ============================================================================

-- Initial greeting - "Are you the pilot?"
vrak_convo_are_you_the_pilot = ConvoScreen:new {
	id = "are_you_the_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_c5fc3d7a", -- Are you the pilot?
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_fca23d59", "yes_i_am_pilot"}, -- Yes. I was told that you could help me.
		{"@conversation/lok_rebel_trainer_2_smuggler:s_a46f0bb8", "corsec_joke"}, -- No, I'm with the CorSec anti smuggling department.
	}
}
vrak_convo:addScreen(vrak_convo_are_you_the_pilot)

-- ============================================================================
-- Path A: Serious Response
-- ============================================================================

-- Player confirms identity
vrak_convo_yes_i_am_pilot = ConvoScreen:new {
	id = "yes_i_am_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_a3c154e6", -- Yes maybe so. You have a, uh, 'package' that you can't open?
	animation = "nod_head_multiple",
	playerAnimation = "nod_head_multiple",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_6bb0cb94", "correct_response"}, -- Correct.
	}
}
vrak_convo:addScreen(vrak_convo_yes_i_am_pilot)

-- Player confirms package
vrak_convo_correct_response = ConvoScreen:new {
	id = "correct_response",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_8dc05a21", -- I know a man that specializes in opening 'packages'. He's a bit paranoid though but when I was contacted by Nym, I made some arrangements. He's agreed to meet you in the Dantooine system... he won't land. You need to meet with him there and transfer the 'package' that you need him to open.
	animation = "whisper",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_50e93f2d", "thank_you_vrak"}, -- Sounds good, thank you Vrak.
	}
}
vrak_convo:addScreen(vrak_convo_correct_response)

-- Thank Vrak - ends first meeting (sets viopaSmuggler = 2)
vrak_convo_thank_you_vrak = ConvoScreen:new {
	id = "thank_you_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_871202ae", -- Sure sure, now go back to your commanding officer and get that data to my friend so he can 'open' it.
	animation = "nervous",
	playerAnimation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
vrak_convo:addScreen(vrak_convo_thank_you_vrak)

-- ============================================================================
-- Path B: CorSec Joke Response
-- ============================================================================

-- Player jokes about being CorSec
vrak_convo_corsec_joke = ConvoScreen:new {
	id = "corsec_joke",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_ed7e2471", -- Wh.. what do you want? I haven't done anything, I swear!
	animation = "implore",
	playerAnimation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_b9280ab0", "just_kidding"}, -- Calm down silly, I'm just kidding. I am the pilot.
	}
}
vrak_convo:addScreen(vrak_convo_corsec_joke)

-- Player admits kidding
vrak_convo_just_kidding = ConvoScreen:new {
	id = "just_kidding",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_d36158bb", -- What are you trying to do? Get me killed? Now what did you need help with?
	animation = "nervous",
	playerAnimation = "slow_down",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_d5132e66", "good_translator"}, -- You are supposed to know a good 'translator'?
	}
}
vrak_convo:addScreen(vrak_convo_just_kidding)

-- Player asks about translator
vrak_convo_good_translator = ConvoScreen:new {
	id = "good_translator",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_53a57295", -- The best. He's a bit paranoid though but when I was contacted by Nym, I made some arrangements. He's agreed to meet you in the Dantooine system... he won't land. You need to meet with him there and transfer the information that you need him to 'translate'.
	animation = "whisper",
	playerAnimation = "whisper",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_6541ff8b", "anything_else"}, -- Sounds good, is there anything else I should know?
	}
}
vrak_convo:addScreen(vrak_convo_good_translator)

-- Player asks if there's anything else
vrak_convo_anything_else = ConvoScreen:new {
	id = "anything_else",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_5dd70a2c", -- What do you mean..?
	animation = "nervous",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_3103c633", "calm_down_goodbye"}, -- I was just asking, calm down. Well, see you around.
	}
}
vrak_convo:addScreen(vrak_convo_anything_else)

-- Calm down goodbye - ends first meeting (sets viopaSmuggler = 2)
vrak_convo_calm_down_goodbye = ConvoScreen:new {
	id = "calm_down_goodbye",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_1106d288", -- Sure sure, now go back to your commanding officer and get that data to my friend so he can 'translate' it.
	animation = "dismiss",
	playerAnimation = "slow_down",
	stopConversation = "true",
	options = {}
}
vrak_convo:addScreen(vrak_convo_calm_down_goodbye)

-- ============================================================================
-- Confrontation Flow (viopaSmuggler == 3)
-- ============================================================================

-- Initial confrontation - "Wh..what are you doing here?!"
vrak_convo_what_are_you_doing_here = ConvoScreen:new {
	id = "what_are_you_doing_here",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_9b75f1f", -- Wh..what are you doing here?!
	animation = "nervous",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_88fb9bcb", "unfinished_business"}, -- We have some unfinished business I believe.
		{"@conversation/lok_rebel_trainer_2_smuggler:s_e28286fc", "blaster_proof"}, -- Oh I'm just here to check if you're blaster-proof.
	}
}
vrak_convo:addScreen(vrak_convo_what_are_you_doing_here)

-- ============================================================================
-- Confrontation Path A: Unfinished Business
-- ============================================================================

vrak_convo_unfinished_business = ConvoScreen:new {
	id = "unfinished_business",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_bf37655b", -- Please, I didn't mean to do it, I had to! Don't hurt me, I'll tell you everything I know!
	animation = "implore",
	playerAnimation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_73e609b7", "im_waiting"}, -- I'm waiting.
		{"@conversation/lok_rebel_trainer_2_smuggler:s_f911cddf", "pity_bones"}, -- So I don't even have to break any of your bones? Pity.
	}
}
vrak_convo:addScreen(vrak_convo_unfinished_business)

-- ============================================================================
-- Confrontation Path B: Blaster-Proof
-- ============================================================================

vrak_convo_blaster_proof = ConvoScreen:new {
	id = "blaster_proof",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_bf37655b", -- Please, I didn't mean to do it, I had to! Don't hurt me, I'll tell you everything I know!
	animation = "implore",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_73e609b7", "im_waiting"}, -- I'm waiting.
		{"@conversation/lok_rebel_trainer_2_smuggler:s_f911cddf", "pity_bones"}, -- So I don't even have to break any of your bones? Pity.
	}
}
vrak_convo:addScreen(vrak_convo_blaster_proof)

-- ============================================================================
-- Confession Path (both paths converge here)
-- ============================================================================

-- I'm waiting
vrak_convo_im_waiting = ConvoScreen:new {
	id = "im_waiting",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_9da8a554", -- A while ago I was contacted by someone named Kud'ar Mub'at, he's the type of 'person' that you don't say no to. He offered a large sum of money for any information on some stolen Imperial data.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_d7fe1a24", "kudar_mubat_who"}, -- Kud'ar Mub'at?
		{"@conversation/lok_rebel_trainer_2_smuggler:s_edb238bc", "betrayal_explanation"}, -- Go on.
	}
}
vrak_convo:addScreen(vrak_convo_im_waiting)

-- Pity about bones
vrak_convo_pity_bones = ConvoScreen:new {
	id = "pity_bones",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_99dcc230", -- I'm not a fighter, I'll tell you all I know. A while ago I was contacted by someone named Kud'ar Mub'at, he's the type of 'person' that you don't say no to. He offered a large sum of money for any information on some stolen Imperial data.
	animation = "explain",
	playerAnimation = "sigh_deeply",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_d7fe1a24", "kudar_mubat_who"}, -- Kud'ar Mub'at?
		{"@conversation/lok_rebel_trainer_2_smuggler:s_edb238bc", "betrayal_explanation"}, -- Go on.
	}
}
vrak_convo:addScreen(vrak_convo_pity_bones)

-- Kud'ar Mub'at question
vrak_convo_kudar_mubat_who = ConvoScreen:new {
	id = "kudar_mubat_who",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_4e307ac2", -- I don't know who he really is, not many have seen him. I only know that he's some sort of shady information broker but he has a lot of power.
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_2387d3d7", "betrayal_explanation"}, -- Alright, go on.
	}
}
vrak_convo:addScreen(vrak_convo_kudar_mubat_who)

-- The betrayal revealed (sets viopaSmuggler = 4)
vrak_convo_betrayal_explanation = ConvoScreen:new {
	id = "betrayal_explanation",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_f7deed3b", -- When I was contacted by one of Nym's people about the data that they couldn't encrypt, I put two and two together. I sent Kud'ar what he needed to know to intercept you and the hacker.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_6789e90e", "what_else"}, -- What else?
	}
}
vrak_convo:addScreen(vrak_convo_betrayal_explanation)

-- What else
vrak_convo_what_else = ConvoScreen:new {
	id = "what_else",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_cf66be5a", -- That's all I know, I swear! Please don't hurt me, my life is just starting. I'm nothing but a pawn, please...
	animation = "weeping",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_b5dd2ed8", "nym_will_take_care"}, -- You're lucky I'm in a hurry. I'm sure Nym will take care of you.
		{"@conversation/lok_rebel_trainer_2_smuggler:s_29b10239", "pathetic_response"}, -- I think you're in the wrong business. Pathetic.
	}
}
vrak_convo:addScreen(vrak_convo_what_else)

-- ============================================================================
-- Final Responses
-- ============================================================================

-- Nym will take care of you
vrak_convo_nym_will_take_care = ConvoScreen:new {
	id = "nym_will_take_care",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_d0098db3", -- I need to get out of here!
	animation = "gesticulate_wildly",
	playerAnimation = "slit_throat",
	stopConversation = "true",
	options = {}
}
vrak_convo:addScreen(vrak_convo_nym_will_take_care)

-- Pathetic response
vrak_convo_pathetic_response = ConvoScreen:new {
	id = "pathetic_response",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_f39484e1", -- I will change, I promise..
	animation = "weeping",
	playerAnimation = "belly_laugh",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2_smuggler:s_6b133072", "nym_ensures_change"}, -- Nym will probably make sure of that.
	}
}
vrak_convo:addScreen(vrak_convo_pathetic_response)

-- Nym ensures change
vrak_convo_nym_ensures_change = ConvoScreen:new {
	id = "nym_ensures_change",
	leftDialog = "@conversation/lok_rebel_trainer_2_smuggler:s_d0098db3", -- I need to get out of here!
	animation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
vrak_convo:addScreen(vrak_convo_nym_ensures_change)

addConversationTemplate("vrak_convo", vrak_convo)
