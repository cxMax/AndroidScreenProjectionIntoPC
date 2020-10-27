//
// Created by TanLin on 2020/9/13.
//

#ifndef APPREMOTE_BITMAP_H
#define APPREMOTE_BITMAP_H


#include "SocketConnection.h"

class Bitmap {
public:
    Bitmap(SocketConnection *connection);
    SocketConnection *conn;
    SDL_Thread *event_tid;
    SDL_bool stop;

    void init();
    void async_start();
    void event_handle();
    void event_handlechar();
    void stop_loop();
};


#endif //APPREMOTE_BITMAP_H
