
#include <system.h>
#include <monitor.h>
#include <log.h>
#include <gdt.h>
#include <interrupts.h>
#include <driver.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>

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
	Log::success("Loaded GDT Module");
	
	Log::success("Loaded Port Module");

	DriverManager driverManager;

	InterruptManager interrupts(0x20, &gdt);
	Log::success("Loaded InterruptManager Module");

	PrintfKeyboardEventHandler keyboardHandler;
	Keyboard keyboard(&interrupts, &keyboardHandler);
	Log::success("Loaded Keyboard Driver");

	MouseToConsoleEventHandler mouseHandler;
	Mouse mouse(&interrupts, &mouseHandler);
	Log::success("Loaded Mouse Driver");

	driverManager.Add(&keyboard);
	driverManager.Add(&mouse);
	driverManager.EnableAll();

	interrupts.Enable();
	Log::success("Interrupts Enabled\n");

	Log::info("Kernel Ready\n");


	while(1){
		
	}
}
