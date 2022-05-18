#include "screencapturefactory.h"
ScreenCaptureFactory::ScreenCaptureFactory()
{}
ScreenCaptureFactory *ScreenCaptureFactory::instance()
{
    static ScreenCaptureFactory instance;
    return &instance;
}

ScreenCapture *ScreenCaptureFactory::getWorkerThread(CaptureType type)
{
    switch(type)
    {
        case ScreenCaptureFactory::CaptureType::FullScreen:
        {
            return new ScreenCapture;
        }
        case ScreenCaptureFactory::CaptureType::PartArea:
        {
            return new ScreenCapture;
        }
    }
    return nullptr;
}
