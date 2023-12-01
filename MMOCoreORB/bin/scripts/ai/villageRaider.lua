awareVillageraider = {
	{id="3355064720",	name="Selector",	pid="none"},
	{id="435736119",	name="LookForTarget",	pid="3355064720"},
	{id="491416417",	name="Sequence",	pid="435736119"},
	{id="708705776",	name="If",	pid="491416417"},
	{id="650454634",	name="CheckProspectInRange",	pid="708705776",	args={condition=32.0}},
	{id="1910919081",	name="TreeSocket",	pid="491416417",	args={slot=AGGRO}},
	{id="4292778610",	name="AlwaysFail",	pid="3355064720"},
	{id="3065616444",	name="Sequence",	pid="4292778610"},
	{id="3058858261",	name="EraseBlackboard",	pid="3065616444",	args={param="aggroMod"}},
	{id="2946449456",	name="EraseBlackboard",	pid="3065616444",	args={param="targetProspect"}}}
addAiTemplate("awareVillageraider", awareVillageraider)
