#!/usr/bin/env python3
"""
format_keymaps.py

Reformats the arguments passed to LAYOUT_ortho_4x12(...) calls found in a
C/QMK keymap file so that:

  * the arguments are laid out as rows of 12 (i.e. 4 rows for a 48-arg
    4x12 layout), and
  * the argument at a given column position starts at the same column in
    every row of every call (columns are padded to the width of the
    widest "argument," found at that position, across the whole file).

The file is edited in place. Nothing is printed on success; warnings or
errors go to stderr.

Only the standard library is used.

Usage:
    python3 format_keymaps.py input.c
"""

import argparse
import re
import sys

MACRO_NAME = "LAYOUT_ortho_4x12"
ARGS_PER_ROW = 12


def find_matching_paren(text, open_idx):
    """Given the index of an opening '(' in text, return the index of the
    matching closing ')' (balanced), or -1 if unbalanced."""
    depth = 0
    i = open_idx
    n = len(text)
    while i < n:
        c = text[i]
        if c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return i
        i += 1
    return -1


def split_top_level_args(s):
    """Split a comma-separated argument string on top-level commas only,
    i.e. ignore commas nested inside parentheses (e.g. LT(0, KC_W))."""
    args = []
    depth = 0
    current = []
    for c in s:
        if c == "(":
            depth += 1
            current.append(c)
        elif c == ")":
            depth -= 1
            current.append(c)
        elif c == "," and depth == 0:
            args.append("".join(current))
            current = []
        else:
            current.append(c)
    args.append("".join(current))
    return args


def detect_indent(content_raw):
    """Given the raw text between the outer '(' and ')' of a call, work out
    the indentation used for argument lines and for the closing paren, so
    the rewritten call matches the file's existing indentation style."""
    last_nl = content_raw.rfind("\n")
    if last_nl != -1:
        close_indent = content_raw[last_nl + 1 :]
        body = content_raw[:last_nl]
    else:
        close_indent = ""
        body = content_raw

    arg_indent = None
    for line in body.split("\n"):
        if line.strip():
            arg_indent = line[: len(line) - len(line.lstrip())]
            break
    if arg_indent is None:
        arg_indent = close_indent + "    "

    return arg_indent, close_indent


def find_calls(text):
    """Locate every LAYOUT_ortho_4x12(...) call in text and parse its
    arguments into rows of ARGS_PER_ROW. Returns a list of dicts."""
    pattern = re.compile(r"\b" + re.escape(MACRO_NAME) + r"\s*\(")
    calls = []
    for m in pattern.finditer(text):
        open_idx = m.end() - 1
        close_idx = find_matching_paren(text, open_idx)
        if close_idx == -1:
            print(
                f"Warning: unbalanced parentheses for {MACRO_NAME} call "
                f"starting at offset {m.start()}; skipping.",
                file=sys.stderr,
            )
            continue

        content_raw = text[open_idx + 1 : close_idx]
        raw_args = split_top_level_args(content_raw)
        raw_args = [re.sub(r"\s+", " ", a.strip()) for a in raw_args]
        raw_args = [a for a in raw_args if a != ""]

        if len(raw_args) % ARGS_PER_ROW != 0:
            print(
                f"Warning: {MACRO_NAME} call at offset {m.start()} has "
                f"{len(raw_args)} arguments, which is not a multiple of "
                f"{ARGS_PER_ROW}; skipping.",
                file=sys.stderr,
            )
            continue

        rows = [
            raw_args[i : i + ARGS_PER_ROW]
            for i in range(0, len(raw_args), ARGS_PER_ROW)
        ]

        arg_indent, close_indent = detect_indent(content_raw)

        calls.append(
            {
                "match_start": m.start(),
                "name_end": m.end(),
                "open_idx": open_idx,
                "close_idx": close_idx,
                "rows": rows,
                "arg_indent": arg_indent,
                "close_indent": close_indent,
            }
        )
    return calls


def update_col_widths(widths, rows):
    """Update (in place) a list of per-column widths given a call's rows.
    The width for a column is the length of the argument plus its trailing
    comma, except for the very last argument of the very last row, which
    has no trailing comma."""
    n_rows = len(rows)
    for r_idx, row in enumerate(rows):
        for c_idx, arg in enumerate(row):
            is_very_last = r_idx == n_rows - 1 and c_idx == len(row) - 1
            token_len = len(arg) if is_very_last else len(arg) + 1  # +1 for ','
            if token_len > widths[c_idx]:
                widths[c_idx] = token_len


def build_row_line(row, widths, is_last_row):
    """Build one formatted row line (no leading indentation) given the
    per-column widths."""
    parts = []
    n = len(row)
    for c_idx, arg in enumerate(row):
        is_very_last = is_last_row and c_idx == n - 1
        token = arg if is_very_last else arg + ","
        if is_very_last:
            parts.append(token)
        else:
            parts.append(token.ljust(widths[c_idx] + 1))  # +1 = min. 1 space gap
    return "".join(parts).rstrip()


def format_calls(text):
    calls = find_calls(text)
    if not calls:
        print(
            f"No {MACRO_NAME}(...) calls found (or none could be parsed).",
            file=sys.stderr,
        )
        return text

    shared_widths = [0] * ARGS_PER_ROW
    for call in calls:
        update_col_widths(shared_widths, call["rows"])

    replacements = []
    for call in calls:
        widths = shared_widths
        n_rows = len(call["rows"])
        lines = [
            call["arg_indent"] + build_row_line(row, widths, r_idx == n_rows - 1)
            for r_idx, row in enumerate(call["rows"])
        ]
        new_content = "\n" + "\n".join(lines) + "\n" + call["close_indent"]
        new_call_text = text[call["match_start"] : call["name_end"]] + new_content + ")"
        replacements.append((call["match_start"], call["close_idx"] + 1, new_call_text))

    # Apply from the end of the file backwards so earlier offsets stay valid.
    for start, end, new_text in sorted(replacements, key=lambda r: r[0], reverse=True):
        text = text[:start] + new_text + text[end:]

    return text


def main():
    parser = argparse.ArgumentParser(
        description=f"Column-align the arguments of {MACRO_NAME}(...) calls "
        f"in a C/QMK keymap file."
    )
    parser.add_argument(
        "input", help="Path to the .c file to reformat " "(edited in place)"
    )
    args = parser.parse_args()

    try:
        with open(args.input, "r", encoding="utf-8") as f:
            text = f.read()
    except OSError as e:
        print(f"Error: could not read {args.input}: {e}", file=sys.stderr)
        sys.exit(1)

    result = format_calls(text)

    try:
        with open(args.input, "w", encoding="utf-8") as f:
            f.write(result)
    except OSError as e:
        print(f"Error: could not write {args.input}: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
