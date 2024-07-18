#include <iostream>
#include <queue>
using namespace std;

// Định nghĩa cấu trúc NODE cho cây nhị phân
struct NODE {
    int key;
    NODE* p_left;
    NODE* p_right;
};

// 1. Khởi tạo một NODE từ một giá trị cho trước
NODE* createNode(int data) {
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->p_left = nullptr;
    newNode->p_right = nullptr;
    return newNode;
}

// 2. Duyệt tiền thứ tự (NLR)
void NLR(NODE* pRoot) {
    if (pRoot == nullptr) return;
    cout << pRoot->key << " ";
    NLR(pRoot->p_left);
    NLR(pRoot->p_right);
}

// 3. Duyệt trung thứ tự (LNR)
void LNR(NODE* pRoot) {
    if (pRoot == nullptr) return;
    LNR(pRoot->p_left);
    cout << pRoot->key << " ";
    LNR(pRoot->p_right);
}

// 4. Duyệt hậu thứ tự (LRN)
void LRN(NODE* pRoot) {
    if (pRoot == nullptr) return;
    LRN(pRoot->p_left);
    LRN(pRoot->p_right);
    cout << pRoot->key << " ";
}

// 5. Duyệt theo mức
void LevelOrder(NODE* pRoot) {
    if (pRoot == nullptr) return;
    queue<NODE*> q;
    q.push(pRoot);
    while (!q.empty()) {
        NODE* current = q.front();
        q.pop();
        cout << current->key << " ";
        if (current->p_left != nullptr) q.push(current->p_left);
        if (current->p_right != nullptr) q.push(current->p_right);
    }
}

// 6. Tìm và trả về một NODE với giá trị cho trước từ một cây nhị phân tìm kiếm
NODE* Search(NODE* pRoot, int x) {
    if (pRoot == nullptr || pRoot->key == x) return pRoot;
    if (x < pRoot->key) return Search(pRoot->p_left, x);
    return Search(pRoot->p_right, x);
}

// 7. Thêm một NODE với giá trị cho trước vào cây nhị phân tìm kiếm
void Insert(NODE* &pRoot, int x) {
    if (pRoot == nullptr) {
        pRoot = createNode(x);
        return;
    }
    if (x < pRoot->key) {
        Insert(pRoot->p_left, x);
    } else {
        Insert(pRoot->p_right, x);
    }
}

// 8. Xoá một NODE với giá trị cho trước từ một cây nhị phân tìm kiếm
NODE* findMin(NODE* pRoot) {
    while (pRoot->p_left != nullptr) pRoot = pRoot->p_left;
    return pRoot;
}

void Remove(NODE* &pRoot, int x) {
    if (pRoot == nullptr) return;
    if (x < pRoot->key) {
        Remove(pRoot->p_left, x);
    } else if (x > pRoot->key) {
        Remove(pRoot->p_right, x);
    } else {
        if (pRoot->p_left == nullptr) {
            NODE* temp = pRoot->p_right;
            delete pRoot;
            pRoot = temp;
        } else if (pRoot->p_right == nullptr) {
            NODE* temp = pRoot->p_left;
            delete pRoot;
            pRoot = temp;
        } else {
            NODE* temp = findMin(pRoot->p_right);
            pRoot->key = temp->key;
            Remove(pRoot->p_right, temp->key);
        }
    }
}

// 9. Khởi tạo một cây nhị phân tìm kiếm từ một mảng cho trước
NODE* createTree(int a[], int n) {
    NODE* root = nullptr;
    for (int i = 0; i < n; i++) {
        Insert(root, a[i]);
    }
    return root;
}

// 10. Xóa hoàn toàn một cây nhị phân tìm kiếm
void removeTree(NODE* &pRoot) {
    if (pRoot == nullptr) return;
    removeTree(pRoot->p_left);
    removeTree(pRoot->p_right);
    delete pRoot;
    pRoot = nullptr;
}

// 11. Tính chiều cao của một cây nhị phân tìm kiếm
int Height(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    int leftHeight = Height(pRoot->p_left);
    int rightHeight = Height(pRoot->p_right);
    return max(leftHeight, rightHeight) + 1;
}

// 12. Đếm số lượng NODE của một cây nhị phân
int countNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}

// 13. Tính tổng giá trị của toàn bộ NODEs trong một cây nhị phân
int sumNode(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    return pRoot->key + sumNode(pRoot->p_left) + sumNode(pRoot->p_right);
}

// 14. Tính toán chiều cao của một NODE với giá trị cho trước (trả về -1 nếu không tồn tại)
int heightNode(NODE* pRoot, int value) {
    NODE* node = Search(pRoot, value);
    if (node == nullptr) return -1;
    return Height(node) - 1;
}

// 15. Tính toán tầng của một NODE cho trước
int Level(NODE* pRoot, NODE* p) {
    if (pRoot == nullptr || p == nullptr) return -1;
    queue<NODE*> q;
    q.push(pRoot);
    int level = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            NODE* current = q.front();
            q.pop();
            if (current == p) return level;
            if (current->p_left != nullptr) q.push(current->p_left);
            if (current->p_right != nullptr) q.push(current->p_right);
        }
        level++;
    }
    return -1;
}

// 16. Đếm số lá của một cây nhị phân
int countLeaf(NODE* pRoot) {
    if (pRoot == nullptr) return 0;
    if (pRoot->p_left == nullptr && pRoot->p_right == nullptr) return 1;
    return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
}

