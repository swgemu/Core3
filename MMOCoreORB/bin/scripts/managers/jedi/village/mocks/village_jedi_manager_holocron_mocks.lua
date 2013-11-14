local realUseHolocron

local VillageJediManagerHolocronMocks = {}

function VillageJediManagerHolocronMocks.setup()
	realUseHolocron = VillageJediManagerHolocron.useHolocron
end

function VillageJediManagerHolocronMocks.teardown()
	VillageJediManagerHolocron.useHolocron = realUseHolocron
end

function VillageJediManagerHolocronMocks.before_each()
	VillageJediManagerHolocron.useHolocron = spy.new(function() end)
end

function VillageJediManagerHolocronMocks.after_each()
end

return VillageJediManagerHolocronMocks
