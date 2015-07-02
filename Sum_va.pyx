# definition of a structure
cdef extern from "va_sum.h":   

    ctypedef struct node_bn:
        double val;

# obviously you'll want to wrap things in terms of Python accessible classes, but this atleast demonstrates how it works
def test_sum(*args):
    cdef node_bn input_node;
    cdef node_bn* output_node_p;
    input_node.val = 5.0 # create a node, and set an initial value

    from ctypes import CDLL, c_double,c_void_p
    import os.path
    # load the Cython library with ctypes to gain access to the "sum_va" function
    # Assuming you've linked it in when you build the Cython module
    full_path = os.path.realpath(__file__)
    this_file_library = CDLL(full_path)

    # I treat all my arguments as doubles - you may need to do
    # something more sophisticated, but the idea is the same:
    # convert them to the c-type the function is expecting
    args = [ c_double(arg) for arg in args ]
    sum_va = this_file_library.sum_va
    sum_va.restype = c_void_p # it returns a pointer

    # pass the pointers as a void pointer
    # my c compiler warns me if I used int instead of long
    # but which integer type you have to use is likely system dependent
    # and somewhere you have to be careful
    output_node_p_as_integer = sum_va(c_void_p(<long>&input_node),len(args),
                           *args)

    # unfortunately getting the output needs a two stage typecast - first to a long, then to a pointer
    output_node_p = <node_bn*>(<long>(output_node_p_as_integer))
    return output_node_p.val