// 17. Đếm số NODE của một cây nhị phân tìm kiếm mà giá trị key nhỏ hơn giá trị cho trước
int countLess(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    if (pRoot->key < x) {
        return 1 + countLess(pRoot->p_left, x) + countLess(pRoot->p_right, x);
    } else {
        return countLess(pRoot->p_left, x);
    }
}

// 18. Đếm số lượng NODE của một cây nhị phân tìm kiếm cho trước mà giá trị key lớn hơn giá trị cho trước
int countGreater(NODE* pRoot, int x) {
    if (pRoot == nullptr) return 0;
    if (pRoot->key > x) {
        return 1 + countGreater(pRoot->p_left, x) + countGreater(pRoot->p_right, x);
    } else {
        return countGreater(pRoot->p_right, x);
    }
}

// 19. Xác định cây nhị phân có phải là cây nhị phân tìm kiếm hay không
bool isBSTUtil(NODE* pRoot, NODE* left, NODE* right) {
    if (pRoot == nullptr) return true;
    if (left != nullptr && pRoot->key <= left->key) return false;
    if (right != nullptr && pRoot->key >= right->key) return false;
    return isBSTUtil(pRoot->p_left, left, pRoot) && isBSTUtil(pRoot->p_right, pRoot, right);
}

bool isBST(NODE* pRoot) {
    return isBSTUtil(pRoot, nullptr, nullptr);
}

// 20. Xác định cây nhị phân có phải là cây nhị phân tìm kiếm đầy đủ hay không
bool isFullBST(NODE* pRoot) {
    if (pRoot == nullptr) return true;
    if ((pRoot->p_left == nullptr && pRoot->p_right != nullptr) || (pRoot->p_left != nullptr && pRoot->p_right == nullptr)) return false;
    return isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right);
}

// Hàm main để kiểm tra các chức năng
int main() {
    int a[] = {15, 10, 20, 8, 12, 17, 25};
    int n = sizeof(a) / sizeof(a[0]);
    
    // Tạo cây nhị phân tìm kiếm từ mảng cho trước
    NODE* root = createTree(a, n);
    
    // Kiểm tra duyệt tiền thứ tự (NLR)
    cout << "Duyet tien thu tu (NLR): ";
    NLR(root);
    cout << endl;
    
    // Kiểm tra duyệt trung thứ tự (LNR)
    cout << "Duyet trung thu tu (LNR): ";
    LNR(root);
    cout << endl;
    
    // Kiểm tra duyệt hậu thứ tự (LRN)
    cout << "Duyet hau thu tu (LRN): ";
    LRN(root);
    cout << endl;
    
    // Kiểm tra duyệt theo mức
    cout << "Duyet theo muc: ";
    LevelOrder(root);
    cout << endl;
    
    // Kiểm tra tìm kiếm giá trị trong cây
    int searchValue = 17;
    NODE* foundNode = Search(root, searchValue);
    if (foundNode != nullptr) {
        cout << "Tim thay gia tri " << searchValue << " trong cay." << endl;
    } else {
        cout << "Khong tim thay gia tri " << searchValue << " trong cay." << endl;
    }
    
    // Kiểm tra thêm một giá trị vào cây
    int insertValue = 19;
    Insert(root, insertValue);
    cout << "Cay sau khi them gia tri " << insertValue << ": ";
    LevelOrder(root);
    cout << endl;
    
    // Kiểm tra xóa một giá trị khỏi cây
    int removeValue = 10;
    Remove(root, removeValue);
    cout << "Cay sau khi xoa gia tri " << removeValue << ": ";
    LevelOrder(root);
    cout << endl;
    
    // Kiểm tra chiều cao của cây
    cout << "Chieu cao cua cay: " << Height(root) << endl;
    
    // Kiểm tra số lượng node trong cây
    cout << "So luong node cua cay: " << countNode(root) << endl;
    
    // Kiểm tra tổng giá trị các node trong cây
    cout << "Tong gia tri cac node cua cay: " << sumNode(root) << endl;
    
    // Kiểm tra chiều cao của một node với giá trị cho trước
    int nodeHeightValue = 20;
    cout << "Chieu cao cua node co gia tri " << nodeHeightValue << ": " << heightNode(root, nodeHeightValue) << endl;
    
    // Kiểm tra số lượng lá của cây
    cout << "So luong la cua cay: " << countLeaf(root) << endl;
    
    // Kiểm tra số lượng node có giá trị nhỏ hơn giá trị cho trước
    int lessValue = 18;
    cout << "So luong node co gia tri nho hon " << lessValue << ": " << countLess(root, lessValue) << endl;
    
    // Kiểm tra số lượng node có giá trị lớn hơn giá trị cho trước
    int greaterValue = 12;
    cout << "So luong node co gia tri lon hon " << greaterValue << ": " << countGreater(root, greaterValue) << endl;
    
    // Kiểm tra cây có phải là cây nhị phân tìm kiếm hay không
    cout << "Cay co phai la cay nhi phan tim kiem hay khong: " << (isBST(root) ? "Co" : "Khong") << endl;
    
    // Kiểm tra cây có phải là cây nhị phân tìm kiếm đầy đủ hay không
    cout << "Cay co phai la cay nhi phan tim kiem day du hay khong: " << (isFullBST(root) ? "Co" : "Khong") << endl;
    
    // Xóa hoàn toàn cây
    removeTree(root);
    
    return 0;
}
