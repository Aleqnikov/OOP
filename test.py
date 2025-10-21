#!/usr/bin/env python3
"""
gather_sources.py

Собирает содержимое всех .h и .cpp файлов из директории (рекурсивно)
в один текстовый файл. По умолчанию файлы копируются (исходники остаются).
Опция --delete удаляет исходные файлы после добавления (т.е. перемещает содержимое).
"""

import argparse
from pathlib import Path
import sys

def gather(root: Path, out_file: Path, delete: bool = False, encoding: str = "utf-8"):
    if not root.exists():
        raise FileNotFoundError(f"Root path does not exist: {root}")
    # Откроем выходной файл в режиме добавления (создастся, если нет)
    with out_file.open("a", encoding=encoding, errors="replace") as outf:
        for p in root.rglob("*"):
            if p.is_file():
                suffix = p.suffix.lower()
                if suffix in {".h", ".hpp", ".cpp", ".cxx", ".cc"}:
                    try:
                        content = p.read_text(encoding=encoding, errors="replace")
                    except Exception as e:
                        # Если чтение по какой-то причине не получилось — отметим это и пропустим
                        outf.write(f"\n--- FAILED TO READ: {p} ({e}) ---\n")
                        continue
                    rel = p.relative_to(root)
                    header = (
                        f"\n\n--- FILE: {rel} ---\n"
                        f"Path: {p}\n"
                        f"Size: {p.stat().st_size} bytes\n"
                        f"--- BEGIN ---\n"
                    )
                    footer = f"\n--- END: {rel} ---\n"
                    outf.write(header)
                    outf.write(content)
                    outf.write(footer)
                    # Если требуется удалить исходник
                    if delete:
                        try:
                            p.unlink()
                        except Exception as e:
                            outf.write(f"\n--- FAILED TO DELETE: {p} ({e}) ---\n")

def parse_args():
    ap = argparse.ArgumentParser(description="Gather .h/.cpp files into one text file.")
    ap.add_argument("root", nargs="?", default=".", help="Root directory to search (default: current dir)")
    ap.add_argument("-o", "--output", default="combined_sources.txt", help="Output text file (default: combined_sources.txt)")
    ap.add_argument("--delete", action="store_true", help="Delete original files after adding (move instead of copy). Use with caution.")
    ap.add_argument("--encoding", default="utf-8", help="File encoding to use for reading/writing (default: utf-8)")
    return ap.parse_args()

def main():
    args = parse_args()
    root = Path(args.root).resolve()
    out_file = Path(args.output).resolve()

    # Предупреждение, если выходной файл находится внутри обрабатываемой директории
    if out_file.exists() and out_file.samefile(root):
        print("Output file is the same as the root directory — aborting.", file=sys.stderr)
        sys.exit(1)
    # Если выходной файл лежит в дереве, добавление может включать сам себя — избегаем этого by writing to temp first.
    try:
        gather(root, out_file, delete=args.delete, encoding=args.encoding)
        print(f"Done. Appended .h/.cpp contents from '{root}' to '{out_file}'.")
        if args.delete:
            print("Original files were deleted (delete flag was set).")
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(2)

if __name__ == "__main__":
    main()

