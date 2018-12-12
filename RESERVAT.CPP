#include<fstream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<process.h>
#include<dos.h>
#include<stdlib.h>
#include<iostream.h>
#include<time.h>

const int MAX_HDR=25,FLD_SIZE=10,MAX_REC_COUNT=50,FILE_NAME_LEN=20;
char gUserId[FLD_SIZE];

class service
{
 public:
  void strintcat(char str[],int num,int numpos)
  {
   char nm[80];
   int l,i=0,r=0,q=num;
   l=strlen(str);
   do
   {
     r=q%10;
     q/=10;
     nm[i]=r+'0';
     i++;
   }while(q!=0);
   nm[i]='\0';
   strrev(nm);

   if(numpos==2)
     strcat(str,nm);
   else
   {
     strcat(nm,str);
     strcpy(str,nm);
   }
  }

  void genUniqueId(char idTxt[FLD_SIZE])
  {
    int i;
    long lid;

    lid=time(0);
    i=0;
    while (lid!=0)
    {
     idTxt[i]='A'+lid%26;
     lid=lid/26;
     i++;
    }
    idTxt[i]='\0';
    strrev(idTxt);
//    cout<<idTxt;
//    getch();
  }
  void pickDate(char title[], int &daysAfter, int daysCount, char strDate[FLD_SIZE])
  {
    int i, day, month, year, days, oDaysAfter;
    time_t now;
    struct tm *aTime;
    char option[MAX_REC_COUNT][80];

    oDaysAfter=daysAfter;
    days=daysAfter+daysCount;
    i=0;
    for (;daysAfter<days;daysAfter++)
    {
//      cout<<";i:"<<i<<";daysAfter:"<<daysAfter<<";days:"<<days;

      now = time(0)+daysAfter*86400;
      struct tm *aTime =localtime(&now);
      day = aTime->tm_mday;
      month=aTime->tm_mon+1;
      year = aTime->tm_year+1900;

      if (day<10)
	strcpy(strDate,"0");
      else
	strcpy(strDate,"");
      strintcat(strDate,day,2);
      if (month<10)
	strcat(strDate,"/0");
      else
	strcat(strDate,"/");
      strintcat(strDate,month,2);
      strcat(strDate,"/");
      strintcat(strDate,year%100,2);

      if (daysCount==1)
      {
//	cout<<";daysCount:"<<daysCount;
//	getch();
	break;
      }

      strcpy(option[i],strDate);

      i++;
      if ((i%15==0)||(daysAfter==(days-1)))
      {
	  strcpy(option[i],"More options...");
	  strcpy(option[i+1],"");

	  int ch;
	  clrscr();
	  ch=menu(0, title,option,0);//menu("Please pick a date");
	  if (ch==(i+1))
	  {
	    if (daysAfter==(days-1))
	    {
	       i=0;
	       daysAfter=oDaysAfter-1;
	       continue;
	    }
	    else
	    {
	       i=0;
	       continue;
	    }
	  }
	  else
	  {
	   daysAfter=ch-1;
	   strcpy(strDate,option[ch-1]);
	   break;
	  }
      }
    }

//    getch();
    /*
    //Long format Date
    now = time(0);
    for (i=0;i<days;i++)
    {
      now = time(0)+i*86400;
      cout<<ctime(&now);
      strcpy(dtList[i],ctime(&now));
      cout<<";dtList[i]:"<<dtList[i];
    }
    getch();
    */

    return;
  }


  void getUniqueStr(char strIn[MAX_REC_COUNT][FLD_SIZE], char strOut[MAX_REC_COUNT][FLD_SIZE])
  {
    int i, f, cStr1=0, cStr2=0;
    while (strlen(strIn[cStr1])>0)
    {
      f=0;
      for (i=0, i<cStr2;i++)
      {
	if (strcmp(strIn[cStr1],strOut[i])==0)
	{
	  f=1;
	  break;
	}
	if (f==0)
	{
	  strcpy(strOut[cStr2],strIn[cStr1]);
	  cStr2++;
	}
      }
      cStr1++;
    }
    strcpy(strOut[cStr2], "");
  }


  void waitMsg(char msg[])
  {
    gotoxy(20,40);
    cout<<msg;
    delay(400);
    cout<<".";
    delay(400);
    cout<<".";
    delay(400);
    cout<<".";
    delay(400);
    cout<<".";
    delay(400);
    cout<<".";
    delay(800);
  }

  void cputsMsg(char msg[])
  {
	   clrscr();
	   gotoxy(38,10);
	   textcolor(CYAN);
	   cputs(msg);
	   cout<<endl;
	   gotoxy(27,12);
	   textbackground(CYAN);
	   for(int q=0; q<30; q++)
	  {
	    cputs(" ");
	    delay(90);
	  }
	  textcolor(WHITE);
	  textbackground(BLACK);

  }

  void getsfn(char n[]) //gets function
  {
    int i=0;
    char ch;
    while(ch!=13 && i<50)
    {
     ch=getch();
     cout<<ch;
     n[i]=ch;
     i++;

    }
    n[i]='\0';
  }

  int getpassword(char password[20])
  {
   char ch;
   int i = 0;
   ch = getch();

   while(ch!=13 && i<20)
   {
     password[i]=ch;
     i++;
     cout<<'*';
     ch=getch();

   }
   password[i]='\0';
   return 1;
  }

  void getAlphaInput(int x, int y, char inpTxt[FLD_SIZE])
  {
   char ch;
   int i = 0,lx=x,ly=y,ich;

   gotoxy(lx, ly);
   ich=ch = getch();
   while(((ch!=13)||(i==0)) && (i<(FLD_SIZE-1)))
   {
     if (ch>='a' && ch<='z')
	ch='A'+ ch -'a';
     if (ch>='A' && ch<='Z')
     {
      inpTxt[i]=ch;
      lx++;
      i++;
      cout<<ch;
     }
     else if ((ich==8)&&(i>0))
     {
	i--;
	lx--;
	gotoxy(lx,ly);
	cout<<" ";
	gotoxy(lx,ly);
     }

     ich=ch=getch();
//     cout<<ich;
   }
   inpTxt[i]='\0';
  }

  int getNumericInput(int x, int y, int numDigits, char inpTxt[FLD_SIZE])
  {
   char ch;
   int i = 0, num=0,lx=x,ly=y,ich;

   gotoxy(lx, ly);

   ich=ch = getch();

   while(ch!=13 && i<numDigits)
   {
     if (ch>='0' && ch<='9')
     {
      inpTxt[i]=ch;
      num=num*10+ch-'0';
      lx++;
      i++;
      cout<<ch;
     }
     else if ((ich==8)&&(i>0))
     {
	i--;
	lx--;
	gotoxy(lx,ly);
	cout<<" ";
	gotoxy(lx,ly);
	num=num/10;
     }
     ich=ch=getch();

   }
   inpTxt[i]='\0';
//   cout<<inpTxt;
   return num;
  }


