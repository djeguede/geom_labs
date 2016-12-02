#ifndef CLIST_H
#define CLIST_H

#include <cstdlib>

using namespace std;
template<class T> class CListItem;
template<class T> class CIterator;


//***** CList  ***********************************************
template<class T>
class CList
{
private:
    CListItem<T> * head;
    CListItem<T> * curr;
    CListItem<T> * prev;
    int size;

public:
    CList();
    ~CList();
   bool empty();
   void push_back(T& elem);
   void push_front(T& elem);

   void push_back(CListItem<T> * elemList);
   void push_front(CListItem<T> * elemList);

   CIterator<T> insert(CIterator<T> &it, CListItem<T> * listElem);
   CListItem<T>* pop(CIterator<T> &it);
   CIterator<T> end();
   CIterator<T> begin();
   void sort();
   CList<T>& merge(CList<T> &L2);
   CList<T>& merge(CList<T> &L1 ,CList<T>& L2);
   CList<T>& operator=(CList<T> & other);
   int length(){ return size;}

};

//template<class T> int CList<T>::size =0;

template<class T>
CList<T>::CList(){
    head =NULL;
    curr =NULL;
    prev =NULL;
    size=0;
}

template<class T>
CList<T>::~CList(){
    /*if(!this->empty()){
        curr= head;
        prev=NULL;
     while(curr!=NULL && curr->getNext()!=NULL){
        prev = curr;
        curr=curr->getNext();
        head=curr;
        delete prev;
      }
     delete head;
    }*/

}

template<class T>
bool CList<T>::empty(){
 if(head){ return false;}
 else{ return true;}
}

template<class T>
void CList<T>::push_back(T& elem){

 CListItem<T> * elemList = new CListItem<T>(elem);
 size++;
 if(this->empty())
 {
  head = elemList;
  curr = elemList;
  prev = NULL;
 }
 else{
    prev = curr;
    curr->setNext(elemList);
    curr = elemList;
 }

}

template<class T>
void CList<T>::push_back(CListItem<T> * elemList){

    size++;
    if(this->empty())
    {
     head = elemList;
     curr = elemList;
     prev = NULL;
    }
    else{
       prev = curr;
       curr->setNext(elemList);
       curr = elemList;
    }
}


template<class T>
void CList<T>::push_front(T& elem){
    CListItem<T> * elemList = new CListItem<T>(elem);
    size++;
    if(this->empty())
    {
     head = elemList;
     curr = elemList;
     prev = NULL;
    }
    else{

        elemList->setNext(head);
        head= elemList;
        curr= head;
        prev= NULL;
    }
}

template<class T>
void CList<T>::push_front(CListItem<T> * elemList){

    size++;
    if(this->empty())
    {
     head = elemList;
     curr = elemList;
     prev = NULL;
    }
    else{

        elemList->setNext(head);
        head= elemList;
        curr= head;
        prev= NULL;
    }
}

template<class T>
CIterator<T> CList<T>::insert(CIterator<T> &it, CListItem<T> * listElem){

  size++;
  prev= it.elem;
  listElem->setNext(prev->getNext());
  prev->setNext(listElem);
  curr=listElem;
  ++it;
  return it;
}

template<class T>
CListItem<T>* CList<T>::pop(CIterator<T> &it){

  size--;
  if(it==this->begin() && it==this->end() )
  {
      CListItem<T>* r;
      r= head;
      head=curr=prev=NULL;
      size=0;
      return r;
  }
  else{

    if(it==this->begin()){
      head=it.elem->Next;
      curr= head;
      prev=NULL;
      CListItem<T>* clitem= it.elem;
      ++it;
      clitem->Next=NULL;
      return clitem;

    }else{
        if(it==this->end()){
            CListItem<T>* save;
            CListItem<T>* ret;
            while(curr != it.elem){
                save=prev;
                prev=curr;
                curr=curr->Next;
            }
            ret =curr;
            curr = prev;
            prev =save;
            curr->setNext(NULL);
            return ret;

        }
        else{

            CListItem<T>* save;
            while(curr != it.elem){
                prev=curr;
                curr=curr->Next;
            }
            save =curr;
            prev->setNext(curr->Next);
            curr=curr->Next;
            save->setNext(NULL);
            return save;

        }
    }

  }
}


template<class T>
CIterator<T> CList<T>::end(){
    curr= head;
    prev=NULL;

    while(curr->getNext() != NULL)
    {
       prev=curr;
       curr= curr->getNext();
    }
 return CIterator<T>(curr );
}

template<class T>
CIterator<T> CList<T>::begin(){
 return CIterator<T>(head);
}

