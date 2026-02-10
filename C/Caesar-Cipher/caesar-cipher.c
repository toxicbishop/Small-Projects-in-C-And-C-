/* 
Before you Start Reading this comment.
I have added So many comments to this code to make it more understandable for You Guys.
Priortizing learning new Libraries for newbiews.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>//Charecter type isalpha or isdigit.
#include <time.h>//Time functions.
#include <sys/stat.h>//Sys Level library for file operations.

#define MAX_BUFFER 1024
#define MAX_FILES 100

// Function prototypes
void encryptFile(const char* inputFile, const char* outputFile, int shift);
void decryptFile(const char* inputFile, const char* outputFile, int shift);
void bruteForceDecrypt(const char* inputFile);
void frequencyAnalysis(const char* inputFile);
void rot13File(const char* inputFile, const char* outputFile);//ROT113 Means shifting the words exactly 13 places
void batchEncrypt();// encrypts multiple data items, files, or messages simultaneously using a single operation  
void batchDecrypt();//decrypts multiple data items, files, or messages simultaneously using a single operation
char encryptChar(char ch, int shift);//encrypts a single character
char decryptChar(char ch, int shift);//decrypts a single character
void displayMenu();//displays the menu
void clearScreen();//clears the screen
int getValidShift();//gets a valid shift value
void displayFileContent(const char* filename);//displays the content of a file
void showFileStats(const char* filename);//shows the statistics of a file
long getFileSize(const char* filename);//gets the size of a file
char* addEncExtension(const char* filename, char* output);//adds .enc extension to a filename
char* removeEncExtension(const char* filename, char* output);//removes .enc extension from a filename
int hasEncExtension(const char* filename);//checks if a filename has .enc extension

int main() {//main start
    int choice;
    char inputFile[256];//Input file name.
    char outputFile[256];//Output file name.
    char tempOutput[300];//Temporary output file name.
    int shift;
    
    while (1) {//Loop until the user chooses to exit.
        clearScreen();//Clears the screen.
        displayMenu();//Displays the menu.
        
        printf("Enter your choice (1-11): ");
        if (scanf("%d", &choice) != 1) { //Checks if the input is a valid integer.
            while (getchar() != '\n');   // Clear input buffer
            printf("\n❌ Invalid input! Press Enter to continue...");
            getchar();//Waits for the user to press Enter.
            continue;
        }
        getchar();// Consume newline
        
        if (choice == 11) {//Checks if the user wants to exit.
            printf("\n👋 Thank you for using Enhanced Caesar Cipher! Goodbye!\n");
            break;
        }
        
        switch (choice) {//Checks the choice of the user.
            case 1: // Encrypt file
                printf("\n🔒 ENCRYPT FILE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);//Reads the input filename.
                inputFile[strcspn(inputFile, "\n")] = 0;//Removes the newline character from the input filename.
                
                printf("Enter output filename (or press Enter for auto): ");
                fgets(outputFile, sizeof(outputFile), stdin);//Reads the output filename.
                outputFile[strcspn(outputFile, "\n")] = 0;//Removes the newline character from the output filename.
                
                if (strlen(outputFile) == 0) {//Checks if the output filename is empty.
                    addEncExtension(inputFile, tempOutput);//Adds .enc extension to the output filename.
                    strcpy(outputFile, tempOutput);//Copies the output filename to the output file.
                    printf("Output will be: %s\n", outputFile);//Prints the output filename.
                }
                
                shift = getValidShift();//Gets a valid shift value.
                
                clock_t start = clock();//Starts the timer.
                encryptFile(inputFile, outputFile, shift);//Encrypts the file.
                clock_t end = clock();//Stops the timer.
                
                double time_spent = (double)(end - start) / CLOCKS_PER_SEC;//Calculates the time spent.
                printf("\n✅ File encrypted successfully!\n");
                printf("⏱️  Time: %.4f seconds\n", time_spent);
                showFileStats(outputFile);//Shows the statistics of the file.
                printf("\nPress Enter to continue...");
                getchar();
                break;
                
            case 2: // Decrypt file
                printf("\n🔓 DECRYPT FILE\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);//Reads the input filename.
                inputFile[strcspn(inputFile, "\n")] = 0;//Removes the newline character from the input filename.
                
                printf("Enter output filename (or press Enter for auto): ");
                fgets(outputFile, sizeof(outputFile), stdin);//Reads the output filename.
                outputFile[strcspn(outputFile, "\n")] = 0;//Removes the newline character from the output filename.
                
                if (strlen(outputFile) == 0) {//Checks if the output filename is empty.
                    if (hasEncExtension(inputFile)) {//Checks if the input filename has .enc extension.
                        removeEncExtension(inputFile, tempOutput);//Removes .enc extension from the input filename.
                        strcpy(outputFile, tempOutput);//Copies the output filename to the output file.
                    } else {
                        strcpy(outputFile, "decrypted.txt");
                    }
                    printf("Output will be: %s\n", outputFile);
                }
                
                shift = getValidShift();
                
                start = clock();//Starts the timer.
                decryptFile(inputFile, outputFile, shift);//Decrypts the file.
                end = clock();//Stops the timer.
                
                time_spent = (double)(end - start) / CLOCKS_PER_SEC;//Calculates the time spent.
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
                fgets(inputFile, sizeof(inputFile), stdin);//Reads the input filename.
                inputFile[strcspn(inputFile, "\n")] = 0;//Removes the newline character from the input filename.
                
                bruteForceDecrypt(inputFile);//Performs brute force decryption.
                printf("\nPress Enter to continue...");
                getchar();//Waits for the user to press Enter.
                break;
                
            case 4: // Frequency analysis
                printf("\n📊 FREQUENCY ANALYSIS\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter filename to analyze: ");
                fgets(inputFile, sizeof(inputFile), stdin);//Reads the input filename.
                inputFile[strcspn(inputFile, "\n")] = 0;//Removes the newline character from the input filename.
                
                frequencyAnalysis(inputFile);//Performs frequency analysis.
                printf("\nPress Enter to continue...");
                getchar();//Waits for the user to press Enter.
                break;
                
            case 5: // ROT13
                printf("\n🔄 ROT13 ENCRYPTION/DECRYPTION\n");
                printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━\n");
                printf("Enter input filename: ");
                fgets(inputFile, sizeof(inputFile), stdin);//Reads the input filename.
                inputFile[strcspn(inputFile, "\n")] = 0;//Removes the newline character from the input filename.
                
                printf("Enter output filename: ");
                fgets(outputFile, sizeof(outputFile), stdin);//Reads the output filename.
                outputFile[strcspn(outputFile, "\n")] = 0;//Removes the newline character from the output filename.
                
                rot13File(inputFile, outputFile);//Applies ROT13 to the file.
                printf("\n✅ ROT13 applied successfully!\n");
                showFileStats(outputFile);//Shows the statistics of the file.
                printf("\nPress Enter to continue...");
                getchar();//Waits for the user to press Enter.
                break;
                
            case 6: // Batch encrypt
                batchEncrypt();//Performs batch encryption.
                printf("\nPress Enter to continue...");
                getchar();//Waits for the user to press Enter.
                break;
                
            case 7: // Batch decrypt
                batchDecrypt();//Performs batch decryption.
                printf("\nPress Enter to continue...");
                getchar();//Waits for the user to press Enter.
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
}//main end

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

// Function to get a valid shift value from the user (1-25)
int getValidShift() {
    int shift;
    while (1) { // Loop until valid input is received
        printf("Enter shift value (1-25): ");
        if (scanf("%d", &shift) == 1 && shift >= 1 && shift <= 25) {
            getchar(); // Consume newline character left in buffer
            return shift;
        }
        while (getchar() != '\n'); // Clear invalid input from buffer
        printf("❌ Invalid! Enter a number between 1 and 25.\n");
    }
}

// Encrypts the source file and writes to the destination file
void encryptFile(const char* inputFile, const char* outputFile, int shift) {
    FILE *inFile = fopen(inputFile, "r"); // Open source file for reading
    FILE *outFile = fopen(outputFile, "w"); // Open/Create destination file for writing
    
    // Check if input file exists
    if (inFile == NULL) {
        printf("\n❌ Error: Cannot open input file '%s'\n", inputFile);
        return;
    }
    
    // Check if output file can be created
    if (outFile == NULL) {
        printf("\n❌ Error: Cannot create output file '%s'\n", outputFile);
        fclose(inFile); // Close input file before returning
        return;
    }
    
    char ch;
    // Read character by character until End Of File (EOF)
    while ((ch = fgetc(inFile)) != EOF) {
        fputc(encryptChar(ch, shift), outFile); // Encrypt and write to output
    }
    
    // Close both files to save changes and free resources
    fclose(inFile);
    fclose(outFile);
}

// Decrypts the source file and writes to the destination file
// This is essentially the reverse of encryptFile
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
        fputc(decryptChar(ch, shift), outFile); // Decrypt and write to output
    }
    
    fclose(inFile);
    fclose(outFile);
}

// Tries all 25 possible shifts to help the user guess the correct key
void bruteForceDecrypt(const char* inputFile) {
    FILE *inFile = fopen(inputFile, "r");
    
    if (inFile == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", inputFile);
        return;
    }
    
    // Read file content into a buffer (limit to 10k chars for safety)
    char content[10000];
    int idx = 0;
    char ch;
    while ((ch = fgetc(inFile)) != EOF && idx < 9999) {
        content[idx++] = ch;
    }
    content[idx] = '\0'; // Null-terminate string
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

// Analyzes letter frequency to help break the cipher
// English language has specific letter frequency (E is most common)
void frequencyAnalysis(const char* inputFile) {
    FILE *file = fopen(inputFile, "r");
    
    if (file == NULL) {
        printf("\n❌ Error: Cannot open file '%s'\n", inputFile);
        return;
    }
    
    int freq[26] = {0}; // Array to store count of each letter A-Z
    int totalLetters = 0;
    char ch;
    
    // Read file and count letters
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            freq[toupper(ch) - 'A']++; // Map 'A' -> 0, 'B' -> 1, etc.
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

// ROT13 is a special case of Caesar Cipher with shift 13
// It is its own inverse (encrypting twice gives original text)
void rot13File(const char* inputFile, const char* outputFile) {
    encryptFile(inputFile, outputFile, 13);
}

// Encrypts multiple files in one go
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
    
    // Array to store multiple filenames
    char files[MAX_FILES][256];
    for (int i = 0; i < numFiles; i++) {
        printf("Enter filename %d: ", i + 1);
        fgets(files[i], sizeof(files[i]), stdin);
        files[i][strcspn(files[i], "\n")] = 0; // Remove newline
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

// Decrypts multiple files in one go
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
        files[i][strcspn(files[i], "\n")] = 0; // Remove newline
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

// Core Encryption Logic: Shifts a single character forward
char encryptChar(char ch, int shift) {
    if (isupper(ch)) {
        // Encryption formula: (char - 'A' + shift) % 26 + 'A'
        return ((ch - 'A' + shift) % 26) + 'A';
    } else if (islower(ch)) {
        // Same formula for lowercase letters
        return ((ch - 'a' + shift) % 26) + 'a';
    } else if (isdigit(ch)) {
        // Encrypt digits 0-9 with wrapping modulo 10
        return ((ch - '0' + shift) % 10) + '0';
    }
    return ch; // Return non-alphanumeric characters unchanged (e.g., punctuation)
}

// Core Decryption Logic: Shifts a single character backward
char decryptChar(char ch, int shift) {
    if (isupper(ch)) {
        // Decryption formula: (char - 'A' - shift + 26) % 26 + 'A'
        // Adding 26 handles negative results from subtraction
        return ((ch - 'A' - shift + 26) % 26) + 'A';
    } else if (islower(ch)) {
        return ((ch - 'a' - shift + 26) % 26) + 'a';
    } else if (isdigit(ch)) {
        // Decrypt digits 0-9 with wrapping
        int val = (ch - '0' - shift) % 10;
        if (val < 0) val += 10; // Handle negative modulo result
        return val + '0';
    }
    return ch; // Non-alphanumeric characters remain unchanged
}

// Displays the first 50 lines of a file
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

// Shows detailed statistics about a file (size, char count, etc.)
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

// Helper: Returns file size in bytes using stat()
long getFileSize(const char* filename) {
    struct stat st;
    if (stat(filename, &st) == 0) {
        return st.st_size;
    }
    return 0;
}

// Adds .enc extension to filename
char* addEncExtension(const char* filename, char* output) {
    strcpy(output, filename);
    strcat(output, ".enc");
    return output;
}

// Removes .enc extension from filename
char* removeEncExtension(const char* filename, char* output) {
    strcpy(output, filename);
    char *ext = strstr(output, ".enc");
    if (ext != NULL) {
        *ext = '\0'; // Truncate string at .enc
    }
    return output;
}

// Checks if filename ends with .enc
int hasEncExtension(const char* filename) {
    return strstr(filename, ".enc") != NULL;
}

// Cross-platform screen clearer
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows command
    #else
        system("clear"); // Unix/Linux command
    #endif
}
