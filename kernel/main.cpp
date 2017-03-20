
#include <system.h>
#include <monitor.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <driver.h>
#include <gdt.h>
#include <interrupts.h>

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

	while(1);
}
