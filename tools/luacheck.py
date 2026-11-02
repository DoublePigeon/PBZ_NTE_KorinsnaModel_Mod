"""Syntax-check the mod's Lua sources with a real Lua 5.4 parser (via lupa).

UE4SS silently swallows errors raised inside a game-thread callback, which makes a typo look like a
logic bug, so the sources are parsed before every install.
"""
import sys
from pathlib import Path

from lupa import LuaRuntime

ROOT = Path(__file__).resolve().parent.parent


def main() -> int:
    lua = LuaRuntime(unpack_returned_tuples=True)
    load = lua.eval("function(src, name) return load(src, name) end")
    failed = 0
    for path in sys.argv[1:] or sorted((ROOT / "ue4ss").rglob("*.lua")):
        path = Path(path)
        ok = True
        result = load(path.read_text(encoding="utf-8"), f"@{path}")
        if isinstance(result, tuple):
            fn, err = result
        else:
            fn, err = result, None
        if fn is None:
            ok = False
        print(f"{'ok  ' if ok else 'FAIL'} {path.relative_to(ROOT)}{'' if ok else ' -> ' + str(err)}")
        failed += 0 if ok else 1
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
