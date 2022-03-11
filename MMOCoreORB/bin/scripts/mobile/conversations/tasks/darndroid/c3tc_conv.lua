c3tc_convo_template = ConvoTemplate:new {
    initialScreen = "first_screen",
    templateType = "Lua",
    luaClassHandler = "c3tc_convo_handler",
    screens = {}
}

first_screen = ConvoScreen:new {
    id = "first_screen",
    leftDialog = "@conversation/c_ddroid_droid:s_52", --Oh dear, oh dear.  My poor master!  Can you help me?

    options = {
        {"@conversation/c_ddroid_droid:s_54","help_with"}, --What do you need help with?
        {"@conversation/c_ddroid_droid:s_102","no_help"}, --No.  Who would want to help a droid?
    }
}
c3tc_convo_template:addScreen(first_screen)

help_with = ConvoScreen:new {
    id = "help_with",
    leftDialog = "@conversation/c_ddroid_droid:s_56", --My master, Valance Serth is missing!  He was supposed to land at the Starport here an hour ago.  I'm afraid something really bad happened and it would be entirely my fault!

    options = {
        {"@conversation/c_ddroid_droid:s_58","your_fault"}, --What are you talking about?  How would it be your fault?
        {"@conversation/c_ddroid_droid:s_94","ill_help"}, --I will help you find your master.
        {"@conversation/c_ddroid_droid:s_98","too_busy"}, --Sorry, too busy.  He may have taken another ship.
    }
}
c3tc_convo_template:addScreen(help_with)

your_fault = ConvoScreen:new {
    id = "your_fault",
    leftDialog = "@conversation/c_ddroid_droid:s_60", --Everything is my fault! My master was supposed to come here and meet me.  I tried to find out what happened, but no one at the Starport will talk to me.  I'm afraid that something terrible has happened to him.

    options = {
        {"@conversation/c_ddroid_droid:s_62","say_that"}, --What would make you say that?
        {"@conversation/c_ddroid_droid:s_74","left_you"}, --Could he have just left you here?
    }
}
c3tc_convo_template:addScreen(your_fault)