  int getFieldIdx(char keyTxt[FLD_SIZE], char fileH[MAX_HDR][FLD_SIZE])
  {
   int j=0,f=0;

   while (strlen(fileH[j])>0)
   {
    if (strcmpi(keyTxt,fileH[j])==0)
    {
     f=1;
     break;
    }
    else
      j++;
   }
   if (f==0)
   {
    cout<<"\nError finding the Field Index";
    return -1;
   }
   else
    return j;
  }

  void readFileH(char fileName[FILE_NAME_LEN], char fileH[MAX_HDR][FLD_SIZE])
  {
   fstream bH(fileName,ios::in);//declaration
   int j=0;

   while (!bH.eof() && bH!=0)
   {
     bH.getline(fileH[j],'\n');
     j++;
   }
   strcpy(fileH[j],"");
   bH.close();
   return;
  }


  int getKeys4KeyFileD(char fileName[FILE_NAME_LEN], char keyTxt[FLD_SIZE], char keyVal[FLD_SIZE], char fileH[MAX_HDR][FLD_SIZE], char retKeyTxt[FLD_SIZE], char retKeyVal[MAX_REC_COUNT][FLD_SIZE])
  {
   int  j=0,f=0,keyIdx, retKeyIdx, retKeyValCount=-1,l_max_hdr=0;
   char tmpKeyVal[FLD_SIZE], tmpRetKeyVal[FLD_SIZE], tmpTxt[FLD_SIZE];

   while (strlen(fileH[l_max_hdr])>0)
     l_max_hdr++;

   keyIdx=getFieldIdx(keyTxt, fileH);
   retKeyIdx=getFieldIdx(retKeyTxt, fileH);

   fstream bD(fileName,ios::in);//declaration

//   cout<<";l_max_hdr:"<<l_max_hdr<<";kId:"<<keyIdx<<";rKId:"<<retKeyIdx;
   while (!bD.eof() && bD!=0)
   {
     f=0;
     strcpy(tmpRetKeyVal,"");
     for (j=0;j<l_max_hdr;j++)
     {
      bD.getline(tmpKeyVal,'\n');
//      if (strcmp(keyVal,"MAA")==0)
//	 cout<<";tKV:"<<tmpKeyVal;
      if (j==keyIdx)
      {
//	cout<<";kV:"<<keyVal<<";tKV:"<<tmpKeyVal;

	if (strcmpi(keyVal, tmpKeyVal)==0)
	  f=1;
      }
      else if (j==retKeyIdx)
      {
	strcpy(tmpRetKeyVal,tmpKeyVal);

//	cout<<";tRKV:"<<tmpRetKeyVal;
//	getch();
      }
     }

     if (f==1)
     {
       retKeyValCount++;
       strcpy(retKeyVal[retKeyValCount], tmpRetKeyVal);
//       cout<<";kV:"<<keyVal<<";tRKV:"<<tmpRetKeyVal<<";C:"<<retKeyValCount;
//       getch();
     }
   }
   bD.close();

   if (retKeyValCount>=0)
   {
     retKeyValCount++;
     strcpy(retKeyVal[retKeyValCount], "");
   }
   else
   {
     cout<<"\nNo record found:"<<keyVal;
     getch();
   }

   return retKeyValCount;
  }

  int getKeys4KeysFileD(char fileName[FILE_NAME_LEN], char keyTxt[MAX_REC_COUNT][FLD_SIZE], char keyVal[MAX_REC_COUNT][FLD_SIZE], char fileH[MAX_HDR][FLD_SIZE], char retKeyTxt[FLD_SIZE], char retKeyVal[MAX_REC_COUNT][FLD_SIZE])
  {
   int  l_max_key_txt=0,j=0,k,f=0,keyIdx[MAX_REC_COUNT], retKeyIdx, retKeyValCount=-1,l_max_hdr=0;
   char tmpKeyVal[FLD_SIZE], tmpRetKeyVal[FLD_SIZE], tmpTxt[FLD_SIZE];
   char tmpFileD[MAX_HDR][FLD_SIZE];

   while (strlen(fileH[l_max_hdr])>0)
     l_max_hdr++;

   while (strlen(keyTxt[l_max_key_txt])>0)
      l_max_key_txt++;

   for (k=0;k<l_max_key_txt;k++)
      keyIdx[k]=getFieldIdx(keyTxt[k], fileH);

   retKeyIdx=getFieldIdx(retKeyTxt, fileH);

   fstream bD(fileName,ios::in);//declaration

//   cout<<";l_max_hdr:"<<l_max_hdr<<";kId:"<<keyIdx<<";rKId:"<<retKeyIdx;
   while (!bD.eof() && bD!=0)
   {
     f=0;
     strcpy(tmpRetKeyVal,"");

     for (j=0;j<l_max_hdr;j++)
       bD.getline(tmpFileD[j],'\n');

     for (k=0;k<l_max_key_txt;k++)
     {
      if (strcmpi(tmpFileD[getFieldIdx(keyTxt[k], fileH)],keyVal[k])==0)
	f++;
      else
	break;
     }
     if (f==l_max_key_txt)
     {
       int duplicate=0;
       for (j=0;j<=retKeyValCount;j++)
	 if (strcmp(retKeyVal[retKeyValCount], tmpFileD[retKeyIdx])==0)
	 {
	   duplicate=1;
	   break;
	 }
       if (duplicate==0)
       {
	 retKeyValCount++;
	 strcpy(retKeyVal[retKeyValCount], tmpFileD[retKeyIdx]);
       }
     }

   }
   bD.close();

   if (retKeyValCount>=0)
   {
     retKeyValCount++;
     strcpy(retKeyVal[retKeyValCount], "");
   }
   else
   {
     cout<<"\nNo record found:"<<keyVal[0];
     getch();
   }

   return retKeyValCount;
  }

  int getKeyVals4KeyTxtFileD(char fileName[FILE_NAME_LEN], char keyTxt[FLD_SIZE], char fileH[MAX_HDR][FLD_SIZE], char keyVal[MAX_REC_COUNT][FLD_SIZE])
  {
   int  j=0,k,f=0,keyIdx, keyValCount=-1,l_max_hdr=0;
   char tmpKeyVal[FLD_SIZE], tmpRetKeyTxt[FLD_SIZE], tmpTxt[FLD_SIZE];

   while (strlen(fileH[l_max_hdr])>0)
     l_max_hdr++;

   keyIdx=getFieldIdx(keyTxt, fileH);

   fstream bD(fileName,ios::in);//declaration

   while (!bD.eof() && bD!=0)
   {
     f=0;
     for (j=0;j<l_max_hdr;j++)
     {
      bD.getline(tmpKeyVal,'\n');
      if (j==keyIdx)
      {
	f=0;
	for (k=0;k<=keyValCount;k++)
	  if (strcmpi(tmpKeyVal, keyVal[k])==0)
	  {
	     f=1;
	     break;
	  }
	if (f==0)
	{
	  keyValCount++;
	  strcpy(keyVal[keyValCount], tmpKeyVal);
	}
      }//End of if
     }//End of For
   }//End of While
   bD.close();

   keyValCount++;
   strcpy(keyVal[keyValCount], "");

   return keyValCount;
  }//End of Function

