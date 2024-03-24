#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


template <class T>
class Tree;

template <class T>
class TreeNode{
    friend class Tree<T>;
    //friend operator==(const T a, const T b);
    private:
	T value;
	TreeNode<T> *left,*right;
	int balance;
    public:
	~TreeNode(){};
	TreeNode(){left=right=0;}
	//TreeNode(const TreeNode& b ){value=b.value;}  // we need to create all  children with equal values
	//TreeNode operator=(const TreeNode &b){va}
	
	void pechat(){ value.pechat();}
	//TreeNode<T>* Add(TreeNode* root, const T&x);
	
	//int Tcmp(const T& b){return Tcmp(value,b);}
	
    
};

template<>
void TreeNode<int>::pechat(){
    printf("value= %d \n", value);
}

template<>
void TreeNode<double>::pechat(){
    //printf("value= %f : %p <- %p -> %p\n", value, (void*)left,(void*)this,(void*)right );
    printf ("%.2f", value);
}

template<>
void TreeNode<const char *>::pechat(){
    //printf("value= %f : %p <- %p -> %p\n", value, (void*)left,(void*)this,(void*)right );
    printf ("%s ", value);
}


/*
template<>
int TreeNode<double>::Tcmp(double  a, double  b){
    if int(a)==int(b) return 1;
    else return  0;

}
*/

/*
template<class T>
int operator==(const T a, const T b){
    if int(a)==int(b) return 1;
    else return 0;


}
*/




struct Double {
    double v;
    bool operator==(const Double &x) { return fabs(v-x.v)<1.e-12; } 


};





//--------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------
template <class T>
class Tree{
    private:
//        int (*Cmp)(const T&, const T&);


	TreeNode<T> *root;
        TreeNode<T>* Add(TreeNode<T> *root,const T&x,int &grow);
        TreeNode<T>* Del(TreeNode<T> *root,const T&x,int &grow);
        int Search(TreeNode<T> *root,const T&x);
	//-------------------------------------------------------
	void print_tree (TreeNode <T> * node, int offset) {
	  if (node == NULL) return;
	  
	  print_tree (node->right, offset+1);
	    
	  for (int i = 0; i <offset; i++) {
	    printf("      ");
	  }
	  node->pechat();
	  printf ("\n");
	  
	  print_tree (node->left, offset+1);
	  
	}
	//------------------------------------------------------
	void delete_node (TreeNode<T> * node) {
	  if (node == NULL) return;
	  
	  delete_node(node->left);
	  delete_node(node->right);
	  delete node;
	}

    public:
	~Tree(){delete_node (root);}
	Tree(){root=0; }
	
	void Add(const T& x){int gr=0; root=Add(root,x,gr);}
	void Del(const T& x){ int otv=Search(root,x); if (otv == -1) printf("Cannot delete not existing element\n"); if (otv==1){int gr=0; root=Del(root,x,gr);}}
	int  Search(const T&x){int otv; otv =Search(root,x);return otv;}
	
	void print_tree () { print_tree (root, 0); }
};

//-----------------------------------------------------------------------------------------------------------------------------------


template <class T>
int Tree<T>::Search(TreeNode<T>*root,const T&x){
    int otv;
    if (root==0) otv=-1;
    else if (x>root->value) otv=Search(root->right,x);
    else if (x<root->value) otv=Search(root->left,x);
    else if (x-root->value <0.00000000001) otv=1;
    return otv;


}



//-----------------------------------------------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------------------------------------

template <class T>
TreeNode<T>* Tree<T>::Add(TreeNode<T> *root,const T&x,int &grow){

    if (root==0) {
	TreeNode<T>*p= new TreeNode<T>;
	p->value=x;
	p->left=p->right=0;
	grow=1;
	p->balance = 0;
	return p;
	}
	
//------------------------------------------------------------------
    else if (x>root->value){
    
        root->right=Add(root->right,x,grow);
        
        if(grow==0) {return root;}
        
        TreeNode<T> *A, *B, *C; 
        A = root;
        B = root->right;
        C =root->right->left;
        
	if((A->balance)==-1) {A->balance = 0; grow = 0; return A; }
        if((A->balance)==0) {A->balance = 1; grow =1; return A; }
        if((A->balance)== 1){
    				if((B->balance)== 1) {A->balance=0; B->balance =0; grow=0; A->right=B->left; B->left=A; return B;}
    				if((B->balance)== 0)  {A->balance=1; B->balance=-1; grow=1; A->right=B->left; B->left=A; return B;}
    				if((B->balance)== -1)    { if((C->balance)==0) {A->balance=0;B->balance=0;C->balance=0; grow=0; 
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C; }  
    							  if((C->balance)==-1) {A->balance=0; B->balance=1;C->balance=0; grow=0; 
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C;}   
    							  if((C->balance)==1) {A->balance=-1; B->balance=0; C->balance=0; grow=0;
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C; }   
    							}
    			    }
        
    }
    
//-------------------------------------------------------------------
    
    else if(x<root->value){
    
        root->left = Add(root->left,x,grow);
        
        if(grow==0) {return root;}
        
        TreeNode<T> *A, *B, *C; 
        A = root;
        B = root->left;
        C =root->left->right;
        
	if((A->balance)==1) {A->balance = 0; grow = 0; return A; }
        if((A->balance)==0) {A->balance = -1; grow =1; return A; }
        if((A->balance)== -1){
    				if((B->balance)== -1) {A->balance=0; B->balance =0; grow=0; A->left=B->right; B->right=A; return B;}
    				if((B->balance)== 0)  {A->balance=-1; B->balance=1; grow=1; A->left=B->right; B->right=A; return B;}
    				if((B->balance)== 1)    { if((C->balance)==0) {A->balance=0;B->balance=0;C->balance=0; grow=0; 
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C; }  
    							  if((C->balance)==1) {A->balance=0; B->balance=-1;C->balance=0; grow=0; 
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C;}   
    							  if((C->balance)==-1) {A->balance=1; B->balance=0; C->balance=0; grow=0;
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C; }   
    							}
    			    }
        
    
    }
    return root;
    
}


