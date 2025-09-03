#ifndef __KPHANDSET_H__
#define __KPHANDSET_H__

#include <AEEAppGen.h>
#include <AEEShell.h>
#include <AEETAPI.h>
#include <AEETelephone.h>
#include <AEEFile.h>
#include <AEEBacklight.h>
#include <AEEGraphics.h>
#include <AEENetwork.h>
#include <AEEBattery.h>
#include <AEEStdLib.h>
#include <AEEMenu.h>
#include <AEEFontsStandard.BiD>

//BTFE
#include <AEETypeface.h>
#include <bid/AEECLSID_TYPEFACE.bid>
#include <bid/AEECLSID_BTFEFONTBIDIUTIL.bid>
//

#include "kpnetwork.h"
#include "kpscreen.h"
#include "kpaudio.h"
#include "kphandset.bid"

class kphelpers;
class kpnetwork;
class kpcutscene;
class kpstill;

#define IMAGE_CACHE_SIZE 9

#define EVT_KPHANDSET_APP_AUDIO_INIT				0x7002	 // The audio file has been initialized

//Network Events
#define EVT_KPHANDSET_APP_NETWORK_CONNECTION_ERROR	0x700A   // A network connection error has occured
#define EVT_KPHANDSET_APP_NETWORK_CONNECTION_RETRY	0x700B   // A network retry has been called
#define EVT_KPHANDSET_APP_NETWORK_WRITE_ERROR		0x700C   // A network write error has occured
#define EVT_KPHANDSET_APP_NETWORK_READ_ERROR		0x700D   // A network read error has occured
#define EVT_KPHANDSET_APP_NETWORK_INCOMING_MESSAGE	0x700E   // Prepares an Incoming Network Message

//Script Events
#define EVT_KPHANDSET_APP_LOAD_SCRIPT				0x7014   // Loads up a script

//Http Events
#define EVT_KPHANDSET_APP_HTTP_TIMEOUT				0x701F	 // HTTP has timed out

//Misc Events
#define EVT_KPHANDSET_APP_RESTART					0x7029   // Restart the App
#define EVT_KPHANDSET_APP_UPDATE_ERROR				0x702A	 // Error has occured while updating
#define EVT_KPHANDSET_APP_SOCKET_PING				0x702B	 // Notifies when the socket is pinged
#define EVT_KPHANDSET_APP_TIMEOUT					0x702C   // Timeout the App

struct kpscript
{
	uint8 conditional;
	uint8 kpscript_unk2[3];
	uint8 kpscript_unk3;
	uint8 kpscript_unk4;
	uint8 kpscript_unk5;
	uint8 kpscript_unk6;
	void* kpscript_unk7;
	void* kpscript_unk8;
	void* kpscript_unk9;
	void* kpscript_unk10;
	void* kpscript_unk11;
	void* kpscript_unk12;
	char pLabel[4096];
	char* tokenizer;
	char* returnLocation;
	char* replayBuffer;
	char* constants;
	unsigned int constantsLength;
	uint8 kpscript_unk20;
	uint8 kpscript_unk21[411];
};

struct kpfilmstrip {
public:
	uint8* frames;
	uint8 skipCutscene;
	uint8 cutscenePlaying;
	uint8 audioPlaying;
	uint16 frameCount;
	uint8 index;
	uint8 preloadedFilmstripIndex;
	uint8 subtitleCount;
	uint8 subtitleIndex;
	uint8 unk456456_3;						//
	uint16 filmstripIndex;
	char* subtitleBuf;
	uint16 kpfilmstrip_unk7_1;				//
	uint16 kpfilmstrip_unk7_2;				//
	void* padding;							//Padding
	uint32 UpTimeMS;
	IImage* Image;
};

struct kptranslation
{
	char* buffer;
	unsigned int length;
};

struct kpBottom
{
	IImage* interface;
	uint8 bottomBarHeight;
	uint8 SubtitleHeight[3];
	uint8 SubtitleWidth[3];
	AECHAR kpBottom_unk9[512];
	AECHAR kpBottom_unk10[34];
	uint8 kpBottom_unk11_1;
	uint8 subtitleSplitIndex;
	uint16 textFont;
};

