#include "tallocation_block.h"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count): _size(size), _count(count)
{
    _used_blocks = (char*)malloc(size * count);
    for (size_t i = 0; i < count; i++) {
        _free_blocks.Push(_used_blocks + i * size);
    }
    _free_count = count;
    std::cout << "Memory init" << "\n";
}

void* TAllocationBlock::allocate()
{
    void* result = nullptr;
    if (_free_count == 0) {
        std::cout << "No memory exception\n" << "\n";
        return result;
    }
    result = _free_blocks.Top();
    _free_blocks.Pop();
    --_free_count;
    std::cout << "Allocate " << (_count - _free_count) << "\n";
    return result;
}

void TAllocationBlock::deallocate(void* pointer)
{
    _free_blocks.Push(pointer);
    ++_free_count;
    std::cout << "Deallocated block\n";
}

bool TAllocationBlock::has_free_blocks()
{
    return _free_count > 0;
}

TAllocationBlock::~TAllocationBlock()
{
    free(_used_blocks);
}
