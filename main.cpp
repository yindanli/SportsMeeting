#include <stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define default_num 3  ///Ĭ�ϻ�������Ŀ��ȡ3��5
typedef struct Sport
{
    char name[20];       ///��Ŀ����
    int win_school[5];   ///��ǰ����ǰ��ѧУ�ı��
    int award_num;       ///����˶���Ŀȡ���ε���Ŀ��ȡ3��5
} Sport;                 ///�����Ŀ��Ϣ
typedef struct School
{
    int total_score[3];///�±�0��ʾѧУ�ܷ֣�1��ʾ�����ܷ֣�2��ʾŮ���ܷ֣�����֮����������������������
    char name[20];   ///ѧУ����
    int scores[50];  ///������Ŀ�÷�
} School;

///��ʼ��Ĭ��ֵ
int n=20;  ///���ѧУ��Ŀ
int m=10;  ///���������Ŀ��Ŀ
int w=10;  ///���Ů����Ŀ��Ŀ
School schools[25];  ///ѧУ�ṹ������
School temp[25];  ///�������������б�ѧУ����
School temp1[25];  ///���򻺴�����
Sport sports[50];  ///������Ŀ�ṹ������
int three[3]={5,3,2};   ///���ǰ������ѧУ����
int five[5]={7,5,3,2,1};  ///���ǰ������ѧУ����

void readFromFile();///�������ļ���ȡ���е��˶���ɼ���Ϣ

void firstUsed()///������������
{
    for(int i=0; i<n; i++)
    {
        schools[i].total_score[0]=0;
        schools[i].total_score[1]=0;
        schools[i].total_score[2]=0;
        for(int j=0; j<m+w; j++){
            schools[i].scores[j]=0;
        }
    }
    for(int i=0; i<m+w; i++)
    {
        for(int j=0; j<5; j++)
            sports[i].win_school[j]=0;
    }

    FILE* fp = fopen("setting.txt","r");
    for(int i=0;i<50;i++)
    {
        fscanf(fp,"%d",&sports[i].award_num);
    }
    fclose(fp);
}
void initialization()///��ʼ���������ڴ��ļ����������д򿪳���Ķ�ȡ��ʼ������
{
    readFromFile();

    FILE* fp = fopen("setting.txt","r");
    if(fp==NULL)
    {
        firstUsed();
    }
    for(int i=0; i<50; i++)
    {
        fscanf(fp,"%d",&sports[i].award_num);
    }
    fscanf(fp,"%d%d%d",&n,&m,&w);
    fclose(fp);
}

void saveToFile()///�����뵽�ڴ��е����ݴ浽�ļ���
{
    FILE* fp1 = fopen("schools.txt","w");
    if(fp1==NULL)
    {
        printf("�ļ�δ�ɹ��򿪣�����\n");
    }
    for(int i=0; i<n; i++)
    {
        fprintf(fp1,"%s\n",schools[i].name);
        fprintf(fp1,"%d %d %d \n",schools[i].total_score[0],schools[i].total_score[1],schools[i].total_score[2]);
        for(int j=0; j<m+w; j++)
        {
            fprintf(fp1,"%d ",schools[i].scores[j]);
        }
        fprintf(fp1,"\n\n");
    }
    fclose(fp1);

    FILE* fp2 = fopen("sports.txt","w");
    if(fp2==NULL)
    {
        printf("�ļ�δ�ɹ��򿪣�����\n");
    }
    for(int i=0; i<m+w; i++)
    {
        fprintf(fp2,"%s\n",sports[i].name);
        fprintf(fp2,"%d\n",sports[i].award_num);
        for(int j=0; j<sports[i].award_num; j++)
        {
            fprintf(fp2,"%d ",sports[i].win_school[j]);
        }
        fprintf(fp2,"\n\n");
    }
    fclose(fp2);
}

