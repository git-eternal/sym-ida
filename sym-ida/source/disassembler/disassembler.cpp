#include "disassembler.hpp"

[[nodiscard]] NTSTATUS Dissassembler::InitializeZydis()
{
#if defined (_WIN64)
  if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder,
    ZYDIS_MACHINE_MODE_LONG_64, 
    ZydisStackWidth::ZYDIS_STACK_WIDTH_64)))
  {
    std::cout << "[INFO]: Zydis decoder failed to initialize!\n";
    return STATUS_ERROR;
  }
#else
  if (!ZYAN_SUCCESS(ZydisDecoderInit(&decoder,
    ZYDIS_MACHINE_MODE_LONG_COMPAT_32,
    ZydisStackWidth::ZYDIS_STACK_WIDTH_32)))
  {
    std::cout << "[INFO]: Zydis decoder failed to initialize!\n";
    return STATUS_ERROR;
  }
#endif

  // Initialize our formatter
  //
  if (!ZYAN_SUCCESS(ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL)))
  {
    std::cout << "[INFO]: Zydis formatter failed to initialize!\n";
    return STATUS_ERROR;
  }
    
  return STATUS_SUCCESS;
}
