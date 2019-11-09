#include<iostream>
#include <vector>
#include<cmath>
using namespace std;
struct pancake{
    int width;
    int parent;
    pancake(){
    }
};
struct score{
    vector<pancake> state;
    int val;
};
struct AI_computer{
    pancake best;
    bool first = true;
    int away=0;
    int active_layer=0;
    int diff_best = 0;
    int difficulty;
    AI_computer(int dif){
        difficulty = dif;
    }

    vector<pancake> flip(int index,vector<pancake> stack, int parent){
        const int size = stack.size();
        vector<pancake> ret;
        vector<pancake> stack2;
        pancake populator;
        for(int i=0;i<size;i++){
            populator.width = 0;
            populator.parent = 0;
            stack2.push_back(populator);
        }
        for(int i=0;i<=index;i++){
            stack2[i].width=stack[index-i].width;
            stack2[i].parent=parent;
        }

        for(int i=index+1;i<size;i++){
            stack2[i].width=stack[i].width;
            stack2[i].parent=parent;
        }

        for(int i=0;i<size;i++){
            ret.push_back(stack2[i]);
        }

        return ret;
    }

    int compute_score(vector<pancake> stack){
        int temp=0;
        int temp2=1;
        int no_flips=0;
        int size = stack.size();
        for(int i=0;i<size;i++){
            if ((stack[i].width-temp)/abs(stack[i].width-temp)!=temp2){
                temp2=(stack[i].width-temp)/abs(stack[i].width-temp);
                no_flips+=1;
            }
            temp=stack[i].width;

        }
        return no_flips;
    }

    vector<vector<pancake> > build_layer(vector<vector< pancake> > stack){
        int layer_size = stack.size();
        int stack_size = stack[0].size();
        vector<vector<pancake> > constructed_layer;
        vector<pancake> temp;
        for(int i = 0;i<layer_size;i++){
            for(int j=1;j<stack_size;j++){
                temp = flip(j,stack[i],stack[i][j].parent);
                constructed_layer.push_back(temp);

                if(compute_score(temp)==0 && first ){
                    best = temp[0];


                    diff_best = difficulty-active_layer;
                    first = false;
                }

            }
        }
        return constructed_layer;
    }
    vector<vector<vector<pancake > > > build_pancake_mm(int diff,vector<pancake> source){
        vector<vector<pancake > > lvl_temp;
        lvl_temp.push_back(source);
        vector<vector<vector<pancake > > > ret;
        ret.push_back(lvl_temp);
        for(int i=0;i<diff-1;i++){
            active_layer=i;
            lvl_temp = build_layer(lvl_temp);
            ret.push_back(lvl_temp);

        }
        return ret;
    }
    vector<pancake> find_min_stack(vector<vector<vector<pancake > > > tree){

        int size = tree.size();
        active_layer = difficulty-1;
        if(first){
            diff_best = difficulty - active_layer;}
        int lvl_size = tree[size-1].size();
        //cerr<<"here"<<endl;
        int stack_size = tree[size-1][0].size();
        vector<pancake> temp_stack;
        int temp_score;
        vector<pancake> min_stack;
        int min_score=1500;

        for(int j=0;j<lvl_size;j++){
            for(int k=0;k<stack_size;k++){
                temp_stack = flip(k,tree[size-1][j],tree[size-1][j][k].parent);

                temp_score = compute_score(temp_stack);
                if(temp_score<min_score){
                    min_stack = temp_stack;
                    min_score = temp_score;
                }
            }

        }
        return min_stack;
    }
    int best_width(vector<pancake> stack){
        pancake curr;
        if(!first){
            curr = best;
        }
        else{
            curr = stack[0];
        }

        int width = curr.parent;



        return width;
    }
    bool is_sorted(vector<pancake> stack){
        bool ret = true;
        int size = stack.size();
        for(int i=0;i<size-1;i++){
            if(stack[i].width > stack[i+1].width){

                ret = false;
                break;
            }
        }
        return ret;
    }
    int get_flip_index(vector<pancake> stack,int width){
        int size = stack.size();
        for(int i=0;i<size;i++){
            if(stack[i].width == width){
                return i;
            }
        }
        return -1;
    }
    vector<pancake> cvt_2_pan(vector<int> stack){
        vector<pancake> stack_vec;
        int size = stack.size();
        pancake temp_cake;
        for(int i=0;i<size;i++){
            temp_cake.parent = stack[i];
            temp_cake.width = stack[i];
            stack_vec.push_back(temp_cake);
        }
        return stack_vec;
    }
    vector<int> cvt_2_int(vector<pancake> stack){
        vector<int> stack_vec;
        int size = stack.size();

        for(int i=0;i<size;i++){

            stack_vec.push_back(stack[i].width);
        }
        return stack_vec;
    }
    int get_best_flip(vector<int> stack){
        vector<pancake> stack_vec = cvt_2_pan(stack);
        vector<vector<vector<pancake> > > tree = build_pancake_mm(difficulty,stack_vec);
        vector<pancake> best_stack = find_min_stack(tree);
        int optimal_width = best_width(best_stack);
        int flip_ind = get_flip_index(stack_vec,optimal_width);
        return flip_ind;

    }

};
// int main(){

// int stack [8] = {8,7,6,5,4,3,2,1};
// vector<int> lvl;
// pancake temp;
// int size = 8;
// AI_computer x(3);
// for(int i=0;i<size;i++){
// lvl.push_back(stack[i]);
// }
// cout<<x.get_best_flip(lvl)<<endl;
// AI_computer y(3);
// cout<<y.get_best_flip(lvl)<<endl;


// }