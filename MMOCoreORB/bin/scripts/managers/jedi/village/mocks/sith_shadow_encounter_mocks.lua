local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")

local realUseWaypointDatapad

local SithShadowEncounterMocks = SithShadowEncounter
SithShadowEncounterMocks.mocks = {}

function SithShadowEncounterMocks.mocks.setup()
	realUseWaypointDatapad = SithShadowEncounter.useWaypointDatapad
end

function SithShadowEncounterMocks.mocks.teardown()
	SithShadowEncounter.useWaypointDatapad = realUseWaypointDatapad
end

function SithShadowEncounterMocks.mocks.before_each()
	SithShadowEncounter.useWaypointDatapad = spy.new(function() end)
end

function SithShadowEncounterMocks.mocks.after_each()
end

return SithShadowEncounterMocks
