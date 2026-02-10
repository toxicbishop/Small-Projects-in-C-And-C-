# Caesar Cipher - Enhanced File Encryption/Decryption

A comprehensive Caesar Cipher implementation in C with advanced features for encryption, decryption, and cryptanalysis!

## 🌟 Features

### 📝 Basic Operations

- 🔒 **File Encryption** - Encrypt entire text files with custom shift values
- 🔓 **File Decryption** - Decrypt encrypted files back to original text
- 🔄 **ROT13** - Special case Caesar cipher with shift=13 (self-inverse)

### 🔬 Analysis & Cracking Tools

- 🔨 **Brute Force Decryption** - Try all 25 possible shifts automatically
- 📊 **Frequency Analysis** - Analyze letter distribution with visual bar charts
- 💡 **Educational Insights** - Learn about cipher vulnerabilities

### 📦 Batch Processing

- 📂 **Batch Encryption** - Encrypt multiple files in one operation
- 📂 **Batch Decryption** - Decrypt multiple files simultaneously
- ⏱️ **Performance Tracking** - See encryption/decryption time

### 🛠️ Smart Features

- 🏷️ **Auto File Extensions** - Automatically adds/removes `.enc` extension
- 📈 **File Statistics** - View file size, character count, lines
- 👁️ **File Viewer** - Preview file contents in the app
- ✅ **Input Validation** - Robust error handling throughout

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
gcc caesar-cipher.c -o caesar-cipher
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
3. 🔨 Brute force decryption (try all shifts)

**Analysis Tools:**
4. 📊 Frequency analysis
5. 🔄 ROT13 encryption/decryption

**Batch Operations:**
6. 📂 Batch encrypt multiple files
7. 📂 Batch decrypt multiple files

**Utilities:**
8. 👁️ View file content
9. 📈 File statistics
10. 📚 About Caesar Cipher
11. 🚪 Exit

## 🎯 Example Workflows

### Encrypting a File

1. Select option 1
2. Input file: `sample.txt`
3. Output file: Press Enter (auto creates `sample.txt.enc`)
4. Shift value: `5`
5. Done! See statistics and timing

### Cracking an Encrypted File

1. Select option 3 (Brute force)
2. Input encrypted file
3. View all 25 possible decryptions
4. Identify the readable one!

### Analyzing Letter Frequency

1. Select option 4
2. Enter filename
3. See visual bar chart of letter distribution
4. Use this to identify common patterns

### Batch Processing

1. Select option 6 (Batch encrypt)
2. Enter number of files
3. Enter each filename
4. Enter shift value
5. All files encrypted with timing!

## 🆕 New Features Explained

### 1. Brute Force Decryption

Don't know the shift? No problem! This feature tries all 25 possible shifts and shows you the first 60 characters of each attempt. Look for readable text!

### 2. Frequency Analysis

Shows:

- Total letter count
- Frequency of each letter (count and percentage)
- Visual bar chart representation
- Comparison to common English letters (E, T, A, O, I, N)

### 3. Auto File Extensions

- Encrypting: `document.txt` → `document.txt.enc`
- Decrypting: `document.txt.enc` → `document.txt`
- Smart detection and removal

### 4. Batch Processing

Process multiple files at once:

- Enter how many files
- Provide all filenames
- One shift value for all
- See progress and results

### 5. File Statistics

View detailed info:

- File size in bytes
- Total character count
- Alphabetic letter count
- Number of lines

### 6. Performance Tracking

- See encryption/decryption time
- Useful for large files
- Displayed in seconds with precision

## Sample File

A `sample.txt` file is included for testing all features!

## Technical Details

- **Algorithm**: Caesar Cipher (Substitution Cipher)
- **Supported Characters**: A-Z, a-z (case preserved)
- **Non-alphabetic Characters**: Preserved unchanged
- **Shift Range**: 1-25
- **ROT13**: Special case with shift=13 (self-inverse property)

## Learning Concepts

- File I/O operations
- Character manipulation and ASCII
- Modular arithmetic
- Menu-driven programming
- Batch processing
- Algorithm analysis and weaknesses
- Frequency analysis in cryptography
- Performance measurement

## Security Note

⚠️ **Educational Purpose Only**: The Caesar Cipher is NOT secure for real-world use:

- Only 25 possible keys (trivial brute force)
- Vulnerable to frequency analysis
- Pattern preservation reveals structure
- This project demonstrates why simple ciphers are weak!

## Why This Project is Educational

1. **Learn Cryptography Basics** - Understand substitution ciphers
2. **See Cipher Weaknesses** - Brute force and frequency analysis demonstrate vulnerability
3. **File I/O Practice** - Work with reading/writing files
4. **Algorithm Implementation** - Practice modular arithmetic
5. **User Interface** - Create comprehensive menu systems

Enjoy learning about cryptography! 🔐