ill_help = ConvoScreen:new {
    id = "ill_help",
    leftDialog = "@conversation/c_ddroid_droid:s_96", --Oh thank you!  Please go to the Moenia Starport. There is a lady named Selan Ellison.  Maybe she could help you.  Please hurry.  Who knows what may have eaten him!
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(ill_help)

too_busy = ConvoScreen:new {
    id = "too_busy",
    leftDialog = "@conversation/c_ddroid_droid:s_100", --He's never late!  My master hates to be late.  That's why I am worried.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(too_busy)

no_help = ConvoScreen:new {
    id = "no_help",
    leftDialog = "@conversation/c_ddroid_droid:s_104", --It isn't me that you would be helping, but my master.  Please please come back if you change your mind.  Otherwise, he will be doomed!
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(no_help)

say_that = ConvoScreen:new {
    id = "say_that",
    leftDialog = "@conversation/c_ddroid_droid:s_64", --Someone was looking for him.  They needed to give him an urgent message from some prince.  Once I told them what ship he was traveling on, they told me not to expect him.  Can you help him?

    options = {
        {"@conversation/c_ddroid_droid:s_66","find_master"}, --I can help you find your master.
        {"@conversation/c_ddroid_droid:s_70","no_droids"}, --No.  I'm not into helping droids.
    }
}
c3tc_convo_template:addScreen(say_that)

left_you = ConvoScreen:new {
    id = "left_you",
    leftDialog = "@conversation/c_ddroid_droid:s_76", --How could you say that?  I am a protocol droid!  No one would be cruel enough to leave their loyal servant.  Anyway, he couldn't do without me.  I am fluent in over 1.5 million forms of communication and am excellent in facilitating diplomacy.

    options = {
        {"@conversation/c_ddroid_droid:s_78","tell_about"}, --Right.  I can help you find your master.  What can you tell me about him?
        {"@conversation/c_ddroid_droid:s_90","not_interested"}, --I don't think I'm interested.
    }
}
c3tc_convo_template:addScreen(left_you)

find_master = ConvoScreen:new {
    id = "find_master",
    leftDialog = "@conversation/c_ddroid_droid:s_68", --Oh thank you!  His name is Valance Serth.  He's from Corellia.  There is a lady named Selan Ellison at the Starport.  Maybe she could help you.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(find_master)

no_droids = ConvoScreen:new {
    id = "no_droids",
    leftDialog = "@conversation/c_ddroid_droid:s_72", --Maybe someone will come along that is kinder than you and help me find my poor master.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(no_droids)

tell_about = ConvoScreen:new {
    id = "tell_about",
    leftDialog = "@conversation/c_ddroid_droid:s_80", --His name is Valance Serth and he's from Corellia. His father was a member of Corsec until he died.  His mother...

    options = {
        {"@conversation/c_ddroid_droid:s_82","start_looking"}, --Valance Serth, right.  I'll start looking.
        {"@conversation/c_ddroid_droid:s_86","another_time"}, --Maybe I will help another time.
    }
}
c3tc_convo_template:addScreen(tell_about)

not_interested = ConvoScreen:new {
    id = "not_interested",
    leftDialog = "@conversation/c_ddroid_droid:s_92", --Oh dear.  Please reconsider.  My master's life may be on the line!
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(not_interested)

start_looking = ConvoScreen:new {
    id = "start_looking",
    leftDialog = "@conversation/c_ddroid_droid:s_84", --Thank you.  There is a lady named Selan Ellison at the Starport.  Maybe she could help you.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(start_looking)

another_time = ConvoScreen:new {
    id = "another_time",
    leftDialog = "@conversation/c_ddroid_droid:s_88", --Another time may be too late!  I'll have to find someone else.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(another_time)

not_done = ConvoScreen:new {
    id = "not_done",
    leftDialog = "@conversation/c_ddroid_droid:s_106", --Oh, you are back. Where is my master, have you seen him?

    options = {}
}
c3tc_convo_template:addScreen(not_done)

on_talus = ConvoScreen:new {
    id = "on_talus",
    leftDialog = "@conversation/c_ddroid_droid:s_110", --Talus?  What did you do to him?  Oh dear.  I should be there for him.

    options = {
        {"@conversation/c_ddroid_droid:s_112","was_hurt"}, --He was hurt when his ship crashed but he's recovering.
    }
}
c3tc_convo_template:addScreen(on_talus)

maybe_no_tell = ConvoScreen:new {
    id = "maybe_no_tell",
    leftDialog = "@conversation/c_ddroid_droid:s_138", --Oh he must be dead.  Master, I wasn't there for you!  Oh master!
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(maybe_no_tell)

no_use = ConvoScreen:new {
    id = "no_use",
    leftDialog = "@conversation/c_ddroid_droid:s_142", --Please go find out what happened to him.  I'm sure he needs help.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(no_use)

was_hurt = ConvoScreen:new {
    id = "was_hurt",
    leftDialog = "@conversation/c_ddroid_droid:s_114", --Oh thank the maker!  He will be all right.  I won't be a droid without a master after all.  After those men came here threatening me and you too!  They wanted to know when you started looking for my master.

    options = {
        {"@conversation/c_ddroid_droid:s_116","they_did"}, --They did?
        {"@conversation/c_ddroid_droid:s_128","tell_anything"}, --Why did you tell them anything?!
    }
}
c3tc_convo_template:addScreen(was_hurt)

they_did = ConvoScreen:new {
    id = "they_did",
    leftDialog = "@conversation/c_ddroid_droid:s_118", --Oh yes.  When I told them that you were going to look for him immediately, they left in a hurry.  I do hope you are well.

    options = {
        {"@conversation/c_ddroid_droid:s_120","run_this"}, --Well enough. Master Serth wants you to run this program.
        {"@conversation/c_ddroid_droid:s_124","no_thanks"}, --Yes, no thanks to you.  Run this program through your banks.
    }
}
c3tc_convo_template:addScreen(they_did)

tell_anything = ConvoScreen:new {
    id = "tell_anything",
    leftDialog = "@conversation/c_ddroid_droid:s_130", --Was I not supposed to say anything?  At first I thought they were going to help you find him.  How am I supposed to know?

    options = {
        {"@conversation/c_ddroid_droid:s_132","run_this"}, --Never mind.  Master Serth wants you to run this program.
    }
}
c3tc_convo_template:addScreen(tell_anything)

run_this = ConvoScreen:new {
    id = "run_this",
    leftDialog = "@conversation/c_ddroid_droid:s_122", --Certainly, if my master wants it...oh my, what was I saying?  How strange.  Here, I am supposed to give this to you, I think.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(run_this)

no_thanks = ConvoScreen:new {
    id = "no_thanks",
    leftDialog = "@conversation/c_ddroid_droid:s_126", --Oh dear, I hope it's safe. I wouldn't want to jeopardize...hmm, what was I saying? I think I am supposed to give this to you.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(no_thanks)

mem_wiped = ConvoScreen:new {
    id = "mem_wiped",
    leftDialog = "@conversation/c_ddroid_droid:s_144", --Hello!  I seem to be a bit lost.  Droids need masters, but I don't have one.  How odd.  Maybe someone will come for me soon.
    stopConversation = "true",
    options = {}
}
c3tc_convo_template:addScreen(mem_wiped)

addConversationTemplate("c3tc_convo_template", c3tc_convo_template)