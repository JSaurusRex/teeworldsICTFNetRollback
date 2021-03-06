/* File is created by Teetime for the TW+ mod
 */

#include "gamecontext.h"
#include <game/version.h>
#include <engine/shared/config.h>
#include <stdio.h>

#include "bot.h"

bool CGameContext::ShowCommand(int ClientID, CPlayer* pPlayer, const char* pMessage, int *pTeam)
{
	if(StrLeftComp(pMessage, "go") || StrLeftComp(pMessage, "stop") || StrLeftComp(pMessage, "restart"))
	{/* Do nothing */}
	else if(pMessage[0] == '/' || pMessage[0] == '!')
		pMessage++;
	else
		return true;

	int Len = 0;

	// AuthLevel > 0  => Moderator/Admin
	int AuthLevel = Server()->IsAuthed(ClientID);
	// It's a command so we set Team to CHAT_ALL that things like restart can't be written in teamchat and will be visible for everybody
	*pTeam = CHAT_ALL;

	if(StrLeftComp(pMessage, "info"))
	{
		char aBuf[128];
		str_format(aBuf, sizeof(aBuf), "TW+ Mod v.%s created by Teetime. Improved by hardliner66 and JSaurusRex.", MOD_VERSION);
		SendChatTarget(ClientID, aBuf);

		SendChatTarget(ClientID, "For a list of available commands type \"/cmdlist\"");

		str_format(aBuf, sizeof(aBuf), "Gametype: %s", GameType());
		SendChatTarget(ClientID, aBuf);

		if(m_pController->IsIFreeze())
				SendChatTarget(ClientID, "iFreeze is originally created by Tom94. Big thanks to him");
		return false;
	}
	else if(StrLeftComp(pMessage, "credits"))
	{
		SendChatTarget(ClientID, "Credits goes to the whole Teeworlds-community and especially");
		SendChatTarget(ClientID, "to BotoX, Tom and Greyfox. This mod has some of their ideas included.");
		SendChatTarget(ClientID, "Also thanks to fisted and eeeee for their amazing loltext.");
		return false;
	}
	else if(StrLeftComp(pMessage, "cmdlist"))
	{
		SendChatTarget(ClientID, "----- Commands -----");
		SendChatTarget(ClientID, "\"/info\" Information about the mod");
		SendChatTarget(ClientID, "\"/credits\" See some credits");
		SendChatTarget(ClientID, "\"/stats\" Show player stats");

		if(g_Config.m_SvPrivateMessage || AuthLevel)
		{
			SendChatTarget(ClientID, "\"/sayto <Name/ID> <Msg>\" Send a private message to a player");
			SendChatTarget(ClientID, "\"/whisper <Name/ID> <Msg>\" Send a private message to a player");
			SendChatTarget(ClientID, "\"/w <Name/ID> <Msg>\" Send a private message to a player");
			SendChatTarget(ClientID, "\"/r <Msg>\" Answer to the player, the last PM came from");
		}

		if(g_Config.m_SvStopGoFeature)
		{
			SendChatTarget(ClientID, "\"/stop\" Pause the game");
			SendChatTarget(ClientID, "\"/go\" Start the game");
			SendChatTarget(ClientID, "\"/restart\" Start a new round");
		}

		if(g_Config.m_SvBotsEnabled)
		{
			SendChatTarget(ClientID, "\"/difficulty\" Shows the current difficulty.");
			SendChatTarget(ClientID, "\"/d\" Shows the current difficulty.");
			// SendChatTarget(ClientID, "\"/difficulty [difficulty]\" Changes the difficulty or shows all difficulties if called without argument.");
			// SendChatTarget(ClientID, "\"/d [difficulty]\" Changes the difficulty or shows all difficulties if called without argument.");
			SendChatTarget(ClientID, "\"/difficulties\" Show available difficulties");
			SendChatTarget(ClientID, "\"/ds\" Show available difficulties");
			if (g_Config.m_SvBotVsHuman) {
				SendChatTarget(ClientID, "\"/switch\" Vote to switch sides");
			}
		}

		if(g_Config.m_SvXonxFeature)
		{
			SendChatTarget(ClientID, "\"/reset\" Reset the Spectator Slots");
			SendChatTarget(ClientID, "\"/1on1\" - \"6on6\" Starts a war");
		}

		if(CanExec(ClientID, "set_team"))
		{
			SendChatTarget(ClientID, "\"/spec <client id>\" Set player to spectators");
			SendChatTarget(ClientID, "\"/red <client id>\" Set player to red team");
			SendChatTarget(ClientID, "\"/blue <client id>\" Set player to blue team");
		}
		return false;
	}
	else if(StrLeftComp(pMessage, "stop"))
	{
		int team = pPlayer->GetTeam();
		if(team != TEAM_SPECTATORS)
		{
			if(g_Config.m_SvStopGoFeature)
			{
				int maxStops = g_Config.m_SvMaxStopRequestsPerTeam;
				if (maxStops) {
					if (m_pController->m_StopsTaken[team] < maxStops) {
						if(!m_World.m_Paused)
						{
							m_pController->m_StopsTaken[team]++;
							int stopsTaken = m_pController->m_StopsTaken[team];
							m_World.m_Paused = true;

							const char* team_name = team == TEAM_RED ? "Red" : "Blue";
							char aBuf[128];
							str_format(aBuf, sizeof(aBuf), "%s team called for timeout (%d/%d).", team_name, stopsTaken, maxStops);
							SendChat(-1, CHAT_ALL, aBuf);
						}
						m_pController->m_FakeWarmup = 0;
					} else {
						SendChatTarget(ClientID, "Your team has no more stops left!");
					}
				} else {
					if(!m_World.m_Paused)
					{
						m_World.m_Paused = true;
						SendChat(-1, CHAT_ALL, "Game paused.");
					}
					m_pController->m_FakeWarmup = 0;
				}
			}
			else
				SendChatTarget(ClientID, "This feature is not available at the moment.");
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "go"))
	{
		if(pPlayer->GetTeam() != TEAM_SPECTATORS)
		{
			if(g_Config.m_SvStopGoFeature)
			{
				if(CanStartVote(pPlayer))
					StartVoteAs("Unpause game", "go", "", pPlayer);
			}
			else
				SendChatTarget(ClientID, "This feature is not available at the moment.");
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "restart"))
	{
		if(pPlayer->GetTeam() != TEAM_SPECTATORS)
		{
			if(g_Config.m_SvStopGoFeature)
			{
				if(CanStartVote(pPlayer))
					StartVoteAs("Restart round", "restart", "", pPlayer);
			}
			else
				SendChatTarget(ClientID, "This feature is not available at the moment.");
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "switch"))
	{
		if (g_Config.m_SvBotsEnabled && !g_Config.m_SvBotVsHuman) {
			return false;
		}
		if(CanStartVote(pPlayer))
		{
			char aDesc[VOTE_DESC_LENGTH] = "switch";
			char aCmd[VOTE_CMD_LENGTH] = "switch";

			StartVoteAs(aDesc, aCmd, "", pPlayer);
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "difficulties") || StrLeftComp(pMessage, "ds"))
	{
		if (!g_Config.m_SvBotsEnabled) {
			return false;
		}

		SendDifficulties(ClientID);

		return false;
	}
	else if(StrLeftComp(pMessage, "difficulty") || StrLeftComp(pMessage, "d"))
	{
		if (!g_Config.m_SvBotsEnabled) {
			return false;
		}

		// if(CanStartVote(pPlayer))
		// {
		// 	int Args;
		// 	int Difficulty;
		// 	if ((Args = sscanf(pMessage, "difficulty %d", &Difficulty)) >= 1
		// 	||  (Args = sscanf(pMessage, "d %d", &Difficulty)) >= 1)
		// 	{
		// 		if (ValidDifficulty(Difficulty)) {
		// 			char aBuf[64];
		// 			str_format(aBuf, sizeof(aBuf), "Change difficulty to \"%s\"", GetDifficultyName(Difficulty));
		// 			char bBuf[64];
		// 			str_format(bBuf, sizeof(bBuf), "difficulty %d", Difficulty);
		// 			StartVoteAs(aBuf, bBuf, "", pPlayer);
		// 		} else {
		// 			SendChatTarget(ClientID, "Invalid difficulty.");

		// 			SendDifficulties(ClientID);
		// 		}
		// 	} else {
				// if (str_comp_nocase(pMessage, "difficulty") || str_comp_nocase(pMessage, "d")) {
					char bBuf[64];
					str_format(bBuf, sizeof(bBuf), "Current Difficulty: %s", GetDifficultyName(m_BotDifficulty));
					SendChatTarget(ClientID, bBuf);
				// } else {
				// 	SendChatTarget(ClientID, "Invalid difficulty. Difficulty should be a number.");
				// 	SendChatTarget(ClientID, "Usage: /difficulty [difficulty]");
				// }
		// 	}
		// }
		return false;
	}
	else if(StrLeftComp(pMessage, "1on1") || StrLeftComp(pMessage, "2on2") || StrLeftComp(pMessage, "3on3") ||
			StrLeftComp(pMessage, "4on4") || StrLeftComp(pMessage, "5on5") || StrLeftComp(pMessage, "6on6"))
	{
		if(pPlayer->GetTeam() != TEAM_SPECTATORS)
		{
			if(!g_Config.m_SvXonxFeature)
			{
				SendChatTarget(ClientID, "This feature is not available at the moment.");
				return false;
			}
			else
			{
				if(CanStartVote(pPlayer))
				{
					int Mode = (int)pMessage[0] - (int)'0';
					char aBuf[32];
					str_format(aBuf, sizeof(aBuf), "Restart round as %don%d", Mode, Mode);
					char bBuf[32];
					str_format(bBuf, sizeof(aBuf), "xonx %d", Mode);
					StartVoteAs(aBuf, bBuf, "", pPlayer);
				}
			}
		}

		return true;
	}
	else if(StrLeftComp(pMessage, "reset"))
	{
		if(pPlayer->GetTeam() != TEAM_SPECTATORS)
		{
			if(!g_Config.m_SvXonxFeature)
			{
				SendChatTarget(ClientID, "This feature is not available at the moment.");
				return false;
			}
			else
			{
				if(CanStartVote(pPlayer))
					StartVoteAs("No player limit", "reset", "", pPlayer);
			}
		}
		return true;
	}
	else if((Len = StrLeftComp(pMessage, "stats")))
	{
		int ReceiverID = -1;
		char aBuf[32] = { 0 };
		CPlayer *pP = pPlayer;

		if (sscanf(pMessage, "stats %2s", aBuf) > 0)
		{
			pMessage += Len;

			ParsePlayerName((char*) pMessage, &ReceiverID);

			if(IsValidCID(ReceiverID))
			{
				pP = m_apPlayers[ReceiverID];
				str_format(aBuf, sizeof(aBuf), "(%s) ", Server()->ClientName(ReceiverID));
			}
			else
			{
				SendChatTarget(ClientID, "No player with this name ingame");
				return false;
			}
		}

		ShowStats(ClientID, ReceiverID);
		return false;
	}
	else if((Len=StrLeftComp(pMessage, "sayto")) || (Len=StrLeftComp(pMessage, "st")) || (Len=StrLeftComp(pMessage, "pm")) || (Len=StrLeftComp(pMessage, "whisper")) || (Len=StrLeftComp(pMessage, "w")))
	{
		if(!g_Config.m_SvPrivateMessage && !AuthLevel)
			SendChatTarget(ClientID, "This feature is not available at the moment.");
		else
		{
			int ReceiverID = -1;

			char *pMsg = str_skip_whitespaces(const_cast<char*>(pMessage + Len));

			if(pMsg[0] == '\0')
			{
				SendChatTarget(ClientID, "Usage: \"/sayto <Name/ID> <Message>\"");
				return false;
			}

			int Len = ParsePlayerName(pMsg, &ReceiverID);

			if(IsValidCID(ReceiverID))
			{
				if(ReceiverID == ClientID)
				{
					SendChatTarget(ClientID, "You can't send yourself a private message");
				}
				else
				{
					pMsg = str_skip_whitespaces(pMsg + Len);

					if(pMsg[0] == '\0')
						SendChatTarget(ClientID, "Your message is empty");
					else
					{
						char aBuf[512];
						str_format(aBuf, sizeof(aBuf), "You received a private message from %s (ID: %d)", Server()->ClientName(ClientID), ClientID);
						SendChatTarget(ReceiverID, aBuf);

						str_format(aBuf, sizeof(aBuf), "%s: %s", Server()->ClientName(ClientID), pMsg);
						SendChatTarget(ReceiverID, aBuf);
						SendChatTarget(ClientID, "PM successfully sent");

						m_apPlayers[ReceiverID]->m_LastPMReceivedFrom = ClientID;
						m_apPlayers[ClientID]->m_LastPMReceivedFrom = ReceiverID;

						str_format(aBuf, sizeof(aBuf), "%d:%s sent a PM to %d:%s", ClientID, Server()->ClientName(ClientID), ReceiverID, Server()->ClientName(ReceiverID));
						Console()->Print(IConsole::OUTPUT_LEVEL_ADDINFO, "PM", aBuf);
					}
				}
			}
			else
				SendChatTarget(ClientID, "No player with this name or ID found");
		}
		return false;
	}
	else if((Len=StrLeftComp(pMessage, "ans")) || (Len=StrLeftComp(pMessage, "r")))
	{
		if(!g_Config.m_SvPrivateMessage && !AuthLevel)
			SendChatTarget(ClientID, "This feature is not available at the moment.");
		else
		{
			int LastChatterID = m_apPlayers[ClientID]->m_LastPMReceivedFrom;
			if(IsValidCID(LastChatterID))
			{
				char *pMsg = str_skip_whitespaces(const_cast<char *>(pMessage+Len));

				if(pMsg[0] == '\0')
					SendChatTarget(ClientID, "Your Message is empty.");
				else
				{
					char aBuf[512];
					str_format(aBuf, sizeof(aBuf), "%s: %s", Server()->ClientName(ClientID), pMsg);
					SendChatTarget(LastChatterID, aBuf);
					SendChatTarget(ClientID, "PM successfully sent");

					m_apPlayers[LastChatterID]->m_LastPMReceivedFrom = ClientID;
					m_apPlayers[ClientID]->m_LastPMReceivedFrom = LastChatterID;

					str_format(aBuf, sizeof(aBuf), "%d:%s sent a PM to %d:%s", ClientID, Server()->ClientName(ClientID), LastChatterID, Server()->ClientName(LastChatterID));
					Console()->Print(IConsole::OUTPUT_LEVEL_ADDINFO, "PM", aBuf);
				}
			}
			else
			{
				if(LastChatterID == -1)
					SendChatTarget(ClientID, "Please first write a PM with /sayto");
				else if(LastChatterID == -2)
					SendChatTarget(ClientID, "The original player leaved, please use /sayto to write a new PM");
				else //dafuq?
					SendChatTarget(ClientID, "Something went kinda wrong. Use /sayto");
			}
		}
		return false;
	}
	else if(StrLeftComp(pMessage, "emote"))
	{
		char aType[16];
		int Time = -1, Args;
		if(!pPlayer->GetCharacter())
		{
			SendChatTarget(ClientID, "\"emote\" is not available at the moment. Join game or wait till you spawn to set.");
			return false;
		}

		if((Args = sscanf(pMessage, "emote %15s %d", aType, &Time)) >= 1)
		{
			if(Args < 2 || Time < 0)
				Time = 2;

			int Tick = Server()->Tick() + Time*Server()->TickSpeed();

			if(!str_comp_nocase(aType, "surprise"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_SURPRISE, Tick);
			else if(!str_comp_nocase(aType, "blink"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_BLINK, Tick);
			else if(!str_comp_nocase(aType, "happy"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_HAPPY, Tick);
			else if(!str_comp_nocase(aType, "pain"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_PAIN, Tick);
			else if(!str_comp_nocase(aType, "angry"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_ANGRY, Tick);
			else if(!str_comp_nocase(aType, "normal"))
				pPlayer->GetCharacter()->SetEmoteFix(EMOTE_NORMAL, Tick);
			else
				SendChatTarget(ClientID, "Unkown emote. Type \"/emote\"");
		}
		else
		{
			SendChatTarget(ClientID, "Usage: /emote <type> <sec>. Use as type: \"surprise\", \"blink\", \"happy\", \"pain\", \"angry\" or \"normal\".");
			SendChatTarget(ClientID, "Example: \"/emote pain 10\" for showing 10 seconds emote pain.");
		}

		return false;
	}
	else if(StrLeftComp(pMessage, "spec"))
	{
		if(AuthLevel && CanExec(ClientID, "set_team"))
		{
			int ID;
			if(sscanf(pMessage, "spec %d", &ID) == 1)
			{
				if (!IsValidCID(ID))
					SendChatTarget(ClientID, "Invalid ID");
				else
					m_apPlayers[ID]->SetTeam(TEAM_SPECTATORS);
			}
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "red"))
	{
		if(AuthLevel && CanExec(ClientID, "set_team"))
		{
			int ID;
			if(sscanf(pMessage, "red %d", &ID) == 1)
			{
				if (!IsValidCID(ID))
					SendChatTarget(ClientID, "Invalid ID");
				else
					m_apPlayers[ID]->SetTeam(TEAM_RED);
			}
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "blue"))
	{
		if(AuthLevel && CanExec(ClientID, "set_team"))
		{
			int ID;
			if (sscanf(pMessage, "blue %d", &ID) == 1)
			{
				if (!IsValidCID(ID))
					SendChatTarget(ClientID, "Invalid ID");
				else
					m_apPlayers[ID]->SetTeam(TEAM_BLUE);
			}
		}
		return true;
	}
	else if(StrLeftComp(pMessage, "lat"))
	{
		bool latcomp = m_apPlayers[ClientID]->useLatComp;
		m_apPlayers[ClientID]->useLatComp = !latcomp;

		if(!latcomp)
			SendChatTarget(ClientID, "enabled latency compensation");
		else
			SendChatTarget(ClientID, "disabled latency compensation");
	}
	else
		SendChatTarget(ClientID, "No such command. Type \"/cmdlist\" to get a list of available commands");

	return false;
}

bool CGameContext::CanExec(int ClientID, const char* pCommand)
{
	return (Server()->IsAuthed(ClientID) == 2 || (Server()->IsAuthed(ClientID) == 1 && Console()->GetCommandInfo(pCommand, CFGFLAG_SERVER, false)->GetAccessLevel() == IConsole::ACCESS_LEVEL_MOD));
}

int CGameContext::ParsePlayerName(char *pMsg, int *ClientID)
{
	//Give names a higher priority than IDs because players doesn't see IDs but can choose names with tab

	int NameLength, NameLengthHit = 0;
	*ClientID = -1;
	bool ShortenName = false;
	pMsg = str_skip_whitespaces(pMsg);

	if(m_pController->IsIFreeze() && str_comp_num(pMsg, "[F] ", 4) == 0)
	{
		ShortenName = true;
		pMsg += 4;
	}

	// Search for name
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		NameLength = str_length(Server()->ClientName(i));
		//In iFreeze: If a player has the frozen tag and his name is long, ignore the last 4 chars (+1 for \0)
		int Count = (ShortenName && NameLength > MAX_NAME_LENGTH-5) ? NameLength -4 : NameLength;

		if((str_comp_nocase_num(pMsg, Server()->ClientName(i), Count) == 0) && (pMsg[Count] == ' ' || pMsg[Count] == '\0'))
		{
			*ClientID = i;
			NameLengthHit = NameLength;
		}
	}
	if(*ClientID != -1)
		return NameLengthHit;

	// if nobody found by name, check if ID is given
	if (*ClientID < 0 && (sscanf(pMsg, "%d", ClientID) == 1))
	{
		int Len = 0;
		while (*pMsg && *pMsg != ' ')
		{
			Len++;
			pMsg++;
		}
		return Len;
	}

	return 0;
}

int CGameContext::StrLeftComp(const char *pOrigin, const char *pSub)
{
	const char *pSlide = pOrigin;
	while(*pSlide && *pSub)
	{
		if(*pSlide == *pSub)
		{
			pSlide++;
			pSub++;

			if(*pSub == '\0' && (*pSlide == ' ' || *pSlide == '\0'))
				return pSlide - pOrigin;
		}
		else
			return 0;
	}
	return 0;
}