//-------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------


template <class T>
TreeNode<T>* Tree<T>::Del(TreeNode<T>*root, const T&x,int &grow){
    printf("searching %f rootvalue=%f  \n",x,root->value);
    
    if(fabs((x)-(root->value))<0.000000001){
    //if(int(x)==int(root->value)){
	printf("found\n");
	if  (  ((root->right)==NULL )&&(  (root->left)==NULL )  ) {printf("3333\n");delete root;grow=0; return NULL;}
	else if  (  ((root->right)!=NULL )&&(  (root->left)==NULL ) ) {printf("4444444\n");TreeNode<T>*p=root->right; delete root;grow=-1; return p;}
	else if  (  ((root->left)!=NULL  )&&(  (root->right)==NULL) ) {printf("555555\n");TreeNode<T>*p=root->left; delete root; grow=1;return p;}
	else if  (  ((root->right)!=NULL )&&(  (root->right)!=NULL) ) {printf("66666\n");TreeNode<T>* nodeforchange=root->right;
								 while(nodeforchange->left != NULL) {nodeforchange=nodeforchange->left;} 
								 root->value=nodeforchange->value; printf("value=%f \n", root->value);root->right=Del(root->right,root->value,grow);return root; }
    }
    
    //----------------------------------------------------------------------------------------------------------------------------------
    else if((x) < (root->value)) {
	printf("11111111\n");root->left=Del(root->left, x,grow);printf("grow= %d \n",grow);
	
        if(grow==0) {return root;}
        
        TreeNode<T> *A, *B, *C; 
        A = root;
        B = root->right;
        C =root->right->left;
        
	if((A->balance)==-1) {A->balance = 0; grow = -1; return A; }
        if((A->balance)==0) {A->balance = 1; grow =0; return A; }
        if((A->balance)== 1){
    				if((B->balance)== 1) {A->balance=0; B->balance =0; grow=-1; A->right=B->left; B->left=A; return B;}
    				if((B->balance)== 0)  {A->balance=1; B->balance=-1; grow=0; A->right=B->left; B->left=A; return B;}
    				if((B->balance)== -1)    { if((C->balance)==0) {A->balance=0;B->balance=0;C->balance=0; grow=-1; 
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C; }  
    							  if((C->balance)==-1) {A->balance=0; B->balance=1;C->balance=0; grow=-1; 
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C;}   
    							  if((C->balance)==1) {A->balance=-1; B->balance=0; C->balance=0; grow=-1;
    										A->right=C->left;B->left=C->right; C->left=A; C->right=B;return C; }   
    							}
    			    }
        
    }
    //-----------------------------------------------------------------------------------------------------------------------------------------
    
    else if((x) > (root->value)) {
	printf("222222\n");root->right=Del(root->right, x,grow); printf("grow %d \n",grow);
    
	
        if(grow==0) {return root;}
        
        TreeNode<T> *A, *B, *C; 
        A = root;
        B = root->left;
        C =root->left->right;
        
	if((A->balance)==1) {A->balance = 0; grow = 0; return A; }
        if((A->balance)==0) {A->balance = -1; grow =-1; return A; }
        if((A->balance)== -1){
    				if((B->balance)== -1) {A->balance=0; B->balance =0; grow=-1; A->left=B->right; B->right=A; return B;}
    				if((B->balance)== 0)  {A->balance=-1; B->balance=1; grow=0; A->left=B->right; B->right=A; return B;}
    				if((B->balance)== 1)    { if((C->balance)==0) {A->balance=0;B->balance=0;C->balance=0; grow=-1; 
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C; }  
    							  if((C->balance)==1) {A->balance=0; B->balance=-1;C->balance=0; grow=-1; 
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C;}   
    							  if((C->balance)==-1) {A->balance=1; B->balance=0; C->balance=0; grow=-1;
    										B->right=C->left;A->left=C->right; C->left=B; C->right=A;return C; }   
    							}
    			    }
        
    }
    
    
    
    return root;





}







#endif