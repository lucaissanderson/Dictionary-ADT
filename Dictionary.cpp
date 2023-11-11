/****************************************
 *  Dictionary.cpp
 *  lzsander
 *  Dictionary function implementation
 * **************************************/

#include "Dictionary.h"

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    // recursive call with multiple base cases
    if(!num_pairs) return;
    if(R->left != nil) inOrderString(s, R->left);
    s += R->key + " : " + std::to_string(R->val) + "\n";
    if(R->right != nil) inOrderString(s, R->right);
}

// preOrderString()
// appends to s everything in R's subtree in preorder
void Dictionary::preOrderString(std::string& s, Node* R) const{
    // recursive call with multiple base cases
    if(!num_pairs) return;
    s += R->key + "\n";
    if(R->left != nil) preOrderString(s, R->left);
    if(R->right != nil) preOrderString(s, R->right);
}

// postOrderDelete()
// recursively delete R's subtree in postorder
void Dictionary::postOrderDelete(Node* R){
    if(R->right!=nil) postOrderDelete(R->right);
    if(R->left!=nil) postOrderDelete(R->left);
    delete R;
}

// search()
// returns node matching key k
Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const{
    // iterative 
    while(R!=nil && k!=R->key){
        if(k < R->key) R = R->left;
        else R = R->right;
    }
    return R;
}

// findMin()
// returns left-most node
Dictionary::Node* Dictionary::findMin(Dictionary::Node* R){
    while(R->left!=nil){
        R = R->left;
    }
    return R;
};

// findMax()
// returns right-most node
Dictionary::Node* Dictionary::findMax(Dictionary::Node* R){
    while(R->right!=nil){
        R = R->right;
    }
    return R;
}

// findNext()
// returns next node from inorder walk
Dictionary::Node* Dictionary::findNext(Dictionary::Node* R){
    Node* y;
    if(R->right != nil){
        return findMin(R->right);
    }
    y = R->parent;
    while(y!=nil && R==y->right){
        R = y;
        y = y->parent;
    }
    return y;
}

// findPrev()
// returns previous node from inorder walk
Dictionary::Node* Dictionary::findPrev(Dictionary::Node* R){
    Node* y;
    if(R->left != nil){
        return findMax(R->left);
    }
    y = R->parent;
    while(y!=nil && R==y->left){
        R = y;
        y = y->parent;
    }
    return y;
}

// transplant()
// make u parent of v's children and make v sibling of u
void Dictionary::transplant(Dictionary::Node* u, Dictionary::Node* v){
    if(u->parent==nil) root = v;
    else if(u==u->parent->left) u->parent->left = v;
    else u->parent->right = v;
    if(v!=nil) v->parent = u->parent;
}

// inOrderCopy()
// executes a copy from x's subtree onto this
void Dictionary::inOrderCopy(Node* x){
    if(x != nil){
        inOrderCopy(x->left);
        this->setValue(x->key, x->val);
        inOrderCopy(x->right);
    }
}


// Constructor/Destructors ------------------------------

// node constructor
// define node constructor
Dictionary::Node::Node(keyType k, valType v){
    val = v;
    key = k;
}

// create dictionary of empty state
// define Dictionary constructor
Dictionary::Dictionary(){
    num_pairs = 0;
    nil = nullptr;
    root = nullptr;
    current = nullptr;
}

// create copy
// copy D onto this
Dictionary::Dictionary(const Dictionary& D){
    // parameters
    num_pairs = D.size();
    nil = nullptr;
    root = nil;
    current = nil;
    // copy dynamic members
    Node* N = D.root;
    inOrderCopy(N);
}

// destroy dictionary
// destry dynamic members and lets C++ take care of rest
Dictionary::~Dictionary(){
    if(num_pairs) postOrderDelete(root);
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return num_pairs;
}

// contains()
// returns true if this contains node with k, false otherwise
bool Dictionary::contains(keyType k) const{
    return search(root,k) != nil ? true : false;
}

