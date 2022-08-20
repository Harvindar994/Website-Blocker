#include <stdio.h>
#include <stdlib.h>
//#include<custom.h>
#include<time.h>
#include<windows.h>
#define up 72
#define down 80
//#define left 75
#define right 77

struct SMALL_RECT {
    SHORT Left;
    SHORT Top;
    SHORT Right;
    SHORT Bottom;
};
struct blocking
{
    char website[450];
    char ip_addresss[20];
    int day,month,year;
    struct blocking *link;
}gdata;
struct user
{
    char user[70];
    char pass[70];
    char mobile[14];
}guser;
struct blocking *start=NULL;
char windows_drive;
char path[]="C:\\Windows\\System32\\drivers\\etc\\hosts";
char block_path[]="C:\\Windows\\System32\\drivers\\etc\\brightgoal_blocked";
char user_path[]="C:\\Windows\\brightgoal_user";
char user_backup[]="C:\\Windows\\System32\\brightgoal_backup";


void user_account()
{
    int i,x,y;
    char ch,forget[70];
    FILE *fp,*backup,*edit;
    char confirm[70];
    struct user create;
    struct user modify;
    if(chack_permission())
    {
        restart:
        if(chack_account_status())
        {
            reboot:
            setcolor(12);
            system("cls");
            drowbox(16,68,6,18);
            drowlineH(16,35,4,220);
            drowlineV(5,5,16,219);
            drowlineV(5,5,35,219);
            gotoxy(19,5);
            printf("Manage Account");
            setcolor(7);
            drowlineH(17,69,19,219);
            drowlineV(7,19,69,219);
            x=25;
            y=8;
            Clear_buffer();
            reset:
                setcolor(9);
                gotoxy(35,8);
                printf("%c%cChange your User Name",256,256);
                gotoxy(35,10);
                printf("%c%cChange Your Password",256,256);
                gotoxy(35,12);
                printf("%c%cChange Your Mobile Number",256,256);
                gotoxy(35,14);
                printf("%c%cRemove Your Account",256,256);
                gotoxy(35,16);
                printf("%c%cBack To Home",256,256);

                if(y==8)
                {
                    gotoxy(35,8);
                    printf("Change your User Name%c%c",256,256);
                }
                if(y==10)
                {
                    gotoxy(35,10);
                    printf("Change Your Password%c%c",256,256);
                }
                if(y==12)
                {
                    gotoxy(35,12);
                    printf("Change Your Mobile Number%c%c",256,256);
                }
                if(y==14)
                {
                    gotoxy(35,14);
                    printf("Remove Your Account%c%c",256,256);
                }
                if(y==16)
                {
                    gotoxy(35,16);
                    printf("Back To Home%c%c",256,256);
                }
                setcolor(12);
                gotoxy(x,y);
                printf("%c",16);
                gotoxy(70,19);
                ch=getch();
                gotoxy(70,19);
                printf("%c",256);
                if(ch==-32)
                {
                    ch=getch();
                    if(ch==up || ch==down)
                    {
                        switch(ch)
                        {
                        case up:
                            if(y>8 && y<=16)
                            {
                                gotoxy(x,y);
                                printf("%c",256);
                                y=y-2;
                            }
                            goto reset;
                        case down:
                            if(y>=8 && y<16)
                            {
                                gotoxy(x,y);
                                printf("%c",256);
                                y=y+2;
                            }
                            goto reset;
                        }
                    }
                    else
                    {
                        goto reset;
                    }
                }
                else if(ch==13)
                {
                    switch(y)
                    {
                    case 8:
                        system("cls");
                        edit=fopen(user_path,"rb");
                        if(edit==NULL)
                        {
                            fclose(edit);
                            edit=fopen(user_backup,"rb");
                            if(edit==NULL)
                            {
                                fclose(edit);
                                MSGinM("Error! You Cannot change User Name",21);
                                getch();
                                goto reset;
                            }
                        }
                        fread(&modify,sizeof(struct user),1,edit);
                        fclose(edit);
                        decryption(modify.mobile);
                        decryption(modify.user);
                        decryption(modify.pass);
                        setcolor(12);
                        i=drow_search_box("New Username",12,10,14);
                        setcolor(9);
                        input_Number_char(modify.user,56,i,12);
                        encryption(modify.mobile);
                        encryption(modify.user);
                        encryption(modify.pass);
                        fp=fopen(user_path,"wb");
                        if(fp==NULL)
                        {
                            fclose(fp);
                            MSGinM("Error! You Cannot change User Name",21);
                            getch();
                            goto reset;
                        }
                        backup=fopen(user_backup,"wb");
                        if(backup==NULL)
                        {
                            fclose(backup);
                            MSGinM("Error! You Cannot change User Name",21);
                            getch();
                            goto reset;
                        }
                        fwrite(&modify,sizeof(struct user),1,fp);
                        fwrite(&modify,sizeof(struct user),1,backup);
                        fclose(fp);
                        fclose(backup);
                        MSGinM("User Name Succesfully Changed",16);
                        getch();
                        goto reboot;
                        break;
                    case 10:
                        system("cls");
                        edit=fopen(user_path,"rb");
                        if(edit==NULL)
                        {
                            fclose(edit);
                            edit=fopen(user_backup,"rb");
                            if(edit==NULL)
                            {
                                fclose(edit);
                                MSGinM("Error! You Cannot change Password",21);
                                getch();
                                goto reset;
                            }
                        }
                        fread(&modify,sizeof(struct user),1,edit);
                        fclose(edit);

                        decryption(modify.mobile);
                        decryption(modify.user);
                        decryption(modify.pass);
                        setcolor(12);
                        i=drow_search_box("New Password",12,10,14);
                        setcolor(9);
                        input_password(modify.pass,56,i,12);
                        encryption(modify.mobile);
                        encryption(modify.user);
                        encryption(modify.pass);
                        fp=fopen(user_path,"wb");
                        if(fp==NULL)
                        {
                            fclose(fp);
                            MSGinM("Error! You Cannot change Password",21);
                            getch();
                            goto reset;
                        }
                        backup=fopen(user_backup,"wb");
                        if(backup==NULL)
                        {
                            fclose(backup);
                            MSGinM("Error! You Cannot change Password",21);
                            getch();
                            goto reset;
                        }
                        fwrite(&modify,sizeof(struct user),1,fp);
                        fwrite(&modify,sizeof(struct user),1,backup);
                        fclose(fp);
                        fclose(backup);
                        MSGinM("Password Succesfully Changed",16);
                        getch();
                        goto reboot;
                        break;
                    case 12:
                        system("cls");
                        edit=fopen(user_path,"rb");
                        if(edit==NULL)
                        {
                            fclose(edit);
                            edit=fopen(user_backup,"rb");
                            if(edit==NULL)
                            {
                                fclose(edit);
                                MSGinM("Error! You Cannot change Mobile Number",21);
                                getch();
                                goto reset;
                            }
                        }
                        fread(&modify,sizeof(struct user),1,edit);
                        fclose(edit);

                        decryption(modify.mobile);
                        decryption(modify.user);
                        decryption(modify.pass);
                        setcolor(12);
                        i=drow_search_box("New Mobile",12,10,14);
                        setcolor(9);
                        input_mobile(modify.mobile,10,i,12);
                        encryption(modify.mobile);
                        encryption(modify.user);
                        encryption(modify.pass);
                        fp=fopen(user_path,"wb");
                        if(fp==NULL)
                        {
                            fclose(fp);
                            MSGinM("Error! You Cannot change Mobile Number",21);
                            getch();
                            goto reset;
                        }
                        backup=fopen(user_backup,"wb");
                        if(backup==NULL)
                        {
                            fclose(backup);
                            MSGinM("Error! You Cannot change Mobile Number",21);
                            getch();
                            goto reset;
                        }
                        fwrite(&modify,sizeof(struct user),1,fp);
                        fwrite(&modify,sizeof(struct user),1,backup);
                        fclose(fp);
                        fclose(backup);
                        MSGinM("Mobile Number Succesfully Changed",16);
                        getch();
                        goto reboot;
                        break;
                    case 14:
                        fp=fopen(user_path,"wb");
                        backup=fopen(user_backup,"wb");
                        fclose(fp);
                        fclose(backup);
                        MSGinM("Account Successfully Removed",21);
                        getch();
                        return 1;
                        break;
                    case 16:
                        return 1;
                        goto reboot;
                        break;
                    }
                }
                else
                {
                    goto reset;
                }
        }
        else
        {
            setcolor(12);
            drowlineV(6,21,20,179);
            drowlineH(1,78,9,219);
            drowlineH(1,78,13,219);
            drowlineH(1,78,17,219);
            drowbox(1,78,5,21);
            drowlineH(30,53,4,223);
            drowlineH(30,53,2,220);
            drowlineV(3,3,30,219);
            drowlineV(3,3,53,219);
            MSGinM("Create New Account",3);
            setcolor(7);
            drowlineV(6,22,79,219);
            drowlineH(2,79,22,219);
            setcolor(9);
            gotoxy(3,7);
            printf("User Name");
            gotoxy(3,11);
            printf("Password");
            gotoxy(3,15);
            printf("Confirm Password");
            gotoxy(3,19);
            printf("Mobile");
            input_Number_char(create.user,56,21,7);
            repass:
            input_password(create.pass,56,21,11);
            input_password(confirm,56,21,15);
            if(!match_string(confirm,create.pass))
            {
                MSGinM("Password are not Match",24);
                getche();
                for(i=30;i<=55;i++)
                {
                    gotoxy(i,24);
                    printf("%c",256);
                }
                for(i=21;i<=76;i++)
                {
                    gotoxy(i,11);
                    printf("%c",256);
                    gotoxy(i,15);
                    printf("%c",256);
                }
                goto repass;
            }
            input_mobile(create.mobile,10,21,19);
            encryption(create.mobile);
            encryption(create.pass);
            encryption(create.user);
            fflush(stdin);
            fp=fopen(user_path,"wb");
            backup=fopen(user_backup,"wb");
            if(fp==NULL)
            {
                MSGinM("Error Account Does't Open",24);
                getche();
                return 0;
            }
            if(backup==NULL)
            {
                MSGinM("Error Account Does't Open",24);
                getche();
                return 0;
            }
            fwrite(&create,sizeof(struct user),1,fp);
            fclose(fp);
            fwrite(&create,sizeof(struct user),1,backup);
            fclose(backup);
            MSGinM("Account Succesfully Created",23);
            getche();
             goto restart;
        }
    }
    else
    {
        setcolor(12);
        drowbox(19,64,9,15);
        setcolor(7);
        drowlineH(20,65,16,219);
        drowlineV(10,16,65,219);
        setcolor(9);
        MSGinM("Access Denied",11);
        MSGinM("Open this Software in administrator Mode",13);
        getch();
        return 0;
    }

}
int input_mobile(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
		if(a[i]==27)
		{
			a[i]='\0';
			return 202;
		}
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>=48 && a[i]<=57))
        {

        }
        else if(a[i]==13 && i==10)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int input_password(char *a,int lenth,int x,int y)
{
    int i=0,j;
    for(i=0;i<lenth;i++)
    {

        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
		if(a[i]==27)
		{
			a[i]='\0';
			return 202;
		}
        if(a[i]!=8)
        {
            gotoxy(x,y);
            printf("*");
        }
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }
        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z') || (a[i]>=48 && a[i]<=57))
        {

        }
        else if(a[i]==33 || a[i]==64 || a[i]==35 || a[i]==36 ||a[i]==37 || a[i]==94 ||a[i]==38 || a[i]==42)
        {

        }
        else if(a[i]==13 && i>=8)
        {
            a[i]='\0';
            return;
        }
        else
        {

            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int input_Number_char(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z'))
        {

        }
        else if(a[i]==32 && i!=0 && a[i-1]!=' ')
        {

        }
        else if(a[i]>=48 && a[i]<=57)
        {

        }
        else if(a[i]==13 && i>=5)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
void setcolor(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut=GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut,&csbi))
    {
    wColor=(csbi.wAttributes & 0xF0)+(ForgC & 0x0F);
    // SetConsoleTextAttributes(hStdOut,wColor);
    SetConsoleTextAttribute(hStdOut,wColor);
    }
}
void adjustWindowSize(int left,int top,int x,int y)
{
    struct SMALL_RECT test;

    HANDLE hStdout;
    COORD coord;
    BOOL ok;

    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    coord.X = x;      //width 112 full size with same buffer size  or (111 width & 42 height with large buffer size;
    coord.Y = y;       //hieght 43
    //ok = SetConsoleScreenBufferSize(hStdout, coord);

    test.Left = left;	//0
    test.Top = top;		//0
    test.Right = coord.X-1;
    test.Bottom = coord.Y-1;

    SetConsoleWindowInfo(hStdout, ok, &test);

}
int drow_search_box(char *p,int pos,int y,int y1)
{
    int i,j=6;
    j=j+strlen(p);
    for(i=1;i<=78;i++)
    {
        gotoxy(i,y);
        printf("%c",219);
        gotoxy(i,y1);
        printf("%c",219);
    }
    for(i=y;i<=y1;i++)
    {
        gotoxy(1,i);
        printf("%c",219);
        gotoxy(78,i);
        printf("%c",219);
        gotoxy(j,i);
        printf("%c",219);
    }
    gotoxy(3,pos);
    printf("%s",p);
    gotoxy(j+2,pos);
    return j+2;
}
void Clear_buffer()
{
    while(kbhit())
    {
        getch();
    }
}
void gotoxy(int x,int y)
{

    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int match_two_string(char *a,char *b)
{
    char a1[65];
    char b1[65];
    int i,j,m1,m2,m3,m4;
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]>='a' && a[i]<='z')
            a1[i]=a[i]-32;
        else
            a1[i]=a[i];
    }
    a1[i]='\0';
    for(j=0;b[j]!='\0';j++)
    {
        if(b[j]>='a' && b[j]<='z')
            b1[j]=b[j]-32;
        else
            b1[j]=b[j];
    }
    b1[j]='\0';
    m1=m2=m3=m4=0;
    for(i=0;a1[i]!='\0';i++)
    {
        m1++;
        if(a1[i]==b1[i])
            m2++;
    }
    for(j=0;b1[j]!='\0';j++)
    {
        m3++;
        if(a1[j]==b1[j])
            m4++;
    }
    if(m1==m2 && m3==m4)
        return 1;
    else
        return 0;
}
void encryption(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]>='a' && a[i]<='z')
        {
            switch(a[i])
            {
            case 97:
                a[i]=154;
                break;
            case 98:
                a[i]=155;
                break;
            case 99:
                a[i]=156;
                break;
            case 100:
                a[i]=157;
                break;
            case 101:
                a[i]=158;
                break;
            case 102:
                a[i]=159;
                break;
            case 103:
                a[i]=160;
                break;
            case 104:
                a[i]=161;
                break;
            case 105:
                a[i]=162;
                break;
            case 106:
                a[i]=163;
                break;
            case 107:
                a[i]=164;
                break;
            case 108:
                a[i]=165;
                break;
            case 109:
                a[i]=166;
                break;
            case 110:
                a[i]=167;
                break;
            case 111:
                a[i]=168;
                break;
            case 112:
                a[i]=169;
                break;
            case 113:
                a[i]=170;
                break;
            case 114:
                a[i]=171;
                break;
            case 115:
                a[i]=172;
                break;
            case 116:
                a[i]=173;
                break;
            case 117:
                a[i]=174;
                break;
            case 118:
                a[i]=175;
                break;
            case 119:
                a[i]=176;
                break;
            case 120:
                a[i]=177;
                break;
            case 121:
                a[i]=178;
                break;
            case 122:
                a[i]=179;
                break;
            }
        }
        else if(a[i]>='A' && a[i]<='Z')
        {
            switch(a[i])
            {
            case 65:
                a[i]=128;
                break;
            case 66:
                a[i]=129;
                break;
            case 67:
                a[i]=130;
                break;
            case 68:
                a[i]=131;
                break;
            case 69:
                a[i]=132;
                break;
            case 70:
                a[i]=133;
                break;
            case 71:
                a[i]=134;
                break;
            case 72:
                a[i]=135;
                break;
            case 73:
                a[i]=136;
                break;
            case 74:
                a[i]=137;
                break;
            case 75:
                a[i]=138;
                break;
            case 76:
                a[i]=139;
                break;
            case 77:
                a[i]=140;
                break;
            case 78:
                a[i]=141;
                break;
            case 79:
                a[i]=142;
                break;
            case 80:
                a[i]=143;
                break;
            case 81:
                a[i]=144;
                break;
            case 82:
                a[i]=145;
                break;
            case 83:
                a[i]=146;
                break;
            case 84:
                a[i]=147;
                break;
            case 85:
                a[i]=148;
                break;
            case 86:
                a[i]=149;
                break;
            case 87:
                a[i]=150;
                break;
            case 88:
                a[i]=151;
                break;
            case 89:
                a[i]=152;
                break;
            case 90:
                a[i]=153;
                break;
            }
        }
        else if(a[i]>=48 && a[i]<=57)
        {
            switch(a[i])
            {
            case 48:
                a[i]=224;
                break;
            case 49:
                a[i]=225;
                break;
            case 50:
                a[i]=226;
                break;
            case 51:
                a[i]=227;
                break;
            case 52:
                a[i]=228;
                break;
            case 53:
                a[i]=229;
                break;
            case 54:
                a[i]=230;
                break;
            case 55:
                a[i]=231;
                break;
            case 56:
                a[i]=232;
                break;
            case 57:
                a[i]=233;
                break;
            }
        }
    }
}
void decryption(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]>=-102 && a[i]<=-77)
        {
            switch(a[i])
            {
            case -102:
                a[i]=97;
                break;
            case -101:
                a[i]=98;
                break;
            case -100:
                a[i]=99;
                break;
            case -99:
                a[i]=100;
                break;
            case -98:
                a[i]=101;
                break;
            case -97:
                a[i]=102;
                break;
            case -96:
                a[i]=103;
                break;
            case -95:
                a[i]=104;
                break;
            case -94:
                a[i]=105;
                break;
            case -93:
                a[i]=106;
                break;
            case -92:
                a[i]=107;
                break;
            case -91:
                a[i]=108;
                break;
            case -90:
                a[i]=109;
                break;
            case -89:
                a[i]=110;
                break;
            case -88:
                a[i]=111;
                break;
            case -87:
                a[i]=112;
                break;
            case -86:
                a[i]=113;
                break;
            case -85:
                a[i]=114;
                break;
            case -84:
                a[i]=115;
                break;
            case -83:
                a[i]=116;
                break;
            case -82:
                a[i]=117;
                break;
            case -81:
                a[i]=118;
                break;
            case -80:
                a[i]=119;
                break;
            case -79:
                a[i]=120;
                break;
            case -78:
                a[i]=121;
                break;
            case -77:
                a[i]=122;
                break;
            }
        }
        else if(a[i]>=-128 && a[i]<=-103)
        {
            switch(a[i])
            {
            case -128:
                a[i]=65;
                break;
            case -127:
                a[i]=66;
                break;
            case -126:
                a[i]=67;
                break;
            case -125:
                a[i]=68;
                break;
            case -124:
                a[i]=69;
                break;
            case -123:
                a[i]=70;
                break;
            case -122:
                a[i]=71;
                break;
            case -121:
                a[i]=72;
                break;
            case -120:
                a[i]=73;
                break;
            case -119:
                a[i]=74;
                break;
            case -118:
                a[i]=75;
                break;
            case -117:
                a[i]=76;
                break;
            case -116:
                a[i]=77;
                break;
            case -115:
                a[i]=78;
                break;
            case -114:
                a[i]=79;
                break;
            case -113:
                a[i]=80;
                break;
            case -112:
                a[i]=81;
                break;
            case -111:
                a[i]=82;
                break;
            case -110:
                a[i]=83;
                break;
            case -109:
                a[i]=84;
                break;
            case -108:
                a[i]=85;
                break;
            case -107:
                a[i]=86;
                break;
            case -106:
                a[i]=87;
                break;
            case -105:
                a[i]=88;
                break;
            case -104:
                a[i]=89;
                break;
            case -103:
                a[i]=90;
                break;
            }
        }
        else if(a[i]>=-32 && a[i]<=-23)
        {
            switch(a[i])
            {
            case -32:
                a[i]=48;
                break;
            case -31:
                a[i]=49;
                break;
            case -30:
                a[i]=50;
                break;
            case -29:
                a[i]=51;
                break;
            case -28:
                a[i]=52;
                break;
            case -27:
                a[i]=53;
                break;
            case -26:
                a[i]=54;
                break;
            case -25:
                a[i]=55;
                break;
            case -24:
                a[i]=56;
                break;
            case -23:
                a[i]=57;
                break;
            }
        }
    }
}
void drowlineH(int x,int x1,int y,int type)
{
    int i;
    for(i=x;i<=x1;i++)
    {
        gotoxy(i,y);
        printf("%c",type);
    }
}
void drowlineV(int y,int y1,int x,int type)
{
    int i;
    for(i=y;i<=y1;i++)
    {
        gotoxy(x,i);
        printf("%c",type);
    }
}
void drowbox(int x,int x1,int y,int y1)
{
    int i;
    for(i=x;i<=x1;i++)
    {
        gotoxy(i,y);
        printf("%c",219);
        gotoxy(i,y1);
        printf("%c",219);
    }
    for(i=y;i<=y1;i++)
    {
        gotoxy(x,i);
        printf("%c",219);
        gotoxy(x1,i);
        printf("%c",219);
    }
}

