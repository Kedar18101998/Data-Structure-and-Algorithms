import random, sys

class Array_iterator: 
    def __init__(self, G): 
        self.G = G 
    def __next__(self): 
        return self.G.__next__()
        
class Array: 
    def __init__(self, N:int):
        if type(N) != int: 
            raise TypeError("Bad type for int")
        if N <= 0: 
            raise ValueError("Bad value for array size") 
        self.a = [random.randint(0, 100000) for n in range(N)]

    def sort(self) -> None: 
        for j in range(1, len(self.a)): 
            key = self.a[j]
            i = j - 1
            while i > -1 and self.a[i] > key: 
                self.a[i+1] = self.a[i]
                i = i - 1 
            self.a[i+1] = key 

    def __iter__(self): 
        def get_generator(L:list): 
            for x in L:
                yield x 
            return Array_iterator(get_generator(self.a))

    def __getitem__(self, index_or_slice): 
        if type(index_or_slice) == int: 
            return self.a[index_or_slice]
        tmpA = Array(1)
        tmpA.a = self.a[index_or_slice] 
        return tmpA 

    def __len__(self): 
        return len(self.a)

def main(argc, argv): 
    if argc != 2: 
        print("Usage Error: %s number of elements" % argv[0])
        sys.exit(-1)
    
    A = Array(int(argv[1]))

    print("Before sort:")
    for i in range(len(A)): 
        print("A[{}]:{}".format(i, A[i]))

    A.sort()

    print("After sort:")
    for i in range(len(A)): 
        print("A[{}]:{}".format(i, A[i]))

    sys.exit(0) 

main(len(sys.argv), sys.argv)

