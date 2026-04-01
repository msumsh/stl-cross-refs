# stl-cross-refs
Cross-Reference Index Implementation using STL Hash Table. Built with STL containers and an interactive command system.

## Features
- File parsing - reads text files
- Word indexing - maps each word to all line numbers where it appears
- Search - query specific words to see their line references
- Full map output - display the complete cross-reference index
- Case-insensitive, handles hyphens and apostrophes
- Interactive commands

## Technologies
- Language: C++17
- Build System: CMake
- STL containers: std::unordered_map, std::set, std::vector

## Run instructions
Basic Usage
```bash
./< executed_program > ./your_text.txt
```

## Available Commands
- HELP - display all available commands
- MAP - show the complete cross-reference index (all words)
- REFS <word> - show line numbers for a specific word


