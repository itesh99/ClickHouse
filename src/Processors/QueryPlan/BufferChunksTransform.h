#pragma once
#include <Processors/IProcessor.h>
#include <queue>

namespace DB
{

class BufferChunksTransform : public IProcessor
{
public:
    BufferChunksTransform(const Block & header_, size_t max_rows_to_buffer_, size_t limit_);

    Status prepare() override;
    String getName() const override { return "BufferChunks"; }

private:
    Chunk pullChunk();

    InputPort & input;
    OutputPort & output;

    size_t max_rows_to_buffer;
    size_t limit;

    std::queue<Chunk> chunks;
    size_t num_buffered_rows = 0;
    size_t num_processed_rows = 0;
};

}
