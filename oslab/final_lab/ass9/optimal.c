//Q2: Optimal Page Replacement in C
#include <stdio.h>

int findOptimal(int pages[], int frames[], int n, int index, int f) {
    int farthest = index, result = -1;
    for (int i = 0; i < f; i++) {
        int j;
        for (j = index; j < n; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    result = i;
                }
                break;
            }
        }
        if (j == n)
            return i; // If a frame is never used again, replace it
    }

    return (result == -1) ? 0 : result;
}

int main() {
    int n, f, i, j, pageFaults = 0;
    int pages[100], frames[10];

    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter the page reference string:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
        frames[i] = -1;

    printf("\nPage\tFrames\n");

    for (i = 0; i < n; i++) {
        int flag = 0;

        // Check if page is already present
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        // Page fault
        if (!flag) {
            int replaced = -1;

            // Check for empty frame
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    frames[j] = pages[i];
                    replaced = j;
                    break;
                }
            }

            if (replaced == -1) {
                int index = findOptimal(pages, frames, n, i + 1, f);
                frames[index] = pages[i];
            }

            pageFaults++;

            // Print frame content
            printf("%d\t", pages[i]);
            for (j = 0; j < f; j++) {
                if (frames[j] != -1)
                    printf("%d ", frames[j]);
                else
                    printf("- ");
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults = %d\n", pageFaults);
    return 0;
}
