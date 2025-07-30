// Q5: LFU Page Replacement Algorithm in C
#include <stdio.h>

#define MAX 100  // Maximum number of pages

// Define a structure to hold page number and its frequency
typedef struct {
    int page;  // page number
    int freq;  // how many times the page was used
} PageFrame;

// Function to find the index of the Least Frequently Used (LFU) page
int findLFU(PageFrame frames[], int frameCount) {
    int minFreq = frames[0].freq;
    int pos = 0;

    // Loop to find the page with minimum frequency
    for (int i = 1; i < frameCount; i++) {
        if (frames[i].freq < minFreq) {
            minFreq = frames[i].freq;
            pos = i;
        }
    }
    return pos;  // Return position of LFU page
}

int main() {
    int pages[MAX], n, frameCount;

    // Input number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    // Input page reference string
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    // Input number of frames available
    printf("Enter number of frames: ");
    scanf("%d", &frameCount);

    PageFrame frames[frameCount];  // Array of page frames
    int pageFaults = 0;            // Counter for page faults
    int filled = 0;                // Number of frames currently filled

    // Initialize all frames as empty
    for (int i = 0; i < frameCount; i++) {
        frames[i].page = -1;  // -1 indicates empty frame
        frames[i].freq = 0;
    }

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame (Page Hit)
        for (int j = 0; j < frameCount; j++) {
            if (frames[j].page == page) {
                frames[j].freq++;  // Increase frequency count
                found = 1;
                break;
            }
        }

        // Page not found -> Page Fault
        if (!found) {
            if (filled < frameCount) {
                // If there's empty space in memory, insert page
                frames[filled].page = page;
                frames[filled].freq = 1;
                filled++;
            } else {
                // If all frames are full, replace LFU page
                int replacePos = findLFU(frames, frameCount);
                frames[replacePos].page = page;
                frames[replacePos].freq = 1;
            }
            pageFaults++;  // Increase page fault count
        }

        // Print current status of frames
        printf("Frame: ");
        for (int j = 0; j < frameCount; j++) {
            if (frames[j].page != -1)
                printf("%d ", frames[j].page);  // Print loaded pages
            else
                printf("- ");  // Print empty slots
        }
        printf("\n");
    }

    // Print total page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
