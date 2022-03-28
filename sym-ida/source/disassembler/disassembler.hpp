#pragma once

#include "../other/includes.hpp"

#define STATUS_SUCCESS TRUE
#define STATUS_ERROR FALSE

namespace Disassembler
{
	inline ZydisDecoder decoder{};
	inline ZydisFormatter formatter{};

	[[nodiscard]] NTSTATUS InitializeZydis();
  std::string GetObjectCode(void* functionAddress, std::size_t size, bool countBranches);
}