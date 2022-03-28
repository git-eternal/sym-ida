#pragma once

#include "../other/includes.hpp"

#define STATUS_SUCCESS TRUE
#define STATUS_ERROR FALSE

namespace Dissassembler
{
	inline ZydisDecoder decoder{};
	inline ZydisFormatter formatter{};

	[[nodiscard]] NTSTATUS InitializeZydis();
}