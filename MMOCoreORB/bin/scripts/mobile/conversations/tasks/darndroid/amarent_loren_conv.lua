amarent_loren_convo_template = ConvoTemplate:new {
    initialScreen = "first_screen",
    templateType = "Lua",
    luaClassHandler = "amarent_loren_convo_handler",
    screens = {}
}

first_screen = ConvoScreen:new {
    id = "first_screen",
    leftDialog = "@conversation/c_ddroid_amarent:s_279", --You appear to be looking for someone.

    options = {
        {"@conversation/c_ddroid_amarent:s_281","sent_me"}, --Selan Ellison sent me.
    }
}
amarent_loren_convo_template:addScreen(first_screen)

sent_me = ConvoScreen:new {
    id = "sent_me",
    leftDialog = "@conversation/c_ddroid_amarent:s_283", --Ah Selan.  I hope she is doing well.  I don't see her near enough.  I have a moment, but as I said, I really am busy.

    options = {}
}
amarent_loren_convo_template:addScreen(sent_me)

my_influence = ConvoScreen:new {
    id = "my_influence",
    leftDialog = "@conversation/c_ddroid_amarent:s_287", --Oh!  Excuse me sir.  Forgive my insolence.  Things have just been really busy here.

    options = {
        {"@conversation/c_ddroid_amarent:s_289","forgiven"}, --I'm sure they are.  You are forgiven.  I need to know about a ship that is missing.
        {"@conversation/c_ddroid_amarent:s_293","no_excuse"}, --There is no excuse for impertinence!  I need information on a missing ship, now.
    }
}
amarent_loren_convo_template:addScreen(my_influence)

need_info = ConvoScreen:new {
    id = "need_info",
    leftDialog = "@conversation/c_ddroid_amarent:s_303", --I'm sorry, but I cannot give out that kind of information unless you are a member of the Imperial Transit Authority.

    options = {}
}
amarent_loren_convo_template:addScreen(need_info)

forgiven = ConvoScreen:new {
    id = "forgiven",
    leftDialog = "@conversation/c_ddroid_amarent:s_291", --Yes sir.  I have been investigating that ship.  It appears that the ship was diverted to Talus, though I have no information as to whether it crashed due to a malfunction or hijacking.  I have been told, sir, that it is a low priority and likely won't be pursued for several more days. Here are the coordinates if you would like to investigate the crash site.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(forgiven)

no_excuse = ConvoScreen:new {
    id = "no_excuse",
    leftDialog = "@conversation/c_ddroid_amarent:s_295", --Yes sir.  Give me a moment to consult with my notes. Yes, I think that ship is here.  One more moment...

    options = {
        {"@conversation/c_ddroid_amarent:s_297","come_on"}, --Come on, man!  I don't have all day.
    }
}
amarent_loren_convo_template:addScreen(no_excuse)

come_on = ConvoScreen:new {
    id = "come_on",
    leftDialog = "@conversation/c_ddroid_amarent:s_299", --Ah!  Here it is.  It crashed on Talus.  I will transmit the location to your datapad...sir.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(come_on)

bribe_credits = ConvoScreen:new {
    id = "bribe_credits",
    leftDialog = "@conversation/c_ddroid_amarent:s_307", --I suppose it is only helping out a concerned citizen.  The ship that you are looking for crashed on Talus.  I can copy the location to your datapad.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(bribe_credits)

life_worth = ConvoScreen:new {
    id = "life_worth",
    leftDialog = "@conversation/c_ddroid_amarent:s_311", --Erm...no need for any weapons, I assure you! The ship crashed on Talus.  If you don't hurt me, I'll copy the location to your datapad.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(life_worth)

not_ready = ConvoScreen:new {
    id = "not_ready",
    leftDialog = "@conversation/c_ddroid_amarent:s_313", --I'm very busy.  I'm sorry I can't talk to you right now.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(not_ready)

more_help = ConvoScreen:new {
    id = "more_help",
    leftDialog = "@conversation/c_ddroid_amarent:s_315", --Do you need more help?

    options = {
        {"@conversation/c_ddroid_amarent:s_316","need_waypoint"}, --I need to know where the crash is again.
    }
}
amarent_loren_convo_template:addScreen(more_help)

need_waypoint = ConvoScreen:new {
    id = "need_waypoint",
    leftDialog = "@conversation/c_ddroid_amarent:s_317", --All right.  I'll copy it into your datapad.
    stopConversation = "true",
    options = {}
}
amarent_loren_convo_template:addScreen(need_waypoint)

addConversationTemplate("amarent_loren_convo_template", amarent_loren_convo_template)