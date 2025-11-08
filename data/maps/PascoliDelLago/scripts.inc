PascoliDelLago_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PascoliDelLago_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PascoliDelLago_OnFrame
    .byte 0

PascoliDelLago_OnFrame:
    map_script_2 VAR_PASCOLI_DEL_LAGO_INTRO_STATE, 6, PascoliDelLago_EventScript_KnightArrive
    .2byte 0

PascoliDelLago_OnTransition:
	setflag FLAG_VISITED_PASCOLI_DEL_LAGO
	end

PascoliDelLago_EventScript_Miltank::
    playmoncry SPECIES_MILTANK, CRY_MODE_NORMAL
	msgbox PascoliDelLago_Text_Miltank, MSGBOX_NPC
	waitmoncry
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
    setflag FLAG_HIDE_MILTANK_FROM_FIELD
    end

PascoliDelLago_EventScript_BetterNotInThisDirection::
    msgbox PascoliDelLago_Text_BetterNotInThisDirection, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkLeft
    waitmovement 0
    end

PascoliDelLago_EventScript_IHaveToHurryToStable::
    lockall
    msgbox PascoliDelLago_Text_IHaveToHurry, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkUp
    waitmovement 0
    releaseall
    end

PascoliDelLago_EventScript_IHaveToHurry::
    msgbox PascoliDelLago_Text_IHaveToHurry, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_PLAYER, Common_Movement_WalkRight
    waitmovement 0
    end

PascoliDelLago_EventScript_Tauros::
    playmoncry SPECIES_TAUROS, CRY_MODE_NORMAL
	msgbox PascoliDelLago_Text_Tauros, MSGBOX_NPC
	waitmoncry
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

PascoliDelLago_EventScript_KnightArrive::
    lockall
    delay 16
    applymovement LOCALID_PLAYER, PascoliDelLago_Movement_PlayerGoingHome
    waitmovement 0
    delay 16
    msgbox PascoliDelLago_Text_KnightIntroduce, MSGBOX_DEFAULT
    delay 8
    msgbox PascoliDelLago_Text_FatherAnswer, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_SaverioAnswer, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_SaverioContinue, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_FatherWorried, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_SaverioNoExcuse, MSGBOX_DEFAULT
    closemessage
    delay 30
    applymovement LOCALID_SAVERIO_INTRO, Common_Movement_FaceRight
    applymovement LOCALID_FATHER_INTRO, Common_Movement_FaceRight
    applymovement LOCALID_RAPIDASH_INTRO, Common_Movement_FaceRight
    waitmovement 0
    msgbox PascoliDelLago_Text_SaverioSoHereYouAre, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_SAVERIO_INTRO, Common_Movement_WalkRight3
    waitmovement 0
    msgbox PascoliDelLago_Text_SaverioExplainMission, MSGBOX_DEFAULT
    closemessage
    delay 30
    msgbox PascoliDelLago_Text_SaverioGivesEquipment, MSGBOX_DEFAULT
    closemessage
    bufferspeciesname STR_VAR_1, SPECIES_HONEDGE
    setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_HONEDGE
    givemon SPECIES_HONEDGE, 5
    showmonpic SPECIES_HONEDGE, 10, 3
    playmoncry SPECIES_HONEDGE, CRY_MODE_NORMAL
    waitmoncry
    message PascoliDelLago_Text_ReceivedStarter
    waitmessage
    waitbuttonpress
    hidemonpic
    msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, PascoliDelLago_EventScript_ReceivedMon
    call Common_EventScript_GetGiftMonPartySlot
    call Common_EventScript_NameReceivedPartyMon
    goto PascoliDelLago_EventScript_ReceivedMon

PascoliDelLago_EventScript_ReceivedMon::
    applymovement LOCALID_FATHER_INTRO, Common_Movement_ExclamationMark
    waitmovement 0
    delay 16
    msgbox PascoliDelLago_Text_FatherShocked, MSGBOX_DEFAULT
    applymovement LOCALID_SAVERIO_INTRO, Common_Movement_FaceLeft
    waitmovement 0
    msgbox PascoliDelLago_Text_SaverioMysterious, MSGBOX_DEFAULT
    msgbox PascoliDelLago_Text_FatherReluctant, MSGBOX_DEFAULT
    closemessage
    delay 16
    msgbox PascoliDelLago_Text_SaverioPreFinal, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_SAVERIO_INTRO, Common_Movement_FaceRight
    waitmovement 0
    delay 30
    msgbox PascoliDelLago_Text_SaverioFinal, MSGBOX_DEFAULT
    closemessage
    applymovement LOCALID_SAVERIO_INTRO, PascoliDelLago_Movement_SaverioFinal
    delay 30
    applymovement LOCALID_RAPIDASH_INTRO, Common_Movement_WalkDown6
    waitmovement 0
    startquest QUEST_KNIGHT_WAY
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_KNIGHT_WAY SUB_QUEST_KNIGHT_WAY_1
    applymovement LOCALID_FATHER_INTRO, PascoliDelLago_Movement_FatherFinal
    waitmovement 0
    msgbox PascoliDelLago_Text_FatherFinal, MSGBOX_DEFAULT
    closemessage
    delay 16
    fadescreen FADE_TO_BLACK
    setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 7
    setvar VAR_KNIGHT_WAY_STATE 1
    setflag FLAG_HIDE_KNIGHT_FROM_FIELD
    setflag FLAG_SYS_POKEMON_GET
    setflag FLAG_PLAYER_IS_KNIGHT
    clearflag FLAG_HIDE_FOLLOWER
    releaseall
    warp MAP_PASCOLI_DEL_LAGO_BRENDANS_HOUSE_1F, 3, 3
    end

