import sys

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
#
sys.path.extend([".", ".."])

# from pycparser import parse_file
import pycparser as pyc

if __name__ == "__main__":
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        filename = "examples/c_files/year.c"

    ast = pyc.parse_file(
        filename,
        use_cpp=True,
        cpp_path="gcc",
        cpp_args=["-std=c99", "-E", r"-Iutils/fake_libc_include"],
    )
    ast.show(showcoord=True)
    print("AST type {}".format(type(ast)))
    # for fieldname, value in ast.iter_fields(ast):
    #     print(fieldname)
    #     print(value)
    # print("Children nodes \n")
    # print(ast.ext[0])
    # print(ast.ext[0].decl.name)  # get fumctions' name

    for i in range(0, len(ast.ext)):
        if isinstance(ast.ext[i], pyc.c_ast.FuncDef):
            print("function")
        elif isinstance(ast.ext[i], pyc.c_ast.Typedef):
            print("typedef")
        elif isinstance(ast.ext[i], pyc.c_ast.FuncDecl):
            print("func_decl")
        elif isinstance(ast.ext[i], pyc.c_ast.FuncCall):
            print("function CALL")