template<class T>
CList<T>& CList<T>::merge(CList<T> &L2){

  if(!L2.empty()){
    if (this->empty()){
         head= L2.head;
         curr= L2.curr;
         prev= L2.prev;
         size =L2.size;
         return *this;
     }
     else{
       CIterator<T> it1, it2;
         it1= this->end();
         it2= L2.begin();
         it1.elem->Next= it2.elem;
        this->size+=L2.size;
        return *this;
     }
  }
  else{
      return *this;
  }
}

template<class T>
CList<T>& CList<T>::merge(CList<T> &L1 ,CList<T>& L2){

    if(!L2.empty()){
        if (L1.empty()){
             head= L2.head;
            curr= L2.curr;
            prev= L2.prev;
            size =L2.size;
            return *this;
            }
        else{
            CIterator<T> it1, it2;
            it1= L1.end();
            it2= L2.begin();
            it1.elem->Next= it2.elem;
            L1.size+= L2.size;
            return L1;
        }
    }
    else{
       return L1;
    }
}

template<class T>
CList<T>& CList<T>::operator=(CList<T> & other){
    this->head=other.head ;
    this->curr=other.curr ;
    this->prev=other.prev;
    this->size=other.size;
    return *this;
}

template<class T>
void CList<T>::sort(){

    qDebug()<<"sort() ";
  if(!this->empty() /*&& this->length()>1*/)
  {
     CListItem<T>* Pivot = this->pop(this->begin());
     //qDebug()<<"Pivot: "<< Pivot->getData();
     CList<T> Inf, Sup;

     if(!this->empty())
     {
        CListItem<T>* help;
        CIterator<T> it(this->begin());
        for(it; it!=this->end(); )
        {
            if(Pivot->getData()>it.elem->getData())
            {
                help = pop(it);
                Inf.push_back(help);

            }
            else{
                 help = pop(it);
                 Sup.push_back(help);
            }
         }

          if(Pivot->getData()>it.elem->getData())
           {
             help = pop(it);
             Inf.push_back(help);

           }
           else{
             help = pop(it);
             Sup.push_back(help);
           }
     }

     //qDebug()<<"Recursion: Inf.sort() ; length= "<<Inf.length();
     Inf.sort();
     //qDebug()<<"Recursion: Sup.sort() ; length=  "<<Sup.length();
     Sup.sort();
     //qDebug()<<"After Recursions";

     this->merge(Inf);
     this->push_back(Pivot);
     this->merge(Sup);
  }

}

//****** CIterator  *************************
template<class T>
class CIterator
{
    friend class CList<T>;
private:
    CListItem<T> * elem;
public:
    CIterator( CListItem<T> * e);
    CIterator ();
    CIterator<T> & operator ++();
    T operator *();
    CIterator<T> & operator=( CIterator<T> & it );
    bool operator == (CIterator<T> & it);
    bool operator != (CIterator<T> & it);
    void setElem(CListItem<T> * e);
};

template<class T> CIterator<T>::CIterator(CListItem<T> * e):elem(e){

}
template<class T> CIterator<T>::CIterator(){
    elem=NULL;
}

template<class T> CIterator<T> & CIterator<T>::operator++(){
    if(elem!=NULL && elem->getNext()!=NULL)  elem = elem->getNext();
 return *this;
}


template<class T>
T CIterator<T>::operator *(){
 return elem->data;
}



template<class T>
CIterator<T> & CIterator<T>::operator=( CIterator<T> & it ){
  this->elem =it.elem;

  return *this;
}

template<class T>
bool CIterator<T>::operator == (CIterator<T> & it){
    return this->elem ==it.elem;
}

template<class T>
bool CIterator<T>::operator != (CIterator<T> & it){
    return this->elem != it.elem;

}

template<class T>
void CIterator<T>::setElem(CListItem<T> * e){
 this->elem=e;
}

//****** CListItem *******************************
template<class T>
class CListItem
{
    friend class CList<T>;
    friend class CIterator<T>;
 private:
    T data;
    CListItem<T> * Next;

 public:
    CListItem(T& d);
    void setData(T & dat);
    void setNext(CListItem<T> * n);

    T & getData();
    CListItem<T> * getNext();
    ostream& serialize(ostream &out);
    void deserialize(istream &in );


};

template<class T>
CListItem<T>::CListItem(T& d):data(d){
 Next=NULL;
}

template<class T>
void CListItem<T>::setData(T &dat){
 data= dat;
}

template<class T>
void CListItem<T>::setNext(CListItem<T> * n){
 Next =n;
}

template<class T>
T& CListItem<T>::getData(){
    return data;
}

template<class T>
CListItem<T> * CListItem<T>::getNext(){
    return Next;
}

template<class T>
ostream & CListItem<T>::serialize(ostream &out){

    out<< data;
}

template<class T>
void CListItem<T>::deserialize(istream &in){

    in >> data;
}
#endif // CLIST_H
