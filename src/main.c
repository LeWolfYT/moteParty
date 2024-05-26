#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <grrlib.h>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <asndlib.h>
#include "oggplayer.h"

#include "CurP1_png.h"
#include "CurP2_png.h"
#include "CurP3_png.h"
#include "CurP4_png.h"
#include "bg143_png.h"
#include "bg1169_png.h"
#include "logo1_png.h"
#include "logo2_png.h"
#include "exluna_ogg.h"
#include "mote_party_main_ogg.h"
#include "mote_party_intro_ogg.h"
#include "drum1_raw.h"
#include "drum2_raw.h"

ir_t ir;
ir_t ir2;
ir_t ir3;
ir_t ir4;

u32 type;

orient_t orienta;
bool introe = true;

s8 HWButton = -1;

void WiiResetPressed()
{
	HWButton = SYS_RETURNTOMENU;
}

void WiiPowerPressed()
{
	HWButton = SYS_POWEROFF_STANDBY;
}

void WiimotePowerPressed(s32 chan)
{
	HWButton = SYS_POWEROFF_STANDBY;
}

void playsfx(int freq, void *pcm, s32 pcmsize, int soundvol) {
	ASND_SetVoice(SND_GetFirstUnusedVoice(), 3, freq, 0, pcm, pcmsize, soundvol, soundvol, NULL);
}

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    GRRLIB_texImg *cursor;
    GRRLIB_texImg *cursor2;
    GRRLIB_texImg *cursor3;
    GRRLIB_texImg *cursor4;
    GRRLIB_texImg *bg143;
    GRRLIB_texImg *bg1169;
    GRRLIB_texImg *logo1;
    GRRLIB_texImg *logo2;
    cursor = GRRLIB_LoadTexture(CurP1_png);
    cursor2 = GRRLIB_LoadTexture(CurP2_png);
    cursor3 = GRRLIB_LoadTexture(CurP3_png);
    cursor4 = GRRLIB_LoadTexture(CurP4_png);
    bg143 = GRRLIB_LoadTexture(bg143_png);
    bg1169 = GRRLIB_LoadTexture(bg1169_png);
    logo1 = GRRLIB_LoadTexture(logo1_png);
    logo2 = GRRLIB_LoadTexture(logo2_png);

    // Initialise the Wiimotes
    WPAD_Init();

    ASND_Init();

    SYS_SetResetCallback(WiiResetPressed);
	SYS_SetPowerCallback(WiiPowerPressed);

	// Init IR
	WPAD_SetVRes(0, 640, 480);
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetDataFormat(WPAD_CHAN_1, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetDataFormat(WPAD_CHAN_2, WPAD_FMT_BTNS_ACC_IR);
    WPAD_SetDataFormat(WPAD_CHAN_3, WPAD_FMT_BTNS_ACC_IR);

	WPAD_SetPowerButtonCallback(WiimotePowerPressed);

    GRRLIB_DrawImg(30, 30, cursor, 0, 1, 1, RGBA( 255, 255, 255, 255 ));
    GRRLIB_DrawImg(50, 50, cursor2, 0, 1, 1, RGBA( 255, 255, 255, 255 ));
    GRRLIB_DrawImg(70, 70, cursor3, 0, 1, 1, RGBA( 255, 255, 255, 255 ));
    GRRLIB_DrawImg(90, 90, cursor4, 0, 1, 1, RGBA( 255, 255, 255, 255 ));

    PlayOgg(mote_party_intro_ogg, mote_party_intro_ogg_size, 0, OGG_ONE_TIME);
    //ASND_SetInfiniteVoice(0, VOICE_STEREO_16BIT, 0, 0, exluna_raw, exluna_raw_size, 127, 127);

    while(1) {
        WPAD_ScanPads();  // Scan the Wiimotes

        GRRLIB_FillScreen(0x000000FF);

        int prob1 = WPAD_Probe(0, &type);
        int prob2 = WPAD_Probe(1, &type);
        int prob3 = WPAD_Probe(2, &type);
        int prob4 = WPAD_Probe(3, &type);

        if ((StatusOgg() != OGG_STATUS_RUNNING) && introe) {
            PlayOgg(mote_party_main_ogg, mote_party_main_ogg_size, 0, OGG_INFINITE_TIME);
        }

        if (!(prob1==WPAD_ERR_NO_CONTROLLER || prob1==WPAD_ERR_NOT_READY)) {
            WPAD_IR(0, &ir);
            u16 buttonsDown1 = WPAD_ButtonsDown(0);
            if (buttonsDown1 & WPAD_BUTTON_A) {
                //PlayOgg(drum1_ogg, drum1_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum1_raw, drum1_raw_size, 127);
            }
            if (buttonsDown1 & WPAD_BUTTON_B) {
                //PlayOgg(drum2_ogg, drum2_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum2_raw, drum2_raw_size, 127);
            }
        }
        if (!(prob2==WPAD_ERR_NO_CONTROLLER || prob2==WPAD_ERR_NOT_READY)) {
            WPAD_IR(1, &ir2);
            u16 buttonsDown2 = WPAD_ButtonsDown(1);
            if (buttonsDown2 & WPAD_BUTTON_A) {
                //PlayOgg(drum1_ogg, drum1_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum1_raw, drum1_raw_size, 127);
            }
            if (buttonsDown2 & WPAD_BUTTON_B) {
                //PlayOgg(drum2_ogg, drum2_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum2_raw, drum2_raw_size, 127);
            }
        }
        if (!(prob3==WPAD_ERR_NO_CONTROLLER || prob3==WPAD_ERR_NOT_READY)) {
            WPAD_IR(2, &ir3);
            u16 buttonsDown3 = WPAD_ButtonsDown(2);
            if (buttonsDown3 & WPAD_BUTTON_A) {
                //PlayOgg(drum1_ogg, drum1_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum1_raw, drum1_raw_size, 127);
            }
            if (buttonsDown3 & WPAD_BUTTON_B) {
                //PlayOgg(drum2_ogg, drum2_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum2_raw, drum2_raw_size, 127);
            }
        }
        if (!(prob4==WPAD_ERR_NO_CONTROLLER || prob4==WPAD_ERR_NOT_READY)) {
            WPAD_IR(3, &ir4);
            u16 buttonsDown4 = WPAD_ButtonsDown(3);
            if (buttonsDown4 & WPAD_BUTTON_A) {
                //PlayOgg(drum1_ogg, drum1_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum1_raw, drum1_raw_size, 127);
            }
            if (buttonsDown4 & WPAD_BUTTON_B) {
                //PlayOgg(drum2_ogg, drum2_ogg_size, 0, OGG_ONE_TIME);
                playsfx(44100, (char *) drum2_raw, drum2_raw_size, 127);
            }
        }


        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME)  break;
        
        if (CONF_GetAspectRatio() == CONF_ASPECT_16_9) {
            GRRLIB_DrawImg(0, 0, bg1169, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));

GRRLIB_DrawImg(20*0.75, 20, logo1, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));
GRRLIB_DrawImg(20*0.75, 70, logo2, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));

            if (!(prob1==WPAD_ERR_NO_CONTROLLER || prob1==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir.x-6, ir.y-1, cursor, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob2==WPAD_ERR_NO_CONTROLLER || prob2==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir2.x-6, ir2.y-1, cursor2, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob3==WPAD_ERR_NO_CONTROLLER || prob3==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir3.x-6, ir3.y-1, cursor3, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob4==WPAD_ERR_NO_CONTROLLER || prob4==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir4.x-6, ir4.y-1, cursor4, 0, 0.75, 1, RGBA( 255, 255, 255, 255 ));}
        } else {
            GRRLIB_DrawImg(0, 0, bg143, 0, 1, 1, RGBA( 255, 255, 255, 255 ));

GRRLIB_DrawImg(20, 20, logo1, 0, 1, 1, RGBA( 255, 255, 255, 255 ));
GRRLIB_DrawImg(20, 70, logo2, 0, 1, 1, RGBA( 255, 255, 255, 255 ));

            if (!(prob1==WPAD_ERR_NO_CONTROLLER || prob1==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir.x-6, ir.y-1, cursor, 0, 1, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob2==WPAD_ERR_NO_CONTROLLER || prob2==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir.x-6, ir.y-1, cursor2, 0, 1, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob3==WPAD_ERR_NO_CONTROLLER || prob3==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir.x-6, ir.y-1, cursor3, 0, 1, 1, RGBA( 255, 255, 255, 255 ));}
            if (!(prob4==WPAD_ERR_NO_CONTROLLER || prob4==WPAD_ERR_NOT_READY)) {GRRLIB_DrawImg(ir.x-6, ir.y-1, cursor4, 0, 1, 1, RGBA( 255, 255, 255, 255 ));}
        }
        //GRRLIB_Rectangle(ir.x-5, ir.y-5, 10, 10, 0xFFFFFFFF, false);

        GRRLIB_Render();  // Render the frame buffer to the TV
        if(HWButton != -1)
	{
		SYS_ResetSystem(HWButton, 0, 0);
	}
    }

    

    GRRLIB_FreeTexture(cursor);
    GRRLIB_FreeTexture(cursor2);
    GRRLIB_FreeTexture(cursor3);
    GRRLIB_FreeTexture(cursor4);
    GRRLIB_FreeTexture(bg143);
    GRRLIB_FreeTexture(bg1169);
    GRRLIB_FreeTexture(logo1);
    GRRLIB_FreeTexture(logo2);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

    

    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}