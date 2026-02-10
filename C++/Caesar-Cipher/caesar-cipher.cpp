#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <limits>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <sys/stat.h>

using namespace std;

class CaesarCipher {
private:
    int shift;
    
    char encryptChar(char ch) const {
        if (isupper(ch)) {
            return ((ch - 'A' + shift) % 26) + 'A';
        } else if (islower(ch)) {
            return ((ch - 'a' + shift) % 26) + 'a';
        } else if (isdigit(ch)) {
            return ((ch - '0' + shift) % 10) + '0';
        }
        return ch;
    }
    
    char decryptChar(char ch) const {
        if (isupper(ch)) {
            return ((ch - 'A' - shift + 26) % 26) + 'A';
        } else if (islower(ch)) {
            return ((ch - 'a' - shift + 26) % 26) + 'a';
        } else if (isdigit(ch)) {
            int val = (ch - '0' - shift) % 10;
            if (val < 0) val += 10;
            return val + '0';
        }
        return ch;
    }
    
    char decryptCharWithShift(char ch, int s) const {
        if (isupper(ch)) {
            return ((ch - 'A' - s + 26) % 26) + 'A';
        } else if (islower(ch)) {
            return ((ch - 'a' - s + 26) % 26) + 'a';
        } else if (isdigit(ch)) {
            int val = (ch - '0' - s) % 10;
            if (val < 0) val += 10;
            return val + '0';
        }
        return ch;
    }
    
public:
    CaesarCipher(int s = 3) : shift(s) {}
    
    void setShift(int s) {
        shift = s;
    }
    
