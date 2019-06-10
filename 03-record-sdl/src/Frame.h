//
// Created by camix on 04/06/19.
//

#ifndef PORTAL_FRAME_H
#define PORTAL_FRAME_H

#include <string>
extern "C" {
#include <libavutil/frame.h>
#include <libavcodec/avcodec.h>
}

#define INIT_FRAME_EXC "There was an error while allocating memory for a Frame\n"
#define SEND_FRAME_EXC "There was an error while sending the frame\n"

class FrameException : public std::exception {
protected:
    std::string message;
public:
    explicit FrameException() = default;
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
};

class FrameInitException : public FrameException {
public:
    explicit FrameInitException() {
        message = INIT_FRAME_EXC;
    }
};

class FrameSendException : public FrameException {
    virtual const char *what() const throw() {
        return this->message.c_str();
    }
public:
    explicit FrameSendException() {
        message = SEND_FRAME_EXC;
    }
};

class SwsContext;

class Frame {
private:
    AVFrame* frame;
    int currentPts;

public:
    Frame(int format, int width, int height);
    ~Frame();

    void write(const char *data, SwsContext *ctx);
    void sendTo(AVCodecContext* codecContext);


    AVFrame* get() {return this->frame;}
};



#endif //PORTAL_FRAME_H