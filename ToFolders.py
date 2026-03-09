import os
import re
import shutil
from collections import defaultdict

# Root directory containing the C++ files
ROOT_DIR = "."  # Change if needed

# Regex to extract contest number from first line
CONTEST_REGEX = re.compile(r"https://codeforces\.com/contest/(\d+)/problem/")

def get_contest_number(filepath):
    """
    Reads the first line of a file and extracts the contest number.
    Returns the contest number as a string, or None if not found.
    """
    try:
        with open(filepath, "r", encoding="utf-8") as f:
            first_line = f.readline().strip()
            match = CONTEST_REGEX.search(first_line)
            if match:
                return match.group(1)
    except Exception:
        pass
    return None


def main():
    contest_groups = defaultdict(list)

    # Scan all .cpp files in ROOT_DIR (non-recursive)
    for filename in os.listdir(ROOT_DIR):
        if filename.endswith(".cpp"):
            full_path = os.path.join(ROOT_DIR, filename)
            if os.path.isfile(full_path):
                contest_number = get_contest_number(full_path)
                if contest_number:
                    contest_groups[contest_number].append(full_path)

    # Create numbered folders and move files
    folder_index = 1
    for contest_number, files in contest_groups.items():
        if len(files) == 0:
            continue

        folder_name = str(folder_index)
        os.makedirs(folder_name, exist_ok=True)

        for file_path in files:
            destination = os.path.join(folder_name, os.path.basename(file_path))
            shutil.move(file_path, destination)

        folder_index += 1


if __name__ == "__main__":
    main()