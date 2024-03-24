//#ifndef AVL-tree_H
//#define AVL-tree_H
#include <new>
#include<stdio.h>
#include<stdlib.h>


int maximaln(int a, int b){
	if (a>b) return a;
	return b;

}


template <class T>
class Tree;
//------------------------------------------------------------------------------------
template <class T>
class TreeNode{
    //friend TreeNode<T>* Add(TreeNode<T>* root, const T&x);
    friend class Tree<T>;
    private:
        T value;
        int balance;
        TreeNode<T>* left;
        TreeNode<T>* right;
    public:
        TreeNode(){left=right=NULL;balance=0;}
        ~TreeNode(){}
        TreeNode(T v){value=v;left=right=NULL;balance=0;}
        void pechat(){value.pechat();}
};

template<>
void TreeNode<double>::pechat(){
    printf("%.2f \n",value);
};

template<>
void TreeNode<int>::pechat(){
    printf("%d \n",value);
};


//-------------------------------------------------------------------------------------


template<class T>
class Tree{
    private:
        TreeNode<T>* myroot;
	TreeNode<T>* Add(TreeNode<T>* root, const T&x, int& grow);
	TreeNode<T>* Del(TreeNode<T>* root, const T&x, int& grow);
	int Search(TreeNode<T>* root, const T&x);
	int Glubina(TreeNode<T>* root);
	int Razmer(TreeNode<T>* root);
        void del_node(TreeNode<T>* koren){if (koren==NULL)return;
                                          del_node(koren->left);
                                          del_node(koren->right);
					  delete koren;}
        void printtree(TreeNode<T>* koren,int offset){if(koren==NULL) return;
                                                      printtree(koren->right,offset+1);
                                                      for(int i=0;i<offset;i=i+1) printf("       ");
                                                      koren->pechat();
                                                      printtree(koren->left,offset+1);}
	
                                              
                
    public:
        Tree(){myroot=NULL;}
        ~Tree(){del_node(myroot);}
        Tree(TreeNode<T>* koren){myroot=koren;}
        void Push(const T&x){int found=Search(myroot, x); 
			     if (found==1) {printf("no need to add "); x.pechat();}
			     if(found==-1) {printf("We are adding "); x.pechat();int gr=0;myroot=Add(myroot,x,gr);}}
	void Withdraw(const T&x){int found=Search(myroot, x);
				 if (found==-1) {printf("no such element\n");}
				 if (found==1) {int gr=0; myroot=Del(myroot,x,gr);}
				}
        void pechat(){printf("derevo ");printf("\n\n\n");printtree(myroot,0);printf("\n\n\n");}
	int Find(const T&x){return Search(myroot, x);}
	int Depth(){return Glubina(myroot);}
	int Size(){return Razmer(myroot);}
        
};


//----------------------------------------------------------------------------------------
template<class T>
int Tree<T>::Razmer(TreeNode<T>* root){
	int otv;
	if (root==NULL) otv=0;
	else otv= Razmer(root->left)+Razmer(root->right)+1 ;
	return otv;

}


//----------------------------------------------------------------------------------------
template<class T>
int Tree<T>::Glubina(TreeNode<T>* root){
	int otv;
	if (root==NULL) otv=0;
	else otv= maximaln(Glubina(root->left),Glubina(root->right))+1 ;
	return otv;

}

//-----------------------------------------------------------------------------------------

template<class T>
int Tree<T>::Search(TreeNode<T>* root, const T&x){
	int otv=-1;
	if (root==0) otv= -1;
	else if (x>root->value) otv= Search(root->right, x);
	else if (x<root->value) otv= Search(root->left, x);
	else  otv=1;
	return otv; 

}

//--------------------------------------------------------------------------------------------

