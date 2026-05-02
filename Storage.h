#ifndef STORAGE_H
#define STORAGE_H
template<class T>
class Storage{
    T data[100]; int count;
public:
    Storage()
    {
    count=0;

    } 
    void clear()
    {
    count=0;
    }
    bool add(const T& x){
    if(count>=100) 
    return false;
    data[count++]=x;
    return true;
    }
    bool removeByIndex(int idx)
    { 
    if(idx<0||idx>=count) 
    return false;
    for(int i=idx;i<count-1;i++)
    data[i]=data[i+1];
    count--;
    return true;
    }
    T* getAll()
    {
    return data;
    } 
    const T* getAll() 
    const{
    return data;
    } 
    int size() const
    {
    return count;
    }
    T* getAt(int i)
    {
    if(i<0||i>=count) 
    return 0; 
    return &data[i]; 
    } 
    const T* getAt(int i) const
    {
    if(i<0||i>=count) 
    return 0; 
    return &data[i];
    }
};
#endif
