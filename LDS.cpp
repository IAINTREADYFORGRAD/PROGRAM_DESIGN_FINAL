#include<stdio.h>
#include <cstdbool>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD 50
#define MAX_WEEK_WORD 10

//
typedef struct
{
    char week[MAX_WEEK_WORD];
    int begin_hours, begin_minutes, end_hours, end_minutes;
} _time;

struct _Course
{
    char course_name[MAX_WORD];    // (course name)

    struct _Course *next;
    struct _Course *prev;
};
typedef struct _Course Course;

void add_course(Course *head, char *Name)
{
    Course *newCourse = (Course *)malloc(sizeof(Course));
    strcpy(newCourse->course_name, Name);
    newCourse->next = NULL;
    newCourse->prev = NULL;

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

//

int max(int a, int b){
    if(a>=b)
        return a;
    else
        return b;
}

struct a_found_course{
    int LCS_num;
    char course_name[MAX_WORD];
    struct a_found_course *right;
    struct a_found_course *left;
};

struct a_found_course *create_node(int LCS_num, char course_name_[MAX_WORD]){
    struct a_found_course *new_node = (struct a_found_course *)malloc(sizeof(struct a_found_course));
    new_node->LCS_num = LCS_num;
    strcpy(new_node->course_name, course_name_);
    new_node->left = new_node->right = NULL;
    return new_node;
}

void create_tree(struct a_found_course** root, int LCS_num, char course_name[MAX_WORD]){
    struct a_found_course* temp = *root;

    if(temp==NULL){
        temp = create_node(LCS_num, course_name);
    }

    //arranged by LCS_num
    else if(LCS_num<temp->LCS_num){
        return create_tree(&(temp->left), LCS_num, course_name);
    }
    
    else if(LCS_num>temp->LCS_num){
        return create_tree(&(temp->right), LCS_num, course_name);
    }    
    
    //when LCS_nums resemble
    else{
        //the order would be based on the length of the name of the course
        struct a_found_course *new_= create_node(LCS_num, course_name);

        if(strlen(course_name) < strlen(temp->course_name)){
            if (temp->left != NULL){// insert
                new_->left = temp->left;
                temp->left = new_;
            }
            else{
                temp->left = new_;
            }
        }

        else{
            if (temp->right != NULL){
                new_->right = temp->right;
                temp->right = new_;
            }
            else{
                temp->right = new_;
            }
        }
        //what if courses have the same LCS_num and the same name length? -> possible?
    }
    *root = temp;
}

//for printing out
//reverse: to print out the most matched courses top 3
void inorder_traversal_reverse(struct a_found_course* root, int i, char*** result){
    struct a_found_course* temp = root;
    char **temp_result = *result;

    if(temp!=NULL){
        inorder_traversal_reverse(temp->right, i, &temp_result);
        temp_result = (char **)realloc(temp_result, sizeof(char *) * (i + 1));
        temp_result[i] = (char *)realloc(temp_result, sizeof(char) * strlen(temp->course_name));
        strcpy(temp_result[i], temp->course_name);
        i++;
        inorder_traversal_reverse(temp->left, i, &temp_result);
    }

    *result = temp_result;
}

void print_top3 (char ** result){
    for (int i = 0; i < 3; i++){
        printf("%s", result[i]);
    }
}

void find_courses(char* targeted_course_name, Course *head){
    int i, j; 
    int targeted_course_len = strlen(targeted_course_name);
    struct a_found_course *start = NULL;

    for (Course *temp = head->next; temp != NULL; temp=temp->next){
        int cmp_course_len = strlen(temp->course_name);
        char cmp_course_name[cmp_course_len];
        strcpy(cmp_course_name, temp->course_name);
        int square[targeted_course_len+1][cmp_course_len+1];

        for (i = 0; i < targeted_course_len+1; i++)
            square[i][0] = 0;
        for (j = 0; j < cmp_course_len+1; j++)
            square[0][j] = 0;

        for (i = 1; i < targeted_course_len+1; i++){
            for (j = 1; j < cmp_course_len+1; j++){
                if (targeted_course_name[i-1]==cmp_course_name[j-1]){
                    square[i][j] = square[i - 1][j - 1] + 1;
                }
                else {
                    square[i][j] = max(square[i][j - 1], square[i - 1][j]);
                }
            }
        }
        //binary search (tree)
        if(square[i-1][j-1]>0){
            create_tree(&start, square[i-1][j-1], cmp_course_name);
        }
    }

    char ** result=NULL;
    printf("%s", result[0]);
    i = 0;
    inorder_traversal_reverse(start, i, &result);
    print_top3(result);
}

int main(){
    char name[MAX_WORD], to_find[MAX_WORD];
    Course *newCourse = (Course *)malloc(sizeof(Course));
    Course *head = newCourse;
    head->next = NULL;

    int num;
    scanf("%d", &num);
    for (int i = 0; i < num; i++){
        scanf("%s", name);
        add_course(head, name);
    }

  

    scanf("%s", to_find);
    find_courses(to_find, head);
}


