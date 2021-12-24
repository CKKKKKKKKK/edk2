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
)
{
    EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *DevicePathFromText;
    EFI_DEVICE_PATH_UTILITIES_PROTOCOL *DevicePathUtilities;
    EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DevicePathToText;

    EFI_DEVICE_PATH_PROTOCOL *dev_node;
    EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;

    EFI_STATUS Status;
    void *image;


    Status = SystemTable->BootServices->OpenProtocol(
        ImageHandle, &gEfiLoadedImageProtocolGuid, 
        (void **)&LoadedImage, ImageHandle, NULL,
        EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR (Status)) {
        ASSERT (FALSE);
        return Status;
    }

    Status = SystemTable->BootServices->OpenProtocol(
        LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, 
        (void **)&DevicePath, ImageHandle,
        NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    if (EFI_ERROR (Status)) {
        ASSERT (FALSE);
        return Status;
    }

    SystemTable->BootServices->LocateProtocol(&gEfiDevicePathFromTextProtocolGuid, NULL, (void **)&DevicePathFromText);
    SystemTable->BootServices->LocateProtocol(&gEfiDevicePathUtilitiesProtocolGuid, NULL, (void **)&DevicePathUtilities);
    SystemTable->BootServices->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (void **)&DevicePathToText);
    
    dev_node = DevicePathFromText->ConvertTextToDeviceNode(ImageFileName);
    dev_path_merged = DevicePathUtilities->AppendDeviceNode(DevicePath, dev_node);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Image file path: ");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, DevicePathToText->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

    Status = SystemTable->BootServices->LoadImage(FALSE, ImageHandle, dev_path_merged, NULL, 0, &image);
    if (EFI_ERROR (Status)) {
        ASSERT (FALSE);
        return Status;
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Load image success\r\n");

    Status = SystemTable->BootServices->StartImage(image, NULL, NULL);
    if (EFI_ERROR (Status)) {
        ASSERT (FALSE);
        return Status;
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Start image success\r\n");

    SystemTable->BootServices->CloseProtocol(LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, ImageHandle, NULL);
    SystemTable->BootServices->CloseProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, ImageHandle, NULL);
    
    return EFI_SUCCESS;
}

// EFI_STATUS
// EFIAPI
// UefiMain (
//   IN EFI_HANDLE        ImageHandle,
//   IN EFI_SYSTEM_TABLE  *SystemTable
//   )
// {
    // EFI_LOADED_IMAGE_PROTOCOL *LoadedImage;
    // EFI_DEVICE_PATH_PROTOCOL *DevicePath;
    // EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL *DevicePathFromText;
    // EFI_DEVICE_PATH_UTILITIES_PROTOCOL *DevicePathUtilities;
    // EFI_DEVICE_PATH_TO_TEXT_PROTOCOL *DevicePathToText;

    // EFI_DEVICE_PATH_PROTOCOL *dev_node;
    // EFI_DEVICE_PATH_PROTOCOL *dev_path_merged;

    // EFI_STATUS Status;
    // void *image;


    // Status = SystemTable->BootServices->OpenProtocol(
    //     ImageHandle, &gEfiLoadedImageProtocolGuid, 
    //     (void **)&LoadedImage, ImageHandle, NULL,
    //     EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    // if (EFI_ERROR (Status)) {
    //     ASSERT (FALSE);
    //     return Status;
    // }

    // Status = SystemTable->BootServices->OpenProtocol(
    //     LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, 
    //     (void **)&DevicePath, ImageHandle,
    //     NULL, EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    // if (EFI_ERROR (Status)) {
    //     ASSERT (FALSE);
    //     return Status;
    // }

    // SystemTable->BootServices->LocateProtocol(&gEfiDevicePathFromTextProtocolGuid, NULL, (void **)&DevicePathFromText);
    // SystemTable->BootServices->LocateProtocol(&gEfiDevicePathUtilitiesProtocolGuid, NULL, (void **)&DevicePathUtilities);
    // SystemTable->BootServices->LocateProtocol(&gEfiDevicePathToTextProtocolGuid, NULL, (void **)&DevicePathToText);
    
    // CHAR16* ImageFileName = L"HelloWorld.efi";
    // dev_node = DevicePathFromText->ConvertTextToDeviceNode(ImageFileName);
    // dev_path_merged = DevicePathUtilities->AppendDeviceNode(DevicePath, dev_node);

    // SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Image file path: ");
    // SystemTable->ConOut->OutputString(SystemTable->ConOut, DevicePathToText->ConvertDevicePathToText(dev_path_merged, FALSE, FALSE));
    // SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\r\n");

    // Status = SystemTable->BootServices->LoadImage(FALSE, ImageHandle, dev_path_merged, NULL, 0, &image);
    // if (EFI_ERROR (Status)) {
    //     ASSERT (FALSE);
    //     return Status;
    // }
    // SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Load image success\r\n");

    // Status = SystemTable->BootServices->StartImage(image, NULL, NULL);
    // if (EFI_ERROR (Status)) {
    //     ASSERT (FALSE);
    //     return Status;
    // }
    // SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Start image success\r\n");

    // SystemTable->BootServices->CloseProtocol(LoadedImage->DeviceHandle, &gEfiDevicePathProtocolGuid, ImageHandle, NULL);
    // SystemTable->BootServices->CloseProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, ImageHandle, NULL);
    
    // return EFI_SUCCESS;
//     return StartImage(L"HelloWorld.efi", ImageHandle, SystemTable);
// }
