# Caesar Cipher - Enhanced File Encryption/Decryption (C++)

A comprehensive Caesar Cipher implementation in C++ using Object-Oriented Programming with advanced features for encryption, decryption, and cryptanalysis!

## 🌟 Features

### 📝 Basic Operations

- 🔒 **File Encryption** - Encrypt entire text files with custom shift values
- 🔓 **File Decryption** - Decrypt encrypted files back to original text
- 🔤 **Quick Text Encryption/Decryption** - Encrypt or decrypt text directly without files
- 🔄 **ROT13** - Special case Caesar cipher with shift=13 (self-inverse)

### 🔬 Analysis & Cracking Tools

- 🔨 **Brute Force Decryption** - Try all 25 possible shifts automatically
- 📊 **Frequency Analysis** - Analyze letter distribution with visual bar charts
- 💡 **Educational Insights** - Learn about cipher vulnerabilities

### 📦 Batch Processing

- 📂 **Batch Encryption** - Encrypt multiple files in one operation
- 📂 **Batch Decryption** - Decrypt multiple files simultaneously
- ⏱️ **Performance Tracking** - See encryption/decryption time for each file

### 🛠️ Smart Features

- 🏷️ **Auto File Extensions** - Automatically adds/removes `.enc` extension
- 📈 **File Statistics** - View file size, character count, lines
- 👁️ **File Viewer** - Preview file contents in the app
- ✅ **Input Validation** - Robust error handling throughout
- 🏗️ **OOP Design** - Clean class architecture with encapsulation

## What is Caesar Cipher?

The Caesar Cipher is one of the oldest and simplest encryption techniques. It's a **substitution cipher** where each letter in the plaintext is shifted by a fixed number of positions down the alphabet.

### Example (Shift = 3)

```text
Plain:  HELLO WORLD
Cipher: KHOOR ZRUOG
```

### ROT13 Example

```text
Plain:  HELLO WORLD
ROT13:  URYYB JBEYQ
```

## How to Use

### 1. Compile the Program

```bash
g++ caesar-cipher.cpp -o caesar-cipher
```

### 2. Run the Program

```bash
./caesar-cipher        # Linux/Mac
caesar-cipher.exe      # Windows
```

### 3. Enhanced Menu Options

**Basic Operations:**

1. 🔒 Encrypt a file
2. 🔓 Decrypt a file
3. 🔤 Encrypt text (quick)
4. 🔤 Decrypt text (quick)
5. 🔨 Brute force decryption (try all shifts)

**Analysis Tools:**
6. 📊 Frequency analysis
7. 🔄 ROT13 encryption/decryption

**Batch Operations:**
8. 📂 Batch encrypt multiple files
9. 📂 Batch decrypt multiple files

**Utilities:**
10. 👁️ View file content
11. 📈 File statistics
12. 📚 About Caesar Cipher
13. 🚪 Exit

## 🎯 Example Workflows

### Quick Text Encryption

1. Select option 3
2. Enter: `Hello World`
3. Shift: `7`
4. Result: `Olssv Dvysk` 🔒

### Cracking an Encrypted File

1. Select option 5 (Brute force)
2. Input encrypted file
3. View all 25 possible decryptions
4. Identify the readable one!

### Analyzing Letter Frequency

1. Select option 6
2. Enter filename
3. See visual bar chart with percentages
4. Compare to English letter frequency

### Batch Processing

1. Select option 8 (Batch encrypt)
2. Enter: `3` files
3. List filenames
4. Enter shift value
5. See progress with individual timing!

## 🆕 Enhanced Features Explained

### 1. Brute Force Decryption

Don't know the shift? No problem! This feature tries all 25 possible shifts and shows you the first 60 characters of each attempt. Perfect for learning about cipher weakness!

### 2. Frequency Analysis

Advanced visualization:

- Total letter count
- Frequency of each letter (count and percentage)
- Visual bar chart with `█` blocks
- Scale normalized to max frequency
- Tips about common English letters

### 3. Auto File Extensions

Smart file handling:

- Encrypting: `document.txt` → `document.txt.enc`
- Decrypting: `document.txt.enc` → `document.txt`
- Automatic detection and removal
- Manual override available

### 4. Batch Processing

Efficient multi-file operations:

- Process multiple files with one command
- Individual timing for each file
- Success/failure tracking
- Automatic output naming

### 5. File Statistics

Comprehensive file info:

- File size in bytes
- Total character count
- Alphabetic letter count
- Number of lines

### 6. Performance Tracking

Precision timing:

- High-resolution timing with `clock()`
- Displayed to 4 decimal places
- Separate timing for batch operations
- Useful for performance analysis

## Code Structure

```cpp
class CaesarCipher {
    - Core encryption/decryption logic
    - File I/O operations
    - Text processing methods
    - Analysis tools (brute force, frequency)
    - Statistics and viewing
}

class FileHelper {
    - File extension management
    - File existence checking
    - Path manipulation utilities
}

class CaesarCipherApp {
    - User interface management
    - Menu system
    - Input validation
    - Batch operation coordination
}
```

## Sample File

A `sample.txt` file is included for testing all features!

## Technical Details

- **Algorithm**: Caesar Cipher (Substitution Cipher)
- **Supported Characters**: A-Z, a-z (case preserved)
- **Non-alphabetic Characters**: Preserved unchanged
- **Shift Range**: 1-25
- **ROT13**: Special case with shift=13 (self-inverse property)
- **Architecture**: Multi-class OOP design
- **STL Usage**: Strings, vectors, file streams

## Learning Concepts

- Object-Oriented Programming (classes, encapsulation, methods)
- File I/O with `ifstream`/`ofstream`
- String manipulation with STL
- Vector containers
- Character manipulation and ASCII
- Modular arithmetic
- Algorithm analysis and weaknesses
- Frequency analysis in cryptography
- Performance measurement with `clock()`
- Clean code architecture and separation of concerns

## Security Note

⚠️ **Educational Purpose Only**: The Caesar Cipher is NOT secure for real-world use:

- Only 25 possible keys (trivial brute force)
- Vulnerable to frequency analysis
- Pattern preservation reveals structure
- This project demonstrates why simple ciphers are weak!

## Why This Project is Educational

1. **Learn Cryptography Basics** - Understand substitution ciphers
2. **See Cipher Weaknesses** - Brute force and frequency analysis demonstrate vulnerability
3. **Practice OOP** - Multi-class design with clear responsibilities
4. **File I/O Mastery** - Work with file streams effectively
5. **STL Usage** - Strings, vectors, algorithms
6. **Performance** - Timing and optimization awareness

Enjoy learning about cryptography and C++! 🔐