template<class T>
TreeNode<T>* Tree<T>::Add(TreeNode<T>* root, const T&x, int& grow){
    if(root==NULL){TreeNode<T>*p=new TreeNode<T>;
                    p->value=x;
		    p->balance=0;
                    p->left=p->right=NULL;
		    grow=1;
                    return p;}
    if(x<root->value){ 
			root->left=Add(root->left,x,grow);
			if (grow==0) return root;
			TreeNode<T>* A= root;
			TreeNode<T>* B= root->left;
			TreeNode<T>* C= root->left->right;
			
			if (A->balance==-1){if(B->balance==-1){ A->balance=0;B->balance=0; grow=0;A->left=B->right;B->right=A; return B;}
					    else if(B->balance==0){ A->balance=-1;B->balance=1; grow=1;A->left=B->right;B->right=A; return B;}
					    else if(B->balance==1){ if (C->balance==-1){A->balance=1;B->balance=0;C->balance=0; grow=0;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								    else if (C->balance==0){A->balance=0;B->balance=0;C->balance=0; grow=0;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								    else if (C->balance==1){A->balance=0;B->balance=-1;C->balance=0; grow=0;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								  }
						
					    }
			else if (A->balance==0) {A->balance=-1; grow=1; return A;}
			else if (A->balance==1) {A->balance=0; grow=0; return A;}
			
		
		     }

    if(x>root->value){root->right=Add(root->right,x,grow);
			if (grow==0) {return root;}

			TreeNode<T>* A= root;
			TreeNode<T>* B= root->right;
			TreeNode<T>* C= root->right->left;
		      			
			
			

			if (A->balance==-1) {A->balance=0; grow=0; return A;}
			else if (A->balance==0) {A->balance=1; grow=1; return A;}
			else if (A->balance==1){if(B->balance==1){A->balance=0;B->balance=0; grow=0;A->right=B->left;B->left=A; return B;}
					    else if(B->balance==0){ A->balance=1;B->balance=-1; grow=1;A->right=B->left;B->left=A; return B;}
					    else if(B->balance==-1){ if (C->balance==-1){A->balance=0;B->balance=1;C->balance=0; grow=-1;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								    else if (C->balance==0){A->balance=0;B->balance=0;C->balance=0; grow=-1;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								    else if (C->balance==1){A->balance=-1;B->balance=0;C->balance=0; grow=-1;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								  }
						
					    }
			
			
		     }
    return root;


};


//-----------------------------------------------------------------------------------------------


template<class T>
TreeNode<T>* Tree<T>::Del(TreeNode<T>*root, const T&x,int& grow){
	if (x>root->value) {root->right=Del(root->right, x, grow);
				
			    if (grow==0) return root;
			TreeNode<T>* A= root;
			TreeNode<T>* B= root->left;
			TreeNode<T>* C= root->left->right;
			
			if (A->balance==-1){if(B->balance==-1){ A->balance=0;B->balance=0; grow=-1;A->left=B->right;B->right=A; return B;}
					    else if(B->balance==0){ A->balance=-1;B->balance=1; grow=0;A->left=B->right;B->right=A; return B;}
					    else if(B->balance==1){ if (C->balance==-1){A->balance=1;B->balance=0;C->balance=0; grow=-1;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								    else if (C->balance==0){A->balance=0;B->balance=0;C->balance=0; grow=-1;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								    else if (C->balance==1){A->balance=0;B->balance=-1;C->balance=0; grow=-1;
											A->left=C->right;B->right=C->left;C->left=B; C->right=A; return C;}
								  }
						
					    }
			else if (A->balance==0) {A->balance=-1; grow=-1; return A;}
			else if (A->balance==1) {A->balance=0; grow=0; return A;}

				

			   }
	else if (x<root->value) {root->left=Del(root->left, x, grow);

					if (grow==0) {return root;}

			TreeNode<T>* A= root;
			TreeNode<T>* B= root->right;
			TreeNode<T>* C= root->right->left;
		      			
			
			

			if (A->balance==-1) {A->balance=0; grow=-1; return A;}
			else if (A->balance==0) {A->balance=1; grow=0; return A;}
			else if (A->balance==1){if(B->balance==1){A->balance=0;B->balance=0; grow=-1;A->right=B->left;B->left=A; return B;}
					    else if(B->balance==0){ A->balance=1;B->balance=-1; grow=0;A->right=B->left;B->left=A; return B;}
					    else if(B->balance==-1){ if (C->balance==-1){A->balance=0;B->balance=1;C->balance=0; grow=0;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								    else if (C->balance==0){A->balance=0;B->balance=0;C->balance=0; grow=0;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								    else if (C->balance==1){A->balance=-1;B->balance=0;C->balance=0; grow=0;
											A->right=C->left;B->left=C->right;C->left=A; C->right=B; return C;}
								  }
						
					    }
			

				
				}



	else {printf("found\n");
		if ((root->right==NULL)&&(root->left==NULL)) {delete root; return NULL;}
		else if ((root->right!=NULL)&&(root->left==NULL)){TreeNode<T>*p=root->right; delete root; return p;}
		else if ((root->left!=NULL)&&(root->right==NULL)){TreeNode<T>*p=root->left; delete root; return p;}
		else if ((root->left!=NULL)&&(root->right!=NULL)){TreeNode<T>* nodeforchange=root->right;
								  while(nodeforchange->left != NULL){nodeforchange=nodeforchange->left;}
								  root->value=nodeforchange->value; root->right=Del(root->right, root->value, grow); return root;
								 }
	     }


	return root;

}


//#endif