  int readInput4FileD(char fileH[MAX_HDR][FLD_SIZE], char fileD[MAX_HDR][FLD_SIZE])
  {
   int i=0,j=0,l_max_hdr=0;
   char tmpFileD[MAX_HDR][FLD_SIZE];

   while (strlen(fileH[l_max_hdr])>0)
      l_max_hdr++;
   for (j=0;j<l_max_hdr;j++)
       getline(fileD[j],'\n');

  }

  int readFileD(char fileName[FILE_NAME_LEN], char keyTxt[MAX_HDR][FLD_SIZE], char keyVal[MAX_HDR][FLD_SIZE], char fileH[MAX_HDR][FLD_SIZE], char fileD[MAX_HDR][FLD_SIZE])
  {
   int recPosition=-1,i=0,j=0,k=0,f=0,l_max_hdr=0,l_max_key_txt=0;
   char tmpFileD[MAX_HDR][FLD_SIZE];

   while (strlen(fileH[l_max_hdr])>0)
      l_max_hdr++;

   while (strlen(keyTxt[l_max_key_txt])>0)
      l_max_key_txt++;

   fstream bD(fileName,ios::in);//declaration

   while (!bD.eof() && bD!=0)
   {
     for (j=0;j<l_max_hdr;j++)
       bD.getline(tmpFileD[j],'\n');
     for (k=0;k<l_max_key_txt;k++)
     {
      if (strcmpi(tmpFileD[getFieldIdx(keyTxt[k], fileH)],keyVal[k])==0)
	f++;
      else
	break;
     }
     if (f==l_max_key_txt)
     {
       for (j=0;j<l_max_hdr;j++)
	 strcpy(fileD[j],tmpFileD[j]);

       break;
     }
     i++;
   }

   bD.close();

   if(f==l_max_key_txt)
    recPosition=i;
   else
    recPosition=-1;
   return recPosition;
  }

  int writeFileD(char fileName[FILE_NAME_LEN], char fileH[MAX_HDR][FLD_SIZE], char fileD[MAX_HDR][FLD_SIZE])
  {
   int recPosition=-1,i=0,j=0,f=0,maxsize=-1;
   char tmpFileD[MAX_HDR][FLD_SIZE];

   fstream bDi(fileName,ios::in);//declaration
   if (!bDi.eof() && bDi!=0)
     recPosition=0;

   ofstream bD(fileName,ios::app);//declaration

   if(recPosition==0)
      bD<<'\n';

   j=0;
   while (strlen(fileD[j])>0)
   {
    if (strlen(fileD[j+1])==0)
       bD<<fileD[j];
    else
       bD<<fileD[j]<<'\n';
    j++;
   }

   maxsize++;
   bD.close();
   return maxsize;
  }


  void coutXY(int X, int Y, char msg[80], int clrEOL)
  {
    int i,len,max;
    if ((X>=1) && (X<=80) && (Y>=1) && (Y<=25))
    {
      gotoxy(X, Y);
      cputs(msg);
      if (clrEOL == 1)
      {
	len = strlen(msg);
	max=80-X+1-len;
	for (i=0; i<max;i++)
	  cout<<" ";
      }
    }
  }

  int charcmpcust(char ch1,char ch2,int igncase)
  {
    char chi1, chi2;
    int ichi1, ichi2;

    chi1=ch1;
    chi2=ch2;
    if(igncase==1)
    {
      if (chi1>='a'&&chi1<='z')
	chi1='A'+chi1-'a';

      if (chi2>='a'&&chi2<='z')
	chi2='A'+chi2-'a';
    }

    ichi1=chi1;
    ichi2=chi2;

    if(ichi1>ichi2)
      return 1;
    else if(ichi1<ichi2)
      return (-1);
    else
      return 0;
  }

  int menu(int info,char title[],char option[MAX_REC_COUNT][80],int seqno)
  {
   int const TITLE_Y=3,OPTION_Y=TITLE_Y+3;
   int move,nextOptionPos,maxOption,s,ich,i,j,f,ff,title_x,option_x[MAX_REC_COUNT];
   int opc,currOptionPos=0,min_x,max_x,min_y,max_y;
   char ch,txt[MAX_REC_COUNT][80], txtseq[80];
   title_x=(80-strlen(title))/2;
   min_x=title_x;
   max_x=title_x+strlen(title)-1;
   min_y=TITLE_Y;

   textbackground(RED);
   coutXY(title_x,TITLE_Y,title,0);
   textbackground(BLACK);

   do
   {
    if (seqno==0)
    {
     option_x[currOptionPos]=(80-strlen(option[currOptionPos]))/2;
     strcpy(txt[currOptionPos],option[currOptionPos]);
    }
    else
    {
     option_x[currOptionPos]=title_x-20;
     strcpy(txtseq,". ");
     strintcat(txtseq,currOptionPos+1,1);
     strcat(txtseq,option[currOptionPos]);
     strcpy(txt[currOptionPos],txtseq);
    }
    coutXY(option_x[currOptionPos],OPTION_Y+currOptionPos,txt[currOptionPos],0);
    if (min_x>option_x[currOptionPos])
      min_x= option_x[currOptionPos];
    if (max_x<(option_x[currOptionPos]+strlen(txt[currOptionPos])-1))
      max_x=option_x[currOptionPos]+strlen(txt[currOptionPos])-1;
    max_y=OPTION_Y+currOptionPos;
    currOptionPos++;

   } while(strlen(option[currOptionPos]) != 0);

   maxOption=currOptionPos;

   textbackground(BLACK);
   textcolor(WHITE);

   if (info==1)
   {
    textbackground(WHITE);
    textcolor(BLACK);
    coutXY((80-4)/2,OPTION_Y+maxOption+1,"Go Back",0);
    textbackground(BLACK);
    textcolor(WHITE);

    return 0;
   }
   currOptionPos=0;
   textbackground(WHITE);
   textcolor(BLACK);
   coutXY(option_x[currOptionPos],OPTION_Y+currOptionPos,txt[currOptionPos],0);
   textbackground(BLACK);
   textcolor(WHITE);

   while(1==1)
   {
    move=0;
    nextOptionPos=-1;
    if(kbhit())
    {
     ich=ch = getch();
     //ich=ch;

     if (ich==0)
     {
      s=1;
      ch=getch();
      ich=ch;
     }
     else
      s=0;

     if (s==1)
     {
      if ((ich==75)||(ich==72)||(ich==15)) //LeftArrow:075; UpArrow:072; Shift+Tab:15;
      {
       move=1;
       if (currOptionPos>0)
	nextOptionPos=currOptionPos-1;
       else
	nextOptionPos=maxOption-1;
      }
      else if ((ich==77)||(ich==80)) //RtArrow:077; DownArrow:080
      {
       move=1;
       if (currOptionPos<(maxOption-1))
	nextOptionPos=currOptionPos+1;
       else
	nextOptionPos=0;
      }
     } //end of if s==1
     else
     {
      if (ich==9) //Tab:9
      {
       move=1;
       if (currOptionPos<(maxOption-1))
	nextOptionPos=currOptionPos+1;
       else
	nextOptionPos=0;
      }
      else if (ich==13) //Return:013
      {
       return (currOptionPos+1);
      }
      else if ((ich-'0'>0) && ((ich-'0')<=maxOption))
      {
       move=1;
       nextOptionPos=ich-'0'-1;
      }
      else if (((ich>='A')&&(ich<='Z'))||((ch>>'a')&&(ch<='z')))
      {
       ff=0;
       for (i=currOptionPos+1;i<maxOption;i++)
	if (charcmpcust(option[i][0],ich,1)==0)
	{
	  ff=1;
	  break;
	}
       if (ff==0)
	for (i=0;i<currOptionPos;i++)
	 if (charcmpcust(option[i][0],ich,1)==0)
	 {
	   ff=1;
	   break;
	 }
       if (ff==1)
       {
	move=1;
	nextOptionPos=i;
       }
      }
     } //part of s==1 condition

    }

    if (move==1)
    {
      textbackground(BLACK);
      textcolor(WHITE);
      coutXY(option_x[currOptionPos],OPTION_Y+currOptionPos,txt[currOptionPos],0);

      currOptionPos = nextOptionPos;

      textbackground(WHITE);
      textcolor(BLACK);
      coutXY(option_x[currOptionPos],OPTION_Y+currOptionPos,txt[currOptionPos],0);

      textbackground(BLACK);
      textcolor(WHITE);
    }
   }

  // return (currOptionPos+1);
  }

};//End of class generic

