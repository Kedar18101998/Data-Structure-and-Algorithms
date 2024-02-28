import sys 
from traceback import print_tb 

def print_exc_info(): 
    exc_name, exc_data, exc_tb = sys.exc_info() 
    print_tb(exc_tb)
    print(exc_name, exc_data, sep=':')

def main(argc, argv): 
    if argc != 3: 
        print("Usage Error: %s file name" % argv[0])
        sys.exit(-1)
    
    try: 
        f_src = open(argv[1])
        f_dest = open(argv[2], "w")
        
        for line in f_src: 
            if line.startswith('v'): 
                print(line, file=f_dest, end='')
            elif line.startswith('f'):
                op_line = "f"
                lst = line.split()
                for entry in lst[1:]: 
                    L = entry.split("/") 
                    op_line += " " + L[0]
                print(op_line, file=f_dest)
        
        f_src.close() 
        f_dest.close() 
    except: 
        print_exc_info()

    sys.exit(0)

main(len(sys.argv), sys.argv)