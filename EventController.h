//
// Created by Cry on 2018-12-20.
//

#ifndef APPREMOTE_EVENTCONTROLLER_H
#define APPREMOTE_EVENTCONTROLLER_H


#include "EventCache.h"
#include "SDL2/SDL_thread.h"
#include "SDL_Screen.h"
#include "SocketConnection.h"
#include "FFmpegDecoder.h"

#define EVENT_UP 0
#define EVENT_DOWN 1
#define EVENT_SCROLL 2
#define EVENT_KEY 3
#define EVENT_RESIZE 4
#define EVENT_CUSTOM 5
#define EVENT_HOLD -1

class EventController {
public:
    EventQueue *queue;
    SDL_Thread *event_tid;
    SDL_Screen *screen;
    SocketConnection *connection;
    SDL_bool stop;

    SDL_mutex *mutex;
    SDL_cond *cond;

    EventController(SDL_Screen *screen, SocketConnection *connection);

    void init();

    void async_start();

    void destroy();

    void event_handle();

    void stop_loop();

    void push_event(SDL_Event event);

    void handleButtonEvent(SDL_Screen *screen, SDL_MouseButtonEvent *event);

    void handleSDLKeyEvent(SDL_Screen *sc, SDL_KeyboardEvent *event);

    void handleScrollEvent(SDL_Screen *sc, SDL_MouseWheelEvent *event);

    void handleMsg(SDL_Screen *sc, SDL_TextInputEvent *event);
    void handleMotionEvent(SDL_Screen *sc, SDL_MouseMotionEvent *event);
    void handleResize(SDL_Screen *sc, SDL_Event event);
    void handleBitmap(SDL_Screen *sc, SDL_Event event);
    void handleBitmap2(SDL_Screen *sc, SDL_Event event);

};


#endif //APPREMOTE_EVENTCONTROLLER_H