class flight
{
 service svc;

 public:

  void getFlightStatus()
  {
   char fltNum[FLD_SIZE],dtDep[FLD_SIZE],fltStsH[MAX_HDR][FLD_SIZE], fltStsD[MAX_HDR][FLD_SIZE];
   int i,j,f=0,recPosition,pnr_count,ch;
   char fileName[FILE_NAME_LEN],keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE];

   strcpy(fileName, "fltStsH.txt");
   svc.readFileH(fileName, fltStsH);

   strcpy(keyTxt[0],"FLTNUM");
   cout<<"Enter your flight number:\t";
   gets(keyVal[0]);

   strcpy(keyTxt[1],"DTDEP");
   cout<<"\nEnter your date of flight:\t";
   gets(keyVal[1]);

   strcpy(keyTxt[2],"");
   strcpy(keyVal[2],"");

   strcpy(fileName, "fltStsD.txt");

   recPosition=svc.readFileD(fileName, keyTxt, keyVal, fltStsH, fltStsD);
   if(recPosition==-1)
   {
       cout<<"No record Found\n";
       getch();
   }
   else
   {
       cout<<"\nFlight Status is: "<<fltStsD[svc.getFieldIdx("FLTSTATUS", fltStsH)];
       getch();
   }
   return;
  }
};

class booking
{
 public:

  void getSourceCity(char sourceCity[FLD_SIZE])
  {
   service svc;
   char fltH[MAX_HDR][FLD_SIZE], fltD[MAX_HDR][FLD_SIZE];
   char cityH[MAX_HDR][FLD_SIZE], cityD[MAX_HDR][FLD_SIZE];

   int i,j,f=0,recPosition,sourceCityCount,ch;
   char fileName[20], sourceCityCode[MAX_REC_COUNT][FLD_SIZE],sourceCityName[MAX_REC_COUNT][FLD_SIZE];
   char keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE],lSourceCity[FLD_SIZE];

   strcpy(fileName, "fltH.txt");
   svc.readFileH(fileName, fltH);
   strcpy(fileName, "fltD.txt");

   sourceCityCount=svc.getKeyVals4KeyTxtFileD(fileName, "Source", fltH, sourceCityCode);

   i=0;
   while (strlen(sourceCityCode[i])>0)
   {
//     cout<<";"<<sourceCityCode[i];
     i++;
   }

//   getch();

   strcpy(fileName, "cityH.txt");
   svc.readFileH(fileName, cityH);

   strcpy(fileName, "cityD.txt");


   char option[MAX_REC_COUNT][80];

   i=0;
   while (strlen(sourceCityCode[i])>0)
   {
     strcpy(keyTxt[0],"CityCode");
     strcpy(keyVal[0],sourceCityCode[i]);
     strcpy(keyTxt[1],"");
     strcpy(keyVal[1],"");

//     svc.getKeys4KeyFileD(fileName, "CityCode", sourceCityCode[i], cityH, "CityName", sourceCityName);
     svc.getKeys4KeysFileD(fileName, keyTxt, keyVal, cityH, "CityName", sourceCityName);
//     cout<<";WsSC:"<<sourceCityCode[i]<<";WsSN:"<<sourceCityName[0];

     strcpy(option[i],sourceCityCode[i]);
     strcat(option[i]," - ");
     strcat(option[i],sourceCityName[0]);
     i++;
   }

   strcpy(option[i],"");   
   clrscr();
   ch=svc.menu(0, "Booking -> Select Departing Airport/ City",option,0);


//   cout<<"\n\t1> Enter Airport code or City Name ";
   strcpy(sourceCity,sourceCityCode[ch-1]);
   return;
  }

  void getDestCity(char sourceCityCode[FLD_SIZE], char destCity[FLD_SIZE])
  {
   service svc;
   char fltH[MAX_HDR][FLD_SIZE], fltD[MAX_HDR][FLD_SIZE];
   char cityH[MAX_HDR][FLD_SIZE], cityD[MAX_HDR][FLD_SIZE];

   int i,j,f=0,recPosition,destCityCount,ch;
   char fileName[20], destCityCode[MAX_REC_COUNT][FLD_SIZE],destCityName[MAX_REC_COUNT][FLD_SIZE];
   char keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE],lDestCity[FLD_SIZE];

   strcpy(fileName, "fltH.txt");
   svc.readFileH(fileName, fltH);
   strcpy(fileName, "fltD.txt");

   strcpy(keyTxt[0],"Source");
   strcpy(keyVal[0],sourceCityCode);
   strcpy(keyTxt[1],"");
   strcpy(keyVal[1],"");

//   destCityCount=svc.getKeys4KeyFileD(fileName, "Source", sourceCityCode, fltH, "DEST", destCityCode);
   destCityCount=svc.getKeys4KeysFileD(fileName, keyTxt, keyVal, fltH, "DEST", destCityCode);


   i=0;
   while (strlen(destCityCode[i])>0)
   {
//     cout<<";"<<destCityCode[i];
     i++;
   }

//   getch();
//
   strcpy(fileName, "cityH.txt");
   svc.readFileH(fileName, cityH);

   strcpy(fileName, "cityD.txt");

   char option[MAX_REC_COUNT][80];

   i=0;
   while (strlen(destCityCode[i])>0)
   {
     strcpy(keyTxt[0],"CityCode");
     strcpy(keyVal[0],destCityCode[i]);
     strcpy(keyTxt[1],"");
     strcpy(keyVal[1],"");

//     svc.getKeys4KeyFileD(fileName, "CityCode", destCityCode[i], cityH, "CityName", destCityName);
     svc.getKeys4KeysFileD(fileName, keyTxt, keyVal, cityH, "CityName", destCityName);
//     cout<<";WdSC:"<<destCityCode[i]<<";WdSN:"<<destCityName[0];
     strcpy(option[i],destCityCode[i]);
     strcat(option[i]," - ");
     strcat(option[i],destCityName[0]);
     i++;
   }

   strcpy(option[i],"");
   clrscr();

   ch=svc.menu(0, "Booking -> Select Arrival Airport/ City",option,0);


