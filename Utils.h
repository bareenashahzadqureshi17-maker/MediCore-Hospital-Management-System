#ifndef UTILS_H
#define UTILS_H
class Utils {
public:
    static int len(const char* s);
    static void copy(char*& d,const char* s);
    static void copyArr(char* d,const char* s,int n);
    static bool eq(const char* a,const char* b);
    static bool eqi(const char* a,const char* b);
    static int toInt(const char* s);
    static float toFloat(const char* s);
    static bool digit(char c);
    static void splitCSV(char* line,char out[][500],int& c,int maxT);
    static int cmpDate(const char* a,const char* b);
    static int cmpTime(const char* a,const char* b);
};
#endif
