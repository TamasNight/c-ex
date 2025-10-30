PascoliDelLago_MapScripts::
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
	msgbox PascoliDelLago_Text_PlayersHouse, MSGBOX_SIGN
	end

PascoliDelLago_EventScript_MomCry::
    applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
    waitmovement 0
    msgbox PascoliDelLago_Text_MomCry, MSGBOX_DEFAULT
    closemessage
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 3
    removeobject LOCALID_TAUROS_CORNER
    setflag FLAG_HIDE_TAUROS_FROM_FIELD
    end

PascoliDelLago_EventScript_BetterNotInThisDirection::
    msgbox PascoliDelLago_Text_BetterNotInThisDirection, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
    waitmovement 0
    end

PascoliDelLago_EventScript_IHaveToHurry::
    msgbox PascoliDelLago_Text_IHaveToHurry, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkRight
    waitmovement 0
    end

PascoliDelLago_EventScript_Tauros::
	msgbox PascoliDelLago_Text_Tauros, MSGBOX_NPC
	end

PascoliDelLago_EventScript_MomResqueUpper::
    lockall
    applymovement LOCALID_PLAYER, PascoliDelLago_EventScript_ApproachMomUpper
    waitmovement 0
    goto PascoliDelLago_EventScript_MomResque

PascoliDelLago_EventScript_MomResqueLower::
    lockall
    applymovement LOCALID_PLAYER, PascoliDelLago_EventScript_ApproachMomLower
    waitmovement 0
    goto PascoliDelLago_EventScript_MomResque

PascoliDelLago_EventScript_MomResque::
    msgbox PascoliDelLago_Text_PlayerAsk, MSGBOX_DEFAULT
    delay 8
    msgbox PascoliDelLago_Text_MomExplains, MSGBOX_DEFAULT
    delay 8
    msgbox PascoliDelLago_Text_PlayerRevenge, MSGBOX_DEFAULT
    applymovement LOCALID_PASCOLI_DEL_LAGO_MON, Common_Movement_ExclamationMark
    waitmovement 0
    msgbox PascoliDelLago_Text_MomWarnings, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_PlayerAssure, MSGBOX_DEFAULT
    delay 8
    msgbox PascoliDelLago_Text_MomAccept, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PASCOLI_DEL_LAGO_MON, PascoliDelLago_EventScript_MomLeaves
    waitmovement 0
    removeobject LOCALID_PASCOLI_DEL_LAGO_MON
    setflag FLAG_HIDE_MOM_FROM_FIELD
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 4
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_START_JOURNEY SUB_QUEST_START_JOURNEY_3
    updatequestmsg QUEST_START_JOURNEY
    releaseall
    end

PascoliDelLago_EventScript_ApproachMomLower:
    walk_fast_right
    walk_fast_right
    walk_fast_right
    walk_fast_down
    walk_fast_down
    walk_fast_down
    face_right
    step_end

PascoliDelLago_EventScript_ApproachMomUpper:
    walk_fast_down
    walk_fast_right
    walk_fast_right
    walk_fast_down
    walk_fast_down
    walk_fast_down
    face_right
    step_end

PascoliDelLago_EventScript_MomLeaves:
    walk_up
    walk_up
    walk_up
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    step_end

PascoliDelLago_Text_IHaveToHurry:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I have to hurry!$"

PascoliDelLago_Text_MomCry:
    .string "???: Ahhhhhh.$"

PascoliDelLago_Text_BetterNotInThisDirection:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: It's better not to go in\n"
    .string "this direction.$"

PascoliDelLago_Text_PlayerAsk:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: Mom, what happened?$"

PascoliDelLago_Text_MomExplains:
	.string "{COLOR}{RED}Mom{COLOR}{02}: I had taken a break from work and\n"
	.string "had come to see how Tauros was doing.\p"
	.string "Then they arrived, two of them...\n"
	.string "Houndour, I think. Their eyes were like\l"
	.string "fire... they scared Tauros, who ran away\l"
	.string "across the river into the woods to the\l"
	.string "east. Then those two beasts rushed\l"
    .string "after him.$"

PascoliDelLago_Text_PlayerRevenge:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I didn't think those\n"
	.string "bastards would get so close to the\l"
	.string "farm.\p"
	.string "I'll go into the woods to look for\n"
	.string "Tauros.\l"
	.string "I have to find him before they do.$"

PascoliDelLago_Text_MomWarnings:
	.string "{COLOR}{RED}Mom{COLOR}{02}: No!\n"
    .string "It's too dangerous, and you don't even\l"
    .string "have a Pokémon with you.$"

PascoliDelLago_Text_PlayerAssure:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I'll be careful, I won't make\n"
    .string "myself noticed.\p"
    .string "It's the only way to save Tauros.\n"
    .string "He's too important for the farm.$"

PascoliDelLago_Text_MomAccept:
    .string "{COLOR}{RED}Mom{COLOR}{02}: Okay, you're right. I'll go tell your\n"
    .string "father so he can come and help you.$"

PascoliDelLago_Text_Miltank:
	.string "Mil... Mil... tank!$"

PascoliDelLago_Text_Tauros:
	.string "Tau... Tau... ros!$"

PascoliDelLago_Text_BirchSpendsDaysInLab:
	.string "Tieni questa mappa.$"

PascoliDelLago_Text_TownSign:
	.string "Pascoli del Lago\n"
	.string "{DOWN_ARROW} La Valle$"

PascoliDelLago_Text_PlayersHouse:
	.string "{PLAYER}'s house$"