void readFromFile()
{
    FILE* fp1 = fopen("schools.txt","r");
    if(fp1==NULL)
    {
        firstUsed();
    }
    for(int i=0; i<n; i++)
    {
        fscanf(fp1,"%s",schools[i].name);
        fscanf(fp1,"%d %d %d",&schools[i].total_score[0],&schools[i].total_score[1],&schools[i].total_score[2]);
        for(int j=0; j<m+w; j++)
        {
            fscanf(fp1,"%d",&schools[i].scores[j]);
        }
    }
    fclose(fp1);

    FILE* fp2 = fopen("sports.txt","r");
    if(fp2==NULL)
    {
        firstUsed();
    }
    for(int i=0; i<m+w; i++)
    {
        fscanf(fp2,"%s",sports[i].name);
        fscanf(fp2,"%d",&sports[i].award_num);
        for(int j=0; j<sports[i].award_num; j++)
        {
            fscanf(fp2,"%d",&sports[i].win_school[j]);
        }
    }
    fclose(fp2);
}

void merge_sort(School temp[],int st,int en,int option,School temp1[])///���ղ�ͬ�Ĳ�����ѧУ�����������
{
    if(en-st==1)return;
    int mid = st + (en-st)/2;
    merge_sort(temp,st,mid,option,temp1);
    merge_sort(temp,mid,en,option,temp1);

    int st1=st,st2=mid,tst=st;
    while(st1<mid&&st2<en)
    {
        if(temp[st1].total_score[option]>temp[st2].total_score[option])temp1[tst++]=temp[st1++];
        else temp1[tst++]=temp[st2++];
    }
    while(st1<mid)temp1[tst++]=temp[st1++];
    while(st2<en)temp1[tst++]=temp[st2++];
    int j;
    for(j = st; j<en; j++)
        temp[j]=temp1[j];
}

void schoolInput(int schoolnum,int award_num,int i,int pos)///����ѧУ�ɼ���ͳ��
{
    if(award_num==3)
    {
        schools[schoolnum].scores[pos]+=three[i];
        schools[schoolnum].total_score[0]+=three[i];
        if(pos>=0&&pos<m)schools[schoolnum].total_score[1]+=three[i];
        else if(pos>=m&&pos<m+w)schools[schoolnum].total_score[2]+=three[i];
    }
    else if(award_num==5)
    {
        schools[schoolnum].scores[pos]+=five[i];
        schools[schoolnum].total_score[0]+=five[i];
        if(pos>=0&&pos<m)schools[schoolnum].total_score[1]+=five[i];
        else if(pos>=m&&pos<m+w)schools[schoolnum].total_score[2]+=five[i];
    }
}

void inputScores()///������Ŀ�ɼ��˵�
{
loop1:
    system("cls");
    printf("�밴˳�����������Ŀ�ɼ�����λ�����λΪǰ������ǰ�����ĳɼ�,���ο�ǰ�������룩��\n");
    firstUsed();
    for(int pos=0; pos<m+w; pos++)
    {
        printf("���%d:",pos+1);
        int award_num = sports[pos].award_num;
        if(award_num==3)
        {
            for(int i=0; i<award_num; i++)
            {
                scanf("%d",&sports[pos].win_school[i]);
                sports[pos].win_school[i]--;
                if(sports[pos].win_school[i]<0||sports[pos].win_school[i]>=m+w)
                {
                    i--;
                    printf("û��������ı�Ŷ�Ӧ��ѧУ�����������룺\n");
                    continue;
                }
                schoolInput(sports[pos].win_school[i],award_num,i,pos);
            }
        }
        else if(award_num==5)
        {
            for(int i=0; i<award_num; i++)
            {
                scanf("%d",&sports[pos].win_school[i]);
                sports[pos].win_school[i]--;
                if(sports[pos].win_school[i]<0||sports[pos].win_school[i]>=m+w)
                {
                    i--;
                    printf("û��������ı�Ŷ�Ӧ��ѧУ�����������룺\n");
                    continue;
                }
                schoolInput(sports[pos].win_school[i],award_num,i,pos);
            }
        }
    }

    int flag=0;
loop2:
    system("cls");
    printf("\n\n\n");
    printf("\t\t**************************************************\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*     ������������ɣ����������²�����Ӧ���     *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t*             1.��������                         *\n");
    printf("\t\t*             2.��������                         *\n");
    printf("\t\t*             3.�������˵�                       *\n");
    printf("\t\t*             4.�˳�ϵͳ                         *\n");
    printf("\t\t*                                                *\n");
    printf("\t\t**************************************************\n");
    if(flag==0)printf("��������ѡ���ѡ���Ӧ�ı�ţ�\n");
    else printf("û���������ѡ���ţ����������룺\n");
    int option;
    scanf("%d",&option);
    switch(option)
    {
    case 1:
        saveToFile();
        printf("\n\n\n\t\t\t\t����ɹ�������\n");
        Sleep(1000);
        goto loop2;
        break;
    case 2:
        initialization();
        goto loop1;
        break;
    case 3:
        initialization();
        system("cls");
        return;
        break;
    case 4:
        saveToFile();
        Sleep(1000);
        exit(0);
        break;
    default:
        flag=1;
        goto loop1;
    }
}

