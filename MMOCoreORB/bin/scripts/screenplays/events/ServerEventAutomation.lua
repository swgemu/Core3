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

-- Support quick check of syntax from cmd line
if Object == nil and arg ~= nil then
		Object = { }
		function Object:new(init)
				return init
		end
end

ServerEventAutomation = Object:new {
	vebose = false,
	syntax_version = 2,
	config = nil
}

function ServerEventAutomation:playerLoggedIn(pPlayer)
	if (pPlayer == nil) then
		return
	end
	self:logPlayerEvent(pPlayer, "playerLoggedIn")

	-- Are we configured?
	if self.config == nil then
		return
	end

	self:sendEventEmails(pPlayer, "playerLoggedIn")
end

function ServerEventAutomation:playerLoggedOut(pPlayer)
	if (pPlayer == nil) then
		return
	end
	self:logPlayerEvent(pPlayer, "playerLoggedOut")
end

function ServerEventAutomation:sendEventEmails(pPlayer, source_event)
	if (pPlayer == nil) then
		return
	end

	-- Is email configured?
	if self.config.emails == nil then
		return
	end

	local now = getTimestamp()

	for email_id, email in pairs(self.config.emails) do
		email.id = email_id

		if (email.start_time == nil or now >= email.start_time) and (email.end_time == nil or now <= email.end_time) then
			if not self:getSent(pPlayer, email) then
				if email.target == nil or email.target(self, pPlayer, email) then
						self:sendEventEmail(pPlayer, email)
						self:logPlayerEvent(pPlayer, "sentEventEmail:" .. email_id)
						if email.after_send ~= nil then
								email.after_send(self, pPlayer, email)
						end
						self:setSent(pPlayer, email)
				else
						self:logPlayerEvent(pPlayer, "filteredFromEventEmail:" .. email_id)
				end
			else
				if self.verbose then
					self:logPlayerEvent(pPlayer, "emailAlreadySent:" .. email_id)
				end
			end
		else
			if self.verbose then
				self:logEvent("email " .. email_id .. " is not eligible to send, now = " .. now .. " email.start_time = " .. email.start_time .. " email.end_time = " .. email.end_time)
			end
		end
	end
end

function ServerEventAutomation:sendEventEmail(pPlayer, email)
	local firstName = CreatureObject(pPlayer):getFirstName()
	local from = email.sender
	local subject = email.subject
	local body = email.body

	if from == nil then
		from = "Server Event System"
	end

	if subject == nil then
		subject = "New Server Event"
	end

	if body == nil then
		self:logPlayerEvent(pPlayer, "invalidConfiguration, body missing")
		return
	end

	body = string.gsub(body, "%%firstname%%", firstName)

	sendMail(from, subject, body, firstName)
end

function ServerEventAutomation:getSentKey(pPlayer, email)
	return CreatureObject(pPlayer):getObjectID() .. ":ServerEventAutomation:email:" .. email.id
end

function ServerEventAutomation:setSent(pPlayer, email)
	setQuestStatus(self:getSentKey(pPlayer, email), getTimestamp())
end

function ServerEventAutomation:getSent(pPlayer, email)
	local when = getQuestStatus(self:getSentKey(pPlayer, email))

	if when == nil then
		return false
	end

	return true
end

function ServerEventAutomation:logEvent(what)
	local fh = io.open("log/ServerEventAutomation.log", "a+")
	fh:write(string.format("%s [ServerEventAutomation] %s\n", getFormattedTime(), what))
	fh:flush()
	fh:close()
end

function ServerEventAutomation:logPlayerEvent(pPlayer, what)
	local creature = CreatureObject(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()
	self:logEvent(string.format(
		"playerEvent %s (oid: %d, %s) on %s at %s %s - %s",
		creature:getFirstName(),
		creature:getObjectID(),
		PlayerObject(pGhost):getPlayedTimeString(),
		creature:getZoneName(),
		math.floor(creature:getWorldPositionX()),
		math.floor(creature:getWorldPositionY()),
		what
	))
end

function ServerEventAutomation:init(config_file)
	local seaconfig = loadfile(config_file)

	if seaconfig == nil then
		return
	end

	seaconfig()

	if self.config == nil then
		self:logEvent("WARNING: Configuration error, didn't set ServerEventAutomation.config")
		return
	end

	-- Check to see if the config is compatiable with the code
	if self.config.syntax_version == nil or self.config.syntax_version > self.syntax_version then
		self:logEvent("WARNING: Configuartion syntax_version doesn't match code syntax_version, please verify feature support.")
		self.config = nil
		return
	end

	if self.config.verbose ~= nil and self.config.verbose then
		self.verbose = true
		self:logEvent("Loaded config from " .. config_file)
	end
end

ServerEventAutomation:init("conf/ServerEventAutomationConfig.lua")

return ServerEventAutomation
