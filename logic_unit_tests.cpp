#include "logic_unit.cpp"
struct logic_tests{
    vector<bool> test_results;
    vector<int> stack0;
    vector<int> stack1;
    vector<int> stack2;
    vector<pancake> p_stack0;
    vector<pancake> p_stack1;
    vector<pancake> p_stack2;
    int diff = 3;
    AI_computer AI = AI_computer(diff);

    logic_tests(){
        int three_pans0[3] = {3,2,1};
        int three_pans1[3] = {2,1,3};
        int five_pans0[5] = {2,1,3,4,5};
        pancake temp;
        for(int i=0;i<3;i++){
            stack0.push_back(three_pans0[i]);
            stack1.push_back(three_pans1[i]);
            temp.parent=(int)NULL;
            temp.width = three_pans0[i];
            p_stack0.push_back(temp);
            temp.width = three_pans1[i];
            p_stack1.push_back(temp);
        }
        for(int i=0;i<5;i++){
            temp.parent=(int)NULL;
            temp.width = five_pans0[i];
            stack2.push_back(five_pans0[i]);
            p_stack2.push_back(temp);
        }

    }
    bool cvt_test(){
        vector<pancake> test_vec = AI.cvt_2_pan(stack0);
        bool pass=true;
        for(int i=0;i<3;i++){
            if(test_vec[i].width!=p_stack0[i].width){
                pass = false;
            }
        }
        return pass;
    }
    bool compute_score_test(){
        int score = AI.compute_score(p_stack2);
        return score==2;
    }
    bool flip_test(){
        bool res=true;
        int test_arr[3] = {2,3,1};
        vector<pancake> flip = AI.flip(1,p_stack0,(int)NULL);
        for(int i=0;i<3;i++){

            if(flip[i].width!=test_arr[i]){
                res = false;
            }
        }
        return res;
    }
    //TO DO: Add sorted test
    bool is_sorted_test(){
        bool res=true;
        bool sorted = AI.is_sorted(p_stack2);
        if(sorted){
            res = false;
        }
        return res;
    }
    bool get_flip_index_test(){
        bool res = true;

        if(AI.get_flip_index(p_stack2,3)!=2){
            res = false;
        }
        return res;
    }
    bool get_best_flip_test(){
        int width = AI.get_best_flip(stack0);
        bool res=true;

        if(width != 2){
            res=false;
        }

        return res;
    }

    void print_test_results(){
        int size=test_results.size();
        for(int i=0;i<size;i++){
            cout<<"Test"<<(i+1)<<" result: ";
            if(test_results[i]){
                cout<<"Passed"<<endl;
            }
            else{
                cout<<"Failed"<<endl;
            }
        }
    }
    void run_tests(){
        test_results.push_back(cvt_test());
        test_results.push_back(compute_score_test());
        test_results.push_back(flip_test());
        test_results.push_back(is_sorted_test());
        test_results.push_back(get_flip_index_test());
        test_results.push_back(get_best_flip_test());
        print_test_results();

    }
};

//int main(){
//    logic_tests tests;
//    tests.run_tests();
//}