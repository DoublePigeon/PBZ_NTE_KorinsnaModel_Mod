"""Detect Lua local functions used before they are declared.

UE4SS silently reports such a call as "attempt to call a nil value (global 'x')" at run time, which
cost several in-game test rounds: a `local function` is only visible from the line it appears on, so
calling it from an earlier function makes the name resolve to a global (nil).

The check is textual and conservative: it collects `local function NAME` / `local NAME =` / bare
`local NAME` declarations with their line numbers, then flags every `NAME(...)` call that appears
before the declaration line. A bare `local NAME` followed by an assignment further down is the
deliberate "declare first, assign where the helpers exist" form used for a few mutually dependent
functions, and counts as a declaration. Names that are also assigned without `local` somewhere in the
file are treated as intentional globals.

It also flags a *second* top-level `local` declaration of the same name. That is not a syntax error in
Lua: it shadows the first one, so an assignment to the "shared" variable can end up writing to a
different one - which is how a forward-declared cache ended up unused by the code that read it.
Declarations at column 0 only; shadowing inside a nested function or a loop is legitimate.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

DECL_FUNC = re.compile(r"^\s*local\s+function\s+([A-Za-z_]\w*)\s*\(")
DECL_VAR = re.compile(r"^\s*local\s+([A-Za-z_]\w*)\s*(?:,|=(?!=)|$)")
TOP_DECL = re.compile(r"^local\s+(?:function\s+)?([A-Za-z_]\w*)")
GLOBAL_ASSIGN = re.compile(r"^\s*([A-Za-z_]\w*)\s*=[^=\s]")
CALL = re.compile(r"(?<![\w.:])([A-Za-z_]\w*)\s*\(")
STRING = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


def strip_code(line: str) -> str:
    """Comments and string literals removed, so only real identifiers remain."""
    code = line.split("--", 1)[0]
    return STRING.sub('""', code)


def label(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def check(path: Path) -> int:
    lines = path.read_text(encoding="utf-8").splitlines()
    first_decl = {}
    globals_assigned = set()
    top_decls = {}
    duplicates = []
    for number, line in enumerate(lines, start=1):
        stripped = line.split("--", 1)[0]
        top = TOP_DECL.match(stripped)
        if top:
            if top.group(1) in top_decls:
                duplicates.append((number, top.group(1), top_decls[top.group(1)]))
            else:
                top_decls[top.group(1)] = number
        match = DECL_FUNC.match(stripped) or DECL_VAR.match(stripped)
        if match:
            first_decl.setdefault(match.group(1), number)
            continue
        assign = GLOBAL_ASSIGN.match(stripped)
        if assign:
            globals_assigned.add(assign.group(1))

    problems = []
    for number, line in enumerate(lines, start=1):
        code = strip_code(line)
        for match in CALL.finditer(code):
            name = match.group(1)
            declared = first_decl.get(name)
            if declared is None or globals_assigned.intersection({name}):
                continue
            if number < declared:
                problems.append((number, name, declared))

    for number, name, declared in problems:
        print(f"FAIL {label(path)}:{number}: '{name}' called before its local "
              f"declaration on line {declared}")
    for number, name, first in duplicates:
        print(f"FAIL {label(path)}:{number}: '{name}' declared local twice "
              f"(first on line {first}) - the second shadows the first")
    if not problems and not duplicates:
        print(f"ok   {label(path)}")
    return 1 if problems or duplicates else 0


def main() -> int:
    paths = [Path(p) for p in sys.argv[1:]] or sorted((ROOT / "ue4ss").rglob("*.lua"))
    failed = 0
    for path in paths:
        failed += check(path)
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
