#ifndef SCREEN_CAPTURE_H
#define SCREEN_CAPTURE_H

#include <QThread>
#include <QTcpSocket>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <libavutil/fifo.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
}
extern "C"
{
#ifdef __cplusplus
#define __STDC_CONSTANT_MACROS
#ifdef _STDINT_H
#undef _STDINT_H
#endif
#include<stdint.h>
#endif
}

class ScreenCapture : public QThread
{
    Q_OBJECT
public:
    explicit ScreenCapture(QWidget *parent = 0, QString savefile = "record.mp4");
    void initGeometry(const int offsetX, const int offsetY, const int width, const int height);
protected:
    void run();

private:
    AVFrame* avFrameRgb;                //解码帧对象RGB
    AVFrame* avFrameYuv;                //解码帧对象YUV
    AVStream* in_stream;                //输入视频流
    AVStream* out_stream;               //输出视频流
    AVCodecContext* deCodecCtx;         //解码器上下文
    AVCodecContext* enCodecCtx;         //解码器上下文
    SwsContext* swsContextYuvtoRgb;     //格式转换上下文（YuvtoRgb）
    SwsContext* swsContextRgbtoYuv;     //格式转换上下文（RgbtoYuv）
    AVFormatContext *ifmt_ctx;          //输入格式对象
    AVFormatContext *ofmt_ctx;          //输出格式对象
    AVOutputFormat *ofmt;               //输出格式
    AVPacket *avDePacket;               //包对象
    AVPacket* avEnPacket;               //包对象
    AVPixelFormat srcFormat;            //像素格式
    AVPixelFormat dstFormat;            //像素格式

    QString url;                        //视频流地址
    QString fileName;                   //保存文件名称
    bool m_bStop;                          //线程停止标志
    int videoStreamIndex;               //视频流索引
    int videoWidth;                     //视频宽度
    int videoHeight;                    //视频高度
    int videoFps;                       //视频帧率
    int videoIndex;                     //视频索引
    uint64_t frameCount;                //帧计数

    int m_offsetX = 0;                  //x偏移量
    int m_offsetY = 0;                  //y偏移量
    int m_width = 0;                    //录制宽度
    int m_height = 0;                   //录制高度

private:
    bool  intiDeContext();
    bool  initDecoder();
    bool  initEncoder();
    bool  initOutputStream();
    bool  initSwsContext();
    void  memoryAlloc();
    bool  initmodules();

signals:
    void initFinished();

public:
    void setStop(bool stop);
};

#endif // SCREEN_CAPTURE_H
