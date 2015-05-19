/*****************************************************************************
* protocol.h
*
* This file implements the streaming download protocol
*
* Copyright (c) 2007-2015
* Qualcomm Technologies Incorporated.
* All Rights Reserved.
* Qualcomm Confidential and Proprietary
*
*****************************************************************************/
/*=============================================================================
Edit History

$Header: //source/qcom/qct/platform/uefi/workspaces/pweber/apps/8x26_emmcdl/emmcdl/main/latest/inc/protocol.h#4 $
$DateTime: 2015/05/07 21:41:17 $ $Author: pweber $

when       who     what, where, why
-------------------------------------------------------------------------------
12/09/15   pgw     Initial version.
=============================================================================*/
#pragma once

#include "partition.h"
#ifdef _WIN32
#include <windows.h>
#endif

#define MAX_XML_LEN         2048
#define MAX_TRANSFER_SIZE   0x100000

class Protocol {
public:
  //int ConnectToFlashProg(fh_configure_t *cfg);
  //int CreateGPP(uint32_t dwGPP1, uint32_t dwGPP2, uint32_t dwGPP3, uint32_t dwGPP4);
  //int SetActivePartition(int prtn_num);

  Protocol();
  ~Protocol();

  int DumpDiskContents(__uint64_t start_sector, __uint64_t num_sectors, char *szOutFile, UINT8 partNum, char *szPartName);
  int WipeDiskContents(__uint64_t start_sector, __uint64_t num_sectors, char *szPartName);

  int ReadGPT(bool debug);
  int WriteGPT(char *szPartName, char *szBinFile);
  void EnableVerbose(void);
  int GetDiskSectorSize(void);
  void SetDiskSectorSize(int size);
  __uint64_t GetNumDiskSectors(void);
  HANDLE GetDiskHandle(void);

  virtual int DeviceReset(void) = ERROR_SUCCESS;
  virtual int WriteData(unsigned char *writeBuffer, int64_t writeOffset, uint32_t writeBytes, uint32_t *bytesWritten, UINT8 partNum) = ERROR_SUCCESS;
  virtual int ReadData(unsigned char *readBuffer, int64_t readOffset, uint32_t readBytes, uint32_t *bytesRead, UINT8 partNum) = ERROR_SUCCESS;
  virtual int FastCopy(HANDLE hRead, int64_t sectorRead, HANDLE hWrite, int64_t sectorWrite, __uint64_t sectors, UINT8 partNum) = ERROR_SUCCESS;
  virtual int ProgramRawCommand(char *key) = ERROR_SUCCESS;
  virtual int ProgramPatchEntry(PartitionEntry pe, char *key) = ERROR_SUCCESS;

protected:

  int LoadPartitionInfo(char *szPartName, PartitionEntry *pEntry);
  void Log(char *str, ...);
  void Log(char *str, ...);

  gpt_header_t gpt_hdr;
  gpt_entry_t *gpt_entries;
  __uint64_t disk_size;
  HANDLE hDisk;
  unsigned char *buffer1;
  unsigned char *buffer2;
  unsigned char *bufAlloc1;
  unsigned char *bufAlloc2;
  int DISK_SECTOR_SIZE;

private:

  bool bVerbose;


};
