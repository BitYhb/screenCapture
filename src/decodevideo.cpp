#include "decodevideo.h"
#include <QDebug>
DecodeVideo::DecodeVideo()
{}

bool DecodeVideo::videoToPicture(const char * strOutPutFileName, const char * strInputFileName)
{
    AVFormatContext* pFormatCtx = NULL;
    //[1] 打开输入的视频文件，获取文件流的信息
    if(avformat_open_input(&pFormatCtx,strInputFileName,NULL,NULL))
    {
        qDebug() << "avformat_open_input error";
        return false;
    }
    //[2]获取文件流信息info
    if(avformat_find_stream_info(pFormatCtx,NULL) < 0)
    {
        qDebug() << "avformat_find_stream_info";
        return false;
    }
    //just output format info of input file
    av_dump_format(pFormatCtx,0,strInputFileName,0);
    int videoStream = -1;
    //[3] 查找视屏文件流
    for(int i = 0 ; i < pFormatCtx->nb_streams ; ++i)
    {
        if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            videoStream = i;
            break;
        }
    }
    if(-1 == videoStream)
    {
        qDebug() << "find video stream error";
        return false;
    }
    AVCodecContext *pCodeCtxOrg = NULL;
    AVCodecContext *pCodeCtx = NULL;

    AVCodec *pCodec = NULL;
    //[4] 查找解码器
    pCodec = avcodec_find_decoder(pCodeCtxOrg->codec_id);
    if(!pCodec)
    {
        qDebug() << "find decoder error";
        return false;
    }
    //[5] 获取AVCodeContext一个实例,解码需要
    pCodeCtx = avcodec_alloc_context3(pCodec);
    if(avcodec_copy_context(pCodeCtx,pCodeCtxOrg) != 0)
    {
        qDebug() << "avcodec_copy_context error";
        return false;
    }
    //[6] 打开
    if(avcodec_open2(pCodeCtx,pCodec,NULL) < 0)
    {
        return false;
    }
    //输出
    AVFrame *pFrame = NULL;
    AVFrame *pFrameRGB = NULL;
    pFrame = av_frame_alloc();
    pFrameRGB = av_frame_alloc();

    int numBytes = 0;
        uint8_t* buffer = NULL;
        numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodeCtx->width, pCodeCtx->height);
            buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));

            avpicture_fill((AVPicture*)pFrameRGB, buffer, AV_PIX_FMT_RGB24, pCodeCtx->width, pCodeCtx->height);

            struct SwsContext* sws_ctx = NULL;
            sws_ctx = sws_getContext(pCodeCtx->width, pCodeCtx->height, pCodeCtx->pix_fmt,
                pCodeCtx->width, pCodeCtx->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);

            AVPacket packet;
            int i = 0;
            //step 7:read frame
            while (av_read_frame(pFormatCtx, &packet) >= 0)
            {
                int frameFinished = 0;
                avcodec_decode_video2(pCodeCtx, pFrame, &frameFinished, &packet);
                if (frameFinished)
                {
                    sws_scale(sws_ctx, (uint8_t const * const *)pFrame->data, pFrame->linesize, 0,
                        pCodeCtx->height, pFrameRGB->data, pFrameRGB->linesize);

                    if (++i <= 5)
                    {
                        //step 8:save frame
                        saveFrame(pFrameRGB, pCodeCtx->width, pCodeCtx->height, i,strOutPutFileName);
                    }
                }
            }
            //release resource
            av_free_packet(&packet);

            av_free(buffer);
            av_frame_free(&pFrameRGB);

            av_frame_free(&pFrame);

            avcodec_close(pCodeCtx);
            avcodec_close(pCodeCtxOrg);

            avformat_close_input(&pFormatCtx);


    return true;
}

bool DecodeVideo::saveFrame(AVFrame *pFrame, int width, int height, int iFrame, const char *outname)
{
    FILE *pFile;
        char szFilename[32];
        int  y;

        // Open file
        sprintf(szFilename, outname, iFrame);
        pFile = fopen(szFilename, "wb");
        if (pFile == NULL)
            return false;

        // Write header
        fprintf(pFile, "P6\n%d %d\n255\n", width, height);

        // Write pixel data
        for (y = 0; y < height; y++)
            fwrite(pFrame->data[0] + y*pFrame->linesize[0], 1, width * 3, pFile);

        // Close file
        fclose(pFile);
    return true;
}
