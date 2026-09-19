#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void xorEncrypt(char *data, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0; data[i] != '\0'; ++i) {
        data[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice[9];
    printf("Enter 'encrypt' or 'decrypt': ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0';
    
    if (strcmp(choice, "encrypt") == 0) {
        char message[256];
        char filename[256];
        char key[256];

        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save the encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        printf("Enter the key for encryption: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        if (strlen(key) == 0){
            perror("Key is empty; XOR encryption cannot be performed");
            return 0;
        } if (strlen(message) == 0){
            perror("Message is empty; XOR encryption cannot be performed");
            return 0;
        }

        xorEncrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);

    } else if (strcmp(choice, "decrypt") == 0) {
        char filename[256];
        char key[256];

        printf("Enter the filename containing the encrypted data: ");
        fgets(filename, sizeof(filename), stdin);
        filename[strcspn(filename, "\n")] = '\0';

        printf("Enter the key for decryption: ");
        fgets(key, sizeof(key), stdin);
        key[strcspn(key, "\n")] = '\0';

        FILE *file = fopen(filename, "r");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encryptedData = malloc(fileSize + 1);
        if (encryptedData == NULL) {
            perror("Error allocating memory for encrypted data");
            fclose(file);
            return 1;
        }

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        if (strlen(key) == 0){
            perror("Key is empty; XOR decryption cannot be performed");
            free(encryptedData);
            return 1;
        } if (strlen(encryptedData) == 0){
            perror("Message is empty; XOR decryption cannot be performed");
            free(encryptedData);
            return 1;
        if (strlen(key) == 0){
            perror("Key is empty; XOR decryption cannot be performed");
            free(encryptedData);
            return 1;
        } if (strlen(encryptedData) == 0){
            perror("Message is empty; XOR decryption cannot be performed");
            free(encryptedData);
            return 1;
        }
        }

        xorEncrypt(encryptedData, key);
        printf("Decrypted message: %s\n", encryptedData);

        free(encryptedData);
    } else {
        printf("Invalid choice. Please enter 'encrypt' or 'decrypt'.\n");
    }

    return 0;
}