#include <iostream>
#include <string>
#include <sstream>

#include "TreeNode.hpp"
#include "NodeStack.hpp"
#include "StringStack.hpp"

using namespace std;

    string removeDoubleNegation(string expression) {
        string result = expression;
        size_t length = expression.length();
        for (size_t i = 0; i < length - 2; ++i) {
            if (result[i] == '~' && result[i + 2] == '~') {
                result.erase(i, 4);
                length -= 2;
                --i;
            }
        }
        return result;
    }

    string replaceVariablesWithValues(string x, string values) { // Substitui a variável pelo seu valor (para casos 1 ou 2 dígitos)
        string result = "";
        unsigned long int i = 0;

        while (i < x.size()) {
            string result = "";
            unsigned long int i = 0;

            while (i < x.size()) {
                if (isdigit(x[i])) {
                    int num = 0;
                    if (i + 1 < x.size() && isdigit(x[i + 1])) {
                        num = (x[i] - '0') * 10 + (x[i + 1] - '0');
                        i += 2;
                    } else {
                        num = x[i] - '0';
                        i++;
                    }
                    if (num >= 0 && num <= 99 && num < values.size()) {
                        result += values[num];
                    } else {
                        result += to_string(num);
                    }
                } else {
                    result += x[i];
                    i++;
                }
            }
            return result;
        }
    }

    bool isOperator (string x) {
        if(x == "~" || x == "|" || x == "&"){
            return true;
        } else {
            return false;
        }
    }

    int getOperatorPrecedence(string op){
        if(op == "|") return 1;
        if(op == "&") return 2;
        if(op == "~") return 3;
        return 0;
    }

    float evaluate(float a, float b, string op){
        if(op == "|") return a || b;
        if(op == "&") return a && b;
        return 0;
    }

    float evaluate(float b, string op){
        if(op == "~") return !b;
        return 0;
    }


    TreeNode* buildInfixExpressionTree(string infix){
        NodeStack st;
        StringStack op_st;
        stringstream ss(infix);
        string token;
        while (ss >> token){
            if(token == "("){
                op_st.push(token);
            } else if(token == ")"){
                while(op_st.getTop() != "("){
                    TreeNode* node = new TreeNode(op_st.getTop());
                    op_st.pop();
                    if(node->val == "~"){
                        node->right = st.getTop();
                        st.pop();
                    } else{
                        node->right = st.getTop();
                        st.pop();
                        node->left = st.getTop();
                        st.pop();
                    }
                    st.push(node);
                }
                op_st.pop();
            } else if (isOperator(token)) {
                while (!op_st.isEmpty() && op_st.getTop() != "(" && getOperatorPrecedence(token) <= getOperatorPrecedence(op_st.getTop())) {
                    TreeNode* node = new TreeNode(op_st.getTop());
                    op_st.pop();
                    if (node->val == "~") {
                        node->right = st.getTop();
                        st.pop();
                    } else {
                        node->right = st.getTop();
                        st.pop();
                        node->left = st.getTop();
                        st.pop();
                    }
                    st.push(node);
                }
                op_st.push(token);
            } else {
                TreeNode* node = new TreeNode(token);
                st.push(node);
            }
        }

        while(!op_st.isEmpty()){
            TreeNode* node = new TreeNode(op_st.getTop());
            op_st.pop();
            if (node->val == "~") {
                node->right = st.getTop();
                st.pop();
            } else {
                node->right = st.getTop();
                st.pop();
                node->left = st.getTop();
                st.pop();
            }
            st.push(node);
        }
        return st.getTop();
    }

    float evaluateInfixExpressionTree(TreeNode* root) {
        if (!root) {
            return 0;
        }

        if (!root->left && !root->right) {
            return stof(root->val);
        }

        if (root->val == "|") {
            float left = evaluateInfixExpressionTree(root->left);
            float right = evaluateInfixExpressionTree(root->right);
            return left || right;
        } else if (root->val == "&") {
            float left = evaluateInfixExpressionTree(root->left);
            float right = evaluateInfixExpressionTree(root->right);
            return left && right;
        } else if (root->val == "~") {
            float right = evaluateInfixExpressionTree(root->right);
            return !right; // Inverte o valor
        }

        return 0;
    }


    float completeEvaluate(string expression, string values) {
        if(expression.size() > 1){
            string result = replaceVariablesWithValues(expression, values);
            string result2 = removeDoubleNegation(result);
            TreeNode* result3 = buildInfixExpressionTree(result2);
            float result4 = evaluateInfixExpressionTree(result3);
            return result4;
        } else if (values[0] == '0') {
            return 0;
        } else {
            return 1;
        }
    }

    float satisfability(string expression, string& values) {
        for(unsigned long int i = 0; i < values.size(); i++){
            if(values[i] == 'a'){
                string case0 = values;
                case0[i] = '0';
                float resultCase0 = satisfability(expression, case0);

                string case1 = values;
                case1[i] = '1';
                float resultCase1 = satisfability(expression, case1);
                if(resultCase0 == 1 && resultCase1 == 1){
                    return 1;
                } else {
                    return 0;
                }
            }

            if(values[i] == 'e'){
                string case0 = values;
                case0[i] = '0';
                float resultCase0 = satisfability(expression, case0);

                string case1 = values;
                case1[i] = '1';
                float resultCase1 = satisfability(expression, case1);
                if(resultCase0 == 1 && resultCase1 == 1){
                    values[i] = 'a';
                    return 1;
                } else if(resultCase0 == 1){
                    values = case0;
                    return 1;
                } else if(resultCase1 == 1){
                    values = case1;
                    return 1;
                }
                else {
                    return 0;
                }
            } 
        }
        return completeEvaluate(expression, values);
    }

    string changeEtoA (string values){
        string result = values;
        for(unsigned long int i = 0; i < values.size(); i++){
            if(values[i] == 'e'){
                result[i] = 'a';
            }
        }
        return result;
    }

int main(int argc, char *argv[]){

    string expression = argv[2];
    string values = argv[3];
    float result;

    switch (argv[1][1]) {
        case 'a':

            result = completeEvaluate(expression, values);
            cout << result << endl;
            break;

        case 's':

            result = satisfability(expression, values);
            values = changeEtoA(values);
            if(result == 1){
                cout << result << " " << values << endl; 
            } else {
            cout << result << endl; 
            }
    }

    return 0;
}