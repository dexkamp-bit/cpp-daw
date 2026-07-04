# Fluid DAW — C++ Digital Audio Workstation

A cross-platform DAW (Digital Audio Workstation) inspired by FL Studio, built with **C++20** and **JUCE framework**.

## Features (Roadmap)

- ✅ Real-time audio engine with lock-free communication
- ✅ VST3 plugin hosting (effects & instruments)
- ✅ Audio track recording with waveform display
- ✅ MIDI piano roll editor
- ✅ Mixer with volume, pan, mute/solo, effects chains
- ✅ Automation lanes for any parameter
- ✅ Drag-and-drop file import
- ✅ Project save/load with undo/redo
- ✅ Modern dark-themed UI

## Build Instructions

### Prerequisites

- **CMake** 3.21+
- **C++20 compiler** (MSVC 2019+, Clang 10+, GCC 10+)
- **JUCE** (automatically downloaded via submodule)

### macOS

```bash
git clone https://github.com/dexkamp-bit/cpp-daw.git
cd cpp-daw
git submodule update --init --recursive  # Fetch JUCE
mkdir build && cd build
cmake -GXcode ..
cmake --build . --config Release
./FluidDAW_artefacts/Release/Fluid\ DAW.app/Contents/MacOS/Fluid\ DAW
```

### Windows

```bash
git clone https://github.com/dexkamp-bit/cpp-daw.git
cd cpp-daw
git submodule update --init --recursive
mkdir build && cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release
.\FluidDAW_artefacts\Release\Fluid DAW.exe
```

### Linux (Experimental)

```bash
git clone https://github.com/dexkamp-bit/cpp-daw.git
cd cpp-daw
git submodule update --init --recursive
mkdir build && cd build
cmake ..
cmake --build .
./FluidDAW_artefacts/Release/Fluid\ DAW
```

## Architecture

```
Source/
├── Main.cpp                    # Application entry point
├── MainWindow.h/cpp            # Top-level window
├── Audio/
│   ├── AudioEngine.h/cpp       # Real-time audio callback manager
│   ├── ProcessorGraph.h/cpp    # Track & plugin graph routing
│   └── Transport.h/cpp         # Playback transport (play, stop, record)
└── UI/
    ├── MainComponent.h/cpp     # Main UI layout
    ├── TimelineView.h/cpp      # Arrangement/timeline editor
    ├── MixerView.h/cpp         # Mixer strips
    ├── PianoRoll.h/cpp         # MIDI editor
    └── BrowserPanel.h/cpp      # File/plugin browser

ThirdParty/
└── JUCE/                       # JUCE framework (submodule)

Resources/
└── (Fonts, images, etc.)
```

## Milestones

1. ✅ **Scaffold + CMake + JUCE** — Basic window, build system
2. 🔄 **Audio Engine** — Play sine wave, load WAV
3. ⏳ **Audio Track + Waveform** — Drag-and-drop import
4. ⏳ **Mixer** — Volume, pan, mute/solo
5. ⏳ **VST3 Hosting** — Plugin scanning & loading
6. ⏳ **MIDI Track + Piano Roll** — Instrument hosting
7. ⏳ **Recording** — Audio & MIDI capture
8. ⏳ **Buses & Routing** — Submixes, sends
9. ⏳ **Automation** — Curve editing
10. ⏳ **Project Save/Load** — Persistence & undo/redo
11. ⏳ **Polish** — Metering, snapping, performance

## Development

See [DEVELOPMENT.md](./DEVELOPMENT.md) for guidelines on real-time safety, plugin architecture, and contribution workflow.

## License

MIT
