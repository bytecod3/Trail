
/**
 * @file files.h
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file implements filesystem operation functions
 * @version 0.1
 * @date 2025-07-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

const char* wificonfig_folder_path = "/wificonfig";
const char* config_file_path = "/wificonfig/config.ini";
const char* saved_networks_file_path = "/wificonfig/saved_networks.ini";

char file_data_buffer[256];

void listDir(fs::FS &fs, const char *dirname, uint8_t levels) {
    Serial.printf("Listing directory: %s\r\n", dirname);

    File root = fs.open(dirname);
    if (!root) {
        Serial.println("- failed to open directory");
        return;
    }
    if (!root.isDirectory()) {
        Serial.println(" - not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if (levels) {
                listDir(fs, file.path(), levels - 1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char *path) {
    Serial.printf("Creating Dir: %s\n", path);

    if (fs.mkdir(path)) {
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char *path) {
    Serial.printf("Removing Dir: %s\n", path);
    if (fs.rmdir(path)) {
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char *path) {
    Serial.printf("Reading file: %s\r\n", path);

    File file = fs.open(path);
    if (!file || file.isDirectory()) {
        Serial.println("- failed to open file for reading");
        return;
    }

    Serial.println("- read from file:");
    uint16_t byte_index = 0;
    while (file.available()) {
        //Serial.write(file.read());

        char c = file.read();
        file_data_buffer[byte_index] = c;

        byte_index++;
    }

    file.close();
}

void writeFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char *path, const char *message) {
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if (!file) {
        Serial.println("- failed to open file for appending");
        return;
    }
    if (file.print(message)) {
        Serial.println("- message appended");
    } else {
        Serial.println("- append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char *path1, const char *path2) {
    Serial.printf("Renaming file %s to %s\r\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("- file renamed");
    } else {
        Serial.println("- rename failed");
    }
}

void deleteFile(fs::FS &fs, const char *path) {
    Serial.printf("Deleting file: %s\r\n", path);
    if (fs.remove(path)) {
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }
}

// SPIFFS-like write and delete file, better use #define CONFIG_LITTLEFS_SPIFFS_COMPAT 1

void writeFile2(fs::FS &fs, const char *path, const char *message) {
    if (!fs.exists(path)) {
        if (strchr(path, '/')) {
            Serial.printf("Create missing folders of: %s\r\n", path);
            char *pathStr = strdup(path);
            if (pathStr) {
                char *ptr = strchr(pathStr, '/');
                while (ptr) {
                    *ptr = 0;
                    fs.mkdir(pathStr);
                    *ptr = '/';
                    ptr = strchr(ptr + 1, '/');
                }
            }
            free(pathStr);
        }
    }

    Serial.printf("Writing file to: %s\r\n", path);
    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return;
    }
    if (file.print(message)) {
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

void deleteFile2(fs::FS &fs, const char *path) {
    Serial.printf("Deleting file and empty folders on path: %s\r\n", path);

    if (fs.remove(path)) {
        Serial.println("- file deleted");
    } else {
        Serial.println("- delete failed");
    }

    char *pathStr = strdup(path);
    if (pathStr) {
        char *ptr = strrchr(pathStr, '/');
        if (ptr) {
            Serial.printf("Removing all empty folders on path: %s\r\n", path);
        }
        while (ptr) {
            *ptr = 0;
            fs.rmdir(pathStr);
            ptr = strrchr(pathStr, '/');
        }
        free(pathStr);
    }

}


void testFileIO(fs::FS &fs, const char *path) {
    Serial.printf("Testing file I/O with %s\r\n", path);

    static uint8_t buf[512];
    size_t len = 0;
    File file = fs.open(path, FILE_WRITE);
    if (!file) {
        Serial.println("- failed to open file for writing");
        return;
    }

    size_t i;
    Serial.print("- writing");
    uint32_t start = millis();
    for (i = 0; i < 2048; i++) {
        if ((i & 0x001F) == 0x001F) {
            Serial.print(".");
        }
        file.write(buf, 512);
    }
    Serial.println("");
    uint32_t end = millis() - start;
    Serial.printf(" - %u bytes written in %lu ms\r\n", 2048 * 512, end);
    file.close();

    file = fs.open(path);
    start = millis();
    end = start;
    i = 0;
    if (file && !file.isDirectory()) {
        len = file.size();
        size_t flen = len;
        start = millis();
        Serial.print("- reading");
        while (len) {
            size_t toRead = len;
            if (toRead > 512) {
                toRead = 512;
            }
            file.read(buf, toRead);
            if ((i++ & 0x001F) == 0x001F) {
                Serial.print(".");
            }
            len -= toRead;
        }
        Serial.println("");
        end = millis() - start;
        Serial.printf("- %u bytes read in %lu ms\r\n", flen, end);
        file.close();
    } else {
        Serial.println("- failed to open file for reading");
    }
}
