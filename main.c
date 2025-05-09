#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



char name[50], v[3][6];
int score, number, questions;

typedef struct lb
{
    char names[50];
    int scores;
};
struct lb l[101];

typedef struct question
{
    char s[500], a[3][100];
    int c;
};
struct question e[15], m[25], h[10];

void red() {
    printf("\033[0;31m");
}

void green() {
    printf("\033[0;32m");
}

void reset() {
    printf("\033[0m");
}

void header()
{
    printf("--------------\n");
    printf("1 - New game\n");
    printf("2 - Resume\n");
    printf("3 - See leaderboard\n");

    printf("0 - Exit\n");
    printf("--------------\n");
}

void store_leaderboard()
{
    FILE *file1 = fopen("leaderboard.txt", "r");
    if (file1 == NULL) {
        perror("Error opening file");
        exit(1);
    }

    fscanf(file1, "%d\n", &number);
    for (int i = 0; i < number; i++)
    {
        fgets(l[i].names, sizeof(l[i].names), file1);
        fscanf(file1, "%d\n", &l[i].scores);
    }

    fclose(file1);
}

void update_leaderboard(int n)
{
    FILE *file = fopen("leaderboard.txt", "w");

    for (int i=0; i<n-1; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (l[i].scores<l[j].scores)
            {
                struct lb temp;
                temp = l[i];
                l[i] = l[j];
                l[j] = temp;
            }
        }
    }

    fprintf(file, "%d\n", n);

    for (int i=0; i<n; i++)
    {
        fprintf(file, "%s\n", l[i].names);
        fprintf(file, "%d\n", l[i].scores);
    }

    store_leaderboard();
}

void remove_progress(){
    FILE *file = fopen("current.txt", "w");
    fprintf(file, "%s", "NULL");
    fclose(file);
}

void save_progress(int i) {
    FILE *file = fopen("current.txt", "w");

    fprintf(file, "%s\n", name);
    fprintf(file, "%d\n", score);
    fprintf(file, "%d\n", i);

    if (i <= 3)
    {
        for (int j = 0; j < i; j++)
        {
            fprintf(file, "%d\n", v[0][j]);
        }
    }
    else
    {
        if (i <= 8)
        {
            for (int j = 0; j < 3; j++)
            {
                fprintf(file, "%d\n", v[0][j]);
            }
            for (int j = 0; j < i-3; j++)
            {
                fprintf(file, "%d\n", v[1][j]);
            }
        }
        else
        {
            for (int j = 0; j < 3; j++)
            {
                fprintf(file, "%d\n", v[0][j]);
            }
            for (int j = 0; j < 5; j++)
            {
                fprintf(file, "%d\n", v[1][j]);
            }
            for (int j = 0; j < i-8; j++)
            {
                fprintf(file, "%d\n", v[2][j]);
            }
        }
    }

    fclose(file);
}

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Discard leftover characters
}

void new(int k) {
   char a, quit;
   int ok = 1, n, answer, r;

   remove_progress();

    if (k == 0)
    {
        score = 0;

        system("cls");
        do
        {
            printf("Enter your name:");
            fflush(stdout);
            clear_input_buffer();
            fgets(name, sizeof(name), stdin);
            if (strcmp(name, "NULL")==0)
                system("cls");
                printf("\nName unavailable, please choose another one.\n");
        }while (strcmp(name, "NULL")==0);
    }

   srand(time(NULL));

   for (int i=k; i<3; i++)
   {
        do
        {
            n = rand()%15;
            ok = 1;
            for (int j=0; j<i; j++)
            {
                if (v[0][j]==n)
                {
                    ok = 0;
                    break;
                }
            }
        }while(ok == 0);
        v[0][i] = n;

        system("cls");

        printf("\n%s\n", e[n].s);
        printf("\n(1)%s\n", e[n].a[0]);
        printf("(2)%s\n", e[n].a[1]);
        printf("(3)%s\nYour answer:", e[n].a[2]);
        scanf("%d", &answer);

        if (answer - 1 == e[n].c)
        {
            green();
            printf("\nCorrect!");
            reset();
            printf(" You got 1 point.");
            score += 1;
        }
        else
        {
            red();
            printf("\nWrong");
            reset();
            printf(" answer!");
        }

        save_progress(i+1);
        printf("\nDo you want to continue? (y/n) ");
        while (getchar() != '\n');
        scanf("%c", &quit);
        if (quit == 'n')
        {

            break;
        }
   }
    if (quit != 'n')
    {

        if (k>3)
            r = k;
        else
            r = 3;

        for (int i=r; i<8; i++)
       {
            do
            {
                n = rand()%25;
                ok = 1;
                for (int j=0; j<i-3; j++)
                {
                    if (v[1][j]==n)
                    {
                        ok = 0;
                        break;
                    }
                }
            }while(ok == 0);
            v[1][i-3] = n;

            system("cls");

            printf("\n%s\n", m[n].s);
            printf("\n(1)%s\n", m[n].a[0]);
            printf("(2)%s\n", m[n].a[1]);
            printf("(3)%s\nYour answer:", m[n].a[2]);
            scanf("%d", &answer);

            if (answer - 1 == m[n].c)
            {
                green();
            printf("\nCorrect!");
            reset();
            printf(" You got 2 points.");
                score += 2;
            }
            else
            {
                red();
                printf("\nWrong");
                reset();
                printf(" answer!");
            }

            save_progress(i+1);

            printf("\nDo you want to continue? (y/n) ");
            while (getchar() != '\n');
            scanf("%c", &quit);
            if (quit == 'n')
            {

                break;
            }
       }
        if (quit != 'n')
        {

            if (k > 8)
                r = k;
            else
                r = 8;

            for (int i=r; i<10; i++)
           {
                do
                {
                    n = rand()%10;
                    ok = 1;
                    for (int j=0; j<i-8; j++)
                    {
                        if (v[2][j]==n)
                        {
                            ok = 0;
                            break;
                        }
                    }
                }while(ok == 0);
                v[2][i-8] = n;

                system("cls");

                printf("\n%s\n", h[n].s);
                printf("\n(1)%s\n", h[n].a[0]);
                printf("(2)%s\n", h[n].a[1]);
                printf("(3)%s\nYour answer:", h[n].a[2]);
                scanf("%d", &answer);

                if (answer - 1 == h[n].c)
                {
                    green();
                printf("\nCorrect!");
                reset();
                printf(" You got 3 points.");
                    score += 3;
                }
                else
                {
                    red();
                    printf("\nWrong");
                    reset();
                    printf(" answer!");
                }

                save_progress(i+1);

                printf("\nDo you want to continue? (y/n) ");
                while (getchar() != '\n');
                scanf("%c", &quit);
                if (quit == 'n')
                {

                    break;
                }
           }
           system("cls");
           if (quit != 'n')
           {
               printf("Congratulations on finishing the game! You have got ");
               green();
               printf("%d", score);
               reset();
               printf(" points!");
               number++;
               l[number-1].scores = score;
               strcpy(l[number-1].names, name);
               update_leaderboard(number);
               remove_progress();
           }

        }

    }

   getchar();
   scanf("%c", &a );
}