PascoliDelLago_EventScript_Father::
    msgbox PascoliDelLago_Text_Father, MSGBOX_NPC
    end

PascoliDelLago_EventScript_Mom::
    msgbox PascoliDelLago_Text_Mom, MSGBOX_NPC
    end


PascoliDelLago_Movement_FatherFinal:
    walk_down
    walk_right
    walk_right
    walk_right
    step_end

PascoliDelLago_Movement_SaverioFinal:
    walk_left
    walk_left
    walk_left
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    step_end

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

PascoliDelLago_Text_KnightIntroduce:
    .string "???: Is it here that {PLAYER}, son of\n"
	.string "Raimondo, lives?$"

PascoliDelLago_Text_FatherAnswer:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: Yes, he lives here, and I am\n"
    .string "Raimondo, but I would like to know who\l"
    .string "you are.$"

PascoliDelLago_Text_SaverioAnswer:
    .string "???: Fair enough, my name is Saverio.$"

PascoliDelLago_Text_SaverioContinue:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: I am a knight of the Duke\n"
	.string "of Iria, and the Duke has requested\l"
	.string "the services of your son.$"

PascoliDelLago_Text_FatherWorried:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: But... but he's just a lad.$"

PascoliDelLago_Text_SaverioNoExcuse:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: He will be until someone\n"
    .string "teaches him how to fight and the\l"
    .string "meaning of loyalty.\p"
    .string "The duke needs arms, not excuses.$"

PascoliDelLago_Text_SaverioSoHereYouAre:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: You must be {PLAYER}, right?\n"
    .string "I suppose you've already heard who I am\l"
    .string "and why I am here, so let's get straight\l"
    .string "to the point.$"

PascoliDelLago_Text_SaverioExplainMission:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: I am here to take you to Forte\n"
    .string "Giove, where you will begin your training\l"
    .string "to serve the Duke.$"

PascoliDelLago_Text_SaverioGivesEquipment:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: Before we depart, the Duke\n"
    .string "entrusted me with these for you.\p"
    .string "A chainmail, forged in Iria, and a\n"
    .string "Pokémon - both marks of those who serve.$"

PascoliDelLago_Text_FatherShocked:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: A chainmail? And a Pokémon?\n"
    .string "For my son? These are gifts of great\l"
	.string "worth... why would the Duke offer such\l"
	.string "things to him?$"

PascoliDelLago_Text_SaverioMysterious:
    .string "{COLOR}{BLUE}Saverio{COLOR}{02}: The Duke sees what others\n"
    .string "cannot. Perhaps your son’s path is\l"
    .string "meant for more than tending the fields.$"

PascoliDelLago_Text_FatherReluctant:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: If that is the Duke’s will, then\n"
    .string "so be it... but take care of him, knight.\l"
    .string "He knows nothing of war.$"

PascoliDelLago_Text_SaverioPreFinal:
	.string "{COLOR}{BLUE}Saverio{COLOR}{02}: None of us did, once...$"

PascoliDelLago_Text_SaverioFinal:
	.string "{PLAYER}, put on your armor and say your\n"
	.string "farewells.\p"
	.string "I’ll be waiting at the edge of the\n"
	.string "pasture - make haste, the road to Forte\l"
	.string "Giove is long and unforgiving.$"

PascoliDelLago_Text_FatherFinal:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: If this is the Duke’s will, then\n"
    .string "so be it... I won’t stand in the way.\p"
    .string "Come inside to change and say goodbye\n"
    .string "to Mom and Grandma before you leave.$"


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

PascoliDelLago_Movement_PlayerGoingHome::
    walk_down
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    walk_right
    delay_8
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    walk_down
    delay_8
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    walk_left
    emote_exclamation_mark
    step_end

PascoliDelLago_Text_ReceivedStarter:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02} received {COLOR}{GREEN}{STR_VAR_1}{COLOR}{02}\n"
	.string "from {COLOR}{BLUE}Saverio{COLOR}{02}!$"

PascoliDelLago_Text_Father:
	.string "{COLOR}{GREEN}Father{COLOR}{02}: Running the farm without you\n"
	.string "isn't the same, but if the duke needs\l"
	.string "you, we have no choice.$"

PascoliDelLago_Text_Mom:
    .string "{COLOR}{RED}Mom{COLOR}{02}: I'm so happy to see you, please\n"
    .string "don't leave us again.$"


