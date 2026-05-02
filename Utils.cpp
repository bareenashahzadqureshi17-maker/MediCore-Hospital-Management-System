#include "Utils.h"
int Utils::len(const char* s){int i=0; if(!s) return 0; while(s[i]) i++; return i;}
void Utils::copy(char*& d,const char* s){ if(d){delete[] d; d=0;} int n=len(s); d=new char[n+1]; for(int i=0;i<n;i++) d[i]=s[i]; d[n]='\0';}
void Utils::copyArr(char* d,const char* s,int n){int i=0; if(!d||n<=0) return; while(s&&s[i]&&i<n-1){d[i]=s[i]; i++;} d[i]='\0';}
bool Utils::eq(const char* a,const char* b){if(!a||!b) return false; int i=0; while(a[i]&&b[i]){ if(a[i]!=b[i]) return false; i++; } return a[i]=='\0'&&b[i]=='\0';}
bool Utils::eqi(const char* a,const char* b){if(!a||!b) return false; int i=0; while(a[i]&&b[i]){ char x=a[i], y=b[i]; if(x>='A'&&x<='Z') x+=32; if(y>='A'&&y<='Z') y+=32; if(x!=y) return false; i++; } return a[i]=='\0'&&b[i]=='\0';}
int Utils::toInt(const char* s){int i=0,v=0,sign=1; if(!s) return 0; if(s[0]=='-'){sign=-1;i=1;} for(;s[i];i++) if(s[i]>='0'&&s[i]<='9') v=v*10+(s[i]-'0'); return v*sign;}
float Utils::toFloat(const char* s){if(!s) return 0; int i=0,sign=1; if(s[0]=='-'){sign=-1;i=1;} float v=0; while(s[i]&&s[i]!='.'){if(s[i]>='0'&&s[i]<='9') v=v*10+(s[i]-'0'); i++;} if(s[i]=='.') i++; float f=.1f; while(s[i]){if(s[i]>='0'&&s[i]<='9'){v+=(s[i]-'0')*f; f/=10;} i++;} return v*sign;}
bool Utils::digit(char c){return c>='0'&&c<='9';}
void Utils::splitCSV(char* line,char out[][500],int& c,int maxT){c=0; int i=0,j=0; while(line[i]&&c<maxT){ if(line[i]==','){out[c][j]='\0'; c++; j=0;} else out[c][j++]=line[i]; i++; } if(c<maxT){out[c][j]='\0'; c++;}}
int Utils::cmpDate(const char* a,const char* b){int da=(a[0]-'0')*10+a[1]-'0', db=(b[0]-'0')*10+b[1]-'0'; int ma=(a[3]-'0')*10+a[4]-'0', mb=(b[3]-'0')*10+b[4]-'0'; int ya=(a[6]-'0')*1000+(a[7]-'0')*100+(a[8]-'0')*10+a[9]-'0'; int yb=(b[6]-'0')*1000+(b[7]-'0')*100+(b[8]-'0')*10+b[9]-'0'; if(ya!=yb) return ya-yb; if(ma!=mb) return ma-mb; return da-db;}
int Utils::cmpTime(const char* a,const char* b){int ha=(a[0]-'0')*10+a[1]-'0', hb=(b[0]-'0')*10+b[1]-'0'; int ma=(a[3]-'0')*10+a[4]-'0', mb=(b[3]-'0')*10+b[4]-'0'; if(ha!=hb) return ha-hb; return ma-mb;}
