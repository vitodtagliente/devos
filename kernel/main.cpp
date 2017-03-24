
#include <system.h>
#include <monitor.h>
#include <gdt.h>
#include <interrupts.h>
#include <driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/vga.h>

#include <gui/desktop.h>
#include <gui/window.h>

class PrintfKeyboardEventHandler : public KeyboardEventHandler
{
	public:
		void OnKeyDown(char c)
		{
			Monitor::printf("keyDown\n");
		}
};


extern "C" void kernelMain(void* multiboot_structure, unsigned int magic_number /*multiboot_magic*/)
{	
	Monitor monitor;
	monitor.write("");
	monitor.setForeground(Monitor::light_cyan);
	monitor.writeLine("Welcome to my DevOS");
	monitor.writeLine("Dev4Fun Operating System");
	monitor.setForeground(Monitor::light_red);
	monitor.writeLine("");
	monitor.writeLine("@credits:");
	monitor.writeLine("  Vito Domenico Tagliente");
	monitor.writeLine("");
	monitor.setForeground(Monitor::white);

	GlobalDescriptorTable gdt;
	monitor.write("Loaded GDT Module\n");
	
	monitor.write("Loaded Port Module\n");

	DriverManager driverManager;

	InterruptManager interrupts(0x20, &gdt);
	monitor.write("Loaded InterruptManager Module\n");

	PrintfKeyboardEventHandler keyboardHandler;
	Keyboard keyboard(&interrupts, &keyboardHandler);
	monitor.write("Loaded Keyboard Driver\n");

	MouseToConsoleEventHandler mouseHandler;
	Mouse mouse(&interrupts, &mouseHandler);
	monitor.write("Loaded Mouse Driver\n");

	driverManager.Add(&keyboard);
	driverManager.Add(&mouse);
	driverManager.EnableAll();

	interrupts.Enable();
	monitor.write("Interrupts Enabled\n");

	monitor.write("\n");
	monitor.setForeground(Monitor::light_green);
	monitor.write("Kernel Ready\n");

	// Video Mode
	#ifdef VIDEOMODE
	VideoGraphicsArray vga;
	vga.SetMode(320, 200, 8);

	Desktop desktop(320, 200, 0x00, 0x00, 0xA8);
	Window win1(&desktop, 10, 10, 30, 30, 0xA8, 0x00, 0x00);
	Window win2(&desktop, 50, 10, 30, 30, 0x00, 0xA8, 0x00);
	desktop.AddChild(&win1);
	desktop.AddChild(&win2);
	#endif

	while(1){
		#ifdef VIDEOMODE
		desktop.Draw(&vga);
		#endif
	}
}
