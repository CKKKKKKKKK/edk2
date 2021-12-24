#include "StartImage.h"

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    return StartImage(L"HelloWorld.efi", ImageHandle, SystemTable);
}
