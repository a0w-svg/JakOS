#ifndef BPB_H
#define BPB_H

#include "../common/include/types.h"

typedef struct 
{
    uint8_t OEMname[8];
    uint16_t BytesPerSector;
    uint8_t SectorsPerCluster;
    uint16_t ReservedSectors;
    uint8_t NumberOfFats;
    uint16_t NumDirEntries;
    uint16_t NumSectors;
    uint8_t Media;
    uint16_t SectorsPerFat;
    uint16_t SectorsPerTrack;
    uint16_t HeadsPerCyl;
    uint32_t HuddenSectors;
    uint32_t LongSectors;
}BPB, *PBPB;

typedef struct 
{
    uint32_t SectorsPerFat32;
    uint16_t Flags;
    uint16_t Version;
    uint16_t RootCluster;
    uint16_t InfoCluster;
    uint16_t BackupBoot;
    uint16_t Reserved[6];
}BPB_EX, *PPB_EX;

typedef struct 
{
    uint8_t Ignore[3];
    BPB bpb;
    BPB_EX bpb_ex;
    uint8_t Filler[448];
}BootSector, *PBootSector;

#endif