void resume() {

    char a;
    FILE *file = fopen("current.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fgets(name, sizeof(name), file);
    if (strcmp(name, "NULL")==0)
    {
        printf("There is no saved game to be resumed.\nPress Enter to continue.");
    }
    else
    {
        fscanf(file, "%d\n", &score);
        fscanf(file, "%d\n", &questions);

        if (questions<3)
        {
            for (int i = 0; i<questions; i++)
                fscanf(file, "%d\n", &v[0][i]);
        }
        else
        {
            for (int i = 0; i<3; i++)
                fscanf(file, "%d\n", &v[0][i]);
            if (questions<8)
            {
                for (int i = 0; i<questions-3; i++)
                    fscanf(file, "%d\n", &v[1][i]);
            }
            else
            {
                for (int i = 0; i<5; i++)
                    fscanf(file, "%d\n", &v[1][i]);
                for (int i=0; i<questions-8; i++)
                    fscanf(file, "%d\n", &v[2][i]);
            }
        }

        new(questions);
    }
    fclose(file);

    getchar();
    scanf("%c", &a );
}


void leaderboard()
{
    char a;
    system("cls");
    if (number != 0)
    {
        printf("Leaderboard:\n");
        for (int i=0; i<number; i++)
        {
            printf("\n%d.%s ", i+1, l[i].names);
            green();
            printf("%d ", l[i].scores);
            reset();
            printf("points");
        }
    }
    else
        printf("The leaderboard is empty. Press Enter to continue.");
    getchar();
    scanf("%c", &a );
}

void menu1(int op)
{
    switch(op)
    {
    case 1:
        new(0);
        break;
    case 2:
        resume();
        break;
    default:
        printf("Exit to main menu.\n");
    }
}

void h1()
{
    printf("--------------\n");
    printf("Are you sure you want to start a new game? Current progress on unfinished game may be lost.\n\n");
    printf("1 - Yes\n");
    printf("2 - Resume\n");
    printf("0 - Exit to main menu\n");
    printf("--------------\n");
}

void sm1()
{
    int o;

    do{
        system("cls");
        h1();
        printf("Enter option: ");
        scanf("%d", &o);
        menu1(o);
    } while(o > 1 && o <= 2);
}



void menu(int op)
{
    switch(op)
    {
    case 1:
        sm1();
        break;
    case 2:
        resume();
        break;
    case 3:
        leaderboard();
        break;
    default:
        printf("EXIT!\n");
    }
}


int main()
{
    int option;

    FILE *file = fopen("questions.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(1);
    }

    store_leaderboard();

    for (int i = 0; i < 50; i++) {
        struct question *q;
        if (i < 15)
            q = &e[i];
        else
        {
            if (i < 40)
                q = &m[i - 15];
            else
                q = &h[i - 40];
        }

        fgets(q->s, sizeof(q->s), file);
        fgets(q->a[0], sizeof(q->a[0]), file);
        fgets(q->a[1], sizeof(q->a[1]), file);
        fgets(q->a[2], sizeof(q->a[2]), file);
        fscanf(file, "%d\n", &q->c);
    }

    fclose(file);

    do{
        system("cls");
        header();
        printf("Enter option: ");
        scanf("%d", &option);
        menu(option);
    } while(option > 0 && option <= 3);

    return 0;
}
