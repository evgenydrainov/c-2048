import sys
if len(sys.argv) >= 2:
    print("unsigned char IMAGE_DATA[] = {{{}}};".format(
            ",".join(str(b) for b in open(sys.argv[1], "rb").read())))
else:
    print("usage:", sys.argv[0], "myimage.png")
