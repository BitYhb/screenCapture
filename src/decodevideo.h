#ifndef DECODEVIDEO_H
#define DECODEVIDEO_H

#include <QWidget>
#include <QString>
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
class DecodeVideo
{
public:
    explicit DecodeVideo();
    //将视屏文件解析为一帧一帧的图片并保存  保存之后将这些图片进行重新编码 生成另外的视屏
    static bool videoToPicture(const char *strOutPutFileName, const char *strInputFileName);
    static bool saveFrame(AVFrame* pFrame, int width, int height, int iFrame,const char *outname);
};

#endif // DECODEVIDEO_H
