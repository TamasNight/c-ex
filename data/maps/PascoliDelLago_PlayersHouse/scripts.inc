PascoliDelLago_PlayersHouse_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PascoliDelLago_PlayersHouse_OnFrame
	.byte 0

PascoliDelLago_PlayersHouse_OnFrame:
	map_script_2 VAR_PASCOLI_DEL_LAGO_INTRO_STATE, 0, PascoliDelLago_PlayersHouse_EventScript_WakeUp
	.2byte 0


PascoliDelLago_PlayersHouse_EventScript_WakeUp::
	lockall
	delay 16
	setflag FLAG_SYS_QUEST_MENU_GET
	applymovement LOCALID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	delay 16
	msgbox PascoliDelLago_PlayersHouse_Text_WakeUp, MSGBOX_DEFAULT
	delay 8
	msgbox PascoliDelLago_PlayersHouse_Text_YesGrandma, MSGBOX_DEFAULT
	msgbox PascoliDelLago_PlayersHouse_Text_BeAMan, MSGBOX_DEFAULT
	delay 8
	msgbox PascoliDelLago_PlayersHouse_Text_FinallyGo, MSGBOX_DEFAULT
	closemessage
	setvar VAR_PASCOLI_DEL_LAGO_INTRO_STATE 1
	startquest QUEST_START_JOURNEY
    subquestmenu QUEST_MENU_COMPLETE_QUEST QUEST_START_JOURNEY SUB_QUEST_START_JOURNEY_1
	releaseall
	end

PascoliDelLago_PlayersHouse_EventScript_Grandma::
    goto_if_ge VAR_KNIGHT_WAY_STATE, 1, PascoliDelLago_PlayersHouse_EventScript_RememberHowYouAre
    msgbox PascoliDelLago_PlayersHouse_Text_StillHere, MSGBOX_NPC
    end

PascoliDelLago_PlayersHouse_EventScript_RememberHowYouAre::
    msgbox PascoliDelLago_PlayersHouse_Text_RememberHowYouAre, MSGBOX_NPC
    end

PascoliDelLago_PlayersHouse_EventScript_Mom::
    lockall
    msgbox PascoliDelLago_PlayersHouse_Text_MomCry, MSGBOX_DEFAULT
    delay 8
    msgbox PascoliDelLago_PlayersHouse_Text_MomGoodbye, MSGBOX_NPC
    releaseall
    end

PacsoliDelLago_PlayersHouse_EventScript_DadGiftTrigger::
    applymovement LOCALID_PLAYER, Common_Movement_FaceRight
    waitmovement 0
    goto PascoliDelLago_PlayersHouse_EventScript_DadGift

PascoliDelLago_PlayersHouse_EventScript_DadGift::
    lock
    goto_if_eq VAR_KNIGHT_WAY_STATE, 2, PascoliDelLago_PlayersHouse_EventScript_DadGiftEnd
    applymovement LOCALID_FATHER_HOME, Common_Movement_FacePlayer
    waitmovement 0
    msgbox PascoliDelLago_PlayersHouse_Text_DadGift, MSGBOX_DEFAULT
    giveitem ITEM_POTION, 5
    setvar VAR_KNIGHT_WAY_STATE 2
    clearflag FLAG_HIDE_MILTANK_FROM_FIELD
    delay 8
    goto PascoliDelLago_PlayersHouse_EventScript_DadGiftEnd

PascoliDelLago_PlayersHouse_EventScript_DadGiftEnd::
    lock
    applymovement LOCALID_FATHER_HOME, Common_Movement_FacePlayer
    waitmovement 0
    msgbox PascoliDelLago_PlayersHouse_Text_DadGiftEnd, MSGBOX_DEFAULT
    release
    end

PascoliDelLago_PlayersHouse_Text_DadGift:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: Before you go, I have prepared\n"
    .string "some of the healing herbs that grow in\n"
    .string "the Alpi for you.$"

PascoliDelLago_PlayersHouse_Text_DadGiftEnd:
    .string "{COLOR}{GREEN}Father{COLOR}{02}: Take care of yourself and make\n"
    .string "us proud.$"

PascoliDelLago_PlayersHouse_Text_MomCry:
    .string "{COLOR}{RED}Mom{COLOR}{02}: ... ...\p"
    .string "(sniff)$"

