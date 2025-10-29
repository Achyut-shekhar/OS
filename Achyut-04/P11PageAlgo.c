#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
    int num_frames, num_references;

    /* Read number of frames */
    printf("Enter number of frames: ");
    if (scanf("%d", &num_frames) != 1 || num_frames <= 0)
    {
        fprintf(stderr, "Invalid number of frames. Must be positive integer.\n");
        return 1;
    }

    /* Read number of page references */
    printf("Enter number of page references: ");
    if (scanf("%d", &num_references) != 1 || num_references <= 0)
    {
        fprintf(stderr, "Invalid number of page references. Must be positive integer.\n");
        return 1;
    }

    /* Allocate memory for the reference sequence array */
    int *refs = (int *)malloc(num_references * sizeof(int));
    if (!refs)
    {
        fprintf(stderr, "Memory allocation failure.\n");
        return 1;
    }

    /* Read the page reference sequence */
    printf("Enter the page reference sequence (space separated): \n");
    for (int i = 0; i < num_references; ++i)
    {
        if (scanf("%d", &refs[i]) != 1)
        {
            fprintf(stderr, "Error reading reference sequence at element %d.\n", i + 1);
            free(refs);
            return 1;
        }
    }

    /* Allocate memory for the frames array */
    int *frames = (int *)malloc(num_frames * sizeof(int));
    if (!frames)
    {
        fprintf(stderr, "Memory allocation failure.\n");
        free(refs);
        return 1;
    }

    /* Frames array initialized to -1 (empty) */
    for (int i = 0; i < num_frames; ++i)
    {
        frames[i] = -1;
    }

    int page_faults = 0;
    int page_hits = 0;
    int next_to_replace = 0; /* FIFO pointer: index of oldest page */

    /* Simulation start output */
    printf("\nSimulation start (FIFO): \n");
    printf("Ref\tStatus\tFrames\n");
    printf("---\t------\t");
    for (int i = 0; i < num_frames; ++i)
    {
        printf("F%d ", i);
    }
    printf("\n");
    printf("---\t------\t");
    for (int i = 0; i < num_frames; ++i)
    {
        printf("---");
    }
    printf("\n");

    /* Main simulation loop */
    for (int i = 0; i < num_references; ++i)
    {
        int page = refs[i];
        int hit = 0;

        /* Check for hit */
        for (int j = 0; j < num_frames; ++j)
        {
            if (frames[j] == page)
            {
                hit = 1;
                break;
            }
        }

        if (hit)
        {
            page_hits++;
            printf("%d\tHit\t%d\t", page, page);
        }
        else
        {
            /* Page fault */
            page_faults++;
            int placed = 0;
            for (int j = 0; j < num_frames; ++j)
            {
                if (frames[j] == -1)
                {
                    frames[j] = page;
                    placed = 1;
                    break;
                }
            }

            if (!placed)
            {
                // Replace the oldest page (FIFO)
                frames[next_to_replace] = page;
                // Move the FIFO pointer to the next frame
                next_to_replace = (next_to_replace + 1) % num_frames;
            }

            printf("%d\tFault\t%d\t", page, page);
        }

        /* Print current frame contents */
        for (int j = 0; j < num_frames; ++j)
        {
            if (frames[j] == -1)
            {
                printf("- "); // Use '-' for empty frame
            }
            else
            {
                printf("%d ", frames[j]);
            }
        }
        printf("\n");
    }

    /* Print final results */
    printf("\nTotal references: %d\n", num_references);
    printf("Page faults: %d\n", page_faults);
    printf("Page hits: %d\n", page_hits);
    printf("Fault ratio: %.3f\n", (double)page_faults / (double)num_references);

    /* Clean up allocated memory */
    free(refs);
    free(frames);

    return 0;
}
