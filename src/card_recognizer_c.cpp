//src/card_recognizer_c.cpp
#include <iostream>
#include <chrono>
#include <memory>
#include <string>
#include "CrossPlatform/Include/Public/IRecognitionCore.h"
#include "CrossPlatform/Include/Public/IRecognitionCoreDelegate.h"
#include "CrossPlatform/Include/Public/ITorchDelegate.h"
#include "CrossPlatform/Include/Public/Enums.h"
#include "CrossPlatform/Recognizer/RecognitionCore.h"






// Заглушка для IRecognitionCoreDelegate
class RecognitionCoreDelegateStub : public IRecognitionCoreDelegate {
public:
    static bool GetInstance(std::shared_ptr<IRecognitionCoreDelegate>& recognitionDelegate, void* platformDelegate = nullptr, void* recognizer = nullptr) {
        recognitionDelegate = std::make_shared<RecognitionCoreDelegateStub>();
        return true;
    }

    void RecognitionDidFinish(const std::shared_ptr<IRecognitionResult>& result, PayCardsRecognizerMode resultFlags) override {
        std::cout << "Stub: RecognitionDidFinish called" << std::endl;
    }

    void CardImageDidExtract(cv::Mat cardImage) override {
        std::cout << "Stub: CardImageDidExtract called" << std::endl;
    }
};

// Заглушка для ITorchDelegate
class TorchDelegateStub : public ITorchDelegate {
public:
    static bool GetInstance(std::shared_ptr<ITorchDelegate>& torchDelegate, void* platformDelegate = nullptr) {
        torchDelegate = std::make_shared<TorchDelegateStub>();
        return true;
    }

    void TorchStatusDidChange(bool status) override {
        std::cout << "Stub: TorchStatusDidChange called with status: " << status << std::endl;
    }
};

extern "C" {
    static std::shared_ptr<IRecognitionCore> recognitionCore = nullptr;

    unsigned long long nativeInit(){


        std::shared_ptr<IRecognitionCoreDelegate> recognitionDelegate;
        RecognitionCoreDelegateStub::GetInstance(recognitionDelegate);

        std::shared_ptr<ITorchDelegate> torchDelegate;
        TorchDelegateStub::GetInstance(torchDelegate);


        IRecognitionCore::GetInstance(recognitionCore, recognitionDelegate, torchDelegate);

        std::cout << "Instances created successfully" << std::endl;


        recognitionCore->SetRecognitionMode(PayCardsRecognizerModeNumber);

        recognitionCore->Deploy();

        return static_cast<unsigned long long>(reinterpret_cast<intptr_t>(recognitionCore.get()));

    }

}