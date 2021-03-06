/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */
#ifndef GAME_SERVER_GAMECONTEXT_H
#define GAME_SERVER_GAMECONTEXT_H

#include <engine/server.h>
#include <engine/console.h>
#include <engine/shared/memheap.h>

#include <game/layers.h>
#include <game/voting.h>

#include "eventhandler.h"
#include "gamecontroller.h"
#include "gameworld.h"
#include "player.h"
#include "mute.h"
#include "botengine.h"

#include "database/database.h"

#include <string>
#include <vector>

/*
	Tick
		Game Context (CGameContext::tick)
			Game World (GAMEWORLD::tick)
				Reset world if requested (GAMEWORLD::reset)
				All entities in the world (ENTITY::tick)
				All entities in the world (ENTITY::tick_defered)
				Remove entities marked for deletion (GAMEWORLD::remove_entities)
			Game Controller (GAMECONTROLLER::tick)
			All players (CPlayer::tick)


	Snap
		Game Context (CGameContext::snap)
			Game World (GAMEWORLD::snap)
				All entities in the world (ENTITY::snap)
			Game Controller (GAMECONTROLLER::snap)
			Events handler (EVENT_HANDLER::snap)
			All players (CPlayer::snap)

*/

class CGameContext : public IGameServer
{
	IServer *m_pServer;
	class IConsole *m_pConsole;
	CLayers m_Layers;
	CCollision m_Collision;
	CNetObjHandler m_NetObjHandler;
	CTuningParams m_Tuning;

	CDatabase m_DataBase;

	static void ConTuneParam(IConsole::IResult *pResult, void *pUserData);
	static void ConTuneReset(IConsole::IResult *pResult, void *pUserData);
	static void ConTuneDump(IConsole::IResult *pResult, void *pUserData);
	static void ConPause(IConsole::IResult *pResult, void *pUserData);
	static void ConChangeMap(IConsole::IResult *pResult, void *pUserData);
	static void ConRestart(IConsole::IResult *pResult, void *pUserData);
	static void ConBroadcast(IConsole::IResult *pResult, void *pUserData);
	static void ConSay(IConsole::IResult *pResult, void *pUserData);
	static void ConSetTeam(IConsole::IResult *pResult, void *pUserData);
	static void ConSetTeamAll(IConsole::IResult *pResult, void *pUserData);
	static void ConSwapTeams(IConsole::IResult *pResult, void *pUserData);
	static void ConShuffleTeams(IConsole::IResult *pResult, void *pUserData);
	static void ConLockTeams(IConsole::IResult *pResult, void *pUserData);
	static void ConAddVote(IConsole::IResult *pResult, void *pUserData);
	static void ConRemoveVote(IConsole::IResult *pResult, void *pUserData);
	static void ConForceVote(IConsole::IResult *pResult, void *pUserData);
	static void ConClearVotes(IConsole::IResult *pResult, void *pUserData);
	static void ConVote(IConsole::IResult *pResult, void *pUserData);
	static void ConchainSpecialMotdupdate(IConsole::IResult *pResult, void *pUserData, IConsole::FCommandCallback pfnCallback, void *pCallbackUserData);

	static void ConFreeze(IConsole::IResult *pResult, void *pUserData);
	static void ConUnFreeze(IConsole::IResult *pResult, void *pUserData);
	static void ConMuteSpec(IConsole::IResult *pResult, void *pUserData);
	static void ConStop(IConsole::IResult *pResult, void *pUserData);
	static void ConGo(IConsole::IResult *pResult, void *pUserData);
	static void ConXonX(IConsole::IResult *pResult, void *pUserData);
	static void ConReset(IConsole::IResult *pResult, void *pUserData);
	static void ConSetName(IConsole::IResult *pResult, void *pUserData);
	static void ConSetClan(IConsole::IResult *pResult, void *pUserData);
	static void ConKill(IConsole::IResult *pResult, void *pUserData);
	static void ConSwitch(IConsole::IResult *pResult, void *pUserData);
	static void ConSetDifficulty(IConsole::IResult *pResult, void *pUserData);
#ifdef USECHEATS
	static void ConGive(IConsole::IResult *pResult, void *pUserData);
	static void ConTakeWeapon(IConsole::IResult *pResult, void *pUserData);
	static void ConTeleport(IConsole::IResult *pResult, void *pUserData);
#endif

	void UpdateBotDifficulty(int difficulty);

	CGameContext(int Resetting);
	void Construct(int Resetting);

	bool m_Resetting;
public:
	//400 ms / 20ms per tick = 20
	#define MAX_PLAYER_HISTORY 40
	int playerHistoryIndex = 0;
	int latencyVariable = 0;
	vec2 playerHistory [MAX_PLAYER_HISTORY] [MAX_CLIENTS];


	IServer *Server() const { return m_pServer; }
	class IConsole *Console() { return m_pConsole; }
	CCollision *Collision() { return &m_Collision; }
	CTuningParams *Tuning() { return &m_Tuning; }

	CGameContext();
	~CGameContext();

	void Clear();

