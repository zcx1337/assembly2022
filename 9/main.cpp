#include <iostream.h>
#include <stdio.h>

#include <conio.h>
#include <dos.h>
#include <bios.h>

void main()
{
    clrscr();
    cout << "press keys to get codes\npress space for end\n";
    char scan_code, asci_code, status;
    int adress;
    do
    {
        asm {            // load ds:si with 0x40:0x1A
            push ds      // save
            push si      
            push di
            mov ax, 0x40
            mov ds, ax      // segment
            mov si, 0x1A    // head
            mov di, 0x1C    // tail
        }
    wait_kbd:
        asm {
            mov ax, [si]    // wait for press
            cmp ax, [di]
            je wait_kbd

            mov si, [si]
        }
        adress = _SI;

        asm mov ax, [si]
        // now _AL and _AH contain scan code and ASCII code

        asm mov si, 0x17     // adress of first buffer (byte) of status of keyboard
        asm mov bx, [si]     // bx is both buffers (bytes)

        asm pop di      // recover
        asm pop si
        asm pop ds

        scan_code = _AH;
        asci_code = _AL;
        status = _BL;       // first buffer (byte) is about ctrl and shift

        printf("adress = %x scan code = %d ASCII = %d\n", adress, scan_code, asci_code);
        printf("status %x\n", status);
    } while(getch() != ' ');

    cout << "Press any key...\n";
    getch(); // fuck borland
}