void showSchool()///���ѧУ�˵�
{
    char* str[]= {"�ܷ�","�����ܷ�","Ů���ܷ�"};
    int flag=0;
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t******************************************\n");
        printf("\t\t*                                        *\n");
        printf("\t\t*          1.��ѧУ����г�              *\n");
        printf("\t\t*          2.��ѧУ�ܷ��г�              *\n");
        printf("\t\t*          3.��������Ŀ�ܷ��г�          *\n");
        printf("\t\t*          4.��Ů����Ŀ�ܷ��г�          *\n");
        printf("\t\t*          5.�������˵�                  *\n");
        printf("\t\t*          6.�˳�ϵͳ                    *\n");
        printf("\t\t*                                        *\n");
        printf("\t\t******************************************\n");
        if(flag==0)
            printf("������ѡ���Ӧ��ţ�\n");
        else printf("û���������ѡ����������룺\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
        case 1:
            system("cls");
            printf("ѧУ���ձ���г���\n");
            printf("ѧУ����\tѧУ�ܷ�\t�����ܷ�\tŮ���ܷ�\n");
            for(int i=0; i<n; i++)
            {
                printf("%8s\t%8d\t%8d\t%8d\n",schools[i].name,schools[i].total_score[0],schools[i].total_score[1],schools[i].total_score[2]);
            }
            printf("-----�������������һ��-----");
            getch();
            break;

        case 2:
        case 3:
        case 4:
            system("cls");
            for(int i=0; i<n; i++)
            {
                temp[i]=schools[i];
            }
            merge_sort(temp,0,n,option-2,temp1);
            printf("ѧУ����%s�г���\n",str[option-2]);
            printf("ѧУ����\tѧУ�ܷ�\t�����ܷ�\tŮ���ܷ�\n");
            for(int i=0; i<n; i++)
            {
                printf("%8s\t%8d\t%8d\t%8d\n",temp[i].name,temp[i].total_score[0],temp[i].total_score[1],temp[i].total_score[2]);
            }
            printf("-----�������������һ��-----");
            getch();
            break;
        case 5:
            system("cls");
            return;
            break;
        case 6:
            saveToFile();
            Sleep(1000);
            exit(0);
            break;
        default:
            flag=1;
        }
    }
}

