#pragma once

#include <juce_core/juce_core.h>
#include <atomic>

class Transport
{
public:
    Transport();
    ~Transport();

    // Playback control
    void start();
    void stop();
    void pause();
    void setLoopEnabled(bool shouldLoop);

    // State
    bool isPlaying() const { return playing.load(); }
    bool isPaused() const { return paused.load(); }
    bool isLoopEnabled() const { return loopEnabled.load(); }

    // Position & timing
    void setSampleRate(double sr) { sampleRate = sr; }
    double getSampleRate() const { return sampleRate; }

    int64_t getPlayheadPositionInSamples() const { return playheadPosition.load(); }
    double getPlayheadPositionInSeconds() const;

    void setTempo(double bpm) { tempo = bpm; }
    double getTempo() const { return tempo; }

    void setTimeSignature(int numerator, int denominator)
    {
        timeSignatureNum = numerator;
        timeSignatureDen = denominator;
    }

    // Audio processing
    void process(int numSamples);

private:
    std::atomic<bool> playing{false};
    std::atomic<bool> paused{false};
    std::atomic<bool> loopEnabled{false};
    std::atomic<int64_t> playheadPosition{0};

    double sampleRate = 44100.0;
    double tempo = 120.0;
    int timeSignatureNum = 4;
    int timeSignatureDen = 4;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Transport)
};
