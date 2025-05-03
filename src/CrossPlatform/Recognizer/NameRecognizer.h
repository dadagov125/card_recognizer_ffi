//
//  NameRecognizer.h
//  CardRecognizer
//
//  Created by Vladimir Tchernitski on 08/02/16.
//  Copyright © 2016 Vladimir Tchernitski. All rights reserved.
//

#ifndef NameRecognizer_h
#define NameRecognizer_h

#include "INameRecognizer.h"
#include <fstream>
#include <sstream>

class INeuralNetworkResultList;
class IServiceContainer;
class INeuralNetwork;
class INeuralNetworkObjectFactory;
class IRecognitionCoreDelegate;

class CNameRecognizer : public INameRecognizer
{
    
public:
    CNameRecognizer(const shared_ptr<IServiceContainer>& container);
    
    virtual ~CNameRecognizer();
    
public:
    
    virtual shared_ptr<INeuralNetworkResultList> Process(cv::Mat& matrix,
                                                         vector<cv::Mat>& digitsSamples, std::string& postprocessedName);
    
    virtual bool Deploy();
    
    virtual void SetRecognitionMode(PayCardsRecognizerMode flag);
    
    virtual void SetDelegate(const shared_ptr<IRecognitionCoreDelegate>& delegate);

    
private:
    
    void Predict(const vector<cv::Mat>& matrixes, shared_ptr<INeuralNetworkResultList>& neuralNetworkResultList, const shared_ptr<INeuralNetwork>& neuralNetwork);
    int FilterCoords(const std::vector<float>& xCoords, float modelDist, std::pair<int, int>& result);
    int LevenshteinDistance(const string& src, const string& dst);
private:
    
    weak_ptr<IServiceContainer> _container;
    weak_ptr<IRecognitionCoreDelegate> _delegate;
    weak_ptr<INeuralNetworkObjectFactory> _factory;

    cv::CascadeClassifier _yCascade;
    
    shared_ptr<INeuralNetwork> _localizationXNeuralNetwork;
    shared_ptr<INeuralNetwork> _spaceCharNeuralNetwork;
    

    std::istringstream _namesDict;
    
    PayCardsRecognizerMode _mode;
};


#endif /* NameRecognizer_h */
