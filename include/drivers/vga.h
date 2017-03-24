#ifndef __VGA_H
#define __VGA_H

#include <port.h>
#include <driver.h>

class VideoGraphicsArray
{
    protected:
        Port8Bit miscPort;
        Port8Bit crtcIndexPort;
        Port8Bit crtcDataPort;
        Port8Bit sequencerIndexPort;
        Port8Bit sequencerDataPort;
        Port8Bit graphicsControllerIndexPort;
        Port8Bit graphicsControllerDataPort;
        Port8Bit attributeControllerIndexPort;
        Port8Bit attributeControllerReadPort;
        Port8Bit attributeControllerWritePort;
        Port8Bit attributeControllerResetPort;
        
        void WriteRegisters(unsigned char* registers);
        unsigned char* GetFrameBufferSegment();
        
        virtual unsigned char GetColorIndex(unsigned char r, unsigned char g, unsigned char b);
        
        
    public:
        VideoGraphicsArray();
        ~VideoGraphicsArray();
        
        virtual bool SupportsMode(unsigned int width, unsigned int height, unsigned int colordepth);
        virtual bool SetMode(unsigned int width, unsigned int height, unsigned int colordepth);
        virtual void PutPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b);
        virtual void PutPixel(int x, int y, unsigned char colorIndex);
        
        virtual void FillRectangle(unsigned int x, unsigned int y, unsigned int w, unsigned int h,   unsigned char r, unsigned char g, unsigned char b);

};

#endif