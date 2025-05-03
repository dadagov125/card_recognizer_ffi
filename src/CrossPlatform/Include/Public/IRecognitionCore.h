//
//  IRecognitionCore.h
//  CardRecognizer
//
//  Created by Vladimir Tchernitski on 12/01/16.
//  Copyright © 2016 Vladimir Tchernitski. All rights reserved.
//

#ifndef IRecognitionCore_h
#define IRecognitionCore_h

#include <opencv2/opencv.hpp>
#include "Enums.h"

typedef enum DetectedLineFlags
{
    DetectedLineNoneFlag    = 0,
    DetectedLineTopFlag     = 1,
    DetectedLineBottomFlag  = 2,
    DetectedLineLeftFlag    = 4,
    DetectedLineRightFlag   = 8
} DetectedLineFlags;

class IRecognitionResult;
class IRecognitionCoreDelegate;
class ITorchDelegate;

using namespace std;

class IRecognitionCore
{
public:
    
    virtual ~IRecognitionCore() {}
    
public:
    
    static bool GetInstance(shared_ptr<IRecognitionCore> &recognitionCore,
                            const shared_ptr<IRecognitionCoreDelegate>& recognitionDelegate,
                            const shared_ptr<ITorchDelegate>& torchDelegate);
    
    virtual void SetRecognitionMode(PayCardsRecognizerMode flag) = 0;
    
    virtual void Deploy() = 0;
    
    virtual void SetOrientation(PayCardsRecognizerOrientation orientation) = 0;
    

    virtual bool IsIdle() const = 0;
    virtual void SetIdle(bool isIdle) = 0;
    virtual void ResetResult() = 0;
    
    virtual void SetTorchStatus(bool status) = 0;
    
    virtual cv::Rect CalcWorkingArea(cv::Size frameSize, int captureAreaWidth) = 0;
    
    virtual void ProcessFrame(DetectedLineFlags& edgeFlags, void* bufferY, void* bufferUV, size_t bufferSizeY, size_t bufferSizeUV) = 0;
};

#endif /* IRecognitionCore_h */