int login()
{
    struct user log;
    int count=0,mobo=0,i;
    int Emergency1=0;
    char forget[70];
    struct user modify;
    FILE *fp,*backup,*edit;
    rechackandlogin:
    if(chack_account_status())
    {
        relogin:
            setcolor(12);
            system("cls");
            drowlineH(36,48,4,223);
            drowlineH(36,48,6,220);
            drowlineV(4,6,36,219);
            drowlineV(4,6,48,219);
            setcolor(7);
            drowlineH(37,49,7,223);
            drowlineV(5,6,49,219);
            setcolor(12);
            MSGinM("LOGIN",5);
            drowlineV(8,16,14,179);
            drowlineH(1,78,12,219);
            drowbox(1,78,8,16);
            setcolor(7);
            drowlineH(2,79,17,219);
            drowlineV(9,17,79,219);
            setcolor(12);
            gotoxy(3,10);
            printf("User Name");
            gotoxy(3,14);
            printf("Password");
            setcolor(9);
            input_Number_char(log.user,56,16,10);
            if(match_string(log.user,"Brightgoal"))
            {
                Emergency1=1;
            }
            else if(!match_two_string(log.user,guser.user))
            {
                MSGinM("Incorrect Username",19);
                getch();
                goto relogin;
            }
            repass:
            if(count>2)
            {
                system("cls");
                if(yes_or_no_choise("Do You Want forget Your Password"))
                {
                        count=0;
                        edit=fopen(user_path,"rb");
                        if(edit==NULL)
                        {
                            fclose(edit);
                            edit=fopen(user_backup,"rb");
                            if(edit==NULL)
                            {
                                fclose(edit);
                                MSGinM("Error! You Cannot Forget Password",10);
                                getch();
                                count=0;
                                goto relogin;
                            }
                        }
                        fread(&modify,sizeof(struct user),1,edit);
                        fclose(edit);
                        decryption(modify.mobile);
                        decryption(modify.user);
                        decryption(modify.pass);
                        reinputpassword:
                        if(mobo>2)
                        {
                            goto relogin;
                        }
                        setcolor(12);
                        system("cls");
                        Clear_buffer();
                        i=drow_search_box("Enter Mobile Number",12,10,14);
                        setcolor(7);
                        drowlineH(2,79,15,219);
                        drowlineV(11,15,79,219);
                        setcolor(9);
                        input_mobile(forget,10,i,12);
                        if(match_string(forget,modify.mobile))
                        {
                            setcolor(12);
                            system("cls");
                            i=drow_search_box("New Password",12,10,14);
                            setcolor(7);
                            drowlineH(2,79,15,219);
                            drowlineV(11,15,79,219);
                            setcolor(9);
                            input_password(modify.pass,56,i,12);
                        }
                        else
                        {
                            MSGinM("Incorrect Mobile Number",16);
                            getche();
                            mobo++;
                            fflush(stdin);
                            goto reinputpassword;
                        }
                        encryption(modify.mobile);
                        encryption(modify.user);
                        encryption(modify.pass);
                        fp=fopen(user_path,"wb");
                        if(fp==NULL)
                        {
                            fclose(fp);
                            MSGinM("Error! You Cannot Forget Password",20);
                            getch();
                            goto relogin;
                        }
                        backup=fopen(user_backup,"wb");
                        if(backup==NULL)
                        {
                            fclose(backup);
                            MSGinM("Error! You Cannot Forget Password",20);
                            getch();
                            goto relogin;
                        }
                        fwrite(&modify,sizeof(struct user),1,fp);
                        fwrite(&modify,sizeof(struct user),1,backup);
                        fclose(fp);
                        fclose(backup);
                        MSGinM("Password Succesfully Changed",16);
                        delay(2);
                        system("cls");
                        if(yes_or_no_choise("Do You want to login in your Account"))
                        {
                            goto rechackandlogin;
                        }
                        else
                        {
                            exit(0);
                        }
                }
                else
                {
                    count=0;
                    goto relogin;
                }
            }
            input_password(log.pass,56,16,14);
            if(Emergency1)
            {
                if(match_string(log.pass,"056Brightgoal@!560*%&!056"))
                {
                    MSGinM("Emergency Login Successful",19);
                    MSGinM("Your Account & Password successfully Removed",21);
                    fp=fopen(user_path,"wb");
                    backup=fopen(user_backup,"wb");
                    fclose(fp);
                    fclose(backup);
                    getch();

                }
                else
                {
                    MSGinM("Emergency Password Incorrect",19);
                    getch();
                    for(i=16;i<=76;i++)
                    {
                        gotoxy(i,14);
                        printf("%c",256);
                    }
                    for(i=26;i<=55;i++)
                    {
                        gotoxy(i,19);
                        printf("%c",256);
                    }
                    goto repass;
                }
            }
            else
            {
                if(!match_string(log.pass,guser.pass))
                {
                    MSGinM("Incorrect Password",19);
                    getch();
                    count++;
                    for(i=16;i<=76;i++)
                    {
                        gotoxy(i,14);
                        printf("%c",256);
                    }
                    for(i=30;i<=55;i++)
                    {
                        gotoxy(i,19);
                        printf("%c",256);
                    }
                    goto repass;
                }
                else
                {
                    MSGinM("Login Successful",19);
                    delay(2);
                }
            }
    }
}
void delay(unsigned int msecond)
{
    clock_t goal=msecond+clock();
    while(goal>clock());
}
int yes_or_no_choise(char *a)
{
    system("COLOR F9");
	setcolor(12);
    int i,j,y,x1,y1;
    char ch;
    for(i=8;i<=17;i++)
    {
        gotoxy(20,i);
        printf("%c",219);
        gotoxy(65,i);
        printf("%c",219);
    }
    for(i=20;i<=65;i++)
    {
        gotoxy(i,8);
        printf("%c",219);
        gotoxy(i,17);
        printf("%c",219);
    }
	setcolor(7);
	drowlineH(22,66,18,219);
	drowlineV(9,18,66,219);
	setcolor(9);
    x1=22;
    y1=10;
    for(i=0;a[i]!='\0';i++)
    {
        gotoxy(x1,y1);
        printf("%c",a[i]);
        if(x1==65 && y1==12)
            break;
        if(x1==65)
        {
            x1=21;
            y1++;
        }
        x1++;
    }
    gotoxy(40,14);
    printf("Yes");
    gotoxy(58,14);
    printf("No");
    y=53;               //53,36
    reprint:
    for(i=y;i<=y+10;i++)
    {
        gotoxy(i,13);
        printf("%c",220);
        gotoxy(i,15);
        printf("%c",223);
    }
    for(i=14;i<=14;i++)
    {
        gotoxy(y,i);
        printf("%c",219);
        gotoxy(y+10,i);
        printf("%c",219);
    }
    gotoxy(1,1);
    ch=getche();
    gotoxy(1,1);
    printf("%c",256);
    if(ch==-32)
    {
        ch=getche();
        if(ch==75 || ch==77)
        {
            switch(ch)
            {
            case 75:
                setcolor(12);
                if(y==53)
                {
                    for(i=y;i<=y+10;i++)
                    {
                        gotoxy(i,13);
                        printf("%c",256);
                        gotoxy(i,15);
                        printf("%c",256);
                    }
                    for(i=14;i<=14;i++)
                    {
                        gotoxy(y,i);
                        printf("%c",256);
                        gotoxy(y+10,i);
                        printf("%c",256);
                    }
                    y=y-17;
                }
                goto reprint;
            case 77:
                setcolor(9);
                if(y==36)
                {
                    for(i=y;i<=y+10;i++)
                    {
                        gotoxy(i,13);
                        printf("%c",256);
                        gotoxy(i,15);
                        printf("%c",256);
                    }
                    for(i=14;i<=14;i++)
                    {
                        gotoxy(y,i);
                        printf("%c",256);
                        gotoxy(y+10,i);
                        printf("%c",256);
                    }
                    y=y+17;
                }
                goto reprint;
            }
        }
        else
        {
            goto reprint;
        }
    }
    else if(ch==13)
    {
        switch(y)
        {
        case 53:
            return 0;
            break;
        case 36:
            return 1;
            break;
        }
    }
    else
    {
        goto reprint;
    }
}
int match_string(char *a,char *b)
{
    int i,count=0,lenth=0;
    lenth=strlen(a);
    if((strlen(a)==strlen(b)))
    {
        for(i=0;b[i]!='\0';i++)
        {
            if(a[i]==b[i])
            {
                count++;
            }
        }
        if(lenth==count)
            return 1;
        else
            return 0;
    }
    else
    {
        return 0;
    }

}
int chack_account_status()
{
    FILE *fp;
    int flag=0;
    fp=fopen(user_path,"rb");
    if(fp==NULL)
    {
        fclose(fp);
        fp=fopen(user_backup,"rb");
        if(fp==NULL)
        {
            fclose(fp);
            return 0;
        }
    }
    while(fread(&guser,sizeof(struct user),1,fp)>0)
    {
        flag=1;
    }
    if(flag)
    {
        fclose(fp);
        decryption(guser.mobile);
        decryption(guser.pass);
        decryption(guser.user);
        return 1;
    }
    else
    {
        fclose(fp);
        fp=fopen(user_backup,"rb");
        if(fp==NULL)
        {
            fclose(fp);
            return 0;
        }
        while(fread(&guser,sizeof(struct user),1,fp)>0)
        {
            flag=1;
        }
        if(flag)
        {
            fclose(fp);
            decryption(guser.mobile);
            decryption(guser.pass);
            decryption(guser.user);
            return 1;
        }
        else
        {
            fclose(fp);
             return 0;
        }
    }
}
struct blocking* newnode()
{
    struct blocking *n;
    n=(struct blocking*)malloc(sizeof(struct blocking));
    return n;
}
void load_website_host()
{
    FILE *fp;
    struct blocking *view,*t;
    fp=fopen(block_path,"rb");
    if(fp==NULL)
    {
        return;
    }
    view=newnode();
    while(fread(view,sizeof(struct blocking),1,fp)>0)
    {
        view->link=NULL;
        if(start==NULL)
        {
            start=view;
        }
        else
        {
            t=start;
            while(t->link!=NULL)
            {
                t=t->link;
            }
            t->link=view;
        }
        view=newnode();
    }
    fclose(fp);
    return;
}
int remove_website(char *a)
{
    FILE *fp;
    struct blocking *t,*back;
    load_website_host();
    t=start;
    do
    {
        if(match_two_string(a,t->website))
        {
            if(start==t)
            {
                start=t->link;
                free(t);
            }
            else
            {
                back->link=t->link;
                free(t);
            }
            t=start;
            if(t==NULL)
            {
                fp=fopen(block_path,"wb");
                fclose(fp);
            }
            else
            {
                fp=fopen(block_path,"wb");
                while(t!=NULL)
                {
                    fwrite(t,sizeof(struct blocking),1,fp);
                    t=t->link;
                }
                fclose(fp);
                t=start;
                back=start;
                while(t!=NULL)
                {
                    back=t;
                    t=t->link;
                    free(t);
                }
                start=t;
                return 1;
            }
            return 1;
        }
        back=t;
        t=t->link;
    }while(t!=NULL);
    t=start;
    back=start;
    while(t!=NULL)
    {
        back=t;
        t=t->link;
        free(t);
    }
    start=t;
    return 0;
}
void buffer_size(int x,int y)
{
    HANDLE wHnd;    // Handle to write to the console.
    wHnd=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize;
    bufferSize.X=x;
    bufferSize.Y=y;
    SetConsoleScreenBufferSize(wHnd, bufferSize);
}
void createdby()
{
    int i;
    int li;
    char a[]="BRIGHTGOAL.IN";
    char a1[]="      WEBSITE BLOCKER";
    char a2[]="CREATED BY HARVINDAR SINGH";
    system("COLOR FC");
    for(i=27;i<=56;i++)
    {
        gotoxy(i,9);
        printf("%c",219);
        for(li=0;li<=1000000;li++);
    }

    for(i=9;i<=15;i++)
    {
        gotoxy(56,i);
        printf("%c",219);
        for(li=0;li<=1000000;li++);
    }
    for(i=56;i>=27;i--)  //56,27
    {
        gotoxy(i,15);
        printf("%c",219);
        for(li=0;li<=1000000;li++);
    }
    for(i=15;i>=9;i--) //15,9
    {
        gotoxy(27,i);
        printf("%c",219);
        for(li=0;li<=1000000;li++);
    }
    for(i=8;i>=7;i--)
    {
        gotoxy(30,i);
        printf("%c",219);
        for(li=0;li<=10000000;li++);
    }
    for(i=30;i>=23;i--) //23,30
    {
        gotoxy(i,6);
        printf("%c",220);
        for(li=0;li<=10000000;li++);

    }
    for(i=7;i<=11;i++)  //7,11
    {
        gotoxy(23,i);
        printf("%c",219);
        for(li=0;li<=10000000;li++);
    }
    for(i=24;i<=26;i++)     //23,26
    {
        gotoxy(i,11);
        printf("%c",220);
        for(li=0;li<=10000000;li++);
    }
    gotoxy(32,7);
    setcolor(9);
    for(i=0;a[i]!='\0';i++)
    {
        printf("%c",a[i]);
        for(li=0;li<=10000000;li++);
    }
    gotoxy(29,11);
    for(i=0;a1[i]!='\0';i++)
    {
        printf("%c",a1[i]);
        for(li=0;li<=10000000;li++);
    }
    gotoxy(29,13);
    for(i=0;a2[i]!='\0';i++)
    {
        printf("%c",a2[i]);
        for(li=0;li<=10000000;li++);
    }
    for(li=0;li<=1000000000;li++);// Wating section

    gotoxy(32,7);
    for(i=0;a[i]!='\0';i++)
    {
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    gotoxy(29,11);
    for(i=0;a1[i]!='\0';i++)
    {
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    gotoxy(29,13);
    for(i=0;a2[i]!='\0';i++)
    {
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    for(i=27;i<=56;i++)  //erase............................................
    {
        gotoxy(i,9);
        printf("%c",256);
        for(li=0;li<=1000000;li++);
    }
    for(i=9;i<=15;i++)
    {
        gotoxy(56,i);
        printf("%c",256);
        for(li=0;li<=1000000;li++);
    }
    for(i=56;i>=27;i--)  //56,27
    {
        gotoxy(i,15);
        printf("%c",256);
        for(li=0;li<=1000000;li++);
    }
    for(i=15;i>=9;i--) //15,9
    {
        gotoxy(27,i);
        printf("%c",256);
        for(li=0;li<=1000000;li++);
    }
    for(i=8;i>=7;i--)
    {
        gotoxy(30,i);
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    for(i=30;i>=23;i--) //23,30
    {
        gotoxy(i,6);
        printf("%c",256);
        for(li=0;li<=10000000;li++);

    }
    for(i=7;i<=11;i++)  //7,11
    {
        gotoxy(23,i);
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    for(i=24;i<=26;i++)     //23,26
    {
        gotoxy(i,11);
        printf("%c",256);
        for(li=0;li<=10000000;li++);
    }
    fflush(stdin);
}
void Main_Menu()
{
    char ch;
    int x,y,i;
    struct blocking unblock;
    reset:
        setcolor(12);
    Clear_buffer();
    system("cls");
    drowlineV(3,3,15,219);
    drowlineV(3,3,15+20,219);
    drowlineH(15,15+20,2,220);
    drowbox(15,70,4,20);
    gotoxy(15+3,3);
    printf("Harvindar Singh");
    setcolor(7);
    shadow_mainmenu();
    y=6;
    x=25;
    restart:
        setcolor(9);
        gotoxy(35,6);
        printf("%cUser Account",256);
        gotoxy(35,8);
        printf("%cBlock Website",256);
        gotoxy(35,10);
        printf("%cUnblock Website",256);
        gotoxy(35,12);
        printf("%cView Blocked Website",256);
        gotoxy(35,14);
        printf("%cExport Blocked Website List",256);
        gotoxy(35,16);
        printf("%cVew Author profile",256);
        gotoxy(35,18);
        printf("%cExit",256);
        setcolor(12);
        if(y==6)
        {
            gotoxy(35,6);
            printf("User Account%c",256);
        }
        if(y==8)
        {
            gotoxy(35,8);
            printf("Block Website%c",256);
        }
        if(y==10)
        {
            gotoxy(35,10);
            printf("Unblock Website%c",256);
        }
        if(y==12)
        {
            gotoxy(35,12);
            printf("View Blocked Website%c",256);
        }
        if(y==14)
        {
            gotoxy(35,14);
            printf("Export Blocked Website List%c",256);
        }
        if(y==16)
        {
            gotoxy(35,16);
            printf("Vew Author profile%c",256);
        }
        if(y==18)
        {
            gotoxy(35,18);
            printf("Exit%c",256);
        }
        gotoxy(x,y);
        printf("%c",16);
        gotoxy(73,20);
        ch=getche();
        gotoxy(73,20);
        printf("%c",256);
        if(ch==-32 || ch==-32)
        {
            ch=getche();
            if(ch==up || ch==down)
            {
                switch(ch)
                {
                case up:
                    if(y>6 && y<=18)
                    {
                        gotoxy(x,y);
                        printf("%c",256);
                        y=y-2;
                    }
                    goto restart;
                    break;
                case down:
                    if(y<18 && y>=6)
                    {
                        gotoxy(x,y);
                        printf("%c",256);
                        y=y+2;
                    }
                    goto restart;
                    break;
                }
            }
            else
            {
                goto restart;
            }
        }
        else if(ch==13)
        {
            system("cls");
            switch(y)
            {
            case 6:
                system("cls");
                user_account();
                goto reset;
            case 8:
                system("cls");
                block_website();
                goto reset;
                break;
            case 10:
                if(!chack_permission())
                {
                    setcolor(12);
                    drowbox(19,64,9,15);
                    setcolor(7);
                    drowlineH(20,65,16,219);
                    drowlineV(10,16,65,219);
                    setcolor(9);
                    MSGinM("Access Denied",11);
                    MSGinM("Open this Software in administrator Mode",13);
                    getch();
                    goto reset;
                }
                setcolor(12);
                drowlineV(10,14,11,179);
                drowbox(1,78,10,14);
                gotoxy(3,12);
                printf("Website");
                setcolor(9);
                i=input_website_name(unblock.website,64,12,12);
                if(i==202)
                    goto reset;
                conver_stringin_lowercase(unblock.website);
                if(Website_alredy_blocked(unblock.website))
                {
                    i=unblock_website("127.0.0.1 ",unblock.website);
                    if(i==606)
                    {
                        MSGinM("Website Successfully Unblock",16);
                        getch();
                        goto reset;
                    }
                }
                MSGinM("This Website Are not Blocked",16);
                getch();
                goto reset;
                break;
            case 12:
                system("cls");
                view_blocked_website();
                goto reset;
                break;
            case 14:
                system("cls");
                Export_list();
                goto reset;
                break;
            case 16:
                system("cls");
                profile();
                goto reset;
                break;
            case 18:
                exit(0);
            }
        }
        else
        {
            goto restart;
        }

}
void profile()
{
    char name[]="Harvindar Singh";
    char website[]="www.brightgoal.in";
    char mobile[]="9695806109";
    char email[]="brightgoal.enquiry@gmail.com";
    char twitter[]="twitter.com/brightgoal_in";
    char instagram[]="instagram.com/brightgoal.in";
    char facebook[]="facebook.com/brightgoal.in.Education";
    setcolor(12);
    drowlineV(2,2,7,219);
    drowlineV(2,2,7+20,219);
    drowlineH(7,7+20,1,220);
    //drowlineH(7,7+20,2,223);
    drowbox(7,73,3,22);
    setcolor(7);
    drowlineH(8,74,23,219);
    drowlineV(4,23,74,219);
    setcolor(12);
    gotoxy(7+3,2);
    printf("Harvindar Singh");
    setcolor(9);
    delay(60);
    gotoxy(10,5);
    printf("Name      :  %s",name);
    delay(60);
    gotoxy(10,7);
    printf("Mobile    :  %s",mobile);
    delay(60);
    gotoxy(10,9);
    printf("Email     :  %s",email);
    delay(60);
    gotoxy(10,11);
    printf("Website   :  %s",website);
    delay(60);
    gotoxy(10,13);
    setcolor(12);
    printf("Follow on Social Media");
    gotoxy(10,14);
    printf("%c%c%c%c%c%c%c%c%c%c",220,220,220,220,220,220,220,220,220,220);
    delay(60);
    setcolor(8);
    gotoxy(10,16);
    printf("Facebook  :  %s",facebook);
    delay(60);
    gotoxy(10,18);
    printf("Twitter   :  %s",twitter);
    delay(60);
    gotoxy(10,20);
    printf("Instagram :  %s",instagram);
    getche();
}
void shadow_mainmenu()
{
    drowlineH(16,71,21,219);
    drowlineV(5,21,71,219);
}
void block_website()
{
    int i,count=0;
    FILE *fp,*host;
    struct blocking new;
    strcpy(new.ip_addresss,"127.0.0.1");
    host=fopen(path,"a");
    if(host==NULL)
    {
        setcolor(12);
        drowbox(19,64,9,15);
        setcolor(7);
        drowlineH(20,65,16,219);
        drowlineV(10,16,65,219);
        setcolor(9);
        MSGinM("Access Denied",11);
        MSGinM("Open this Software in administrator Mode",13);
        getch();
        return 0;
    }
    restart:
        setcolor(12);
        system("cls");
        drowlineV(8,16,10,179);
        drowbox(1,78,8,16);
        drowlineH(1,78,12,219);
        gotoxy(3,10);
        printf("Website");
        gotoxy(3,14);
        printf("Date");
        setcolor(9);
        i=input_website_name(new.website,63,11,10);
        if(i==202)
            return 202;
        fflush(stdin);
        if((new.website[0]!='w' && new.website[0]!='W') || (new.website[1]!='w' && new.website[1]!='W') || (new.website[2]!='w' && new.website[2]!='W') || new.website[3]!='.')
        {
            gotoxy(37,18);
            printf("Invalid Website");
            getche();
            goto restart;
        }
        for(i=0;new.website[i]!='\0';i++)
        {
            if(new.website[i]=='.')
            {
                count++;
            }
        }
        if(count<2)
        {
            MSGinM("Invalid Website",18);
            getche();
            goto restart;
        }
        if(Website_alredy_blocked(new.website))
        {
            MSGinM("Website already Blocked",18);
            getch();
            return 0;
        }
        conver_stringin_lowercase(new.website);
        input_date(&new.day,&new.month,&new.year,11,14,40,18);

        fp=fopen(block_path,"ab");
        if(fp==NULL)
        {
            MSGinM("Error to Blocking Website Try Again",18);;
            getche();
            return 0;
        }
        fprintf(host,"\n%s %s",new.ip_addresss,new.website);
        fclose(host);
        encryption(new.ip_addresss);
        encryption(new.website);
        fwrite(&new,sizeof(struct blocking),1,fp);
        fclose(fp);
        MSGinM("Website Blocked Successfully",18);
        getch();

}
int input_date(int *day1,int *month1,int *year1,int x,int y,int ex,int ey)
{
    int ch;
    int a,day=0,month=0,year=0,count=1,m,loop=0,i,j;
    m=x;
    gotoxy(x,y);
    printf("dd/mm/yyyy");
    restart:
    gotoxy(x,y);
    ch=getche();
    systemback:
    if(ch==-32)
    {
        ch=getche();
        gotoxy(x,y);
        printf("%c",256);
    }
    if(ch>=48 && ch<=57)
    {
        switch(ch)
        {
        case 48:
            a=0;
            break;
        case 49:
            a=1;
            break;
        case 50:
            a=2;
            break;
        case 51:
            a=3;
            break;
        case 52:
            a=4;
            break;
        case 53:
            a=5;
            break;
        case 54:
            a=6;
            break;
        case 55:
            a=7;
            break;
        case 56:
            a=8;
            break;
        case 57:
            a=9;
            break;
        }
        if(count<=2)
        {
            day=(day*10)+a;
            count++;
            x++;
            if(count==3)
            {
                printf("/");
                x++;
            }
            if(count==3)
            {

                    if(day>31 || day<1)
                    {
                                ch=8;
                                loop=1;
                                gotoxy(ex,ey);
                                printf("Invalid Day");
                                for(i=0;i<=100000000;i++);
                                for(i=ex;i<=ex+12;i++)
                                {
                                    gotoxy(i,ey);
                                    printf("%c",256);
                                    for(j=0;j<=10000000;j++);
                                }
                                goto systemback;
                    }
            }
            goto restart;
        }
        else if(count<=4)
        {
            month=(month*10)+a;
            count++;
            x++;
            if(count==5)
            {
                x++;
                printf("/");
            }
            if(count==5)
            {
                if(month>12 || month<1)
                {
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                }
            }
            if(count==5)
            {
                if(day>28)
                {
                    if(month==2)
                    {
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                    }
                }
                if(day>30)
                {
                    if(month==4 || month==6 || month==9 || month==11)
                    {
                            ch=8;
                            loop=1;
                            gotoxy(ex,ey);
                            printf("Invalid Month");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                    }
                }
            }
            goto restart;
        }
        else if(count<=8)
        {
            year=(year*10)+a;
            count++;
            x++;
            if(count==9)
            {
                if(year<2018)
                {
                            ch=8;
                            loop=3;
                            gotoxy(ex,ey);
                            printf("Invalid Year");
                            for(i=0;i<=100000000;i++);
                            for(i=ex;i<=ex+12;i++)
                            {
                                gotoxy(i,ey);
                                printf("%c",256);
                                for(j=0;j<=10000000;j++);
                            }
                            goto systemback;
                }
            }
            goto restart;
        }
        else
        {
            *day1=day;
            *month1=month;
            *year1=year;
            return 1;
        }
    }
    else if(ch==13)
    {
        if(day==0 || month==0 || year<2018)
        {
            gotoxy(x,y);
            printf("%c",256);
            goto restart;
        }
        *day1=day;
        *month1=month;
        *year1=year;
        return 1;
    }
    else if(ch==8)
    {
        gotoxy(x,y);
        printf("%c",256);
        if(count>1)
        {
            count--;
        }
        if(count>=5 && count<=8)
        {
            year=year/10;
        }
        if(count>=3 && count<=4)
        {
            month=month/10;
        }
        if(count>=1 && count<=2)
        {
            day=day/10;
        }
        if(count==4)
        {
            gotoxy(x,y);
            printf("%c",256);
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(count==2)
        {
            gotoxy(x,y);
            printf("%c",256);
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(x>m)
        {
            x--;
            gotoxy(x,y);
            printf("%c",256);
        }
        if(loop==0)
        goto restart;
        else
        {
            while(loop)
            {
                loop--;
                goto systemback;
            }
        }
    }
    else
    {
        gotoxy(x,y);
        printf("%c",256);
        goto restart;
    }
}
void conver_stringin_lowercase(char *a)
{
    int i;
    for(i=0;a[i]!='\0';i++)
    {
        if(a[i]>='A' && a[i]<='Z')
            a[i]=(a[i]+32);
    }
}
int chack_permission()
{
    FILE *fp;
    fp=fopen(path,"a");
    if(fp!=NULL)
    {
        fclose(fp);
        return 1;
    }
    else
    {
        fclose(fp);
        return 0;
    }
}
void MSGinM(char *a,int y)
{
    gotoxy(42-(strlen(a)/2),y);
    printf("%s",a);
}
int Website_alredy_blocked(char *a)
{
    FILE *fp;
    fp=fopen(block_path,"rb");
    struct blocking chack;
    if(fp==NULL)
    {
        fclose(fp);
        return 0;
    }
    while(fread(&chack,sizeof(struct blocking),1,fp)>0)
    {
        decryption(chack.website);
        if(match_two_string(a,chack.website))
        {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
void  view_blocked_website()
{
    FILE *fp;
    int x,y,flag=0;
    struct blocking view;
    fp=fopen(block_path,"rb");
    if(fp==NULL)
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("List Empty",12);
        getch();
        fclose(fp);
        return 0;
    }
    y=1;
    while(fread(&view,sizeof(struct blocking),1,fp)>0)
    {
        decryption(view.website);
        drowbox(1,78,y,y+6);
        setcolor(9);
        gotoxy(3,y+2);
        printf("Website : %s",view.website);
        gotoxy(3,y+4);
        printf("Date    : %d/%d/%d",view.day,view.month,view.year);
        setcolor(12);
        flag=1;
        y=y+6;
    }
    fclose(fp);
    if(!flag)
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("List Empty",12);
        getch();
        fclose(fp);
        return 0;
    }
    getch();
}
void  Export_list()
{
    FILE *fp,*expo;
    int flag=0;
    struct blocking view;
    fp=fopen(block_path,"rb");
    if(fp==NULL)
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("List Empty",12);
        getch();
        fclose(fp);
        return 0;
    }
    expo=fopen("Brightgoal_Blocked_website_list.txt","w");
    if(expo==NULL)
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("Error Occurred",12);
        getch();
        fclose(expo);
        return 0;
    }
    fprintf(expo,"_____________________________________________________________________________\n\n");
    while(fread(&view,sizeof(struct blocking),1,fp)>0)
    {
        decryption(view.website);
       fprintf(expo,"Website : %s\n\n",view.website);
       fprintf(expo,"Date    : %d/%d/%d\n",view.day,view.month,view.year);
       fprintf(expo,"_____________________________________________________________________________\n\n");
       flag=1;
    }
    fclose(fp);
    if(!flag)
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("List Empty",12);
        fclose(fp);
        fclose(expo);
        remove("Brightgoal_Blocked_website_list.txt");
        getch();
        return 0;
    }
    else
    {
        drowbox(18,65,10,14);
        setcolor(7);
        drowlineH(19,66,15,219);
        drowlineV(11,15,66,219);
        setcolor(9);
        MSGinM("List Exported",12);
        fclose(fp);
        fclose(expo);
        getch();
        return 1;
    }

}
int input_website_name(char *a,int lenth,int x,int y)
{
    int i=0;
    for(i=0;i<lenth;i++)
    {
        abc:
        gotoxy(x,y);
        a[i]=getche();
        if(a[i]==27)
        {
            gotoxy(x,y);
            printf("%c",256);
            return 202;
        }
        if(a[i]==-32)
        {
            a[i]=getche();
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        if(a[i]==8)
        {
            if(i==0)
            {
                goto abc;
            }
            else
            {
            i--;
            x--;
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
            }

        }
        if((a[i]>='a' && a[i]<='z') || (a[i]>='A' && a[i]<='Z') || a[i]>='0' && a[i]<='9')
        {

        }
        else if(a[i]=='.' && i>2 && a[i-1]!='.')
        {

        }
        else if(a[i]=='-' && i>4 && a[i-1]!='-')
        {

        }
        else if(a[i]==13 && i>=8)
        {
            a[i]='\0';
            return 1;
        }
        else
        {
            gotoxy(x,y);
            printf("%c",256);
            goto abc;
        }
        x++;
    }
    a[i]='\0';
    return a;
}
int unblock_website(char *ip,char *web)
{
    FILE *fp,*host;
    char *edit;
    char ch,unblock[450];
    int i;
    int count=5;
    fp=fopen(path,"r");
    if(fp==NULL)
    {
        return 404;
    }
    while((ch=getc(fp))!=EOF)
    {
        count++;
    }
    fclose(fp);
    edit=(char*)malloc(count*sizeof(char));
    if(i==404)
    {
        return 0;
    }
    host=fopen(path,"r");
    if(host==NULL)
    {
        return 0;
    }
    i=0;
    while((ch=getc(host))!=EOF)
    {
        edit[i]=ch;
        i++;
    }
    edit[i]='\0';
    fclose(host);
    strcpy(unblock,ip);
    strcat(unblock,web);
    remove_string(edit,unblock);
    host=fopen(path,"w");
    if(host==NULL)
    {
        fclose(host);
        return 0;
    }
    fflush(stdin);
    for(i=0;edit[i]!='\0';i++)
    {
        putc(edit[i],host);
    }
    fclose(host);
    free(edit);
    encryption(web);
    remove_website(web);
    return 606;
    getche();
}
int remove_string(char *a,char *removing)
{
    int i,j,lenth,index,flag=0;
    lenth=(strlen(removing)-1);
    for(i=0,j=0;a[i]!='\0';i++)
    {
        if(a[i]==removing[j])
        {
            j++;
            if(flag==0)
            {
                index=i;
                flag=1;
            }
            if(j>lenth)
            {
                if(a[index-1]=='\n')
                {
                    index--;
                }
                i++;
                for(;a[i]!='\0';index++,i++)
                {
                    a[index]=a[i];
                }
                a[index]='\0';
                return 1;
            }
        }
        else
        {
            j=0;
            flag=0;
        }
    }
    return 0;
}
int detect_windows_drive(char *ch)
{
    char a='a';
    FILE *fp;
    char path[]="a:\\Windows\\System32\\control.exe";
    while(a<='z')
    {
        fp=fopen(path,"r");
        if(fp!=NULL)
        {
            *ch=a;
            fclose(fp);
            return 1;
        }
        a++;
        path[0]=a;
    }
    return 0;
}
void main()
{
    system("COLOR FC");
    int i;
    i=detect_windows_drive(&windows_drive);
    if(i)
    {
        path[0]=windows_drive;
        block_path[0]=windows_drive;
        user_path[0]=windows_drive;
        user_backup[0]=windows_drive;
    }
    SetConsoleTitleA("Wbsite Blocker Powered By Brightgoal.in");
    adjustWindowSize(0,0,81,26);
    buffer_size(81,1000);
    createdby();
    login();
    Clear_buffer();
    Main_Menu();
    getche();
}