void showSports()///���������Ŀ�˵�
{
    int flag=0;
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t******************************************\n");
        printf("\t\t*                                        *\n");
        printf("\t\t*          1.��ѯѧУ��Ŀ�ɼ�            *\n");
        printf("\t\t*          2.��ѯ��Ŀ��ѧУ            *\n");
        printf("\t\t*          3.�������˵�                  *\n");
        printf("\t\t*          4.�˳�ϵͳ                    *\n");
        printf("\t\t*                                        *\n");
        printf("\t\t******************************************\n");
        if(flag==0)
            printf("������ѡ���Ӧ��ţ�\n");
        else printf("�������ѡ����ڣ����������룺\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
        case 1:
            system("cls");
            printf("������Ҫ��ѯ��ѧУ��ţ�\n");
            int num;
            scanf("%d",&num);
            num--;
            printf("������Ҫ��ѯ�ĸ�ѧУ����Ŀ��ţ�\n");
            int sp;
            scanf("%d",&sp);
            sp--;
            printf("%s��%s��Ŀ�񽱵÷�������£�\n",schools[num].name,sports[sp].name);
            printf("%d\n\n",schools[num].scores[sp]);
            printf("-----�������������һ��-----");
            getch();
            break;
        case 2:
            system("cls");
            printf("������Ҫ��ѯ����Ŀ��ţ�\n");
            int num1;
            scanf("%d",&num1);
            num1--;
            printf("����ѯ��%s��Ŀ�Ļ�ѧУ���£�\n",sports[num1].name);
            for(int i=0; i<sports[num1].award_num; i++)
            {
                printf("%d : %s\n",sports[num1].win_school[i],schools[sports[num1].win_school[i]].name);
            }
            printf("-----�������������һ��-----");
            getch();
            break;
        case 3:
            system("cls");
            return;
            break;
        case 4:
            saveToFile();
            Sleep(1000);
            exit(0);
            break;
        default:
            flag=1;
        }
    }
}

void setting()///���ò˵�
{
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t******************************************\n");
        printf("\t\t*                                        *\n");
        printf("\t\t*           1.������Ŀǰ����ǰ��         *\n");
        printf("\t\t*           2.����ѧУ��Ŀ               *\n");
        printf("\t\t*           3.����������Ŀ��Ŀ           *\n");
        printf("\t\t*           4.����Ů����Ŀ��Ŀ           *\n");
        printf("\t\t*           5.�������˵�                 *\n");
        printf("\t\t*           6.�˳�ϵͳ                   *\n");
        printf("\t\t*                                        *\n");
        printf("\t\t******************************************\n");
        printf("������ѡ���Ӧ��ţ�\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
        case 1:
            while(1)
            {
                system("cls");
                printf("������Ҫ���õ���Ŀ��ţ�\n");
                int n1;
                scanf("%d",&n1);
                n1--;
                printf("������3��5���ø���ĿҪȡ�Ļ����Σ�\n");
                while(1)
                {
                    int n2;
                    scanf("%d",&n2);
                    if(n2==3||n2==5)
                    {
                        sports[n1].award_num=n2;
                        break;
                    }
                    system("cls");
                    printf("������������������������룺\n");
                }
                printf("��������������1��������һ��������2��\n");
                scanf("%d",&n1);
                if(n1==1)continue;
                else if(n1==2)break;
            }
            break;
        case 2:
            system("cls");
            printf("������ѧУ��Ŀ��\n");
            while(1)
            {
                scanf("%d",&n);
                if(n<=20&&n>=1)break;
                else
                {
                    system("cls");
                    printf("�������ѧУ��Ŀ���Ϸ������������룺\n");
                }
            }
            printf("-----�������������һ��-----\n");
            getch();
            break;
        case 3:
            system("cls");
            printf("������������Ŀ��Ŀ��\n");
            while(1)
            {
                scanf("%d",&m);
                if(m<=20&&m>=0)break;
                else
                {
                    system("cls");
                    printf("�������������Ŀ��Ŀ���Ϸ������������룺\n");
                }
            }
            printf("-----�������������һ��-----\n");
            getch();
            break;
        case 4:
            system("cls");
            printf("������Ů����Ŀ��Ŀ��\n");
            while(1)
            {
                scanf("%d",&w);
                if(w<=20&&w>=0)break;
                else
                {
                    system("cls");
                    printf("�������Ů����Ŀ��Ŀ���Ϸ������������룺\n");
                }
            }
            printf("-----�������������һ��-----\n");
            getch();
            break;
        case 5:
            system("cls");
            return;
            break;
        case 6:
            saveToFile();
            Sleep(1000);
            exit(0);
            break;
        }

        FILE* fp = fopen("setting.txt","w");
        if(fp==NULL)
        {
            printf("�ļ�δ�ɹ��򿪣�����\n");
            system("pause");
        }
        for(int i=0; i<m+w; i++)
        {
            fprintf(fp,"%d ",sports[i].award_num);
        }
        for(int i=m+w; i<50; i++)
        {
            fprintf(fp,"%d ",default_num);
        }
        fprintf(fp,"\n%d\n%d\n%d\n",n,m,w);
        fclose(fp);
    }
}

