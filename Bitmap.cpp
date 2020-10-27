//
// Created by TanLin on 2020/9/13.
//

#include <SDL2/SDL_quit.h>
#include <SDL2/SDL_thread.h>
#include "Bitmap.h"
#include "FFmpegDecoder.h"
#include <iostream>
#include <fstream>


Bitmap::Bitmap(SocketConnection *connection) : conn(connection) { }

void Bitmap::init() {
    printf("bitmap init");
}

int bitmap_run(void *data) {
    Bitmap *controller = static_cast<Bitmap *>(data);
    controller->stop = SDL_FALSE;
    // controller->event_handle();
    controller->event_handlechar();
    return 0;
}

void Bitmap::async_start() {
    event_tid = SDL_CreateThread(bitmap_run, "bitmap_controller", this);
}

void Bitmap::event_handle() {
    printf("bitmap event_handle\n");
    int size = BUF_SIZE;
    uint8_t *buf = new uint8_t[BUF_SIZE];
    int flag = 0;
    for (;;) {
        int count = conn->recv_from_(reinterpret_cast<uint8_t *>(buf), size);
        // conn->recv_from_()
        printf("bitmap.cpp read count = %d\n%s", count, buf);
        if (count <= 0) {
            break;
        }
        int len = buf[0];
        printf("length = %d\n", len);
        std::ofstream outfile("a.jpg", std::ios::binary);

    }
}

void appendFile(const char* f, char* t, int offset, int count) {
    for (unsigned long i = 0; i < count; i++) {
        t[offset + i] = f[i];
    }
}

void appendFile2(char* f, const char* t, int offset) {
    for (int i = offset; i < sizeof(f); i++) {
        f[i] = t[offset];
    }
}

void Bitmap::event_handlechar() {
    printf("bitmap event_handle\n");
    // 这个数值有点儿讲究，太大不行（不是不行，是需要调整分割图像的逻辑）
    int size = 1 << 15;
    char *buf = new char[1 << 15];
    int flag = 0;
    char *name = new char[50];
    char *fileBuff = new char[1 << 24];
    sprintf(name, "video%d.jpg", flag);
    std::ofstream outFile;
    int read = 0;
    unsigned int len = 0;
    int slice = 0;
    for (;;) {
        int count = conn->recv_from_(buf, size);
        // conn->recv_from_()
        printf("read count = %d\n", count);
        if (count <= 0) {
            break;
        }
        if (read == 0) {
            slice++;
            sprintf(name, "jpgs/video_%d.jpg", slice);
            // len = buf[0];
            len = (buf[3] & 0xFF) << 24 | ((buf[2] & 0xFF) << 16) | ((buf[1] & 0xFF) << 8) | (buf[0] & 0xFF);
            // printf("byte value = %d+%d+%d+%d len=%d, flag=%d\n", buf[0], buf[1], buf[2], buf[3], len, buf[4]);
            printf("byte len=%d, 这是第%d帧图像\n", len, slice);
            outFile.open(name, std::ios::out);
            char* tmp = new char[len];
            // appendFile2(buf, tmp, 0);
            for (int j = 5; j < count; j++) {
                tmp[j - 5] = buf[j];
            }
            appendFile(tmp, fileBuff, read, len);
            read = count - 5;
            if (read == len) {
                outFile.write(fileBuff, read);
                outFile.close();
                read = 0;
                len = 0;
            }
        } else if (read == len) {
            outFile.write(fileBuff, read);
            outFile.close();
            read = 0;
            len = 0;
        } else {
            appendFile(buf, fileBuff, read, count);
            // outFile.write(buf, count);
            read += count;
            if (read == len) {
                outFile.write(fileBuff, read);
                outFile.close();
                read = 0;
                len = 0;
            }
        }
    }
}

void Bitmap::stop_loop() {
    stop = SDL_TRUE;
    SDL_DetachThread(event_tid);
}