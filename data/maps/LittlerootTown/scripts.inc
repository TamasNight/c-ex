LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, LittlerootTown_OnTransition
	.byte 0

LittlerootTown_OnTransition:
	setflag FLAG_VISITED_PASCOLI_DEL_LAGO
	end

PascoliDelLago_EventScript_Miltank::
	msgbox PascoliDelLago_Text_Miltank, MSGBOX_NPC
	end

PascoliDelLago_EventScript_Boy::
	msgbox PascoliDelLago_Text_BirchSpendsDaysInLab, MSGBOX_NPC
	end

PascoliDelLago_EventScript_TownSign::
	msgbox PascoliDelLago_Text_TownSign, MSGBOX_SIGN
	end

PascoliDelLago_EventScript_PlayersHouseSign::
	msgbox PascoliDelLago_Text_PlayersHouse, MSGBOX_DEFAULT
	end

PascoliDelLago_Text_Miltank:
	.string "Mil... Mil... tank!$"

PascoliDelLago_Text_BirchSpendsDaysInLab:
	.string "PROF. BIRCH spends days in his LAB\n"
	.string "studying, then he'll suddenly go out in\l"
	.string "the wild to do more research…\p"
	.string "When does PROF. BIRCH spend time\n"
	.string "at home?$"

PascoliDelLago_Text_TownSign:
	.string "Pascoli del Lago\n"
	.string "{DOWN_ARROW} La Valle$"

PascoliDelLago_Text_PlayersHouse:
	.string "{PLAYER}'s house$"