// getValue()
// return reference to value at key k
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{

    if(!contains(k)) throw std::logic_error("Dictionary: getValue(): does not contain k");

    Node* N = root;

    while(N != nil){
        if(N->key == k) break;
        else if(N->key < k) N = N->right;
        else N = N->left;
    }

    return N->val;

};

// hasCurrent()
// returns true if cursor defined, false otherwise
bool Dictionary::hasCurrent() const{

    return current == nil ? false : true;

};

// currentKey()
// returns the key of the current node
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{

    if(!hasCurrent()) throw std::logic_error("Dictionary: currentKey(): current not set");

    return current->key;

};

// currentVal()
// returns value reference of current node
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{

    if(!hasCurrent()) throw std::logic_error("Dictionary: currentVal(): current not set");

    return current->val;

}



// Manipulation procedures -------------------------------------------------

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){

    Node* z;
    Node* y = nil;
    Node* x = root;
    while(x != nil){
        // pair exists
        if(k == x->key){
            x->val = v;
            return;
        }
        y = x;
        if(k  < x->key){
            x = x->left;
        } else x = x->right;
    }
    z = new Node(k,v);
    if(y == nil){
        root = z;
    } else if(z->key < y->key){
        y->left = z;
    } else{ 
        y->right = z;
    }

    z->parent = y;
    z->left = nil;
    z->right = nil;

    num_pairs++;

}

// remove()
// deletes node with key k
// Pre: contains(k)
void Dictionary::remove(keyType k){

    Node* z = search(root,k);
    Node* y;
    if(z==nil) throw std::logic_error("Dictionary: remove(): does not contain k");

    if(z->left == nil){
        transplant(z, z->right);
    } else if(z->right==nil){
        transplant(z, z->left);
    } else {
        y = findMin(z->right);
        if(y->parent!=z){
            transplant(y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z,y);
        y->left = z->left;
        y->left->parent = y;
    }

    num_pairs--;

    delete z;

}

// clear()
// set this to zero state
void Dictionary::clear(){
    if(num_pairs) postOrderDelete(root);
    num_pairs = 0;
    root = nil;
    current = nil;
}

// begin()
// set current node to smallest value
void Dictionary::begin(){
    if(!num_pairs) throw std::logic_error("Dictionary: begin(): empty dictionary");
    current = findMin(root);
}

// end()
// set current node to largest value
void Dictionary::end(){
    if(!num_pairs) throw std::logic_error("Dictionary: end(): empty dictionary");
    current = findMax(root);
}

// next()
// set current to next node in inorder walk
// Pre: hasCurrent()
void Dictionary::next(){
    if(!hasCurrent()) throw std::logic_error("Dictionary: next(): current not set");
    current = findNext(current);
}

// prev()
// set current to prev node in inorder walk
// Pre: hasCurrent()
void Dictionary::prev(){
    if(!hasCurrent()) throw std::logic_error("Dictionary: prev(): current not set");
    current = findPrev(current);
}

// Other functions --------------------------------------------------------

// to_string()
// returns string of dictionary, inorder walk
std::string Dictionary::to_string() const{

    std::string s = "";
    inOrderString(s, root);
    return s;

};

// pre_string()
// returns string of dictionary, preorder walk
std::string Dictionary::pre_string() const{

    std::string s = "";
    preOrderString(s, root);
    return s;

}

// equals()
// returns true if equal, false otherwise
bool Dictionary::equals(const Dictionary& D) const{

    return this->to_string()==D.to_string();

};

// overloaded -------------------------------------------------

// stream
// returns file stream of to_string()
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.Dictionary::to_string();
}

// operator==()
// overload for equals()
bool operator==(const Dictionary& A, const Dictionary& B){
    return A.equals(B);
}

// operator=()
// overwrite this with D
Dictionary& Dictionary::operator=( const Dictionary& D ){
    this->clear();
    // parameters
    nil = nullptr;
    root = nil;
    current = nil;
    // copy dynamic members
    Node* N = D.root;
    inOrderCopy(N);
    return *this;
};
