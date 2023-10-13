#include <iostream>
#include <string>
#include <sstream>

#include "TreeNode.hpp"
#include "NodeStack.hpp"
#include "StringStack.hpp"

using namespace std;

    string replaceVariablesWithValues(std::string x, std::string values) {
        for (unsigned long int i = 0; i < x.size(); i++) {
            // Verifica se o caractere é um dígito e substitui pelo valor correspondente em values
            if (isdigit(x[i])) {
                int index = x[i] - '0'; // Converte o caractere para inteiro
                x[i] = values[index];    // Substitui pelo valor correspondente em values
            }
        }
        return x;
    }

    bool isOperator (string x) {
        if(x == "|" || x == "&"){
            return true;
        } else {
            return false;
        }
    }

    bool isOperatorNegation (string x) {
        if(x == "~"){
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
        if(op == "~") return !(b != 0);
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
                    node->right = st.getTop();
                    st.pop();
                    node->left = st.getTop();
                    st.pop();
                    st.push(node);
                }
                op_st.pop();
            } else if(isOperator(token)){
                while(!op_st.isEmpty() && op_st.getTop() != "(" && getOperatorPrecedence(token) <= getOperatorPrecedence(op_st.getTop())){
                    TreeNode* node = new TreeNode(op_st.getTop());
                    op_st.pop();
                    node->right = st.getTop();
                    st.pop();
                    node->left = st.getTop();
                    st.pop();
                    st.push(node);
                }
                op_st.push(token);
            } else if(isOperatorNegation(token)){
                while(!op_st.isEmpty() && op_st.getTop() != "(" && getOperatorPrecedence(token) <= getOperatorPrecedence(op_st.getTop())){
                    TreeNode* node = new TreeNode(op_st.getTop());
                    op_st.pop();
                    node->right = st.getTop();
                    st.pop();
                    st.push(node);
                }
                op_st.push(token);
            } else{
                TreeNode* node = new TreeNode(token);
                st.push(node);
            }
        }
        while(!op_st.isEmpty()){
            TreeNode* node = new TreeNode(op_st.getTop());
            op_st.pop();
            node->right = st.getTop();
            st.pop();
            node->left = st.getTop();
            st.pop();
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
        } else {
            return evaluate(right, root->val);
        }
    }

int main(){

    string comando, expressao, valoracao;
    //cout << "Comando: ";
    //cin >> comando;
    //cin.ignore();

    //if(comando == "-a"){
        cout << "Expressão: ";
        getline(cin, expressao);
        cout << "Valoração: ";
        cin >> valoracao;
        string result = replaceVariablesWithValues(expressao, valoracao);
        cout << "Resultado valoração: ";
        cout << result << endl;
        TreeNode* aux = buildInfixExpressionTree(result);
        float aux2 = evaluateInfixExpressionTree(aux);
        cout << "Outro resultado: ";
        cout << aux2 << endl; 

    //} else {
        return 0;
    //}

}