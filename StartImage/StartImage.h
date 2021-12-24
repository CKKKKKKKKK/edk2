#ifndef __START_IMAGE__
#define __START_IMAGE__

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathUtilities.h>


EFI_STATUS
EFIAPI
StartImage (
    IN CHAR16 *ImageFileName,
    IN EFI_HANDLE        ImageHandle,
    IN EFI_SYSTEM_TABLE  *SystemTable
);


#endif
