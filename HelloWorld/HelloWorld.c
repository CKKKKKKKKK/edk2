#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/DebugLib.h>

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello world!\r\n");
    
    return EFI_SUCCESS;
}
