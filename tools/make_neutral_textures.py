"""Generate the neutral helper maps the host materials need.

The hero's master materials sample every channel through a virtual texture, so the
overrides have to be at least one VT tile (128) and are kept small and flat:
  _ARM  : R = AO 1.0, G = roughness 1.0, B = metallic 0.0  -> matte, non-metallic
  _N    : flat tangent-space normal
  Black : black mask (no grime / no extra detail)
"""
import os
import struct

OUT = r"J:\VS_Projects\PBZ_KorinsnaSkinMod\KorinsnaModel\textures"
SIZE = 256


def write_tga(name, rgb):
    """`rgb` is (R, G, B, A); a TGA stores it as B, G, R, A."""
    path = os.path.join(OUT, name + ".tga")
    red, green, blue, alpha = rgb
    stored = (blue, green, red, alpha)
    header = struct.pack("<BBBHHBHHHHBB", 0, 0, 2, 0, 0, 0, 0, 0, SIZE, SIZE, 32, 8)
    with open(path, "wb") as fh:
        fh.write(header)
        fh.write(bytes(stored) * (SIZE * SIZE))
    print("wrote", path, "rgb=", (red, green, blue))


write_tga("T_Korinsna_ARM", (255, 255, 0, 255))     # AO 1.0, roughness 1.0, metallic 0.0
write_tga("T_Korinsna_N", (128, 128, 255, 255))     # flat tangent-space normal
write_tga("T_Korinsna_White", (255, 255, 255, 255))
write_tga("T_Korinsna_Black", (0, 0, 0, 255))
