//Q4: Simulate Paging Technique in C
#include <stdio.h>

int main() {
    int memSize, frameSize, numPages, i;
    int pageTable[100];

    printf("Enter memory size (in bytes): ");
    scanf("%d", &memSize);

    printf("Enter frame size (in bytes): ");
    scanf("%d", &frameSize);

    numPages = memSize / frameSize;

    printf("Number of frames available: %d\n", numPages);

    // Create page table
    for (i = 0; i < numPages; i++) {
        printf("Enter frame number where page %d is stored: ", i);
        scanf("%d", &pageTable[i]);
    }

    int logicalAddr;
    printf("\nEnter a logical address (page number and offset):\n");
    int pageNum, offset;
    scanf("%d %d", &pageNum, &offset);

    if (pageNum >= numPages || offset >= frameSize) {
        printf("Invalid page number or offset!\n");
    } else {
        int frameNum = pageTable[pageNum];
        int physicalAddr = frameNum * frameSize + offset;
        printf("Physical Address: %d\n", physicalAddr);
    }

    return 0;
}
