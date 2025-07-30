// Q1: FIFO Page Replacement in C
#include <stdio.h>
int main() {
    // Declare variables
    int pages[50], frames[10]; 
    // pages[] stores page reference string; frames[] stores memory frames
    int n, f, i, j, k, flag, pageFaults = 0;

    // Input number of pages in the reference string
    printf("Enter number of pages: ");
    scanf("%d", &n);

    // Input the page reference string
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    // Input number of available frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize all frames to -1 (indicating empty)
    for (i = 0; i < f; i++)
        frames[i] = -1;

    int pos = 0; // Tracks the position to insert the next page (FIFO queue)

    printf("\nPage\tFrames\n");

    // Loop over each page in the reference string
    for (i = 0; i < n; i++) {
        flag = 0; // Used to check if the current page is already in a frame

        // Check if the current page is already in one of the frames
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1; // Page is already in memory, no page fault
                break;
            }
        }

        // If page is not in any frame => page fault
        if (!flag) {
            frames[pos] = pages[i];           // Replace the page at the current position (FIFO)
            pos = (pos + 1) % f;              // Move to the next position in a circular manner
            pageFaults++;                     // Increase the page fault count

            // Print the current state of the frames
            printf("%d\t", pages[i]);
            for (k = 0; k < f; k++) {
                if (frames[k] != -1)
                    printf("%d ", frames[k]); // Print page number in frame
                else
                    printf("- ");             // Frame is still empty
            }
            printf("\n");
        }
        // If page is found in frame, we do nothing (no replacement)
    }

    // Print the total number of page faults
    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
