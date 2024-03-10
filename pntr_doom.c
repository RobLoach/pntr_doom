#include <string.h>

#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_DISABLE_MATH
#include "pntr_app.h"

#define DOOM_IMPLEMENT_PRINT
#define DOOM_IMPLEMENT_FILE_IO
#define DOOM_IMPLEMENT_GETTIME
#define DOOM_IMPLEMENTATION 
#include "vendor/PureDOOM/PureDOOM.h"

bool keepRunning;

#ifdef PNTR_APP_SDL
SDL_AudioSpec audio_spec;
#endif

char* pntr_doom_getenv(const char* var) {
    if (strcmp(var, "HOME") == 0) {
        return ".";
    }

    if (strcmp(var, "DOOMWADDIR") == 0) {
        return ".";
    }

    return NULL;
}

void* pntr_doom_malloc(int size) {
    return pntr_load_memory((size_t)size);
}

void pntr_doom_exit(int code) {
    keepRunning = false;
}

void audio_callback(void* userdata, Uint8* stream, int len)
{
    #ifdef PNTR_APP_SDL
    SDL_LockAudio();
    int16_t* buffer = doom_get_sound_buffer();
    SDL_UnlockAudio();

    pntr_memory_copy(stream, buffer, len);
    #endif
}

bool Init(pntr_app* app) {
    keepRunning = true;

    #ifdef PNTR_APP_SDL
    // Capture mouse
    SDL_SetRelativeMouseMode(SDL_TRUE);

    // SDL Audio thread
    memset(&audio_spec, 0, sizeof(audio_spec));
    audio_spec.freq = DOOM_SAMPLERATE;
    audio_spec.format = AUDIO_S16;
    audio_spec.channels = 2;
    audio_spec.samples = 512;
    audio_spec.callback = audio_callback;

    if (SDL_OpenAudio(&audio_spec, NULL) < 0) {
        printf("Failed to SDL_OpenAudio\n");
        return 1;
    }

    SDL_PauseAudio(0);
    #endif

    return true;
}

bool Update(pntr_app* app, pntr_image* screen) {
    #ifdef PNTR_APP_SDL
    SDL_LockAudio();
    doom_update();
    SDL_UnlockAudio();
    #else
    doom_update();
    #endif

    // Render
    const uint8_t* framebuffer = doom_get_framebuffer(4);
    pntr_image* image = pntr_image_from_pixelformat((const void*)framebuffer, SCREENWIDTH, SCREENHEIGHT, PNTR_PIXELFORMAT_RGBA8888);
    pntr_draw_image(screen, image, 0, 0);
    pntr_unload_image(image);

    #ifdef PNTR_APP_SDL
    int x, y;
    SDL_GetRelativeMouseState(&x, &y);
    doom_mouse_move(x * 4, y * 4);
    #endif

    return keepRunning;
}

void Close(pntr_app* app) {
    #ifdef PNTR_APP_SDL
    SDL_SetRelativeMouseMode(SDL_FALSE);
    #endif
}

