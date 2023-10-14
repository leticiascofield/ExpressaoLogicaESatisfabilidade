#include <iostream>
#include <string>
#include <sstream>

#include "TreeNode.hpp"
#include "NodeStack.hpp"
#include "StringStack.hpp"

using namespace std;


    string replaceVariablesWithValues(string x, string values) {
        for(unsigned long int i = 0; i < x.size(); i++) {
            // Verifica se o caractere é um dígito e substitui pelo valor correspondente em values
            if(isdigit(x[i])) {
                int index = x[i] - '0'; // Converte o caractere para inteiro
                x[i] = values[index];    // Substitui pelo valor correspondente em values
            }
        }
        return x;
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

    float evaluateInfixExpressionTree(TreeNode* root){ //bool
        if(!root){
            return 0;
        }

        if(!root->left && !root->right){
            return stof(root->val); 
        }

        float left = evaluateInfixExpressionTree(root->left);
        float right = evaluateInfixExpressionTree(root->right);

        if(root->val == "|" || root->val == "&"){  // rever isso aqui, questão da negação
            return evaluate(left, right, root->val);
        } else if(root->val == "~"){
            return evaluate(right, root->val);
        } else {
            return 0;
        }
    }

    float completeValuate(string expression, string values) {
        string result = replaceVariablesWithValues(expression, values);
        TreeNode* result2 = buildInfixExpressionTree(result);
        float result3 = evaluateInfixExpressionTree(result2);
        return result3;
    }

    float satisfability(string expression, string values) {
        for(unsigned long int i = 0; i < values.size(); i++){
            if(values[i] == 'a'){
                string case0 = values;
                case0[i] = '0';
                float resultCase0 = completeValuate(expression, case0);

                string case1 = values;
                case1[i] = '1';
                float resultCase1 = completeValuate(expression, case1);
                if(resultCase0 == 1 && resultCase1 == 1){
                    return 1;
                } else {
                    return 0;
                }
            }
            if(values[i] == 'e'){
                string case0 = values;
                case0[i] = '0';
                float resultCase0 = completeValuate(expression, case0);

                string case1 = values;
                case1[i] = '1';
                float resultCase1 = completeValuate(expression, case1);
                if(resultCase0 == 1 || resultCase1 == 1){
                    return 1;
                } else {
                    return 0;
                }
            }
        }
        return completeValuate(expression, values);
    }
    
int main(){

    string comando, expressao, valoracao;
    cout << "Comando: ";
    cin >> comando;
    cin.ignore();

    if(comando == "-a"){
        cout << "Expressão: ";
        getline(cin, expressao);
        cout << "Valoração: ";
        cin >> valoracao;

        float result = completeValuate(expressao, valoracao);
        cout << "Resultado avaliação: ";
        cout << result << endl; 

    } else if(comando == "-s") {
        cout << "Expressão: ";
        getline(cin, expressao);
        cout << "Valoração: ";
        cin >> valoracao;

        float result = satisfability(expressao, valoracao);
        cout << "Resultado avaliação: ";
        cout << result << endl; 
        
    }
    return 0;
}