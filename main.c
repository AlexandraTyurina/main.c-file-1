#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h"
#include "list2.h"
#include "list3.h"
#define MAXLEN 60
#define EPS 3e-6

int main()
{
    Head *p0=NULL;
    Node *p=NULL,*p1=NULL;
    Node2 *g=NULL,*g1=NULL,*MyNode=NULL;
    FILE *df;
    int n,i;
    int num=0,slen,a=0;
    float (*sort[8])(Node2*);
    float result, per;
    int choice;
    char s1[MAXLEN],*s2;
    sort[0] = sRAM;
    sort[1] = snucleus;
    sort[2] = srate;
    sort[3] = sweight;
    sort[4] = spar0;
    sort[5] = spar1;
    sort[6] = spar2;
    printf ("What do you want to work with?\n\t 0 - for linear single-linked list;\n\t 1 - for a linear doubly linked list;\n\t 2 - for a doubly linked ring list\n");
    scanf ("%i", &choice);
    df=fopen("laptop_info.csv","r");
    if(df!=NULL)
    {
        n=0;
        while(fgets(s1,MAXLEN,df)!=NULL)
        {
            n++;
        }
        rewind(df);
    }
    if ((choice==0)&&(df))
    {
        p0=MakeHead();
        p=CreateNode(df);
        AddFirst(p0,p);
        for (i=0; i<(n-2); i++)
        {
            p1=CreateNode(df);
            InsertAfter(p0, p1,p0->last);
        }
        p1=CreateNode(df);
        AddLast(p0,p1,p0->last);
        printf ("\tInitial data\n\n");
        print_header();
        p=p0->first;
        while(p!=NULL)
        {
            struct_out(p->comp);
            p=p->next;
        }
        printf ("What number you choose?");
        scanf ("%i", &num);
        if (num==1) printf ("The removal is not possible!");
        else
        {
            p=SelectById(p0, num);
            if (num==2)
            {
                p0->first=p->next;
                free(p);
                p=NULL;
            }
            else  deleteSelected(p0, p);
            printf ("\tChanged data\n\n");
            print_header();
            p=p0->first;
            while(p!=NULL)
            {
                struct_out(p->comp);
                p=p->next;
            }
        }
//cleaning the list, head and additional pointer
        p=p0->first;
        while(p!=NULL)
        {
            p1=p->next;
            ClearStructure(p->comp);
            free(p);
            p=p1;
        }
        if(p0)
            free(p0);
        free(p0->first);
        p0->first=NULL;
        free (p0->last);
        p0->last=NULL;
    }
    if ((choice==1)&&(df))
    {
        p0=MakeHead();
        g1=CreateNode2(df); 
        AddFirst2(p0,g1);
        g=p0->first;
        for (i=0; i<(n-2); i++)
        {
            MyNode=CreateNode2(df);
            InsertAfter2(p0, MyNode, g);
            g=MyNode;
        }
        g1=CreateNode2 (df);
        AddLast2(p0, g1, g);
        printf("\n--Input is finished.--\n");
        printf("\n--Your data is:--\n");
        print_header();
        g=p0->first;
        while(g!=NULL)
        {
            struct_out(g->comp);
            g=g->next;
        }
        printf ("What sort of data do you want to choose?\n0-'RAM';\n1-'nucleus';\n2-'rate';\n3-'weight';\n4-parameter[0];\n5-parameter[1];\n6-parameter[2];\n7-'name'\n8-'seria'\n");
        scanf ("%i", &num);
        getchar();
        printf ("Enter data : \n");
        fgets(s1, 15, stdin);
        slen=strlen(s1);
        s1[slen-1]='\0';
        slen=strlen(s1);
        g=p0->first;
        while(g!=NULL)
        {
            if (num<7)
                {
                    result=sort[num](g);
                    per=atof(s1);
                }
            if ((num<7)&&(fabs(per-result)< EPS))
            {
                a++;
                if ((g->prev!=NULL)&&(g->next!=NULL))
                {
                    g1=g->prev;
                    g1->next=g->next;
                    MyNode=g->next;
                    MyNode->prev=g1;

                }
                else
                {
                    if (g->prev==NULL)
                    {
                        p0->first=g->next;
                        ClearStructure(g->comp);
                    }
                    else
                    {
                        g1=g->prev;
                        g1->next=NULL;
                        p0->last=g->prev;
                        ClearStructure(g->comp);
                    }
                }
            }
            if (num==7)
            {
                s2=(char*)malloc((MAXLEN)*sizeof(char));
                s2=g->comp->name;
            }
            if (num==8)
            {
                s2=(char*)malloc((MAXLEN)*sizeof(char));
                s2=g->comp->seria;
            }
            if ((num==7)&&(strcmp(s1,s2)==0)&&(s2!=NULL))
            {
                a++;
                if ((g->prev!=NULL)&&(g->next!=NULL))
                {
                    g1=g->prev;
                    g1->next=g->next;
                    MyNode=g->next;
                    MyNode->prev=g1;

                }
                else
                {
                    if (g->prev==NULL)
                    {
                        p0->first=g->next;
                        ClearStructure(g->comp);
                    }
                    else
                    {
                        g1=g->prev;
                        g1->next=NULL;
                        p0->last=g->prev;
                        ClearStructure(g->comp);
                    }
                }
            }
            if ((num==8)&&(strcmp(s1,s2)==0))
            {
                a++;
                if ((g->prev!=NULL)&&(g->next!=NULL))
                {
                    g1=g->prev;
                    g1->next=g->next;
                    MyNode=g->next;
                    MyNode->prev=g1;

                }
                else
                {
                    if (g->prev==NULL)
                    {
                        p0->first=g->next;
                        ClearStructure(g->comp);
                    }
                    else
                    {
                        g1=g->prev;
                        g1->next=NULL;
                        p0->last=g->prev;
                        ClearStructure(g->comp);
                    }
                }
            }
            g=g->next;
        }
        if (a!=0)
        {
            printf("\n--Changed data is:--\n");
            print_header();
            g=p0->first;
            while(g!=NULL)
            {
                struct_out(g->comp);
                g=g->next;
            }
        }
        else
            printf ("There aren't any matching values!");
        //cleaning the list, head and additional pointer
        g=p0->first;
        while(g!=NULL)
        {
            g1=g->next;
            if (g->comp) ClearStructure(g->comp);
            free (g);
            g=g1;
        }
        free(p0);
        if (MyNode) free (MyNode);
    }
    if ((choice==2)&&(df))
    {
        p0=MakeHead();
        g1=CreateNode2(df); 
        AddFirst2(p0,g1);
        g=p0->first;
        for (i=0; i<(n-2); i++)
        {
            MyNode=CreateNode2(df);
            InsertAfter2(p0, MyNode, g);
            g=MyNode;
        }
        g1=CreateNode2 (df);
        AddLast2(p0, g1, g);
        g1->next=p0->first;
        g=p0->first;
        g->prev=g1;
        g=p0->last;
        printf("\n--Your data is:--\n");
        print_header();
        g=p0->first;
        do
        {
            struct_out(g->comp);
            g=g->next;
        }
        while(g!=p0->first);
        printf("\n--Input is finished.--\n");
        addition_elemF (p0,g1,g);
        printf("\n--Changed data is:--\n");
        print_header();
        g=p0->first;
        do
        {
            struct_out(g->comp);
            g=g->next;
        }
        while(g!=p0->first);
//cleaning the list, head and additional pointer
        g=p0->first;
        g=g->next;
        while(g->prev!=p0->last)
        {
            g1=g->next;
            if (g) free (g);
            g=g1;
        }
        if (g1)
        {
            free (g1);
            g1=NULL;
        }
        if (g)
        {
            free (g);
            g=NULL;
        }
        free(p0);
        if (MyNode) free (MyNode);
    }
    if (df==NULL)
    {
        p0=MakeHead();
        addition_elemN (p0);
    }
    fclose (df);
    return 0;

}
