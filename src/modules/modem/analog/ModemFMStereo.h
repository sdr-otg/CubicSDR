#pragma once
#include "Modem.h"

class ModemKitFMStereo: public ModemKit {
public:
    ModemKitFMStereo() : audioResampler(nullptr), stereoResampler(nullptr), audioResampleRatio(0), firStereoLeft(nullptr), firStereoRight(nullptr), iirStereoPilot(nullptr) {
    }
    
    msresamp_rrrf audioResampler;
    msresamp_rrrf stereoResampler;
    double audioResampleRatio;
    
    firfilt_rrrf firStereoLeft;
    firfilt_rrrf firStereoRight;
    iirfilt_crcf iirStereoPilot;
    
    firhilbf firStereoR2C;
    firhilbf firStereoC2R;
    
    nco_crcf stereoPilot;
};


class ModemFMStereo : public Modem {
public:
    ModemFMStereo();
    ~ModemFMStereo();
    
    std::string getType();
    std::string getName();
    
    Modem *factory();
    
    int checkSampleRate(long long sampleRate, int audioSampleRate);
    int getDefaultSampleRate();
    
    ModemKit *buildKit(long long sampleRate, int audioSampleRate);
    void disposeKit(ModemKit *kit);
    
    void demodulate(ModemKit *kit, ModemIQData *input, AudioThreadInput *audioOut);
    
private:
    std::vector<float> demodOutputData;
    std::vector<float> demodStereoData;
    std::vector<float> resampledOutputData;
    std::vector<float> resampledStereoData;
    freqdem demodFM;
};