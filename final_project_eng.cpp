#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Base.h"
#include "struct.h"
#include "DP_Select.h"
#include "map.h"
// global
char order[30]; //輸入的指令
struct _Student Student[50];
//插入課程名稱 1->2
void insert(Course *head,char *name,char *name2){
  Course *p =  search(head,name);
  Course *p2 = search(head,name2);
  if(p == NULL){
    printf("insertion failed. no corresponding course. add the course at the end of the course list\n");
  }
  else{
    p2->next = p->next;
    p2->prev = p;
    p->next = p2;
  }
}
// memset 變數 要不然後續的輸入值會被覆蓋掉
void mem_ALL(char name[], char week[], char location[],char name2[])
{
    memset(order, 0, sizeof(order));        //初始0
    memset(week, 0, sizeof(*week));         //初始0
    memset(name, 0, sizeof(*name));         //初始0
    memset(location, 0, sizeof(*location)); //初始0
    memset(name2, 0, sizeof(*name2));         //初始0
}
// list information把如何使用指令印出//可更改成更舒服的輸入方式 ADD/DELETE/LIST/INSERT/SORT
void print_inform()
{
    char T[2];
    printf("####   [instructions]   ####\n");
    if (strcmp(order, "ADD") == 0)
    {
        printf("ADD command format:\n");
        printf("class name | building | classroom | day (Monday, Tuesday, etc) | begin at (hr) | begin at (min) | end at (hr) | end at (min) | difficultt | credits\n");
        printf("building abbriviation (format):\n");
        printf("[common class building A/B:edA/edB][colege of engineering A/B: enA /enB][college of science A/B: scA/scB][college of social science A/B: soA/soB][innovation building: inno]\n");
        printf("[college of management: man][college of humanities: hum][activity center: center][gymnasium: gym][language center: lan][college of law: law]\n");
        printf("$$NOTICE: 24-hour time (namely, 3:05 pm would be 15 | 05)  $$\n");
    }
    else if (strcmp(order, "DELETE") == 0)
    {
        printf("DELETE command format:\n");
        printf("[DELETE course name]\n");
    }
    else if (strcmp(order, "LIST") == 0)
    {
        printf("LIST command format:\n");
        printf("[LIST]\n");
    }
    else if (strcmp(order, "INSERT") == 0)
    {
        printf("INSERT command format:\n");
        printf("[INSERT course name A | course name B]");
        printf("$$NOTICE:  course name B will be after A (**NAME_A->NAME_B**)$$\n");
    }
    else if (strcmp(order, "SORT") == 0)
    {
        printf("SORT command format:\n");
        printf("[SORT]");
    }
    else if (strcmp(order, "SEARCH") == 0)
    {
        printf("SEARCH command format:\n");
        printf("[SEARCH course name]\n");
    }
    else
    {
        printf("!!wrong format or invalid input !!\nTry again?(Y/N): ");
        scanf("%s", T);
        if (strcmp(T, "Y") == 0 || strcmp(T, "YES") == 0)
        {
            printf("enter the command again (the command 'ORDER' is not needed): ");
            memset(order, 0, sizeof(order));
            scanf("%s", order);
            print_inform();
        }
    }
}
// memset node to null 之後有想要memset的可以自行修改 目前只有設前後pointer和名稱 NULL
//多寫註解，要不然以後會看得很痛苦喔
//多寫提示
int token1(int i, char not_attend[])
{
    int str_long = strlen(not_attend);
    int k = 0, m = 0, count = 0;
    for (int j = 0; j < str_long; j++)
    {
        if (not_attend[j] != ' ' && not_attend[j] != '\n')
        {
            Student[i].cannot_attend[k][m] = not_attend[j];
            m++;
        }
        else if (not_attend[j] == ' ')
        {
            k++;
            m = 0;
            count++;
        }
        else if (not_attend[j] == '\n')
        {
            return count + 1;
        }
    }
    return count + 1;
}
int token2(int i, char already[])
{
    int str_long = strlen(already);
    int k = 0, m = 0, count = 0;
    for (int j = 0; j < str_long; j++)
    {
        if (already[j] != ' ' && already[j] != '\n')
        {
            Student[i].course_already[k][m] = already[j];
            m++;
        }
        else if (already[j] == ' ')
        {
            k++;
            m = 0;
            count++;
        }
        else if (already[j] == '\n')
        {
            return count + 1;
        }
    }
    return count + 1;
}

