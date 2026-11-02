import struct, os
out = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\KorinsnaModel\textures"


def write_tga(path, w, h, bgra):
    hdr = struct.pack("<BBBHHBHHHHBB", 0, 0, 2, 0, 0, 0, 0, 0, w, h, 32, 8)
    with open(path, "wb") as f:
        f.write(hdr)
        f.write(bytes(bgra) * (w * h))


# stored as B,G,R,A so the sampled colours are:
# 0 red, 1 green, 2 blue, 3 yellow, 4 magenta, 5 cyan, 6 orange, 7 purple
palette = [(0, 0, 255), (0, 255, 0), (255, 0, 0), (0, 255, 255),
           (255, 0, 255), (255, 255, 0), (0, 128, 255), (255, 0, 128)]
for i, (b, g, r) in enumerate(palette):
    write_tga(os.path.join(out, "T_Palette_%d.tga" % i), 32, 32, (b, g, r, 255))
print("palette written")
