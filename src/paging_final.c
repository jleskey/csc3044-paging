/*
	Code developed by Dr. Robbeloth for CSC-3044

	History:
			3/4: search_physical_memory -- used char T/F for
				 found, change to use long w/ page frame index
				 where virtual page table entry was found

	Modified 3/2025 by Deborah Wilson

	NAME:
	DATE:
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define FALSE 0x0
#define TRUE 0x1

// Verbose display of output to diagnose problems
#define DEBUG_MODE FALSE

// Bit field for the counters
struct bit_entry
{
	unsigned bit : 1;
};

struct paging_entry
{

	// page table entries
	long page_frame_number;

	// is the page in the physical memory
	unsigned present_absent : 1;

	// rwx bits, not used
	unsigned protection : 3;

	// need to write page out to disk, not used
	unsigned modified : 1;

	// page referenced in last clock tick
	// should be cleared before next clock tick
	unsigned referenced : 1;

	// page maps onto register, not used
	unsigned caching_disabled : 1;

	// reserved for future use, not used
	unsigned reserved : 1;
};

// TODO: look at each page frame
// Return physical page frame where virtual page table entry is found;
// -1 is not found.
long search_physical_memory(long *physical_memory, long page_frame_size,
							long value)
{
	;
}

// TODO: complete this routine
// Change location physical_memory[index] with new value.
void modify_physical_memory(long *physical_memory, long index, long value)
{
	;
}

// TODO: complete this routine
// Look to see if a page frame has a zero in it
// What about page references to page table entry zero,
// could be a bug. You could just avoid using that entry
// in your file of page references
long find_free_page_frame(long *physical_memory, long page_frame_size)
{
	;
}

// TODO: complete this routine
// Simple look through each page table entry and print out
// the needed fields fields.
// Primarily a debugging aid so yo don't always have to jump
// into gdb.
void print_virtual_memory(struct paging_entry *pt, long virtual_mem_sz)
{
	;
}

// TODO complete this routine
// Primarily a debugging aid to look at physical memory contents
// without having to use gdb.
void print_physical_memory(long *phy_mem, long pg_frm_sz)
{
	;
}

// TODO: complete this routine
// Look at Figure 3-17 in the Tanenbaum text
// Look at how referenced bits from pages map into counter.
void update_counter(struct bit_entry *cnt, struct paging_entry *pt, long virt_mem_sz)
{
}

// TODO: complete this routine
// Hint: Use a count down loop to move left to right, like Figure 3-17.
void print_counter(struct bit_entry *cnt, long szCntr)
{
	;
}

// TODO: complete this routine
// Hint: You can use lcnts as a 2D array.
void update_local_counters(struct paging_entry *pt, struct bit_entry **lcnts, long virt_mem_sz)
{
	;
}

// TODO: complete this routine
// This is a tricky one to get right.
// Here you can put the bits into a value for comparison
// and use bit operations to help you.
// Return the page with the lowest counter.
long find_page_lowest_counter(struct paging_entry *pt, struct bit_entry **lcnts, long virt_mem_sz)
{
	;
}

int main(int argc, char *argv[])
{
	int errnum;
	long *page_references;
	size_t result;
	long num_page_references;
	long szCounter;
	long page_faults = 0;
	long page_hits = 0;
	long virt_mem_mult = 10;

	if (argc < 3)
	{
		printf("Usage: %s number_page_frames page_reference_file " +
				   "[virt_mem_multiplier = 10]\n",
			   argv[0]);
		exit(EXIT_FAILURE);
	}

	long page_frame_size = strtol(argv[1], NULL, 10);
	if (argc == 4)
	{
		virt_mem_mult = strtol(argv[3], NULL, 10);
	}
	long virtual_memory_size = page_frame_size * virt_mem_mult;

	// Set up current clock tick counter
	struct bit_entry *counter;
	struct bit_entry **local_counters;

	counter = (struct bit_entry *)malloc(sizeof(struct bit_entry) *
										 virtual_memory_size);
	szCounter = sizeof(counter);
	for (long i = 0; i < virtual_memory_size; i++)
	{
		counter[i].bit = 0;
	}

	local_counters = (struct bit_entry **)malloc(sizeof(struct bit_entry *) *
												 virtual_memory_size);

	for (long i = 0; i < virtual_memory_size; i++)
	{
		local_counters[i] = (struct bit_entry *)malloc(sizeof(struct
															  bit_entry) *
													   virtual_memory_size);

		for (long j = 0; j < virtual_memory_size; j++)
		{
			counter[j].bit = 0;
		}
	}

	// Create paging table for virtual memory
	struct paging_entry *paging_table;
	paging_table = (struct paging_entry *)malloc(sizeof(struct paging_entry) *
												 virtual_memory_size);

	// Create page frames
	long *physical_memory;
	physical_memory = (long *)malloc(sizeof(long) * page_frame_size);
	for (long i = 0; i < page_frame_size; i++)
	{
		physical_memory[i] = 0;
	}

	// Initialize the paging table for virtual memory
	for (long i = 0; i < virtual_memory_size; i++)
	{
		paging_table[i].page_frame_number = i % page_frame_size;
	}

	if (DEBUG_MODE)
		print_virtual_memory(paging_table, virtual_memory_size);

	// open page_reference file
	char *filename;
	filename = argv[2];
	int fd;
	fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		errnum = errno;
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		fprintf(stderr, "Error opening file %s\n", strerror(errnum));
		exit(EXIT_FAILURE);
	}

	/* Input file should only have longs in binary format,
	   read in metadata on file, including file size
	*/
	struct stat sb;
	if (stat(filename, &sb) != 0)
	{
		fprintf(stderr, "'stat' failed for '%s': %s.\n", filename,
				strerror(errno));
		exit(EXIT_FAILURE);
	}

	// Determine number of page references in input file
	num_page_references = sb.st_size / sizeof(long);
	page_references = (long *)malloc(sizeof(long) * num_page_references);

	// TODO: Read in the page references
	;

	/* TODO: Implement the aging algorithm.

	   Determine if ith entry is in physical memory.
	   If not add entry into physical memory.

	   Assume each page reference read to be a clock tick.
	*/
	for (int i = 0; i < num_page_references; i++)
	{

		/* General algorithm, feel free to use this as
		   a guide or develop your own, probably better process

		   1. Take page reference i
		   2. Look at table for page reference i
		   3. Mark it's reference field
		   4. if present is marked, should be in physical memory
		   5. If in physical memory page_hit++
		   6. If not in physical memory, find open spot
		   7. If open spot, record page reference in phy memory
		   8. If no open spot, find lowest counter
			  one local counter/ virtual page, page table entry
		   9. What if it's present bit is 0, find next lowest
			  find lowest should also check for a present bit
		   10. Now, remove that entry in physical memory and
			   replace with this page reference, update p/a bits
		   11. For #7 or #10, page_miss++
		   12. Update global counter
		   13. Update local counters
		   14. Clear reference bits for next clock

		*/
	}

	/* TODO: Print statistics on current execution.
	   Keep the data somewhere for plotting data:
	   page faults, page hits, ratio of page faults
	   per 1k page references ,other interesting data
	   for analysis.
	*/

	/* Cleanup -- A bonus point or two if you
	   find something not released or closed.
	*/
	free(paging_table);
	free(physical_memory);
	free(page_references);
	free(counter);
	free(local_counters);
	close(fd);

	// Normal exit
	return EXIT_SUCCESS;
}
