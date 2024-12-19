#include <stdio.h>
#include <string.h>

// Define maximum number of notes
#define MAX_NOTES 100
#define NOTE_LENGTH 100

typedef struct {
    int day;
    int month;
    char note[NOTE_LENGTH];
} Note;

Note notes[MAX_NOTES];
int noteCount = 0;

// Calculate the first day of the year
int getFirstDayOfTheYear(int year)
{
    int day = (year * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400) % 7;
    return day;
}

void addNote()
{
    if (noteCount >= MAX_NOTES)
    {
        printf("Note limit reached!\n");
        return;
    }

    int day, month;
    char note[NOTE_LENGTH];

    printf("Enter month (1-12): ");
    scanf("%d", &month);
    printf("Enter day: ");
    scanf("%d", &day);
    getchar(); // To consume the newline character left by scanf
    printf("Enter your note: ");
    fgets(note, NOTE_LENGTH, stdin);

    note[strcspn(note, "\n")] = '\0'; // Remove newline character

    notes[noteCount].day = day;
    notes[noteCount].month = month;
    strncpy(notes[noteCount].note, note, NOTE_LENGTH);
    noteCount++;

    printf("Note added successfully!\n");
}

void printNotesForMonth(int month)
{
    printf("\nNotes for %s:\n", month == 1 ? "January" :
                                 month == 2 ? "February" :
                                 month == 3 ? "March" :
                                 month == 4 ? "April" :
                                 month == 5 ? "May" :
                                 month == 6 ? "June" :
                                 month == 7 ? "July" :
                                 month == 8 ? "August" :
                                 month == 9 ? "September" :
                                 month == 10 ? "October" :
                                 month == 11 ? "November" :
                                               "December");
    int hasNotes = 0;
    for (int i = 0; i < noteCount; i++)
    {
        if (notes[i].month == month)
        {
            printf(" - Day %d: %s\n", notes[i].day, notes[i].note);
            hasNotes = 1;
        }
    }
    if (!hasNotes)
    {
        printf(" No notes for this month.\n");
    }
}

void searchNotes()
{
    int day, month;
    printf("\nEnter the month (1-12) to search: ");
    scanf("%d", &month);
    printf("Enter the day: ");
    scanf("%d", &day);

    int found = 0;
    printf("\nNotes for %d/%d:\n", day, month);
    for (int i = 0; i < noteCount; i++)
    {
        if (notes[i].month == month && notes[i].day == day)
        {
            printf(" - %s\n", notes[i].note);
            found = 1;
        }
    }
    if (!found)
    {
        printf(" No notes found for this date.\n");
    }
}

int main()
{
    char *months[] = { "January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"
                     };
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    int i, j, totalDays, weekDay = 0, spaceCounter = 0, year;

    // Get year input from the user
    printf("Enter year:\n");
    scanf("%d", &year);
    printf("\n********** Welcome to %d **********\n\n", year);

    // Check if it is a leap year
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    {
        daysInMonth[1] = 29; // February has 29 days in a leap year
    }

    // Get the first day of the year
    weekDay = getFirstDayOfTheYear(year);

    // Menu for adding notes and searching notes
    char choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add a note\n");
        printf("2. Search for notes\n");
        printf("3. View calendar\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            addNote();
            break;
        case '2':
            searchNotes();
            break;
        case '3':
            for (i = 0; i < 12; i++)
            {
                printf("\n\n  ------------ %s ------------\n\n", months[i]);
                printNotesForMonth(i + 1); // Display notes for the month
                printf("\n   Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

                // Print leading spaces for the first week
                for (spaceCounter = 1; spaceCounter <= weekDay; spaceCounter++)
                {
                    printf("     ");
                }

                totalDays = daysInMonth[i];

                // Print the days of the month
                for (j = 1; j <= totalDays; j++)
                {
                    printf("%5d", j);

                    // Move to the next line after Saturday
                    if (++weekDay > 6)
                    {
                        weekDay = 0;
                        printf("\n");
                    }
                }

                // Prepare the weekday for the next month
                if (weekDay != 0)
                {
                    printf("\n");
                }
            }
            break;
        case '4':
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != '4');

    return 0;
}
