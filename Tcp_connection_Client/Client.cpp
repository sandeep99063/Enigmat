#include "Client.h"

using namespace std;
int xx=0,yy=9,xxx,yyy,flag;
int q=0,w=0,e=0;
int Pos[3];							//GLOBAL VARIABLE FOR POSITION OF ROTORS
char R[3][27],
		   //ABCDEFGHIJKLMNOPQRSTUVWXYZ
AR[5][27]={	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",//R1
			"AJDKSIRUXBLHWTMCQGZNPYFVOE",//R2
			"BDFHJLCPRTXVZNYEIWGAKMUSQO",//R3
			"ESOVPZJAYQUIRHXLNFTGKDCMWB",//R4
			"VZBRGITYUPSDNHLXAWMJQOFECK"},//R5
Ref[27]=	"EJMZALYXVBWFCRQUONTSPIKHGD",//REFLECTOR
pb[27]=		"ZYXWVUTSRQKLMNOPJIHGFEDCBA";//PLUGBOARD
		   //ABCDEFGHIJKLMNOPQRSTUVWXYZ
char rotor(char a)
{
	int i=-1,j;
	if(a>96)a-=32;
	a=pb[a-65];//FIRST PASS IN PLUG BOARD
	while(++i<3)	
		a=R[i][(a-65+Pos[i])%26];//PASSING THROUGH EACH ROTOR 1ST TIME TOP TO BOTTOM
	a=Ref[a-65];				  //REFLECTOR CHANGE THE VALUE
	while(j=26,i--)					//PASSING THROUGH ROTORS 2ND TIME FROM BOTTOM TO TOP
	{
		while(--j*(R[i][j]-a));		//FINDING INDEX OF CHARACTER a FROM 25 TO 0(RIGHT TO LEFT)
		a=65+((j-Pos[i]+26)%26);	
	}
	if(!(Pos[0]=++Pos[0]%26))//ROATATING ROTOR 1
		//IF ROTOR 1 HAS VALUE 26 THN IT WILL ROTATE 2ND ROTOR ND VALUE OF 1ST ROTOR WILL BE 0
		if(!(Pos[1]=++Pos[1]%26))//ROTATING ROTOR 2 IF ROTOR 1 IS ZERO
			//IF ROTOR 2 HAS VALUE 26 THN IT WILL ROTATE 3RD ROTOR WILL BE 0
			Pos[2]=++Pos[2]%26;//ROTATING ROTOR 3 IF ROTOR 1 AND ROTOR 2 ARE ZERO
	a=pb[a-65];//SECOND PASS THROUGH PLUG BOARD 
	return a;
}
void gotoxy(int x, int y) 
{ 
  HANDLE hConsoleOutput; 
  COORD dwCursorPosition;

  cout.flush(); 
  dwCursorPosition.X = x; 
  dwCursorPosition.Y = y; 
  hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE); 
  SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
}
//=================================================

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}
//=================================================
DWORD WINAPI ReadingThread(LPVOID param)
{
  HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    SOCKET s = (SOCKET) param;
    char message[500],coded1[500]="\0";
	string conv;

   long iResult;

    do
    {
        iResult = recv(s, message,sizeof(message), NULL);
        conv=message;
		gotoxy(0,yy=2+yy);
			for(int i=0;coded1[i]='\0',message[i]!='\0';i++)
			coded1[i]=rotor(message[i]);
      SetConsoleTextAttribute(h,FOREGROUND_GREEN | FOREGROUND_INTENSITY );
		cout << "Recv: " << coded1<<"\n                                               ";
		yyy=wherey();
		xxx=wherex();
		gotoxy(5,5);
		cout<<"                                                        ";
		gotoxy(xxx,yyy);
		SetConsoleTextAttribute(h,FOREGROUND_BLUE | FOREGROUND_INTENSITY );
		cout<<"\n\n        Type The Message :";
		gotoxy(26,yyy=yyy+2);
		
		

    }
    while (true);

    return 0;

}
void main()
{
	system("COLOR 0B");
long SUCCESSFUL;
int x=1,w=1;
char b;
char str[20];
	int i;
DWORD dwThreadID;
HANDLE hThread,h1=GetStdHandle(STD_OUTPUT_HANDLE),h2=GetStdHandle(STD_OUTPUT_HANDLE);
	WSAData WinSockData;
	WORD DLLVersion;
	//-----------------------------------------------
	
	cout<<setw(45)<<"||__Enigma__||";
	
		cout<<"\n\nEnter Order Of Rotors( |5| |4| |3| |2| |1| ) ";
		cin>>q>>w>>e;
		for(int k=0;k<26;k++)
		{
			R[0][k]=AR[q-1][k];
			R[1][k]=AR[w-1][k];
			R[2][k]=AR[e-1][k];
		}
		
	//x:	try
		//{
		cout<<"\n\nEnter the Rotor Positions :";
/*	cin>>Pos[2]>>Pos[1]>>Pos[0];
	Pos[0]--;
	Pos[1]--;
	Pos[2]--;
*/
		for(i=3;i--;Pos[i]--)		//ENTERING INITIAL POSITIONS OF ROTORS
			cin>>Pos[i];
	//-----------------------------------------------------

		system("cls");
DLLVersion=MAKEWORD(2,1);

SUCCESSFUL=WSAStartup(DLLVersion,&WinSockData);

string RESPONSE;
string CONVERTER;
char MESSAGE[200],messg[500],coded[500]="\0";

SOCKADDR_IN ADDRESS;

SOCKET sock;
sock=socket(AF_INET,SOCK_STREAM,NULL);
ADDRESS.sin_addr.s_addr=inet_addr("127.0.0.1");
ADDRESS.sin_family=AF_INET;
ADDRESS.sin_port=htons(444);

cout<<"\n\t CLIENT:Do you want to connect to this Server(Y/N)";
cin>>RESPONSE;

RESPONSE[0]=tolower(RESPONSE[0]);
if(RESPONSE == "n")
{
	cout<<"\n\tOk! Quitting Instead ";
}
else if(RESPONSE == "y")
{
	connect(sock,(SOCKADDR*)&ADDRESS,sizeof(ADDRESS));
	hThread=CreateThread(NULL,0,&ReadingThread,(void*)sock,0,&dwThreadID);
	while(w)
		{
			xxx=wherex();
			yyy=wherey();
		gotoxy(5,yyy=yyy+3);
		
		SetConsoleTextAttribute(h1,FOREGROUND_BLUE | FOREGROUND_INTENSITY );
		
	 cout<<"Type The Message : ";
		cout<<"                                                         ";
		gotoxy(24,yyy);
		
		fflush(stdin);
		
	   cin.getline(messg,500);
	   gotoxy(5,yyy);
	   cout<<"                                                               ";
		//cin>>messg;
		gotoxy(0,yy=2+yy);
		SetConsoleTextAttribute(h1,FOREGROUND_RED | FOREGROUND_INTENSITY );
		cout<<"Sent: "<<messg;
		for(int i=0;coded[i]='\0',messg[i]!='\0';i++)
			coded[i]=rotor(messg[i]);
		//cin>>messg;
		
		SUCCESSFUL=send(sock,coded,46,NULL);
	
		
		}

}
else
{
	cout<<"\n\tThat was an inappropriate RESPONSE: ";
}
cout<<"\n\n\t";
system("PAUSE");
exit(1);
	
	}
	