doom_key_t pntr_doom_key(pntr_app_key key) {
    switch (key) {
        case PNTR_APP_KEY_SPACE: return DOOM_KEY_SPACE;
        case PNTR_APP_KEY_APOSTROPHE: return DOOM_KEY_APOSTROPHE;
        case PNTR_APP_KEY_COMMA: return DOOM_KEY_COMMA;
        case PNTR_APP_KEY_MINUS: return DOOM_KEY_MINUS;
        case PNTR_APP_KEY_PERIOD: return DOOM_KEY_PERIOD;
        case PNTR_APP_KEY_SLASH: return DOOM_KEY_SLASH;
        case PNTR_APP_KEY_0: return DOOM_KEY_0;
        case PNTR_APP_KEY_1: return DOOM_KEY_1;
        case PNTR_APP_KEY_2: return DOOM_KEY_2;
        case PNTR_APP_KEY_3: return DOOM_KEY_3;
        case PNTR_APP_KEY_4: return DOOM_KEY_4;
        case PNTR_APP_KEY_5: return DOOM_KEY_5;
        case PNTR_APP_KEY_6: return DOOM_KEY_6;
        case PNTR_APP_KEY_7: return DOOM_KEY_7;
        case PNTR_APP_KEY_8: return DOOM_KEY_8;
        case PNTR_APP_KEY_9: return DOOM_KEY_9;
        case PNTR_APP_KEY_SEMICOLON: return DOOM_KEY_SEMICOLON;
        case PNTR_APP_KEY_EQUAL: return DOOM_KEY_EQUALS;
        case PNTR_APP_KEY_A: return DOOM_KEY_A;
        case PNTR_APP_KEY_B: return DOOM_KEY_B;
        case PNTR_APP_KEY_C: return DOOM_KEY_C;
        case PNTR_APP_KEY_D: return DOOM_KEY_D;
        case PNTR_APP_KEY_E: return DOOM_KEY_E;
        case PNTR_APP_KEY_F: return DOOM_KEY_F;
        case PNTR_APP_KEY_G: return DOOM_KEY_G;
        case PNTR_APP_KEY_H: return DOOM_KEY_H;
        case PNTR_APP_KEY_I: return DOOM_KEY_I;
        case PNTR_APP_KEY_J: return DOOM_KEY_J;
        case PNTR_APP_KEY_K: return DOOM_KEY_K;
        case PNTR_APP_KEY_L: return DOOM_KEY_L;
        case PNTR_APP_KEY_M: return DOOM_KEY_M;
        case PNTR_APP_KEY_N: return DOOM_KEY_N;
        case PNTR_APP_KEY_O: return DOOM_KEY_O;
        case PNTR_APP_KEY_P: return DOOM_KEY_P;
        case PNTR_APP_KEY_Q: return DOOM_KEY_Q;
        case PNTR_APP_KEY_R: return DOOM_KEY_R;
        case PNTR_APP_KEY_S: return DOOM_KEY_S;
        case PNTR_APP_KEY_T: return DOOM_KEY_T;
        case PNTR_APP_KEY_U: return DOOM_KEY_U;
        case PNTR_APP_KEY_V: return DOOM_KEY_V;
        case PNTR_APP_KEY_W: return DOOM_KEY_W;
        case PNTR_APP_KEY_X: return DOOM_KEY_X;
        case PNTR_APP_KEY_Y: return DOOM_KEY_Y;
        case PNTR_APP_KEY_Z: return DOOM_KEY_Z;
        //case PNTR_APP_KEY_LEFT_BRACKET: return DOOM_KEY_BACKSPACE;
        //case PNTR_APP_KEY_BACKSLASH: return ;
        //case PNTR_APP_KEY_RIGHT_BRACKET: return ;
        case PNTR_APP_KEY_GRAVE_ACCENT: return DOOM_KEY_ESCAPE;
        //case PNTR_APP_KEY_WORLD_1: return ;
        //case PNTR_APP_KEY_WORLD_2: return ;
        case PNTR_APP_KEY_ESCAPE: return DOOM_KEY_ESCAPE;
        case PNTR_APP_KEY_ENTER: return DOOM_KEY_ENTER;
        case PNTR_APP_KEY_TAB: return DOOM_KEY_TAB;
        case PNTR_APP_KEY_BACKSPACE: return DOOM_KEY_BACKSPACE;
        //case PNTR_APP_KEY_INSERT: return ;
        //case PNTR_APP_KEY_DELETE: return ;
        case PNTR_APP_KEY_RIGHT: return DOOM_KEY_RIGHT_ARROW;
        case PNTR_APP_KEY_LEFT: return DOOM_KEY_LEFT_ARROW;
        case PNTR_APP_KEY_DOWN: return DOOM_KEY_DOWN_ARROW;
        case PNTR_APP_KEY_UP: return DOOM_KEY_UP_ARROW;
        //case PNTR_APP_KEY_PAGE_UP: return ;
        //case PNTR_APP_KEY_PAGE_DOWN: return ;
        //case PNTR_APP_KEY_HOME: return ;
        //case PNTR_APP_KEY_END: return ;
        //case PNTR_APP_KEY_CAPS_LOCK: return ;
        //case PNTR_APP_KEY_SCROLL_LOCK: return ;
        //case PNTR_APP_KEY_NUM_LOCK: return ;
        //case PNTR_APP_KEY_PRINT_SCREEN: return ;
        //case PNTR_APP_KEY_PAUSE: return ;
        case PNTR_APP_KEY_F1: return DOOM_KEY_F1;
        case PNTR_APP_KEY_F2: return DOOM_KEY_F2;
        case PNTR_APP_KEY_F3: return DOOM_KEY_F3;
        case PNTR_APP_KEY_F4: return DOOM_KEY_F4;
        case PNTR_APP_KEY_F5: return DOOM_KEY_F5;
        case PNTR_APP_KEY_F6: return DOOM_KEY_F6;
        case PNTR_APP_KEY_F7: return DOOM_KEY_F7;
        case PNTR_APP_KEY_F8: return DOOM_KEY_F8;
        case PNTR_APP_KEY_F9: return DOOM_KEY_F9;
        case PNTR_APP_KEY_F10: return DOOM_KEY_F10;
        case PNTR_APP_KEY_F11: return DOOM_KEY_F11;
        case PNTR_APP_KEY_F12: return DOOM_KEY_F12;
        // case PNTR_APP_KEY_F13: return ;
        // case PNTR_APP_KEY_F14: return ;
        // case PNTR_APP_KEY_F15: return ;
        // case PNTR_APP_KEY_F16: return ;
        // case PNTR_APP_KEY_F17: return ;
        // case PNTR_APP_KEY_F18: return ;
        // case PNTR_APP_KEY_F19: return ;
        // case PNTR_APP_KEY_F20: return ;
        // case PNTR_APP_KEY_F21: return ;
        // case PNTR_APP_KEY_F22: return ;
        // case PNTR_APP_KEY_F23: return ;
        // case PNTR_APP_KEY_F24: return ;
        // case PNTR_APP_KEY_F25: return ;
        case PNTR_APP_KEY_KP_0: return DOOM_KEY_0;
        case PNTR_APP_KEY_KP_1: return DOOM_KEY_1;
        case PNTR_APP_KEY_KP_2: return DOOM_KEY_2;
        case PNTR_APP_KEY_KP_3: return DOOM_KEY_3;
        case PNTR_APP_KEY_KP_4: return DOOM_KEY_4;
        case PNTR_APP_KEY_KP_5: return DOOM_KEY_5;
        case PNTR_APP_KEY_KP_6: return DOOM_KEY_6;
        case PNTR_APP_KEY_KP_7: return DOOM_KEY_7;
        case PNTR_APP_KEY_KP_8: return DOOM_KEY_8;
        case PNTR_APP_KEY_KP_9: return DOOM_KEY_9;
        // case PNTR_APP_KEY_KP_DECIMAL: return ;
        // case PNTR_APP_KEY_KP_DIVIDE: return ;
        // case PNTR_APP_KEY_KP_MULTIPLY: return ;
        // case PNTR_APP_KEY_KP_SUBTRACT: return ;
        // case PNTR_APP_KEY_KP_ADD: return ;
        // case PNTR_APP_KEY_KP_ENTER: return ;
        // case PNTR_APP_KEY_KP_EQUAL: return ;
        case PNTR_APP_KEY_LEFT_SHIFT: return DOOM_KEY_SHIFT;
        case PNTR_APP_KEY_LEFT_CONTROL: return DOOM_KEY_CTRL;
        case PNTR_APP_KEY_LEFT_ALT: return DOOM_KEY_ALT;
        // case PNTR_APP_KEY_LEFT_SUPER: return ;
        case PNTR_APP_KEY_RIGHT_SHIFT: return DOOM_KEY_SHIFT;
        case PNTR_APP_KEY_RIGHT_CONTROL: return DOOM_KEY_CTRL;
        case PNTR_APP_KEY_RIGHT_ALT: return DOOM_KEY_ALT;
        // case PNTR_APP_KEY_RIGHT_SUPER: return ;
        // case PNTR_APP_KEY_MENU: return ;
    }

    return DOOM_KEY_UNKNOWN;
}

