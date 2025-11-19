/*practical-11*/
#include <stdio.h>

int main()
{
  printf("NAME: ACHYUT SHEKHAR SINGH |SECTION: C | ROLL No.: 04\n");
  int frames[50], pages[100];
  int num_frames, num_pages;
  int page_faults = 0, page_hits = 0;
  int next_to_replace = 0;

  printf("Enter number of frames (positive number): ");
  if (scanf("%d", &num_frames) != 1 || num_frames <= 0)
  {
    printf("Invalid input! Number of frames must be a positive integer\n");
    return 1;
  }

  printf("Enter number of pages (positive integer): ");
  if (scanf("%d", &num_pages) != 1 || num_pages <= 0)
  {
    printf("Invalid input! Number of pages must be a positive integer\n");
    return 1;
  }

  printf("Enter the page reference sequence: ");
  for (int i = 0; i < num_pages; i++)
  {
    if (scanf("%d", &pages[i]) != 1)
    {
      printf("Invalid input! Page references must be integers\n");
      return 1;
    }
  }

  // Initialize frames
  for (int i = 0; i < num_frames; i++)
  {
    frames[i] = -1;
  }

  // Process page requests
  for (int i = 0; i < num_pages; i++)
  {
    int page = pages[i];
    int hit = 0;

    // Check if page is already in frame (HIT)
    for (int j = 0; j < num_frames; j++)
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
      printf("Page %d: HIT\tFrames: ", page);
    }
    else
    {
      // Replace page using FIFO
      frames[next_to_replace] = page;
      next_to_replace = (next_to_replace + 1) % num_frames;
      page_faults++;
      printf("Page %d: FAULT\tFrames: ", page);
    }

    // Print current frame contents
    for (int j = 0; j < num_frames; j++)
    {
      if (frames[j] == -1)
        printf("- ");
      else
        printf("%d ", frames[j]);
    }
    printf("\n");
  }

  float fault_ratio = (float)page_faults / num_pages;
  float hit_ratio = (float)page_hits / num_pages;

  printf("\nTotal Page Faults = %d", page_faults);
  printf("\nTotal Page Hits = %d", page_hits);
  printf("\nPage Fault Ratio = %.2f", fault_ratio);
  printf("\nPage Hit Ratio = %.2f\n", hit_ratio);

  return 0;
}