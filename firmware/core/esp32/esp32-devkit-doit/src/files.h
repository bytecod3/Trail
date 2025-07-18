
/**
 * @file files.h
 * @author Edwin Mwiti (emwiti658@gmail.com)
 * @brief This file declares file-system operation functions
 * @version 0.1
 * @date 2025-07-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef FILES_H
#define FILES_H

#include <FS.h>
#include <LittleFS.h>

#define FORMAT_LITTLEFS_IF_FAILED true      /*!< If LittleFS is not formatted, format it */

extern const char* wificonfig_folder_path;      /*!< to hold the WIFI config files */
extern const char* config_file_path;            /*!< stores configurations settings for WIFI */
extern const char* saved_networks_file_path;    /*!< holds teh saved WIFI networks SSIDs and passwords */

extern char file_data_buffer[256];

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void createDir(fs::FS &fs, const char *path);
void removeDir(fs::FS &fs, const char *path);
void readFile(fs::FS &fs, const char *path);
void writeFile(fs::FS &fs, const char *path, const char *message);
void appendFile(fs::FS &fs, const char *path, const char *message);
void renameFile(fs::FS &fs, const char *path1, const char *path2);
void deleteFile(fs::FS &fs, const char *path);
void writeFile2(fs::FS &fs, const char *path, const char *message);
void deleteFile2(fs::FS &fs, const char *path);
void testFileIO(fs::FS &fs, const char *path);

#endif