class kphandset : public AEEApplet {
public:
	IFileMgr* pFileMgr;
	IBacklight* pBacklight;
	IGraphics* pGraphics;
	uint8 unk_padding[28];							//Padding
	ITypeface* pTypeface;
	IHFont* pIFont_User1;
	IHFont* pIFont_Large;
	IHFont* pIFont_User2;
	AEEBitmapInfo pBitmapInfo;
	char handsetID[8];
	char contentVersion[8];
	byte lowBattery;
	byte flippedOpen;
	byte unk21_3;									//Unknown
	byte adminMode;
	AEECallback pSystemCallback;
	kpaudio pAudio;
	kpnetwork network;
	kptranslation pTranslatorMgr;
	kpscript script;
	kpscreen* pSelectedStartup;
	struct NetworkMessage* pPop;
	IImage* ui_waiting_Interface;
	IImage* ui_full_Interface;
	IImage* ui_bottom_Interface;
	IImage* ui_bottom_clear_Interface;
	IImage* ui_help_Interface;
	IImage* ui_ok_Interface;
	IImage* ui_replay_Interface;
	IImage* ui_retrigger_Interface;
	kpfilmstrip filmstripBuffer[IMAGE_CACHE_SIZE];
	char lang[2];
	char episode[2];
	char kphandset_unk98_1[32];

	char scriptBuf[192];
	void* kphandset_unk100;

	char kphandset_unk148[8];
	char kphandset_unk150[9];
	char scratch[400];
	char kphandset_unk154[400];
	uint8 kphandset_unk156[1106];
	kpBottom global_bottom;
	uint8 kphandset_isStartup1;
	uint8 unk_padding_3[3];							//Padding
	uint8 kpstartup1[4564];
	uint8 kphandset_isStartup2;
	uint8 unk_padding_4[3];							//Padding
	uint8 kpstartup2[4564];
	int global_timeout_remaining;
	int globalTimeoutState;
	int global_one;
	int global_two;
	int global_alert_count;
	uint32 timeSeconds;

	//Interface
	static boolean Init(kphandset* pApp);
	static void FreeAppData(AEEApplet* pMe);

	//Unknown where these functions go
	static int DisplayMessageBox(kphandset* pApp, const char* messageText);
	static bool SDCheck(kphandset* pApp);
	static void StartingApp(kphandset* pApp);
	static void Sys_Init(kphandset* pApp);
	static int CheckLowBattery(kphandset* pApp);
	static char* InitScriptMgr(kphandset* pApp);
	static int RefreshBacklight(kphandset* pApp); //28178
	static bool kp_CheckToken(int a1);
	static void InitFonts(kphandset* a1);
	static void kpsys_PreloadUIImages(kphandset* pApp);
	static void PrintRamUsage(kphandset* a1);
	static void* FetchScreen(kphandset* a1);
	static void kpscr_func_1DDAC(kpscreen* a1);
	static void kp_func_2A334(kpscreen* a1);
	static void kpscript_Free(kphandset* pApp);
	//

	//Sys
	static void kpsys_SetLanguage(kphandset* pApp, const char* language);
	static void kpsys_SetPavilion(kphandset* pApp, const char* pavilion);
	static void kpsys_LoadScript(kphandset* pApp, char* script);
	static void kpsys_ClearScript(kphandset* pApp);
	static void kpsys_ReadScript(kphandset* pApp, const char* script);
	static void kpscr_ParseScript(kphandset* pApp);
	static bool kpscr_Command_Goto(kphandset* pApp, const char* script);
	static const char* kpscr_GetCommand(char* tokenizer);
	static bool kpscr_func_310B8(char* a1);
	static void kpsys_PickRandomSong(kphandset* pApp);
	static void kpscr_func_2AB8C(kphandset* pApp);
	static void kpscr_func_23C18(kphandset* pApp);
	//

	//Commands
	static void kpscr_RenderSubtitles(kpBottom* a1);
	static void kpscr_InitBottomBar(kpBottom* a1, const char* a2, const char* a3);
	static void kpscr_subtitles_func_305F4(kpBottom* a1, const char* a2);
	static bool kpscr_Tokenizer(int a1);
	static void kpscr_Command_ZodiacTrigger(kphandset* pApp);
	static void kpscr_Command_PrepDate(kphandset* pApp);
	static void kpscr_Command_Ignore(kphandset* pApp, const char* commandBuffer);
	static void kpscr_Command_Preload(kphandset* pApp, char* pFilmstrip);
	static void kpscr_Command_Vibrate(kphandset* a1, char* a2);
	static void kpscr_Command_Message(kphandset* a1, char* a2);
	static void kpscr_Command_Mark(kphandset* pApp);
	static void kpscr_Command_Reboot(kphandset* pApp);
	static void kpscr_Command_Return(kphandset* pApp);
	static void kpscr_Command_SetReset(kphandset* pApp, char* a2, char isSet);
	//

	//Translation Mgr
	static void kp_InitTranslatorMgr_func_27AD8(kphandset* pApp);
	static void LoadStringTranslation(kphandset* pApp, const char* path);
	static void kptranslator_Free(kphandset* pApp);
	//

	static char* kphandset_ReadFromScratch(const char* haystack, const char* needle);
};

#endif
