#include "ICommand.h"
#include "../CommandBuffer.h"
#include "../Buffers/AbstractBuffer.h"

namespace Vulkan
{
    class CopyBufferCommand : public ICommand
    {
	public:
		CopyBufferCommand(CommandBuffer& buffer, const AbstractBuffer& srcBuffer, const AbstractBuffer &trgtBuffer);
		void execute() const override;
	private:
		const AbstractBuffer& srcBuffer;
		const AbstractBuffer &trgtBuffer;
		CommandBuffer& buffer;
    };
}
