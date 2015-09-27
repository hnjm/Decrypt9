#pragma once

#include "common.h"

#define MAX_ENTRIES 1024

typedef struct {
    u8   CTR[16];
    u32  size_mb;
    char filename[180];
} __attribute__((packed)) SdInfoEntry;

typedef struct {
    u32 n_entries;
    SdInfoEntry entries[MAX_ENTRIES];
} __attribute__((packed, aligned(16))) SdInfo;

typedef struct {
    u8   CTR[16];
    u8   keyY[16];
    u32  size_mb;
    u8   reserved[4];
    u32  usesSeedCrypto;
    u32  uses7xCrypto;
    u64  titleId;
    char filename[112];
} __attribute__((packed)) NcchInfoEntry;

typedef struct {
    u32 padding;
    u32 ncch_info_version;
    u32 n_entries;
    u8  reserved[4];
    NcchInfoEntry entries[MAX_ENTRIES];
} __attribute__((packed, aligned(16))) NcchInfo;

typedef struct {
    u64 titleId;
    u8 external_seed[16];
    u8 reserved[8];
} __attribute__((packed)) SeedInfoEntry;

typedef struct {
    u32 n_entries;
    u8 padding[12];
    SeedInfoEntry entries[MAX_ENTRIES];
} __attribute__((packed)) SeedInfo;

typedef struct {
    u32  keyslot;
    u32  setKeyY;
    u8   CTR[16];
    u8   keyY[16];
    u32  size;
    u32  mode;
    u8*  buffer;
} __attribute__((packed)) CryptBufferInfo;

typedef struct {
    u32  keyslot;
    u32  setKeyY;
    u8   CTR[16];
    u8   keyY[16];
    u32  size_mb;
    u32  mode;
    char filename[180];
} __attribute__((packed, aligned(16))) PadInfo;

typedef struct {
    u32 commonKeyIndex;
    u8  reserved[4];
    u8  titleId[8];
    u8  encryptedTitleKey[16];
} __attribute__((packed)) TitleKeyEntry;

typedef struct {
    u32 n_entries;
    u8  reserved[12];
    TitleKeyEntry entries[MAX_ENTRIES];
} __attribute__((packed, aligned(16))) EncKeysInfo;

typedef struct {
    char name[16];
    u8  magic[8];
    u32 offset;
    u32 size;
    u32 keyslot;
    u32 mode;
} __attribute__((packed)) PartitionInfo;

u32 CryptBuffer(CryptBufferInfo *info);
u32 DecryptTitlekey(TitleKeyEntry* entry);
u32 CreatePad(PadInfo *info);
u32 GetNandCtr(u8* ctr, u32 offset);
u32 SeekFileInNand(u32* offset, u32* size, u32* seekpos, const char* filename, PartitionInfo* partition);
u32 DecryptNandToMem(u8* buffer, u32 offset, u32 size, PartitionInfo* partition);
u32 DecryptNandToFile(const char* filename, u32 offset, u32 size, PartitionInfo* partition);
u32 DecryptNandPartition(PartitionInfo* p);

u32 EncryptMemToNand(u8* buffer, u32 offset, u32 size, PartitionInfo* partition);
u32 EncryptFileToNand(const char* filename, u32 offset, u32 size, PartitionInfo* partition);
u32 InjectNandPartition(PartitionInfo* p);
