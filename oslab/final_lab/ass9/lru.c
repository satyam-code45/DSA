// Q3: LRU Page Replacement in C
#include <stdio.h>

// Function to find the Least Recently Used (LRU) frame based on time[]
int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];  // find the smallest time value
            pos = i;        // position of the least recently used page
        }
    }
    return pos;  // return position to replace
}

int main() {
    int n, f, i, j, pageFaults = 0;
    int time[10], counter = 0;     // time[] stores last used time for each frame
    int pages[100], frames[10];    // pages[] is the reference string, frames[] is memory

    // Input: Number of pages
    printf("Enter number of pages: ");
    scanf("%d", &n);

    // Input: Page reference string
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    // Input: Number of frames
    printf("Enter number of frames: ");
    scanf("%d", &f);

    // Initialize all frames and their times to -1 and 0
    for (i = 0; i < f; i++) {
        frames[i] = -1;  // frame is initially empty
        time[i] = 0;     // last used time
    }

    printf("\nPage\tFrames\n");

    // Iterate over each page in the reference string
    for (i = 0; i < n; i++) {
        int flag = 0;  // flag to check if page hit

        // Check if page is already present (page hit)
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;             // page hit
                time[j] = ++counter;  // update time of this frame
                break;
            }
        }

        // Page fault occurs
        if (!flag) {
            int pos = -1;

            // Look for an empty frame
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;  // use empty frame
                    break;
                }
            }

            // If no empty frame, find least recently used one
            if (pos == -1)
                pos = findLRU(time, f);

            // Replace page in frame and update its last used time
            frames[pos] = pages[i];
            time[pos] = ++counter;
            pageFaults++;

            // Display frame status
            printf("%d\t", pages[i]);
            for (j = 0; j < f; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);  // display valid page
                else
                    printf("- ");              // display empty frame
            }
            printf("\n");
        }
    }

    // Final result
    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
