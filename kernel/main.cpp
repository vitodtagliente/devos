
#include <system.h>
#include <drivers/monitor.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
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
	monitor.setColor(0xCC, 0x00);
	monitor.puts("\n");
	monitor.puts("---------------------------\n");
	monitor.puts("\n");
	monitor.puts("            VitoOS         \n");
	monitor.puts("\n");
	monitor.puts("---------------------------\n");
	monitor.setColor(0xFF, 0x00);
	monitor.puts("\n");
	monitor.puts("Welcome to my Operating System\n");

	GlobalDescriptorTable gdt;
	monitor.puts("Loaded GDT Module\n");
	
	monitor.puts("Loaded Port Module\n");

	DriverManager driverManager;

	InterruptManager interrupts(0x20, &gdt);
	monitor.puts("Loaded InterruptManager Module\n");

	PrintfKeyboardEventHandler keyboardHandler;
	Keyboard keyboard(&interrupts, &keyboardHandler);
	monitor.puts("Loaded Keyboard Driver\n");

	MouseToConsoleEventHandler mouseHandler;
	Mouse mouse(&interrupts, &mouseHandler);
	monitor.puts("Loaded Mouse Driver\n");

	driverManager.AddDriver(&keyboard);
	driverManager.AddDriver(&mouse);
	driverManager.EnableAll();

	interrupts.Enable();
	monitor.puts("Interrupts Enabled\n");

	monitor.puts("\n");
	monitor.setColor(0xD, 0x00);
	monitor.puts("Kernel Ready\n");

	while(1);
}
