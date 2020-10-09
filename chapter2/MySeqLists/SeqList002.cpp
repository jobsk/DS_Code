#include <iostream>
const int  DEFAULT_SIZE = 20;
enum Status {ENTRY_FOUND, NOT_PRESENT, SUCESS, RANGE_ERROR, OVER_FLOW};
 
template <class ElemType>
void visit(const ElemType& e)
{
    std::cout << e << ", ";
}
 
template <class ElemType>
class SeqList
{
    protected:
        int length;
        int maxLength;
        ElemType *elems;
    public:
        SeqList(int size=DEFAULT_SIZE);      
        SeqList(ElemType v[], int n, int size=DEFAULT_SIZE);
        virtual ~SeqList();
         
        int GetLength() const
        {
            return length;
        }
        bool IsEmpty() const
        {
            return length>0? false : true;
        }
        void Clear();
        void Traverse(void (*Visit) (const ElemType &)) const;
        int LocateElem(const ElemType &e) const;
        Status GetElem(int i, ElemType &e) const;
        Status SetElem(int i, const ElemType &e);
        Status DeleteElem(int i, ElemType &e);
        Status InsertElem(int i, const ElemType &e);
        Status InsertElem(const ElemType &e);
         
        SeqList(const SeqList<ElemType> &sa);
        SeqList<ElemType> &operator =(const SeqList<ElemType> &sa);
};
 
// 01
template <class ElemType>
SeqList<ElemType>::SeqList(int size)
{
    elems = new ElemType[size];
    maxLength = size;
    length = 0;
}
 
//02
template <class ElemType>
SeqList<ElemType>::SeqList(ElemType v[], int n, int size)
{
    elems = new ElemType(size);
    maxLength = size;
    length = n;
    for (int i=0; i<length; i++)
    {
        elems[i]=v[i];
    }
}
 
// 3
template <class ElemType>
SeqList<ElemType>::~SeqList()
{
    delete []elems;
}
 
// 4
template <class ElemType>
void SeqList<ElemType>::Clear()
{
    length = 0;
}
 
// 5
template <class ElemType>
void SeqList<ElemType>::Traverse(void (*Visit) (const ElemType &)) const
{
    for (int i=0; i<length; i++)
    {
        (*Visit)(elems[i]);
    }
}
 
//6
template <class ElemType>
int SeqList<ElemType>::LocateElem(const ElemType &e) const
{
    int i=0;
    while (i<length && elems[i]!=e)
    {
        i++;
    }
    return i<length ? i+1 : 0;
}
 
// 07
template <class ElemType>
Status SeqList<ElemType>::GetElem(int i, ElemType &e) const
{
    if (i<1 || i>length)
    {
        return NOT_PRESENT;
    }
    else {
        e = elems[i-1];
        return ENTRY_FOUND;
    }
}
 
// 08
template <class ElemType>
Status SeqList<ElemType>::SetElem(int i, const ElemType &e)
{
    if (i<1 || i>length)
    {
        return RANGE_ERROR;
    }
    else {
        elems[i-1] = e;
        return SUCESS;
    }
}
 
// 09
template <class ElemType>
Status SeqList<ElemType>::DeleteElem(int i, ElemType &e)
{
    if (i<1 || i> length)
    {
        return RANGE_ERROR;
    }
    else {
        e = elems[i-1]; //
        for (int j=i; j<length; j++)
        {
            elems[j-1] = elems[j];
        }
        length--;
        return SUCESS;
    }
}
 
// 10
template <class ElemType>
Status SeqList<ElemType>::InsertElem(int i, const ElemType &e)
{
    if (length==maxLength)
    {
        return OVER_FLOW;
    }
    else if (i<1 || i>length+1)
    {
        return RANGE_ERROR;
    }
    else {
        for (int j=length; j>=i; j--)
        {
            elems[j] = elems[j-1];
        }
        elems[i-1] = e;
        length++;
        return SUCESS;
    }
}
 
// 011
template <class ElemType>
Status SeqList<ElemType>::InsertElem(const ElemType &e)
{
    if (length == maxLength)
    {
        return OVER_FLOW;
    }
    else {
        elems[length] = e;
        length++;
        return SUCESS;
    }
}
 
// 012
template <class ElemType>
SeqList<ElemType>::SeqList(const SeqList<ElemType> &sa)
{
    length = sa.length;
    maxLength = sa.maxLength;
    elems = new ElemType[maxLength];
    for (int i=0; i<length; i++)
    {
        elems[i] = sa.elems[i];
    }
}
 
template <class ElemType>
SeqList<ElemType>& SeqList<ElemType>::operator =(const SeqList<ElemType> &sa)
{
    length = sa.length;
    maxLength = sa.maxLength;
    elems = new ElemType[maxLength];
    for (int i=0; i<length; i++)
    {
        elems[i] = sa.elems[i];
    }
    return *this;
}
 
 
int main()
{
    using std::cout;
    using std::endl;
     
    SeqList<int> s1;
    int array[] = {9,8,0,6,1,3};
    SeqList<int> s2(array, 6);
    cout << "s1:";
    s1.Traverse(visit);
    cout << "\ns2:";
    s2.Traverse(visit);
    cout << endl;
     
    SeqList<int> s3(s2);
    int six;
    s3.GetElem(s2.LocateElem(6), six);
    cout << six << endl;
     
    s1 = s2;
    s1.SetElem(1, 1);
    s1.SetElem(2, 9);
    cout << "s1: 1,9,0,6,1,3\n";
    s1.Traverse(visit);
    cout << endl;
     
    s1.InsertElem(3,9);
    s1.InsertElem(4,8);
    cout << "s1: 1,9,9,8,0,6,1,3\n";
    s1.Traverse(visit);
    cout << endl;
     
    int three = 333;
    Status deleteStatus = s3.DeleteElem(6,three);
    cout << "three: " << three << " status: "<< deleteStatus << endl;
    s3.InsertElem(5);
    cout << "s3: 9,8,0,6,1,5\n";
    s3.Traverse(visit);
    cout << endl;
    return 0;
}
