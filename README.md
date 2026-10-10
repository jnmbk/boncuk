# Boncuk

**Boncuk** is a fast, simple, and useful Turkish-English-German dictionary. Originally a C++ port of `pysozluk-qt`, it provides a lightweight desktop interface and a console tool to search translations both online and offline.

## Features

- **Multi-language Support:** Search translations between Turkish, English, and German.
- **Offline & Online Modes:** 
  - Includes a built-in SQLite database for fast offline searches.
  - Supports fetching definitions online via Sesli Sözlük.
- **Command-line Interface:** Comes with a built-in console mode for quick terminal lookups.
- **Search History:** Keeps a configurable history of your previous searches.
- **Lightweight:** Built with C++ and Qt for maximum performance and minimal resource usage.

## Requirements

To build and run Boncuk, you will need:
- Qt 6
- SQLite plugin for Qt 6 (`libqt6sql6-sqlite` or equivalent depending on your system)
- Make, GCC/Clang, or other standard C++ build tools

## Installation

### Compiling from Source

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/boncuk.git
   cd boncuk
   ```

2. **Generate translation files:**
   ```bash
   lrelease boncuk.pro
   ```

3. **Build the project:**
   ```bash
   qmake
   make
   ```

4. **Run Boncuk:**
   The compiled binary will be placed in the `bin/` directory.
   ```bash
   ./bin/boncuk
   ```

## Usage

### Graphical Interface (GUI)
Simply run the `boncuk` executable to launch the graphical interface. You can type a word and press Enter (or click the search button) to see translations.

### Console Interface (CLI)
You can use Boncuk directly from your terminal by passing a word as an argument:
```bash
boncuk "word to search"
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request or open an issue on GitHub.
- See `TODO` for planned features and known bugs.
- See `AUTHORS` for the list of contributors.

## License

Boncuk is open-source software. See the `COPYING` file for more details.