int main()
{
    Course *newCourse = (Course *)malloc(sizeof(Course));
    Course *head = newCourse;
    set_node(head);
    //變數
    char name[MAX_WORD];
    char name2[MAX_WORD];
    char location[MAX_WORD];
    int room_number;
    char week[MAX_WEEK_WORD];
    char start[MAX_WORD];
    char end[MAX_WORD];
    int begin_hours;
    int begin_minutes;
    int end_hours;
    int end_minutes;
    double difficult;
    double course_credit;
    //
    FILE *fp1, *fp2;
    fp1 = fopen("filename.txt", "w");
    fp2 = fopen("filename.txt", "r");
    //提示字
    printf("enter one of the commands : ADD | DELETE | LIST | SORT | INSERT | SEARCH | MAP\n");
    printf("enter 'ORDER NAME' to get the further commands regarding course\n");
    printf("enter 'END' to end the command! \n");
    printf("plz enter a command:\n");
    //測試區 用指令方式 能比較方便用
    // while (scanf("%s", order) != EOF)
    scanf("%s", order);
    while (strcmp(order, "END"))
    {
        if (strcmp(order, "ORDER") == 0)
        {
            memset(order, 0, sizeof(order)); //初始0
            scanf("%s", order);              //吃名字
            print_inform();                  //印出指令template
            printf("####   [commands instruction]   ####\n");
        }
        else if (strcmp(order, "ADD") == 0)
        {
            printf("class name | building | classroom | day (Monday, Tuesday, etc) | begin at | end at | difficultt | credits\n");
            scanf("%s %s %d %s %s %s %lf %lf", name, location, &room_number, week, start,end, &difficult, &course_credit);
            if(start[2]!=':'||end[2]!=':'||start[5]!='\0'||end[5]!='\0'){
                printf("wrong time format. correct format: xx:xx (24-hour time). failed to ADD the course\n");
            }
            else{
                char sh[3],sm[3],eh[3],em[3];
                for(int i=0;i<2;i++){
                    sh[i] = start[i];
                    eh[i] = end[i];
                }
                for(int i=3;i<5;i++){
                    sm[i-3] = start[i];
                    em[i-3] = end[i];
                }
                sh[2] = '\0';
                sm[2] = '\0';
                eh[2] = '\0';
                em[2] = '\0';
                add_course(head, name, location, room_number, week, atoi(sh), atoi(sm), atoi(eh), atoi(em), difficult, course_credit);
            }

        }
        else if (strcmp(order, "DELETE") == 0)
        {
            printf("to delete (enter the course name):\n");
            scanf("%s", name);
            delete_course(head, name);
        }
        else if (strcmp(order, "LIST") == 0)
        {
            print_all(head);
        }
        else if (strcmp(order, "INSERT") == 0)
        {
            printf("name of the previous course:\n");
            scanf("%s",name);
            printf("class name | building | classroom | day (Monday, Tuesday, etc) | begin at | end at | difficultt | credits\n");
            scanf("%s %s %d %s %s %s %lf %lf", name, location, &room_number, week, start,end, &difficult, &course_credit);
            if(start[2]!=':'||end[2]!=':'||start[5]!='\0'||end[5]!='\0'){
                printf("wrong time format. correct format: xx:xx (24-hour time). failed to ADD the course\n");
            }
            else{
                char sh[3],sm[3],eh[3],em[3];
                for(int i=0;i<2;i++){
                    sh[i] = start[i];
                    eh[i] = end[i];
                }
                for(int i=3;i<5;i++){
                    sm[i-3] = start[i];
                    em[i-3] = end[i];
                }
                sh[2] = '\0';
                sm[2] = '\0';
                eh[2] = '\0';
                em[2] = '\0';
                add_course(head, name, location, room_number, week, atoi(sh), atoi(sm), atoi(eh), atoi(em), difficult, course_credit);
                insert(head,name,name2);
              }
        }
        else if (strcmp(order, "SORT") == 0)
        {
            char seq[MAX_WORD];
            printf("preference: in time sequence or in alphabet sequence\n");
            printf("plz enter: TIME | ALPHABET\n");
            scanf("%s", seq);

            if (!strcmp(seq, "TIME")){
                time_sequence(head);
                print_all(head);
            }

            else if (!strcmp(seq, "ALPHABET")){
                alphabet_sequence(head);
                print_all(head);
            }

            else{
                printf("typo, try again\n");
            }
        }
        else if (strcmp(order,"SEARCH") == 0){
            scanf("%s",name);
            Course *p = search(head,name);
            if(p == NULL){
                printf("no matched course!\n");
            }
            else{
                print_single(p);
            }
        }
        else if (strcmp(order,"MAP") == 0){
            printf("course course|next course");
            scanf("%s %s",name,name2);
            SP_ED(head, name, name2, fp1);
        }
        else
        {
            printf("wrong command!\nTry again!\n");
        }
        mem_ALL(name, week, location,name2);
        printf("enter one of the commands : ADD | DELETE | LIST | SORT | INSERT | SEARCH | MAP\n");
        printf("enter 'ORDER NAME' to get the further commands regarding course\n");
        printf("enter 'END' to end the command! \n");
        printf("plz enter a command:\n");
        scanf("%s", order);
    }

    for (int i = 0; i < 50; i++)
    {
        strcpy(Student[i].student_name, "\0");
        for (int j = 0; j < 5; j++)
        {
            strcpy(Student[i].cannot_attend[j], "\0");
        }
        for (int k = 0; k < 50; k++)
        {
            strcpy(Student[i].course_already[k], "\0");
        }
    }
    int student_number;
    char st_name[MAX_WORD];
    char not_attend[1000];
    char already[1000];
    printf("enter the number of students: ");
    scanf("%d", &student_number);
    int cannot_days[50] = {0};
    int already_course[50] = {0};
    printf("enter student info\n");
    for (int i = 0; i < student_number; i++) //輸入學生資料
    {
        printf("name | unavailable day | the courses have been token\n");
        scanf("%s\n", st_name);
        strcpy(Student[i].student_name, st_name);
        fgets(not_attend, 1000, stdin);
        cannot_days[i] = token1(i, not_attend);
        fgets(already, 1000, stdin);
        already_course[i] = token2(i, already);
    }

    char class_arrangement[MAX_WORD]; //排課方式
    printf("enter wanted class arrangement way: ");
    scanf("%s", class_arrangement);
    for (int i = 0; i < student_number; i++)
    {
        if (!strcmp(class_arrangement, "DP_select"))
        {
            printf("print the curriculum timetable: \n");
            course_select(head, i, Student, cannot_days[i], already_course[i]);
        }
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
//(╯°Д°）╯︵ /(.□ . \)
//╭(°A°`)╮

/*void print_course(Course a)
{
    printf("the day : %s, begin : %d:%d, end : %d:%d\n", a.time.week, a.time.begin_hours, a.time.begin_minutes, a.time.end_hours, a.time.end_minutes);
    printf("%s, %s, %d\n", a.class_location, a.course_name, a.classroom_number);
    printf("%f, %d\n", a.stars, a.credits);
}*/
/*for (int i = 0; i < student_number; i++)
    {
        printf("%s\n", Student[i].student_name);
        for (int j = 0; j < cannot_days; j++)
        {
            printf("%s\n", Student[i].cannot_attend[j]);
        }
        for (int j = 0; j < already_course; j++)
        {
            printf("%s\n", Student[i].course_already[j]);
        }
    }*/


// gcc -o trytry Base.cpp DP_Select.cpp final_project_eng.cpp map.cpp
// cd C:\vscode\final_project

//程設那種有兩個時段的，蘇那個查詢會不會只印出某一天的