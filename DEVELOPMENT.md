# Development Guidelines

## Real-Time Safety

**CRITICAL**: The audio thread must never:
- Allocate memory (`new`, `malloc`, `std::vector.push_back()`, etc.)
- Lock mutexes (use lock-free structures like `juce::AbstractFifo`, atomic operations)
- Log to files (use `DBG()` macro only during non-real-time or for debugging)
- Block I/O operations
- Call virtual functions with unknown implementations

### Lock-Free Communication

For UI ↔ Audio thread communication, use:
- `juce::AbstractFifo` for lock-free FIFO queues
- `std::atomic<T>` for simple values
- Message queues built on atomic operations

### Example: Safe Parameter Update

```cpp
// Bad (locks on audio thread):
std::lock_guard<std::mutex> lock(mutex);
parameter = newValue;  // VIOLATES REAL-TIME SAFETY

// Good (lock-free):
parameterAtomic.store(newValue);
// In audio thread:
auto value = parameterAtomic.load();
```

## Plugin Architecture

### Track Model

Each track holds:
- **Input routing** (device channel or previous track output)
- **Plugin chain** (ordered vector of `juce::AudioProcessor` instances)
- **Mixer parameters** (volume, pan, mute, solo)
- **Automation data** (parameter curves)
- **Output routing** (to bus or master)

### Processor Graph

The `ProcessorGraph` maintains a directed acyclic graph (DAG):
- Nodes: Tracks, buses, auxiliary returns, master
- Edges: Signal flow
- Topological sort ensures correct processing order
- No loops (feedback managed via explicit auxiliary send/return)

## Testing

### Audio Thread Profiling

Before merging, check:
- Peak CPU usage (aim for <20% on audio thread)
- Glitch detection (monitor for buffer overruns)
- Memory stability (audio thread should not allocate after startup)

### Build Verification

```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Coding Standards

- Use C++20 features (e.g., `std::unique_ptr`, structured bindings)
- Follow JUCE naming conventions (`camelCase` for functions, `PascalCase` for classes)
- Prefer `juce::String` over `std::string` in JUCE code
- Always use `JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR` in class bodies
