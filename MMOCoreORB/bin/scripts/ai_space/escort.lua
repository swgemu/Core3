awareEscort = {
	{id="1432301304",	name="SequenceSpace",	pid="none"},
	{id="965485614",	name="IfSpace",	pid="1432301304"},
	{id="472617544",	name="CheckProspectInRange",	pid="965485614"},
	{id="2151056364",	name="AlwaysSucceedSpace",	pid="1432301304"},
	{id="2975746901",	name="SetAlert",	pid="2151056364",	args={aggroDelay=5.0}},
	{id="3241454373",	name="IfSpace",	pid="1432301304"},
	{id="2685966823",	name="CheckAggroDelayPast",	pid="3241454373"},
	{id="658558868",	name="TreeSocketSpace",	pid="1432301304",	args={slot=AGGROSPACE}}}
addAiTemplate("awareEscort", awareEscort)

idleEscort = {
	{id="3878147956",	name="SequenceSpace",	pid="none"},
	{id="3826170193",	name="NotSpace",	pid="3878147956"},
	{id="1569932203",	name="IfSpace",	pid="3826170193"},
	{id="1062834130",	name="CheckHasPatrol",	pid="1569932203"},
	{id="1111847443",	name="GeneratePatrol",	pid="3878147956",	args={distFromHome=256.0, numPoints=5}}}
addAiTemplate("idleEscort", idleEscort)

moveEscort = {
	{id="3162096793",	name="SequenceSpace",	pid="none"},
	{id="3119158273",	name="IfSpace",	pid="3162096793"},
	{id="311662512",	name="CheckDestination",	pid="3119158273"},
	{id="4219492080",	name="AlwaysFailSpace",	pid="3162096793"},
	{id="145123387",	name="FindNextPosition",	pid="4219492080"}}
addAiTemplate("moveEscort", moveEscort)

rootEscort = {
	{id="763915188",	name="SelectorSpace",	pid="none"},
	{id="2765964998",	name="TreeSocketSpace",	pid="763915188",	args={slot=MOVESPACE}},
	{id="274678305",	name="SequenceSpace",	pid="763915188"},
	{id="244308363",	name="SelectorSpace",	pid="274678305"},
	{id="1389030440",	name="TreeSocketSpace",	pid="244308363",	args={slot=TARGETSPACE}},
	{id="1131517349",	name="TreeSocketSpace",	pid="244308363",	args={slot=AWARESPACE}},
	{id="861764988",	name="TreeSocketSpace",	pid="274678305",	args={slot=ATTACKSPACE}},
	{id="3409670866",	name="TreeSocketSpace",	pid="763915188",	args={slot=IDLESPACE}}}
addAiTemplate("rootEscort", rootEscort)

targetEscort = {
	{id="3290098785",	name="SelectorSpace",	pid="none"},
	{id="3951740411",	name="SequenceSpace",	pid="3290098785"},
	{id="2841003354",	name="SelectorSpace",	pid="3951740411"},
	{id="1620568575",	name="GetProspectFromThreatMap",	pid="2841003354"},
	{id="1345817549",	name="GetProspectFromDefenders",	pid="2841003354"},
	{id="1871742210",	name="SetDefenderFromProspect",	pid="2841003354"},
	{id="1343376248",	name="IfSpace",	pid="3951740411"},
	{id="1733346912",	name="CheckTargetIsValid",	pid="1343376248"},
	{id="934802909",	name="AlwaysFailSpace",	pid="3290098785"},
	{id="1252347732",	name="SequenceSpace",	pid="934802909"},
	{id="4111572918",	name="EraseBlackboard",	pid="1252347732",	args={param="aggroMod"}},
	{id="428911276",	name="EraseBlackboard",	pid="1252347732",	args={param="targetShipProspect"}},
	{id="1001791584",	name="ExitCombat",	pid="1252347732"}}
addAiTemplate("targetEscort", targetEscort)