PascoliDelLago_PlayersHouse_Text_MomGoodbye:
	.string "{COLOR}{RED}Mom{COLOR}{02}: Be brave, my dear... and come back\n"
	.string "to us... no matter how long the road may\l"
	.string "be...$"

PascoliDelLago_PlayersHouse_Text_WakeUp:
    .string "{COLOR}{RED}Grandma{COLOR}{02}: You got up late, kid...\p"
    .string "{COLOR}{BLUE}Miltank {COLOR}{02}won't wait, and neither will the\n"
    .string "sun...\p"
    .string "Go check the stables before your dad\n"
    .string "gets mad.$"

PascoliDelLago_PlayersHouse_Text_YesGrandma:
    .string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: I'm sorry, Grandma, you're\n"
    .string "right...\p"
    .string "But I had a very strange dream about a\n"
    .string "shadow stretching over the farm.$"

PascoliDelLago_PlayersHouse_Text_BeAMan:
	.string "{COLOR}{RED}Grandma{COLOR}{02}: Don't make excuses. Your\n"
	.string "grandfather always said: every day\l"
	.string "that the earth sees you working, you\l"
	.string "become a little more of a man.\p"
	.string "But maybe you don't want to be like him.$"

PascoliDelLago_PlayersHouse_Text_FinallyGo:
	.string "{COLOR}{BLUE}{PLAYER}{COLOR}{02}: It wasn't an excuse...\n"
	.string "anyway, I'm going now.$"

PascoliDelLago_PlayersHouse_Text_StillHere:
	.string "{COLOR}{RED}Grandma{COLOR}{DARK_GRAY}: What are you still doing here?\n"
	.string "Go on!$"


PlayersHouse_1F_Text_IsntItNiceInHere:
	.string "MOM: See, {PLAYER}?\n"
	.string "Isn't it nice in here, too?$"

PlayersHouse_1F_Text_MoversPokemonGoSetClock:
	.string "The mover's POKéMON do all the work\n"
	.string "of moving us in and cleaning up after.\l"
	.string "This is so convenient!\p"
	.string "{PLAYER}, your room is upstairs.\n"
	.string "Go check it out, dear!\p"
	.string "DAD bought you a new clock to mark\n"
	.string "our move here.\l"
	.string "Don't forget to set it!$"

PlayersHouse_1F_Text_ArentYouInterestedInRoom:
	.string "MOM: Well, {PLAYER}?\p"
	.string "Aren't you interested in seeing your\n"
	.string "very own room?$"

PlayersHouse_1F_Text_GoSetTheClock:
	.string "MOM: {PLAYER}.\p"
	.string "Go set the clock in your room, honey.$"

PlayersHouse_1F_Text_OhComeQuickly:
	.string "MOM: Oh! {PLAYER}, {PLAYER}!\n"
	.string "Quick! Come quickly!$"

PlayersHouse_1F_Text_MaybeDadWillBeOn:
	.string "MOM: Look! It's PETALBURG GYM!\n"
	.string "Maybe DAD will be on!$"

PlayersHouse_1F_Text_ItsOverWeMissedHim:
	.string "MOM: Oh… It's over.\p"
	.string "I think DAD was on, but we missed him.\n"
	.string "Too bad.$"

PlayersHouse_1F_Text_GoIntroduceYourselfNextDoor:
	.string "Oh, yes.\n"
	.string "One of DAD's friends lives in town.\p"
	.string "PROF. BIRCH is his name.\p"
	.string "He lives right next door, so you should\n"
	.string "go over and introduce yourself.$"

PlayersHouse_1F_Text_SeeYouHoney:
	.string "MOM: See you, honey!$"

PlayersHouse_1F_Text_DidYouMeetProfBirch:
	.string "MOM: Did you introduce yourself to\n"
	.string "PROF. BIRCH?$"

PlayersHouse_1F_Text_YouShouldRestABit:
	.string "MOM: How are you doing, {PLAYER}?\n"
	.string "You look a little tired.\p"
	.string "I think you should rest a bit.$"

PlayersHouse_1F_Text_TakeCareHoney:
	.string "MOM: Take care, honey!$"

PlayersHouse_1F_Text_GotDadsBadgeHeresSomethingFromMom:
	.string "MOM: Oh? Did DAD give you that BADGE?\p"
	.string "Then here's something from your MOM!$"

