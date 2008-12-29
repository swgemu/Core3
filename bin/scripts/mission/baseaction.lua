--Copyright (C) 2007 <SWGEmu>
 
--This File is part of Core3.
 
--This program is free software; you can redistribute 
--it and/or modify it under the terms of the GNU Lesser 
--General Public License as published by the Free Software
--Foundation; either version 2 of the License, 
--or (at your option) any later version.
 
--This program is distributed in the hope that it will be useful, 
--but WITHOUT ANY WARRANTY; without even the implied warranty of 
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
--See the GNU Lesser General Public License for
--more details.
 
--You should have received a copy of the GNU Lesser General 
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
--Linking Engine3 statically or dynamically with other modules 
--is making a combined work based on Engine3. 
--Thus, the terms and conditions of the GNU Lesser General Public License 
--cover the whole combination.
 
--In addition, as a special exception, the copyright holders of Engine3 
--give you permission to combine Engine3 program with free software 
--programs or libraries that are released under the GNU LGPL and with 
--code included in the standard release of Core3 under the GNU LGPL 
--license (or modified versions of such code, with unchanged license). 
--You may copy and distribute such a system following the terms of the 
--GNU LGPL for Engine3 and the licenses of the other code concerned, 
--provided that you include the source code of that other code when 
--and as the GNU LGPL requires distribution of source code.
 
--Note that people who make modified versions of Engine3 are not obligated 
--to grant this special exception for their modified versions; 
--it is their choice whether to do so. The GNU Lesser General Public License 
--gives permission to release a modified version without this exception; 
--this exception also makes it possible to release a modified version 
--which carries forward this exception.

--------------------------------------------
-- ACTION CLASS
--------------------------------------------

Action = Object:new {
    	objectName = "",
	actionKey = "", -- UNIQUE internal key used to identify the action. No spaces, keep small but informational

	prereqMask = 0,
	actionMask = 0,

	-- Optional Triggers
	onConverse = 0,
	onTrade = 0,
	onAttack = 0,
	onDeath = 0,
	--

	--------
	-- Prerequisite Vars:
	--------

	-- Has mission:
	meet_hasMission = "", -- Fill in w/ mission key to check if player has specified mission

	-- Kill Count Limit - KILL COUNTING / TRACKING
	meet_killLimitList = "", -- List of creature crc / limit value pairs. See documentation for more information.

	--------
	-- Action Vars:
	--------

	-- Conversation Vars
	convoScreenList = "", -- Keep this updated with ALL your screen ids. ScreenID "0" is REQUIRED.
	--
}

--------------------------------------------
-- ACTION:CONVERSATION SCREEN TABLE
--------------------------------------------

-- Global Screen Table
ScreenTable = {}

function ScreenTable:addConvoScreen(obj)
	self[obj:getId()] = obj
end

function getConvoScreen(sid)
	return ScreenTable[sid]
end

function clearScreenTable()
	ScreenTable = {}
end

--------------------------------------------
-- ACTION:CONVERSATION SCREEN CLASS
--------------------------------------------

ConvoScreen = Object:new {
    id = "",
    leftDialog = "",

    optionCount = 0,
    compOptionText = "",
    compOptionLinks = "",
}

function ConvoScreen:setId(td)
	self.id = td
end

function ConvoScreen:getId()
	return self.id
end

function ConvoScreen:setDialog(text)
    self.leftDialog = text
end

function ConvoScreen:getDialog()
    return self.leftDialog
end

function ConvoScreen:getOptionCount()
    return self.optionCount
end

function ConvoScreen:addOption(optText, linkParameter, actionKey)
    if optionCount==0 then
        self.compOptionText = optText
        self.compOptionLinks = linkParameter .. "," .. actionKey
    else
        self.compOptionText = self.compOptionText .. "|" .. optText
        self.compOptionLinks = self.compOptionLinks .. "|" .. linkParameter .. "," .. actionKey
    end
    self.optionCount = self.optionCount + 1
end

function ConvoScreen:getCompiledOptionText()
    return self.compOptionText
end

function ConvoScreen:getCompiledOptionLinks()
    return self.compOptionLinks
end
