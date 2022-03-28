#include "disassembler/disassembler.hpp"
#include "other/cmdargs.hpp"

int main(int argc, char* argv[])
{
  Arguments::ArgumentParser args("sym-ida");

  args.Add("--p", "--path")
    .Help("path to the library file(s)")
    .Required()
    .Action([](const std::string& value)
      {
        fs::path path{ value };

        std::cout << "path: " << path << '\n';
      });

  try 
  {
    args.Parse(argc, argv);
  }
  catch (const std::runtime_error& e)
  {
    std::cout << e.what() << '\n' << args;

    std::exit(0);
  }

	if (!Dissassembler::InitializeZydis())
	{
		std::cout << "[INFO]: Zydis failed to initialize!\n";

		std::exit(-1);
	}

	std::cout << "[INFO]: Zydis initialized!\n";

	return {};
}