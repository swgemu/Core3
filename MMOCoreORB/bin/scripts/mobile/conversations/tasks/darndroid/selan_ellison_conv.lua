selan_ellison_convo_template = ConvoTemplate:new {
    initialScreen = "first_screen",
    templateType = "Lua",
    luaClassHandler = "selan_ellison_convo_handler",
    screens = {}
}

first_screen = ConvoScreen:new {
    id = "first_screen",
    leftDialog = "@conversation/c_ddroid_selan:s_211", --You appear to be looking for someone.

    options = {
        {"@conversation/c_ddroid_selan:s_215","what_know"}, --What do you know of a late ship from Corellia?
    }
}
selan_ellison_convo_template:addScreen(first_screen)

not_ready = ConvoScreen:new {
    id = "not_ready",
    leftDialog = "@conversation/c_ddroid_selan:s_239", --Lovely day at the Starport, isn't it?
    stopConversation = "true",
    options = {}
}
selan_ellison_convo_template:addScreen(not_ready)

what_know = ConvoScreen:new {
    id = "what_know",
    leftDialog = "@conversation/c_ddroid_selan:s_219", --Actually, I did hear that a ship had 'trouble' on the way here, but there isn't much information from the Port Authority.  I think that there's a good reason to worry.

    options = {
        {"@conversation/c_ddroid_selan:s_223","isnt_good"}, --That isn't good.  I need to find one of the passengers on that ship.
    }
}
selan_ellison_convo_template:addScreen(what_know)

isnt_good = ConvoScreen:new {
    id = "isnt_good",
    leftDialog = "@conversation/c_ddroid_selan:s_227", --Perhaps I could help?

    options = {
        {"@conversation/c_ddroid_selan:s_231","appreciate_it"}, --If you can, I would appreciate it.
    }
}
selan_ellison_convo_template:addScreen(isnt_good)

appreciate_it = ConvoScreen:new {
    id = "appreciate_it",
    leftDialog = "@conversation/c_ddroid_selan:s_235", --I have a friend who works for the Port Authority in Tyrena, on Corellia.  His name is Amarent Loren.  Just tell him that Selan Ellison sent you.
    stopConversation = "true",
    options = {}
}
selan_ellison_convo_template:addScreen(appreciate_it)

addConversationTemplate("selan_ellison_convo_template", selan_ellison_convo_template)