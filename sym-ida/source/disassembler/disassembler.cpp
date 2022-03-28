#include "disassembler.hpp"

[[nodiscard]] NTSTATUS Disassembler::InitializeZydis()
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

std::string Disassembler::GetObjectCode(void* functionAddress, std::size_t size)
{
  ZydisDecodedInstruction instruction{}; ZyanUSize offset{ 0 };

  std::string opCodes{};

  // Iterate through the instruction stream, parsing each opcode
  //
  while (ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(
    &decoder, 
    reinterpret_cast<PBYTE>(functionAddress) + offset, 
    size - offset,
    &instruction)))
  {
    char buffer[256];

    ZydisFormatterFormatInstruction(&formatter,
      &instruction, buffer, sizeof(buffer), NULL);

    char opcode[3];
    sprintf_s(opcode, "%02x", instruction.opcode);

    opCodes.append(opcode);

    offset += instruction.length;
  }

  return opCodes.empty() ? "Error parsing code" : opCodes;
}