doom_button_t pntr_doom_mouse_button(pntr_app_mouse_button button) {
    switch (button) {
        case PNTR_APP_MOUSE_BUTTON_LEFT: return DOOM_LEFT_BUTTON;
        case PNTR_APP_MOUSE_BUTTON_RIGHT: return DOOM_RIGHT_BUTTON;
        case PNTR_APP_MOUSE_BUTTON_MIDDLE: return DOOM_MIDDLE_BUTTON;
    }

    return -1;
}

void Event(pntr_app* app, pntr_app_event* event) {
    doom_key_t doomKey = pntr_doom_key(event->key);
    doom_button_t mouseButton = pntr_doom_mouse_button(event->mouseButton);
    switch (event->type) {
        case PNTR_APP_EVENTTYPE_KEY_DOWN:
            if (doomKey != DOOM_KEY_UNKNOWN) {
                doom_key_down(doomKey);
            }
        break;
        case PNTR_APP_EVENTTYPE_KEY_UP:
            if (doomKey != DOOM_KEY_UNKNOWN) {
                doom_key_up(doomKey);
            }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN: {
            if (mouseButton >= 0) {
                doom_button_down(mouseButton);
            }
        }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP: {
            if (mouseButton >= 0) {
                doom_button_up(mouseButton);
            }
        }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_MOVE: {
            //doom_mouse_move(-event->mouseDeltaX * 100, -event->mouseDeltaY*100);
        }
        break;
    }
}

pntr_app Main(int argc, char* argv[]) {

    // Change default bindings to modern
    doom_set_default_int("key_up", DOOM_KEY_W);
    doom_set_default_int("key_down", DOOM_KEY_S);
    doom_set_default_int("key_strafeleft", DOOM_KEY_A);
    doom_set_default_int("key_straferight", DOOM_KEY_D);
    doom_set_default_int("key_use", DOOM_KEY_E);
    doom_set_default_int("mouse_move", 0); // Mouse will not move forward

    doom_set_malloc(pntr_doom_malloc, pntr_unload_memory);
    doom_set_exit(pntr_doom_exit);
    doom_set_getenv(pntr_doom_getenv);
    doom_init(argc, argv, DOOM_FLAG_MENU_DARKEN_BG);

    return (pntr_app) {
        .width = SCREENWIDTH,
        .height = SCREENHEIGHT,
        .title = "pntr_doom",
        .init = Init,
        .update = Update,
        .close = Close,
        .event = Event,
        .fps = 60,
        //.userData = pntr_load_memory(sizeof(AppData)),
    };
}