    bool encryptFile(const string& inputFile, const string& outputFile) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);
        
        if (!inFile.is_open()) {
            cerr << "\n❌ Error: Cannot open input file '" << inputFile << "'" << endl;
            return false;
        }
        
        if (!outFile.is_open()) {
            cerr << "\n❌ Error: Cannot create output file '" << outputFile << "'" << endl;
            return false;
        }
        
        char ch;
        while (inFile.get(ch)) {
            outFile.put(encryptChar(ch));
        }
        
        inFile.close();
        outFile.close();
        return true;
    }
    
    bool decryptFile(const string& inputFile, const string& outputFile) {
        ifstream inFile(inputFile);
        ofstream outFile(outputFile);
        
        if (!inFile.is_open()) {
            cerr << "\n❌ Error: Cannot open input file '" << inputFile << "'" << endl;
            return false;
        }
        
        if (!outFile.is_open()) {
            cerr << "\n❌ Error: Cannot create output file '" << outputFile << "'" << endl;
            return false;
        }
        
        char ch;
        while (inFile.get(ch)) {
            outFile.put(decryptChar(ch));
        }
        
        inFile.close();
        outFile.close();
        return true;
    }
    
    void bruteForceDecrypt(const string& inputFile) {
        ifstream inFile(inputFile);
        
        if (!inFile.is_open()) {
            cerr << "\n❌ Error: Cannot open file '" << inputFile << "'" << endl;
            return;
        }
        
        string content((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();
        
        cout << "\n🔨 Trying all 25 possible shifts:" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl << endl;
        
        for (int s = 1; s <= 25; s++) {
            cout << "Shift " << setw(2) << s << ": ";
            
            int charCount = 0;
            for (char ch : content) {
                if (charCount >= 60) break;
                char decrypted = decryptCharWithShift(ch, s);
                if (decrypted == '\n' || decrypted == '\r') break;
                cout << decrypted;
                charCount++;
            }
            cout << endl;
        }
        
        cout << "\n💡 Tip: Look for readable text to find the correct shift!" << endl;
    }
    
    void frequencyAnalysis(const string& inputFile) {
        ifstream file(inputFile);
        
        if (!file.is_open()) {
            cerr << "\n❌ Error: Cannot open file '" << inputFile << "'" << endl;
            return;
        }
        
        vector<int> freq(26, 0);
        int totalLetters = 0;
        char ch;
        
        while (file.get(ch)) {
            if (isalpha(ch)) {
                freq[toupper(ch) - 'A']++;
                totalLetters++;
            }
        }
        file.close();
        
        if (totalLetters == 0) {
            cout << "\n⚠️  No alphabetic characters found in file." << endl;
            return;
        }
        
        cout << "\n📊 Letter Frequency Analysis:" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "Total letters: " << totalLetters << endl << endl;
        
        int maxFreq = *max_element(freq.begin(), freq.end());
        
        for (int i = 0; i < 26; i++) {
            if (freq[i] > 0) {
                char letter = 'A' + i;
                float percentage = (float)freq[i] / totalLetters * 100;
                int barLength = (int)((float)freq[i] / maxFreq * 40);
                
                cout << letter << ": " << setw(4) << freq[i] 
                     << " (" << fixed << setprecision(2) << setw(5) << percentage << "%) ";
                
                for (int j = 0; j < barLength; j++) {
                    cout << "█";
                }
                cout << endl;
            }
        }
        
        cout << "\n💡 In English, common letters are: E, T, A, O, I, N" << endl;
    }
    
    bool rot13File(const string& inputFile, const string& outputFile) {
        int oldShift = shift;
        shift = 13;
        bool result = encryptFile(inputFile, outputFile);
        shift = oldShift;
        return result;
    }
    
    string encryptText(const string& text) const {
        string result;
        for (char ch : text) {
            result += encryptChar(ch);
        }
        return result;
    }
    
    string decryptText(const string& text) const {
        string result;
        for (char ch : text) {
            result += decryptChar(ch);
        }
        return result;
    }
    
    void displayFileContent(const string& filename) {
        ifstream file(filename);
        
        if (!file.is_open()) {
            cerr << "\n❌ Error: Cannot open file '" << filename << "'" << endl;
            return;
        }
        
        cout << "\n📄 Content of '" << filename << "':" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        string line;
        int lineCount = 0;
        while (getline(file, line) && lineCount < 50) {
            cout << line << endl;
            lineCount++;
        }
        
        if (!file.eof()) {
            cout << "\n... (truncated, showing first 50 lines) ..." << endl;
        }
        
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        file.close();
    }
    
    void showFileStats(const string& filename) {
        ifstream file(filename, ios::binary);
        
        if (!file.is_open()) {
            cerr << "\n❌ Error: Cannot open file '" << filename << "'" << endl;
            return;
        }
        
        struct stat st;
        stat(filename.c_str(), &st);
        long fileSize = st.st_size;
        
        file.seekg(0);
        int charCount = 0, letterCount = 0, numberCount = 0, lineCount = 0;
        char ch;
        
        while (file.get(ch)) {
            charCount++;
            if (isalpha(ch)) letterCount++;
            if (isdigit(ch)) numberCount++;
            if (ch == '\n') lineCount++;
        }
        file.close();
        
        cout << "\n📈 File Statistics for '" << filename << "':" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "📏 File size:      " << fileSize << " bytes" << endl;
        cout << "📝 Total chars:    " << charCount << endl;
        cout << "🔤 Letters:        " << letterCount << endl;
        cout << "🔢 Numbers:        " << numberCount << endl;
        cout << "📄 Lines:          " << lineCount << endl;
    }
};

class FileHelper {
public:
    static string addEncExtension(const string& filename) {
        return filename + ".enc";
    }
    
    static string removeEncExtension(const string& filename) {
        if (filename.length() > 4 && filename.substr(filename.length() - 4) == ".enc") {
            return filename.substr(0, filename.length() - 4);
        }
        return filename;
    }
    
    static bool hasEncExtension(const string& filename) {
        return filename.length() > 4 && filename.substr(filename.length() - 4) == ".enc";
    }
    
    static bool fileExists(const string& filename) {
        ifstream file(filename);
        return file.good();
    }
};

class CaesarCipherApp {
private:
    CaesarCipher cipher;
    
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }
    
    void displayMenu() {
        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗" << endl;
        cout << "║                                                    ║" << endl;
        cout << "║      🔐 ENHANCED CAESAR CIPHER TOOL 🔐            ║" << endl;
        cout << "║                                                    ║" << endl;
        cout << "╚════════════════════════════════════════════════════╝" << endl << endl;
        cout << "  📝 BASIC OPERATIONS" << endl;
        cout << "  1. 🔒 Encrypt a file" << endl;
        cout << "  2. 🔓 Decrypt a file" << endl;
        cout << "  3. 🔤 Encrypt text (quick)" << endl;
        cout << "  4. 🔤 Decrypt text (quick)" << endl;
        cout << "  5. 🔨 Brute force decryption (try all shifts)" << endl << endl;
        cout << "  🔬 ANALYSIS TOOLS" << endl;
        cout << "  6. 📊 Frequency analysis" << endl;
        cout << "  7. 🔄 ROT13 encryption/decryption" << endl << endl;
        cout << "  📦 BATCH OPERATIONS" << endl;
        cout << "  8. 📂 Batch encrypt multiple files" << endl;
        cout << "  9. 📂 Batch decrypt multiple files" << endl << endl;
        cout << "  🛠️  UTILITIES" << endl;
        cout << "  10. 👁️  View file content" << endl;
        cout << "  11. 📈 File statistics" << endl;
        cout << "  12. 📚 About Caesar Cipher" << endl;
        cout << "  13. 🚪 Exit" << endl << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl << endl;
    }
    
    int getValidShift() {
        int shift;
        while (true) {
            cout << "Enter shift value (1-25): ";
            if (cin >> shift && shift >= 1 && shift <= 25) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return shift;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid! Enter a number between 1 and 25." << endl;
        }
    }
    
    void batchEncrypt() {
        cout << "\n📂 BATCH ENCRYPT FILES" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        int numFiles;
        cout << "How many files to encrypt? ";
        if (!(cin >> numFiles) || numFiles < 1) {
            cout << "❌ Invalid number of files." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cipher.setShift(getValidShift());
        
        vector<string> files(numFiles);
        for (int i = 0; i < numFiles; i++) {
            cout << "Enter filename " << (i + 1) << ": ";
            getline(cin, files[i]);
        }
        
        cout << "\n🔄 Processing files..." << endl;
        int successCount = 0;
        
        for (const auto& file : files) {
            string outFile = FileHelper::addEncExtension(file);
            
            if (FileHelper::fileExists(file)) {
                clock_t start = clock();
                if (cipher.encryptFile(file, outFile)) {
                    clock_t end = clock();
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                    cout << "✅ " << file << " → " << outFile 
                         << " (" << fixed << setprecision(4) << time_spent << "s)" << endl;
                    successCount++;
                }
            } else {
                cout << "❌ " << file << " (file not found)" << endl;
            }
        }
        
        cout << "\n🎉 Batch encryption complete! " << successCount << "/" << numFiles << " files processed." << endl;
    }
    
    void batchDecrypt() {
        cout << "\n📂 BATCH DECRYPT FILES" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        
        int numFiles;
        cout << "How many files to decrypt? ";
        if (!(cin >> numFiles) || numFiles < 1) {
            cout << "❌ Invalid number of files." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cipher.setShift(getValidShift());
        
        vector<string> files(numFiles);
        for (int i = 0; i < numFiles; i++) {
            cout << "Enter filename " << (i + 1) << ": ";
            getline(cin, files[i]);
        }
        
        cout << "\n🔄 Processing files..." << endl;
        int successCount = 0;
        
        for (const auto& file : files) {
            string outFile;
            if (FileHelper::hasEncExtension(file)) {
                outFile = FileHelper::removeEncExtension(file);
            } else {
                outFile = "decrypted_" + file;
            }
            
            if (FileHelper::fileExists(file)) {
                clock_t start = clock();
                if (cipher.decryptFile(file, outFile)) {
                    clock_t end = clock();
                    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                    cout << "✅ " << file << " → " << outFile 
                         << " (" << fixed << setprecision(4) << time_spent << "s)" << endl;
                    successCount++;
                }
            } else {
                cout << "❌ " << file << " (file not found)" << endl;
            }
        }
        
        cout << "\n🎉 Batch decryption complete! " << successCount << "/" << numFiles << " files processed." << endl;
    }
    
    void showAbout() {
        cout << "\n📚 ABOUT CAESAR CIPHER" << endl;
        cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
        cout << "\nThe Caesar Cipher is one of the simplest and oldest" << endl;
        cout << "encryption techniques. It is a substitution cipher" << endl;
        cout << "where each letter is shifted by a fixed number of" << endl;
        cout << "positions in the alphabet." << endl << endl;
        cout << "Example (shift = 3):" << endl;
        cout << "  Plain:  A B C D E F G H I J K L M" << endl;
        cout << "  Cipher: D E F G H I J K L M N O P" << endl << endl;
        cout << "  \"HELLO\" → \"KHOOR\"" << endl << endl;
        cout << "Named after Julius Caesar who used it to protect" << endl;
        cout << "military messages." << endl << endl;
        cout << "🔓 Weaknesses:" << endl;
        cout << "  • Only 25 possible keys (easily brute-forced)" << endl;
        cout << "  • Vulnerable to frequency analysis" << endl;
        cout << "  • Not secure for modern use" << endl;
    }
    
public:
    void run() {
        int choice;
        string inputFile, outputFile, text;
        
        while (true) {
            clearScreen();
            displayMenu();
            
            cout << "Enter your choice (1-13): ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\n❌ Invalid input! Press Enter to continue...";
                cin.get();
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
            if (choice == 13) {
                cout << "\n👋 Thank you for using Enhanced Caesar Cipher! Goodbye!" << endl;
                break;
            }
            
            switch (choice) {
                case 1: { // Encrypt file
                    cout << "\n📝 ENCRYPT FILE" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter input filename: ";
                    getline(cin, inputFile);
                    
                    cout << "Enter output filename (or press Enter for auto): ";
                    getline(cin, outputFile);
                    
                    if (outputFile.empty()) {
                        outputFile = FileHelper::addEncExtension(inputFile);
                        cout << "Output will be: " << outputFile << endl;
                    }
                    
                    cipher.setShift(getValidShift());
                    
                    clock_t start = clock();
                    if (cipher.encryptFile(inputFile, outputFile)) {
                        clock_t end = clock();
                        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                        cout << "\n✅ File encrypted successfully!" << endl;
                        cout << "⏱️  Time: " << fixed << setprecision(4) << time_spent << " seconds" << endl;
                        cipher.showFileStats(outputFile);
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                
                case 2: { // Decrypt file
                    cout << "\n🔓 DECRYPT FILE" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter input filename: ";
                    getline(cin, inputFile);
                    
                    cout << "Enter output filename (or press Enter for auto): ";
                    getline(cin, outputFile);
                    
                    if (outputFile.empty()) {
                        if (FileHelper::hasEncExtension(inputFile)) {
                            outputFile = FileHelper::removeEncExtension(inputFile);
                        } else {
                            outputFile = "decrypted.txt";
                        }
                        cout << "Output will be: " << outputFile << endl;
                    }
                    
                    cipher.setShift(getValidShift());
                    
                    clock_t start = clock();
                    if (cipher.decryptFile(inputFile, outputFile)) {
                        clock_t end = clock();
                        double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                        cout << "\n✅ File decrypted successfully!" << endl;
                        cout << "⏱️  Time: " << fixed << setprecision(4) << time_spent << " seconds" << endl;
                        cipher.showFileStats(outputFile);
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                }
                
                case 3: // Encrypt text
                    cout << "\n🔤 ENCRYPT TEXT" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter text to encrypt: ";
                    getline(cin, text);
                    
                    cipher.setShift(getValidShift());
                    
                    cout << "\n🔒 Encrypted: " << cipher.encryptText(text) << endl;
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 4: // Decrypt text
                    cout << "\n🔤 DECRYPT TEXT" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter text to decrypt: ";
                    getline(cin, text);
                    
                    cipher.setShift(getValidShift());
                    
                    cout << "\n🔓 Decrypted: " << cipher.decryptText(text) << endl;
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 5: // Brute force
                    cout << "\n🔨 BRUTE FORCE DECRYPTION" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter encrypted filename: ";
                    getline(cin, inputFile);
                    
                    cipher.bruteForceDecrypt(inputFile);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 6: // Frequency analysis
                    cout << "\n📊 FREQUENCY ANALYSIS" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter filename to analyze: ";
                    getline(cin, inputFile);
                    
                    cipher.frequencyAnalysis(inputFile);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 7: // ROT13
                    cout << "\n🔄 ROT13 ENCRYPTION/DECRYPTION" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter input filename: ";
                    getline(cin, inputFile);
                    
                    cout << "Enter output filename: ";
                    getline(cin, outputFile);
                    
                    if (cipher.rot13File(inputFile, outputFile)) {
                        cout << "\n✅ ROT13 applied successfully!" << endl;
                        cipher.showFileStats(outputFile);
                    }
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 8: // Batch encrypt
                    batchEncrypt();
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 9: // Batch decrypt
                    batchDecrypt();
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 10: // View file
                    cout << "\n👁️  VIEW FILE CONTENT" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter filename to view: ";
                    getline(cin, inputFile);
                    
                    cipher.displayFileContent(inputFile);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 11: // File statistics
                    cout << "\n📈 FILE STATISTICS" << endl;
                    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
                    cout << "Enter filename: ";
                    getline(cin, inputFile);
                    
                    cipher.showFileStats(inputFile);
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                case 12: // About
                    showAbout();
                    cout << "\nPress Enter to continue...";
                    cin.get();
                    break;
                    
                default:
                    cout << "\n❌ Invalid choice! Please select 1-13." << endl;
                    cout << "Press Enter to continue...";
                    cin.get();
            }
        }
    }
};

int main() {
    CaesarCipherApp app;
    app.run();
    return 0;
}