void InputName()///����ѧУ����Ŀ���Ʋ˵�
{
    int flag=0;
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t******************************************\n");
        printf("\t\t*                                        *\n");
        printf("\t\t*           1.����ѧУ����               *\n");
        printf("\t\t*           2.���������Ŀ����           *\n");
        printf("\t\t*           3.�������˵�                 *\n");
        printf("\t\t*           4.�˳�ϵͳ                   *\n");
        printf("\t\t*                                        *\n");
        printf("\t\t******************************************\n");
        if(flag==0)
            printf("������ѡ���Ӧ��ţ�\n");
        else printf("û���������ѡ����������룺\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
        case 1:
            system("cls");
            printf("�밴�ձ��˳������ѧУ���ƣ�\n");
            for(int i=0; i<n; i++)
            {
                printf("��� %d��",i+1);
                scanf("%s",schools[i].name);
            }
            printf("-----�������������һ��-----\n");
            saveToFile();
            getch();
            break;
        case 2:
            system("cls");
            printf("�밴�ձ��˳��������Ŀ���ƣ�\n");
            for(int i=0; i<m+w; i++)
            {
                if(i<m)
                {
                    printf("������Ŀ ��� %d��",i+1);
                    scanf("%s",sports[i].name);
                }
                else
                {
                    printf("Ů����Ŀ ��� %d��",i+1);
                    scanf("%s",sports[i].name);
                }
            }
            printf("-----�������������һ��-----\n");
            saveToFile();
            getch();
            break;
        case 3:
            system("cls");
            return;
            break;
        case 4:
            saveToFile();
            Sleep(1000);
            exit(0);
            break;
        default:
            flag=1;
        }
    }
}

void menu()///���˵��Ĳ���
{
    int flag = 0;
    while(1)
    {
        system("cls");
        printf("\n\n\n");
        printf("\t\t******************************************\n");
        printf("\t\t*                                        *\n");
        printf("\t\t*           1.������Ŀ�ɼ�               *\n");
        printf("\t\t*           2.�鿴ѧУ�ɼ�               *\n");
        printf("\t\t*           3.�鿴��Ŀ�ɼ�               *\n");
        printf("\t\t*           4.����ѧУ����Ŀ����         *\n");
        printf("\t\t*           5.����                       *\n");
        printf("\t\t*           6.�˳�                       *\n");
        printf("\t\t*                                        *\n");
        printf("\t\t******************************************\n");
        if(flag==0)
            printf("�������Ӧѡ��ı�ţ�\n");
        else printf("û���������ѡ����������룺\n");
        int option;
        scanf("%d",&option);
        switch(option)
        {
        case 1:
            inputScores();
            break;
        case 2:
            showSchool();
            break;
        case 3:
            showSports();
            break;
        case 4:
            InputName();
            break;
        case 5:
            setting();
            break;
        case 6:
            saveToFile();
            Sleep(1000);
            exit(0);
            break;
        default:
            flag=1;
        }
    }
}

int main()
{
    initialization();
    menu();
    return 0;
}
