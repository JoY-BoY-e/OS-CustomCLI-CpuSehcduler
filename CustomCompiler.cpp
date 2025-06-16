# include <iostream>
# include <unistd.h>
# include <cstring>
# include <sys/wait.h>
# include <vector>
# include <fcntl.h>
# include <vector>
# include <stdexcept>

#define HistorySize 10
using namespace std;

int main()
{
pid_t ret_Val;
cout<<"Process ID: "<<getpid()<<endl;

string cmd;
vector<string> hist;
bool exFlag=false;
int histInd=0;
do{
char cwd[1024];
getcwd(cwd,sizeof(cwd));
cout<<"\nEnter CMD| "<< cwd<<" :\t";
getline(cin,cmd);
if(hist.size() == HistorySize )
	hist.pop_back();
hist.insert(hist.begin(),cmd);

if(cmd=="exit")
	break;
//tokenization
	int pipe_count=0;
	for(int ii=0;ii<cmd.length();ii++)
	{
		if(cmd[ii]=='|')
			pipe_count++;
		
			
	}
	
	
	int pipe_fd[pipe_count][2];
	
for(int jj=0;jj<pipe_count+1;jj++){   //  

	string tokenCmd;	
	if(jj==pipe_count)
		tokenCmd=cmd;
	else
		{
			tokenCmd=cmd.substr(0,cmd.find("|"));
			cmd=cmd.substr(cmd.find("|")+1);
		}
	cout<<tokenCmd<<endl;
	
	//pipe Handling....................
	if(jj<pipe_count){
	if(pipe(pipe_fd[jj])==-1){
		perror("pipe\n");
		exit(1);
	}
	}
	//.........................	
	
  	char ch[50];
  	int ind=0;
  	int spcount=0;
   		bool fl=false;
   		bool hisFlag=false;
   		bool cd_flag=false;
  	for(;ind<tokenCmd.length();ind++)
  	{
  		if(tokenCmd.find("!!") != string::npos )
  			{
  				hisFlag=true;
  			}
  			
  		if(tokenCmd.find("!") != string::npos && tokenCmd[tokenCmd.find("!")+1] != '!')
		{
			string dig=tokenCmd.substr(tokenCmd.find("!")+1, tokenCmd.find(" ") );
			cout<<"STRING = "<<dig<<endl;
			/*
			queue<string> tem = hist;
			for(int qind=0;qind<stoi(dig);qind++)
				tem.pop();
				
			tokenCmd =tem.front();
			*/
			if(dig >= '0' && dig <='9')
			{
			int cmdInd=0;
			bool flagHis=false;
			for(auto & H_ind : hist)
			{
				if(cmdInd == stoi(dig))
				{
					flagHis=true;
					tokenCmd=H_ind;	
					break;
				}		
				cmdInd++;
			}
			}
			else 
				flagHis=true;
			if(!flagHis)
				{cout<<"OUT OF Range Or Not In History\n";
				exFlag=true;
				break;
				}	
			cout<<tokenCmd;
			//exit(1);
			ind=-1;
			continue;
			
		}
		if(tokenCmd.find("cd") !=string ::npos || tokenCmd.find("CD") !=string ::npos )
		{
			cd_flag=true;
		}
  		if(tokenCmd[ind]==' ')
  			spcount++;
  		if(tokenCmd[ind]=='&')
  		{	
  			fl=true;
  			break;
  		}
  		ch[ind]=tokenCmd[ind];
  	}
  	ch[ind]='\0';
    	
    	if(exFlag)
    		{ exFlag=false;
    		break;
    		}

//..................
if(!cd_flag){
ret_Val=fork();
if(ret_Val<0)
{
//fork failed
cout<<"Fork failed"<<endl;}
else if(ret_Val==0)
{
int zzz=0;

	//pipe Handling....................
	 if (pipe_count > 0) {       //   ls | cat \ ls 
    if (jj == 0) {
     
        if (dup2(pipe_fd[jj][1], STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            exit(EXIT_FAILURE);
        }
        close(pipe_fd[jj][1]); 
       
   	 } else if (jj == pipe_count) {
       
        if (dup2(pipe_fd[jj - 1][0], STDIN_FILENO) == -1) {
            perror("dup2 failed");
            exit(EXIT_FAILURE);
       	 }
        close(pipe_fd[jj - 1][0]); 
        	
    	} else {
     	
       	 if (dup2(pipe_fd[jj - 1][0], STDIN_FILENO) == -1) {
       	     perror("dup2 failed");
       	     exit(EXIT_FAILURE);
       	 }
       	 close(pipe_fd[jj - 1][0]); 
       	
     
        	if (dup2(pipe_fd[jj][1], STDOUT_FILENO) == -1) {
 	           perror("dup2 failed");
	            exit(EXIT_FAILURE);
	        }
	        close(pipe_fd[jj][1]); 
	        
	 } 
	}
	
	if(hisFlag)
	{
		//queue<string> temp = hist;
		hist.erase(hist.begin(),hist.begin()+1);
		int hh=0;
		if(hist.size() == 0)
		{
			cout<<"No Commands In History\n";
			exit(0);
		}
		else{
			for(auto & H_ind : hist)
			{
				//if(hh != 0)
				//{
					cout<<hh+2<<" -> "<<H_ind<<endl;
				//}
				hh++;
			}
		
		}
		
		exit(0);
	}
	
	//pipe data handling 

	char **arg;
	char *token;
  	bool flag_in=false,flag_out=false;
  	arg=new char*[spcount+2];
  	char *rest=ch;
   		int count=0;
   		char chk_IN[]="<";
   		char chk_Out[]=">";
    	 while ((token = strtok_r(rest, " ", &rest)))   //  
        {
        	if(strcmp(token,chk_IN) == 0)
        	{
        		cout<<token<<endl;
        		token = strtok_r(rest, " ", &rest);
        		if(strcmp(token,chk_Out) == 0 )
        			{
        				cout<<"\nError File name is Empty\n";
        				exit(1);
        			}
        		int fdin;
        		if(!(fdin=open(token,0)))
        			{
        				cout<<"Error opening File";
        				exit(1);        			
        			}
        		dup2(fdin,STDIN_FILENO);
        		close(fdin);
        		
        		flag_in=true;
        		continue;
        		
        	}
        	if(strcmp(token,chk_Out) == 0)
        	{
        			token = strtok_r(rest, " ", &rest);
        			cout<<token<<endl;
        			
        			int fdout;
        			if(!(fdout=open(token,O_WRONLY | O_CREAT | O_TRUNC, 0666)))
        			{
        				cout<<"Error opening File";
        				exit(1);
        			}
        			
        			if(dup2(fdout,STDOUT_FILENO)==-1){
        			perror("DUP\n");
        			exit(1);
        			}
        			
        			close(fdout);
        			flag_out=true;
        			continue;
        	}
        	
        	arg[count++]=token;
        }
        arg[count++]=NULL;
        
       
execvp(arg[0],arg);

cout<<"\nError Occured in processing this cmd"<<getpid()<<endl;

exit(0);
}
else{
//parent proces
int status;
if(!fl)
{pid_t id=wait(&status);
cout<<"\nTerminated child id is: "<<id<<" and exit status is: "<<status;}
cout<<"\nParent process ID: "<<getpid()<<endl<<endl;
sleep(1);
if(pipe_count>0){
if(jj==0){
	close(pipe_fd[jj][1]);
	}
else if (jj==pipe_count){
	close(pipe_fd[jj-1][0]);
	}
else{
	close(pipe_fd[jj-1][0]);
	close(pipe_fd[jj][1]);
}
}
}
}else{
	char * path=ch;
	strtok_r(path," ",&path);
	//cout<<"chdir to "<<path;
	chdir(path);
}
}
/*
for(int iiii=0;iiii<pipe_count;iiii++)
{
	close(pipe_fd[iiii][0]);
	close(pipe_fd[iiii][1]);
}
*/
}while(true);

return 0;
}
