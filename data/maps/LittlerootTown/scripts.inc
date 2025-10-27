LittlerootTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PascoliDelLago_OnTransition
	.byte 0

PascoliDelLago_OnTransition:
	setflag FLAG_VISITED_PASCOLI_DEL_LAGO
	end

PascoliDelLago_EventScript_Miltank::
	msgbox PascoliDelLago_Text_Miltank, MSGBOX_NPC
	end

PascoliDelLago_EventScript_Dad::
    lockall
	msgbox PascoliDelLago_Text_BirchSpendsDaysInLab, MSGBOX_DEFAULT
	giveitem ITEM_TOWN_MAP
	closemessage
	releaseall
	end

PascoliDelLago_EventScript_TownSign::
	msgbox PascoliDelLago_Text_TownSign, MSGBOX_SIGN
	end

PascoliDelLago_EventScript_PlayersHouseSign::
	msgbox PascoliDelLago_Text_PlayersHouse, MSGBOX_DEFAULT
	end

PascoliDelLago_EventScript_PlayersGrampasHouseSign::
	msgbox PascoliDelLago_Text_PlayersGrampasHouse, MSGBOX_DEFAULT
	end

PascoliDelLago_Text_Miltank:
	.string "Mil... Mil... tank!$"

PascoliDelLago_Text_BirchSpendsDaysInLab:
	.string "Tieni questa mappa.$"

PascoliDelLago_Text_TownSign:
	.string "Pascoli del Lago\n"
	.string "{DOWN_ARROW} La Valle$"

PascoliDelLago_Text_PlayersHouse:
	.string "{PLAYER}'s house$"

PascoliDelLago_Text_PlayersGrampasHouse:
	.string "{PLAYER}'s Grampa's house$"
