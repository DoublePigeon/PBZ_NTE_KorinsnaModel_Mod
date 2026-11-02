from minidump.minidumpfile import MinidumpFile
import sys

path = sys.argv[1]
mf = MinidumpFile.parse(path)
rec = mf.exception.exception_records[0].ExceptionRecord
code = getattr(rec.ExceptionCode, "value", rec.ExceptionCode)
addr = int(rec.ExceptionAddress)
print("code=0x%08x addr=0x%x" % (code, addr))
mods = mf.modules.modules


def find(a):
    for m in mods:
        b = int(m.baseaddress)
        s = int(m.size)
        if b <= a < b + s:
            return "%s+0x%x" % (m.name, a - b)
    return "unknown"


print("faulting:", find(addr))
