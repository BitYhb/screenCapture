#ifndef SCREENCAPTUREFACTORY_H
#define SCREENCAPTUREFACTORY_H


#include "screencapture.h"

class ScreenCaptureFactory final
{
public:
    enum class CaptureType{FullScreen = 0x01,PartArea};
    static ScreenCaptureFactory *instance();

    ScreenCapture *getWorkerThread(ScreenCaptureFactory::CaptureType type);
private:
    ScreenCaptureFactory();
private:
};

#endif // SCREENCAPTUREFACTORY_H