//   cout<<"\n\t1> Enter Airport code or City Name ";
   strcpy(destCity,destCityCode[ch-1]);

   return;
  }

  void getFltNum(char sourceCityCode[FLD_SIZE], char destCityCode[FLD_SIZE], char fltNum[FLD_SIZE], char tmDep[FLD_SIZE], char depTerm[FLD_SIZE], char tmArr[FLD_SIZE])
  {
   service svc;
   char fltH[MAX_HDR][FLD_SIZE], fltD[MAX_HDR][FLD_SIZE];

   int i,j,f=0,recPosition,fltNumCount,ch;
   char fileName[20], fltNumList[MAX_REC_COUNT][FLD_SIZE];
   char keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE],lFltNum[FLD_SIZE];

   strcpy(fileName, "fltH.txt");
   svc.readFileH(fileName, fltH);
   strcpy(fileName, "fltD.txt");

   strcpy(keyTxt[0],"Source");
   strcpy(keyVal[0],sourceCityCode);
   strcpy(keyTxt[1],"Dest");
   strcpy(keyVal[1],destCityCode);

   strcpy(keyTxt[2],"");
   strcpy(keyVal[2],"");

   fltNumCount=svc.getKeys4KeysFileD(fileName, keyTxt, keyVal, fltH, "FLTNUM", fltNumList);

   i=0;
   while (strlen(fltNumList[i])>0)
   {
//     cout<<";"<<fltNumList[i];
     i++;
   }


   char option[MAX_REC_COUNT][80];

   if (fltNumCount>0)
     for (i=0; i<fltNumCount;i++)
     {
      strcpy(keyTxt[0],"FLTNUM");
      strcpy(keyVal[0],fltNumList[i]);
      strcpy(keyTxt[1],"");
      strcpy(keyVal[1],"");
      recPosition=svc.readFileD(fileName, keyTxt, keyVal, fltH, fltD);
      if(recPosition==-1)
       cout<<"No record Found\n";
      else
      {
//       printFlt(fltH, fltD);

//       strcpy(option[i],fltNumList[i]);
       strcpy(option[i],fltD[0]);
       strcat(option[i]," ");
       strcat(option[i],fltD[1]);
       strcat(option[i]," ");
       strcat(option[i],fltD[2]);
       strcat(option[i]," ");
       strcat(option[i],fltD[3]);
       strcat(option[i]," ");
       strcat(option[i],fltD[4]);
       strcat(option[i]," ");
       strcat(option[i],fltD[6]);
       /*
       */
//       cout<<"Record "<<i+1<<" of "<<fltNumCount;
//       getch();
      }
     }

     strcpy(option[i],"");
     clrscr();
     ch=svc.menu(0, "Booking -> <SRC DEST FLT# TmDep DTerm TmArr>",option,0);

