/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_VARIABLES_H
#define GAME_VARIABLES_H
#undef GAME_VARIABLES_H // this file will be included several times


// client
MACRO_CONFIG_INT(ClPredict, cl_predict, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Predict client movements")
MACRO_CONFIG_INT(ClNameplates, cl_nameplates, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show name plates")
MACRO_CONFIG_INT(ClNameplatesAlways, cl_nameplates_always, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Always show name plates disregarding of distance")
MACRO_CONFIG_INT(ClNameplatesTeamcolors, cl_nameplates_teamcolors, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Use team colors for name plates")
MACRO_CONFIG_INT(ClNameplatesSize, cl_nameplates_size, 50, 0, 100, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Size of the name plates from 0 to 100%")
MACRO_CONFIG_INT(ClAutoswitchWeapons, cl_autoswitch_weapons, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Auto switch weapon on pickup")

MACRO_CONFIG_INT(ClShowhud, cl_showhud, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show ingame HUD")
MACRO_CONFIG_INT(ClShowChatFriends, cl_show_chat_friends, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show only chat messages from friends")
MACRO_CONFIG_INT(ClShowfps, cl_showfps, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Show ingame FPS counter")

MACRO_CONFIG_INT(ClAirjumpindicator, cl_airjumpindicator, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClThreadsoundloading, cl_threadsoundloading, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Load sound files threaded")

MACRO_CONFIG_INT(ClWarningTeambalance, cl_warning_teambalance, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Warn about team balance")

MACRO_CONFIG_INT(ClMouseDeadzone, cl_mouse_deadzone, 300, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMouseFollowfactor, cl_mouse_followfactor, 60, 0, 200, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMouseMaxDistance, cl_mouse_max_distance, 800, 0, 0, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

MACRO_CONFIG_INT(EdShowkeys, ed_showkeys, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

//MACRO_CONFIG_INT(ClFlow, cl_flow, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")

MACRO_CONFIG_INT(ClShowWelcome, cl_show_welcome, 1, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "")
MACRO_CONFIG_INT(ClMotdTime, cl_motd_time, 10, 0, 100, CFGFLAG_CLIENT|CFGFLAG_SAVE, "How long to show the server message of the day")

MACRO_CONFIG_STR(ClVersionServer, cl_version_server, 100, "version.teeworlds.com", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Server to use to check for new versions")

MACRO_CONFIG_STR(ClLanguagefile, cl_languagefile, 255, "", CFGFLAG_CLIENT|CFGFLAG_SAVE, "What language file to use")

MACRO_CONFIG_INT(PlayerUseCustomColor, player_use_custom_color, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toggles usage of custom colors")
MACRO_CONFIG_INT(PlayerColorBody, player_color_body, 65408, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player body color")
MACRO_CONFIG_INT(PlayerColorFeet, player_color_feet, 65408, 0, 0xFFFFFF, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player feet color")
MACRO_CONFIG_STR(PlayerSkin, player_skin, 24, "default", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Player skin")

MACRO_CONFIG_INT(UiPage, ui_page, 6, 0, 10, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface page")
MACRO_CONFIG_INT(UiToolboxPage, ui_toolbox_page, 0, 0, 2, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Toolbox page")
MACRO_CONFIG_STR(UiServerAddress, ui_server_address, 64, "localhost:8303", CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface server address")
MACRO_CONFIG_INT(UiScale, ui_scale, 100, 50, 150, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface scale")
MACRO_CONFIG_INT(UiMousesens, ui_mousesens, 100, 5, 100000, CFGFLAG_SAVE|CFGFLAG_CLIENT, "Mouse sensitivity for menus/editor")

MACRO_CONFIG_INT(UiColorHue, ui_color_hue, 160, 0, 255, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface color hue")
MACRO_CONFIG_INT(UiColorSat, ui_color_sat, 70, 0, 255, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface color saturation")
MACRO_CONFIG_INT(UiColorLht, ui_color_lht, 175, 0, 255, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface color lightness")
MACRO_CONFIG_INT(UiColorAlpha, ui_color_alpha, 228, 0, 255, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Interface alpha")

MACRO_CONFIG_INT(GfxNoclip, gfx_noclip, 0, 0, 1, CFGFLAG_CLIENT|CFGFLAG_SAVE, "Disable clipping")

// server
MACRO_CONFIG_INT(SvWarmup, sv_warmup, 0, 0, 0, CFGFLAG_SERVER, "Number of seconds to do warmup before round starts")
MACRO_CONFIG_STR(SvMotd, sv_motd, 900, "", CFGFLAG_SERVER, "Message of the day to display for the clients")
MACRO_CONFIG_INT(SvTeamdamage, sv_teamdamage, 0, 0, 1, CFGFLAG_SERVER, "Team damage")
MACRO_CONFIG_STR(SvMaprotation, sv_maprotation, 768, "", CFGFLAG_SERVER, "Maps to rotate between")
MACRO_CONFIG_INT(SvRoundsPerMap, sv_rounds_per_map, 1, 1, 100, CFGFLAG_SERVER, "Number of rounds on each map before rotating")
MACRO_CONFIG_INT(SvRoundSwap, sv_round_swap, 1, 0, 1, CFGFLAG_SERVER, "Swap teams between rounds")
MACRO_CONFIG_INT(SvPowerups, sv_powerups, 1, 0, 1, CFGFLAG_SERVER, "Allow powerups like ninja")
MACRO_CONFIG_INT(SvScorelimit, sv_scorelimit, 20, 0, 1000, CFGFLAG_SERVER, "Score limit (0 disables)")
MACRO_CONFIG_INT(SvTimelimit, sv_timelimit, 0, 0, 1000, CFGFLAG_SERVER, "Time limit in minutes (0 disables)")
MACRO_CONFIG_STR(SvGametype, sv_gametype, 32, "dm", CFGFLAG_SERVER, "Game type (dm, tdm, ctf, idm, itdm, ictf, ifreeze, gdm, gtdm, gctf)")
MACRO_CONFIG_INT(SvTournamentMode, sv_tournament_mode, 0, 0, 1, CFGFLAG_SERVER, "Tournament mode. When enabled, players joins the server as spectator")
MACRO_CONFIG_INT(SvSpamprotection, sv_spamprotection, 1, 0, 1, CFGFLAG_SERVER, "Spam protection")
MACRO_CONFIG_INT(SvAllowEmoteSpam, sv_allow_emote_spam, 1, 0, 1, CFGFLAG_SERVER, "Allow emote spam")

MACRO_CONFIG_INT(SvRespawnDelayTDM, sv_respawn_delay_tdm, 3, 0, 10, CFGFLAG_SERVER, "Time needed to respawn after death in tdm gametype")

MACRO_CONFIG_INT(SvSpectatorSlots, sv_spectator_slots, 0, 0, MAX_CLIENTS, CFGFLAG_SERVER, "Number of slots to reserve for spectators")
MACRO_CONFIG_INT(SvTeambalanceTime, sv_teambalance_time, 1, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before autobalancing teams")
MACRO_CONFIG_INT(SvInactiveKickTime, sv_inactivekick_time, 3, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before taking care of inactive players")
MACRO_CONFIG_INT(SvInactiveKick, sv_inactivekick, 1, 0, 2, CFGFLAG_SERVER, "How to deal with inactive players (0=move to spectator, 1=move to free spectator slot/kick, 2=kick)")

MACRO_CONFIG_INT(SvStrictSpectateMode, sv_strict_spectate_mode, 0, 0, 1, CFGFLAG_SERVER, "Restricts information in spectator mode")
MACRO_CONFIG_INT(SvVoteSpectate, sv_vote_spectate, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to move players to spectators")
MACRO_CONFIG_INT(SvVoteSpectateRejoindelay, sv_vote_spectate_rejoindelay, 3, 0, 1000, CFGFLAG_SERVER, "How many minutes to wait before a player can rejoin after being moved to spectators by vote")
MACRO_CONFIG_INT(SvVoteKick, sv_vote_kick, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to kick players")
MACRO_CONFIG_INT(SvVoteKickMin, sv_vote_kick_min, 0, 0, MAX_CLIENTS, CFGFLAG_SERVER, "Minimum number of players required to start a kick vote")
MACRO_CONFIG_INT(SvVoteKickBantime, sv_vote_kick_bantime, 5, 0, 1440, CFGFLAG_SERVER, "The time to ban a player if kicked by vote. 0 makes it just use kick")

//Server Bots
MACRO_CONFIG_INT(SvBotsEnabled, sv_bots_enabled, 0, 0, 1, CFGFLAG_SERVER, "Enable bots")
MACRO_CONFIG_INT(SvBotStartDifficulty, sv_bot_start_difficulty, 3, -3, 99, CFGFLAG_SERVER, "Bot Start Difficulty")
MACRO_CONFIG_INT(SvBotAccuracy, sv_bot_accuracy, 52, 0, 100, CFGFLAG_SERVER, "Bot Accuracy")
MACRO_CONFIG_INT(SvBotDelay, sv_bot_delay, 10, 0, 50, CFGFLAG_SERVER, "Bot Delay")
MACRO_CONFIG_INT(SvBotReach, sv_bot_reach, 100, 0, 100, CFGFLAG_SERVER, "Bot Aim Distance in percent")
MACRO_CONFIG_INT(SvBotHookReach, sv_bot_hook_reach, 100, 0, 100, CFGFLAG_SERVER, "Bot Hook Distance in percent")
MACRO_CONFIG_INT(SvBotSlots, sv_bot_slots, 2, 0, MAX_CLIENTS, CFGFLAG_SERVER, "Number of slots to reserve for bots")
MACRO_CONFIG_INT(SvBotVsHuman, sv_bot_vs_human, 1, 0, 1, CFGFLAG_SERVER, "If bots only join the enemy team")
MACRO_CONFIG_INT(SvBotSwitchTime, sv_bot_switch_time, 5, 0, 600, CFGFLAG_SERVER, "Time to switch sides")
MACRO_CONFIG_STR(SvBotSkin, sv_bot_skin, 24, "default", CFGFLAG_SERVER, "Bot skin")
MACRO_CONFIG_INT(SvBotAllowHook, sv_bot_allow_hook, 1, 0, 1, CFGFLAG_SERVER, "Bots are allowed to hook")
MACRO_CONFIG_INT(SvBotAllowPlayerHook, sv_bot_allow_player_hook, 1, 0, 1, CFGFLAG_SERVER, "Bots are allowed to hook player")
MACRO_CONFIG_INT(SvBotAllowMove, sv_bot_allow_move, 1, 0, 1, CFGFLAG_SERVER, "Bots are allowed to move")
MACRO_CONFIG_INT(SvBotAllowFire, sv_bot_allow_fire, 1, 0, 1, CFGFLAG_SERVER, "Bots fire")
MACRO_CONFIG_INT(SvBotDrawTarget, sv_bot_draw_target, 0, 0, 1, CFGFLAG_SERVER, "Show bot target")
MACRO_CONFIG_INT(SvBotEngineDrawGraph, sv_botengine_draw_graph, 0, 0, 1, CFGFLAG_SERVER, "Draw graph")

// debug
#ifdef CONF_DEBUG // this one can crash the server if not used correctly
	MACRO_CONFIG_INT(DbgDummies, dbg_dummies, 0, 0, 15, CFGFLAG_SERVER, "")
#endif

MACRO_CONFIG_INT(DbgFocus, dbg_focus, 0, 0, 1, CFGFLAG_CLIENT, "")
MACRO_CONFIG_INT(DbgTuning, dbg_tuning, 0, 0, 1, CFGFLAG_CLIENT, "")

// Mute-On-Spam
MACRO_CONFIG_INT(SvChatValue, sv_chat_value, 250, 100, 1000, CFGFLAG_SERVER, "A value which is added on each message and decreased on each tick")
MACRO_CONFIG_INT(SvChatThreshold, sv_chat_threshold, 1000, 250, 10000, CFGFLAG_SERVER, "If this threshold will exceed by too many messages the player will be muted")
MACRO_CONFIG_INT(SvMuteDuration, sv_mute_duration, 60, 0, 3600, CFGFLAG_SERVER, "How long the player will be muted (in seconds)")
MACRO_CONFIG_INT(SvChatMaxDuplicates, sv_chat_max_duplicates, 3, -1, 25, CFGFLAG_SERVER, "How many duplicates of a chat messages is allowed to send in a row (-1 for no limit)")
MACRO_CONFIG_INT(SvVoteMute, sv_vote_mute, 1, 0, 1, CFGFLAG_SERVER, "Allow voting to mute players")
MACRO_CONFIG_INT(SvVoteMuteDuration, sv_vote_mute_duration, 300, 0, 600, CFGFLAG_SERVER, "How many seconds to mute a player after being muted by vote.")

// Anti Capslock
MACRO_CONFIG_INT(SvAntiCapslock, sv_anticapslock, 1, 0, 1, CFGFLAG_SERVER, "If all letters of a chat-message are capitalized they will be lowercased")
MACRO_CONFIG_INT(SvAntiCapslockTolerance, sv_anticapslock_tolerance, 5, 0, 10, CFGFLAG_SERVER, "How many letters of 10 are allowed to be lowercased that it just work")
MACRO_CONFIG_INT(SvAntiCapslockMinimum, sv_anticapslock_minimum, 8, 1, 128, CFGFLAG_SERVER, "Minimum number of letters that the anti-capslock feature works")

//Anticamper
MACRO_CONFIG_INT(SvAnticamper, sv_anticamper, 0, 0, 2, CFGFLAG_SERVER, "0 disables, 1 enables anticamper in all modes and 2 only in instagib gamemodes")
MACRO_CONFIG_INT(SvAnticamperFreeze, sv_anticamper_freeze, 0, 0, 15, CFGFLAG_SERVER, "If a player should freeze on camping (and how long) or die")
MACRO_CONFIG_INT(SvAnticamperTime, sv_anticamper_time, 9, 5, 20, CFGFLAG_SERVER, "How many seconds to wait till the player dies/freezes")
MACRO_CONFIG_INT(SvAnticamperRange, sv_anticamper_range, 300, 100, 1000, CFGFLAG_SERVER, "Distance how far away the player must move to escape anticamper")

// General Stuff
MACRO_CONFIG_INT(SvVoteForceReason, sv_vote_forcereason, 1, 0, 1, CFGFLAG_SERVER, "Allow only votes with a reason (except settings)")
MACRO_CONFIG_INT(SvGoTime, sv_go_time, 5, 0, 10, CFGFLAG_SERVER, "The restart time for the go-command")
MACRO_CONFIG_INT(SvStopGoFeature, sv_stopgo_feature, 1, 0, 1, CFGFLAG_SERVER, "Enable stop/go-feature in chat")
MACRO_CONFIG_INT(SvXonxFeature, sv_xonx_feature, 1, 0, 1, CFGFLAG_SERVER, "Enables chat-commands like /1on1 - /6on6 for wars")
MACRO_CONFIG_INT(SvWarTime, sv_war_time, 15, 0, 600, CFGFLAG_SERVER, "Default warmup-time before a war")
MACRO_CONFIG_INT(SvLaserjumps, sv_laserjumps, 0, 0, 1, CFGFLAG_SERVER, "Enable laserjumps (only in instagib)")
MACRO_CONFIG_INT(SvEmotionalTees, sv_emotional_tees, 1, 0, 1, CFGFLAG_SERVER, "Enable emotional tees")
MACRO_CONFIG_INT(SvPrivateMessage, sv_private_message, 1, 0, 1, CFGFLAG_SERVER, "Enable/Disable private message")
MACRO_CONFIG_INT(SvSpawnprotection, sv_spawnprotection, 0, 0, 5, CFGFLAG_SERVER, "Spawnprotection in seconds (0 disables)")
MACRO_CONFIG_INT(SvLaserReloadTime, sv_laser_reload_time, 800, 0, 2400, CFGFLAG_SERVER, "Reload-time for laser when you are not at killing-spree (Default: 800)")
MACRO_CONFIG_INT(SvRedStartPoints, sv_red_start_points, 0, 0, 1000, CFGFLAG_SERVER, "With how many points the red team starts the next round.")
MACRO_CONFIG_INT(SvBlueStartPoints, sv_blue_start_points, 0, 0, 1000, CFGFLAG_SERVER, "With how many points the blue team starts the next round.")
MACRO_CONFIG_INT(SvMaxStopRequestsPerTeam, sv_max_stop_requests_per_team, 0, 0, 10, CFGFLAG_SERVER, "How often a team can press stop. 0 to disable.")
//
MACRO_CONFIG_STR(SvStatsFile, sv_stats_file, 256, "stats.txt", CFGFLAG_SERVER, "Name of the file where the statistics are stored in")
MACRO_CONFIG_INT(SvStatsOutputlevel, sv_stats_outputlevel, 0, 0, 3, CFGFLAG_SERVER, "How much informations in the statistics-file should be saved (0 to disable saving)")
//
MACRO_CONFIG_STR(SvChatMessage, sv_chat_message, 256, "", CFGFLAG_SERVER, "A message which will be periodically shown in chat")
MACRO_CONFIG_INT(SvChatMessageInterval, sv_chat_message_interval, 15, 7, 1000000, CFGFLAG_SERVER, "The interval in minutes where the message is sent to chat")
MACRO_CONFIG_INT(SvWallshotOnly, sv_wallshot_only, 0, 0, 1, CFGFLAG_SERVER, "Only wallshots can kill if this is set to 1")

// Loltext
MACRO_CONFIG_INT(SvLoltextHspace, sv_loltext_hspace, 14, 10, 25, CFGFLAG_SERVER, "Horizontal offset between loltext 'pixels'")
MACRO_CONFIG_INT(SvLoltextVspace, sv_loltext_vspace, 14, 10, 25, CFGFLAG_SERVER, "Vertical offset between loltext 'pixels'")
MACRO_CONFIG_INT(SvLoltextLifespan, sv_loltext_lifespan, 50, 25, 100, CFGFLAG_SERVER, "How long the loltext is shown")
MACRO_CONFIG_INT(SvLoltextShow, sv_loltext_show, 0, 0, 1, CFGFLAG_SERVER, "Show loltext")

// Grenade
MACRO_CONFIG_INT(SvGrenadeMinDamage, sv_grenade_min_damage, 4, 3, 6, CFGFLAG_SERVER, "Minimum damage the grenade must make to kill the player (depends how far away the bullet explodes)")
MACRO_CONFIG_INT(SvGrenadeAmmo, sv_grenade_ammo, 6, -1, 10, CFGFLAG_SERVER, "How much ammo for the grenade")
MACRO_CONFIG_INT(SvGrenadeAmmoRegen, sv_grenade_ammo_regen, 1000, 800, 2000, CFGFLAG_SERVER, "Time till one bullet regenerates")

//iFreeze
MACRO_CONFIG_INT(SvIFreezeAutomeltTime, sv_ifreeze_automelt_time, 30, 10, 120, CFGFLAG_SERVER, "Time till the player respawn automatically when he's frozen")
MACRO_CONFIG_INT(SvIFreezeMeltRange, sv_ifreeze_melt_range, 100, 10, 1000, CFGFLAG_SERVER, "Maximum range to melt a player")
MACRO_CONFIG_INT(SvIFreezeMeltTime, sv_ifreeze_melt_time, 1200, 500, 5000, CFGFLAG_SERVER, "Time (in ms) the player must stand next to a player to melt him")
MACRO_CONFIG_INT(SvIFreezeMeltRespawn, sv_ifreeze_melt_respawn, 1, 0, 1, CFGFLAG_SERVER, "If a player respawns after he was being melted")
MACRO_CONFIG_INT(SvIFreezeFrozenTag, sv_ifreeze_frozen_tag, 1, 0, 1, CFGFLAG_SERVER, "If frozen players have \"[F]\" in front of their name")
MACRO_CONFIG_INT(SvIFreezeJoinFrozen, sv_ifreeze_join_frozen, 0, 0, 1, CFGFLAG_SERVER, "New players join a current game as frozen players")

// Killingspree
MACRO_CONFIG_INT(SvKillingspreeKills, sv_kspree_kills, 5, 3, 20, CFGFLAG_SERVER, "How many kills are needed to be on a killing-spree")
MACRO_CONFIG_INT(SvKillingspreeIFreeze, sv_kspree_ifreeze, 1, 0, 1, CFGFLAG_SERVER, "Give the killingspree award only in iFreeze")
MACRO_CONFIG_INT(SvKillingspreeAward, sv_kspree_award, 0, 0, 1, CFGFLAG_SERVER, "If players with more than \"sv_killingspree_kills\" kills get the killingspree award")
MACRO_CONFIG_INT(SvKillingspreeAwardLasers, sv_kspree_award_laser, 3, 1, 10, CFGFLAG_SERVER, "How many lasers will shot when you got the award")
MACRO_CONFIG_INT(SvKillingspreeAwardLasersSplit, sv_kspree_award_laser_split, 1, 1, 10, CFGFLAG_SERVER, "Split of the lasers while having the award")
MACRO_CONFIG_INT(SvKillingspreeAwardFiredelay, sv_kspree_award_laser_firedelay, 100, 0, 800, CFGFLAG_SERVER, "Firedelay of the weapon when you got the award")

MACRO_CONFIG_INT(SvBotDbEnabled, sv_bot_db_enabled, 0, 0, 1, CFGFLAG_SERVER, "Enables the bot.db")
MACRO_CONFIG_STR(SvBotDbFile, sv_bot_db_file, 1024, "", CFGFLAG_SERVER, "The name of the bot.db")
#endif
