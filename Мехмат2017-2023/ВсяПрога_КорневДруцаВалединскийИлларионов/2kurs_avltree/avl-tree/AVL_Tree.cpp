#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"avl-tree.h"

//int aa(const Double &a,const Double &b)
//{


//}


struct str 
{
    char *s;
    str() { s=0; }
    str(const char *a)  { s=new char[strlen(a)+1]; strcpy(s,a); }
    ~str(){ delete [] s; }
    bool operator<(const str &x) const { return strcmp(s,x.s)<0; }
    bool operator==(const str &x) const { return strcmp(s,x.s)==0; }
    bool operator>(const str &x) const { return strcmp(s,x.s)>0; }
    void pechat() const { printf("%s ",s ); }

    const str & operator=(const str &x) { if (s) delete []s;  s=new char[strlen(x.s)+1]; strcpy(s,x.s); return *this; }

};


int main(){
    Tree<double>  Myderevo;
/*
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(1);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(4);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(6);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(2);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(5);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(4.5);
    Myderevo.print_tree (); printf ("\n\n\n");
   */
Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(3);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(2);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(7);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(4);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(9);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(8);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(10);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(1);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(5);
    Myderevo.print_tree (); printf ("\n\n\n");

    //Myderevo.Del(4);
    //Myderevo.print_tree();
  /* 
    Myderevo.Add(8);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(6);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(17);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(100);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(50);
    Myderevo.print_tree (); printf ("\n\n\n");
    Myderevo.Add(30);
    Myderevo.print_tree (); printf ("\n\n\n");
    
  */  
    
    
    Myderevo.Del(7);
    Myderevo.Del(9);
    Myderevo.print_tree();
    
    int otv=Myderevo.Search(7);
    printf("otv= %d \n",otv);
    
    
    Tree<str> Derevo;
    
    
    //char a='a', b='b';
    //char *pa, *pb;
    
    //if ( pa < pb ) { printf("aaa\n"); }
    Derevo.Add(str("abc"));
    Derevo.Add(str("xyz"));
    Derevo.Add(str("qwe"));
    Derevo.print_tree();
    
    
    //Derevo.print_tree();printf("\n\n\n");
    
    
    



    return 0;
}