class bst: 

    class bst_node: 
        def __init__(self, new_data:any): 
            self.data = new_data 
            self.left = None 
            self.right = None 
            self.parent = None 

    def __init__(self): 
        self.root_node = None 
        self.nr_elements = 0 

    def insert(self, new_element:any)->None: 
        run = self.root_node 
        if run is None: 
            self.root_node = self.bst_node(new_element) 
            return 
        
        while True: 
            if new_element <= run.data: 
                if run.left is None: 
                    run.left = self.bst_node(new_element) 
                    run.left.parent = run 
                    self.nr_elements += 1 
                    break 
                else: 
                    run = run.left 
            else: 
                if run.right is None: 
                    run.right = self.bst_node(new_element) 
                    run.right.parent = run
                    self.nr_elements += 1 
                    break 
                else: 
                    run = run.right

    @staticmethod               
    def search_node(root_node, data): 
        run = root_node 
        while run is not None: 
            if data == run.data: 
                return run
            elif data < run.data: 
                run = run.left 
            else: 
                run = run.right 
        return None

    def search(self, data:any)->bool:
        ret = self.search_node(self.root_node, data)
        return (ret is not None)

    def preorder_walk(self)->None: 
        def walk(node): 
            if node is not None: 
                print("[{}]<->".format(node.data), end='')
                walk(node.left)
                walk(node.right)
        print("PREORDER_WALK:[START]<->", end='') 
        walk(self.root_node) 
        print("[END]")

    def inorder_walk(self)->None: 
        def walk(node): 
            if node is not None: 
                walk(node.left)
                print("[{}]<->".format(node.data), end='')
                walk(node.right)
        print("INORDER_WALK:[START]<->", end='') 
        walk(self.root_node) 
        print("[END]")
 
    def postorder_walk(self)->None: 
        def walk(node): 
            if node is not None: 
                walk(node.left)
                walk(node.right)
                print("[{}]<->".format(node.data), end='')
        print("POSTORDER_WALK:[START]<->", end='') 
        walk(self.root_node) 
        print("[END]")

    def maximum(self)->any: 
        run = self.root_node
        if run is None: 
            return None 
        while run.right != None: 
            run = run.right 
        return run.data 

    def minimum(self)->any: 
        run = self.root_node 
        if run is None: 
            return None 
        while run.left != None: 
            run = run.left 
        return run.data 

    def inorder_successor(self, e_data:any)->any: 
        e_node = self.search_node(self.root_node, e_data)
        if e_node is None: 
            raise ValueError("Non-existent data:{}".format(e_data))
        
        if e_node.right is not None: 
            run = e_node.right 
            while run.left is not None: 
                run = run.left 
            return run.data 

        x = e_node 
        y = e_node.parent 

        while (y is not None) and (x == y.right): 
            x = y 
            y = x.parent 

        if y is None: 
            return None 
        else: 
            return y.data

    def inorder_predecessor(self, e_data:any)->any: 
        e_node = self.search_node(self.root_node, e_data)
        if e_node is None: 
            raise ValueError("Non-existent data:{}".format(e_data))
        
        if e_node.left is not None: 
            run = e_node.left 
            while run.right is not None: 
                run = run.right 
            return run.data 

        x = e_node 
        y = e_node.parent 

        while (y is not None) and (x == y.left): 
            x = y 
            y = x.parent 

        if y is None: 
            return None 
        else: 
            return y.data

    def remove(self, r_data)->None: 
        r_node = self.search_node(self.root_node, r_data)
        if r_node is None: 
            raise ValueError("Non-existent data {} for remove".format(r_data)) 
        x = r_node 
        if x.left is None: 
            if x.parent is None: 
                self.root_node = x.right  
            elif x == x.parent.left: 
                x.parent.left = x.right 
            else: 
                x.parent.right = x.right 
            if x.right is not None: 
                x.right.parent = x.parent 
        elif x.right is None: 
            if x.parent is None: 
                self.root_node = x.left 
            elif x == x.parent.left: 
                x.parent.left = x.left 
            else: 
                x.parent.right = x.left 
            x.left.parent = x.parent 
        else: 
            # 1. Find out your inorder successor 
            run = x.right 
            while run.left is not None: 
                run = run.left 
            y = run 

            # If inorder successor is not your right child 
            if y != x.right:
                # Delegate responsibility of successor's (possible) 
                # right subtree to successor's parent 
                y.parent.left = y.right 
                if y.right is not None: 
                    y.right.parent = y.parent 

                # Success takes charge of x's right subtree 
                y.right = x.right 
                y.right.parent = y 

            # Successor becomes a child of x's parent 
            # and x's parent accept successor as its child 
            # if x has no parent then y is a root node 
            if x.parent is None: 
                self.root_node = y 
            elif x == x.parent.left: 
                x.parent.left = y 
            else: 
                x.parent.right = y 
            y.parent = x.parent 

            # successor takes charge of x's left subtree 
            y.left = x.left 
            y.left.parent = y 
        
def main(): 

    L = [100, 125, 75, 175, 125, 50, 65, 80, 180]
    B = bst() 
    for x in L:
        B.insert(x)
    B.preorder_walk() 
    B.inorder_walk() 
    B.postorder_walk() 

    LC = L.copy() 
    LC.sort()
    for x in LC: 
        succ_x = B.inorder_successor(x)
        pred_x = B.inorder_predecessor(x)
        if succ_x is None: 
            print(x, "has no successor")
        else: 
            print("Succ({}):{}".format(x, succ_x))
        if pred_x is None: 
            print(x, "has no predecessor")
        else: 
            print("Pred({}):{}".format(x, pred_x))
    
    B.inorder_walk() 
    for x in L: 
        B.remove(x)
        B.inorder_walk() 

main()