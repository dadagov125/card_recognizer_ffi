//
//  INameRecognizer.h
//  CardRecognizer
//
//  Created by Vladimir Tchernitski on 08/02/16.
//  Copyright © 2016 Vladimir Tchernitski. All rights reserved.
//

#ifndef INameRecognizer_h
#define INameRecognizer_h

#include "IBaseObj.h"
#include "Enums.h"

class INeuralNetworkResultList;
class IRecognitionCoreDelegate;

using namespace std;

class INameRecognizer : public IBaseObj
{
public:
    
    virtual ~INameRecognizer() {}
    
public:
    
    virtual shared_ptr<INeuralNetworkResultList> Process(cv::Mat& frame, vector<cv::Mat>& samples, std::string& postprocessedName) = 0;
    virtual bool Deploy() = 0;
    
    virtual void SetRecognitionMode(PayCardsRecognizerMode flag) = 0;
    
    virtual void SetDelegate(const shared_ptr<IRecognitionCoreDelegate>& delegate) = 0;


};


#endif /* INameRecognizer_h */
