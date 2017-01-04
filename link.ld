ENTRY(loader)

SECTIONS {
	. = 1M; /* Load code at 1MB */

	.text BLOCK(4K) : ALIGN (4K) /* Align at 4 KB */
	{
		*(.multiboot) 
		*(.text) /* All text sections from all files */
	}

	.note.gnu.build-id BLOCK(4K) : ALIGN(4K)
	{
		*(.note.gnu.build-id)
	}

	.rodata BLOCK(4K) : ALIGN (4K) /* Align at 4 KB */
	{
		*(.rodata*) /* All read-only data sections from all files */
	}

	.data BLOCK(4K) : ALIGN (4K) /* Align at 4 KB */
	{
		*(.data) /* All data sections from all files */
	}

	.bss BLOCK(4K) : ALIGN (4K) /* Align at 4 KB */
	{
		*(COMMON) /* All COMMON sections from all files */
		*(.bss) /* All bss sections from all files */
	}
	kernel_end_addr = .;
}
