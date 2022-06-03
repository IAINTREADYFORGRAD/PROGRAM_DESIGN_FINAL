#include "Base.h"
#include "struct.h"
void add_course(Course *head, char *Name, char *Location, int room_number, char *week, int begin_hours, int begin_minutes, int end_hours, int end_minutes, double difficult, double course_credit)
{

    Course *newCourse = (Course *)malloc(sizeof(Course));
    strcpy(newCourse->course_name, Name);
    strcpy(newCourse->class_location, Location);
    newCourse->classroom_number = room_number;
    strcpy(newCourse->time.week, week);
    newCourse->time.begin_hours = begin_hours;
    newCourse->time.begin_minutes = begin_minutes;
    newCourse->time.end_hours = end_hours;
    newCourse->time.end_minutes = end_minutes;
    newCourse->next = NULL;
    newCourse->prev = NULL;
    newCourse->star = difficult;
    newCourse->credits = course_credit;

    Course *cur = head, *pre;
    while (1)
    {
        if (cur->next == NULL)
        {
            pre = cur;
            cur->next = newCourse;
            cur = cur->next;
            cur->next = NULL;
            cur->prev = pre;
            return;
        }
        pre = cur;
        cur = cur->next;
    }
}

void add_curriculum(Course *class_head, Course *curriculm, int max_cp_A)
{
    Course *p = class_head;
    int i = 0;
    for (; p != NULL; p = p->next)
    {
        i++;
        if (i == max_cp_A + 1)
        {
            add_course(curriculm, p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
        }
    }
}

void delete_course(Course *head, char *name)
{
    Course *pre, *cur = head;

    while (1)
    {
        if (!strcmp(cur->course_name, name))
        {
            Course *t = cur;

            if (cur->next != NULL)
            {
                pre->next = cur->next;
                cur = cur->next;
                cur->prev = pre;
            }
            else
            {
                pre->next = NULL;
            }

            free(t);
            return;
        }

        if (cur->next == NULL)
        {
            printf("Invalid\n");
            return;
        }

        pre = cur;
        cur = cur->next;
    }
}

void delete_cannot_time(Course *class_head, char *week)
{
    Course *pre, *cur = class_head;

    while (1)
    {
        if (!strcmp(cur->time.week, week))
        {
            Course *t = cur;

            if (cur->next != NULL)
            {
                pre->next = cur->next;
                cur = cur->next;
                cur->prev = pre;
            }
            else
            {
                pre->next = NULL;
            }

            free(t);
            return;
        }

        if (cur->next == NULL)
        {
            return;
        }

        pre = cur;
        cur = cur->next;
    }
}

void print_all(Course *head) //印出全部
{
    Course *p = head->next;
    for (; p != NULL; p = p->next)
    {
        printf("%s %s %d %s %d %d %d %d %lf %lf\n", p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
    }
}

int start_time_to_min(Course *p)
{
    int time_min = 0;
    if (!strcmp(p->time.week, "Monday"))
    {
        p->week_to_int = 0;
    }
    else if (!strcmp(p->time.week, "Tuesday")) //如果是Tuesday就加一天24hr
    {
        p->week_to_int = 24;
    }
    else if (!strcmp(p->time.week, "Wednesday")) //如果是Wednesday就再加一天24hr＝48hr
    {
        p->week_to_int = 48;
    }
    else if (!strcmp(p->time.week, "Thursday"))
    {
        p->week_to_int = 72;
    }
    else if (!strcmp(p->time.week, "Friday"))
    {
        p->week_to_int = 96;
    }
    time_min = (p->time.begin_hours + p->week_to_int) * 60 + p->time.begin_minutes; //轉成分鐘
    return time_min;
}

int end_time_to_min(Course *p)
{
    int time_min = 0;
    if (!strcmp(p->time.week, "Monday"))
    {
        p->week_to_int = 0;
    }
    else if (!strcmp(p->time.week, "Tuesday")) //如果是Tuesday就加一天24hr
    {
        p->week_to_int = 24;
    }
    else if (!strcmp(p->time.week, "Wednesday")) //如果是Wednesday就再加一天24hr＝48hr
    {
        p->week_to_int = 48;
    }
    else if (!strcmp(p->time.week, "Thursday"))
    {
        p->week_to_int = 72;
    }
    else if (!strcmp(p->time.week, "Friday"))
    {
        p->week_to_int = 96;
    }
    time_min = (p->time.end_hours + p->week_to_int) * 60 + p->time.end_minutes; //轉成分鐘
    return time_min;
}

void time_sequence(Course *head)
{
    Course *p = head;
    int count = 0;
    p = p->next;
    for (; p != NULL; p = p->next)
    { //計算有幾個node，且判斷星期幾
        count++;
        // count_time(p);
    }
    Course *pre, *cur;
    for (int i = 0; i < count - 1; i++)
    {
        pre = head->next;
        for (int j = 0; j < count - i - 1; j++)
        {
            cur = pre->next;
            int compare1, compare2;
            compare1 = start_time_to_min(pre);
            compare2 = start_time_to_min(cur);

            // bubble sort(你原本寫的)
            if (compare1 > compare2)
            {
                cur->prev = pre->prev;
                pre->prev->next = cur;
                pre->prev = cur;
                pre->next = cur->next;
                if (cur->next != NULL)
                {
                    cur->next->prev = pre;
                }
                cur->next = pre;
            }
            else
            {
                pre = pre->next;
            }
        }
    }
}

void set_node(Course *p)
{
    p->next = NULL;
    p->prev = NULL;
    strcpy(p->course_name, "NULL");
    strcpy(p->class_location, "NULL");
    strcpy(p->time.week, "NULL");
    p->time.begin_hours = 0;
    p->time.begin_minutes = 0;
    p->time.end_hours = 0;
    p->time.end_minutes = 0;
    p->classroom_number = 0;
    p->star = 0;
    p->credits = 0;
    p->week_to_int = 0;
}
//搜尋 根據名字找到課程
Course *search(Course *head, const char *name)
{
    Course *p = head;
    for (; p != NULL; p = p->next)
    {
        if (strcmp(p->course_name, name) == 0)
        {
            return p;
        }
    }
    return NULL; //沒找到
}
//印一個
void print_single(Course *p)
{
    printf("你擁有此課程，以下是它的資訊:\n");
    printf("%s %s %d %s %d %d %d %d %lf %lf\n", p->course_name, p->class_location, p->classroom_number, p->time.week, p->time.begin_hours, p->time.begin_minutes, p->time.end_hours, p->time.end_minutes, p->star, p->credits);
}


//sort by alphabet

int count_courses(Course *head){
    Course *temp = head;
    int count=0;
    for (; temp->next != NULL; temp=temp->next){
        count++;
    }
    return count;
}

void insert_course(Course* head, Course* be_inserted, Course* to_insert){
    Course *be_pre=head, *to_pre=head;

    if (be_inserted==to_insert){
        return;
    }
    
    //to find _insert_'s previous node
    for (; be_pre->next != be_inserted; be_pre = be_pre->next) //; ? ;
        continue;

    for (; to_pre->next!=to_insert; to_pre=to_pre->next)
        continue;

    //insert
    to_pre->next = to_insert->next;
    to_insert->next = be_inserted;
    be_pre->next = to_insert;
}

int cmp_letter (Course* a, Course* b){
    char a_name[MAX_WORD];
    strcpy(a_name, a->course_name);
    char b_name[MAX_WORD];
    strcpy(b_name, b->course_name);
    int i = 0;

    //all convert to lowercase
    //use of undeclared identifier 'tolower'?
    int a_len = strlen(a_name);
    for (int j = 0; j < a_len; j++)
    {
        a_name[j] = tolower(a_name[j]);
    }

    int b_len = strlen(b_name);
    for (int j = 0; j < b_len; j++)
    {
        b_name[j] = tolower(b_name[j]); 
    }


    //to find the different letter location
    for (; i < MAX_WORD; i++)
    {
        if (a_name[i] != b_name[i]){
            break;
        }
    }

    //to compare letters at the location [i]
    if(a_name[i]>=b_name[i] || b_name[i]=='\r'){ // b_name will precede a_name
        return 0;
    }

    else if (a_name[i]<b_name[i] || a_name[i]=='\r'){ // b_name will be after a_name
        return 1;
    }
}

int binary_search(Course* head, int low, int high, Course* to_insert_node){
    Course *temp1=head->next, *temp_mid=head->next;
    int return_val;
    //to get the node located at low/highth
    for (int i = 0; i < low; i++){
        temp1 = temp1->next;
    }

    if (low >= high){   
        if(cmp_letter(temp1, to_insert_node)){ // if cmp_letter = 1, b_name will be after a_name
            return low + 1;
        }

        else{
            return low;
        }
    }
    else{ 
        int mid = (low + high) / 2; //operation '/': round down
        for (int i = 0; i < mid; i++){
            temp_mid = temp_mid->next;
        }

        if(!cmp_letter(temp_mid, to_insert_node)){ //if cmp_letter = 0, b_name will precede a_name
            return_val=binary_search(head, low, mid - 1, to_insert_node);
        }

        if(cmp_letter(temp_mid, to_insert_node)){
            return_val=binary_search(head, mid + 1, high, to_insert_node);
        }
    }
    return return_val;
}

void alphabet_sequence (Course *head){
    int count = count_courses(head);
    int loc;
    Course *to_insert_node, *temp;

    for (int i = 0; i < count-1; i++){
        to_insert_node=head->next;
        for (int j = 0; j < i + 1; j++){
            to_insert_node = to_insert_node->next;
        }
        
        loc=binary_search(head, 0, i, to_insert_node);
        temp = head->next;
        for (int j = 0; j < loc; j++){
            temp = temp->next;
        }
        insert_course(head, temp, to_insert_node);
    }
}

