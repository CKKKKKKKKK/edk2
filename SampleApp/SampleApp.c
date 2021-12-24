/** @file
  This is a simple shell application

  Copyright (c) 2008, Intel Corporation                                                         
  All rights reserved. This program and the accompanying materials                          
  are licensed and made available under the terms and conditions of the BSD License         
  which accompanies this distribution.  The full text of the license may be found at        
  http://opensource.org/licenses/bsd-license.php                                            

  THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,                     
  WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.             

**/

// /**
//   as the real entry point for the application.

//   @param[in] ImageHandle    The firmware allocated handle for the EFI image.  
//   @param[in] SystemTable    A pointer to the EFI System Table.
  
//   @retval EFI_SUCCESS       The entry point is executed successfully.
//   @retval other             Some error occurs when executing this entry point.

// **/
// EFI_STATUS
// EFIAPI
// UefiMain (
//   IN EFI_HANDLE        ImageHandle,
//   IN EFI_SYSTEM_TABLE  *SystemTable
//   )
// {
//   return EFI_SUCCESS;
// }

// #include "efi.h"
// #include "common.h"
#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/DevicePathToText.h>


EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    unsigned long long Status;
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DevicePathToText;

    Status = SystemTable->BootServices->OpenProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void **)&LoadedImage, ImageHandle, NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR(Status)) {
      SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Open loaded image protocol error \r\n");
      return Status;
    }
    SystemTable->BootServices->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (void **)&DevicePathToText);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"lip->FilePath: ");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, DevicePathToText->ConvertDevicePathToText(LoadedImage->FilePath, FALSE, FALSE));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

    SystemTable->BootServices->CloseProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, ImageHandle, NULL);

    while (TRUE)
        ;

    return EFI_SUCCESS;
}