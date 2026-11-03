"""Detect Lua local functions used before they are declared.

UE4SS silently reports such a call as "attempt to call a nil value (global 'x')" at run time, which
cost several in-game test rounds: a `local function` is only visible from the line it appears on, so
calling it from an earlier function makes the name resolve to a global (nil).

The check is textual and conservative: it collects `local function NAME` / `local NAME =` declarations
with their line numbers, then flags every `NAME(...)` call that appears before the declaration line.
Names that are also assigned without `local` somewhere in the file are treated as intentional globals.
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

DECL_FUNC = re.compile(r"^\s*local\s+function\s+([A-Za-z_]\w*)\s*\(")
DECL_VAR = re.compile(r"^\s*local\s+([A-Za-z_]\w*)\s*=")
GLOBAL_ASSIGN = re.compile(r"^\s*([A-Za-z_]\w*)\s*=[^=\s]")
CALL = re.compile(r"(?<![\w.:])([A-Za-z_]\w*)\s*\(")
STRING = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'')


def strip_code(line: str) -> str:
    """Comments and string literals removed, so only real identifiers remain."""
    code = line.split("--", 1)[0]
    return STRING.sub('""', code)


def check(path: Path) -> int:
    lines = path.read_text(encoding="utf-8").splitlines()
    first_decl = {}
    globals_assigned = set()
    for number, line in enumerate(lines, start=1):
        stripped = line.split("--", 1)[0]
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
        print(f"FAIL {path.relative_to(ROOT)}:{number}: '{name}' called before its local "
              f"declaration on line {declared}")
    if not problems:
        print(f"ok   {path.relative_to(ROOT)}")
    return 1 if problems else 0


def main() -> int:
    paths = [Path(p) for p in sys.argv[1:]] or sorted((ROOT / "ue4ss").rglob("*.lua"))
    failed = 0
    for path in paths:
        failed += check(path)
    return 1 if failed else 0


if __name__ == "__main__":
    raise SystemExit(main())
