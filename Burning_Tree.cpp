Input:      
          1
        /   \
      2      3
    /  \      \
   4    5      6
       / \      \
      7   8      9
                   \
                   10
Target Node = 8
Output: 7
Explanation: If leaf with the value 
8 is set on fire. 
After 1 sec: 5 is set on fire.
After 2 sec: 2, 7 are set to fire.
After 3 sec: 4, 1 are set to fire.
After 4 sec: 3 is set to fire.
After 5 sec: 6 is set to fire.
After 6 sec: 9 is set to fire.
After 7 sec: 10 is set to fire.
It takes 7s to burn the complete tree.
  
CODE:

class Solution {
  public:
   Node* solve(Node* root, int target, unordered_map<Node*,Node*>&parent){
       queue<Node*>q;
       Node*targetNode=0;
       q.push(root);
       parent[root]=0;
       while(!q.empty()){
           Node* front=q.front();
           q.pop();
           if(front->data==target){
               targetNode=front;
           }
          if(front->left){
              q.push(front->left);
              parent[front->left]=front;
          }
          if(front->right){
              q.push(front->right);
              parent[front->right]=front;
          }
       }
       return targetNode;
   }
   int Burntime( Node* targetNode, unordered_map<Node*,Node*>&parent){
       unordered_map<Node*,bool>isBurn;
       queue<Node*>q;
       int t=0;
       q.push(targetNode);
       isBurn[targetNode]=true;
       while(!q.empty()){
           int size=q.size();
           bool isFireSpread=0; //agar fire spread hogi tabhi time increment hoga
           for(int i=0;i<size;++i){
               Node*front=q.front();
               q.pop();
               if(front->left && isBurn[front->left]==false){
                   q.push(front->left);
                   isBurn[front->left]=true;
                   isFireSpread=1;
               }
                if(front->right && isBurn[front->right]==false){
                   q.push(front->right);
                   isBurn[front->right]=true;
                   isFireSpread=1;
               }
               if(parent[front] && isBurn[parent[front]]==false){
                   q.push(parent[front]);
                   isBurn[parent[front]]=true;
                   isFireSpread=1;
               }
               
           }
           if(isFireSpread==1){
               t++;
           }
           
       }
       return t;
       
   }
    int minTime(Node* root, int target) 
    {
      unordered_map<Node*,Node*>parent;
      Node* targetNode= solve(root,target,parent);
      return Burntime(targetNode,parent);
    }
};