PlayersHouse_1F_Text_DontPushYourselfTooHard:
	.string "Don't push yourself too hard, dear.\n"
	.string "You can always come home.\p"
	.string "Go for it, honey!$"

PlayersHouse_1F_Text_IsThatAPokenav:
	.string "MOM: What is that, honey? A POKéNAV?\n"
	.string "Someone from DEVON gave it to you?\p"
	.string "Well, honey, how about registering\n"
	.string "your mom?\p"
	.string "… … …$"

PlayersHouse_1F_Text_RegisteredMom:
	.string "Registered MOM\n"
	.string "in the POKéNAV.$"

PlayersHouse_1F_Text_Vigoroth1:
	.string "Fugiiiiih!$"

PlayersHouse_1F_Text_Vigoroth2:
	.string "Huggoh, uggo uggo…$"

PlayersHouse_1F_Text_ReportFromPetalburgGym:
	.string "INTERVIEWER: …We brought you this\n"
	.string "report from in front of PETALBURG GYM.$"

PlayersHouse_1F_Text_TheresAMovieOnTV:
	.string "There is a movie on TV.\p"
	.string "Two men are dancing on a big piano\n"
	.string "keyboard.\p"
	.string "Better get going!$"

PlayersHouse_1F_Text_RunningShoesManual:
	.string "It's the instruction booklet for the\n"
	.string "RUNNING SHOES.\p"
	.string "“Press the B Button to run while\n"
	.string "wearing your RUNNING SHOES.\p"
	.string "“Lace up your RUNNING SHOES and hit\n"
	.string "the road running!”$"

PlayersHouse_1F_Text_TicketFromBrineyCameForYou:
	.string "DAD: Hm?\p"
	.string "Hey, it's {PLAYER}!\p"
	.string "It's been a while since I saw you,\n"
	.string "but you look…stronger, somehow.\p"
	.string "That's the impression I get.\n"
	.string "But your old man hasn't given up yet!\p"
	.string "Oh, yes, I have something for you.\n"
	.string "This came to you from someone named\l"
	.string "MR. BRINEY.$"

PlayersHouse_1F_Text_PortsInSlateportLilycove:
	.string "DAD: Hm, a TICKET for a ferry?\p"
	.string "If I recall, there are ferry ports in\n"
	.string "SLATEPORT and LILYCOVE.$"

PlayersHouse_1F_Text_BetterGetBackToGym:
	.string "I'd better get back to PETALBURG GYM.\p"
	.string "MOM, thanks for looking after the house\n"
	.string "while I'm away.$"

PlayersHouse_1F_Text_DadShouldStayLonger:
	.string "MOM: That DAD of yours…\p"
	.string "He comes home for the first time in a\n"
	.string "while, but all he talks about is POKéMON.\p"
	.string "He should relax and stay a little longer.$"

PlayersHouse_1F_Text_IsThatABreakingStory:
	.string "MOM: Is that a breaking news story?$"

PlayersHouse_1F_Text_LatiEmergencyNewsFlash:
	.string "We bring you this emergency\n"
	.string "news flash!\p"
	.string "In various HOENN locales, there have\n"
	.string "been reports of a BZZT…colored\l"
	.string "POKéMON in flight.\p"
	.string "The identity of this POKéMON is\n"
	.string "currently unknown.\p"
	.string "We now return you to the regular\n"
	.string "movie program.$"

PlayersHouse_1F_Text_WhatColorDidTheySay:
	.string "MOM: {PLAYER}, did you catch that?\p"
	.string "What color did the announcer say\n"
	.string "that POKéMON was?$"

PlayersHouse_1F_Text_StillUnknownPokemon:
	.string "MOM: Well, isn't that something!\n"
	.string "There are still unknown POKéMON.$"

PascoliDelLago_PlayersHouse_Text_RememberHowYouAre:
	.string "{COLOR}{RED}Grandma{COLOR}{02}: My dear boy...\n"
	.string "Once you’ve tasted the iron and the\l"
	.string "blood, it’s easy to forget who you truly\l"
	.string "are...\p"
	.string "Promise me you’ll remember - no matter\n"
	.string "what you see or do, don’t let the world\l"
	.string "turn your heart cold.$"
