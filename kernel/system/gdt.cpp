
#include <gdt.h>

GlobalDescriptorTable::GlobalDescriptorTable()
    : nullSegmentSelector(0, 0, 0),
        unusedSegmentSelector(0, 0, 0),
        codeSegmentSelector(0, 64*1024*1024, 0x9A),
        dataSegmentSelector(0, 64*1024*1024, 0x92)
{
    unsigned int i[2];
    i[1] = (unsigned int)this;
    i[0] = sizeof(GlobalDescriptorTable) << 16;
    asm volatile("lgdt (%0)": :"p" (((unsigned char *) i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

unsigned short GlobalDescriptorTable::DataSegmentSelector()
{
    return (unsigned char*)&dataSegmentSelector - (unsigned char*)this;
}

unsigned short GlobalDescriptorTable::CodeSegmentSelector()
{
    return (unsigned char*)&codeSegmentSelector - (unsigned char*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(unsigned int base, unsigned int limit, unsigned char type)
{
    unsigned char* target = (unsigned char*)this;

    if (limit <= 65536)
    {
        // 16-bit address space
        target[6] = 0x40;
    }
    else
    {
        // 32-bit address space
        // Now we have to squeeze the (32-bit) limit into 2.5 regiters (20-bit).
        // This is done by discarding the 12 least significant bits, but this
        // is only legal, if they are all ==1, so they are implicitly still there

        // so if the last bits aren't all 1, we have to set them to 1, but this
        // would increase the limit (cannot do that, because we might go beyond
        // the physical limit or get overlap with other segments) so we have to
        // compensate this by decreasing a higher bit (and might have up to
        // 4095 wasted bytes behind the used memory)

        if((limit & 0xFFF) != 0xFFF)
            limit = (limit >> 12)-1;
        else
            limit = limit >> 12;

        target[6] = 0xC0;
    }

    // Encode the limit
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;
    target[6] |= (limit >> 16) & 0xF;

    // Encode the base
    target[2] = base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    // Type
    target[5] = type;
}

unsigned int GlobalDescriptorTable::SegmentDescriptor::Base()
{
    unsigned char* target = (unsigned char*)this;

    unsigned int result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

unsigned int GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    unsigned char* target = (unsigned char*)this;

    unsigned int result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];

    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;

    return result;
}
