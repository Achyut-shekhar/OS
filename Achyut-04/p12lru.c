#include <stdio.h>
#include <limits.h>

int findLRU(int time[], int n)
{
  int minimum = time[0], pos = 0;
  for (int i = 1; i < n; i++)
  {
    if (time[i] < minimum)
    {
      minimum = time[i];
      pos = i;
    }
  }
  return pos;
}

int main()
{
  printf("\n\t\t\t\t\tNAME: ACHYUT SHEKHAR SINGH | SECTION: C (G1) | ROLL NUMBER: 04\n");
  int n, capacity;

  printf("Enter number of pages: ");
  scanf("%d", &n);

  int pages[n];
  printf("Enter the page reference string (space-separated): ");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &pages[i]);
  }

  printf("Enter frame capacity: ");
  scanf("%d", &capacity);

  int frames[capacity];
  int time[capacity];
  int counter = 0, pageFaults = 0, flag1, flag2, pos;

  for (int i = 0; i < capacity; i++)
  {
    frames[i] = -1; // initialize as empty
  }

  printf("\n--- LRU Page Replacement Simulation ---\n\n");

  for (int i = 0; i < n; i++)
  {
    flag1 = flag2 = 0;

    // Check if page is already in frame
    for (int j = 0; j < capacity; j++)
    {
      if (frames[j] == pages[i])
      {
        counter++;
        time[j] = counter;
        flag1 = flag2 = 1;
        printf("Step %d | Page: %d → No Page Fault (Already in Frame)\n", i + 1, pages[i]);
        break;
      }
    }

    // If page not found and empty slot available
    if (flag1 == 0)
    {
      for (int j = 0; j < capacity; j++)
      {
        if (frames[j] == -1)
        {
          counter++;
          pageFaults++;
          frames[j] = pages[i];
          time[j] = counter;
          flag2 = 1;
          printf("Step %d | Page: %d → Page Fault (Added)\n", i + 1, pages[i]);
          break;
        }
      }
    }

    // If frame is full → replace least recently used page
    if (flag2 == 0)
    {
      pos = findLRU(time, capacity);
      printf("Step %d | Page: %d → Page Fault (Replaced LRU Page: %d)\n", i + 1, pages[i], frames[pos]);
      counter++;
      pageFaults++;
      frames[pos] = pages[i];
      time[pos] = counter;
    }

    // Print current frame content
    printf("   Current Frames: ");
    for (int j = 0; j < capacity; j++)
    {
      if (frames[j] != -1)
        printf("%d ", frames[j]);
      else
        printf("- ");
    }
    printf("\n\n");
  }

  printf("--------------------------------------\n");
  printf("Total Page Faults = %d\n", pageFaults);
  return 0;
}