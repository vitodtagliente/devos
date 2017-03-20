
#ifndef __GDT_H_
#define __GDT_H_

class GlobalDescriptorTable
{
    public:

        class SegmentDescriptor
        {
            private:
                unsigned short limit_lo;
                unsigned short base_lo;
                unsigned char base_hi;
                unsigned char type;
                unsigned char limit_hi;
                unsigned char base_vhi;

            public:
                SegmentDescriptor(unsigned int base, unsigned int limit, unsigned char type);
                unsigned int Base();
                unsigned int Limit();
        } __attribute__((packed));

    private:
        SegmentDescriptor nullSegmentSelector;
        SegmentDescriptor unusedSegmentSelector;
        SegmentDescriptor codeSegmentSelector;
        SegmentDescriptor dataSegmentSelector;

    public:

        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

        unsigned short CodeSegmentSelector();
        unsigned short DataSegmentSelector();
};

#endif