	CEventHandler m_Events;
	CPlayer *m_apPlayers[MAX_CLIENTS];

	IGameController *m_pController;
	CGameWorld m_World;

	// helper functions
	class CCharacter *GetPlayerChar(int ClientID);
	inline bool IsValidCID(int CID) { return (CID >= 0) && (CID < MAX_CLIENTS) && m_apPlayers[CID]; }

	int m_LockTeams;

	// voting
	bool CanStartVote(CPlayer *pPlayer);
	void StartVote(const char *pDesc, const char *pCommand, const char *pReason);
	void StartVoteAs(const char *pDesc, const char *pCommand, const char *pReason, CPlayer *pPlayer);
	void EndVote();
	void SendVoteSet(int ClientID);
	void SendVoteStatus(int ClientID, int Total, int Yes, int No);
	void AbortVoteKickOnDisconnect(int ClientID);

	int CreateLolText(CEntity *pParent, bool Follow, vec2 Pos, vec2 Vel, int Lifespan, const char *pText);
	int CreateLolText(CEntity *pParent, const char *pText);
	void DestroyLolText(int TextID);

	void ShowStats(int ClientID, int ReceiverID=-1);

	int m_VoteCreator;
	int64 m_VoteCloseTime;
	bool m_VoteUpdate;
	int m_VotePos;
	char m_aVoteDescription[VOTE_DESC_LENGTH];
	char m_aVoteCommand[VOTE_CMD_LENGTH];
	char m_aVoteReason[VOTE_REASON_LENGTH];
	int m_NumVoteOptions;
	int m_VoteEnforce;
	enum
	{
		VOTE_ENFORCE_UNKNOWN=0,
		VOTE_ENFORCE_NO,
		VOTE_ENFORCE_YES,
	};
	CHeap *m_pVoteOptionHeap;
	CVoteOptionServer *m_pVoteOptionFirst;
	CVoteOptionServer *m_pVoteOptionLast;

	class CBotEngine *m_pBotEngine;

	// helper functions
	void CreateDamageInd(vec2 Pos, float AngleMod, int Amount);
	void CreateExplosion(vec2 Pos, int Owner, int Weapon, bool NoDamage);
	void CreateHammerHit(vec2 Pos);
	void CreatePlayerSpawn(vec2 Pos);
	void CreateDeath(vec2 Pos, int Who);
	void CreateSound(vec2 Pos, int Sound, int Mask=-1);
	void CreateSoundGlobal(int Sound, int Target=-1);


	enum
	{
		CHAT_ALL=-2,
		CHAT_SPEC=-1,
		CHAT_RED=0,
		CHAT_BLUE=1
	};

	CMute m_Mute;

	int m_BotDifficulty;

	void SendDifficulties(int ClientID);

	// network
	void SendChatTarget(int To, const char *pText);
	void SendChat(int ClientID, int Team, const char *pText);
	void SendEmoticon(int ClientID, int Emoticon);
	void SendWeaponPickup(int ClientID, int Weapon);
	void SendBroadcast(const char *pText, int ClientID);


	//
	void CheckPureTuning();
	void SendTuningParams(int ClientID);
	void SendFreezeTuningParams(int ClientID);

	// Bot slots
	virtual void DeleteBot(int i);
	bool AddBot(int i, bool UseDropPlayer = false);
	virtual bool ReplacePlayerByBot(int ClientID);
	void SendLeaveMessage(int ClientID, const char* pReason);
	void CheckBotNumber();

	//
	void SwapTeams();

	// engine events
	virtual void OnInit();
	virtual void OnConsoleInit();
	virtual void OnShutdown();

	virtual void OnTick();
	virtual void OnPreSnap();
	virtual void OnSnap(int ClientID);
	virtual void OnPostSnap();

	virtual void OnMessage(int MsgID, CUnpacker *pUnpacker, int ClientID);

	virtual void OnClientConnected(int ClientID);
	virtual void OnClientEnter(int ClientID);
	virtual void OnClientDrop(int ClientID, const char *pReason);
	virtual void OnClientDirectInput(int ClientID, void *pInput);
	virtual void OnClientPredictedInput(int ClientID, void *pInput);

	virtual bool IsClientReady(int ClientID);
	virtual bool IsClientPlayer(int ClientID);

	virtual const char *GameType();
	virtual const char *Version();
	virtual const char *NetVersion();

	bool m_SpecMuted;
	bool ShowCommand(int ClientID, CPlayer* pPlayer, const char* pMessage, int *pTeam);
	//Helpers
	bool CanExec(int, const char*);
	int ParsePlayerName(char* pMsg, int *ClientID);
	int StrLeftComp(const char *pOrigin, const char *pSub);
	bool CheckForCapslock(const char *pStr);
};

inline int CmaskAll() { return -1; }
inline int CmaskOne(int ClientID) { return 1<<ClientID; }
inline int CmaskAllExceptOne(int ClientID) { return 0x7fffffff^CmaskOne(ClientID); }
inline bool CmaskIsSet(int Mask, int ClientID) { return (Mask&CmaskOne(ClientID)) != 0; }
#endif
