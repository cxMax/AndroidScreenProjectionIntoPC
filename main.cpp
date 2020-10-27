#include <iostream>
#include <SDL2/SDL_stdinc.h>
#include "SocketConnection.h"
#include "SDL_Screen.h"
#include "FrameCache.h"
#include "FFmpegDecoder.h"
#include "EventCache.h"
#include "EventController.h"
#include "log.h"
#include "Bitmap.h"

#define DEVICE_NAME_FIELD_LENGTH 64

bool
device_read_info(int device_socket, char *device_name, struct Size *size) {
    unsigned char buf[DEVICE_NAME_FIELD_LENGTH + 4];
    int r = recv(device_socket, buf, sizeof(buf), 0);
    if (r < DEVICE_NAME_FIELD_LENGTH + 4) {
        LOGE("Could not retrieve device information %d", r);
        return false;
    }
    buf[DEVICE_NAME_FIELD_LENGTH - 1] = '\0';
    strcpy(device_name, (char *) buf);
    size->width = (buf[DEVICE_NAME_FIELD_LENGTH] << 8)
                  | buf[DEVICE_NAME_FIELD_LENGTH + 1];
    size->height = (buf[DEVICE_NAME_FIELD_LENGTH + 2] << 8)
                   | buf[DEVICE_NAME_FIELD_LENGTH + 3];
    return true;
}

int main() {

    char *test = new char[4];
    test[0] = 2;
    test[1] = 1;
    test[2] = 1;
    test[3] = -1;

    printf("连接成功 %d\n", (test[3]<< 7));
    printf("连接成功 %d\n", ((test[3] & 0xff) >> 4));
    if (1) {
        // return 0;
    }
    printf("连接成功\n");

    unsigned char buf[1];
    // int r = recv(videoConn->client_conn, buf, sizeof(buf), 0);
    // printf("第一个socket=%d，字节数=%d(必读)\n\n", videoConn->client_conn, r);

    // 连接控制 socket
    SocketConnection *controlConn = new SocketConnection();
    if (controlConn->connect_server(9000) == SDL_FALSE) {
        return -1;
    }
    // 等待 2s
    SDL_Delay(2000);

    // 连接图像 socket
    SocketConnection *imageConn = new SocketConnection();
    if (imageConn->connect_server(9002) == SDL_FALSE) {
        return -1;
    }
    printf("连接 Image 成功\n");
    char buf2[3];
    memset(buf2, 0, sizeof(buf2));
    buf2[0] = 20;
    buf2[1] = 1;
    buf2[2] = 0;
    printf("发送启动图像命令 %d\n", buf2[0]);
    controlConn->send_to_(reinterpret_cast<uint8_t *>(buf2), 3);

    // 连接视频 socket
    SocketConnection *videoConn = new SocketConnection();
    if (videoConn->connect_server(9001) == SDL_FALSE) {
        return -1;
    }
    printf("连接 Video 成功\n");

    Size* devWH = new Size();
    char device_name[DEVICE_NAME_FIELD_LENGTH];
    printf("第二个 socket=%d\n", controlConn->client_conn);
    // printf("第三个 socket=%d\n", imageConn->client_conn);
    // device_read_info(videoConn->client_conn, device_name, devWH);
    // printf("dev name=%s width=%d height=%d\n\n", device_name, devWH->width, devWH->height);

    // uint8_t size[4];
    // videoConn->recv_from_(reinterpret_cast<uint8_t *>(size), 4);

    //这里先写死，后面从客户端内接受
    // int width = (size[0] << 8) | (size[1]);
    // int height = (size[2] << 8) | (size[3]);

    int width = devWH->width;
    int height = devWH->height;

    printf("width = %d , height = %d \n", width, height);


    int scale =2;
    char name[] = "as_remote";
    // auto *screen = new SDL_Screen(name, static_cast<int>(width / scale), static_cast<int>(height / scale));
    auto *screen = new SDL_Screen(name, static_cast<int>(width), static_cast<int>(height));

    screen->init();
    //开启编码器
    FrameCache *cache = new FrameCache();
    cache->init();

    FFmpegDecoder *decoder = new FFmpegDecoder(videoConn, cache, screen);
//    decoder->init();
    decoder->async_start();

    EventController *controller = new EventController(screen, controlConn);
    controller->init();
    controller->async_start();

    //开启事件循环
    printf("开启事件循环\n");
    Bitmap *bitmap = new Bitmap(controlConn);
    bitmap->conn = imageConn;
    bitmap->async_start();

    SDL_Event event;
    //开启Event Loop
    for (;;) {
        SDL_WaitEvent(&event);
//        printf("接到事件\n");

        if (event.type == EVENT_NEW_FRAME) { //渲染
            AVFrame *render = cache->render_frame;
            screen->uploadTexture(
                    render->data[0], render->linesize[0],
                    render->data[1], render->linesize[1],
                    render->data[2], render->linesize[2]
            );
            cache->consume_render = SDL_TRUE;
        } else if (event.type == SDL_QUIT) {
            printf("rev event type=SDL_QUIT\n");
            break;
        } else {
            controller->push_event(event);
        }
    }

    controller->destroy();
    decoder->stop();
    bitmap->stop_loop();
    decoder->destroy();
    screen->destroy();
    delete screen;
    delete controller;
    delete cache;
    delete decoder;
    close_conn:
    videoConn->close_client();
    controlConn->close_client();
    delete videoConn;
    delete controlConn;
    delete bitmap;
    return 0;
}

