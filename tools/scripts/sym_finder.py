import argparse
import os
import shutil
import subprocess
import sys
from pathlib import Path


def collect_objs(dir: Path) -> list[Path]:

    items = os.listdir(dir)
    files = []

    for item in items:
        item_path = dir / item

        if item_path.is_dir():
            files.extend(collect_objs(item_path))
        elif item_path.suffix == ".o":
            files.append(item_path)

    return files


def symbol_defined_in_obj(obj_path: Path, target_symbol: str) -> bool:

    lines = (
        subprocess.run(
            ["mips-linux-gnu-objdump", "-t", obj_path.absolute()],
            check=False,
            capture_output=True,
            text=True,
        )
        .stdout.strip()
        .splitlines()[3:]
    )  # Discard info lines, only want the symbols

    for line in lines:
        *_base_addr_and_flags, section, _size, symbol = line.strip().split()

        if section != "*UND*" and symbol == target_symbol:
            return True

    return False


def main():

    parser = argparse.ArgumentParser(
        description="Given a path to the PsyQ `lib` folder, attempts to find the object file(s) containing target symbols"
    )

    parser.add_argument("lib_path", help="Path to PsyQ `lib` folder")
    parser.add_argument(
        "targets", nargs="+", help="Space-separated list of symbol names to find"
    )

    args = parser.parse_args()

    if shutil.which("mips-linux-gnu-objdump") is None:
        print("Cannot find 'mips-linux-gnu-objdump'!")
        sys.exit(1)

    if not Path(args.lib_path).exists():
        print(f"{args.lib_path} does not exist!")
        sys.exit(1)

    if not Path(args.lib_path).is_dir():
        print(f"{args.lib_path} does is not a folder!")
        sys.exit(1)

    files = collect_objs(Path(args.lib_path))

    if len(files) == 0:
        print("Not found")
        return

    resolved = []

    for file in files:
        worklist = set(args.targets) - set(resolved)

        if len(worklist) == 0:
            break

        for entry in worklist:
            if symbol_defined_in_obj(file, entry):
                resolved.append(entry)
                print(f"Symbol '{entry}' found in {file}")


if __name__ == "__main__":
    main()
