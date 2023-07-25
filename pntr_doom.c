#define PNTR_APP_IMPLEMENTATION
#define PNTR_ENABLE_DEFAULT_FONT
#define PNTR_DISABLE_MATH
#include "pntr_app.h"

#define DOOM_IMPLEMENT_PRINT
#define DOOM_IMPLEMENT_MALLOC
#define DOOM_IMPLEMENT_FILE_IO

#define DOOM_IMPLEMENTATION 
#include "PureDOOM.h"


bool shouldClose;

void* pntr_doom_malloc(int size) {
    return pntr_load_memory((size_t)size);
}

void pntr_doom_exit(int code) {
    shouldClose = true;
}

bool Init(void* userData) {
    shouldClose = false;


    return true;
}

bool Update(pntr_image* screen, void* userData) {
    doom_update();

    // Render
    const uint8_t* framebuffer = doom_get_framebuffer(4);
    pntr_image* pntrFramebuffer = pntr_image_from_pixelformat((const void*)framebuffer, screen->width, screen->height, PNTR_PIXELFORMAT_RGBA8888);

    pntr_draw_image(screen, pntrFramebuffer, 0, 0);

    pntr_unload_image(pntrFramebuffer);

    return shouldClose;
}

void Close(void* userData) {

}

void Event(pntr_app_event* event, void* userData) {

    switch (event->type) {
        case PNTR_APP_EVENTTYPE_KEY_DOWN:
            if (event->key == PNTR_APP_KEY_SPACE) {
            }
        break;
        case PNTR_APP_EVENTTYPE_KEY_UP:
            if (event->key == PNTR_APP_KEY_SPACE) {
            }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_DOWN: {
        }
        break;
        case PNTR_APP_EVENTTYPE_MOUSE_BUTTON_UP: {
        }
        break;
        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_DOWN:
        {
           break;
        }
        case PNTR_APP_EVENTTYPE_GAMEPAD_BUTTON_UP:
        {
            break;
        }
        break;
    }
}

pntr_app Main(int argc, char* argv[]) {

    // Doom
    doom_set_malloc(pntr_doom_malloc, pntr_unload_memory);
    doom_set_exit(pntr_doom_exit);
    doom_init(argc, argv, DOOM_FLAG_MENU_DARKEN_BG);
    return (pntr_app) {
        .width = 320,
        .height = 200,
        .title = "pntr_doom",
        .init = Init,
        .update = Update,
        .close = Close,
        .event = Event,
        .fps = 60,
        //.userData = pntr_load_memory(sizeof(AppData)),
    };
}