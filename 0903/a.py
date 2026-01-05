#!/usr/bin/env python3
import glob, os, subprocess, sys

PROG = "./f"  # program to run

def norm(data: bytes) -> bytes:
    # normalize line endings and trim trailing whitespace/newlines
    data = data.replace(b"\r\n", b"\n").replace(b"\r", b"\n")
    data = b"\n".join(line.rstrip() for line in data.split(b"\n"))
    return data.strip()

def main():
    diffs = []
    for in_path in sorted(glob.glob("*.in")):
        base, _ = os.path.splitext(in_path)
        ans_path = base + ".ans"

        if not os.path.exists(ans_path):
            diffs.append(in_path)
            continue

        try:
            with open(in_path, "rb") as f:
                proc = subprocess.run(
                    [PROG],
                    input=f.read(),
                    stdout=subprocess.PIPE,
                    stderr=subprocess.DEVNULL,
                    timeout=10,
                )
        except Exception:
            diffs.append(in_path)
            continue

        out = proc.stdout
        with open(ans_path, "rb") as f:
            ans = f.read()

        if norm(out) != norm(ans):
            diffs.append(in_path)

    for x in diffs:
        print(x)

    sys.exit(1 if diffs else 0)

if __name__ == "__main__":
    main()
