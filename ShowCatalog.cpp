#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ShowCatalog::ShowCatalog() {
    string title = "";
    int year = -1;
    string showRating = "";
    float userRating = -1;
    ShowItem* left = nullptr;
    ShowItem* right = nullptr;
    root = nullptr;
    //DONE
}

ShowCatalog::~ShowCatalog() {
    while (root) {
        if (!root->left) {
            ShowItem* temp = root;
            root = root->right;
            delete temp;
        } else {
            ShowItem* predecessor = root->left;
            while (predecessor->right && predecessor->right != root) {
                predecessor = predecessor->right;
            }

            if (!predecessor->right) {
                predecessor->right = root;
                root = root->left;
            } else {
                predecessor->right = nullptr;
                ShowItem* temp = root;
                root = root->right;
                delete temp;
            }
        }
    }
    //DONE
}

void ShowCatalog::printShowCatalog() {
    ShowItem *temp = root;
    if (root == nullptr){
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    while (temp){   
        if (temp->left == NULL)  {  
            cout << "Show: " << temp->title << " " << temp->userRating << endl;  
            temp = temp->right;  
        } else{   
            ShowItem *current = temp->left;  
            while (current->right && current->right != temp)  {
                current = current->right; 
            } 
            if (current->right == temp){  
                current->right = NULL;  
                temp = temp->right;  
            } else {  
                cout << "Show: " << temp->title << " " << temp->userRating << endl;  
                current->right = temp;  
                temp = temp->left;  
            }  
        }  
    }  

}

void ShowCatalog::getShow(string title) {
    ShowItem* temp = root;
    bool found = false;

    while (temp && !found) {
        int result = title.compare(temp->title);
        if (result == 0) {
            cout << "Show Info:" << endl;
            cout << "==================" << endl;
            cout << "Title :" << temp->title << endl;
            cout << "Year :" << temp->year << endl;
            cout << "Show Rating :" << temp->showRating << endl;
            cout << "User Rating :" << temp->userRating << endl;
            found = true;
        } else if (result < 0) {
            temp = temp->left;
        } else {
            temp = temp->right;
        }
    }

    if (!found) {
        cout << "Show not found." << endl;
    }
    //DONE
}

void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
    ShowItem *newShow = new ShowItem{title, year, showRating, userRating};
    ShowItem *temp = root;
    if (root == nullptr){
        root = newShow;
        return;
    }
    ShowItem *parent;
    while (temp != nullptr) {
        parent = temp;
        int result = newShow->title.compare(temp->title);
        if (result < 0) {
            temp = temp->left;
        } else if (result > 0) {
            temp = temp->right;
        } 
    }




    int result = newShow->title.compare(parent->title);
    if (result > 0){
            parent->right = newShow;
    } else if(result < 0) {
            parent->left = newShow;
    }
    //DONE
}

void ShowCatalog::printLeafNodes() {
    ShowItem* temp = root;

    while (temp) {
        if (!temp->left) {
            // Check if temp is a leaf node
            cout << temp->title << endl;
            temp = temp->right;
        } else {
            ShowItem* next = temp->left;
            while (next->right && next->right != temp) {
                next = next->right;
            }

            if (!next->right) {
                // Check if temp is a leaf node
                if (!temp->right) {
                    cout << temp->title << endl;
                }

                next->right = temp;
                temp = temp->left;
            } else {
                next->right = nullptr;
                temp = temp->right;
            }
        }
    }

}

void ShowCatalog::searchShows(char titleChar) {
    cout << "Shows that starts with " << titleChar << ":" << endl;
    
    if (root == nullptr){
        cout << "Tree is Empty. Cannot search Shows" << endl;
        return;
    }
    ShowItem* current = root;

    while (current) {
        if (current->left) {
            ShowItem* predecessor = current->left;
            while (predecessor->right && predecessor->right != current) {
                predecessor = predecessor->right;
            }

            if (!predecessor->right) {
                // Check if the current show's title starts with titleChar before going left
                if (current->title.front() == titleChar) {
                    cout << current->title << "(" << current->year << ") " << current->userRating << endl;
                }

                predecessor->right = current;
                current = current->left;
            } else {
                predecessor->right = nullptr;
                current = current->right;
            }
        } else {
            // Check if the current show's title starts with titleChar before going right
            if (current->title.front() == titleChar) {
                cout << current->title << "(" << current->year << ") " << current->userRating << endl;
            }

            current = current->right;
        }
    }
}

void ShowCatalog::displayNumShowRating(int &count, string showRating) {
    ShowItem *temp = root;
    while (temp){   
        if (temp->left == NULL)  {  
            if (temp->showRating == showRating){
                count+=1;
            }  
            temp = temp->right;  
        } else{   
            ShowItem *current = temp->left;  
            while (current->right && current->right != temp)  {
                current = current->right; 
            } 
            if (current->right == temp){  
                current->right = NULL;  
                temp = temp->right;  
            } else {  
                if (temp->showRating == showRating){
                    count+=1;
                }  
                current->right = temp;  
                temp = temp->left;  
            }  
        }  
    } 
    
    
}