//   cout<<"\n\t1> Enter Flight Num ";

     strcpy(fltNum,fltNumList[ch-1]);

     strcpy(keyTxt[0],"FLTNUM");
     strcpy(keyVal[0],fltNum);
     strcpy(keyTxt[1],"");
     strcpy(keyVal[1],"");
     recPosition=svc.readFileD(fileName, keyTxt, keyVal, fltH, fltD);
     if(recPosition==-1)
       cout<<"No record Found\n";
     else
     {
       strcpy(tmDep,fltD[3]);
       strcpy(depTerm,fltD[4]);
       strcpy(tmArr,fltD[6]);
     }

     return;
  }

  void printPNR(char bookingH[MAX_HDR][FLD_SIZE], char bookingD[MAX_HDR][FLD_SIZE])
  {
     service svc;
     const int ETKT_X=12, ETKT_Y=8;

     clrscr();
     textcolor(BLACK);
     textbackground(WHITE);
     gotoxy(ETKT_X,ETKT_Y);
     cputs("CV Airline  >-|--                                       ");
     gotoxy(ETKT_X,ETKT_Y+1);
     cputs("eTicket Itinerary/ Receipt                              ");
     gotoxy(ETKT_X,ETKT_Y+2);
     cputs("Date of Issue: ");
     cputs(bookingD[svc.getFieldIdx("DTISSUE", bookingH)]);
     cputs("                                 ");
     gotoxy(ETKT_X,ETKT_Y+3);
     cputs("Booking Reference (PNR): ");
     cputs(bookingD[svc.getFieldIdx("PNR", bookingH)]);
     cputs("       ");
     cputs("eTicket#:  ");
     cputs(bookingD[svc.getFieldIdx("ETKTNUM", bookingH)]);
     gotoxy(ETKT_X,ETKT_Y+4);
     cputs("Passenger Name: ");
     cputs(bookingD[svc.getFieldIdx("FNAME", bookingH)]);
     cputs(" ");
     cputs(bookingD[svc.getFieldIdx("LNAME", bookingH)]);
     cputs("             Class:");
     cputs(bookingD[svc.getFieldIdx("CLASS", bookingH)]);

     gotoxy(ETKT_X,ETKT_Y+5);
     cout<<"Dep Date\tTime\tFrom\tTo\tFlt#\tTerminal";
     gotoxy(ETKT_X,ETKT_Y+6);
     cout<<bookingD[svc.getFieldIdx("DTDEP1", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("TMDEP1", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("SOURCE", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("DEST", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("FLTNUM1", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("DEPTERM1", bookingH)];
     if (strcmp(bookingD[svc.getFieldIdx("OW_RT", bookingH)],"RT")==0)
     {
      gotoxy(ETKT_X,ETKT_Y+7);
      cout<<bookingD[svc.getFieldIdx("DTDEP2", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("TMDEP2", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("DEST", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("SOURCE", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("FLTNUM2", bookingH)]<<'\t'<<bookingD[svc.getFieldIdx("DEPTERM2", bookingH)];
     }
     gotoxy(ETKT_X,ETKT_Y+8);
     cputs("Please press enter to send eTicket to customer...       ");
     gotoxy(ETKT_X,ETKT_Y+9);
     textcolor(WHITE);
     textbackground(BLACK);
  }

  void printstat()
  {
   service svc;
   char pnrTxt[FLD_SIZE],bookingH[MAX_HDR][FLD_SIZE], bookingD[MAX_HDR][FLD_SIZE];
   int i,j,f=0,recPosition,pnr_count,ch;
   const int ETKT_X=12, ETKT_Y=8;
   char fileName[20], userId[FLD_SIZE], pnr[MAX_REC_COUNT][FLD_SIZE];
   char keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE];

   strcpy(fileName, "bookingH.txt");
   svc.readFileH(fileName, bookingH);

   cout<<"Enter your choice:";
   cout<<"\n\t1> Enter UserId to generate/ send eTicket(s)";
   cout<<"\n\t2> Enter PNR to generate/ send eTicket";
   cout<<"\n\t3> Quit\n";

   strcpy(fileName, "bookingD.txt");

   cin>>ch;

   if (ch==1)
   {
    cout<<"Enter UserId to generate /send eTicket:\t";
    gets(userId);

    strcpy(keyTxt[0],"UserId");
    strcpy(keyVal[0],userId);
    strcpy(keyTxt[1],"");
    strcpy(keyVal[1],"");

//    pnr_count=svc.getKeys4KeyFileD(fileName, "UserId", userId, bookingH, "PNR", pnr);
    pnr_count=svc.getKeys4KeysFileD(fileName, keyTxt, keyVal, bookingH, "PNR", pnr);

    if (pnr_count>0)
     for (i=0; i<pnr_count;i++)
     {
      strcpy(keyTxt[0],"PNR");
      strcpy(keyVal[0],pnr[i]);
      strcpy(keyTxt[1],"");
      strcpy(keyVal[1],"");
      recPosition=svc.readFileD(fileName, keyTxt, keyVal, bookingH, bookingD);
      if(recPosition==-1)
       cout<<"No record Found\n";
      else
      {
       printPNR(bookingH, bookingD);
       cout<<"Record "<<i+1<<" of "<<pnr_count;
       getch();
      }
     }
   else
     cout<<"No record Found\n";
   }
   else if (ch==2)
   {
    cout<<"Enter PNR to generate /send eTicket:\t";
    gets(pnrTxt);
    //strcpy(pnrTxt,"Z706138"); //uncomment strcpy... to check this function with an example input.
    strcpy(keyTxt[0],"PNR");
    strcpy(keyVal[0],pnrTxt);
    strcpy(keyTxt[1],"");
    strcpy(keyVal[1],"");

    recPosition=svc.readFileD(fileName, keyTxt, keyVal, bookingH, bookingD);
    if(recPosition==-1)
     cout<<"No record Found\n";
    else
    {
     printPNR(bookingH, bookingD);
     cout<<"Record 1 of 1";
     getch();
    }
   }
   else
    return;
  }

  void inputBooking()
  {
   service svc;
   char bookingH[MAX_HDR][FLD_SIZE], bookingD[MAX_HDR][FLD_SIZE];
   int  i,j,f=0,recPosition,ch;
   char fileName[20];
   char keyTxt[MAX_HDR][FLD_SIZE],keyVal[MAX_HDR][FLD_SIZE];
   char userId[FLD_SIZE], pnr[FLD_SIZE], eTktNum[FLD_SIZE], class_code[FLD_SIZE];
   char dtIssue[FLD_SIZE],ow_rt[FLD_SIZE];
   int  i_ow_rt,i_class_code;
   const int MAX_PAS=5;
   int   daysAfter=0, numOfPas, i_age;
   char fName[MAX_PAS][FLD_SIZE],lName[MAX_PAS][FLD_SIZE],sex[MAX_PAS][FLD_SIZE],age[MAX_PAS][FLD_SIZE];
   char source[FLD_SIZE],dest[FLD_SIZE];
   char	fltNum1[FLD_SIZE], dtDep1[FLD_SIZE], tmDep1[FLD_SIZE], depTerm1[FLD_SIZE], dtArr1[FLD_SIZE], tmArr1[FLD_SIZE];
   char	fltNum2[FLD_SIZE], dtDep2[FLD_SIZE], tmDep2[FLD_SIZE], depTerm2[FLD_SIZE], dtArr2[FLD_SIZE], tmArr2[FLD_SIZE];

   strcpy(userId, gUserId);
   svc.genUniqueId(pnr);
   strcpy(eTktNum,pnr);

   svc.pickDate("", daysAfter, 1, dtIssue);

   const int X_H1=1, X_H2=14, X_H3=27, X_H4=40, X_H5=53, X_H6=66;

   cout<<"\t\t  WELCOME TO FLYING FLIGHTS BOOKING MODULE"<<endl<<endl;

   do
   {
     svc.coutXY(X_H1, 3, "Please enter: 1<OneWay> or 2<RoundTrip>",0);
     gotoxy(X_H1,4);
     svc.coutXY(X_H1,4," ",0);
     gotoxy(X_H1,4);

     i_ow_rt=svc.getNumericInput(X_H1,4,1,ow_rt);
   }while(!(i_ow_rt==1 || i_ow_rt==2));
   if (i_ow_rt==2)
     strcpy(ow_rt,"RT");
   else
     strcpy(ow_rt,"OW");

   do
   {
     svc.coutXY(X_H1, 3, "Please enter Class: 1<First> or 2<Business> or 3<Economy>",1);
     gotoxy(X_H1,4);
     svc.coutXY(X_H1,4," ",0);
     gotoxy(X_H1,4);

     i_class_code=svc.getNumericInput(X_H1,4,1,class_code);
   }while(!(i_class_code==1 || i_class_code==2 || i_class_code==3));
   if (i_class_code==1)
     strcpy(class_code,"First");
   else if (i_class_code==2)
     strcpy(class_code, "Business");
   else
     strcpy(class_code, "Economy");

   getSourceCity(source);
   getDestCity(source,dest);
   svc.pickDate("Booking -> Please select de		parture date...", daysAfter, 30, dtDep1);
   strcpy(dtArr1, dtDep1);
   if (i_ow_rt==2)
   {
     svc.pickDate("Booking -> Please select return date...", daysAfter, 30, dtDep2);
     strcpy(dtArr2,dtDep2);
   }
   else
   {
     strcpy(dtDep2,"");
     strcpy(dtArr2,"");
   }

   getFltNum(source,dest,fltNum1,tmDep1,depTerm1,tmArr1);
   if (i_ow_rt==2)
   {
     getFltNum(dest,source,fltNum2,tmDep2,depTerm2,tmArr2);
   }
   else
   {
     strcpy(fltNum2,"");
     strcpy(tmDep2,"");
     strcpy(depTerm2,"");
     strcpy(tmArr2,"");
   }

   clrscr();
   svc.coutXY(X_H1,2,"User Id", 0);
   svc.coutXY(X_H2,2,"BookingDt", 0);
   svc.coutXY(X_H3,2,"1Way/RdTrip", 0);
   svc.coutXY(X_H4,2,"Class", 0);

   svc.coutXY(X_H1,3,userId, 0);
   svc.coutXY(X_H2,3,dtIssue, 0);
   svc.coutXY(X_H3,3,ow_rt, 0);
   svc.coutXY(X_H4,3,class_code, 0);

   svc.coutXY(X_H1,5,"Source", 0);
   svc.coutXY(X_H2,5,"Dest", 0);
   svc.coutXY(X_H3,5,"Flight#", 0);
   svc.coutXY(X_H4,5,"DepDt", 0);
   svc.coutXY(X_H5,5,"DepTime", 0);
   svc.coutXY(X_H6,5,"ArrTime", 0);

   svc.coutXY(X_H1,6,source, 0);
   svc.coutXY(X_H2,6,dest, 0);
   svc.coutXY(X_H3,6,fltNum1, 0);
   svc.coutXY(X_H4,6,dtDep1, 0);
   svc.coutXY(X_H5,6,tmDep1, 0);
   svc.coutXY(X_H6,6,tmArr1, 0);

   if (i_ow_rt==2)
   {
     svc.coutXY(X_H1,7,dest, 0);
     svc.coutXY(X_H2,7,source, 0);
     svc.coutXY(X_H3,7,fltNum2, 0);
     svc.coutXY(X_H4,7,dtDep2, 0);
     svc.coutXY(X_H5,7,tmDep2, 0);
     svc.coutXY(X_H6,7,tmArr2, 0);
   }
   char txt[FLD_SIZE];


   do
   {
     svc.coutXY(X_H1,9,"Enter # of Passengers <1..5>",0);
     gotoxy(X_H1,10);
     svc.coutXY(X_H1,10," ",0);
     gotoxy(X_H1,10);
     numOfPas=svc.getNumericInput(X_H1,10,1,txt);
   }while(!(numOfPas>=1&&numOfPas<=5));

   svc.coutXY(X_H1,11,"FName", 0);
   svc.coutXY(X_H2,11,"LName", 0);
   svc.coutXY(X_H3,11,"Sex<M/F>", 0);
   svc.coutXY(X_H4,11,"Age<1..99>", 0);

   gotoxy(X_H1,12);
   for (i=0;i<numOfPas;i++)
   {
     svc.getAlphaInput(X_H1,12+i,fName[i]);
     svc.getAlphaInput(X_H2,12+i,lName[i]);
     svc.getAlphaInput(X_H3,12+i,sex[i]);
     do
     {
       gotoxy(X_H4,12+i);
       svc.coutXY(X_H4,12+i,"  ",0);
       gotoxy(X_H4,12+i);
       i_age=svc.getNumericInput(X_H4,12+i,2,age[i]);
     }while(!(i_age>=1&&i_age<=99));
   }

   strcpy(fileName, "bookingD.txt");
   fstream bDi(fileName,ios::in);//declaration
   if (!bDi.eof() && bDi!=0)
     recPosition=0;

   ofstream bD(fileName,ios::app);//declaration
   if(recPosition==0)
      bD<<'\n';

   for (i=0;i<numOfPas;i++)
   {
       bD<<gUserId<<'\n';
       bD<<pnr<<i<<'\n';
       bD<<eTktNum<<i<<'\n';
       bD<<class_code<<'\n';
       bD<<dtIssue<<'\n';
       bD<<ow_rt<<'\n';
       bD<<fName[i]<<'\n';
       bD<<lName[i]<<'\n';
       bD<<sex[i]<<'\n';
       bD<<age[i]<<'\n';
       bD<<source<<'\n';
       bD<<dest<<'\n';
       bD<<fltNum1<<'\n';
       bD<<dtDep1<<'\n';
       bD<<tmDep1<<'\n';
       bD<<depTerm1<<'\n';
       bD<<dtArr1<<'\n';
       bD<<tmArr1<<'\n';
       bD<<fltNum2<<'\n';
       bD<<dtDep2<<'\n';
       bD<<tmDep2<<'\n';
       bD<<depTerm2<<'\n';
       bD<<dtArr2<<'\n';

       if(i==(numOfPas-1))
	  bD<<tmArr2;
       else
	  bD<<tmArr2<<'\n';
   }
   bD.close();

   gotoxy(X_H1,12+i);
   svc.waitMsg("Please Wait, your details are being proccessed.");

   svc.coutXY(X_H5,11,"PNR#", 0);
   svc.coutXY(X_H6,11,"Ticket#", 0);
   char strTxt[FLD_SIZE];
   for (i=0;i<numOfPas;i++)
   {
     strcpy(strTxt,pnr);
     svc.strintcat(strTxt,i,2);
     svc.coutXY(X_H5,12+i,strTxt, 0);
     strcpy(strTxt,eTktNum);
     svc.strintcat(strTxt,i,2);
     svc.coutXY(X_H6,12+i,strTxt, 0);
   }
   svc.coutXY(X_H1,12+i, "Booking successfully saved...", 1);
   getch();
  }

}; //End of class booking

class user
{
 service svc;

 public:
  int readFile(char puserid[MAX_REC_COUNT][FLD_SIZE],char ppassword[MAX_REC_COUNT][20],char pfname[MAX_REC_COUNT][50], char plname[MAX_REC_COUNT][50],char psex[MAX_REC_COUNT][10], char page[MAX_REC_COUNT][10], char pemail[MAX_REC_COUNT][50], char paddress[MAX_REC_COUNT][200],char pphone[MAX_REC_COUNT][15])
  {
   int i=0,maxsize=0;
   ifstream fptrpwd("password.txt",ios::in);//declaration
   while (!fptrpwd.eof() && fptrpwd!=0 && i<100)
   {
    fptrpwd.getline(puserid[i],FLD_SIZE,'\n');
    fptrpwd.getline(ppassword[i],20,'\n');
    fptrpwd.getline(pfname[i],50,'\n');
    fptrpwd.getline(plname[i],50,'\n');
    fptrpwd.getline(psex[i],10,'\n');
    fptrpwd.getline(page[i],10,'\n');
    fptrpwd.getline(pemail[i],50,'\n');
    fptrpwd.getline(paddress[i],200,'\n');
    fptrpwd.getline(pphone[i],15,'\n');

    i++;
   }
   if(i==0)
    maxsize=-1;
   else
    maxsize=i-1;
   fptrpwd.close();
   return maxsize;
  }
  int writeFile(int maxsize,char puserid[FLD_SIZE],char ppassword[20],char pfname[50], char plname[50],char psex[10],char page[10],char pemail[50], char paddress[200],char pphone[15])
  {
   ofstream fptrpwd("password.txt",ios::app);
   if(maxsize>=0)
   fptrpwd<<'\n';
   fptrpwd<<puserid<<'\n';
   fptrpwd<<ppassword<<'\n';
   fptrpwd<<pfname<<'\n';
   fptrpwd<<plname<<'\n';
   fptrpwd<<psex<<'\n';
   fptrpwd<<page<<'\n';
   fptrpwd<<pemail<<'\n';
   fptrpwd<<paddress<<'\n';
   fptrpwd<<pphone;
   maxsize++;
   fptrpwd.close();
   return maxsize;
  }

  int useridexists(int pmaxsize, char puserid[MAX_REC_COUNT][FLD_SIZE],char userid[FLD_SIZE])
  {
   int i=0;

   for(i=0;i<=pmaxsize;i++)
   {
    if (strcmp(userid,puserid[i])==0)
     return 1;
   }
   return 0;
  }

  int validatelogin(int pmaxsize, char puserid[MAX_REC_COUNT][FLD_SIZE],char ppassword[MAX_REC_COUNT][20], char userid[50], char password[20])
  {
   int i=0;

   for(i=0;i<=pmaxsize;i++)
   {
    if (strcmp(userid,puserid[i])==0)
     if(strcmp(password,ppassword[i])==0)
     {
      return 1;
     }
   }
   return 0;
  }

  int login(int pmaxsize, char puserid[MAX_REC_COUNT][FLD_SIZE], char ppassword[MAX_REC_COUNT][20])
  {
   int r, f=0;
   char userid[50],password[20],ch;

   while(1==1)
   {
    strcpy(password,"");
    cout<<"Enter the username:\t";
    gets(userid);
    cout<<"\n\nEnter the password:\t";
    svc.getpassword(password);
    r = validatelogin(pmaxsize, puserid, ppassword, userid,password);
    if(r==0)
    {
     f++;
     cout<<"\nLogin failed !!! "<<3-f<<" trial left";
     getch();
     clrscr();
     if (f==3)
      return 0;
    }
    else
    {
     strcpy(gUserId,userid);

     cout<<"\nLogin passed!!!";
     break;
    }
   }
   return 1;
  }

  //!Registration Module Begin-----------
  int reg(int pmaxsize, char puserid[MAX_REC_COUNT][FLD_SIZE],char userid[50],char ppassword[20],char pfname[50], char plname[50],char psex[10], char page[10],char pemail[50], char paddress[200],char pphone[15])
  {
   char vpassword[20]; //verfication of password
   while(1==1)
   {
    cout<<"Enter your user id:\t";
    gets(userid);
    if(strlen(userid)<=3)
    {
     cout<<"\nUser id should be more than 3 characters";
     continue;
    }
    if(useridexists(pmaxsize,puserid,userid)==1)
     cout<<"\nUser ID already exists!!!";
    else
     break;
   }
   while(1==1)
   {
    cout<<"\nEnter your password:\t";
    svc.getpassword(ppassword);
    if(strlen(ppassword)<=4)
    {
     cout<<"\nPassword should be more than 4 characters";
     continue;
    }
    cout<<"\nVerify your password:\t";
    svc.getpassword(vpassword);
    if(strcmp(vpassword,ppassword)==0)
     break;
    else
     cout<<"\nPasswords do not match\n";
   }
   cout<<"\n\nEnter your first name:\t";
   gets(pfname);
   cout<<"\n\nEnter your last name:\t";
   gets(plname);
   cout<<"\n\nEnter your gender(Male or Female):\t";
   gets(psex);
   cout<<"\n\nEnter your present age:\t ";
   gets(page);
   cout<<"\n\nEnter your email address:\t";
   gets(pemail);
   cout<<"\n\nEnter your phone no:\t";
   gets(pphone);
   cout<<"\n\nEnter your address:\t";
   gets(paddress);
   return 1;
  }

  int login()
  {
   int maxsize, retVal;
   char puserid[MAX_REC_COUNT][FLD_SIZE],ppassword[MAX_REC_COUNT][20],pfname[MAX_REC_COUNT][50], plname[MAX_REC_COUNT][50];
   char psex[MAX_REC_COUNT][10],page[MAX_REC_COUNT][10],pemail[MAX_REC_COUNT][50],paddress[MAX_REC_COUNT][200],pphone[MAX_REC_COUNT][15];
   char userid[FLD_SIZE],password[20],fname[50],lname[50],sex[10],age[10],email[50],address[200],phone[15];

   maxsize = readFile(puserid,ppassword,pfname,plname,psex,page,pemail,paddress,pphone);

   retVal = login(maxsize,puserid,ppassword);
   getch();
   return retVal;
  }

  int reg()
  {
   int maxsize, retVal;
   char puserid[MAX_REC_COUNT][FLD_SIZE],ppassword[MAX_REC_COUNT][20],pfname[MAX_REC_COUNT][50], plname[MAX_REC_COUNT][50];
   char psex[MAX_REC_COUNT][10],page[MAX_REC_COUNT][10],pemail[MAX_REC_COUNT][50],paddress[MAX_REC_COUNT][200],pphone[MAX_REC_COUNT][15];
   char userid[FLD_SIZE],password[20],fname[50],lname[50],sex[10],age[10],email[50],address[200],phone[15];

   maxsize = readFile(puserid,ppassword,pfname,plname,psex,page,pemail,paddress,pphone);
   retVal=reg(maxsize,puserid,userid,password,fname,lname,sex,age,email,address,phone);
   retVal=writeFile(maxsize,userid,password,fname,lname,sex,age,email,address,phone);

   strcpy(gUserId,userid);
   cout<<"Registraion completed\n";
   getch();
   return 1;
  }

};//End of class user

void abt()
{
  clrscr();
  cout<<"Welcome to flying flights C++ application for Microsoft Windows. This application has been designed to ease your ticket bookings and their management. This program was developed by Aakash Singh, Aswath Sivakumaran and Tannmay Rout of Class XII-F3.\nThis software if protected and owned by FITTJEE SWAG and is goverend under strict copyright laws. Any unauthorized modification, distribution or both will lead to maximum criminal penalities that can be imposed by law of the country";
  getch();
}

int disc()
{
 char cha;

 cout<<"\n-----------------------------------DISCLAIMER-----------------------------------\nThe terms of use of this program is goverend by flying flight. The terms of service can be read by going to the menu and pressing 5.";
 cout<<"\nBy using this program you confirm that you are in accordance with the above stated Terms of Service and our privacy policy.\nWhile using this program please provide correct information.\nAny misguiding or fake information provided will be taken as a serious matter.";
 cout<<"\nAny incorrect information provided on purpose or by accident must be notified to us immiediatly.\nFailure to do so will result in criminal proscecution.\nThis program is a copywritten and propertairy work of FIITJEE SWAG Inc. This program cannot be modified, redistributed or sold for or in any means.";
 cout<<"\nPress Y if you agree to use this program or X for exit.";

 do
 {
   cha=getch();

   if(cha=='y'||cha=='Y')
    return 1;
   else if(cha=='X'||cha=='x')
    return 0;
   else
     cout<<"\nInvalid Choice, Enter again.";
 } while(cha!='Y'||cha!='y');
}

void main()
{
  service svc;
  flight flt;
  booking bkg;
  user usr;

  clrscr();
  int ch;

  char option[MAX_REC_COUNT][80];
  int ch2,goback;

  clrscr();
  svc.cputsMsg("INITIALIZING");
  clrscr();
  if (disc()==0)
    return;

  while (1==1)//While for main menu
  {
    clrscr();
    strcpy(option[0],"Login");
    strcpy(option[1],"Register");
    strcpy(option[2],"Exit");
    strcpy(option[3],"");
    ch2=svc.menu(0, "LOGIN MENU",option,0);
    switch(ch2)
    {
      case 1:
	   clrscr();
	   if (usr.login()==0)
	      return;
	   else
	      break;

      case 2:
	   clrscr();
	   if (usr.reg()==0)
	      return;
	   else
	      break;

      case 3:
	   svc.cputsMsg("EXITING");
	   return;
    }

    goback=0;
    while(goback==0)//While for sub-menu
    {
     clrscr();
     strcpy(option[0],"BOOK TICKETS");
     strcpy(option[1],"FLIGHT STATUS");
     strcpy(option[2],"PRINT TICKETS");
     strcpy(option[3],"ABOUT US");
     strcpy(option[4],"QUIT PROGRAM");
     strcpy(option[5],"");
     ch2=svc.menu(0, "SELECTION MENU",option,0);
     switch(ch2)
     {
      case 1:
	clrscr();
	bkg.inputBooking();
	break;

      case 2:
	clrscr();
	flt.getFlightStatus();
	break;

      case 3:
	clrscr();
	bkg.printstat();
	getch();
	break;

      case 4:
	abt();
	break;

      case 5:
	goback=1;
	break;
     }
    }//While for sub-menu
  }//While for main menu
}//End of main()