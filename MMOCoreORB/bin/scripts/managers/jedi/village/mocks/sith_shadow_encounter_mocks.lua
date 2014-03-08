local SithShadowEncounter = require("managers.jedi.village.sith_shadow_encounter")

local realUseDatapad

local SithShadowEncounterMocks = SithShadowEncounter
SithShadowEncounterMocks.mocks = {}

function SithShadowEncounterMocks.mocks.setup()
	realUseDatapad = SithShadowEncounter.useDatapad
end

function SithShadowEncounterMocks.mocks.teardown()
	SithShadowEncounter.useDatapad = realUseDatapad
end

function SithShadowEncounterMocks.mocks.before_each()
	SithShadowEncounter.useDatapad = spy.new(function() end)
end

function SithShadowEncounterMocks.mocks.after_each()
end

return SithShadowEncounterMocks
