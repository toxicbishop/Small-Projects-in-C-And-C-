#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/stat.h>

#define MAX_BUFFER 1024
#define MAX_FILES 100

// Function prototypes
void encryptFile(const char* inputFile, const char* outputFile, int shift);
void decryptFile(const char* inputFile, const char* outputFile, int shift);
void bruteForceDecrypt(const char* inputFile);
void frequencyAnalysis(const char* inputFile);
void rot13File(const char* inputFile, const char* outputFile);
void batchEncrypt();
void batchDecrypt();
char encryptChar(char ch, int shift);
char decryptChar(char ch, int shift);
void displayMenu();
void clearScreen();
int getValidShift();
void displayFileContent(const char* filename);
void showFileStats(const char* filename);
long getFileSize(const char* filename);
char* addEncExtension(const char* filename, char* output);
char* removeEncExtension(const char* filename, char* output);
int hasEncExtension(const char* filename);

int main() {
    int choice;
    char inputFile[256];
    char outputFile[256];
    char tempOutput[300];
    int shift;
    
    while (1) {
        clearScreen();
        displayMenu();
        
        printf("Enter your choice (1-11): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear input buffer
            printf("\n❌ Invalid input! Press Enter to continue...");
            getchar();
            continue;
        }
        getchar(); // Consume newline
        
        if (choice == 11) {
            printf("\n👋 Thank you for using Enhanced Caesar Cipher! Goodbye!\n");
            break;
        }
        
        switch (choice) {
            case 1: // Encrypt file
                printf("\n🔒 ENCRYPT FILE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                printf("Enter output filename (or press Enter for auto): ");
                fgets(outputFile, sizeof(outputFile), stdin);
                outputFile[strcspn(outputFile, "\n")] = 0;
                
                if (strlen(outputFile) == 0) {
                    addEncExtension(inputFile, tempOutput);
                    strcpy(outputFile, tempOutput);
                    printf("Output will be: %s\n", outputFile);
                }
                
                shift = getValidShift();
                
                clock_t start = clock();
                encryptFile(inputFile, outputFile, shift);
                clock_t end = clock();
                
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                printf("\n✅ File encrypted successfully!\n");
                printf("⏱️  Time: %.4f seconds\n", time_spent);
                showFileStats(outputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 2: // Decrypt file
                printf("\n🔓 DECRYPT FILE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                printf("Enter output filename (or press Enter for auto): ");
                fgets(outputFile, sizeof(outputFile), stdin);
                outputFile[strcspn(outputFile, "\n")] = 0;
                
                if (strlen(outputFile) == 0) {
                    if (hasEncExtension(inputFile)) {
                        removeEncExtension(inputFile, tempOutput);
                        strcpy(outputFile, tempOutput);
                    } else {
                        strcpy(outputFile, "decrypted.txt");
                    }
                    printf("Output will be: %s\n", outputFile);
                }
                
                shift = getValidShift();
                
                start = clock();
                decryptFile(inputFile, outputFile, shift);
                end = clock();
                
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;
                printf("\n✅ File decrypted successfully!\n");
                printf("⏱️  Time: %.4f seconds\n", time_spent);
                showFileStats(outputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 3: // Brute force decrypt
                printf("\n🔨 BRUTE FORCE DECRYPTION\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter encrypted filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                bruteForceDecrypt(inputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 4: // Frequency analysis
                printf("\n📊 FREQUENCY ANALYSIS\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter filename to analyze: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                frequencyAnalysis(inputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 5: // ROT13
                printf("\n🔄 ROT13 ENCRYPTION/DECRYPTION\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                printf("Enter output filename: ");
                fgets(outputFile, sizeof(outputFile), stdin);
                outputFile[strcspn(outputFile, "\n")] = 0;
                
                rot13File(inputFile, outputFile);
                printf("\n✅ ROT13 applied successfully!\n");
                showFileStats(outputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 6: // Batch encrypt
                batchEncrypt();
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 7: // Batch decrypt
                batchDecrypt();
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 8: // View file
                printf("\n👁️  VIEW FILE CONTENT\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter filename to view: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                displayFileContent(inputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 9: // File statistics
                printf("\n📈 FILE STATISTICS\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);
                inputFile[strcspn(inputFile, "\n")] = 0;
                
                showFileStats(inputFile);
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 10: // About Caesar Cipher
                printf("\n📚 ABOUT CAESAR CIPHER\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("\nThe Caesar Cipher is one of the simplest and oldest\n");
                printf("encryption techniques. It is a substitution cipher\n");
                printf("where each letter is shifted by a fixed number of\n");
                printf("positions in the alphabet.\n\n");
                printf("Example (shift = 3):\n");
                printf("  Plain:  A B C D E F G H I J K L M\n");
                printf("  Cipher: D E F G H I J K L M N O P\n\n");
                printf("  \"HELLO\" → \"KHOOR\"\n\n");
                printf("Named after Julius Caesar who used it to protect\n");
                printf("military messages.\n\n");
                printf("🔓 Weaknesses:\n");
                printf("  • Only 25 possible keys (easily brute-forced)\n");
                printf("  • Vulnerable to frequency analysis\n");
                printf("  • Not secure for modern use\n");
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            default:
                printf("\n❌ Invalid choice! Please select 1-11.\n");
                printf("Press Enter to continue...");
                getchar();
        }
    }
    
    return 0;
}

void displayMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║                                                    ║\n");
    printf("║      🔐 ENHANCED CAESAR CIPHER TOOL 🔐            ║\n");
    printf("║                                                    ║\n");
    printf("╚════════════════════════════════════════════════════╝\n\n");
    printf("  📝 BASIC OPERATIONS\n");
    printf("  1. 🔒 Encrypt a file\n");
    printf("  2. 🔓 Decrypt a file\n");
    printf("  3. 🔨 Brute force decryption (try all shifts)\n\n");
    printf("  🔬 ANALYSIS TOOLS\n");
    printf("  4. 📊 Frequency analysis\n");
    printf("  5. 🔄 ROT13 encryption/decryption\n\n");
    printf("  📦 BATCH OPERATIONS\n");
    printf("  6. 📂 Batch encrypt multiple files\n");
    printf("  7. 📂 Batch decrypt multiple files\n\n");
    printf("  🛠️  UTILITIES\n");
    printf("  8. 👁️  View file content\n");
    printf("  9. 📈 File statistics\n");
    printf("  10. 📚 About Caesar Cipher\n");
    printf("  11. 🚪 Exit\n\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
}

int getValidShift() {
    int shift;
    while (1) {
        printf("Enter shift value (1-25): ");
        if (scanf("%d", &shift) == 1 && shift >= 1 && shift <= 25) {
            getchar(); // Consume newline
            return shift;
        }
        while (getchar() != '\n'); // Clear input buffer
        printf("❌ Invalid! Enter a number between 1 and 25.\n");
    }
}

void encryptFile(const char* inputFile, const char* outputFile, int shift) {
    FILE *inFile = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "w");
    
    if (inFile == NULL) {
        printf("\n❌ Error: Cannot open input file '%s'\n", inputFile);
        return;
    }
    
    if (outFile == NULL) {
        printf("\n❌ Error: Cannot create output file '%s'\n", outputFile);
        fclose(inFile);
        return;
    }
    
    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
        fputc(encryptChar(ch, shift), outFile);
    }
    
    fclose(inFile);
    fclose(outFile);
}

void decryptFile(const char* inputFile, const char* outputFile, int shift) {
    FILE *inFile = fopen(inputFile, "r");
    FILE *outFile = fopen(outputFile, "w");
    
    if (inFile == NULL) {
        printf("\n❌ Error: Cannot open input file '%s'\n", inputFile);
        return;
    }
    
    if (outFile == NULL) {
        printf("\n❌ Error: Cannot create output file '%s'\n", outputFile);
        fclose(inFile);
        return;
    }
    
    char ch;
    while ((ch = fgetc(inFile)) != EOF) {
        fputc(decryptChar(ch, shift), outFile);
    }
    
    fclose(inFile);
    fclose(outFile);
}

void bruteForceDecrypt(const char* inputFile) {
    FILE *inFile = fopen(inputFile, "r");
    
    if (inFile == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", inputFile);
        return;
    }
    
    // Read file content
    char content[10000];
    int idx = 0;
    char ch;
    while ((ch = fgetc(inFile)) != EOF && idx < 9999) {
        content[idx++] = ch;
    }
    content[idx] = '\0';
    fclose(inFile);
    
    printf("\n🔨 Trying all 25 possible shifts:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n\n");
    
    for (int shift = 1; shift <= 25; shift++) {
        printf("Shift %2d: ", shift);
        
        // Show first 60 characters or until newline
        int charCount = 0;
        for (int i = 0; content[i] != '\0' && charCount < 60; i++) {
            char decrypted = decryptChar(content[i], shift);
            if (decrypted == '\n' || decrypted == '\r') {
                break;
            }
            putchar(decrypted);
            charCount++;
        }
        printf("\n");
    }
    
    printf("\n💡 Tip: Look for readable text to find the correct shift!\n");
}

void frequencyAnalysis(const char* inputFile) {
    FILE *file = fopen(inputFile, "r");
    
    if (file == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", inputFile);
        return;
    }
    
    int freq[26] = {0};
    int totalLetters = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            freq[toupper(ch) - 'A']++;
            totalLetters++;
        }
    }
    fclose(file);
    
    if (totalLetters == 0) {
        printf("\n⚠️  No alphabetic characters found in file.\n");
        return;
    }
    
    printf("\n📊 Letter Frequency Analysis:\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("Total letters: %d\n\n", totalLetters);
    
    // Find max frequency for scaling
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > maxFreq) maxFreq = freq[i];
    }
    
    // Display frequencies with bar chart
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            char letter = 'A' + i;
            float percentage = (float)freq[i] / totalLetters * 100;
            int barLength = (int)((float)freq[i] / maxFreq * 40);
            
            printf("%c: %4d (%5.2f%%) ", letter, freq[i], percentage);
            for (int j = 0; j < barLength; j++) {
                printf("█");
            }
            printf("\n");
        }
    }
    
    printf("\n💡 In English, common letters are: E, T, A, O, I, N\n");
}

void rot13File(const char* inputFile, const char* outputFile) {
    encryptFile(inputFile, outputFile, 13);
}

void batchEncrypt() {
    printf("\n📂 BATCH ENCRYPT FILES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int numFiles;
    printf("How many files to encrypt? ");
    if (scanf("%d", &numFiles) != 1 || numFiles < 1 || numFiles > MAX_FILES) {
        printf("❌ Invalid number of files.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();
    
    int shift = getValidShift();
    
    char files[MAX_FILES][256];
    for (int i = 0; i < numFiles; i++) {
        printf("Enter filename %d: ", i + 1);
        fgets(files[i], sizeof(files[i]), stdin);
        files[i][strcspn(files[i], "\n")] = 0;
    }
    
    printf("\n🔄 Processing files...\n");
    int successCount = 0;
    
    for (int i = 0; i < numFiles; i++) {
        char outFile[300];
        addEncExtension(files[i], outFile);
        
        FILE *test = fopen(files[i], "r");
        if (test != NULL) {
            fclose(test);
            encryptFile(files[i], outFile, shift);
            printf("✅ %s → %s\n", files[i], outFile);
            successCount++;
        } else {
            printf("❌ %s (file not found)\n", files[i]);
        }
    }
    
    printf("\n🎉 Batch encryption complete! %d/%d files processed.\n", successCount, numFiles);
}

void batchDecrypt() {
    printf("\n📂 BATCH DECRYPT FILES\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    int numFiles;
    printf("How many files to decrypt? ");
    if (scanf("%d", &numFiles) != 1 || numFiles < 1 || numFiles > MAX_FILES) {
        printf("❌ Invalid number of files.\n");
        while (getchar() != '\n');
        return;
    }
    getchar();
    
    int shift = getValidShift();
    
    char files[MAX_FILES][256];
    for (int i = 0; i < numFiles; i++) {
        printf("Enter filename %d: ", i + 1);
        fgets(files[i], sizeof(files[i]), stdin);
        files[i][strcspn(files[i], "\n")] = 0;
    }
    
    printf("\n🔄 Processing files...\n");
    int successCount = 0;
    
    for (int i = 0; i < numFiles; i++) {
        char outFile[300];
        if (hasEncExtension(files[i])) {
            removeEncExtension(files[i], outFile);
        } else {
            sprintf(outFile, "decrypted_%s", files[i]);
        }
        
        FILE *test = fopen(files[i], "r");
        if (test != NULL) {
            fclose(test);
            decryptFile(files[i], outFile, shift);
            printf("✅ %s → %s\n", files[i], outFile);
            successCount++;
        } else {
            printf("❌ %s (file not found)\n", files[i]);
        }
    }
    
    printf("\n🎉 Batch decryption complete! %d/%d files processed.\n", successCount, numFiles);
}

char encryptChar(char ch, int shift) {
    if (isupper(ch)) {
        return ((ch - 'A' + shift) % 26) + 'A';
    } else if (islower(ch)) {
        return ((ch - 'a' + shift) % 26) + 'a';
    } else if (isdigit(ch)) {
        // Encrypt digits 0-9 with wrapping
        return ((ch - '0' + shift) % 10) + '0';
    }
    return ch; // Non-alphanumeric characters remain unchanged
}

char decryptChar(char ch, int shift) {
    if (isupper(ch)) {
        return ((ch - 'A' - shift + 26) % 26) + 'A';
    } else if (islower(ch)) {
        return ((ch - 'a' - shift + 26) % 26) + 'a';
    } else if (isdigit(ch)) {
        // Decrypt digits 0-9 with wrapping (handle negative modulo)
        int val = (ch - '0' - shift) % 10;
        if (val < 0) val += 10;
        return val + '0';
    }
    return ch; // Non-alphanumeric characters remain unchanged
}

void displayFileContent(const char* filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", filename);
        return;
    }
    
    printf("\n📄 Content of '%s':\n", filename);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    
    char ch;
    int lineCount = 0;
    while ((ch = fgetc(file)) != EOF && lineCount < 50) {
        putchar(ch);
        if (ch == '\n') lineCount++;
    }
    
    if (ch != EOF) {
        printf("\n... (truncated, showing first 50 lines) ...\n");
    }
    
    printf("\n━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    fclose(file);
}

void showFileStats(const char* filename) {
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", filename);
        return;
    }
    
    long fileSize = getFileSize(filename);
    int charCount = 0, letterCount = 0, numberCount = 0, lineCount = 0;
    char ch;
    
    while ((ch = fgetc(file)) != EOF) {
        charCount++;
        if (isalpha(ch)) letterCount++;
        if (isdigit(ch)) numberCount++;
        if (ch == '\n') lineCount++;
    }
    fclose(file);
    
    printf("\n📈 File Statistics for '%s':\n", filename);
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
    printf("📏 File size:      %ld bytes\n", fileSize);
    printf("📝 Total chars:    %d\n", charCount);
    printf("🔤 Letters:        %d\n", letterCount);
    printf("🔢 Numbers:        %d\n", numberCount);
    printf("📄 Lines:          %d\n", lineCount);
}

long getFileSize(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return 0;
}

char* addEncExtension(const char* filename, char* output) {
    strcpy(output, filename);
    strcat(output, ".enc");
    return output;
}

char* removeEncExtension(const char* filename, char* output) {
    strcpy(output, filename);
    char *ext = strstr(output, ".enc");
    if (ext != NULL) {
        *ext = '\0';
    }
    return output;
}

int hasEncExtension(const char* filename) {
    return strstr(filename, ".enc") != NULL;
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
